//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Main.h"
#include "DLE.h"
#include "PUBLIC.h"
#include "RS232.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//---------------------------------------------------------------------------
int iDLE_RxLen,iDLE_TxLen;
BYTE baDLE_RxBuf[d_DLE_BUF_MAX],baDLE_TxBuf[d_DLE_BUF_MAX];
extern HANDLE hComm232[256];
#pragma package(smart_init)
//RS232 DLE Protocol Communication
void ResetDLEValue(void)
{
	memset(baDLE_RxBuf,0x00,d_DLE_BUF_MAX);
	memset(baDLE_TxBuf,0x00,d_DLE_BUF_MAX);
	iDLE_RxLen = 0;
	iDLE_TxLen = 0;
}
//---------------------------------------------------------------------------
BYTE Cal_ConLRC(BYTE Olrc, BYTE *buf, int len) 
{
    int i ;
    BYTE lrc; 
    BYTE LrcBuf[1024];
    lrc = 0;
    
    memset(LrcBuf,0x00,sizeof(LrcBuf));
    LrcBuf[0] = Olrc;
    memcpy(&LrcBuf[1],&buf[0],len);
    for (i = 0; i < len+1; i++)
        lrc ^= LrcBuf[i];
    return lrc; 
}
//---------------------------------------------------------------------------
BYTE Cal_LRC(BYTE *babuf, int ilen)
{
    int i ;
    BYTE lrc; 
    lrc = 0;

    for (i = 0; i < ilen; i++)
        lrc ^= babuf[i];
    return lrc;
}
//---------------------------------------------------------------------------
BYTE CheckDLEData(void)
{
	BYTE LRC;

	LRC = Cal_LRC(baDLE_RxBuf,iDLE_RxLen-1);	//calculate lrc but lrc itself cannot be calculated included
	if (baDLE_RxBuf[iDLE_RxLen-1]!= LRC)
		return d_FAILED;
	baDLE_RxBuf[iDLE_RxLen-1] = '\0';	//drop LRC
	iDLE_RxLen --;
    return d_OK;
}
//---------------------------------------------------------------------------

BYTE RS232_DLE_SEND(String sComNo,USHORT usMS)
{
	BYTE LRC;
    BYTE baPackSendBuf[d_DLE_BUF_MAX+20];
    int i,idx,iPackLen;

	LRC = 0;
	iPackLen = 0;
	memset(baPackSendBuf,0x00,d_DLE_BUF_MAX+20);
	baPackSendBuf[iPackLen++] = 0x10;
	baPackSendBuf[iPackLen++] = 0x02;

	for (i=0 ; i<iDLE_TxLen ; i++)
		{
			LRC ^= baDLE_TxBuf[i];
			if (baDLE_TxBuf[i] != 0x10)
				baPackSendBuf[iPackLen++] = baDLE_TxBuf[i];
			else
			{
				baPackSendBuf[iPackLen++] = 0x10;
				baPackSendBuf[iPackLen++] = 0x10;
			}
		}
	baPackSendBuf[iPackLen++] = LRC;
	if (LRC == 0x10)
		baPackSendBuf[iPackLen++] = LRC;
	baPackSendBuf[iPackLen++] = 0x10;
	baPackSendBuf[iPackLen++] = 0x03;

    idx = ED_GetCOMIndex(sComNo);
    if(idx == 0)
        return d_DLE_COM_PORT_ERR;
    if(hComm232[idx] == 0)
        return d_DLE_COM_NOT_INITIAL;
    if(iPackLen>(d_DLE_BUF_MAX+20))
        return d_DLE_TX_BUF_OVERFLOW;
	if(ED_SendString(sComNo,baPackSendBuf,iPackLen,usMS)!=d_OK)
		return d_DLE_TX_FAILED;
    return d_OK;
}
//---------------------------------------------------------------------------
BYTE RS232_DLE_RECV(String sComNo,USHORT usWaitMS)
{
	SHORT Getch;
    int i,idx,i232RxLen,i232RxTotalLen;
	BYTE C,isGetSTX,isGetDLE,RecvOK,ba232Rx[d_DLE_BUF_MAX],ba232RxTmp[d_DLE_BUF_MAX];
	isGetDLE = FALSE;
	isGetSTX = FALSE;
    RecvOK = FALSE;

    idx = ED_GetCOMIndex(sComNo);
    if(idx == 0)
        return d_DLE_COM_PORT_ERR;
    if(hComm232[idx] == 0)
        return d_DLE_COM_NOT_INITIAL;

    i232RxLen = 0;
    i232RxTotalLen = 0;
    memset(ba232Rx,0x00,d_DLE_BUF_MAX);
	//iRLen=Ed_ReceiveString(sComNo,baRxBuf,d_WAITING_MODE_LEN,usLen,usWaitMS);
    ED_SetTimeOutMS(usWaitMS);
    while(1)
    {
        if(ED_CheckRS232(sComNo) != d_FAILED)
        {
            i232RxLen = ED_RS232ReadFile(sComNo,ba232RxTmp);
            memcpy(&ba232Rx[i232RxTotalLen],&ba232RxTmp[0],i232RxLen);
            i232RxTotalLen+=i232RxLen;
            memset(ba232RxTmp,0x00,d_DLE_BUF_MAX);
        }
        else
        {
            //10 02 CmdID*1 Ststus*4 Datalen*2 LRC*1 10 03
            if((i232RxTotalLen>=12)&&(ba232Rx[0] == d_DLE)&&(ba232Rx[1] == d_STX)&&(ba232Rx[i232RxTotalLen-2] == d_DLE)&&(ba232Rx[i232RxTotalLen-1] == d_ETX))
                break;
            if(ED_CheckTimeOut() == d_YES)
                return d_DLE_RX_TIMEOUT;
        }
        Application->ProcessMessages();
    }
    memset(baDLE_RxBuf,0x00,d_DLE_BUF_MAX);
	for(i=0;i<i232RxTotalLen;i++)
		{
			if (iDLE_RxLen >= d_DLE_BUF_MAX)
			{
				iDLE_RxLen = 0;		//Reset
                return d_DLE_RX_BUF_OVERFLOW;
			}
			Getch = (BYTE) ba232Rx[i];
			C = (BYTE) Getch;
			if(isGetDLE == FALSE && C == d_DLE)
				isGetDLE = TRUE;
			else if (isGetDLE == TRUE && C == d_STX)
			{
				iDLE_RxLen = 0;
				isGetSTX = TRUE;
				isGetDLE = FALSE;
			}
			else if( isGetSTX == TRUE && isGetDLE == TRUE && C == d_ETX)
			{
				if(CheckDLEData()!= d_OK)
                    return d_DLE_RX_LRC_ERR;
                RecvOK = TRUE;
                isGetSTX = isGetDLE = FALSE;
                break;
			}
			else if (isGetSTX == TRUE)
			{
				if (isGetDLE == TRUE && C == d_DLE)
				{
					baDLE_RxBuf[iDLE_RxLen++] = C;//Add 0x10 to buf
					isGetDLE = FALSE;
				}
				else if (isGetDLE == TRUE)
				{
					//Error block data
					iDLE_RxLen = 0;
					isGetSTX = FALSE;
					isGetDLE = FALSE;
				}
				else
				{
					baDLE_RxBuf[iDLE_RxLen] = C;
					iDLE_RxLen ++;
				}
			}
			else
				isGetDLE = FALSE;
		}
    if(RecvOK == TRUE)
        return d_OK;
    return d_DLE_RX_FAILED;
}
//---------------------------------------------------------------------------
BYTE RS232_DLE_ReadWrite(String sComNo,BYTE *baTxBuf,int iTxLen,BYTE *baRxBuf,int &iRxLen)
{
    BYTE bRtn;

    ResetDLEValue();
	ED_FlushRxRS232(sComNo);
	ED_FlushTxRS232(sComNo);
    memcpy(&baDLE_TxBuf[0],&baTxBuf[0],iTxLen);
    iDLE_TxLen = iTxLen;
    bRtn = RS232_DLE_SEND(sComNo,400);
    if(bRtn!=d_OK)
        return bRtn;
    iRxLen = 0;
    bRtn = RS232_DLE_RECV(sComNo,400);
    if(bRtn!=d_OK)
        return bRtn;
    memcpy(&baRxBuf[0],&baDLE_RxBuf[0],iDLE_RxLen);
    iRxLen = iDLE_RxLen;
    return d_OK;
}
//---------------------------------------------------------------------------

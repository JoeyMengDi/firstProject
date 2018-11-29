//---------------------------------------------------------------------------
#pragma hdrstop
#include <vcl.h>
#include "RS232.h"
#include "public.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

HANDLE hComm232[256];
BYTE bPortOpen[256];
int iRLen,iRecvLen,iSendLen;
BYTE baRBuf[RECVBUF_MAX],baRecvBuf[RECVBUF_MAX],baSendBuf[SENDBUF_MAX];
BYTE bDTR,bRTS,Status;;
ULONG  TimeMS_Start;
USHORT TimeMS_Out;
//---------------------------------------------------------------------------
DWORD SwitchBaudRate(ULONG ulBaudRate)
{
DWORD dwBaudRate;
  switch(ulBaudRate)
  {
        case(256000):
            dwBaudRate = CBR_256000;
            break;
        case(128000):
            dwBaudRate = CBR_128000;
            break;
        case(115200):
            dwBaudRate = CBR_115200;
            break;
        case(57600):
            dwBaudRate = CBR_57600;
            break;
        case(56000):
            dwBaudRate = CBR_56000;
            break;
        case(38400):
            dwBaudRate = CBR_38400;
            break;
        case(19200):
            dwBaudRate = CBR_19200;
            break;
        case(14400):
            dwBaudRate = CBR_14400;
            break;
        case(9600):
            dwBaudRate = CBR_9600;
            break;
        case(4800):
            dwBaudRate = CBR_4800;
            break;
        case(2400):
            dwBaudRate = CBR_2400;
            break;
        case(1200):
            dwBaudRate = CBR_1200;
            break;
        case(600):
            dwBaudRate = CBR_600;
            break;
        case(300):
            dwBaudRate = CBR_300;
            break;
        case(110):
            dwBaudRate = CBR_110;
            break;
        default:
            dwBaudRate = CBR_38400;
            break;
  }
  return dwBaudRate;
}
//---------------------------------------------------------------------------
BYTE SwitchParity(BYTE bParity)
{
BYTE pParity;
  switch(bParity)
  {
        case('N'):
            pParity = NOPARITY;
            break;
        case('O'):
            pParity = ODDPARITY;
            break;
        case('E'):
            pParity = EVENPARITY;
            break;
        case('M'):
            pParity = MARKPARITY;
            break;
        case('S'):
            pParity = SPACEPARITY;
            break;
        default:
            pParity = NOPARITY;
            break;
  }
  return pParity;
}
//---------------------------------------------------------------------------
BYTE SwitchStopBits(BYTE bStopBits)
{
BYTE pStopBits;
  switch(bStopBits)
  {
        case(1):
            pStopBits = ONESTOPBIT;
            break;
        case(15):
            pStopBits = ONE5STOPBITS;
            break;
        case(2):
            pStopBits = TWOSTOPBITS;
            break;
        default:
            pStopBits = ONESTOPBIT;
            break;
  }
  return pStopBits;
}
//---------------------------------------------------------------------------
BYTE SwitchDataBits(BYTE bDataBits)
{
BYTE pDataBits;
  switch(bDataBits)
  {
        case(4):
            pDataBits = 4;
            break;
        case(5):
            pDataBits = 5;
            break;
        case(6):
            pDataBits = 6;
            break;
        case(7):
            pDataBits = 7;
            break;
        case(8):
            pDataBits = 8;
            break;
        default:
            pDataBits = 8;
            break;
  }
  return pDataBits;
}
//---------------------------------------------------------------------------
void Ed_SetTimeOutMS(USHORT usMSec)
{
    TimeMS_Start = ::GetTickCount();
    Application->ProcessMessages();
    TimeMS_Out = usMSec;
}
//---------------------------------------------------------------------------
BYTE Ed_CheckTimeOut()
{
    ULONG TimeMS_Now;

    TimeMS_Now = ::GetTickCount();
    Application->ProcessMessages();
    if((USHORT)(TimeMS_Now-TimeMS_Start)>=(TimeMS_Out*10))
        return d_YES;
    else
        return d_NO;
}
//---------------------------------------------------------------------------
int GetCOMIndex(String sComNo)
{
    int i;
    char *C;
    String COM;
    COM = sComNo.SubString(4,3);
    C = COM.c_str();
    if(COM.Length() == 0)
        return 0;
    for(i=0;i<COM.Length();i++)
    {
        if((C[i]<0x30) || (C[i]>0x39))
            return 0;
    }
    return StrToInt(COM);
}
//---------------------------------------------------------------------------
BYTE Ed_SetDTR(String sComNo,BYTE bStatus)
{
  HANDLE hComm=0;
  int idx;
  
  idx = GetCOMIndex(sComNo);
  hComm = hComm232[idx];
  if (hComm==0)return d_FAILED;
  if (bStatus == d_ON)
    EscapeCommFunction(hComm,SETDTR); //DTR ON
  if (bStatus == d_OFF)
    EscapeCommFunction(hComm,CLRDTR);//DTR OFF
  bDTR = bStatus;
  return d_OK;
}
//---------------------------------------------------------------------------
BYTE Ed_SetRTS(String sComNo,BYTE bStatus)
{
  HANDLE hComm=0;;
  int idx;
  
  idx = GetCOMIndex(sComNo);
  hComm = hComm232[idx];
  if (hComm==0) return d_FAILED;
  if (bStatus == d_ON)
    EscapeCommFunction(hComm,SETRTS); //RTS ON
  if (bStatus == d_OFF)
    EscapeCommFunction(hComm,CLRRTS);//RTS OFF
  bRTS = bStatus;
  return d_OK;
}
//---------------------------------------------------------------------------
BYTE Ed_GetDTR(String sComNo)
{
    return(bDTR);
}
//---------------------------------------------------------------------------
BYTE Ed_GetRTS(String sComNo)
{
    return(bRTS);
}
//---------------------------------------------------------------------------
BYTE Ed_GetCTS(String sComNo)
{
    ULONG ulStatus;
    HANDLE hComm=0;;
    int idx;
  
    idx = GetCOMIndex(sComNo);
    hComm = hComm232[idx];
    if (hComm==0) return d_FAILED;
    if(GetCommModemStatus(hComm,&ulStatus))
    {
        if(ulStatus & MS_CTS_ON)
            return d_ON;
        else
            return d_OFF;
    }
    return d_FAILED;
}
//---------------------------------------------------------------------------
BYTE Ed_GetDSR(String sComNo)
{
    ULONG ulStatus;
    HANDLE hComm=0;;
    int idx;
  
    idx = GetCOMIndex(sComNo);
    hComm = hComm232[idx];
    if (hComm==0) return d_FAILED;
    if(GetCommModemStatus(hComm,&ulStatus))
    {
        if(ulStatus & MS_DSR_ON)
            return d_ON;
        else
            return d_OFF;
    }
    return d_FAILED;
}
//---------------------------------------------------------------------------
BYTE Ed_GetRING(String sComNo)
{
    ULONG ulStatus;
    HANDLE hComm=0;
    int idx;
  
    idx = GetCOMIndex(sComNo);
    hComm = hComm232[idx];
    if (hComm==0) return d_FAILED;
    if(GetCommModemStatus(hComm,&ulStatus))
    {
        if(ulStatus & MS_RING_ON)
            return d_ON;
        else
            return d_OFF;
    }
    return d_FAILED;
}
//---------------------------------------------------------------------------
BYTE Ed_GetCD(String sComNo)
{
    ULONG ulStatus;
    HANDLE hComm=0;;
    int idx;
  
    idx = GetCOMIndex(sComNo);
    hComm = hComm232[idx];
    if (hComm==0) return d_FAILED;
    if(GetCommModemStatus(hComm,&ulStatus))
    {
        if(ulStatus & MS_RLSD_ON)
            return d_ON;
        else
            return d_OFF;
    }
    return d_FAILED;
}
//---------------------------------------------------------------------------
//Initial the RS232 port.
BYTE Ed_InitialRS232(String sComNo,ULONG ulBaudRate,BYTE bParity,BYTE bDataBits,BYTE bStopBits)
{
    DCB dcb;
    HANDLE hComm=0;
    int idx;

    idx = GetCOMIndex(sComNo);
    if (bPortOpen[idx] == 1)
    {
        //ShowMessage(sComNo+" Has Been Opened!");
        return d_FAILED;
    }
    //Temp = "COM"+IntToStr(frmMain->rdCOM->ItemIndex +1);
    hComm = CreateFile(sComNo.c_str(),GENERIC_READ | GENERIC_WRITE,0, NULL, OPEN_EXISTING, 0, 0);
    if (hComm == INVALID_HANDLE_VALUE)
    {
        //ShowMessage(sComNo+" Open Error!!");
        return d_FAILED;
    }
    GetCommState(hComm,&dcb);
    dcb.BaudRate = SwitchBaudRate(ulBaudRate);
    dcb.Parity   = SwitchParity(bParity);
    dcb.ByteSize = SwitchDataBits(bDataBits);//4-8
    dcb.StopBits = SwitchStopBits(bStopBits);
    if (!SetCommState(hComm,&dcb))
    {
        //ShowMessage("Set "+sComNo+" Error!!!");
        CloseHandle(hComm);
        return d_FAILED;
    }
    PurgeComm(hComm,PURGE_TXABORT | PURGE_RXABORT |PURGE_TXCLEAR | PURGE_RXCLEAR ) ;

    bPortOpen[idx] = 1;
    hComm232[idx] = hComm;
    Ed_SetDTR(sComNo,d_ON);
    Ed_SetRTS(sComNo,d_ON);
    return d_OK;
}
//---------------------------------------------------------------------------
//Initial the RS232 port with no-parity, 8-data bits, and 1-stop bits setting.
BYTE Ed_ExInitialRS232(String sComNo,ULONG ulBaudRate)
{
    DCB dcb;
    HANDLE hComm=0;
    int idx;

    idx = GetCOMIndex(sComNo);
    if (bPortOpen[idx] == 1)
    {
        //ShowMessage(sComNo+" Has Been Opened!");
        return d_FAILED;
    }
    //Temp = "COM"+IntToStr(frmMain->rdCOM->ItemIndex +1);
    hComm = CreateFile(sComNo.c_str(),GENERIC_READ | GENERIC_WRITE,0, NULL, OPEN_EXISTING, 0, 0);
    if (hComm == INVALID_HANDLE_VALUE)
    {
        //ShowMessage(sComNo+" Open Error!!");
        return d_FAILED;
    }
    GetCommState(hComm,&dcb);
    dcb.BaudRate = SwitchBaudRate(ulBaudRate);
    dcb.Parity   = SwitchParity('N');
    dcb.ByteSize = 8;
    dcb.StopBits = SwitchStopBits(1);
    if (!SetCommState(hComm,&dcb))
    {
        //ShowMessage("Set "+sComNo+" Error!!!");
        CloseHandle(hComm);
        return d_FAILED;
    }
    PurgeComm(hComm,PURGE_TXABORT | PURGE_RXABORT |PURGE_TXCLEAR | PURGE_RXCLEAR ) ;
    bPortOpen[idx] = 1;
    hComm232[idx] = hComm;
    Ed_SetDTR(sComNo,d_ON);
    Ed_SetRTS(sComNo,d_ON);
    return d_OK;
}
//---------------------------------------------------------------------------
//Close a previous opened RS232 port.
void Ed_CloseRS232(String sComNo)
{
     HANDLE hComm;
     int idx;

     idx = GetCOMIndex(sComNo);
     if(idx == 0)
        return;
     if(bPortOpen[idx]==0)
        return;
     hComm = hComm232[idx];

     if (hComm == 0) return;
     Ed_SetDTR(sComNo,d_OFF);
     Ed_SetRTS(sComNo,d_OFF);
     CloseHandle(hComm);
     hComm232[idx] = 0;
     bPortOpen[idx]=0;
}
//---------------------------------------------------------------------------
SHORT Ed_CheckInQue(String sComNo)
{
   COMSTAT CS;
   DWORD   dwCommError;
   HANDLE hComm=0;;
   int idx;

   idx = GetCOMIndex(sComNo);
   hComm = hComm232[idx];
   if (hComm == 0) return d_NO_DATA;
   ClearCommError(hComm,&dwCommError,&CS);
   if(CS.cbInQue <= 0)
        return d_NO_DATA;
   return (SHORT)CS.cbInQue;
}
//---------------------------------------------------------------------------
SHORT Ed_CheckOutQue(String sComNo)
{
   COMSTAT CS;
   DWORD   dwCommError;
   HANDLE hComm=0;;
   int idx;
  
   idx = GetCOMIndex(sComNo);
   hComm = hComm232[idx];
   if (hComm == 0) return d_NO_DATA;
   ClearCommError(hComm,&dwCommError,&CS);
   if(CS.cbOutQue <= 0)
        return d_NO_DATA;
   return (SHORT)CS.cbOutQue;
}
//---------------------------------------------------------------------------
SHORT Ed_ReadFileProcess(String sComNo,USHORT usReadLen,BYTE *bRxBuf)
{
    DWORD   nBytesRead;
    BYTE bReadBuf[2048];
    HANDLE hComm=0;;
    int idx;

    idx = GetCOMIndex(sComNo);
    hComm = hComm232[idx];
    nBytesRead=0;
    memset(bReadBuf,0x00,2048);
    if(ReadFile(hComm,bReadBuf,usReadLen,&nBytesRead,NULL))
    {
        memcpy(&bRxBuf[0],&bReadBuf[0],nBytesRead);
    }
    return  (SHORT)nBytesRead;
}
SHORT Ed_ModemReadFile(String sComNo,BYTE *bRxBuf)
{
    COMSTAT CS;
    DWORD   nBytesRead;
    DWORD   dwCommError;
    BYTE bReadBuf[20480];
    HANDLE hComm=0;;
    int idx;

    idx = GetCOMIndex(sComNo);
    hComm = hComm232[idx];
    nBytesRead=0;
    memset(bReadBuf,0x00,20480);
    ClearCommError(hComm,&dwCommError,&CS);
    if(ReadFile(hComm,bReadBuf,CS.cbInQue,&nBytesRead,NULL))
    {
        memcpy(&bRxBuf[0],&bReadBuf[0],nBytesRead);
    }
    return  (SHORT)nBytesRead;
}
//---------------------------------------------------------------------------
SHORT Ed_WriteFileProcess(String sComNo,USHORT usWriteLen,BYTE *bWriteBuf)
{
    DWORD   nBytesWrite;
    BYTE bReadBuf[2048];
    HANDLE hComm=0;;
    int idx;

    idx = GetCOMIndex(sComNo);
    hComm = hComm232[idx];
    nBytesWrite=0;
    memset(bReadBuf,0x00,2048);
    if(WriteFile(hComm,bWriteBuf,usWriteLen,&nBytesWrite,NULL))
        return  (SHORT)nBytesWrite;
    return (SHORT)nBytesWrite;
}
SHORT Ed_ModemWriteFile(String sComNo,USHORT usWriteLen,BYTE *bWriteBuf)
{
    DWORD   nBytesWrite;
    BYTE bReadBuf[2048];
    HANDLE hComm=0;;
    int idx;

    idx = GetCOMIndex(sComNo);
    hComm = hComm232[idx];
    nBytesWrite=0;
    memset(bReadBuf,0x00,2048);
    if(WriteFile(hComm,bWriteBuf,usWriteLen,&nBytesWrite,NULL))
        return  (SHORT)nBytesWrite;
    return (SHORT)nBytesWrite;
}
//---------------------------------------------------------------------------
//Check if the data is currently available in RS232 port.
BYTE Ed_CheckRS232(String sComNo)
{
   COMSTAT CS;
   DWORD   dwCommError;

   if(Ed_CheckInQue(sComNo) == d_NO_DATA)
        return d_FAILED;
   else
        return d_OK;
}
//---------------------------------------------------------------------------
//Get one data byte from RS232 port.
SHORT Ed_GetRS232(String sComNo)
{
   BYTE bReadBuf[2];

   memset(bReadBuf,0x00,2);
   if(Ed_CheckInQue(sComNo)!= d_NO_DATA)
   {
        if(Ed_ReadFileProcess(sComNo,1,bReadBuf)!=0)
            return (SHORT)bReadBuf[0];
        return  d_NO_DATA;
   }
   return  d_NO_DATA;
}
//---------------------------------------------------------------------------
//Wait for the current data available in RS232 port within a specific waiting time.
SHORT Ed_GetRS232Waiting(String sComNo,USHORT usWaitMS)
{
    SHORT sC;

    Ed_SetTimeOutMS(usWaitMS);
    while(1)
    {
        sC = Ed_GetRS232(sComNo);
        if(sC!=d_NO_DATA)
            break;
        if(Ed_CheckTimeOut() == d_YES)
            break;
    }
    return sC;
}
//---------------------------------------------------------------------------
//Get a data string from RS232 port.
extern int iSTOP;
SHORT Ed_ReceiveString(String sComNo,BYTE *bRxBuf,BYTE bWaitingMode,USHORT usLenChar,USHORT usMS)
{
    BYTE bReadBuf[2048];
    SHORT sLen,sCh,sChcount;

    memset(bReadBuf,0x00,2048);
    Ed_SetTimeOutMS(usMS);
    if(bWaitingMode == d_WAITING_MODE_LEN)
    {
        while(1)
        {
            sLen = Ed_CheckInQue(sComNo);
            if(sLen!=d_NO_DATA)
            {
                if((USHORT)sLen>= usLenChar)
                {
                    sLen = Ed_ReadFileProcess(sComNo,usLenChar,bReadBuf);
                    memcpy(&bRxBuf[0],&bReadBuf[0],sLen);
                    break;
                }
            }
            if(Ed_CheckTimeOut() == d_YES)
            {
                sLen = Ed_ReadFileProcess(sComNo,sLen,bReadBuf);
                memcpy(&bRxBuf[0],&bReadBuf[0],sLen);
                break;
            }
            if(iSTOP == true)
                break;
        }
        return  sLen;
    }
    if(bWaitingMode == d_WAITING_MODE_CHAR)
    {
        sChcount=0;
        while(1)
        {
            sCh = Ed_GetRS232(sComNo);
            if(sCh!=d_NO_DATA)
            {
                sChcount++;
                if(usLenChar == (USHORT)sCh)
                    break;
            }
            if(Ed_CheckTimeOut() == d_YES)
                break;
            if(iSTOP == true)
                break;
        }
        return sChcount;
    }
    return 0;
}
//---------------------------------------------------------------------------
//Send out one data byte to RS232 port.
BYTE Ed_RS232Put(String sComNo,BYTE bCh)
{
   BYTE PutBuf[2];

   PutBuf[0] = bCh;
   if(Ed_WriteFileProcess(sComNo,1,PutBuf)!=0)
        return d_OK;
   return  d_FAILED;
}
//---------------------------------------------------------------------------
//Send out a data string to RS232 port.
BYTE Ed_SendString(String sComNo,BYTE *bBuf, USHORT usLen, USHORT usMS)
{
    SHORT WritenByte,TotalByte;
    BYTE SendOK = false;

    WritenByte=0;
    TotalByte=0;
    Ed_SetTimeOutMS(usMS);
    while(1)
    {
        WritenByte = Ed_WriteFileProcess(sComNo,usLen,bBuf);
        if(WritenByte == usLen)
        {
            SendOK = true;
            break;
        }
        TotalByte = TotalByte+WritenByte;
        if(TotalByte < usLen)
        {
            usLen = usLen-TotalByte;
            memcpy(&bBuf[0],&bBuf[TotalByte],usLen);
        }
        if(Ed_CheckTimeOut() == d_YES)
            break;
    }
    //frmMain->Edit2->Text = WritenByte;
    if(SendOK == true)
        return d_OK;
    return d_FAILED;
}
//---------------------------------------------------------------------------
//Clear the receive buffer of RS232 port.
BYTE Ed_FlushRxRS232(String sComNo)
{
    HANDLE hComm=0;;
    int idx;

    idx = GetCOMIndex(sComNo);
    hComm = hComm232[idx];
    if(PurgeComm(hComm,PURGE_RXABORT) == 0)
        return d_FAILED;
    if(PurgeComm(hComm,PURGE_RXCLEAR) == 0)
        return d_FAILED;
    return d_OK;
}
//---------------------------------------------------------------------------
//Clear the send buffer of RS232 port.
BYTE Ed_FlushTxRS232(String sComNo)
{
    HANDLE hComm=0;;
    int idx;

    idx = GetCOMIndex(sComNo);
    hComm = hComm232[idx];
    if(PurgeComm(hComm,PURGE_TXABORT) == 0)
        return d_FAILED;
    if(PurgeComm(hComm,PURGE_TXCLEAR) == 0)
        return d_FAILED;
    return d_OK;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//RS232 DLE Protocol Communication
void ResetDLEValue(void)
{
	memset(baRecvBuf,0x00,RECVBUF_MAX);
	memset(baSendBuf,0x00,SENDBUF_MAX);
    memset(bPortOpen,0x00,256);
	iRecvLen = 0;
	iSendLen = 0;
}
//---------------------------------------------------------------------------
BYTE CheckDLEData(void)
{
	BYTE LRC;
	STR buf[20],sBuf[512];
    int i;

	LRC = Cal_LRC(baRecvBuf,iRecvLen-1);	//calculate lrc but lrc itself cannot be calculated included
	if (baRecvBuf[iRecvLen-1]!= LRC)
	{
        //ShowLogMsg("-> LRC Err!",clRed,frmOneCOMMain->RchEdt_Info);
		return d_FAILED;
	}
	baRecvBuf[iRecvLen-1] = '\0';	//drop LRC
	iRecvLen --;
    //ShowLogMsg("-> LRC Check OK.",clBlue,frmOneCOMMain->RchEdt_Info);
    return d_OK;
}
//---------------------------------------------------------------------------
BYTE RS232_DLE_SEND(String sComNo,USHORT usMS)
{
	BYTE LRC;
    BYTE baPackSendBuf[2080];
    int i,iPackLen;
	
	LRC = 0;
	iPackLen = 0;
	memset(baPackSendBuf,0x00,2080);
	baPackSendBuf[iPackLen++] = 0x10;
	baPackSendBuf[iPackLen++] = 0x02;

	for (i=0 ; i<iSendLen ; i++)
		{
			LRC ^= baSendBuf[i];
			if (baSendBuf[i] != 0x10)
				baPackSendBuf[iPackLen++] = baSendBuf[i];
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
	if(Ed_SendString(sComNo,baPackSendBuf,iPackLen,usMS)!=d_OK)
		return d_FAILED;
    return d_OK;
}
//---------------------------------------------------------------------------
BYTE RS232_DLE_RECV(String sComNo,USHORT usLen,USHORT usMS)
{
	int q;
	SHORT Getch;
	BYTE C;
	BYTE isGetSTX, isGetDLE,RecvOK;
	isGetDLE = FALSE;
	isGetSTX = FALSE;
    RecvOK = FALSE;

    memset(baRBuf,0x00,RECVBUF_MAX);
    iRLen = 0;

    /*
    Ed_SetTimeOutMS(usMS);
    while(1)
    {
        if(Ed_CheckRS232(sComNo)!=d_FAILED)
        {
            baRBuf[iRLen] = (BYTE)Ed_GetRS232(sComNo);
            iRLen++;
        }
        if(Ed_CheckTimeOut() == d_YES)
            break;
    }
    */
	iRLen=Ed_ReceiveString(sComNo,baRBuf,d_WAITING_MODE_LEN,usLen,usMS);
	for(q=0 ; q<iRLen ; q++)
		{
			if (iRecvLen >= RECVBUF_MAX)
			{
				iRecvLen = 0;		//Reset
			}
			Getch = (BYTE) baRBuf[q];
			C = (BYTE) Getch;
			if(isGetDLE == FALSE && C == d_DLE)
			{
				isGetDLE = TRUE;
			}
			else if (isGetDLE == TRUE && C == d_STX)
			{
				iRecvLen = 0;
				isGetSTX = TRUE;
				isGetDLE = FALSE;
			}
			else if( isGetSTX == TRUE && isGetDLE == TRUE && C == d_ETX)
			{
				if(CheckDLEData() == d_OK)
				{
					RecvOK = TRUE;
				}
                isGetSTX = isGetDLE = FALSE;
                break;
			}
			else if (isGetSTX == TRUE)
			{
				if (isGetDLE == TRUE && C == d_DLE)
				{
					baRecvBuf[iRecvLen ++] = C;//Add 0x10 to buf
					isGetDLE = FALSE;
				}
				else if (isGetDLE == TRUE)
				{
					//Error block data
					iRecvLen = 0;
					isGetSTX = FALSE;
					isGetDLE = FALSE;
				}
				else
				{
					baRecvBuf[iRecvLen] = C;
					iRecvLen ++;
				}
			}
			else
				isGetDLE = FALSE;
		}
    if(RecvOK == TRUE)
        return d_OK;
    return d_FAILED;
}

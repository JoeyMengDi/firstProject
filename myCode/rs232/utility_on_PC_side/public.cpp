//---------------------------------------------------------------------------
#pragma hdrstop
#include <vcl.h>
#include "Main.h"
//#include "RS232.h"
#include "public.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)

void Delay(DWORD DT)
{
 long tt;
 tt=::GetTickCount();
 while (::GetTickCount()-tt<DT)
 {
  Application->ProcessMessages();
  if ((::GetTickCount()-tt)<=0)
    tt=::GetTickCount();
 }
}
//=========================================================================================
/*
void ShowLogMsg(String Str,TColor Tc ,TRichEdit *TR)//必須至少要有一個 TRichEdit 物件存在
{
    if(Str == "d_CLEAR")
    {
        TR->Clear();
        return;
    }
    TR->SetFocus();
    TR->SelAttributes->Color = Tc;
    TR->Lines->Add(Str);
}
*/
void ShowLogMsg(String Str,TColor Tc ,BYTE bItem)//必須至少要有一個 TRichEdit 物件存在
{
    if(Str == "d_CLEAR")
    {
        switch(bItem)
        {
            case(0x41):
                frmMain->rchedt_TestInfoA->Clear();
                break;
            case(0x42):
                //frmMain->rchedt_TestInfoB->Clear();
                break;
            case(0x43):
                //frmMain->rchedt_TestInfoC->Clear();
                break;
            case(0x44):
                //frmMain->rchedt_TestInfoD->Clear();
                break;
        }
        return;
    }
    switch(bItem)
    {
        case(0x41):
            //frmMain->rchedt_TestInfoA->SetFocus();
            frmMain->rchedt_TestInfoA->SelAttributes->Color = Tc;
            frmMain->rchedt_TestInfoA->Lines->Add(Str);
            break;
        /*case(0x42):
            //frmMain->rchedt_TestInfoA->SetFocus();
            frmMain->rchedt_TestInfoB->SelAttributes->Color = Tc;
            frmMain->rchedt_TestInfoB->Lines->Add(Str);
            break;
        case(0x43):
            //frmMain->rchedt_TestInfoA->SetFocus();
            frmMain->rchedt_TestInfoC->SelAttributes->Color = Tc;
            frmMain->rchedt_TestInfoC->Lines->Add(Str);
            break;
        case(0x44):
            //frmMain->rchedt_TestInfoA->SetFocus();
            frmMain->rchedt_TestInfoD->SelAttributes->Color = Tc;
            frmMain->rchedt_TestInfoD->Lines->Add(Str);
            break;    */
    }
    //TR->SetFocus();
    //TR->SelAttributes->Color = Tc;
    //TR->Lines->Add(Str);
}
//=========================================================================================
void ShowBufToHex(int iLen,BYTE *baBuf ,TMemo *TM)//必須至少要有一個 TMemo 物件存在
{
    int i;
    char caHex[5],caTemp[65535];
    memset(caTemp,0x00,2048);
        for(i=0;i<iLen;i++)
        {
            sprintf(caHex,"%02X ",baBuf[i]);
            strcat(caTemp,caHex);
        }
   TM->Text=TM->Text+caTemp;
   TM->SelStart = TM->Text.Length(); //Set always down
   TM->SelLength = 0;
   //TM->Lines->Add(caTemp);
}
//=========================================================================================
void ShowBufToAsci(int iLen,BYTE *baBuf,TMemo *TM)//必須至少要有一個 TMemo 物件存在
{
    int i;
    char caAsci[5],caTemp[65535];
    memset(caTemp,0x00,2048);
        for(i=0;i<iLen;i++)
        {
            sprintf(caAsci,"%c",baBuf[i]);
            strcat(caTemp,caAsci);
        }
    TM->Lines->Add(caTemp);
}
//=========================================================================================
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
    {
        lrc ^= LrcBuf[i]; 
    }
    return lrc; 
}
//=========================================================================================
BYTE Cal_LRC(BYTE *buf, int len)
{
    int i ;
    BYTE lrc; 
    lrc = 0;

    for (i = 0; i < len; i++) 
    {
        lrc ^= buf[i]; 
    } 
    return lrc; 
}
//=========================================================================================
ULONG Ed_PackAnyTo1(BYTE *BufIN,int AnyLen)
{
    ULONG Out;

	Out = 0;
	switch(AnyLen)
	{
		case 1:
			Out = (ULONG)BufIN[0];
			//OUT = (ULONG)BufIN[0];
			break;
		case 2:
			Out = (ULONG)(BufIN[0]*0x100)+(ULONG)(BufIN[1]);
			//OUT = (ULONG)(BufIN[0]<<8)+(ULONG)(BufIN[1]);
			break;
		case 3:
			Out = (ULONG)(BufIN[0]*0x10000)+(ULONG)(BufIN[1]*0x100)+(ULONG)(BufIN[2]);
			//OUT = (ULONG)(BufIN[0]<<16)+(ULONG)(BufIN[1]<<8)+(ULONG)(BufIN[2]);
			break;
		case 4:
			Out = (ULONG)(BufIN[0]*0x1000000)+(ULONG)(BufIN[1]*0x10000)+(ULONG)(BufIN[2]*0x100)+(ULONG)(BufIN[3]);
			//OUT = (ULONG)(BufIN[0]<<24)+(ULONG)(BufIN[1]<<16)+(ULONG)(BufIN[2]<<8)+(ULONG)(BufIN[3]);
			break;
		default:
			break;
	}
	return Out;
}
//=========================================================================================
int Ed_Pack1ToAny(int ValueIN,int AnyLen,BYTE *OutBuf)
{
	int i;
	i=0;
	memset(OutBuf,0x00,sizeof(OutBuf));
	switch(AnyLen)
	{
		case 1:
			OutBuf[0] = ValueIN%0x100;
		
			//OutBuf[0] = ValueIN&0x00FF;
			i=1;
			break;
		case 2:
			OutBuf[0] = ValueIN/0x100;
			OutBuf[1] = ValueIN%0x100;
			
			//OutBuf[0] = ValueIN>>8;
			//OutBuf[1] = ValueIN&0x00FF;
			i=2;
			break;
		case 3:
			OutBuf[0] = ValueIN/0x10000;
			OutBuf[1] = ValueIN/0x100;
			OutBuf[2] = ValueIN%0x100;
			
			//OutBuf[0] = ValueIN>>16;
			//OutBuf[1] = ValueIN>>8;
			//OutBuf[2] = ValueIN&0x00FF;
			i=3;
			break;
		case 4:
			OutBuf[0] = ValueIN/0x1000000;
			OutBuf[1] = ValueIN/0x10000;
			OutBuf[2] = ValueIN/0x100;
			OutBuf[3] = ValueIN%0x100;
			
			//>>8 = /0x100,>>16 = /0x10000,>>24 = /0x1000000
			//OutBuf[0] = ValueIN>>24;
			//OutBuf[1] = ValueIN>>16;
			//OutBuf[2] = ValueIN>>8;
			//OutBuf[3] = ValueIN&0x00FF;
			i=4;
			break;
		default:
			break;
	}
	return i;
}
//=========================================================================================
void GetFixedData(BYTE *bSrcBuf,USHORT uSrcLen,USHORT uStartAddr,USHORT uFixedLen,BYTE *bDestBuf)
{
	USHORT i;
	BYTE bTemp[512];

	memset(bDestBuf,0x00,sizeof(bDestBuf));
	memset(bTemp,0x00,sizeof(bTemp));
	if((uSrcLen<=0) && (uFixedLen>0))
	{
		uFixedLen = 0;
		return;
	}
	
	if((uStartAddr+uFixedLen) > uSrcLen)
		uFixedLen = uSrcLen-uStartAddr;
	
	for(i=uStartAddr ; i<(uStartAddr+uFixedLen) ; i++)
		{
			bTemp[i-uStartAddr] = bSrcBuf[i];
		}
		memcpy(bDestBuf,bTemp,uFixedLen);
}
//=========================================================================================
ULONG	ToUnixTime(int iYear, int iMonth, int iDate, int iHour, int iMin, int iSec)
{
		int		iDaysofMonth[] = {  0,  31,  59,  90, 120, 151, 181, 212, 243, 273, 304, 334};		
		int		iTemp;
		ULONG	lSec;
		
		iTemp = iYear - 1970;
		if (iYear % 4 == 0)
			iDaysofMonth[iMonth-1]++;
		lSec = (iTemp+2)/4+iTemp*365 + iDaysofMonth[iMonth-1] + iDate-1;
		lSec = lSec * 24 + iHour;   //-8;
		lSec = lSec * 60 + iMin;
		lSec = lSec * 60 + iSec;
		return lSec;
}
//=========================================================================================
void GetUnixTime (BYTE *baTime)
{
	//CIT_RTC stRTC;
	ULONG	ulUT;
	
	//CIT_GetRealTimeClock(&stRTC);
	//ulUT = ToUnixTime(stRTC.bYear+2000, stRTC.bMonth, stRTC.bDay, stRTC.bHour, stRTC.bMinute, stRTC.bSecond);
	Ed_Pack1ToAny(ulUT,4,baTime);
}
//=========================================================================================
ULONG PowSixteen(USHORT usP)
{
	ULONG pow;
	USHORT usT;
	pow = 1;
	for(usT=0 ; usT<usP ; usT++)
			pow*=16;
	return pow;
}
//=========================================================================================

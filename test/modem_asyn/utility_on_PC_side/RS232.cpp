//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "RS232.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
HANDLE hComm232[256];

BYTE bDTR,bRTS;
ULONG  TimeMS_Start;
USHORT TimeMS_Out;
int iInitial = false;
int iSTOP;

//***************add 0427
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
//***************add 0427
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
void ED_SetTimeOutMS(USHORT usMSec)
{
    TimeMS_Start = ::GetTickCount();
    Application->ProcessMessages();
    TimeMS_Out = usMSec;
}
//---------------------------------------------------------------------------
BYTE ED_CheckTimeOut(void)
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
int ED_GetCOMIndex(String sComNo)
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
BYTE ED_SetDTR(String sComNo,BYTE bStatus)
{
    HANDLE hComm=0;
    int idx;

    idx = ED_GetCOMIndex(sComNo);
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
BYTE ED_SetRTS(String sComNo,BYTE bStatus)
{
    HANDLE hComm=0;
    int idx;

    idx = ED_GetCOMIndex(sComNo);
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
BYTE ED_GetDTR(String sComNo)
{
    return(bDTR);
}
//---------------------------------------------------------------------------
BYTE ED_GetRTS(String sComNo)
{
    return(bRTS);
}
//---------------------------------------------------------------------------
BYTE ED_GetCTS(String sComNo)
{
    ULONG ulStatus;
    HANDLE hComm=0;
    int idx;
  
    idx = ED_GetCOMIndex(sComNo);
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
BYTE ED_GetDSR(String sComNo)
{
    ULONG ulStatus;
    HANDLE hComm=0;;
    int idx;
  
    idx = ED_GetCOMIndex(sComNo);
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
BYTE ED_GetRING(String sComNo)
{
    ULONG ulStatus;
    HANDLE hComm=0;
    int idx;
  
    idx = ED_GetCOMIndex(sComNo);
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
BYTE ED_GetCD(String sComNo)
{
    ULONG ulStatus;
    HANDLE hComm=0;;
    int idx;
  
    idx = ED_GetCOMIndex(sComNo);
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
BYTE ED_InitialRS232(String sComNo,ULONG ulBaudRate,BYTE bParity,BYTE bDataBits,BYTE bStopBits)
{
    DCB dcb;
    HANDLE hComm=0;
    int idx;

    if(!iInitial)
    {
        memset(hComm232,0x00,256);
        iInitial = true;
    }
    idx = ED_GetCOMIndex(sComNo);
    if(hComm232[idx]!=0)
    {
        //ShowMessage(sComNo+" Has Been Opened!");
        return d_FAILED;
    }
    hComm = CreateFile(sComNo.c_str(),GENERIC_READ | GENERIC_WRITE,0, NULL,OPEN_EXISTING , 0, 0);
    if (hComm == INVALID_HANDLE_VALUE)
    {
        //ShowMessage(SysErrorMessage(GetLastError()));
        //ShowMessage(sComNo+" Open Error!!");
        return d_FAILED;
    }
    GetCommState(hComm,&dcb);
    dcb.BaudRate = SwitchBaudRate(ulBaudRate);
    dcb.Parity   = SwitchParity(bParity);
    dcb.ByteSize = bDataBits;//4-8
    dcb.StopBits = SwitchStopBits(bStopBits);
    if (!SetCommState(hComm,&dcb))
    {
        //ShowMessage("Set "+sComNo+" Error!!!");
        CloseHandle(hComm);
        return d_FAILED;
    }
    PurgeComm(hComm,PURGE_TXABORT | PURGE_RXABORT |PURGE_TXCLEAR | PURGE_RXCLEAR ) ;

    hComm232[idx] = hComm;
    ED_SetDTR(sComNo,d_ON);
    ED_SetRTS(sComNo,d_ON);
    return d_OK;
}
//---------------------------------------------------------------------------
//Initial the RS232 port with no-parity, 8-data bits, and 1-stop bits setting.
BYTE ED_ExInitialRS232(String sComNo,ULONG ulBaudRate)
{
    DCB dcb;
    HANDLE hComm=0;
    int idx;

    if(!iInitial)
    {
        memset(hComm232,0x00,256);
        iInitial = true;
    }
    idx = ED_GetCOMIndex(sComNo);
    if(hComm232[idx]!=0)
    {
        //ShowMessage(sComNo+" Has Been Opened!");
        return d_FAILED;
    }
    hComm = CreateFile(sComNo.c_str(),GENERIC_READ | GENERIC_WRITE,0, NULL, OPEN_EXISTING, 0, 0);
    if (hComm == INVALID_HANDLE_VALUE)
    {
        //ShowMessage(SysErrorMessage(GetLastError()));
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

    hComm232[idx] = hComm;
    ED_SetDTR(sComNo,d_ON);
    ED_SetRTS(sComNo,d_ON);
    return d_OK;
}
//---------------------------------------------------------------------------
//Close a previous opened RS232 port.
void ED_CloseRS232(String sComNo)
{
     HANDLE hComm;
     int idx;

     idx = ED_GetCOMIndex(sComNo);
     if(idx == 0)
        return;
     hComm = hComm232[idx];

     if (hComm == 0) return;
     ED_SetDTR(sComNo,d_OFF);
     ED_SetRTS(sComNo,d_OFF);
     CloseHandle(hComm);
     hComm232[idx] = 0;
}
//---------------------------------------------------------------------------
SHORT ED_CheckInQue(String sComNo)
{
   COMSTAT CS;
   DWORD   dwCommError;
   HANDLE hComm=0;;
   int idx;

   idx = ED_GetCOMIndex(sComNo);
   hComm = hComm232[idx];
   if (hComm == 0) return d_NO_DATA;
   ClearCommError(hComm,&dwCommError,&CS);
   if(CS.cbInQue <= 0)
        return d_NO_DATA;
   return (SHORT)CS.cbInQue;
}
//---------------------------------------------------------------------------
SHORT ED_CheckOutQue(String sComNo)
{
   COMSTAT CS;
   DWORD   dwCommError;
   HANDLE hComm=0;;
   int idx;
  
   idx = ED_GetCOMIndex(sComNo);
   hComm = hComm232[idx];
   if (hComm == 0) return d_NO_DATA;
   ClearCommError(hComm,&dwCommError,&CS);
   if(CS.cbOutQue <= 0)
        return d_NO_DATA;
   return (SHORT)CS.cbOutQue;
}
//---------------------------------------------------------------------------
//Read RS232 Data With Prefer Len
SHORT ED_ReadFileProcess(String sComNo,USHORT usReadLen,BYTE *bRxBuf)
{
    DWORD   nBytesRead;
    BYTE bReadBuf[2048];
    HANDLE hComm=0;;
    int idx;

    idx = ED_GetCOMIndex(sComNo);
    hComm = hComm232[idx];
    nBytesRead=0;
    memset(bReadBuf,0x00,2048);
    if(ReadFile(hComm,bReadBuf,usReadLen,&nBytesRead,NULL))
    {
        memcpy(&bRxBuf[0],&bReadBuf[0],nBytesRead);
    }
    return  (SHORT)nBytesRead;
}
//---------------------------------------------------------------------------
//Read All RS232 Data In The Queue
SHORT ED_RS232ReadFile(String sComNo,BYTE *bRxBuf)
{
    COMSTAT CS;
    DWORD   nBytesRead;
    DWORD   dwCommError;
    BYTE bReadBuf[20480];
    HANDLE hComm=0;;
    int idx;

    idx = ED_GetCOMIndex(sComNo);
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
//Write RS232 Data With Prefer Len
SHORT ED_WriteFileProcess(String sComNo,USHORT usWriteLen,BYTE *bWriteBuf)
{
    DWORD   nBytesWrite;
    BYTE bReadBuf[2048];
    HANDLE hComm=0;;
    int idx;

    idx = ED_GetCOMIndex(sComNo);
    hComm = hComm232[idx];
    nBytesWrite=0;
    memset(bReadBuf,0x00,2048);
    if(WriteFile(hComm,bWriteBuf,usWriteLen,&nBytesWrite,NULL))
        return  (SHORT)nBytesWrite;
    return (SHORT)nBytesWrite;
}
//---------------------------------------------------------------------------
//Write All RS232 Data Into The Queue
SHORT ED_RS232WriteFile(String sComNo,USHORT usWriteLen,BYTE *bWriteBuf)
{
    DWORD   nBytesWrite;
    BYTE bReadBuf[2048];
    HANDLE hComm=0;;
    int idx;

    idx = ED_GetCOMIndex(sComNo);
    hComm = hComm232[idx];
    nBytesWrite=0;
    memset(bReadBuf,0x00,2048);
    if(WriteFile(hComm,bWriteBuf,usWriteLen,&nBytesWrite,NULL))
        return  (SHORT)nBytesWrite;
    return (SHORT)nBytesWrite;
}
//---------------------------------------------------------------------------
//Check if the data is currently available in RS232 port.
BYTE ED_CheckRS232(String sComNo)
{
   COMSTAT CS;
   DWORD   dwCommError;

   if(ED_CheckInQue(sComNo) == d_NO_DATA)
        return d_FAILED;
   else
        return d_OK;
}
//---------------------------------------------------------------------------
//Get one data byte from RS232 port.
SHORT ED_GetRS232(String sComNo)
{
   BYTE bReadBuf[2];

   memset(bReadBuf,0x00,2);
   if(ED_CheckInQue(sComNo)!= d_NO_DATA)
   {
        if(ED_ReadFileProcess(sComNo,1,bReadBuf)!=0)
            return (SHORT)bReadBuf[0];
        return  d_NO_DATA;
   }
   return  d_NO_DATA;
}
//---------------------------------------------------------------------------
//Wait for the current data available in RS232 port within a specific waiting time.
SHORT ED_GetRS232Waiting(String sComNo,USHORT usWaitMS)
{
    SHORT sC;

    ED_SetTimeOutMS(usWaitMS);
    while(1)
    {
        sC = ED_GetRS232(sComNo);
        if(sC!=d_NO_DATA)
            break;
        if(ED_CheckTimeOut() == d_YES)
            break;
    }
    return sC;
}
//---------------------------------------------------------------------------
//Get a data string from RS232 port.
SHORT ED_ReceiveString(String sComNo,BYTE *bRxBuf,BYTE bWaitingMode,USHORT usLenChar,USHORT usMS)
{
    BYTE bReadBuf[2048];
    SHORT sLen,sCh,sChcount;

    memset(bReadBuf,0x00,2048);
    ED_SetTimeOutMS(usMS);
    if(bWaitingMode == d_WAITING_MODE_LEN)
    {
        while(1)
        {
            sLen = ED_CheckInQue(sComNo);
            if(sLen!=d_NO_DATA)
            {
                if((USHORT)sLen>= usLenChar)
                {
                    sLen = ED_ReadFileProcess(sComNo,usLenChar,bReadBuf);
                    memcpy(&bRxBuf[0],&bReadBuf[0],sLen);
                    break;
                }
            }
            if(ED_CheckTimeOut() == d_YES)
            {
                sLen = ED_ReadFileProcess(sComNo,sLen,bReadBuf);
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
            sCh = ED_GetRS232(sComNo);
            if(sCh!=d_NO_DATA)
            {
                sChcount++;
                if(usLenChar == (USHORT)sCh)
                    break;
            }
            if(ED_CheckTimeOut() == d_YES)
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
BYTE ED_RS232Put(String sComNo,BYTE bCh)
{
   BYTE PutBuf[2];

   PutBuf[0] = bCh;
   if(ED_WriteFileProcess(sComNo,1,PutBuf)!=0)
        return d_OK;
   return  d_FAILED;
}
//---------------------------------------------------------------------------
//Send out a data string to RS232 port.
BYTE ED_SendString(String sComNo,BYTE *bBuf, USHORT usLen, USHORT usMS)
{
    SHORT WritenByte,TotalByte;
    BYTE SendOK = false;

    WritenByte=0;
    TotalByte=0;
    ED_SetTimeOutMS(usMS);
    while(1)
    {
        WritenByte = ED_WriteFileProcess(sComNo,usLen,bBuf);
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
        if(ED_CheckTimeOut() == d_YES)
            break;
        if(iSTOP == true)
            break;
    }
    //frmMain->Edit2->Text = WritenByte;
    if(SendOK == true)
        return d_OK;
    return d_FAILED;
}
//---------------------------------------------------------------------------
//Clear the receive buffer of RS232 port.
BYTE ED_FlushRxRS232(String sComNo)
{
    HANDLE hComm=0;;
    int idx;

    idx = ED_GetCOMIndex(sComNo);
    hComm = hComm232[idx];
    if(PurgeComm(hComm,PURGE_RXABORT) == 0)
        return d_FAILED;
    if(PurgeComm(hComm,PURGE_RXCLEAR) == 0)
        return d_FAILED;
    return d_OK;
}
//---------------------------------------------------------------------------
//Clear the send buffer of RS232 port.
BYTE ED_FlushTxRS232(String sComNo)
{
    HANDLE hComm=0;;
    int idx;

    idx = ED_GetCOMIndex(sComNo);
    hComm = hComm232[idx];
    if(PurgeComm(hComm,PURGE_TXABORT) == 0)
        return d_FAILED;
    if(PurgeComm(hComm,PURGE_TXCLEAR) == 0)
        return d_FAILED;
    return d_OK;
}
//---------------------------------------------------------------------------
void ED_ListComPort(char *caCOMLst)
{
   TStrings *Coms = new TStringList();
   HANDLE hCom;
   char chPort[5];
   memset( chPort, '\0', sizeof( chPort ) );
   for (int i=1; i<256; i++ )
   {
       sprintf( chPort , "COM%d" , i );
       hCom = CreateFile( chPort , GENERIC_READ | GENERIC_WRITE , 0 , NULL ,OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL , 0 );
       if ( hCom != INVALID_HANDLE_VALUE )
           Coms->Add( AnsiString(chPort) );
       CloseHandle(hCom);
   }
       memset(caCOMLst,0x00,sizeof(caCOMLst));
       strcat(caCOMLst,Coms->Text.c_str());
       delete Coms;
}
//---------------------------------------------------------------------------

//***********************add 0427
BYTE Ed_InitialRS232(String sComNo,ULONG ulBaudRate,BYTE bParity,BYTE bDataBits,BYTE bStopBits)
{
    DCB dcb;
    HANDLE hComm=0;
    int idx;

    idx = ED_GetCOMIndex(sComNo);
    if(hComm232[idx]!=0)
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

    //bPortOpen[idx] = 1;
    hComm232[idx] = hComm;
    ED_SetDTR(sComNo,d_ON);
    ED_SetRTS(sComNo,d_ON);
    return d_OK;
}
//****************0427

//---------------------------------------------------------------------------

#ifndef RS232H
#define RS232H

// for all module
#define d_FAILED                   	0
#define d_OK                    	1
#define	d_ERROR                     2
#define d_NO                       	0
#define d_YES                    	1
#define d_OFF                    	0
#define d_ON                   	    1
#define d_NO_DATA                   0
#define d_WAITING_MODE_LEN      	0x80
#define d_WAITING_MODE_CHAR     	0x81

BYTE ED_InitialRS232(String sComNo,ULONG ulBaudRate,BYTE bParity,BYTE bDataBits,BYTE bStopBits);
BYTE ED_ExInitialRS232(String sComNo,ULONG ulBaudRate);
void ED_CloseRS232(String sComNo);
void ED_SetTimeOutMS(USHORT usMSec);
BYTE ED_CheckTimeOut(void);
int ED_GetCOMIndex(String sComNo);
BYTE ED_SetDTR(String sComNo,BYTE bStatus);
BYTE ED_SetRTS(String sComNo,BYTE bStatus);
BYTE ED_GetDTR(String sComNo);
BYTE ED_GetRTS(String sComNo);
BYTE ED_GetCTS(String sComNo);
BYTE ED_GetDSR(String sComNo);
BYTE ED_GetRING(String sComNo);
BYTE ED_GetCD(String sComNo);
BYTE ED_CheckRS232(String sComNo);
SHORT ED_GetRS232(String sComNo);
SHORT ED_GetRS232Waiting(String sComNo,USHORT usWaitMS);
SHORT ED_ReceiveString(String sComNo,BYTE *bRxBuf,BYTE bWaitingMode,USHORT usLenChar,USHORT usMS);
BYTE ED_RS232Put(String sComNo,BYTE bCh);
BYTE ED_SendString(String sComNo,BYTE *bBuf, USHORT usLen, USHORT usMS);
BYTE ED_FlushRxRS232(String sComNo);
BYTE ED_FlushTxRS232(String sComNo);
SHORT ED_RS232ReadFile(String sComNo,BYTE *bRxBuf);
SHORT ED_RS232WriteFile(String sComNo,USHORT usWriteLen,BYTE *bWriteBuf);
SHORT ED_ReadFileProcess(String sComNo,USHORT usReadLen,BYTE *bRxBuf);
void ED_ListComPort(char *caCOMLst);

BYTE Ed_InitialRS232(String sComNo,ULONG ulBaudRate,BYTE bParity,BYTE bDataBits,BYTE bStopBits);
//---------------------------------------------------------------------------
#endif
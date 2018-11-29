//---------------------------------------------------------------------------

#ifndef RS232H
#define RS232H

typedef char STR;

//Const Protocol
#define d_DLE	0x10
#define d_STX	0x02
#define d_ETX	0x03

#define d_ACK	0x06
#define d_NAK	0x15
	
//for Buffer Max Len
#define SENDBUF_MAX	2048
#define RECVBUF_MAX	2048

//Status
#define d_STATUS_APPROVE	0x00
#define d_STATUS_ERROR		0xF0

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

BYTE Ed_InitialRS232(String sComNo,ULONG ulBaudRate,BYTE bParity,BYTE bDataBits,BYTE bStopBits);
BYTE Ed_ExInitialRS232(String sComNo,ULONG ulBaudRate);
void Ed_CloseRS232(String sComNo);
void Ed_SetTimeOutMS(USHORT usMSec);
BYTE Ed_CheckTimeOut();
int GetCOMIndex(String sComNo);
BYTE Ed_SetDTR(String sComNo,BYTE bStatus);
BYTE Ed_SetRTS(String sComNo,BYTE bStatus);
BYTE Ed_GetDTR(String sComNo);
BYTE Ed_GetRTS(String sComNo);
BYTE Ed_GetCTS(String sComNo);
BYTE Ed_GetDSR(String sComNo);
BYTE Ed_GetRING(String sComNo);
BYTE Ed_GetCD(String sComNo);
BYTE Ed_CheckRS232(String sComNo);
SHORT Ed_GetRS232(String sComNo);
SHORT Ed_GetRS232Waiting(String sComNo,USHORT usWaitMS);
SHORT Ed_ReceiveString(String sComNo,BYTE *bRxBuf,BYTE bWaitingMode,USHORT usLenChar,USHORT usMS);
BYTE Ed_RS232Put(String sComNo,BYTE bCh);
BYTE Ed_SendString(String sComNo,BYTE *bBuf, USHORT usLen, USHORT usMS);
BYTE Ed_FlushRxRS232(String sComNo);
BYTE Ed_FlushTxRS232(String sComNo);
void ResetDLEValue(void);
BYTE CheckDLEData(void);
BYTE RS232_DLE_SEND(String sComNo,USHORT usMS);
BYTE RS232_DLE_RECV(String sComNo,USHORT usLen,USHORT usMS);
SHORT Ed_ModemReadFile(String sComNo,BYTE *bRxBuf);
SHORT Ed_ModemWriteFile(String sComNo,USHORT usWriteLen,BYTE *bWriteBuf);
SHORT Ed_ReadFileProcess(String sComNo,USHORT usReadLen,BYTE *bRxBuf);
//---------------------------------------------------------------------------
#endif

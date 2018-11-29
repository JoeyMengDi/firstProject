//---------------------------------------------------------------------------

#ifndef DLEH
#define DLEH

//Const Protocol
#define d_DLE	0x10
#define d_STX	0x02
#define d_ETX	0x03

#define d_ACK	0x06
#define d_NAK	0x15
	
//for Buffer Max Size
#define d_DLE_BUF_MAX	        4096
//for DLE Tx Rx
#define d_DLE_TX_BUF_OVERFLOW   0x70
#define d_DLE_RX_BUF_OVERFLOW	0x71
#define d_DLE_RX_TIMEOUT        0x72
#define d_DLE_RX_LRC_ERR        0x73
#define d_DLE_COM_PORT_ERR      0x74
#define d_DLE_COM_NOT_INITIAL   0x75
#define d_DLE_RX_FAILED         0x76
#define d_DLE_TX_FAILED         0x77

//---------------------------------------------------------------------------
void ResetDLEValue(void);
BYTE Cal_LRC(BYTE *babuf, int ilen);
BYTE RS232_DLE_SEND(String sComNo,USHORT usMS);
BYTE RS232_DLE_RECV(String sComNo,USHORT usWaitMS);
BYTE RS232_DLE_ReadWrite(String sComNo,BYTE *baTxBuf,int iTxLen,BYTE *baRxBuf,int &iRxLen);
#endif
 
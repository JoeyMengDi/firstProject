/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPCommon.h
 * Author: Louis Lu
 *
 * Created on 2017年6月20日, 下午2:30
 */

#ifndef H_CPCOMMON
#define H_CPCOMMON

// #include <sys/timeb.h>
#include <time.h>
#include "../SRC/StdafxHead.h"


#define _IN_
#define _OUT_
#define _IN_OUT_

// Communication Types
#define COMM_TYPE_BT            0x8000
#define COMM_TYPE_ETH           0x4000
#define COMM_TYPE_WIFI          0x2000
#define COMM_TYPE_RS232         0x1000
#define COMM_TYPE_GPRS          0x0800
#define COMM_TYPE_USB           0x0400
#define COMM_TYPE_MODEM         0x0200
#define COMM_TYPE_GSM           0x0100

#define DATA_LENGTH_LEN             2
#define MSG_HEADER_LEN              5
#define RECV_DATA_LONG_TIMEOUT      200     // timeout for receving data with other communication types
#define RECV_DATA_SHORT_TIMEOUT     50      // timeout for receving data with USB, RS232, BT 
#define RECV_DATA_BUF_LEN           2048
#define MSG_INFO_MAX_LEN            2000
#define RECV_DATA_TIMEOUT     20
#define NO_DESIRED_MSG_TYPE        0xF00C
#define RECD_STOP_CMD                    0xE00D


// Control Symbols
#define CONTROL_SYMBOL_STX          0x02
#define CONTROL_SYMBOL_ETX          0x03
#define CONTROL_SYMBOL_ACK          0x06
#define CONTROL_SYMBOL_NAK          0x15
#define CONTROL_SYMBOL_EOT          0x04

#define ACK                         "\x06"
#define NAK                         "\x15"
#define EOT                         "\x04"

// For CProfile class

#define DEF_CONFIG_FILE_PATH        "CastlesPay.xml"
#define DEF_CONFIG_XML_ROOT_NODE    "Config"
#define DEF_CONFIG_XML_COMM_NODE    "COMM_Config"
#define UI_MODE_TEXT                0x01
#define UI_MODE_GRAPHIC             0x02

#define CHECK_POINT(p)	if(NULL == (void*)p) \
                    return DEBUG_RETCODE("Invalid Pointer" ,0xF001);//ERROR_INVALID_PARAM

/////////////////////////////////////////////////////////////////////////////////


// communication type enum
typedef enum enum_COMMTYPE
{
    COMM_BT = 1,
    COMM_ETH,
    COMM_WIFI,
    COMM_RS232,
    COMM_GPRS,
    COMM_USB,
    COMM_MODEM,
    COMM_GSM
} COMMTYPE;


// CMD message type structure used for the message queue.
typedef struct stCMD_MsgType
{

    stCMD_MsgType()
    {
        lMsgType = 0;
        memset(byCmdPacket, 0, sizeof (byCmdPacket));
        nDataLen = 0;
    }

    long lMsgType;
    int nDataLen;
    BYTE byCmdPacket[RECV_DATA_BUF_LEN];

} CMDMSGTYPE, *PCMDMSGTYPE;


// Status message type structure used for message queue
typedef struct stSTATE_MsgType
{
    stSTATE_MsgType()
    {
        lMsgType = 0;
        wStatus = 0;
//        memset(byStatusBuf, 0x00, sizeof(byStatusBuf));
    }
    
    long lMsgType;
    WORD wStatus;
//    BYTE byStatusBuf[RECV_DATA_BUF_LEN];
    
}STAMSGTYPE, *PSTAMSGTYPE;



inline ULONG GetSysTime()
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}



#endif /* H_CPCOMMON */


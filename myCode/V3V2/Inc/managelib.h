/* 
 * File:   managelib.h
 * Author: Vincent Xue
 *
 * Created Date: 2017.8.30
 * 
 * History:
 *         #2018.05.02, Alan.Ren
 *         1. Modify.
 * 
 *         #2018.05.28, Alan.Ren
 *         1. Add CTAP_StopManage() function.
 * 
 *         #2018.06.07, Alan.Ren
 *         1. Add module definition.
 */

#ifndef __CASTLESPAY_MANAGELIB_H__
#define __CASTLESPAY_MANAGELIB_H__

#include "UserModuleDef.h"

#ifndef WORD
#define WORD unsigned short
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif 

#ifndef BOOL
#define BOOL unsigned char
#endif 

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif
    
#ifndef INOUT
#define INOUT
#endif

typedef enum enum_MODULE
{
    MODULE_COMM  = 0x0001,
    MODULE_CLOUD = 0X0002,
    MODULE_RFU2  = 0X0004,
    MODULE_RFU3  = 0X0008,
    MODULE_RFU4  = 0X0010,
    MODULE_RFU5  = 0x0020,
    MODULE_RFU6  = 0x0040,
    MODULE_RFU7  = 0x0080
} MODULETYPE;

#define COMM_MODULE_VERSION         0x03EA          // version: v1001
#define COMM_MAXBUF_SIZE            0x1000

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * enum_CHANNELTYPE
 * 
 * @note:
 *      Enum for Channel ID
 *      When COMM_RegProtocol is called , the eChannelID must be an element of CHANNEL_TYPE
 *
 * modified: Tim.Ma, 05/04/2018
**/
typedef enum enum_CHANNELID
{
    /*********COMM_BEGIN******************/
    CHANNEL_COM1    = 101,  //RS232Config01
    CHANNEL_COM2,           //RS232Config02
    CHANNEL_COM3,           //RS232Config03

    /*********ETH_BEGIN*******************/
    CHANNEL_ETH1    = 201,  //EthConfig01
    CHANNEL_ETH2,           //EthConfig02
    CHANNEL_ETH3,           //EthConfig03
    CHANNEL_ETH4,           //EthConfig04
    CHANNEL_ETH5,           //EthConfig05
    CHANNEL_ETH6,           //EthConfig06
    CHANNEL_ETH7,           //EthConfig07
    CHANNEL_ETH8,           //EthConfig08
    CHANNEL_ETH9,           //EthConfig09
    CHANNEL_ETH10,          //EthConfig10
    CHANNEL_ETH11,          //EthConfig11
    CHANNEL_ETH12,          //EthConfig12

    /*********WiFi_BEGIN******************/
    CHANNEL_WIFI1   = 301,  //WifiConfig01
    CHANNEL_WIFI2,          //WifiConfig02
    CHANNEL_WIFI3,          //WifiConfig03
    CHANNEL_WIFI4,          //WifiConfig04
    CHANNEL_WIFI5,          //WifiConfig05
    CHANNEL_WIFI6,          //WifiConfig06
    CHANNEL_WIFI7,          //WifiConfig07
    CHANNEL_WIFI8,          //WifiConfig08
    CHANNEL_WIFI9,          //WifiConfig09
    CHANNEL_WIFI10,         //WifiConfig10
    CHANNEL_WIFI11,         //WifiConfig11
    CHANNEL_WIFI12,         //WifiConfig12

    /*********GPRS_BEGIN******************/
    CHANNEL_GPRS1   = 401,  //GPRSConfig01
    CHANNEL_GPRS2,          //GPRSConfig02
    CHANNEL_GPRS3,          //GPRSConfig03
    CHANNEL_GPRS4,          //GPRSConfig04
    CHANNEL_GPRS5,          //GPRSConfig05
    CHANNEL_GPRS6,          //GPRSConfig06
    CHANNEL_GPRS7,          //GPRSConfig07
    CHANNEL_GPRS8,          //GPRSConfig08
    CHANNEL_GPRS9,          //GPRSConfig09
    CHANNEL_GPRS10,         //GPRSConfig10
    CHANNEL_GPRS11,         //GPRSConfig11
    CHANNEL_GPRS12,         //GPRSConfig12

    /*********INVALID_CHANNEL*************/
    CHANNEL_ERR     = 0
}CHANNEL_ID;    


/** 
 * TRANSFER_PROTOCOL_PARAM
 * 
 * @param
 *          [IN]    : wCommVersion  - The version of COMM module, must be COMM_MODULE_VERSION
 * 
 *          [IN]    : szDataBuff    - Data received from the server
 *          [IN]    : wDataLength   - Data length that received from the server
 * 
 *          [OUT]   : szDataBuff    - Data that needs to be sent to the server
 *          [OUT]   : wDataLength   - Data length that needs to be sent to the server
 * 
 *          [OUT]   : wNeedRecvSize - The length of data need to received before recv,
 *                                    if 0xFFFF is specify
 **/ 
typedef struct
{
    IN WORD                         wCommVersion;
    INOUT BYTE                      szDataBuff[COMM_MAXBUF_SIZE];
    INOUT WORD                      wDataLength;
    OUT WORD                        wNeedRecvSize;
}TRANSFER_PROTOCOL_PARAM;


/**
 * COMM_PROTOCOL
 * 
 * Function:
 *          callback function to parse kinds of protocol data
 * 
 * @param
 *          [INOUT]: pProtocolParam - refer to TRANSFER_PROTOCOL_PARAM
 * 
 * @return 
 *          0       : OK
 *          other   : error code
 *
 * modified: Tim.Ma, 05/28/2018
 */    
typedef int (*COMM_PROTOCOL)(TRANSFER_PROTOCOL_PARAM *pProtocolParam);

WORD CTAP_RegCommProtocol(IN CHANNEL_ID eChannelID, IN COMM_PROTOCOL pProtocolFunc);

WORD CTAP_InitManage(IN WORD wPara);

WORD CTAP_StopManage(void);

WORD CTAP_RegisterUserModule(IN PUSER_MODULEENTRY pstModuleEntry);

#ifdef	__cplusplus
}
#endif

#endif	/* __CASTLESPAY_MANAGELIB_H__ */


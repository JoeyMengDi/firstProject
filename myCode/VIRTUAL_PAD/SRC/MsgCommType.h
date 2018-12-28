/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MsgCommType.h
 * Author: Administrator
 *
 * Created on 2017年12月28日, 上午9:24
 */

#ifndef MSGCOMMTYPE_H
#define MSGCOMMTYPE_H

#include "../SRC/ErrorCode.h"

#define _IN_
#define _OUT_
#define _IN_OUT_

/* Common */
#define BUFFER_SIZE_256         256
#define BUFFER_SIZE_512         512
#define BUFFER_SIZE_1024        1024
#define BUFFER_SIZE_4           4
#define BUFFER_SIZE_8           8
#define BUFFER_SIZE_32          32

#define NICKEL_STAN_LEN         6
#define NICKEL_AMOUNT_MAX_LEN   12

//XML config Node and Name
#define NICKEL_CFG_XML_NAME         "NickelCFG.xml"
#define NICKEL_CFG_XML_ROOT         "Config"
#define NICKEL_CFG_LOCAL_NODE       "Local_Config"
#define NICKEL_CFG_LOCAL_STAN_NODE  "STAN"
#define STAN_VALUE                  "Value"

#define NICKEL_CFG_GETCFG           "Get_Config"
#define NICKEL_CFG_TXN              "TXN"
#define NICKEL_CFG_CN08             "CN08"

//IP Config Node
#define NICKEL_CFG_IP_NODE          "IP_Config"
#define NICKEL_CFG_IP01             "IP01"      //Primary IP address of gateway   
#define NICKEL_CFG_IP02             "IP02"      //Primary port of gateway IP address
#define NICKEL_CFG_IP03             "IP03"      //Secondary IP address of gateway
#define NICKEL_CFG_IP04             "IP04"      //Secondary port of gateway IP address
#define NICKEL_CFG_IP05             "IP05"      //Secondary IP address of gateway
#define NICKEL_CFG_IP06             "IP06"      //Secondary port of gateway IP address
#define NICKEL_CFG_VALUE            "Value"

//Card Bin range config Node
#define NICKEL_CFG_CARDBIN_NODE     "Card_BinRange_Config"
#define NICKEL_CFG_VI01             "VI01"      //Visa    
#define NICKEL_CFG_MC01             "MC01"      //MasterCard
#define NICKEL_CFG_AX01             "AX01"      //American Express 
#define NICKEL_CFG_DS01             "DS01"      //Discover
#define NICKEL_CFG_GT01             "GT01"      //Gift Card
#define NICKEL_CFG_LC01             "LC01"      //Loyalty Card 
#define NICKEL_CFG_TC01             "TC01"      //Test Card  
#define NICKEL_CFG_DC01             "DC01"      //Driver Card 
#define NICKEL_CFG_OM01             "OM01"      //OEM Card 
#define NICKEL_CFG_AD01             "AD01"      //Audit Card 
#define NICKEL_CFG_UD01             "UD01"      //User Defined Card 
#define NICKEL_CFG_CC01             "CC01"      //Campus Cards 
#define NICKEL_CFG_CC02             "CC02"      //RIID 
#define NICKEL_CFG_CC03             "CC03"      //Non-Unique Card Number Mask 

//Retry config Node
#define NICKEL_CFG_RETRY_NODE       "Retry_Config"
#define NICKEL_CFG_RE01             "RE01"      //message retry times    
#define NICKEL_CFG_RE02             "RE02"      //message retry timeout
#define NICKEL_CFG_RE03             "RE03"      //session retry times 
#define NICKEL_CFG_RE04             "RE04"      //session retry timeout

//Control Parameters Node
#define NICKEL_CFG_CNTR_NODE     "CNTR_Config"
#define NICKEL_CFG_CN01          "CN01"
#define NICKEL_CFG_CN02          "CN02"
#define NICKEL_CFG_CN03          "CN03"
#define NICKEL_CFG_CN04          "CN04"
#define NICKEL_CFG_CN05          "CN05"
#define NICKEL_CFG_CN06          "CN06"
#define NICKEL_CFG_CN07          "CN07"
#define NICKEL_CFG_CN08          "CN08"
#define NICKEL_CFG_CN09          "CN09"
#define NICKEL_CFG_CN10          "CN10"
#define NICKEL_CFG_CN11          "CN11"
#define NICKEL_CFG_CN12          "CN12"
#define NICKEL_CFG_CN13          "CN13"
#define NICKEL_CFG_CN14          "CN14"

#define NICKEL_CFG_VEND_NODE     "VEND_Config"
#define NICKEL_CFG_VE01          "VE01"
#define NICKEL_CFG_VE02          "VE02"
#define NICKEL_CFG_VE03          "VE03"
#define NICKEL_CFG_VE04          "VE04"
#define NICKEL_CFG_VE05          "VE05"
#define NICKEL_CFG_VE06          "VE06"
#define NICKEL_CFG_VE07          "VE07"
#define NICKEL_CFG_VE08          "VE08"
#define NICKEL_CFG_VE09          "VE09"
#define NICKEL_CFG_VE10          "VE10"
#define NICKEL_CFG_VE11          "VE11"

#define NICKEL_CFG_APN_NODE      "APN_Config"
#define NICKEL_CFG_AP01          "AP01"
#define NICKEL_CFG_AP02          "AP02"
#define NICKEL_CFG_AP03          "AP03"
#define NICKEL_CFG_AP04          "AP04"
#define NICKEL_CFG_AP05          "AP05"
#define NICKEL_CFG_AP06          "AP06"  

#define NICKEL_CFG_FW_NODE      "FW_Config"
#define NICKEL_CFG_FW01          "FW01"
#define NICKEL_CFG_FW02          "FW02"
#define NICKEL_CFG_FW03          "FW03"
#define NICKEL_CFG_FW04          "FW04"
#define NICKEL_CFG_FW05          "FW05"
#define NICKEL_CFG_FW06          "FW06"
#define NICKEL_CFG_FW07          "FW07"
#define NICKEL_CFG_FW08          "FW08"
#define NICKEL_CFG_FW09          "FW09"

#define NICKEL_CFG_ECHO_NODE      "ECHO_Config"
#define NICKEL_CFG_EC01          "EC01"
#define NICKEL_CFG_EC02          "EC02"

#define NICKEL_CFG_CUSTOMER_NODE "Customer_Config"
#define NICKEL_CFG_CS01          "CS01"
#define NICKEL_CFG_CS02          "CS02"
#define NICKEL_CFG_CS03          "CS03"
#define NICKEL_CFG_CS04          "CS04"
#define NICKEL_CFG_CS05          "CS05"
#define NICKEL_CFG_CS06          "CS06"
#define NICKEL_CFG_CS07          "CS07"
#define NICKEL_CFG_CS08          "CS08"
#define NICKEL_CFG_CS09          "CS09"
#define NICKEL_CFG_CS10          "CS10"

#define NICKEL_CFG_CONFIG_NODE "Config_Config"
#define NICKEL_CFG_CO01          "CO01"
#define NICKEL_CFG_CO02          "CO02"

/* FOR COMMUNICATION */
#define PRIMARY_IP      0xB000
#define SECONDARY_IP    0xB001
#define VENDING_IP      0xB002

/* txn <-> comm wPara define */
#define SEND_REQUEST_ERR 0xB003
#define RECV_RSP_TIMEOUT 0xB004

/* FOR TXN */
#define NICKEL_MSG_TYPE_LEN 4
#define NICKEL_AUTH_REQUEST_MSG_TYPE            "1100"
#define NICKEL_AUTH_RESP_MSG_TYPE               "1110"
#define NICKEL_ADVICE_REQUEST_MSG_TYPE          "1220"
#define NICKEL_ADVICE_RESP_MSG_TYPE             "1230"
#define NICKEL_REVERSAL_REQUEST_MSG_TYPE        "1420"
#define NICKEL_REVERSAL_RESP_MSG_TYPE           "1430"
#define NICKEL_ADVICE_REQUEST_RESEND_MSG_TYPE   "1221"
#define NICKEL_REVERSAL_REQUEST_RESEND_MSG_TYPE "1421"

#define NICKEL_REVERSAL_REASON_CODE_TIMEOUT     "4021"
#define NICKEL_REVERSAL_REASON_CODE_CANCEL      "4000"
#define NICKEL_REVERSAL_REASON_CODE_Donation    "02"

#define NICKEL_FORCE_FREE_VEND                  "200"
#define NICKEL_DISCRETIONARY_FREE_VEND          "100"

#define NICKEL_CASTLES "CTC"
//Card Type
/* Defined in accordance with the protocol */
#define NICKEL_CARD_TYPE_MSR         '2'
#define NICKEL_CARD_TYPE_CT_ICC      '5'
#define NICKEL_CARD_TYPE_CTLS_ICC    'A'
#define NICKEL_CARD_TYPE_CTLS_MSD    'B'
#define NICKEL_CARD_TYPE_CTLS_NFC    'C'
#define NICKEL_CARD_TYPE_INVALID     'F'
//DE39 Action Code
#define APPROVE                      "000"
#define PARTIAL_APPROVED             "002" 
#define APPROVED_FOR_VIP             "003"
#define INVALID_MAC_VALUE            "916"
#define KEY_SYN_ERR                  "919"

/* FOR UI */
//No Response UI ID
#define NICKEL_UI_MAIN                                   0x1001
#define UI_TYPE_IDLE                                     0x0001
#define UI_TYPE_READCARD                                 0x0002
#define UI_TYPE_AUTHORIZATION                            0x0003
#define UI_TYPE_SELECT_DRINK                             0x0004
#define UI_TYPE_CANCEL                                   0x0005
#define UI_TYPE_VENDING                                  0x0006
#define UI_TYPE_TRYAGAIN                                 0x0007
#define UI_TYPE_ANOTHERSELECT                            0x0008
#define UI_TYPE_SALECOMPLETED                            0x0009
#define UI_TYPE_READCARDERROR                            0x000A
#define UI_TYPE_TRYANOTHERCARD                           0x000B
#define UI_TYPE_NOAUTHRESP                               0x000C
#define UI_TYPE_AUTHDECLINED                             0x000D
#define UI_TYPE_INVALIDCARD                              0x000E
#define UI_TYPE_APPROVED                                 0x000F

#define UI_TYPE_DONATIONENABLE                           0x0010
#define UI_TYPE_DONATIONTHS                              0x0011
#define UI_TYPE_DONATIONTHSFAIL                          0x0012
#define UI_TYPE_FREEVEND                                 0x0013
#define UI_TYPE_ENJOYFREEDRINK                           0x0014
#define UI_TYPE_DISPLAY_TEXT                             0x0015
#define UI_TYPE_USEYOURPOINT                             0x0016
#define UI_TYPE_DISCONNECT                               0x0017


//Have Response UI ID


//Card Type
#define VISA            0xC001
#define MASTERCARD      0xC002
#define AMEX            0xC003
#define DESCOVER        0xC004
#define GIFT            0xC005
#define LOYALTY         0xC006
#define TEXT            0xC007
#define DRIVER          0xC008
#define OEM             0xC009
#define AUDIT           0xC010
#define USERDEFINED     0xC011
#define CAMPUS          0xC012
#define RIID            0xC013
#define NONUNIQUE       0xC014
#define NORMALCARD      0xC015
#define UNKNOWCARD      0xC099


//Retry parameters 
#define RE01            0x0001
#define RE02            0x0002
#define RE03            0x0003
#define RE04            0x0004
#define TIMEMULTIPLES   1000

//Control Parameters type
#define CN01          0x0001
#define CN02          0x0002
#define CN03          0x0003
#define CN04          0x0004
#define CN05          0x0005
#define CN06          0x0006
#define CN07          0x0007
#define CN08          0x0008
#define CN09          0x0009
#define CN10          0x0010
#define CN11          0x0011
#define CN12          0x0012
#define CN13          0x0013
#define CN14          0x0014

//Vend paramters
#define VE01          0x0001
#define VE02          0x0002
#define VE03          0x0003
#define VE04          0x0004
#define VE05          0x0005
#define VE06          0x0006
#define VE07          0x0007
#define VE08          0x0008
#define VE09          0x0009
#define VE10          0x0010
#define VE11          0x0011

//Apn paramters
#define AP01          0x0001
#define AP02          0x0002
#define AP03          0x0003
#define AP04          0x0004
#define AP05          0x0005
#define AP06          0x0006

//FW paramters
#define FW01          0x0001
#define FW02          0x0002
#define FW03          0x0003
#define FW04          0x0004
#define FW05          0x0005
#define FW06          0x0006
#define FW07          0x0007
#define FW08          0x0008
#define FW09          0x0009

//ECHO paramters
#define EC01          0x0001
#define EC02          0x0002

//Customer paramters
#define CS01          0x0001
#define CS02          0x0002
#define CS03          0x0003
#define CS04          0x0004
#define CS05          0x0005
#define CS06          0x0006
#define CS07          0x0007
#define CS08          0x0008
#define CS09          0x0009
#define CS10          0x0010

//Config paramters
#define CO01          0x0001
#define CO02          0x0002

#endif /* MSGCOMMTYPE_H */


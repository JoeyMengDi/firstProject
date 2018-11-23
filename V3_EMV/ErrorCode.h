/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   error_code.h
 * Author: Louis Lu
 *
 * Created on 2017Ôø????4Ôø????7Ôø????, ‰∏ãÂçà7:06
 */
//
#ifndef H_ERROR_CODE
#define H_ERROR_CODE

//Common status
#define OK                                  0x0000
#define MSG_NO_DATA                         0x0002

//Error Code
#define ERROR_BASE                          ( 0xF000 )
#define ERROR_INVALID_PARAM                 ( ERROR_BASE + 0x01 )


#define ERROR_TIMEOUT                       ( ERROR_BASE + 0x07 )

#define ERROR_USER_CANCEL                   ( ERROR_BASE + 0x08 )
#define ERROR_NOT_CONNECTED                 ( ERROR_BASE + 0x0A )
#define ERROR_INSUFFICIENT_BUFFERR          ( ERROR_BASE + 0x0B )
#define ERROR_NOT_REGISTER_CALLBACK         ( ERROR_BASE + 0x0C )
#define ERROR_MSG_QUEUE                     ( ERROR_BASE + 0x0D )
//#define ERROR_MSG_QUEUE                   ( ERROR_BASE + 0x0E )

#define ERROR_NOT_SUPPORT_COMMTYPE          ( ERROR_BASE + 0x0F )


/*WIFI ERROR*/
#define ERROR_WIFI                          ( ERROR_BASE + 0x71 )

/*Ethernet ERROR*/
#define ERROR_ETHERNET                      ( ERROR_BASE + 0x81 )

/*RS232 ERROR*/
#define ERROR_RS232                         ( ERROR_BASE + 0x91 )

/*GPRS ERROR*/
#define ERROR_GPRS                          ( ERROR_BASE + 0xA1 )

/*CLOUD ERROR*/
#define ERROR_CLOUD                         ( ERROR_BASE + 0xB1 )

// CProfile error code
#define ERROR_XML                           ( ERROR_BASE + 0x0101 )

// CParsePosCmd
#define ERROR_DATA                          ( ERROR_BASE + 0x0201)

// UserMng 
#define ERROR_USERMNG                       ( ERROR_BASE + 0x0301)

// PPP Error
#define ERROR_PPP                           ( ERROR_BASE + 0x0401 )

#define SOCKET_ERROR                        ( -1 )

// Communication Error
#define ERROR_INIT_COMM_FAIL                (ERROR_BASE + 0x80)








#endif /* ERROR_CODE_H */


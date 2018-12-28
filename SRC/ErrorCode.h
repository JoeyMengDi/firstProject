/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   error_code.h
 * Author: Administrator
 *
 * Created on 2017年4月7日, 下午7:06
 */
//
#ifndef H_ERROR_CODE
#define H_ERROR_CODE

//Common status
#define OK								0x0000
#define FAILED							0x0001	
#define MSG_NO_DATA			            0x0002
#define ERROR_DATA                      0x0003

//Error Code
#define ERROR_BASE                      0xF000
#define ERROR_INVALID_PARAM             ERROR_BASE + 0x01
#define ERROR_NODATA_PARSE              ERROR_BASE + 0x02
#define ERROR_NODATA_SEND               ERROR_BASE + 0x03

#define ERROR_BT_CONNECTION_BROKEN      ERROR_BASE + 0x04


//#define ERROR_FEILED_INDEX            ERROR_BASE + 0x02
//#define ERROR_NODATA_PARSE			ERROR_BASE + 0x03
//#define ERROR_DE_NOTSET				ERROR_BASE + 0x04
//#define ERROR_OPENXML_FAILED			ERROR_BASE + 0x05
//#define ERROR_XML_FORMAT				ERROR_BASE + 0x06
//#define ERROR_DATA_FORMAT				ERROR_BASE + 0x07

#define ERROR_INVALID_DATA_HEAD			ERROR_BASE + 0x08
#define ERROR_INVALID_DATA_TAIL			ERROR_BASE + 0x09
#define ERROR_INVALID_MSG_ID			ERROR_BASE + 0x0A
#define ERROR_INVALID_MSG_DATA_TYPE		ERROR_BASE + 0x0B
#define ERROR_INVALID_LRC                       ERROR_BASE + 0x0C
#define ERROR_INVALID_DATA                      ERROR_BASE + 0x0D

#define ERROR_SMARTTAP                      ( ERROR_BASE + 0x0500 )
#define ERROR_POLL_CARD_TIMEOUT             ( ERROR_SMARTTAP + 0x06 )
#define ERROR_PAYMENT_NOT_READY             ( ERROR_SMARTTAP + 0x07 )
#define ERROR_GO_TO_PAYMENT                 ( ERROR_SMARTTAP + 0x12 )


// CProfile error code
#define ERROR_XML                           ( ERROR_BASE + 0x0101 )
#define ERROR_INSUFFICIENT_BUFFERR          ( ERROR_BASE + 0x0B )

#define ERROR_INVALID_LOGIC                 ( ERROR_BASE + 0x0102 )




#endif /* ERROR_CODE_H */


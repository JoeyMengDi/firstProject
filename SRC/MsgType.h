/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MsgType.h
 * Author: Louis Lu
 *
 * Created on 2017年7月5日, 上午8:50
 */

#ifndef _H_MSGTYPE_H_
#define _H_MSGTYPE_H_


// Message Type Definition
#define MSG_TXN_DATA                0x00000001
#define MSG_TXN_RSP                 0x00000002

#define MSG_UI                      0x00000004
#define MSG_UI_RSP                  0x00000008

#define MSG_STOP_COMM               0x00000010
#define MSG_STOP_UI                 0x00000020
#define MSG_STOP_TXN                0x00000040

#define MSG_ERR                     0x00000080
#define MSG_WARNING                 0x00000100

#define MSG_COMM_CONN               0x00000200
#define MSG_COMM_CONN_RSP           0x00000400

#define MSG_COMM_DISCONN            0x00000800
#define MSG_COMM_DISCONN_RSP        0x00001000

#define MSG_TXN_ERR                 0x00002000

#define MSG_COMM_EXC_IP             0x00004000
#define MSG_COMM_EXC_IP_RSP         0x00008000

#define MSG_MDB                     0x00010000
#define MSG_MDB_RSP                 0x00020000

#define MSG_MDB_NOTIFY              0x00040000
#define MSG_MDB_NOTIFY_RSP          0x00080000

#define MSG_TXN_REQUEST_OK          0x00100000









//#define MSG_TXN_GETDATA         0x5001
//#define MSG_UI_RSPDATA          0x6001
//#define MSG_STOP_UI             0x6002
//#define MSG_QUERY_STATUS        0x4003
//#define MSG_QUERY_ANSWER        0x4004
//#define MSG_UNSOLICITED_STATUS  0x4007
//#define MSG_OPEN_COMM_FAIL      0x4009


//#define CLEAR_MSG_FLAG          (-16391)


// Status Message Definition
//#define MSG_CONN_BROKEN     0x5001



#endif
/* 
 * File:   defs.h
 * Author: James
 *
 * Created on 2017年7月28日, 上午10:43
 */

#ifndef DEFS_H
#define DEFS_H

#ifdef __cplusplus
extern "C" {
#endif


#define	MINUTE                                 60000		//a minmute
#define MAXTIME                                (MINUTE/4)	//time-out period
#define RECVSENDBUF                            10*1024		//send & recv buffer size

#define PARSE_OK                               (0x0)

#define MSG_AUTHORIZATION                      (0xD000)
#define MSG_FINANCIAL_TRANSACTION              (MSG_AUTHORIZATION + 0x01)
#define MSG_FINANCIAL_TRANSACTION_CONFIRM      (MSG_AUTHORIZATION + 0x02)
#define MSG_REVERSAL                           (MSG_AUTHORIZATION + 0x03)
#define MSG_ONLINE_ADVICE                      (MSG_AUTHORIZATION + 0x04)
#define MSG_BATCH_DATA_CAPTURE                 (MSG_AUTHORIZATION + 0x05)


#define ERROR_SOCKET_OPEN                       (0xE000)
#define ERROR_SOCKET_RECV                       (ERROR_SOCKET_OPEN+0x01)
#define ERROR_SOCKET_SEND                       (ERROR_SOCKET_OPEN+0x02)    
#define ERROR_TLV_TOO_LONG                      (ERROR_SOCKET_OPEN+0x03)
#define ERROR_MSGTYPE_NOT_MATCH                 (ERROR_SOCKET_OPEN+0x04)
#define ERROR_TLV_LENGTH_NOT_MATCH              (ERROR_SOCKET_OPEN+0x05)



#ifdef __cplusplus
}
#endif

#endif /* DEFS_H */


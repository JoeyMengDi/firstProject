
/* 
 * Copyright(c) Castles Technology Co,. Ltd
 * 
 * File Name: msgqueue.h
 * Author: Alan.Ren
 *
 * Date: 2017/07/13
 */

#ifndef _H_MSGQUEUE_H_H_
#define _H_MSGQUEUE_H_H_

#ifndef WORD
#define WORD unsigned short
#endif

#ifndef BYTE
#define BYTE unsigned char
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

#ifdef __cplusplus
extern "C"
{
#endif

    WORD CTAP_Send(IN const DWORD dwMsgType,
                   IN const WORD wParam,
                   IN const WORD lParam,
                   IN const CByteStream *pcData,
                   IN const DWORD dwTimeout);

    WORD CTAP_Recv(INOUT DWORD &dwMsgType,
                  OUT WORD &wWParam,
                  OUT WORD &wLParam,
                  OUT CByteStream &cData,
                  IN const DWORD dwTimeout);
    
    WORD CTAP_RecvMulti(INOUT CByteStream &cMsgIdBuf,
                       OUT WORD &wWParam,
                       OUT WORD &wLParam,
                       OUT CByteStream &cData,
                       IN const DWORD dwTimeout);
    
#ifdef __cplusplus
}
#endif

#endif


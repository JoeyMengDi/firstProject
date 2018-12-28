
/* 
 * File:   cTlv.h
 * Author: Tim Ma
 *
 * Created on 2018年4月28日, 下午3:33
 */

#ifndef  __CLOUDLIB_TLV_H__
#define  __CLOUDLIB_TLV_H__

#ifdef  __cplusplus
extern "C" {
#endif
                                                                                                                      
#define ERRMSG          1           /* false message */                                                                    
#define MAXMSG          2           /* the message is too long */                                                          
#define NOFIELD         3           /* this domain does not exist */                                                       
#define ERRFIELD        4           /* this domain error */                                                                
#define DUPFIELD        5           /* this domain has already existed */                                                  
#define NULLFIELD       6           /* the domain value is null */                                                         
#define MAXFIELD        7           /* the value of this domain is too long */                                             
#define MAXNAME         8           /* this domain name is overlong */    

                                        
#define iMAXFLDNAMELEN  32          /* The maximum length of TLV domain name */     
    
 /**
* Get value from TlvMsgBuff
* @param pFldName   [in]        Tag Name, the max size of TAG NAME is 32(iMAXFLDNAMELEN)
* @param pFldBuffer [out]       Tag Value, point to the special position of pTlvMsgBuf
* @param pTlvMsgBuf [in]        TLV Buffer, store lots of tlvs
* @return            
*                  > 0 : length of the special tag value
*                  -1  : failed
*/                          
int TlvTagGet( char *pFldName,char *pFldBuffer,char *pTlvMsgBuf);


/**
* Set pFldName and pFldBuffer into pTlvMsgBuf
* @param pFldName   [in]        Tag Name
* @param pFldBuffer [in]        Tag Value
* @param pTlvMsgBuf [in_out]    TLV Buffer, store lots of tlvs
* @param iFldLen    [in]        Tag Value length
* @param pErrCode   [out]       error code
 * 
* @return            [out]  
                        -1 : failed
                        >0 : the length of pTlvMsgBuf is
*/
int TlvTagSet( char *pFldName, char *pFldBuffer, char *pTlvMsgBuf, int iFldLen, int *pErrCode);


#ifdef  __cplusplus
}
#endif

#endif



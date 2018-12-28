/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EMVBase.h
 * Author: Administrator
 *
 * Created on 2017年8月3日, 下午5:06
 */

#ifndef H_EMVBASE
#define H_EMVBASE

#include "../SRC/StdafxHead.h"

#define BYTEMAXVAL  256
#define MAXBUFLEN  2048
#define TAG_NO_TFOUND 0xE001


class CEMVBase
{
public:
    CEMVBase();
    virtual ~CEMVBase();
    
    WORD GetData(PCSTR pcTags, BYTE* pScrData, USHORT usLen, CByteStream &cRet, BOOL bFullTlv);
    /* NOT for EMV contactless */
    WORD FillTags(PBYTE pbyTags, WORD wTagLen, PBYTE pbyTLV, PWORD pwTLVLen);
    int CheckTagNumber(PBYTE pbyTags);
    int  CheckTagNumber(PBYTE pbyTags, BYTE byLen);
    int  CheckLengthLength(PBYTE pByLen, USHORT *usValueLen);
    WORD SkipTag(PBYTE *pbyData, int &nSkipLen);
    WORD SkipLength(PBYTE *pbyData, int &nSkipLen, int &nDataLen);
    WORD SkipTL(PBYTE *pbyData, int &nSkipLen, int &nDataLen);
    WORD SkipTLV(PBYTE *pbyData, int &nSkipLen, int &nDataLen);
    
	//PBYTE ScanTag(PBYTE pbyTags, PBYTE pData, int nLen, PINT pLenRet, BYTE byTLV);
    //PBYTE ScanTag(PBYTE pbyTags, CByteStream *pData, PINT pLen, BYTE byTLV);
    
private:
    

};

#endif /* H_EMVBASE */


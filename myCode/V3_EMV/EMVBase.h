/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EMVBase.h
 * Author: Administrator
 *
 * Created on 2017å¹?8??3??, ä¸???5:06
 */

#ifndef H_EMVBASE
#define H_EMVBASE

//#include "StdafxHead.h"
#include "deftype.h"
#include "ByteStream.h"
#include "DbgMacro.h"
#include "EMVCommon.h"

#define BYTEMAXVAL  256
#define MAXBUFLEN  2048
#define TAG_NO_TFOUND 0xE001


class CEMVBase
{
public:
    CEMVBase();
    virtual ~CEMVBase();
    
    WORD GetData(PBYTE pbyTags, CByteStream *pScrData, CByteStream &cRet, BOOL bFullTlv);
    WORD FillTags(PBYTE pbyTags, WORD wTagLen, PBYTE pbyTLV, PWORD pwTLVLen);
    int CheckTagNumber(PBYTE pbyTags);
    int  CheckTagNumber(PBYTE pbyTags, BYTE byLen);
    int  CheckLengthLength(PBYTE pByLen, USHORT *usValueLen);
    WORD SkipTag(PBYTE *pbyData, int &nSkipLen);
    WORD SkipLength(PBYTE *pbyData, int &nSkipLen, int &nDataLen);
    WORD SkipTL(PBYTE *pbyData, int &nSkipLen, int &nDataLen);
    WORD SkipTLV(PBYTE *pbyData, int &nSkipLen, int &nDataLen);
    PBYTE ScanTag(PBYTE pbyTags, PBYTE pData, int nLen, int* pLenRet, BYTE byTLV);
    PBYTE ScanTag(PBYTE pbyTags, CByteStream *pData, int* pLen, BYTE byTLV);
    
private:
    

};

#endif /* H_EMVBASE */


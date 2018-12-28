/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EMVBase.cpp
 * Author: Louis Lu
 * 
 * Created on 2017年8月3日, 下午5:06
 */

#include "EMVBase.h"
#include "../SRC/ErrorCode.h"
#include <emvaplib.h>

 

CEMVBase::CEMVBase()
{
}

CEMVBase::~CEMVBase()
{
}

WORD CEMVBase::GetData(PCSTR pcszTags, BYTE* pbyScrData, USHORT usLen, CByteStream& cRet, BYTE byFullTlv)
{
    DEBUG_ENTRY();
    
    if((pcszTags == NULL) || (pbyScrData == NULL))
        return DEBUG_RETCODE("GetData", ERROR_INVALID_PARAM);

    //Check Tags
    int nTagLen = 0;
    BYTE byTag[4] = {0};//max support N-8 len tag
    LONG lTag = strtol(pcszTags, NULL, 16);
    if(lTag<=0)
        return DEBUG_RETCODE("ERROR: invalid tag", ERROR_CTBC_INVALID_TAG);
    ++nTagLen;
    
    while(lTag>>(8*nTagLen)) 
        ++nTagLen; //check ~0 byte
    
    
    PBYTE pbyTag = (PBYTE)&lTag;
    for(int i = 0; i < nTagLen; ++i)
        byTag[i] = *(pbyTag+nTagLen-i-1);
    
    BYTE byTag1=0, byTag2=0;
    byTag1 = *byTag;

    if(CheckTagNumber(byTag) == 2)
        byTag2 = *(byTag+1);

    BYTE  *pbySeek, byTempbyte;

    pbySeek = pbyScrData;
    PBYTE pEnd = pbySeek + usLen;
   
    BOOL bFind = FALSE;
    WORD wRet = 0;
    cRet.Empty();
    
    while(pbySeek < pEnd)
    {
        if((*pbySeek==0xFF) || (*pbySeek==0x00))
        {
            pbySeek++;
            continue;
        }

        byTempbyte = *pbySeek ;

        if(byTag2 !=0)
        {
            if((byTempbyte == byTag1) && (*(pbySeek+1) == byTag2))
            {
                pbyTag  = pbySeek;
                bFind = TRUE;
                break;
            }
        }
        else
        {
            if(byTempbyte == byTag1)
            {
                pbyTag = pbySeek;
                bFind = TRUE;
                break;
            }
        }  

        //Skip TLV
        int nDataLen = 0, nSkipLen=0;
        wRet = SkipTLV(&pbySeek, nSkipLen, nDataLen);
        if(Failure(wRet))
            return wRet;
    }

    if(bFind)
    {
        PBYTE pTemp = pbySeek;
        int nDataLen = 0, nSkipLen = 0;
        wRet = SkipTL(&pbySeek, nSkipLen, nDataLen);
        if(Failure(wRet))
            return DEBUG_RETCODE("GetData ", wRet);

        if((pEnd-pTemp)<(nSkipLen+nDataLen))
            return  DEBUG_RETCODE("GetData ",ERROR_DATA);

        if(byFullTlv)			
            cRet.Write(pTemp, nSkipLen+nDataLen);
        else
            cRet.Write(pbySeek, nDataLen);

        return DEBUG_RETCODE("GetData ", OK);
    }

    return DEBUG_EXIT(TAG_NO_TFOUND);
}



WORD CEMVBase::FillTags(PBYTE pbyTags, WORD wTagLen, PBYTE pbyTLV, PWORD pwTLVLen)
{
    DEBUG_ENTRY();
    
    if(pbyTags == NULL)
        return ERROR_INVALID_PARAM;

    if(pwTLVLen == NULL)
        return ERROR_INVALID_PARAM;

    CByteStream cTlv, cTemp;
    PBYTE pHead = pbyTags;
    PBYTE pEnd = pbyTags+wTagLen;
    BYTE byValueBuf[MAXBUFLEN];
    USHORT usValueLen = MAXBUFLEN;
    
    cTemp.Empty();
    USHORT usRet = 0;

    while(pHead < pEnd)
    {
        memset(byValueBuf, 0x00, MAXBUFLEN);
        usValueLen = MAXBUFLEN;
        cTemp.Empty();
        int nTag = 1;

        nTag = CheckTagNumber(pHead);
        if(nTag == 1)
        {
            usRet = EMV_DataGet(MAKEWORD(0x00, *pHead), &usValueLen, byValueBuf);
            if((usRet != d_EMVAPLIB_OK) && (usRet != d_EMVAPLIB_ERR_NO_DATA) )
            {
                return DEBUG_RETCODE("EMV_DataGet, ret: ", usRet);
            }
            else if(usRet == d_EMVAPLIB_ERR_NO_DATA)
            {
                pHead += nTag;
                
                continue;
            }
            else
            {
                cTemp.Write(pHead, 1);
                DEBUG_STREAM(&cTemp, "Tag ");
            }
        }
        else if(nTag == 2)
        {           
            usRet = EMV_DataGet(MAKEWORD(*pHead, *(pHead+1)), &usValueLen, byValueBuf);
            if((usRet != d_EMVAPLIB_OK) && (usRet != d_EMVAPLIB_ERR_NO_DATA) )
            {
                return DEBUG_RETCODE("EMV_DataGet, ret: ", usRet);
            }
            else if(usRet == d_EMVAPLIB_ERR_NO_DATA)
            {
                pHead += nTag;
                
                continue;
            }
            else
            {
                cTemp.Write(pHead, 2);
                DEBUG_STREAM(&cTemp, "Tag ");
            }
        }
        else if(nTag == 3)
        {
            usRet = EMV_DataGet(MAKEDWORD(MAKEWORD(0x00, *pHead), MAKEWORD(*(pHead+1), *(pHead+2))), &usValueLen, byValueBuf);
            if((usRet != d_EMVAPLIB_OK) && (usRet != d_EMVAPLIB_ERR_NO_DATA) )
            {
                return DEBUG_RETCODE("EMV_DataGet, ret: ", usRet);
            }
            else if(usRet == d_EMVAPLIB_ERR_NO_DATA)
            {
                pHead += nTag;
                
                continue;
            }
            else
            {
                cTemp.Write(pHead, 3);
                DEBUG_STREAM(&cTemp, "Tag ");
            }
        }
        else if(nTag == 4)
        {
            usRet = EMV_DataGet(MAKEDWORD(MAKEWORD(*pHead, *(pHead+1)), MAKEWORD(*(pHead+2), *(pHead+3))), &usValueLen, byValueBuf);
            if((usRet != d_EMVAPLIB_OK) && (usRet != d_EMVAPLIB_ERR_NO_DATA) )
            {
                return DEBUG_RETCODE("EMV_DataGet, ret: ", usRet);
            }
            else if(usRet == d_EMVAPLIB_ERR_NO_DATA)
            {
                pHead += nTag;
                
                continue;
            }
            else
            {
                cTemp.Write(pHead, 4);
                DEBUG_STREAM(&cTemp, "Tag ");
            }
        }
        else
        {
            return DEBUG_RETCODE("FillTags", ERROR_DATA);
        }
        
        pHead += nTag;

        if(usValueLen < BYTEMAXVAL)
        {            
            cTemp << LOBYTE(usValueLen);
        }
        else
        {
            cTemp << LOBYTE(usValueLen);
            cTemp << HIBYTE(usValueLen);
        }
        
        cTemp.Write(byValueBuf, usValueLen);
        cTlv.Write(cTemp.GetBuffer(), cTemp.GetLength());
    }

    if((cTlv.GetLength()>*pwTLVLen) || (pbyTLV == NULL))
    {
        *pwTLVLen = cTlv.GetLength();
        return DEBUG_RETCODE("FillTags", ERROR_INSUFFICIENT_BUFFERR);
    }

    *pwTLVLen = cTlv.GetLength();
    memcpy(pbyTLV, cTlv.GetBuffer(), *pwTLVLen);

    return DEBUG_EXIT(OK);
}

//pbyData---TLV
//skip Tag return skip bytes
WORD CEMVBase::SkipTag(PBYTE *pbyData, int &nSkipLen)
{
    int nTag = 1;
    BYTE byTag = *(*pbyData);
    //Skip tag
    if((byTag & 0x1F) == 0x1F)
    {
        //Two tag
        (*pbyData) += 2;
        nSkipLen = 2;
    }
    else
    {
        (*pbyData)++; 
        nSkipLen = 1;
    }

    return 0;
}



//pbyData---L+V...
//nSkipLen---skip bytes
//nDataLen---Data length
WORD CEMVBase::SkipLength(PBYTE *pbyData, int &nSkipLen, int &nDataLen)
{
    PBYTE pbySeek = *pbyData;
    
    //check EMV Book3 Page157
    if(*pbySeek >0x82)
        return ERROR_DATA;

    nSkipLen = 0;
    nDataLen = 0;
    if(*pbySeek == 0x81)
    { 
        nDataLen = *(pbySeek+1);

        nSkipLen = 2;
        pbySeek += nSkipLen;
    }
    else if(*pbySeek == 0x82)
    {
        nDataLen = *(pbySeek+1)*256 + (*(pbySeek+2));
        nSkipLen = 3;
        pbySeek += nSkipLen;
    }
    else 
    {
        nDataLen = *pbySeek;

        nSkipLen = 1;
        pbySeek += nSkipLen;
    }

    *pbyData = pbySeek;

    return 0;
}


//nSkipLen---Skip bytes
//nDataLen---Data length
WORD CEMVBase::SkipTL(PBYTE *pbyData, int &nSkipLen, int &nDataLen)
{
    nSkipLen = 0;
    nDataLen = 0;
    int m_nSkipLen = 0;

    WORD wRet = 0;

    SkipTag(pbyData, nSkipLen);
    wRet = SkipLength(pbyData, m_nSkipLen, nDataLen);
    if(Failure(wRet))
    {
        nSkipLen = 0;
        nDataLen = 0;
        return wRet;
    }
    nSkipLen += m_nSkipLen;

    return 0;
}




//return skip bytes
WORD CEMVBase::SkipTLV(PBYTE *pbyData, int &nSkipLen, int &nDataLen)
{
    nSkipLen = 0;
    nDataLen = 0;
    int m_nSkipLen = 0;

    WORD wRet = 0;

    SkipTag(pbyData, nSkipLen);
    wRet = SkipLength(pbyData, m_nSkipLen, nDataLen);
    if(Failure(wRet))
        return wRet;

    nSkipLen += (m_nSkipLen+nDataLen);
    *pbyData += nDataLen;

    return 0;
}



int CEMVBase::CheckTagNumber(PBYTE pbyTags, BYTE byLen)
{
    USHORT usTagLen = 1;

    if(pbyTags == NULL || byLen == 0)
        return 0;

    //check tag
    int iCnt = 0;
    if(((pbyTags[iCnt] & 0x1F) == 0x1F) && (byLen > iCnt))
    {
        usTagLen ++;
        iCnt ++;
        while((pbyTags[iCnt] & 0x80) && (byLen > iCnt))
        {
            usTagLen ++;
            iCnt ++;
            if(usTagLen > 4)
                return ERROR_DATA;
        }        
    }
    
    if(byLen <= iCnt)
    {
        return ERROR_DATA;
    }

    return usTagLen;	// Tag Length
}


int CEMVBase::CheckTagNumber(PBYTE pbyTags)
{
    USHORT usTagLen = 1;

    if(pbyTags == NULL)
        return 0;

    //check tag
    int iCnt = 0;
    if((pbyTags[iCnt] & 0x1F) == 0x1F)
    {
        usTagLen ++;
        iCnt ++;
        while(pbyTags[iCnt] & 0x80)
        {
            usTagLen ++;
            iCnt ++;
            if(usTagLen > 4)
                return ERROR_DATA;
        }        
    }

    return usTagLen;	// Tag Length
}

int CEMVBase::CheckLengthLength(PBYTE pbyLen, unsigned short* pusValueLen)
{
    if(pbyLen == NULL && pusValueLen == NULL)
    {
        return ERROR_DATA;
    }
    
    USHORT usLengthLen;

    if (*pbyLen < 0x80) 
    {
        usLengthLen = 1;
        *pusValueLen = *pbyLen;
    } 
    else if (*pbyLen == 0x81) 
    {
        usLengthLen = 2;
        *pusValueLen = pbyLen[1];
    } 
    else if (*pbyLen == 0x82) 
    {
        usLengthLen = 3;
        *pusValueLen = ((pbyLen[1] << 8) + pbyLen[2]);
    } 
    else if (*pbyLen == 0x83) 
    {
        usLengthLen = 4;
        *pusValueLen = ((pbyLen[1] << 16) + (pbyLen[2] << 8) + pbyLen[3]);
    } 
    else
    {
        usLengthLen = 0;
    }

    return usLengthLen;
}


/**
 * Copyright(c) Castles Technology Co,. Ltd
 * 
 * File Name: DebugInfo.cpp
 * 
 * Author: Sword.Zhang
 * 
 * Create Date: 2017.06.08
 * 
 * History:
 *           #2018.07.25, Tim.Ma
 *           1. Add thread ID in GetTime.
 * 
 *           #2018.06.11, Alan.Ren
 *           1. Modify and improve.
 **/

#include "deftype.h"
#include "ByteStream.h"
#include "DebugInfo.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define ERROR_INVALID_PARAM (-1)

CDebugInfo::CDebugInfo(void)
{
    m_byDebug = 0;
    m_byDebugType = 0;
    m_dwDebugLevel = 0;
    pFunCB = NULL;
}

CDebugInfo::~CDebugInfo(void)
{

}

//byDebug   0-Disenable debug, other-EnabledDebug
//byDebugType   0-Printf, other-CallBack 

WORD CDebugInfo::DebugEnable(BYTE byDebug, BYTE byDebugType, DWORD dwLevel, WORD(*pFun)(WORD wCBType, WPARAM wParam, LPARAM lParam))
{
    m_byDebug = byDebug;
    m_dwDebugLevel = dwLevel;

    if (byDebugType != 0)
    {
        if (pFun != NULL)
            pFunCB = pFun;

    }
    m_byDebugType = byDebugType;

    return 0;
}

WORD CDebugInfo::DebugCBRegister(WORD(*pFun)(WORD wCBType, WPARAM wParam, LPARAM lParam))
{
    if (pFun == NULL)
        return ERROR_INVALID_PARAM;

    pFunCB = pFun;

    return 0;
}

void CDebugInfo::DebugEntry(PCSTR lpFileName, int iLine, PCSTR lpStr)
{
    if (m_byDebug == 0)
        return;

    DebugInfo(lpFileName, iLine, DEBUGINFO_NORMAL, "%s-Entry", lpStr);
}

void CDebugInfo::DebugInfo(PCSTR pSourceFileName, int iLineNo, DWORD dwLevel, PCSTR pFormat, ...)
{
    if (m_byDebug == 0)
        return;

    CByteStream cData;
    int nLen = 0;
    va_list argList;

    GetTime(cData, pSourceFileName, iLineNo);

    va_start(argList, pFormat);
    nLen = vsnprintf(NULL, 0, pFormat, argList) + 1;
    char *pszBuf = (char *) malloc(nLen);
    if (NULL == pszBuf)
        return;
    bzero(pszBuf, nLen);
    vsprintf(pszBuf, pFormat, argList);
    va_end(argList);
	
	//FILE* fp = fopen("tmplog", "a+");

#if 1    
    cData += ":";
    cData += pszBuf;
    cData += "\r\n";

    free(pszBuf);
    pszBuf = NULL;

    if ((m_byDebugType == 0) || (pFunCB == NULL))
    {
        printf(cData.PushZero());
    }
    else if (pFunCB != NULL)
    {
        if (dwLevel != m_dwDebugLevel)
        {
            pFunCB(DEBUG_MSG, (WPARAM) cData.PushZero(), dwLevel);
        }
        else
        {
            pFunCB(DEBUG_MSG, (WPARAM) cData.PushZero(), m_dwDebugLevel);
        }
    }
#endif	
}

WORD CDebugInfo::DebugRetCode(PCSTR lpFileName, int iLine, PCSTR lpStr, WORD wRet)
{
    if (m_byDebug == 0)
        return wRet;

    DebugInfo(lpFileName, iLine, DEBUGINFO_NORMAL, "%s-RetCode:0x%02X%02X", lpStr, wRet / 256, wRet % 256);

    return wRet;
}

WORD CDebugInfo::DebugExit(PCSTR lpFileName, int iLine, PCSTR lpStr, WORD wRet)
{
    if (m_byDebug == 0)
        return wRet;

    DebugInfo(lpFileName, iLine, DEBUGINFO_NORMAL, "%s-Exit, RetCode:0x%02X%02X", lpStr, wRet / 256, wRet % 256);

    return wRet;
}

void CDebugInfo::DebugByteStream(PCSTR lpFileName, int iLine, DWORD dwLevel, BYTE *pbyData, int nLen, PCSTR pszStr)
{
    CByteStream cTemp;
    cTemp.Write(pbyData, nLen);

    DebugByteStream(lpFileName, iLine, dwLevel, &cTemp, pszStr);
}

void CDebugInfo::DebugByteStream(PCSTR lpFileName, int iLine, DWORD dwLevel, CByteStream *pCmd, PCSTR pszStr)
{
    if (m_byDebug == 0)
        return;

    CByteStream cData;
    GetTime(cData, lpFileName, iLine);

    CByteStream cStr;
    Hex2ASC(pCmd, cStr);

    cData += " ";
    cData += pszStr;
    cData += ":";
    cData += cStr;
    cData += "\r\n";

    const char *pszOut = cData.PushZero();

    if ((m_byDebugType == 0) || (pFunCB == NULL))
        printf(pszOut);
    else
    {
        if (dwLevel != m_dwDebugLevel)
            pFunCB(DEBUG_MSG, (WPARAM) pszOut, dwLevel);
        else
            pFunCB(DEBUG_MSG, (WPARAM) pszOut, m_dwDebugLevel);
    }
}

DWORD CDebugInfo::Hex2ASC(CByteStream *pcSrc, CByteStream &cOut, WORD dwFormat)
{

    if (pcSrc == NULL)
        return ERROR_INVALID_PARAM;

    PBYTE pbyData = pcSrc->GetBuffer();
    int nSize = pcSrc->GetLength();
    char szBuf[4];
    cOut.Empty();

    for (int i = 0; i < nSize; i++)
    {
        memset(szBuf, 0, 4);
        sprintf(szBuf, "%02X", pbyData[i]);
        cOut += szBuf;
        if (dwFormat != 0)
        {
            if (dwFormat & FMT_SPACE)
                cOut += " ";
            if (dwFormat & FMT_16NEWLINE)
            {
                if ((((i + 1) % 16) == 0) && (i > 0))
                {
                    cOut << (BYTE) 0x0D;
                    cOut << (BYTE) 0x0A;
                }
            } else if (dwFormat & FMT_32NEWLINE)
            {
                if ((((i + 1) % 32) == 0) && (i > 0))
                {
                    cOut << (BYTE) 0x0D;
                    cOut << (BYTE) 0x0A;
                }
            }

        }
    }

    return 0;
}

void CDebugInfo::GetTime(CByteStream &cTime, PCSTR lpFileName, int iLine)
{
    cTime.Empty();
    char szBuf[512];
    time_t cTm;
    struct tm *loctime;
    memset(szBuf, 0, 512);
    bzero(&cTm, sizeof (time_t));

    cTm = time(NULL);
    loctime = localtime(&cTm);

    sprintf(szBuf, "%02i:%02i:%02i 0x%08X %s-%05i", loctime->tm_hour, loctime->tm_min, loctime->tm_sec, 
            (unsigned int)pthread_self(), lpFileName, iLine);

    cTime = szBuf;
}
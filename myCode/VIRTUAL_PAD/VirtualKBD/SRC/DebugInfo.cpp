#include "DebugInfo.h"
#include "errorcode.h"

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

    if(byDebugType != 0)
    {
        if(pFun != NULL)
            pFunCB = pFun;

    }
    m_byDebugType = byDebugType;

    return 0;
}

WORD CDebugInfo::DebugCBRegister(WORD(*pFun)(WORD wCBType, WPARAM wParam, LPARAM lParam))
{
    if(pFun == NULL)
        return ERROR_INVALID_PARAM;

    pFunCB = pFun;

    return 0;
}

void CDebugInfo::DebugEntry(PCSTR lpFileName, int iLine, PCSTR lpStr)
{
    if(m_byDebug == 0)
        return;

    DebugInfo(lpFileName, iLine, DEBUGINFO_NORMAL, "%s-Entry", lpStr);
}

void CDebugInfo::DebugInfo(PCSTR pSourceFileName, int iLineNo, DWORD dwLevel, PCSTR pFormat, ...)
{
    if(m_byDebug == 0)
        return;

    CByteStream cData;
    GetTime(cData, pSourceFileName, iLineNo);


    int nLen = 0;
    va_list argList;
    va_start(argList, pFormat);

#ifdef CTOS_API    
    nLen = vsnprintf(NULL, 0, pFormat, argList) + 1;
#endif

#ifdef _WINDOWS
    len = _vscprintf(pFormat, argList) + 1;
#endif

    char *pszStr = (char*)malloc(nLen * sizeof(char));
    memset(pszStr, 0, nLen * sizeof(char));
    vsprintf(pszStr, pFormat, argList);

    va_end(argList);

    cData += ":";
    cData += pszStr;
    cData += "\r\n";

    free(pszStr);

    const char *pszOut = cData.PushZero();

    if((m_byDebugType == 0) || (pFunCB==NULL))
        printf(pszOut);
    else
    {
        if(dwLevel != m_dwDebugLevel)
            pFunCB(DEBUG_MSG, (WPARAM)pszOut, dwLevel);
        else
            pFunCB(DEBUG_MSG, (WPARAM)pszOut, m_dwDebugLevel);
    }
}

WORD CDebugInfo::DebugRetCode(PCSTR lpFileName, int iLine, PCSTR lpStr, WORD wRet)
{
    if(m_byDebug == 0)
        return wRet;

    DebugInfo(lpFileName, iLine, DEBUGINFO_NORMAL, "%s-RetCode:0x%02X%02X", lpStr, wRet / 256, wRet % 256);

    return wRet;
}

WORD CDebugInfo::DebugExit(PCSTR lpFileName, int iLine, PCSTR lpStr, WORD wRet)
{
    if(m_byDebug == 0)
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
    if(m_byDebug == 0)
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

    if((m_byDebugType == 0) || (pFunCB==NULL))
        printf(pszOut);
    else
    {
        if(dwLevel != m_dwDebugLevel)
            pFunCB(DEBUG_MSG, (WPARAM)pszOut, dwLevel);
        else
            pFunCB(DEBUG_MSG, (WPARAM)pszOut, m_dwDebugLevel);
    }
}

DWORD CDebugInfo::Hex2ASC(CByteStream *pcSrc, CByteStream &cOut, WORD dwFormat)
{

    if(pcSrc == NULL)
        return ERROR_INVALID_PARAM;

    PBYTE pbyData = pcSrc->GetBuffer();
    int nSize = pcSrc->GetLength();
    char szBuf[4];
    cOut.Empty();

    for(int i = 0; i < nSize; i++)
    {
        memset(szBuf, 0, 4);
        sprintf(szBuf, "%02X", pbyData[i]);
        cOut += szBuf;
        if(dwFormat != 0)
        {
            if(dwFormat & FMT_SPACE)
                cOut += " ";
            if(dwFormat & FMT_16NEWLINE)
            {
                if((((i + 1) % 16) == 0) && (i > 0))
                {
                    cOut << (BYTE)0x0D;
                    cOut << (BYTE)0x0A;
                }
            }
            else if(dwFormat & FMT_32NEWLINE)
            {
                if((((i + 1) % 32) == 0) && (i > 0))
                {
                    cOut << (BYTE)0x0D;
                    cOut << (BYTE)0x0A;
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
    memset(szBuf, 0, 512);

#ifdef _WINDOWS
    SYSTEMTIME cSystemTime;
    memset(&cSystemTime, 0, sizeof(SYSTEMTIME));
    GetLocalTime(&cSystemTime);
    sprintf(szBuf, "%i:%i:%i %s-%05i", cSystemTime.wHour, cSystemTime.wMinute, cSystemTime.wSecond, lpFileName, iLine);
#endif

#ifdef CTOS_API
    CTOS_RTC cSystemTime;
    memset(&cSystemTime, 0, sizeof(CTOS_RTC));
    CTOS_RTCGet(&cSystemTime);
    sprintf(szBuf, "%i:%i:%i %s-%05i", cSystemTime.bHour, cSystemTime.bMinute, cSystemTime.bSecond, lpFileName, iLine);
#endif

    cTime = szBuf;
}
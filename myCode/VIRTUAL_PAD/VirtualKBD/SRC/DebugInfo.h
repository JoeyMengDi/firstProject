#ifndef H_DEBUG 
#define H_DEBUG
#include "Common.h"
#include "ByteStream.h"

#define SRCFILE     __FILE__
#define CODELINE    __LINE__
#define DEBUG_MSG   0x0401

class CDebugInfo
{
public:
    CDebugInfo(void);
    ~CDebugInfo(void);

    WORD            DebugEnable(BYTE byDbg, BYTE byType, DWORD dwLevel, WORD (*pFun)(WORD wCBType, WPARAM wParam, LPARAM lParam));
    virtual void    DebugEntry(PCSTR lpFileName, int iLine, PCSTR lpStr);
    virtual void    DebugInfo(PCSTR pSourceFileName, int iLineNo, DWORD dwLevel, PCSTR pFormat, ...);
    virtual WORD    DebugExit(PCSTR lpFileName, int iLine, PCSTR lpStr, WORD wRet);
    virtual WORD    DebugRetCode(PCSTR lpFileName, int iLine, PCSTR lpStr, WORD wRet);
    virtual void    DebugByteStream(PCSTR lpFileName, int iLine, DWORD dwLevel, CByteStream *pCmd, PCSTR pszStr);
    virtual void    DebugByteStream(PCSTR lpFileName, int iLine, DWORD dwLevel, BYTE *pbyData, int nLen, PCSTR  pszStr);
    virtual WORD    DebugCBRegister(WORD (*pFun)(WORD wCBType, WPARAM wParam, LPARAM lParam));

private:        
    BYTE m_byDebug;
    BYTE m_byDebugType;
    DWORD m_dwDebugLevel;
    WORD (*pFunCB)(WORD wCBType, WPARAM wParam, LPARAM lParam);
    DWORD   Hex2ASC(CByteStream *pcSrc, CByteStream &cOut, WORD  dwFormat=0);
    void    GetTime(CByteStream &cTime, PCSTR lpFileName, int iLine);

};

#endif
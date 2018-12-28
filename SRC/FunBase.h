#ifndef H_FUNBASE
#define H_FUNBASE
#include "ByteStream.h"

class CFunBase
{
public:
    CFunBase(void);
    ~CFunBase(void);

    void        SetByteBit(BYTE& by, int idx, BOOL b);
    BOOL        GetByteBit(const BYTE by, int idx);
    void        Byte2Bit(BYTE byData, CByteStream &cRet);
    DWORD       FormatDataLength(CByteStream &cSrc, int nFormatLen, char ch, DWORD dwJustifiedType);
    DWORD       ASCIIToDec(BYTE* buffer, BYTE Len);
    DWORD       ASCIIToDec(char * pszStr);
    void        DecToASCII(DWORD dwValue, BYTE* buffer, BYTE Digit);
    void        DecToASCII(DWORD dwValue, CByteStream &cRet);
    BYTE        Toupper(BYTE ch);
    BYTE        PackByte(BYTE h, BYTE l);
    CByteStream Hex2Str(PBYTE pbyData, int nSize, WORD  dwFormat=0);
    DWORD       Hex2Str(CByteStream *pcSrc, CByteStream &cOut, WORD  dwFormat=0);
    void        Str2Hex(PCSTR pStr, CByteStream & cOut);

    int         Str2BCD(unsigned char *str, unsigned char *hex, unsigned int nLen);
    DWORD       Str2BCD(CByteStream *pSrc, CByteStream &cOutData);
    DWORD       Bcd2Str(CByteStream *pcSrc, CByteStream &cOut);

    void        Dec2Bcd(DWORD dwValue, CByteStream &cOut);
    DWORD       Bcd2Dec(CByteStream *pcSrc);
};

#endif
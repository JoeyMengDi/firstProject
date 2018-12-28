
/*
 * Copyright (c) Castles
 * All rights reserved.
 *
 * File Name: Md5.h
 * version: 1.0
 * author: Alan
 *  Date: 2017.09.06
 */

#ifndef _H_INC_MD5_H_H_
#define _H_INC_MD5_H_H_

#include "ByteStream.h"

class CMd5
{
public:
    static CByteStream GetMD5(const BYTE* pBuf, const UINT &nLength);
    static CByteStream Encrypt(const CByteStream &cSrcByteStream);

protected:
    //constructor/destructor
    CMd5();

    virtual ~CMd5() { };

    //RSA MD5 implementation
    void Transform(BYTE Block[64]);
    void Update(BYTE* Input, ULONG nInputLen);
    CByteStream Final();
    inline DWORD RotateLeft(DWORD x, int n);
    inline void FF(DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T);
    inline void GG(DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T);
    inline void HH(DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T);
    inline void II(DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T);

    //utility functions
    void DWordToByte(BYTE* Output, DWORD* Input, UINT nLength);
    void ByteToDWord(DWORD* Output, BYTE* Input, UINT nLength);

private:
    BYTE m_lpszBuffer[64]; //input buffer
    ULONG m_nCount[2]; //number of bits, modulo 2^64 (lsb first)
    ULONG m_lMD5[4]; //MD5 checksum
};

#endif // !defined(AFX_MD5CHECKSUM_H__2BC7928E_4C15_11D3_B2EE_A4A60E20D2C3__INCLUDED_)









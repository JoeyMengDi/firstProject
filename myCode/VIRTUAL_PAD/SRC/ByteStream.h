//////////////////////////////////////////////////////
// Copyright (c) 2007,
// All rights reserved.
//
// File Name:ByteStream.h
// version:1.0
// author:Sword
// Date:2007.11.16
//
//////////////////////////////////////////////////////

// ByteStream.h: interface for the CByteStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BYTESTREAM_H__7B0E6B8B_36D7_42D0_AFA2_F6C5E43536B2__INCLUDED_)
#define AFX_BYTESTREAM_H__7B0E6B8B_36D7_42D0_AFA2_F6C5E43536B2__INCLUDED_

#define TEMP_FILE    "Arg42D0_AFA2_F6C5E435.TXT"
#include "Common.h"

class CByteStream
{
public:

    CByteStream()
    {
        m_pData = NULL;
        m_nSize = 0;
        m_nMaxSize = 0;
    }

    CByteStream(PCSTR lpsz)
    {
        m_pData = NULL;
        m_nSize = 0;
        m_nMaxSize = 0;

        int nSrcLen = (lpsz != NULL ? strlen(lpsz) : 0);
        if (nSrcLen != 0) 
        {
            Empty();
            Write(lpsz, nSrcLen);
        }
    }

    CByteStream(const CByteStream &ByteStream)
    {
        m_pData = NULL;
        m_nSize = 0;
        m_nMaxSize = 0;

        Write(ByteStream.GetBuffer(), ByteStream.GetLength());
    }

    virtual ~CByteStream()
    {
        Empty();
    }

    void Write(const void* lpBuf, UINT nLen)
    {
        if (nLen <= 0)
            return;

        int nIndex = 0;
        if (m_nSize > 0)
            nIndex = m_nSize;

        SetSize(m_nSize + nLen);
        memcpy(&m_pData[nIndex], lpBuf, nLen);
    }

    int Compare(PBYTE pData, int nLen)
    {
        return memcmp(pData, m_pData, nLen);
    }

    int Compare(PSTR pStr)
    {
        return memcmp(pStr, m_pData, strlen(pStr));
    }

    int Compare(CByteStream *pData)
    {
        if (m_nSize != pData->GetLength())
            return 1;

        return Compare(pData->GetBuffer(), m_nSize);
    }

    void Empty()
    {
        SetSize(0);
    }

    BOOL IsEmpty()
    {
        if (m_nSize > 0)
            return FALSE;
        else
            return TRUE;
    }

    int GetLength() const
    {
        return m_nSize;
    }

    BYTE* GetBuffer(int nOffSet=0) const
    {
        if(nOffSet>m_nSize)
            return NULL;
        
        if(nOffSet == 0)
            return m_pData;
        else
            return &m_pData[nOffSet];
    }

    void CopyToStr(PSTR pszBuf, int nBufLen)
    {
        memset(pszBuf, 0, nBufLen);
        if(nBufLen<=m_nSize)
            memcpy(pszBuf, m_pData, nBufLen-1);
        else
            memcpy(pszBuf, m_pData, m_nSize);
    }

    PCSTR PushZero()
    {
        BYTE byTemp[4] = {0};
        byTemp[0] = 0x00;

        Write(byTemp, 1);

        return (PCSTR)this->m_pData;
    }
    void PopTailByte(int nByte=1)
    {
        if (m_nSize < nByte)
            return ;

        SetSize(m_nSize - nByte);
    }

    // insertion operations

    CByteStream& operator<<(BYTE by)
    {
        BYTE byTemp[4] = {0};
        byTemp[0] = by;

        Write(byTemp, 1);

        return *this;
    }

    CByteStream& operator>>(BYTE * pby)
    {
        if (m_nSize < 1)
            return *this;


        memcpy(pby, &m_pData[m_nSize - 1], 1);
        SetSize(m_nSize - 1);

        return *this;
    }

    CByteStream& operator<<(char ch)
    {
        BYTE byTemp[4] = {0};
        byTemp[0] = ch;

        Write(byTemp, 1);

        return *this;
    }

    CByteStream& operator>>(char * pch)
    {
        if (m_nSize < 1)
            return *this;


        memcpy(pch, &m_pData[m_nSize - 1], 1);
        SetSize(m_nSize - 1);

        return *this;
    }

    CByteStream& operator<<(PCSTR psz)
    {
        Write(psz, strlen(psz));

        return *this;
    }

    CByteStream& operator<<(const CByteStream &ByteStream)
    {
        Write(ByteStream.GetBuffer(), ByteStream.GetLength());

        return *this;
    }

    CByteStream& operator<<(DWORD dw)
    {
        int nIndex = 0;
        if (m_nSize > 0)
            nIndex = m_nSize;

        SetSize(m_nSize + sizeof (dw));

        memcpy(&m_pData[nIndex], &dw, sizeof (DWORD));

        return *this;
    }

    CByteStream& operator>>(PDWORD pDw)
    {
        int nLen = sizeof (DWORD);
        if (m_nSize < nLen)
            return *this;

        memcpy(pDw, &m_pData[m_nSize - nLen], nLen);
        SetSize(m_nSize - nLen);

        return *this;
    }

    CByteStream& operator<<(WORD w)
    {
        int nIndex = 0;
        if (m_nSize > 0)
            nIndex = m_nSize;

        SetSize(m_nSize + sizeof (WORD));

        memcpy(&m_pData[nIndex], &w, sizeof (WORD));

        return *this;

    }

    CByteStream& operator>>(PWORD pW)
    {
        int nLen = sizeof (WORD);
        if (m_nSize < nLen)
            return *this;


        memcpy(pW, &m_pData[m_nSize - nLen], nLen);
        SetSize(m_nSize - nLen);

        return *this;
    }

    CByteStream& operator=(const CByteStream &ByteStream)
    {
        Empty();
        Write(ByteStream.GetBuffer(), ByteStream.GetLength());

        return *this;
    }

    CByteStream& operator=(PCSTR psz)
    {
        Empty();
        Write(psz, strlen(psz));

        return *this;
    }

    CByteStream& operator+=(const CByteStream &ByteStream)
    {
        Write(ByteStream.GetBuffer(), ByteStream.GetLength());

        return *this;
    }

    CByteStream& TrimLeft(char ch)
    {
        BYTE *pbyTemp = m_pData;
        while(*pbyTemp == ch)
        {
            pbyTemp++;
        }

        int iFirst = int(pbyTemp - m_pData);
        memmove(m_pData, pbyTemp, m_nSize - iFirst);
        SetSize(m_nSize - iFirst);

        return *this;
    }

    CByteStream& TrimRight(char ch)
    {
        PBYTE pbyTemp = m_pData+m_nSize-1;

        while(*pbyTemp == ch)
        {
            pbyTemp--;
        }

        int nLen = int(pbyTemp - m_pData)+1;
        SetSize(nLen);

        return( *this );
    }

    
    CByteStream& Format(PCSTR pFormat, ... )
    {
        char szBuf[1028] = {0};

        SetSize(0);
        va_list argList;
        va_start(argList, pFormat);
        vsprintf(szBuf, pFormat, argList);
        va_end(argList);

        int nLen = strlen(szBuf);
        if(nLen>1024)
            nLen = 1024;        
        Write(szBuf, nLen);

        return( *this );

        //        unlink(TEMP_FILE);
        //         FILE *fp;
        //         fp = fopen(TEMP_FILE,"w");
        //         va_list argList;
        //         va_start(argList, pszFormat);
        //          int nLen = vfprintf(fp, pszFormat, argList);
        //         va_end(arg_ptr);
        //            fclose(fp);
        //         remove(TEMP_FILE);

     }


    //    void operator<<(LONG l);
    //    void operator<<(DWORD dw);
    //    void operator<<(float f);
    //    void operator<<(double d);
    //
    //    void operator<<(int i);
    //    void operator<<(short w);
    //    void operator<<(unsigned u);

    //    // extraction operations
    //    CByteStream& operator>>(BYTE& by);
    //    CByteStream& operator>>(WORD& w);
    //    CByteStream& operator>>(DWORD& dw);
    //    CByteStream& operator>>(LONG& l);
    //    CByteStream& operator>>(float& f);
    //    CByteStream& operator>>(double& d);
    //
    //    CByteStream& operator>>(int& i);
    //    CByteStream& operator>>(short& w);
    //    CByteStream& operator>>(char& ch);
    //    CByteStream& operator>>(unsigned& u);

protected:
    BYTE* m_pData; // the actual array of data
    int m_nSize; // # of elements (upperBound - 1)
    int m_nMaxSize;

    void SetSize(int nNewSize)
    {
        if (nNewSize < 0)
            return;

        int m_nGrowBy = 0;

        if (nNewSize == 0) 
        {
            // shrink to nothing
            if (m_pData != NULL)
                delete[] (BYTE*) m_pData;
            m_pData = NULL;
            m_nSize = m_nMaxSize = 0;
        }
        else if (m_pData == NULL) 
        {
            // create one with exact size
            m_pData = (BYTE*) new BYTE[nNewSize * sizeof (BYTE)];
            memset(m_pData, 0, nNewSize * sizeof (BYTE)); // zero fill
            m_nSize = m_nMaxSize = nNewSize;
        }
        else if (nNewSize <= m_nMaxSize) 
        {
            // it fits
            if (nNewSize > m_nSize) 
            {
                // initialize the new elements
                memset(&m_pData[m_nSize], 0, (m_nMaxSize - m_nSize) * sizeof (BYTE));
            }
            else
                memset(&m_pData[nNewSize], 0, (m_nMaxSize - nNewSize) * sizeof (BYTE));

            m_nSize = nNewSize;
        }
        else 
        {
            // otherwise, grow array
            int nGrowBy = m_nGrowBy;
            if (nGrowBy == 0) 
            {
                // heuristically determine growth when nGrowBy == 0
                //  (this avoids heap fragmentation in many situations)
                nGrowBy = min(1024, max(4, m_nSize / 8));
            }
            int nNewMax;
            if (nNewSize < m_nMaxSize + nGrowBy)
                nNewMax = m_nMaxSize + nGrowBy; // granularity
            else
                nNewMax = nNewSize; // no slush

            BYTE* pNewData = (BYTE*) new BYTE[nNewMax * sizeof (BYTE)];

            // copy new data from old
            // WCE_FCTN(memcpy)(pNewData, m_pData, m_nSize * sizeof(BYTE));
            memcpy(pNewData, m_pData, m_nSize * sizeof (BYTE));
            // construct remaining elements
            memset(&pNewData[m_nSize], 0, (nNewSize - m_nSize) * sizeof (BYTE));
            // get rid of old stuff (note: no destructors called)
            delete[] (BYTE*) m_pData;
            m_pData = pNewData;
            m_nSize = nNewSize;
            m_nMaxSize = nNewMax;
        }
    }
};

#endif // !defined(AFX_BYTESTREAM_H__7B0E6B8B_36D7_42D0_AFA2_F6C5E43536B2__INCLUDED_)

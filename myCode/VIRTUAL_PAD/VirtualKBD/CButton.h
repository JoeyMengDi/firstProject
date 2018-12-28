/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CButton.h
 * Author: Aaron.Chen
 *
 * Created on 2018年12月4日, 下午3:26
 */

#ifndef CBUTTON_H
#define CBUTTON_H

#include "FunctionButtonPic.h"
#include "SRC/DebugInfo.h"
#include "SRC/StdafxHead.h"
#include "CButton.h"
#include <typedef.h>

#define RGB(r,g,b)         ((DWORD)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))

class CButton{
    
public:
    CButton(void);
    ~CButton(void);
    
    USHORT Init(USHORT usX, USHORT usY, USHORT usXSize, USHORT usYSize);
    USHORT SetFontSize(USHORT usFont);
    
    USHORT SetButtonCaption(CByteStream& cBtCaption, USHORT usDataLen);
    USHORT SendButtonCaption(CByteStream& cBtCaption, USHORT *pusDataLen);
    
    USHORT ChangeForeGndColor(ULONG ulColor);
    
    USHORT ShowButton(void);
    USHORT HideButton(void);
    
    USHORT ClickButton(void);
    USHORT ChangeClickBtColor(ULONG ulColor);
    
private:
    BOOL   m_bIsInit;
    USHORT m_usDataLen;
    USHORT m_usBtXCoord;
    USHORT m_usBtYCoord;
    USHORT m_usBtXSize;
    USHORT m_usBtYSize;
    USHORT m_usFontSize;
    ULONG  m_ulForeGndColor;
    ULONG  m_ulClickColor;
    CByteStream m_cText;

};


#endif /* CBUTTON_H */


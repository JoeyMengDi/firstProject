
/* 
 * Copyright (c) Castles Technology Co., Ltd. 
 * 
 * File:   KeyBoard.h
 * Author: Alan.Ren
 *
 * Created: 2017/07/26
 */

#include "stdafxhead.h"

class CKeyBoard
{
public:
    CKeyBoard();
    virtual ~CKeyBoard();
    
public:
    WORD KBDHit(OUT BYTE &byKey);
    
    WORD KBDGet(OUT BYTE &byKey);
    
    void Lock();
    
    void Unlock();
    
private:
    BOOL m_bKBDSingleUse;
};

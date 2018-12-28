/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyKBD.h
 * Author: Joey Meng
 *
 * Created on 2018年12月5日, 下午4:45
 */

#ifndef MYKBD_H
#define MYKBD_H

#include "../SRC/DebugInfo.h"
#include "CButton.h"

#define TYPE_NUM        0
#define TYPE_LETTER     1
#define TYPE_CAPLETTER  2
#define TYPE_SPECIL     3

class MyKBD {
public:
    MyKBD();
    MyKBD(const MyKBD& mykbd);
    virtual ~MyKBD();
    WORD HandleTouch(USHORT& usX, USHORT& usY);
    int TouchInit();
    BOOL TouchGetPosition(USHORT& usX, USHORT& usY);
    void ShowNumber();
    void ShowLetter();
    void ShowCapLetter();
    void ShowSpecil();
    void DetectKey();
    CByteStream GetKeyValue(CByteStream& value, USHORT usN);
    USHORT PartitionArea(USHORT& usX, USHORT& usY);
    void ChangeColor(USHORT usN);
    //
private:
    INT nTouchHandle;
    static BYTE byKeyboardType;
    static CButton curButton;
    CButton cbtNum[15];

};

#endif /* MYKBD_H */


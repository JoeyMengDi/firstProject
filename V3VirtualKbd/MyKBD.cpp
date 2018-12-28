/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyKBD.cpp
 * Author: Joey Meng
 * 
 * Created on 2018年12月5日, 下午4:45
 */

#include "MyKBD.h"



BYTE MyKBD::byKeyboardType = TYPE_NUM;
CButton MyKBD::curButton;

MyKBD::MyKBD() {


}


//MyKBD::MyKBD(const MyKBD& orig) {
//}

MyKBD::~MyKBD() {
}

WORD MyKBD::HandleTouch(USHORT& usX, USHORT& usY) {
    WORD bRet = TouchInit();
    if (bRet < 0) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "TouchInit() fail!  wRet : %d\n", bRet);
        return -1;
    } else {
        //DEBUG_INFO(DEBUGINFO_NORMAL, "TouchInit() success  wRet : %d\n", bRet);
    }

    int n = 0;
    while (1) {
        n++;
        bRet = TouchGetPosition(usX, usY);
        //DEBUG_INFO(DEBUGINFO_NORMAL, "x is: %ld  y is: %ld", usX, usY);
        usleep(100);
        if (!bRet)//Not detected
        {
            if (n >= 100) {
                break;
            } else {
                continue;
            }
        } else//detected
        {
            if ((usX != 0) && (usY != 0))
                break;
        }
    }

    if (n >= 100) {
        //close
        close(nTouchHandle);
        return -1;
    } else {
        DEBUG_INFO(DEBUGINFO_NORMAL, "----------------------------");
        DEBUG_INFO(DEBUGINFO_NORMAL, "x is: %ld  y is: %ld", usX, usY);
        DEBUG_INFO(DEBUGINFO_NORMAL, "----------------------------");
    }
    //close
    close(nTouchHandle);
    return 0;
}

int MyKBD::TouchInit() {
    nTouchHandle = open("/dev/input/event0", O_RDONLY | O_NONBLOCK);
    if (nTouchHandle < 0) {
        return -1;
    }
    return 0;
}

BOOL MyKBD::TouchGetPosition(USHORT& usX, USHORT& usY) {
    struct input_event evtBuf[5];
    int nReadEvtRet;
    int nId = 0;
    BOOL bRet = FALSE;

    nReadEvtRet = read(nTouchHandle, evtBuf, sizeof (evtBuf));
    if ((nReadEvtRet == -1) || nReadEvtRet < (int) sizeof (evtBuf)) {
        goto _func_End;
    }

    for (nId = 0; nId < 5; ++nId) {
        if (EV_ABS == evtBuf[nId].type) {
            if (evtBuf[nId].code == 0) // code 0 is equal to X-axis's coordinate
            {
                usX = evtBuf[nId].value;
            } else if (evtBuf[nId].code == 1) {
                usY = evtBuf[nId].value; //code 1 is equal to Y-axis's coordinate
            }
        }

        if (EV_SYN == evtBuf[nId].type) {
            bRet = TRUE;
            break;
        }
    }

_func_End:
    return bRet;
}

void MyKBD::ShowNumber() {
    MyKBD::byKeyboardType = TYPE_NUM;
    CByteStream cbyNum[12] = {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "abc", "0", "."
    };
    USHORT usN = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            cbtNum[usN].Init(j * 80, 280 + i * 50, 80, 50);
            cbtNum[usN].ButtonCaption(cbyNum[usN], cbyNum[usN].GetLength());
            usN++;
        }
    }
    for (int i = 0; i < 12; i++) {
        cbtNum[i].ShowButton();
    }
}

void MyKBD::ShowLetter() {
    MyKBD::byKeyboardType = TYPE_LETTER;
}

void MyKBD::ShowCapLetter() {
    MyKBD::byKeyboardType = TYPE_CAPLETTER;
}

void MyKBD::ShowSpecil() {
    MyKBD::byKeyboardType = TYPE_SPECIL;
}

void MyKBD::DetectKey() {
    USHORT usX = 0, usY = 0;
    while (1) {
        usX = 0;
        usY = 0;
        if (HandleTouch(usX, usY) == 0) {

            if (usX > 280 && usY > 380) {
                DEBUG_INFO(DEBUGINFO_NORMAL, "_____________________TouchFun END________________________\n");
                break;
            } else {
                USHORT usRet = PartitionArea(usX, usY);
                if (usRet >= 0) {
                    CByteStream byValue;
                    GetKeyValue(byValue, usRet);
                    DEBUG_INFO(DEBUGINFO_NORMAL, "keyValue :%s \n", byValue.GetBuffer(0));
                }
            }
        }
    }
}

USHORT MyKBD::PartitionArea(USHORT& usX, USHORT& usY) {
    if (usY < 280) {
        return -1;
    }
    int x = usX / 80;
    int y = (usY - 280) / 50;
    if (x == 3) {
        return (y >= 2 ? 2 : y) + 12;
    } else {
        return y * 3 + x;
    }
}

CByteStream MyKBD::GetKeyValue(CByteStream& value, USHORT usN) {
    CByteStream cbyNum[15] = {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "abc", "0", ".", "X", "x", "OK"
    };

    if (byKeyboardType == TYPE_NUM) {
        //value << cbyNum[usN];
        MyKBD::curButton = cbtNum[usN];
        value.Write(cbyNum[usN].GetBuffer(0), cbyNum[usN].GetLength());
        return value;
    }
}


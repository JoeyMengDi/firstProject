/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CVKBD.h
 * Author: Administrator
 *
 * Created on 2018年12月11日, 上午9:34
 */

#ifndef CVKBD_H
#define CVKBD_H

#include "CButton.h"
#include "Definition.h"
#include "libVKBD.h"
#include <pthread.h>
#include <signal.h>

void* VKBDThreadFun(void* pVoid);

typedef enum enum_VKBD_MODE
{
    VKBD_MODE_MIN = 0,

    VKBD_MODE_NUMBER,
    VKBD_MODE_LETTER,
    VKBD_MODE_CAP_LETTER,
    VKBD_MODE_SPECIAL_CHARACTER,

    VKBD_MODE_MAX = 5
	
}VKBD_MODE; 

class CVKBD{
    
public:
    CVKBD();
    ~CVKBD();
    
    USHORT VKBDOpen(void);
    USHORT VKBDClose(void);
    USHORT VKBDChooseInterface(BYTE byDefaultMode);
    
    USHORT VKBDInitButton(void);
    USHORT VKBDSetButtonCaption(void);
    USHORT VKBDShowInterface(void);
    USHORT VKBDShowDisplayColumnLen(void);
    USHORT VKBDHideInterface(void);
    
    USHORT HandleInterface();
    USHORT HandleSwitchButton();
    USHORT HandleOneToNineButton();
    USHORT HandlePARENTZeroButton();
    USHORT HandlePARENTCAPButton();
    USHORT HandleCancelButton();
    USHORT HandleClearButton();
    USHORT HandleEnterButton();
    USHORT EnsureButtonCaption();
    
    void TouchClose(void);
    BOOL TouchInit(void);
    BOOL TouchGetPosition(long &lDownX, long &lDownY, long &lUpX, long &lUpY);
    BOOL IsThreadAlive(const pthread_t threadId);
    BYTE ScopeJudgment(long x, long y);
    WORD ClickScope(long* lDownX, long* lDownY, long* lUpX, long* lUpY);
    USHORT HandleTouch(long &lDownX, long &lDownY, long &lUpX,long &lUpY);

    void ClickCancelButton();
    void ClickClearButton();
    void ClickOKButton();
    
    USHORT VKBDGet(BYTE* pbyKey);
    USHORT VKBDHit(BYTE* pbyKey);
    USHORT VKBDGetKeyBuf(void);
    USHORT VKBDGetImportData(CByteStream& cImportData);
    USHORT VKBDBufFlush(void);
    
    WORD VKBDSetSound(BOOL bOnOff);
  
public:
    BOOL m_bBeepFlag;
    BOOL bTouchOK;
    BOOL m_bIsOpen;
    BOOL m_bIsShow;
    BOOL m_bIsShowButton;
    BOOL m_bIsClick;
    BOOL m_bIsShowDisplay;
    
    BYTE m_byNowScope;
    BYTE m_byLastScope;
    BYTE m_byKeyChooseOneValue;
    BYTE m_byKeyChooseTwoValue;
    BYTE m_byKeyChooseThreeValue;
    BYTE m_byKeyBuf;
    
    USHORT m_usJudgeDsiplayColumnLen;
    USHORT m_usDisplayColumnLen;
    ULONG m_ulTime;
    pthread_t m_VKBDThreadID;
    
    VKBD_MODE m_enMode;
    CByteStream m_cDisplayColumn;
    CByteStream m_cExport;
    
private:
    int m_TouchDevHandle;
    long m_lPressX;
    long m_lPressY;
    long m_lUpX;
    long m_lUpY;
    
    CButton m_cBtDisplayColumn;
    CButton m_cBtRow1Column1, m_cBtRow1Column2, m_cBtRow1Column3, m_cBtHide;
    CButton m_cBtRow2Column1, m_cBtRow2Column2, m_cBtRow2Column3, m_cBtCancel;
    CButton m_cBtRow3Column1, m_cBtRow3Column2, m_cBtRow3Column3, m_cBtClear;
    CButton m_cBtRow4Column1, m_cBtRow4Column2, m_cBtRow4Column3, m_cBtOK;
};



#endif /* CVKBD_H */


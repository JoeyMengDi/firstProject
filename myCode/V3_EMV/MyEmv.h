/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyEmv.h
 * Author: Joey Meng
 *
 * Created on 2018å¹?11??20??, ä¸???1:44
 */

#ifndef MYEMV_H
#define MYEMV_H

#include <ctosapi.h>
#include <emvaplib.h>

#include "deftype.h"
#include "MyCallBack.h"
#include "EMVCommon.h"
#include <emvaplib.h>


extern PAYMENT_DATA stPayData;

class MyEmv {
public:
    MyEmv();
    MyEmv(EMV_EVENT &stEEvt, const char *pszConfigFN);
    virtual ~MyEmv();
    USHORT InitEmv(void);
    USHORT StartEMV(void);
    USHORT SelectTxnApp(void);
    USHORT StopEMV(void);

    BOOL IsCardInserted(void);
    USHORT WriteOnlineKey(void);
private:
    EMV_EVENT emv_event;
    CHAR* pszConfigFileName;
};

#endif /* MYEMV_H */


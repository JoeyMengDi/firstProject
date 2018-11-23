/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyCallBack.h
 * Author: Administrator
 *
 * Created on 2018å¹?11??20??, ä¸???2:02
 */

#ifndef MYCALLBACK_H
#define MYCALLBACK_H

#include <ctosapi.h>
#include <emvaplib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "deftype.h"
#include "ByteStream.h"
#include "DbgMacro.h"
#include "collis_tlv/CollisTLV.h"
#include "collis_tlv/defs.h"
#include "EMVCommon.h"
#include "EMVBase.h"

class MyCallBack {
public:
    static void OnDisplayShow(IN char *pStrMsg);
    static void OnErrorMsg(IN char *pStrMsg);
    static void OnEMVConfigActive(INOUT BYTE* pActiveIndex);
    static USHORT OnTxnDataGet(OUT EMV_TXNDATA *pTxnData);
    static USHORT OnAppList(IN BYTE AppNum, IN char AppLabel[ ][d_LABEL_STR_SIZE + 1], OUT BYTE *pAppSelectedIndex);
    static USHORT OnAppSelectedConfirm(IN BOOL IsRequiredbyCard, IN BYTE *pLabel, IN BYTE bLabelLen);
    static BOOL OnTerminalDataGet(IN USHORT usTag, INOUT USHORT *pLen, OUT BYTE *pValue);
    static BOOL OnCAPKGet(IN BYTE *pRID, IN BYTE bKeyIndex, OUT BYTE *pModulus,
            OUT USHORT *pModulusLen, OUT BYTE *pExponent, OUT USHORT *pExponentLen);

    static void OnGetPINNotify(IN BYTE bPINType, IN USHORT bRemainingCounter,
            OUT BOOL* pIsInternalPINPad, OUT DEFAULT_GETPIN_FUNC_PARA *pGetPINFuncPara);

    static USHORT OnOnlinePINBlockGet(OUT ONLINE_PIN_DATA *pOnlinePINData);
    static USHORT OnOfflinePINBlockGet(void);
    static void OnOfflinePINVerifyResult(IN USHORT usResult);
    static void OnTxnOnline(IN ONLINE_PIN_DATA *pOnlinePINData, OUT EMV_ONLINE_RESPONSE_DATA* pOnlineResponseData);
    static void OnTxnIssuerScriptResult(IN BYTE* pScriptResult, IN USHORT pScriptResultLen);
    static void OnTxnResult(IN BYTE bResult, IN BOOL IsSignatureRequired);
    static void OnTotalAmountGet(IN BYTE *pPAN, IN BYTE bPANLen, OUT ULONG *pAmount);
    static void OnExceptionFileCheck(IN BYTE *pPAN, IN BYTE bPANLen, OUT BOOL *isException);
    static BOOL OnCAPKRevocationCheck(IN BYTE *pbRID, IN BYTE bCAPKIdx, IN BYTE *pbSerialNumuber);
    static void OnOutPutCardAPDU(IN BYTE *pTxAPDU, IN USHORT TxAPUDLen, IN BYTE *pRxAPDU, IN USHORT RxAPDULen);

};

#endif /* MYCALLBACK_H */


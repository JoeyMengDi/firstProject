/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyEmv.cpp
 * Author: Joey Meng
 * 
 * Created on 2018å¹?11??20??, ä¸???1:44
 */

#include "MyEmv.h"

MyEmv::MyEmv() {

    memset(&emv_event, 0x00, sizeof (EMV_EVENT));

    memset(&stPayData, 0x00, sizeof (PAYMENT_DATA));

    /* TxnCommon Parameter Initialization */
    memset(stPayData.stTxnCommonParam.byAID, 0x00, 16);
    memset(stPayData.stTxnCommonParam.byAppLabel, 0x00, 16);

    stPayData.stTxnCommonParam.byAIDLen = 0;
    stPayData.stTxnCommonParam.byAppLabelLen = 0;

    stPayData.stTxnCommonParam.usPinKeySet = EMV_PINKEY_SET;
    stPayData.stTxnCommonParam.usPinKeyIndex = EMV_PIN_INDEX;
    stPayData.stTxnCommonParam.byBlockType = EMV_PIN_INFO_BLOCK_TYPE;
    stPayData.stTxnCommonParam.byPINMaxLen = 12;
    stPayData.stTxnCommonParam.byPINMinLen = 4;
    stPayData.stTxnCommonParam.usTimeout = 30;
    stPayData.stTxnCommonParam.byAsteriskPosX = 4;
    stPayData.stTxnCommonParam.byAsteriskPosY = 5;
    stPayData.stTxnCommonParam.byPassPIN = 0;


    /* OnGetPINNotify Parameter Initialization */
    stPayData.stGetPinNotify_Param.usPINLineLeftX = 5;
    stPayData.stGetPinNotify_Param.usPINLineRightX = 20;
    stPayData.stGetPinNotify_Param.usPINLinePosY = 5;

    stPayData.stGetPinNotify_Param.byPINMaxLen = 12;
    stPayData.stGetPinNotify_Param.byPINMinLen = 4;
    stPayData.stGetPinNotify_Param.ulTimeout = 30;


    memset(stPayData.byScriptData, 0x00, 2048);

    /* OnOfflinePINBlockGet Parameter Initialization*/
    memset(stPayData.stOFLPinBlkGet_Param.byEncBlkData, 0x00, 32);
    stPayData.stOFLPinBlkGet_Param.byPINLen = 0;

    /* OnOnlinePINBlockGet Parameter Initialization*/
    memset(&(stPayData.stOLPinBlkGet_Param), 0x00, sizeof (ONOLPINBLKGET_PARAM));
    stPayData.stOLPinBlkGet_Param.usEnBlockLen = 8;
    memset(stPayData.stOLPinBlkGet_Param.byEnBlockBuf, 0x00, 16);
    stPayData.stOLPinBlkGet_Param.byTiemout = 30;
    stPayData.stOLPinBlkGet_Param.byAsteriskPosX = 4;
    stPayData.stOLPinBlkGet_Param.byAsteriskPosY = 5;
    pszConfigFileName = (char*) "emv_config.xml";

    emv_event.Version = 1;
    //    emv_event.OnDisplayShow = MyCallBack::OnDisplayShow;
    //    emv_event.OnDisplayShow = MyCallBack::OnDisplayShow;
    //    emv_event.OnErrorMsg = MyCallBack::OnErrorMsg;
    //    emv_event.OnEMVConfigActive = MyCallBack::OnEMVConfigActive;
    //    emv_event.OnHashVerify = NULL;
    emv_event.OnTxnDataGet = MyCallBack::OnTxnDataGet;
    emv_event.OnAppList = MyCallBack::OnAppList;
    emv_event.OnAppSelectedConfirm = MyCallBack::OnAppSelectedConfirm;
    //    emv_event.OnTerminalDataGet = MyCallBack::OnTerminalDataGet;
    //    emv_event.OnCAPKGet = MyCallBack::OnCAPKGet;
    emv_event.OnGetPINNotify = MyCallBack::OnGetPINNotify;
    //    emv_event.OnOnlinePINBlockGet = MyCallBack::OnOnlinePINBlockGet;
    //    emv_event.OnOfflinePINBlockGet = MyCallBack::OnOfflinePINBlockGet;
    //    emv_event.OnOfflinePINVerifyResult = MyCallBack::OnOfflinePINVerifyResult;
    emv_event.OnTxnOnline = MyCallBack::OnTxnOnline;
    //    emv_event.OnTxnIssuerScriptResult = MyCallBack::OnTxnIssuerScriptResult;
    emv_event.OnTxnResult = MyCallBack::OnTxnResult;
    //    emv_event.OnTotalAmountGet = MyCallBack::OnTotalAmountGet;
    //    emv_event.OnExceptionFileCheck = MyCallBack::OnExceptionFileCheck;
    //    emv_event.OnCAPKRevocationCheck = MyCallBack::OnCAPKRevocationCheck;
}

MyEmv::MyEmv(EMV_EVENT &stEEvt, const char *pszConfigFN) {
    emv_event = stEEvt;
    memcpy(pszConfigFileName, pszConfigFN, strlen(pszConfigFN));
}

MyEmv::~MyEmv() {
}

USHORT MyEmv::InitEmv() {

    DEBUG_ENTRY();
    USHORT usRet;
    usRet = EMV_Initialize(&emv_event, pszConfigFileName);
    //return usRet;
    return DEBUG_EXIT(usRet);
}

USHORT MyEmv::StartEMV(void) {
    DEBUG_ENTRY();

    USHORT usRet;

    EMV_SpecialEventRegister(d_EVENTID_OUTPUT_CARDAPDU, (EVENT_OUTPUTCARDAPDU*) MyCallBack::OnOutPutCardAPDU);
    usRet = WriteOnlineKey();
    if (usRet != 0x00)
        return DEBUG_RETCODE("WriteOnlineKey Failed", usRet);

    return DEBUG_EXIT(usRet);
}

USHORT MyEmv::SelectTxnApp(void) {
    DEBUG_ENTRY();

    USHORT usRet;
    CByteStream cbsBuf;
    BYTE byBuf[128];
    //CUtil cUtil;

    BYTE bySelectedAID[16], bySelectedAIDLen;
    BYTE bySelectedAppLabel[32], bySelectedAppLabelLen;


    BYTE byTagValue[128];
    USHORT usTagLen;

    memset(byBuf, 0x00, 128);
    usRet = EMV_TxnAppSelect(bySelectedAID, &bySelectedAIDLen, bySelectedAppLabel, &bySelectedAppLabelLen);
    if (usRet != d_EMVAPLIB_OK) {
        return DEBUG_RETCODE("EMV_TxnAppSelect Failed, ", usRet);
    }

    //memcpy(stPayData.stTxnCommonParam.byAID, bySelectedAID, bySelectedAIDLen);
    //stPayData.stTxnCommonParam.byAIDLen = bySelectedAIDLen;

    DEBUG_INFO(DEBUGINFO_NORMAL, "EMV_TxnAppSelect ret:%04X", usRet);

    // Get Selected AID
    //CFunBase cFun;
    CByteStream cOutData;
    cOutData.Empty();

    //cOutData = cFun.Hex2Str(bySelectedAID, bySelectedAIDLen);
    //DEBUG_INFO(DEBUGINFO_NORMAL, "AID: %s", cOutData.PushZero());
    DEBUG_BYTEBUF(DEBUGINFO_NORMAL, bySelectedAID, bySelectedAIDLen, "AID");
    cbsBuf.Empty();
    cbsBuf.Write(bySelectedAppLabel, bySelectedAppLabelLen);


    //memcpy(stPayData.stTxnCommonParam.byAppLabel, bySelectedAppLabel, bySelectedAppLabelLen);
    //stPayData.stTxnCommonParam.byAppLabelLen = bySelectedAppLabelLen;


    // Get PAN
    usTagLen = sizeof (byTagValue);
    EMV_DataGet(0x005A, &usTagLen, byTagValue);

    cOutData.Empty();
    //cOutData = cFun.Hex2Str(byTagValue, usTagLen);
    //DEBUG_INFO(DEBUGINFO_NORMAL, "PAN: %s", cOutData.PushZero());
    DEBUG_BYTEBUF(DEBUGINFO_NORMAL, byTagValue, usTagLen, "PAN");
    //memcpy(stPayData.stTxnCommonParam.byPAN, cOutData.GetBuffer(), cOutData.GetLength() - 1);
    //stPayData.stTxnCommonParam.byPANLen = cOutData.GetLength() - 1;

    // Start Perfrom Txn
    usRet = EMV_TxnPerform();
    if (usRet != d_EMVAPLIB_OK) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "EMV_TxnPerform Err: %04X", usRet);

        CTOS_LCDTPrintXY(1, 3, (PBYTE) "TxnPerform Failed");

        return DEBUG_RETCODE("EMV_TxnPerform Failed ", usRet);
    }

    //return 0;
    return DEBUG_EXIT(0x0000);
}

USHORT MyEmv::StopEMV(void) {
    DEBUG_ENTRY();

    USHORT usRet;

    usRet = CTOS_SCPowerOff(d_SC_USER);

    //return usRet;
    return DEBUG_EXIT(usRet);
}

BOOL MyEmv::IsCardInserted(void) {
    //BOOL bCardInserted;
    BYTE byState;

    CTOS_SCStatus(d_SC_USER, &byState);

    if (byState && d_MK_SC_PRESENT)
        return TRUE;
    return FALSE;
}

USHORT MyEmv::WriteOnlineKey(void) {
    DEBUG_ENTRY();
    USHORT usRet;
    CTOS_KMS2KEYWRITE_PARA stKMS2KeyWritePara;
    CByteStream cbsObj;

    memset(&stKMS2KeyWritePara, 0x00, sizeof (CTOS_KMS2KEYWRITE_PARA));
    stKMS2KeyWritePara.Info.KeySet = 0x2000; // Online KeySet
    stKMS2KeyWritePara.Info.KeyIndex = 0x0000; // Online KeyIndex
    stKMS2KeyWritePara.Info.KeyVersion = 0x01;
    stKMS2KeyWritePara.Info.KeyType = KMS2_KEYTYPE_3DES;
    stKMS2KeyWritePara.Info.KeyAttribute = KMS2_KEYATTRIBUTE_PIN;

    stKMS2KeyWritePara.Protection.Mode = KMS2_KEYPROTECTIONMODE_PLAINTEXT;

    stKMS2KeyWritePara.Value.pKeyData = (BYTE*) "\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11";
    stKMS2KeyWritePara.Value.KeyLength = 16;

    usRet = CTOS_KMS2KeyWrite(&stKMS2KeyWritePara);
    if (usRet != d_OK) {
        return DEBUG_RETCODE("Online Key Write Failed", usRet);
    }

    stKMS2KeyWritePara.Info.KeyIndex = 0x0001; // Offline KeyIndex
    stKMS2KeyWritePara.Info.KeyAttribute = KMS2_KEYATTRIBUTE_ENCRYPT + KMS2_KEYATTRIBUTE_DECRYPT;

    usRet = CTOS_KMS2KeyWrite(&stKMS2KeyWritePara);
    if (usRet != d_OK)
        return DEBUG_RETCODE("Write Key Failed", usRet);

    return DEBUG_EXIT(usRet);
}

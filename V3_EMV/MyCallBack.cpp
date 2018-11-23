/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyCallBack.cpp
 * Author: Joey Meng
 * 
 * Created on 2018å¹?11??20??, ä¸???2:02
 */

#include "MyCallBack.h"
#include "MyWiFi.h"


extern PAYMENT_DATA stPayData;

void MyCallBack::OnDisplayShow(IN char *pStrMsg) {
    CTOS_LCDTClearDisplay();
    CTOS_LCDTPrintXY(1, 2, (BYTE*) pStrMsg);
}

void MyCallBack::OnErrorMsg(IN char *pStrMsg) {
    CTOS_LCDTClearDisplay();
    CTOS_LCDTPrintXY(1, 2, (BYTE*) pStrMsg);
}

void MyCallBack::OnEMVConfigActive(INOUT BYTE* pActiveIndex) {
    pActiveIndex = 0;
    //If not providing thisfunction, 
    //the active configuration is according to the configuration file.
}

USHORT MyCallBack::OnTxnDataGet(OUT EMV_TXNDATA *pTxnData) {

    DEBUG_ENTRY();

    BYTE byDate[6];
    BYTE byTime[6];
    CTOS_RTC stRTC;

    //CUIDisplay cUI;
    CByteStream cOutData;
    // CFunBase cFun;
    cOutData.Empty();

    CTOS_LCDTClearDisplay();
    CTOS_LCDTPrintXY(1, 1, (PBYTE) "Pls Select TXN Type:");
    CTOS_LCDTPrintXY(1, 2, (PBYTE) "1 - Purchase ");
    CTOS_LCDTPrintXY(1, 3, (PBYTE) "2 - Cash ");
    CTOS_LCDTPrintXY(1, 4, (PBYTE) "3 - Cash Back ");
    CTOS_LCDTPrintXY(1, 5, (PBYTE) "4 - Refund ");

    BYTE byKey = 0;
    BYTE byTxnType;
    CTOS_KBDGet(&byKey);

    switch (byKey) {
        case d_KBD_1:
            byTxnType = 0x00;

            break;

        case d_KBD_2:
            byTxnType = 0x01;

            break;

        case d_KBD_3:
            byTxnType = 0x09;

            break;

        case d_KBD_4:
            byTxnType = 0x20;

            break;

        default:
            byTxnType = 0x00;
    }

    stPayData.stTxnDataGetParam.byTxnType = byTxnType;

    CTOS_LCDTClearDisplay();

    WORD wRet = 0;
    unsigned long long ullAmount = 0;
    unsigned long long ullTip = 0;

    //CUtil cUtil;

    BYTE baTipOption[4][20] = {"1 >>10% Tips", "2 >>15% Tips", "3 >>20% Tips", "4 >>Others"};
    BYTE baPctNum[4] = {10, 15, 20, 0};

    //wRet = cUtil.GetTotalAmount(&ullAmount, &ullTip, (PBYTE) "Pls Input Amount:", 2, 4, baTipOption, baPctNum);
    //    if (0x0000 != wRet) {
    //        return DEBUG_RETCODE("Get Total Amount error", wRet);
    //    }

    DEBUG_INFO(DEBUGINFO_NORMAL, "===============================================");
    stPayData.stTxnDataGetParam.llAmt = ullAmount;
    stPayData.stTxnDataGetParam.llTipAmt = ullTip;
    DEBUG_INFO(DEBUGINFO_NORMAL, "Amount: %lld", ullAmount);
    DEBUG_INFO(DEBUGINFO_NORMAL, "ullTip: %lld", ullTip);
    DEBUG_INFO(DEBUGINFO_NORMAL, "===============================================");

    BYTE byAmtBuf[12];
    memset(byAmtBuf, 0x00, 12);

    CByteStream cTemp;
    cTemp.Empty();

    USHORT usRet = 0;
    usRet = CTOS_RTCGet(&stRTC);
    if (usRet != d_OK)
        return usRet;

    //CFunBase cFun;
    CByteStream cDate, cTime;
    cDate.Empty();
    cTime.Empty();

    BYTE byDateBuf[8], byTimeBuf[8];
    memset(byDateBuf, 0x00, 8);
    memset(byTimeBuf, 0x00, 8);
    sprintf((char*) byDateBuf, "%02d%02d%02d", stRTC.bYear, stRTC.bMonth, stRTC.bDay);
    sprintf((char*) byTimeBuf, "%02d%02d%02d", stRTC.bHour, stRTC.bMinute, stRTC.bSecond);

    //    pTxnData->Version=0x01;
    //    //pTxnData->ulAmount=1;
    //    pTxnData->ulAmount=wAmt;
    //    pTxnData->bTxnType=byTxnType; // Cash - Transaction Type
    //    memcpy(pTxnData->TxnDate, cData.GetBuffer(), 3);
    //    memcpy(pTxnData->TxnTime, cData.GetBuffer() + 3, 3);
    //pTxnData->bPOSEntryMode=0x00;
    //pTxnData->isForceOnline=d_TRUE;

    EMV_TXNDATA_2 *pTxnData_v2;

    pTxnData_v2 = (EMV_TXNDATA_2 *) pTxnData;
    pTxnData_v2->Version = 0x02;
    pTxnData_v2->bTxnType = byTxnType;
    pTxnData_v2->ulAmount = ullAmount;
    pTxnData_v2->ulAmountOther = ullTip;
    memcpy(pTxnData_v2->TxnDate, byDateBuf, 6);
    memcpy(pTxnData_v2->TxnTime, byTimeBuf, 6);

    //pTxnData_v2->bPOSEntryMode = 0x00;
    pTxnData_v2->isForceOnline = d_FALSE;

    DEBUG_EXIT(0x00);
    return d_OK;
}

USHORT MyCallBack::OnAppList(IN BYTE AppNum, IN char AppLabel[ ][d_LABEL_STR_SIZE + 1], OUT BYTE *pAppSelectedIndex) {
    DEBUG_ENTRY();

    //BYTE byRet = 0;

    BYTE byHead[16 + 1];
    memset(byHead, 0x00, sizeof (byHead));
    sprintf((char*) byHead, "APP LIST");

    if (AppNum <= 0) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "AppNum:%d\n", AppNum);
        return DEBUG_RETCODE("App num fail, %04d", AppNum);
    }
    DEBUG_INFO(DEBUGINFO_NORMAL, "App List\n");
    DEBUG_INFO(DEBUGINFO_NORMAL, "AppNum:%d\n", AppNum);
    for (int i = 0; i < AppNum; i++) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "AppLabel:%s\n", AppLabel[i]);
    }
    *pAppSelectedIndex = 0;

    return d_OK;
}

USHORT MyCallBack::OnAppSelectedConfirm(IN BOOL IsRequiredbyCard, IN BYTE *pLabel, IN BYTE bLabelLen) {

    DEBUG_ENTRY();

    //    BYTE byKey;
    //    CByteStream cByteStream;
    //    cByteStream.Empty();

    if (!IsRequiredbyCard) {
        //        cByteStream = "Def App Selected:        ";
        //        CTOS_LCDTPrintXY(1, 3, cByteStream.GetBuffer());
        //        CTOS_LCDTPrintXY(1, 4, (BYTE*) "App Label:          ");
        //        CTOS_LCDTPrintXY(1, 5, pLabel);
        //
        //        CTOS_LCDTPrintXY(1, 8, (BYTE*) "           Enter->go");
        //        CTOS_KBDGet(&byKey);
        //        if (byKey == d_KBD_ENTER)
        //            return DEBUG_RETCODE("OnAppSelectedConfirm ", d_EMVAPLIB_OK);
        DEBUG_INFO(DEBUGINFO_NORMAL, "App Label:%s\n", (BYTE*) pLabel);
    }


    return DEBUG_EXIT(0x0000);
}

BOOL MyCallBack::OnTerminalDataGet(IN USHORT usTag, INOUT USHORT *pLen, OUT BYTE *pValue) {
    if (usTag == 0xDFB6)
        return FALSE;

    DEBUG_INFO(DEBUGINFO_NORMAL, "IN TAG: usTag - %04X", usTag);

    USHORT usRet = 0;
    USHORT usLen = 256;
    BYTE byBuf[256];
    memset(byBuf, 0x00, sizeof (byBuf));

    usRet = EMV_TerminalDataGet(stPayData.stTxnCommonParam.byAID, stPayData.stTxnCommonParam.byAIDLen, usTag, &usLen, byBuf);

    DEBUG_INFO(DEBUGINFO_NORMAL, "Tag Len: %d", usLen);
    DEBUG_INFO(DEBUGINFO_NORMAL, "Tag Value: %04X", byBuf);

    //    
    //    *pLen = usLen;
    //    memcpy(pValue, byBuf, usLen);



    if (usTag == 0x9F35) // Terminal Type
    {
        DEBUG_INFO(DEBUGINFO_NORMAL, " Get Terminal Type! ");
        *pValue = 0x22;
        *pLen = 1;
        return TRUE;
    } else if (usTag == 0x9F7A) // 
    {
        DEBUG_INFO(DEBUGINFO_NORMAL, " Get EC Terminal Support Indicator! ");
        *pValue = 0x01;
        *pLen = 1;
        return TRUE;
    } else if (usTag == 0x9F4E) // Merchant Name and Location
    {
        DEBUG_INFO(DEBUGINFO_NORMAL, " Get Business Name! ");
        pValue = (PBYTE) "HaErBin Bank       ";
        *pLen = 20;
        return TRUE;
    } else if (usTag == 0x9F02) // Amount Authorised 
    {
        DEBUG_INFO(DEBUGINFO_NORMAL, " Get Amount Data! ");
        pValue = (PBYTE) "HaErBin Bank ";
        *pLen = 6;
        return TRUE;
    }

    //    BYTE byTag[2];
    //    CHAR cTag[4];
    //    
    //    byTag[0] = (usTag >> 8);
    //    byTag[1] = (usTag & 0x00FF);
    //    
    //    CFunBase cFB;
    //    CByteStream cTagData;
    //    cTagData.Empty();
    //    
    //    cTagData = cFB.Hex2Str(byTag, 2);
    //    
    //    if(cTagData.GetLength() <= 2)
    //        return FALSE;

    //    DEBUG_INFO(DEBUGINFO_NORMAL,"OnTerminalDataGet - Exit");
    return FALSE;
}

BOOL MyCallBack::OnCAPKGet(IN BYTE *pRID, IN BYTE bKeyIndex, OUT BYTE *pModulus,
        OUT USHORT *pModulusLen, OUT BYTE *pExponent, OUT USHORT *pExponentLen) {
    return FALSE;
}

void MyCallBack::OnGetPINNotify(IN BYTE bPINType, IN USHORT bRemainingCounter,
        OUT BOOL* pIsInternalPINPad, OUT DEFAULT_GETPIN_FUNC_PARA *pGetPINFuncPara) {
    DEBUG_ENTRY();

    //    USHORT usLen = 16;
    //    BYTE byTC[16] = {0};
    //    EMV_DataGet(0x9F33, &usLen, byTC);
    //    DEBUG_BYTEBUF(DEBUGINFO_NORMAL,byTC, usLen, "Data of 0x9F33");



    CTOS_LCDTClearDisplay();
    CTOS_LCDTPrintXY(1, 3, (PBYTE) "Plz Input PIN:");

    //*pIsInternalPINPad = TRUE;
    *pIsInternalPINPad = FALSE;

    stPayData.stGetPinNotify_Param.byPINRequired = 1;

    memset(pGetPINFuncPara, 0x00, sizeof (DEFAULT_GETPIN_FUNC_PARA));
    pGetPINFuncPara->usLineLeft_X = stPayData.stGetPinNotify_Param.usPINLineLeftX;
    pGetPINFuncPara->usLineRight_X = stPayData.stGetPinNotify_Param.usPINLineRightX;
    pGetPINFuncPara->bPINDigitMaxLength = stPayData.stGetPinNotify_Param.byPINMaxLen;
    pGetPINFuncPara->bPINDigitMinLength = stPayData.stGetPinNotify_Param.byPINMinLen;
    pGetPINFuncPara->usLinePosition_Y = stPayData.stGetPinNotify_Param.usPINLinePosY;
    pGetPINFuncPara->ulTimeout = stPayData.stGetPinNotify_Param.ulTimeout;


    DEBUG_INFO(DEBUGINFO_NORMAL, "OnGetPINNotify - bPINType = %04X", bPINType);

    if (bPINType == d_NOTIFY_OFFLINE_PIN) {
        if (bRemainingCounter == 1) {
            CTOS_LCDTPrintXY(1, 4, (PBYTE) "Last time to enter PIN");
        }
        pGetPINFuncPara->IsReverseLine = FALSE;
        pGetPINFuncPara->IsRightToLeft = FALSE;

    } else if (bPINType == d_NOTIFY_ONLINE_PIN) {
        /*
        CTOS_KMS2PINGET_PARA para;
        BYTE byPINBlock[16];

        memset(&para, 0x00, sizeof(CTOS_KMS2PINGET_PARA));
        memset(byPINBlock, 0x00, sizeof(byPINBlock));
        para.Version=0x01;

        para.PIN_Info.BlockType=KMS2_PINBLOCKTYPE_ANSI_X9_8_ISO_0;
        para.PIN_Info.PINDigitMaxLength = stPayData.stGetPinNotify_Param.byPINMaxLen;
        para.PIN_Info.PINDigitMinLength = stPayData.stGetPinNotify_Param.byPINMinLen;

        para.Protection.CipherKeySet = stPayData.stTxnCommonParam.usPinKeySet;
        para.Protection.CipherKeyIndex = stPayData.stTxnCommonParam.usPinKeyIndex;
        para.Protection.CipherMethod = KMS2_PINCIPHERMETHOD_ECB;
        para.Protection.SK_Length = 0;

        para.AdditionalData.InLength = stPayData.stTxnCommonParam.byPANLen;
        para.AdditionalData.pInData = stPayData.stTxnCommonParam.byPAN;

        para.PINOutput.EncryptedBlockLength = 8;
        para.PINOutput.pEncryptedBlock = byPINBlock;

        para.Control.Timeout = stPayData.stGetPinNotify_Param.ulTimeout;
        para.Control.NULLPIN = FALSE;
        para.Control.piTestCancel = NULL;
        para.Control.AsteriskPositionX = 1;
        para.Control.AsteriskPositionY = 4;
        

        USHORT usRet=0;
        BYTE byKSNData[32];
        BYTE byKSNLen;

        usRet=CTOS_KMS2DUKPTGetKSN(stPayData.stTxnCommonParam.usPinKeySet, stPayData.stTxnCommonParam.usPinKeyIndex, byKSNData, &byKSNLen);
        if(usRet != d_OK)
        {
            DEBUG_INFO(DEBUGINFO_NORMAL,"Get KSN Failed");
            return;
        }
        else
        {
            DEBUG_INFO(DEBUGINFO_NORMAL,"Get KSN OK");
        }
         */
        pGetPINFuncPara->ONLINEPIN_PARA.CipherKeyIndex = stPayData.stTxnCommonParam.usPinKeyIndex;
        pGetPINFuncPara->ONLINEPIN_PARA.CipherKeySet = stPayData.stTxnCommonParam.usPinKeySet;
        pGetPINFuncPara->ONLINEPIN_PARA.bPANLen = stPayData.stTxnCommonParam.byPANLen;

        memcpy(pGetPINFuncPara->ONLINEPIN_PARA.baPAN, stPayData.stTxnCommonParam.byPAN, stPayData.stTxnCommonParam.byPANLen);

        DEBUG_EXIT(0x0000);
    }

}

USHORT MyCallBack::OnOnlinePINBlockGet(OUT ONLINE_PIN_DATA *pOnlinePINData) {
    DEBUG_ENTRY();

    CTOS_KMS2PINGET_PARA stPinGetPara;
    memset(&stPinGetPara, 0x00, sizeof (CTOS_KMS2PINGET_PARA));

    stPinGetPara.Version = 0x01;
    stPinGetPara.PIN_Info.BlockType = stPayData.stTxnCommonParam.byBlockType;
    stPinGetPara.PIN_Info.PINDigitMaxLength = stPayData.stTxnCommonParam.byPINMaxLen;
    stPinGetPara.PIN_Info.PINDigitMinLength = stPayData.stTxnCommonParam.byPINMinLen;

    // if sk lenght is 0
    //    stPinGetPara.Protection.CipherKeySet = stPayData.stTxnCommonParam.usPinKeySet;
    //    stPinGetPara.Protection.CipherKeyIndex = stPayData.stTxnCommonParam.usPinKeyIndex;
    stPinGetPara.Protection.CipherKeySet = ONLINE_KEY_SET;
    stPinGetPara.Protection.CipherKeyIndex = ONLINE_KEY_INDEX;
    stPinGetPara.Protection.SK_Length = 0;
    stPinGetPara.DUKPT_PARA.IsUseCurrentKey = FALSE;

    stPinGetPara.AdditionalData.InLength = stPayData.stTxnCommonParam.byPANLen;
    stPinGetPara.AdditionalData.pInData = stPayData.stTxnCommonParam.byPAN;

    stPinGetPara.PINOutput.EncryptedBlockLength = stPayData.stOLPinBlkGet_Param.usEnBlockLen;
    stPinGetPara.PINOutput.pEncryptedBlock = stPayData.stOLPinBlkGet_Param.byEnBlockBuf;
    stPinGetPara.Control.Timeout = stPayData.stOLPinBlkGet_Param.byTiemout;
    stPinGetPara.Control.AsteriskPositionX = stPayData.stOLPinBlkGet_Param.byAsteriskPosX;
    stPinGetPara.Control.AsteriskPositionY = stPayData.stOLPinBlkGet_Param.byAsteriskPosY;
    stPinGetPara.Control.NULLPIN = TRUE;
    // stPinGetPara.Control.piTestCancel = ;

    USHORT usRet = CTOS_KMS2PINGet(&stPinGetPara);
    if (usRet != d_OK) {
        if (usRet == d_KMS2_KEY_NOT_EXIST) {
            return DEBUG_RETCODE("OnOnlinePINBlockGet - Failed", d_KMS2_KEY_NOT_EXIST);
        } else if (usRet == d_KMS2_GET_PIN_ABORT) {
            return DEBUG_RETCODE("OnOnlinePINBlockGet - Failed", d_KMS2_GET_PIN_ABORT);
        } else if (usRet == d_KMS2_GET_PIN_TIMEOUT) {

            return DEBUG_RETCODE("OnOnlinePINBlockGet - Failed", d_KMS2_GET_PIN_TIMEOUT);
        } else if (usRet == d_KMS2_GET_PIN_NULL_PIN) {
            if (stPinGetPara.Control.NULLPIN) {
                stPayData.stTxnCommonParam.byPassPIN = 1;
                return DEBUG_RETCODE("OnOnlinePINBlockGet - OK", 0);
            } else {
                return DEBUG_RETCODE("OnOnlinePINBlockGet - Failed", d_KMS2_GET_PIN_TIMEOUT);
            }
        } else {
            return DEBUG_RETCODE("Get Online PIN Failed", usRet);
        }
    }

    DEBUG_INFO(DEBUGINFO_NORMAL, "Online PIN Block Length = %d", stPinGetPara.PINOutput.EncryptedBlockLength);
    DEBUG_BYTEBUF(DEBUGINFO_NORMAL, stPayData.stOLPinBlkGet_Param.byEnBlockBuf, stPinGetPara.PINOutput.EncryptedBlockLength, "Online PIN Block ");

    return DEBUG_EXIT(d_EMVAPLIB_OK);
}

USHORT MyCallBack::OnOfflinePINBlockGet(void) {
    DEBUG_ENTRY();

    CTOS_KMS2PINGET_PARA stPINPara;
    USHORT usRet = 0;

    stPINPara.Version = 0x00;
    stPINPara.PIN_Info.BlockType = stPayData.stTxnCommonParam.byBlockType;
    stPINPara.PIN_Info.PINDigitMinLength = stPayData.stTxnCommonParam.byPINMinLen;
    stPINPara.PIN_Info.PINDigitMaxLength = stPayData.stTxnCommonParam.byPINMaxLen;
    stPINPara.Protection.CipherMethod = KMS2_PINCIPHERMETHOD_EMV_OFFLINE_PIN;
    stPINPara.Control.Timeout = stPayData.stTxnCommonParam.usTimeout;
    stPINPara.Control.AsteriskPositionX = stPayData.stTxnCommonParam.byAsteriskPosX;
    stPINPara.Control.AsteriskPositionY = stPayData.stTxnCommonParam.byAsteriskPosY;
    stPINPara.Control.NULLPIN = stPayData.stTxnCommonParam.byPassPIN;
    stPINPara.Control.piTestCancel = NULL; //&(CUtil::CBGetPIN_CancekChk);
    stPINPara.PINOutput.EncryptedBlockLength = 16;
    stPINPara.PINOutput.pEncryptedBlock = stPayData.stOFLPinBlkGet_Param.byEncBlkData;

    usRet = CTOS_KMS2PINGet(&stPINPara);
    stPayData.stOFLPinBlkGet_Param.byPINLen = stPINPara.PINOutput.PINDigitActualLength;

    switch (usRet) {
        case d_OK:
            return DEBUG_RETCODE("GET Offline PIN", d_OK);

        case d_KMS2_GET_PIN_NULL_PIN:
            if (stPINPara.Control.NULLPIN)
                stPayData.stTxnCommonParam.byPassPIN = 1;

            return DEBUG_RETCODE("GET Offline PIN ", d_EMVAPLIB_ERR_PIN_BY_PASS);

        case d_KMS2_GET_PIN_TIMEOUT:
            return DEBUG_RETCODE("Get Offline PIN Timeout", d_KMS2_GET_PIN_TIMEOUT);

        case d_KMS2_GET_PIN_ABORT:
            return DEBUG_RETCODE("Get Offline PIN Abort", d_KMS2_GET_PIN_ABORT);

        default:
            return DEBUG_RETCODE("GET Offline PIN ", d_EMVAPLIB_ERR_CRITICAL_MISTAKES);
    }

    //    USHORT usRet;
    //    BYTE byPINBlock[32], byPINBlockLen;
    //    CTOS_stDefEncOffPINStruc stDefEncOffPIN;
    //    CTOS_KMS2DATAENCRYPT_PARA stKMS2DataEncPara;
    //
    //    stKMS2DataEncPara.Version = 0x00;
    //
    //    stKMS2DataEncPara.Protection.CipherKeyIndex = stPayData.stTxnCommonParam.usPinKeyIndex;
    //    stKMS2DataEncPara.Protection.CipherKeySet=stPayData.stTxnCommonParam.usPinKeySet;
    //    stKMS2DataEncPara.Protection.CipherMethod=KMS2_DATAENCRYPTCIPHERMETHOD_EXTPIN_ECB;
    //
    //    memcpy(byPINBlock, "\xB5\x1E\xC3\xBE\xB7\x24\x37\x13", 8);
    //    byPINBlockLen=8;
    //
    //    stKMS2DataEncPara.Input.pData=byPINBlock;
    //    stKMS2DataEncPara.Input.Length=byPINBlockLen;
    //
    //    usRet=CTOS_KMS2DataEncrypt(&stKMS2DataEncPara);
    //    if(usRet != d_OK)
    //        return DEBUG_RETCODE("OnOfflinePINBlockGet",d_EMVAPLIB_ERR_CRITICAL_ERROR);
    //    
    //    DEBUG_INFO(DEBUGINFO_NORMAL,"OnOfflinePINBlockGet - exit");
    //    
    //    return DEBUG_EXIT("OnOfflinePINBlockGet ",d_EMVAPLIB_ERR_ENTER_KMS_OFFLINEPIN);
}

void MyCallBack::OnOfflinePINVerifyResult(IN USHORT usResult) {
    DEBUG_INFO(DEBUGINFO_NORMAL, "OnOfflinePINVerifyResult - entry");

    BYTE byBuf[32];
    memset(byBuf, 0x00, 32);
    if (usResult == d_PIN_RESULT_OK) {
        //sprintf(byBuf, (const char*)"PIN Verify OK");
        memcpy(byBuf, "PIN Verify OK", sizeof ("PIN Verify OK"));
    } else if (usResult == d_PIN_RESULT_FAIL) {
        memset(byBuf, 0x00, 32);
        memcpy(byBuf, "PIN Verify FAILED", sizeof ("PIN Verify FAILED"));
    } else {
        memset(byBuf, 0x00, 32);
        memcpy(byBuf, "PIN Verify BLOCKED", sizeof ("PIN Verify BLOCKED"));
    }
    CTOS_LCDTPrintXY(1, 3, byBuf);

    DEBUG_INFO(DEBUGINFO_NORMAL, "OnOfflinePINVerifyResult - exit");
}

void MyCallBack::OnTxnOnline(IN ONLINE_PIN_DATA *pOnlinePINData, OUT EMV_ONLINE_RESPONSE_DATA* pOnlineResponseData) {
    DEBUG_INFO(DEBUGINFO_NORMAL, "OnTxnOnline - entry");

    BYTE byTLVBuf[1024];
    WORD wLen = 1024;
    memset(byTLVBuf, 0x00, 1024);
    CEMVBase cEmvBase;

    CByteStream cTagList;
    cTagList.Empty();

    cTagList = "\x82\x9F\x36\x89\x9F\x26\x9F\x27\x9F\x1E\x9F\x10"
            "\x9F\x33\x9F\x35\x95\x9B\x9F\x37\x9F\x01\x9F\x02"
            "\x9F\x03\x5F\x25\x5F\x24\x5A\x5F\x34\x9F\x15\x9F\x16"
            "\x9F\x1A\x9F\x1C\x57\x5F\x2A\x9A\x9F\x21\x9C\xDF\x30";

    //    cTagList = "\x82\x9F\x36\x89\x9F\x26\x9F\x27\x9F\x1E\x9F\x10"
    //            "\x9F\x33\x9F\x35\x95\x9B\x9F\x37\x9F\x01\x9F\x02"
    //            "\x9F\x03\x5F\x25\x5F\x24\x5A\x5F\x34\x9F\x15\x9F\x16"
    //            "\x9F\x1A\x9F\x1C\x57\x5F\x2A\x9C\xDF\x30";


    cEmvBase.FillTags(cTagList.GetBuffer(), cTagList.GetLength(), byTLVBuf, &wLen);

    DEBUG_BYTEBUF(DEBUGINFO_NORMAL, byTLVBuf, wLen, "ARQC TLV List ");

    CByteStream cARQC;
    CByteStream cARPC;

    cARQC.Empty();
    cARPC.Empty();
    cARQC.Write(byTLVBuf, wLen);
    //    cARQC.Write("\x9A\x03\x17\x08\x14\x9F\x21\x03\x18\x13\x00", 11);

    USHORT usRet = 0;
    //usRet = CTOS_EthernetOpenEx();
    MyWiFi myWifi;
    myWifi.OpenWiFi();
    if (usRet != 0x0000) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "EthernetOpen Failed: %04X", usRet);
    } else {
        //usRet = CollisTLVProcess("192.168.31.172", 5020, 3, cARQC, MSG_FINANCIAL_TRANSACTION, cARPC);
        //usRet = 
        myWifi.WifiSocktProcess("192.168.31.176", 7777, 3, cARQC, MSG_FINANCIAL_TRANSACTION, cARPC);
        DEBUG_INFO(DEBUGINFO_NORMAL, "CollisTLVProcess ret: %04X", usRet);
    }

    //CTOS_EthernetClose();
    myWifi.CloseWiFi();
    DEBUG_STREAM(DEBUGINFO_NORMAL, &cARPC, "ARPC ");

    if (cARPC.GetLength() == 0) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "ARPC is EMPTY!!");
        return;
    }

    CByteStream cARC, cIssuerScript;
    cARC.Empty();
    cIssuerScript.Empty();

    cEmvBase.GetData((PBYTE) "\x8A", &cARPC, cARC, FALSE);
    DEBUG_STREAM(DEBUGINFO_NORMAL, &cARC, "ARC ");

    //    cEmvBase.GetData((PBYTE)"\x71\x72", &cARPC, cIssuerScript, FALSE);
    //    DEBUG_STREAM(DEBUGINFO_NORMAL,&cIssuerScript, "Issuer Script ");

    if (cARC.GetLength() < 2) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "ARC is not received!");
        return;
    }

    if ((*(cARC.GetBuffer()) == 0x30) && (*(cARC.GetBuffer() + 1) == 0x35)) {
        pOnlineResponseData->bAction = d_ONLINE_ACTION_DECLINE;
    } else if (((*(cARC.GetBuffer()) == 0x30) && (*(cARC.GetBuffer() + 1) == 0x30)) ||
            ((*(cARC.GetBuffer()) == 0x31) && (*(cARC.GetBuffer() + 1) == 0x31)) ||
            ((*(cARC.GetBuffer()) == 0x31) && (*(cARC.GetBuffer() + 1) == 0x30)) ||
            ((*(cARC.GetBuffer()) == 0x38) && (*(cARC.GetBuffer() + 1) == 0x37))) {
        pOnlineResponseData->bAction = d_ONLINE_ACTION_APPROVAL;
    } else if (((*(cARC.GetBuffer()) == 0x30) && (*(cARC.GetBuffer() + 1) == 0x31)) ||
            ((*(cARC.GetBuffer()) == 0x30) && (*(cARC.GetBuffer() + 1) == 0x32))) {
        //        pOnlineResponseData->bAction = d_ONLINE_ACTION_APPROVAL;
        //CUIDisplay cUI;
        UINT unRet = 0;
       // unRet = cUI.MsgBox((char*) "Call Your Bank, Approve or Decline?", 0);
        //if (unRet == d_KBD_ENTER) {
            pOnlineResponseData->bAction = d_ONLINE_ACTION_APPROVAL;
//        } else {
//            pOnlineResponseData->bAction = d_ONLINE_ACTION_DECLINE;
//        }
    }

    CByteStream cAuthData;
    cAuthData.Empty();

    cEmvBase.GetData((PBYTE) "\x91", &cARPC, cAuthData, FALSE);
    DEBUG_STREAM(DEBUGINFO_NORMAL, &cAuthData, "Issuer Authentication Data ");
    
    pOnlineResponseData->pAuthorizationCode = cARC.GetBuffer(); // \x8A\x02\x30\x35    \x30\x35     \x30\x30
    pOnlineResponseData->pIssuerAuthenticationData = cAuthData.GetBuffer(); //  \xA8\xF6\x59\x85\xE3\x1B\xB2\xD8\x30\x35
    pOnlineResponseData->IssuerAuthenticationDataLen = cAuthData.GetLength(); //11  12 
    pOnlineResponseData->pIssuerScript = (PBYTE) ""; //cIssuerScript.GetBuffer();
    pOnlineResponseData->IssuerScriptLen = 0; // cIssuerScript.GetLength();

    DEBUG_INFO(DEBUGINFO_NORMAL, "OnTxnOnline - exit");
}

void MyCallBack::OnTxnIssuerScriptResult(IN BYTE* pScriptResult, IN USHORT pScriptResultLen) {
    DEBUG_INFO(DEBUGINFO_NORMAL, "OnTxnIssuerScriptResult - entry");

    if (pScriptResultLen)
        memcpy(stPayData.byScriptData, pScriptResult, pScriptResultLen);

    DEBUG_INFO(DEBUGINFO_NORMAL, "OnTxnIssuerScriptResult - exit");
}

void MyCallBack::OnTxnResult(IN BYTE bResult, IN BOOL IsSignatureRequired) {
    DEBUG_INFO(DEBUGINFO_NORMAL, "OnTxnResult - entry");

    CTOS_LCDTClearDisplay();

    CTOS_LCDTPrintXY(1, 3, (BYTE*) "TXN Result:    ");

    switch (bResult) {
        case d_PIN_RESULT_OK:
            CTOS_LCDTPrintXY(1, 4, (BYTE*) "APPROVAL		");
            break;
        case d_PIN_RESULT_FAIL:
            CTOS_LCDTPrintXY(1, 4, (BYTE*) "DECLINE         ");
            break;
        case d_PIN_RESULT_BLOCKED:
            CTOS_LCDTPrintXY(1, 4, (BYTE*) "BLOCKED         ");
            break;
        case d_PIN_RESULT_FAILBLOCKED:
            CTOS_LCDTPrintXY(1, 4, (BYTE*) "FAIL BLOCKED    ");
            break;
    }

    if (IsSignatureRequired) {
        CTOS_LCDTPrintXY(1, 5, (BYTE*) "Signature Needed");
        DEBUG_BYTEBUF(DEBUGINFO_NORMAL, stPayData.stTxnCommonParam.byAID, 8, "OnTxnResult - AID");

        //        CFunBase cFun;
        CByteStream cAID, cBuf;
        cAID.Empty();
        cBuf.Empty();

        //CTOS_PrinterPutString((PBYTE) "App Label:");
        // CTOS_PrinterPutString(stPayData.stTxnCommonParam.byAppLabel);
        //DEBUG_STREAM(DEBUGINFO_NORMAL, &cData, "TVR ");
        DEBUG_INFO(DEBUGINFO_NORMAL, "App Label:%s\n", stPayData.stTxnCommonParam.byAppLabel);
        cBuf.Write(stPayData.stTxnCommonParam.byAID, 8);
        //cFun.Hex2Str(&cBuf, cAID, 0);
        CTOS_PrinterPutString((PBYTE) "AID:");
        DEBUG_INFO(DEBUGINFO_NORMAL, "AID:");
        //CTOS_PrinterPutString((PBYTE) cAID.PushZero());
        DEBUG_STREAM(DEBUGINFO_NORMAL, &cAID, "AID ");
        //CTOS_PrinterPutString((PBYTE) "\n\n");
    }

    DEBUG_INFO(DEBUGINFO_NORMAL, "OnTxnResult - exit");
}

void MyCallBack::OnTotalAmountGet(IN BYTE *pPAN, IN BYTE bPANLen, OUT ULONG *pAmount) {
    DEBUG_INFO(DEBUGINFO_NORMAL, "OnTotalAmountGet - entry");

    *pAmount = 0;

    DEBUG_INFO(DEBUGINFO_NORMAL, "OnTotalAmountGet - exit");
}

void MyCallBack::OnExceptionFileCheck(IN BYTE *pPAN, IN BYTE bPANLen, OUT BOOL *isException) {
    DEBUG_INFO(DEBUGINFO_NORMAL, "OnExceptionFileCheck - entry");

    DEBUG_INFO(DEBUGINFO_NORMAL, "OnExceptionFileCheck - exit");
}

BOOL MyCallBack::OnCAPKRevocationCheck(IN BYTE *pbRID, IN BYTE bCAPKIdx, IN BYTE *pbSerialNumuber) {
    DEBUG_INFO(DEBUGINFO_NORMAL, "OnCAPKRevocationCheck - entry");

    DEBUG_INFO(DEBUGINFO_NORMAL, "OnCAPKRevocationCheck - exit");

    return FALSE;
}

void MyCallBack::OnOutPutCardAPDU(IN BYTE *pTxAPDU, IN USHORT TxAPUDLen, IN BYTE *pRxAPDU, IN USHORT RxAPDULen) {

    DEBUG_INFO(DEBUGINFO_NORMAL, "OnOutPutCardAPDU - entry");

    BYTE byBuf[2048];
    memset(byBuf, 0x00, sizeof (byBuf));

    //CFunBase cFun;

    //CByteStream cOutData;
    //cOutData.Empty();

    //cOutData = cFun.Hex2Str(pTxAPDU, TxAPUDLen);
    DEBUG_BYTEBUF(DEBUGINFO_NORMAL, pTxAPDU, TxAPUDLen, "TxAPDU");
    //DEBUG_STREAM(DEBUGINFO_NORMAL, &cOutData, "TxAPDU");
    //DEBUG_INFO(DEBUGINFO_NORMAL, "TxAPDU - %s", cOutData.PushZero());

    //    cOutData.Empty();
    //    cOutData = cFun.Hex2Str(pRxAPDU, RxAPDULen);
    DEBUG_BYTEBUF(DEBUGINFO_NORMAL, pRxAPDU, RxAPDULen, "RxAPDU");
    //DEBUG_STREAM(DEBUGINFO_NORMAL, &cOutData, "RxAPDU");
    //DEBUG_INFO(DEBUGINFO_NORMAL, "RxAPDU - %s", cOutData.PushZero());

    DEBUG_INFO(DEBUGINFO_NORMAL, "OnOutPutCardAPDU - exit");
}


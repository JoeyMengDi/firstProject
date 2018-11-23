/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EMVCommon.h
 * Author: Administrator
 *
 * Created on 2017年7月31日, 下午6:16
 */

#ifndef EMVCOMMON_H
#define EMVCOMMON_H

#define EMV_PINKEY_SET              0x2010;
#define EMV_PIN_INDEX               0x0001;
#define EMV_PIN_INFO_BLOCK_TYPE     KMS2_PINBLOCKTYPE_ANSI_X9_8_ISO_0 

#define	ONLINE_KEY_SET                  0x2000
#define	ONLINE_KEY_INDEX                0x0000




typedef struct stTxnCommonParam
{
    BYTE byAID[16];
    BYTE byAIDLen;
    
    BYTE byAppLabel[17];
    BYTE byAppLabelLen;
    
    BYTE byPAN[64];
    BYTE byPANLen;
    
    USHORT usPinKeySet;
    USHORT usPinKeyIndex;
    
    BYTE byBlockType;
    BYTE byPINMinLen;
    BYTE byPINMaxLen;
    USHORT usTimeout;
    
    BYTE byAsteriskPosX;
    BYTE byAsteriskPosY;
    
    BYTE byPassPIN;
    
    
    
    
}TXNCOMMON_PARAM;

typedef struct stOnDisplayShow_Param
{
    
}ONDISPSHOW_PARAM;

typedef struct stOnErrorMsg_Param
{
    
}ONERRMSG_PARAM;

typedef struct stOnEMVCfgActive_Param
{
    
}ONEMVCFGACTIVE_PARAM;

typedef struct stOnTxnDataGet_Param
{
    BYTE byTxnType;
    unsigned long long llAmt;
    unsigned long long llTipAmt;
    BYTE byTipPercent;
    
    
    
}ONTXNDATAGET_PARAM;

typedef struct stOnAppList_Param
{
    
}ONAPPLIST_PARAM;

typedef struct stOnAppSelectConfirm_Param
{
    
}ONAPPSELCFM_PARAM;

typedef struct stOnTMDataGet_Param
{
    
}ONTMDATAGET_PARAM;

typedef struct stOnCAPKGet_Param
{
    
}ONCAPKGET_PARAM;

typedef struct stOnOnlinePINBlockGet_Param
{
    USHORT usEnBlockLen;
    BYTE byEnBlockBuf[16];
    BYTE byTiemout;
    BYTE byAsteriskPosX;
    BYTE byAsteriskPosY;
}ONOLPINBLKGET_PARAM;

typedef struct stOnOfflinePINBlockGet_Param
{
    BYTE byEncBlkData[32];
    BYTE byPINLen;
    
    
}ONOFLBLKGET_PARAM;

typedef struct stOnPINVerifyResult_Param
{
    
}ONPINVERIFYRLT_PARAM;

typedef struct stOnTxnOnline_Param
{
    
}ONTXNOL_PARAM;

typedef struct stOnTxnIssuerScriptResult_Param
{
    
}ONTXNISSUERSCRIPTRLT_PARAM;

typedef struct stOnTxnResult_Param
{
    
}ONTXNRLT_PARAM;

typedef struct stOnTotalAmountGet_Param
{
    
}ONTOTAMTGET_PARAM;

typedef struct stOnExceptionFileCheck_Param
{
    
}ONEXPFLCHK_PARAM;

typedef struct stOnCAPKRevocationCheck_Param
{
    
}ONCAPKREVOCHK_PARAM;

typedef struct stOnGetPINNotify_Param
{
    BYTE byPINRequired;

    USHORT usPINLineLeftX;
    USHORT usPINLineRightX;
    USHORT usPINLinePosY;
    
    BYTE byPINMaxLen;
    BYTE byPINMinLen;
    
    ULONG ulTimeout;
    
}ONGETPINNOTIFY_PARAM;

typedef struct stOnOutputCardAPDU_Param
{
    
}ONOUTPUTCAPDU_PARAM;



typedef struct stPaymentData
{
    TXNCOMMON_PARAM             stTxnCommonParam;
    ONTXNDATAGET_PARAM          stTxnDataGetParam;
    ONAPPLIST_PARAM             stAppListParam;
    ONAPPSELCFM_PARAM           stAppSelCfmParam;
    ONTMDATAGET_PARAM           stTmDataGetParam;
    ONCAPKGET_PARAM             stCAPKGet_Param;
    ONOLPINBLKGET_PARAM         stOLPinBlkGet_Param;
    ONOFLBLKGET_PARAM           stOFLPinBlkGet_Param;
    ONPINVERIFYRLT_PARAM        stPinVerifyRlt_Param;
    ONTXNOL_PARAM               stTxnOnline_Param;
    ONTXNISSUERSCRIPTRLT_PARAM  stTxnIssuerScriptRlt_Param;
    ONTXNRLT_PARAM              stTxnResult_Param;
    ONTOTAMTGET_PARAM           stTotAmtGet_Param;
    ONEXPFLCHK_PARAM            stExpFlChk_Param;
    ONCAPKREVOCHK_PARAM         stCAPKRevoChk_Param;
    ONGETPINNOTIFY_PARAM        stGetPinNotify_Param;
    ONOUTPUTCAPDU_PARAM         stOutputCardAPDU_Param;
    
    
    
    
    
    
    
    BYTE byOnlinePIN[32];
    USHORT usOnlinePINLen;
    
    
    BYTE byKSNData[20];
    BYTE byKSNLen;
    
    BYTE byPINRequired;
    
    BYTE byScriptData[2048];
    
}PAYMENT_DATA, *PPAYMENT_DATA;


#endif /* EMVCOMMON_H */


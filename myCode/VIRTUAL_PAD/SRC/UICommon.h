/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CUICommon.h
 * Author: Administrator
 *
 * Created on 2017年8月25日, 上午11:00
 */

#ifndef CUICOMMON_H
#define CUICOMMON_H

#define UI_CONFIG_PATH                     "./RES/LANG/EN/Text/UI_CFG_MP200.xml"
#define CONFIG_UI_TYPE_NODE                "UIType"

#define UI_USERMNG_PATH                     "./RES/LANG/EN/Text/USER_MNG_MENU.xml"
#define USERMNG_UI_TYPE_NODE                "UserMng"

#define CONFIG_UI_INPUT_AMOUNT_APPNAME     "UI_TXN_Input_Amount"
#define CONFIG_UI_L1_NAME                  "L1"
#define CONFIG_UI_L2_NAME                  "L2"
#define CONFIG_UI_L3_NAME                  "L3"
#define CONFIG_UI_L4_NAME                  "L4"
#define CONFIG_UI_L5_NAME                  "L5"
#define CONFIG_UI_L6_NAME                  "L6"
#define CONFIG_UI_L7_NAME                  "L7"
#define CONFIG_UI_L8_NAME                  "L8"
#define CONFIG_UI_L9_NAME                  "L9"
#define CONFIG_UI_L10_NAME                  "L10"
#define CONFIG_UI_L11_NAME                  "L11"
#define CONFIG_UI_L12_NAME                  "L12"
#define CONFIG_UI_L13_NAME                  "L13"
#define CONFIG_UI_L14_NAME                  "L14"
#define CONFIG_UI_L15_NAME                  "L15"
#define CONFIG_UI_L16_NAME                  "L16"

#define CONFIG_UI_KEY_ATTR_ROW              "row"
#define CONFIG_UI_KEY_ATTR_COL                "col"
#define CONFIG_UI_KEY_ATTR_ALIGN            "align"
#define CONFIG_UI_KEY_ATTR_TYPE               "type"
#define CONFIG_UI_KEY_ATTR_PX                   "px"


#define CONFIG_UI_TYPE_EDIT                      "edit"
#define CONFIG_UI_TYPE_LABEL                   "label"
#define CONFIG_UI_ALIGN_LEFT                   "Left"
#define CONFIG_UI_ALIGN_RIGHT                "Right"
#define CONFIG_UI_ALIGN_CENTER             "Center"

//No Response UI ID
#define Conn_UI_Connecting_F2_1                           0x0001
#define Conn_UI_Connected_F2_2                            0x0002
#define Conn_UI_SendData_F2_3                              0x0003
#define Conn_UI_RecvData_F2_4                               0x0004
#define TXN_UI_Accept_F3_3                                     0x0005
#define TXN_UI_Failed_F3_4                                      0x0006

//Have Response UI ID
#define RESPONSE_FLAG                                       0x8000
#define Main_UI_F1_1                                        0x8001
#define Main_UI_FuncList_F1_2                               0x8002
#define Conn_UI_Connection_Failed_F2_5                      0x8003
#define Conn_UI_SendData_Failed_F2_6                        0x8004
#define TXN_UI_InputAmount_F3_1                             0x8005
#define TXN_UI_InputPin_F3_2                                0x8006
#define RCard_UI_Read_F4_1                                  0x8007
#define RCard_UI_ReadErr_F4_2                               0x8008
#define RCard_UI_ChipCardErr_F4_3                           0x8009
#define RCard_UI_UseChipCard_F4_4                           0x800A
//#define UI_REVERSAL_MSG_FAILED_F16                        0x0010

#define  UI_F1_1    "Main_UI_F1_1"
#define  UI_F1_2    "Main_UI_FuncList_F1_2"
#define  UI_F2_1    "Conn_UI_Connecting_F2_1"
#define  UI_F2_2    "Conn_UI_Connected_F2_2"
#define  UI_F2_3    "Conn_UI_SendData_F2_3"
#define  UI_F2_4    "Conn_UI_RecvData_F2_4"
#define  UI_F2_5    "Conn_UI_Connection_Failed_F2_5"
#define  UI_F2_6    "Conn_UI_SendData_Failed_F2_6"
#define  UI_F3_1    "TXN_UI_InputAmount_F3_1"
#define  UI_F3_2    "TXN_UI_InputPin_F3_2"
#define  UI_F3_3    "TXN_UI_Accept_F3_3"
#define  UI_F3_4    "TXN_UI_Failed_F3_4"
#define  UI_F4_1    "RCard_UI_Read_F4_1"
#define  UI_F4_2    "RCard_UI_ReadErr_F4_2"
#define  UI_F4_3    "RCard_UI_ChipCardErr_F4_3"
#define  UI_F4_4    "RCard_UI_UseChipCard_F4_4"

/* User Management */
#define  UI_INIT_FAIL         "Init_Fail"
#define  UI_USER_MENU         "UserMenu"
#define  UI_USER_MENU_NORMAL  "UserMenuNormal"
#define  UI_ADD_MAIN          "AddUserMain"
#define  UI_ADD_INVALID       "AddUserInvalid"
#define  UI_ADD_EXIST         "AddUserExist"

#define  UI_LIST_FAIL     "ListReadErr"
#define  UI_LIST          "UserList"
#define  UI_DELETE        "DelUser"
#define  UI_DEL_FAIL      "DelReadErr"
#define  UI_DEL_CONFIRM   "DelUserConfirm"
#define  UI_DEL_DB_FAIL   "DelFail"

#define  UI_RST           "ResetPWD"
#define  UI_RST_READ_ERR  "ResetReadErr"
#define  UI_RST_CONFIRM   "ResetPWDConfirm"
#define  UI_RST_DB_FAIL   "ResetFail"
#define  UI_RST_SUCCESS   "ResetSuccess"

#define  UI_UPDATE_MAIN         "UpdateMain"
#define  UI_UPDATE_INVALID      "UpdateNewInvalid"
#define  UI_UPDATE_OLD_ERR      "UpdateOldErr"
#define  UI_UPDATE_INCONSISTENT "UpdateNewInconsistent" 
#define  UI_UPDATE_FAIL         "UpdateFail"

#define  UI_CLOSE_FAIL          "UserMngCloseFail"

/* login */
#define  UI_LOGIN         "Login"
#define  UI_LOGIN_INVALID "LoginInvalid"
#define  UI_LOGIN_ERROR   "LoginError"

WORD DisplayPage(_IN_ PCSTR pszFilePath, _IN_ PCSTR pszNode, _IN_ PCSTR pszApp, _IN_ const char (*pszKeyList)[32], BYTE byLineNum);

#endif /* CUICOMMON_H */

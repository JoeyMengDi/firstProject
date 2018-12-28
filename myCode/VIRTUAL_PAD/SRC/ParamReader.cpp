/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParamReader.cpp
 * Author: Louis Lu
 * 
 * Created on 2017年8月22日, 下午1:57
 */

#include "ParamReader.h"
#include "../SRC/StdafxHead.h"
#include "../SRC/Profile.h"
#include "../SRC/XMLNode.h"
#include "../SRC/ErrorCode.h"
#include "../SRC/CPCommon.h"
#include "../SRC/FunBase.h"
#include "../SRC/MsgCommType.h"
#include "../CommLib/CommEthParam.h"
#include "../CommLib/CommWIFIParam.h"
#include "../CommLib/CommGPRSParam.h"
#include <arpa/inet.h>

#define MIN_PORT_NUMBER (0)
#define MAX_PORT_NUMBER (65535)

#define COMMTYPE_ETH  0x0001
#define COMMTYPE_WIFI  0x0002
#define COMMTYPE_GPRS  0x0003

/////////////////////////////////////////////////////////////////////////////////
// CParamReader
//
// Function: 
//          Construct, initialize the member variables of class.
//
// @param: 
//         None.
//
// @return:
//         None
/////////////////////////////////////////////////////////////////////////////////
CParamReader::CParamReader()
{
    m_wCurIPType = PRIMARY_IP;
    memset(m_szPort, 0, sizeof(m_szPort));
    memset(m_szIP, 0, sizeof(m_szIP));
    memset(m_szIPNodeName, 0, sizeof(m_szIPNodeName));
    memset(m_szPortNodeName, 0, sizeof(m_szPortNodeName));
}

/////////////////////////////////////////////////////////////////////////////////
// ~CParamReader
//
// Function:
//          Destruct.
//
// @param:
//          None
//
// @return:
//          None
/////////////////////////////////////////////////////////////////////////////////
CParamReader::~CParamReader()
{
}

/**
 * GetUIMode
 * 
 * Function:
 *      Get the UI Mode set in the configuration file.
 * 
 * @return 
 *      0xF001 - UI Mode set as TEXT mode.
 *      0xF002 - UI Mode set as Graphic mode.
 *      Other values - Please refer to the <ErrorCode.h>
 */
WORD CParamReader::GetUIMode(PBYTE pbyMode)
{
    DEBUG_ENTRY("GetUIMode");

    if(pbyMode == NULL)
        return DEBUG_RETCODE("GetUIMode", ERROR_INVALID_PARAM);

    WORD wRet = 0;
    CProfile cProfile((char*)CONFIG_XML_NAME, (char*)CONFIG_XML_PLATFORM_NODE);
    wRet = cProfile.OpenConfigFile();
    if(wRet != OK)
        return DEBUG_RETCODE("OpenConfigFile Error", wRet);

    CHAR szParaBuf[BUF_LEN];
    memset(szParaBuf, 0x00, sizeof(szParaBuf));
    wRet = cProfile.GetKeyValue(PF_DISPLAY_MODE, VALUE, (char*)"", szParaBuf, sizeof(szParaBuf));
    if(wRet != OK)
        return DEBUG_RETCODE("GetKeyValue Error", wRet);

    cProfile.CloseConfigFile();

    if((strlen(szParaBuf) == 0))
    {
        *pbyMode = UI_MODE_TEXT;
        DEBUG_INFO("No value set for UI Mode");

        return DEBUG_RETCODE("Set UI Mode with TEXT", OK);
    }

    if(!memcmp(szParaBuf, DISPLAY_MODE_TEXT, sizeof(DISPLAY_MODE_TEXT)))
    {
        *pbyMode = UI_MODE_TEXT;
        DEBUG_INFO("UI Mode set with TEXT");
    }
    else if(!memcmp(szParaBuf, DISPLAY_MODE_GRAPHIC, sizeof(DISPLAY_MODE_GRAPHIC)))
    {
        *pbyMode = UI_MODE_GRAPHIC;
        DEBUG_INFO("UI Mode set with GRAPHIC");
    }
    else
    {
        *pbyMode = UI_MODE_TEXT;
        DEBUG_INFO("UI Mode set with TEXT");
    }

    return DEBUG_EXIT("GetUIMode", OK);
}

/**
 * GetCommDebugMode
 * 
 * Function:
 *      Get the COMM debug mode set in the config file.
 * 
 * @Param
 *      pbyDebugMode - Store the debug mode read from xml file
 * @return 
 *      TRUE - Debug mode enabled for COMM module.
 *      FALSE - Debug mode disabled for COMM module.
 *      Other values - please refer to the <ErrorCode.h>
 * 
 */
WORD CParamReader::GetCommDebugMode(PBYTE pbyDebugMode)
{
    DEBUG_ENTRY("GetCommDebugMode");

    if(pbyDebugMode == NULL)
        return DEBUG_RETCODE("GetCommDebugMode", ERROR_INVALID_PARAM);

    CProfile cProfile((char*)CONFIG_XML_NAME, (char*)CONFIG_XML_DEBUG_NODE);
    WORD wRet = 0;
    wRet = cProfile.OpenConfigFile();
    if(wRet != OK)
        return DEBUG_RETCODE("OpenConfigFile Error", wRet);

    CHAR szParaBuf[BUF_LEN];
    memset(szParaBuf, 0x00, sizeof(szParaBuf));
    wRet = cProfile.GetKeyValue(MODULE_COMMLIB, VALUE, (char*)"", szParaBuf, sizeof(szParaBuf));
    if(wRet != OK)
        return DEBUG_RETCODE("GetKeyValue Error", wRet);

    cProfile.CloseConfigFile();

    if((strlen(szParaBuf) == 0))
    {
        *pbyDebugMode = 0; //Debug Mode Disabled
        DEBUG_INFO("No Value Set - Disable Debug Mode");

        return DEBUG_RETCODE("COMM Debug Mode - No Value Set", OK);
    }

    if(!memcmp(szParaBuf, ENABLE, sizeof(ENABLE)))
    {
        *pbyDebugMode = 1; //Debug Mode Enabled
        DEBUG_INFO("COMM Debug Mode Disabled");
    }
    else
    {
        *pbyDebugMode = 0; //Debug Mode Disabled
        DEBUG_INFO("COMM Debgu Mode Enabled");
    }

    return DEBUG_EXIT("GetCommDebugMode", OK);
}

/**
 * GetMenuDebugMode
 * 
 * Function:
 *      Get the Menu debug mode set in the config file.
 * 
 * @Param
 *      pbyDebugMode - Store the debug mode read from xml file
 * @return 
 *      TRUE - Debug mode enabled for Menu module.
 *      FALSE - Debug mode disabled for Menu module.
 *      Other values - please refer to the <ErrorCode.h>
 * 
 */
WORD CParamReader::GetMenuDebugMode(PBYTE pbyDebugMode)
{
    DEBUG_ENTRY("GetMenuDebugMode");

    if(pbyDebugMode == NULL)
        return DEBUG_RETCODE("GetCommDebugMode", ERROR_INVALID_PARAM);

    CProfile cProfile((char*)CONFIG_XML_NAME, (char*)CONFIG_XML_DEBUG_NODE);
    WORD wRet = 0;
    wRet = cProfile.OpenConfigFile();
    if(wRet != OK)
        return DEBUG_RETCODE("OpenConfigFile Error", wRet);

    CHAR szParaBuf[BUF_LEN];
    memset(szParaBuf, 0x00, sizeof(szParaBuf));
    wRet = cProfile.GetKeyValue(MODULE_MENULIB, VALUE, (char*)"", szParaBuf, sizeof(szParaBuf));
    if(wRet != OK)
        return DEBUG_RETCODE("GetKeyValue Error", wRet);

    cProfile.CloseConfigFile();

    if((strlen(szParaBuf) == 0))
    {
        DEBUG_INFO("No Value Set - Disable Debug Mode");
//        return FALSE;
        return DEBUG_RETCODE("No Value Set - Disable Debug Mode", OK);
    }

    if(!memcmp(szParaBuf, ENABLE, sizeof(ENABLE)))
    {
        *pbyDebugMode = 1; // Debug Mode Enabled
        DEBUG_INFO("Menu Debug Mode Enabled");
    }
    else
    {
        *pbyDebugMode = 0; // Debug Mode Disabled
        DEBUG_INFO("Menu Debug Mode Disabled");
    }

    return DEBUG_EXIT("GetMenuDebugMode", OK);
}

/**
 * GetMsgDebugMode
 * 
 * Function:
 *      Get the Msg debug mode set in the config file.
 * 
 * @Param
 *      pbyDebugMode - Store the debug mode read from xml file
 * @return 
 *      TRUE - Debug mode enabled for Msg module.
 *      FALSE - Debug mode disabled for Msg module.
 *      Other values - please refer to the <ErrorCode.h>
 * 
 */
WORD CParamReader::GetMsgDebugMode(PBYTE pbyDebugMode)
{
    DEBUG_ENTRY("GetMsgDebugMode");

    if(pbyDebugMode == NULL)
        return DEBUG_RETCODE("GetMsgDebugMode", ERROR_INVALID_PARAM);

    CProfile cProfile((char*)CONFIG_XML_NAME, (char*)CONFIG_XML_DEBUG_NODE);
    WORD wRet = 0;
    wRet = cProfile.OpenConfigFile();
    if(wRet != OK)
        return DEBUG_RETCODE("OpenConfigFile Error", wRet);

    CHAR szParaBuf[BUF_LEN];
    memset(szParaBuf, 0x00, sizeof(szParaBuf));
    wRet = cProfile.GetKeyValue(MODULE_MSGQUEUELIB, VALUE, (char*)"", szParaBuf, sizeof(szParaBuf));
    if(wRet != OK)
        return DEBUG_RETCODE("GetKeyValue Error", wRet);

    cProfile.CloseConfigFile();

    if((strlen(szParaBuf) == 0))
    {
        DEBUG_INFO("No Value Set - Disable Debug Mode");
        *pbyDebugMode = 0;

        return DEBUG_RETCODE("GetMsgDebugMode", OK);
    }

    if(!memcmp(szParaBuf, ENABLE, sizeof(ENABLE)))
    {
        *pbyDebugMode = 1; // Message Queue Debug Mode Enabled.
        DEBUG_INFO("MSGQ Debug Mode Enabled");
    }
    else
    {
        *pbyDebugMode = 0; // Message Queue Debug Mode Disabled.
        DEBUG_INFO("MSGQ Debug Mode Disabled");
    }

    return DEBUG_EXIT("GetMsgDebugMode", OK);
}

/**
 * GetUIDebugMode
 * 
 * Function:
 *      Get the UI debug mode set in the config file.
 * 
 * @Param
 *      pbyDebugMode - Store the debug mode read from xml file
 * @return 
 *      TRUE - Debug mode enabled for UI module.
 *      FALSE - Debug mode disabled for UI module.
 *      Other values - please refer to the <ErrorCode.h>
 * 
 */
WORD CParamReader::GetUIDebugMode(PBYTE pbyDebugMode)
{
    DEBUG_ENTRY("GetUIDebugMode");

    if(pbyDebugMode == NULL)
        return DEBUG_RETCODE("GetUIDebugMode", ERROR_INVALID_PARAM);

    CProfile cProfile((char*)CONFIG_XML_NAME, (char*)CONFIG_XML_DEBUG_NODE);
    WORD wRet = 0;
    wRet = cProfile.OpenConfigFile();
    if(wRet != OK)
        return DEBUG_RETCODE("OpenConfigFile Error", wRet);

    CHAR szParaBuf[BUF_LEN];
    memset(szParaBuf, 0x00, sizeof(szParaBuf));
    wRet = cProfile.GetKeyValue(MODULE_UILIB, VALUE, (char*)"", szParaBuf, sizeof(szParaBuf));
    if(wRet != OK)
        return DEBUG_RETCODE("GetKeyValue Error", wRet);

    cProfile.CloseConfigFile();

    if((strlen(szParaBuf) == 0))
    {
        *pbyDebugMode = 0;
        DEBUG_INFO("No Value Set - Disable Debug Mode");

        return DEBUG_RETCODE("GetUIDebugMode", OK);
    }

    if(!memcmp(szParaBuf, ENABLE, sizeof(ENABLE)))
    {
        *pbyDebugMode = 1; // UI Debug Mode Enabled.
        DEBUG_INFO("UI Debug Mode Enabled");
    }
    else
    {
        *pbyDebugMode = 0; // UI Debug Mode Disabled.
        DEBUG_INFO("UI Debug Mode Disabled");
    }

    return DEBUG_EXIT("GetUIDebugMode", OK);
}

/**
 * GetProtMode
 * 
 * Function:
 *      Get the Protocol mode set in the config file.
 * 
 * @Param
 *      pbyMode - Store the Procotol mode read from config xml file
 * @return 
 *      TRUE - Procotol mode enabled for Comm module.
 *      FALSE - Procotol mode disabled for Comm module.
 *      Other values - please refer to the <ErrorCode.h>
 * 
 */
WORD CParamReader::GetProtMode(PBYTE pbyMode)
{
    DEBUG_ENTRY("GetProtMode");

    if(pbyMode == NULL)
        return DEBUG_RETCODE("GetProtMode", ERROR_INVALID_PARAM);

    CProfile cProfile((char*)CONFIG_XML_NAME, (char*)CONFIG_XML_PLATFORM_NODE);
    WORD wRet = 0;
    wRet = cProfile.OpenConfigFile();
    if(wRet != OK)
        return DEBUG_RETCODE("OpenConfigFile Error", wRet);

    CHAR szParaBuf[BUF_LEN];
    memset(szParaBuf, 0x00, sizeof(szParaBuf));
    wRet = cProfile.GetKeyValue(PF_PROTOCOL_MODE, VALUE, (char*)"", szParaBuf, sizeof(szParaBuf));
    if(wRet != OK)
        return DEBUG_RETCODE("GetKeyValue Error", wRet);

    cProfile.CloseConfigFile();

    if((strlen(szParaBuf) == 0))
    {
        DEBUG_INFO("No Value Set - Disable Protocol Mode");
        *pbyMode = 0; // Protocol Mode Disabled
        return DEBUG_RETCODE("GetProtMode", OK);
    }

    if(!memcmp(szParaBuf, ENABLE, sizeof(ENABLE)))
    {
        *pbyMode = 1; // Protocol Mode Enabled
        DEBUG_INFO(" Protocol Mode Enabled");
    }
    else
    {
        *pbyMode = 0; // Protocol Mode Disabled
        DEBUG_INFO(" Protocol Mode Enabled");
    }

    return DEBUG_EXIT("GetProtMode", OK); // Enable Debug Mode for Menu module.
}

/**
 * GetTXNDebugMode
 * 
 * Function:
 *      Get the TXN debug mode set in the config file.
 * 
 * @Param
 *      pbyDebugMode - Store the debug mode read from xml file
 * @return 
 *      TRUE - Debug mode enabled for TXN module.
 *      FALSE - Debug mode disabled for TXN module.
 *      Other values - please refer to the <ErrorCode.h>
 * 
 */
WORD CParamReader::GetTXNDebugMode(_IN_OUT_ PBYTE pbyDebugMode)
{
    DEBUG_ENTRY("GetTXNDebugMode");

    if(pbyDebugMode == NULL)
        return DEBUG_RETCODE("GetTXNDebugMode", ERROR_INVALID_PARAM);

    CProfile cProfile((char*)CONFIG_XML_NAME, (char*)CONFIG_XML_DEBUG_NODE);
    WORD wRet = 0;
    wRet = cProfile.OpenConfigFile();
    if(wRet != OK)
        return DEBUG_RETCODE("OpenConfigFile Error", wRet);

    CHAR szParaBuf[BUF_LEN];
    memset(szParaBuf, 0x00, sizeof(szParaBuf));
    wRet = cProfile.GetKeyValue(MODULE_TXNLIB, VALUE, (char*)"", szParaBuf, sizeof(szParaBuf));
    if(wRet != OK)
        return DEBUG_RETCODE("GetKeyValue Error", wRet);

    cProfile.CloseConfigFile();

    if((strlen(szParaBuf) == 0))
    {
        DEBUG_INFO("No Value Set - Disable TXN Mode");
        *pbyDebugMode = 0; // Protocol Mode Disabled
        return DEBUG_RETCODE("GetTXNDebugMode", OK);
    }

    if(!memcmp(szParaBuf, ENABLE, sizeof(ENABLE)))
    {
        *pbyDebugMode = 1; // Protocol Mode Enabled
        DEBUG_INFO("TXNDebugMode Enabled");
    }
    else
    {
        *pbyDebugMode = 0; // Protocol Mode Disabled
        DEBUG_INFO(" TXNDebugMode Disabled");
    }

    return DEBUG_EXIT("GetTXNDebugMode", OK); // Enable Debug Mode for Menu module.
}

/**
 * LoadIPParam
 * 
 * Function:
 *      Load IP param from nickel configer xml file.
 * 
 * @Param
 *      wIPType - IP type.
 * 
 * @return 
 *      OK - Load IP parameters successful;
 *      Other values - please refer to the <ErrorCode.h>
 * 
 */
WORD CParamReader::LoadIPParam(WORD wIPType)
{
    DEBUG_ENTRY("LoadIPParam");
    SwitchIPType(wIPType); 
    m_wCurIPType = wIPType;

    //Read IP from NikelCFG
    WORD wRet = ReadXMLData((char*)NICKEL_CFG_XML_NAME, (char*)NICKEL_CFG_IP_NODE,
                            m_szIPNodeName, (char*)NICKEL_CFG_VALUE,
                            m_szIP, sizeof(m_szIP));
    if(wRet != OK)
        return DEBUG_RETCODE("ERROR: ReadXMLData Error", wRet);

    // Check ip format
    if(INADDR_NONE == inet_addr(m_szIP))
    {
        DEBUG_INFO("Error: Host ip format error, error data is %s", m_szIP);
        return DEBUG_RETCODE("LoadIPParam", ERROR_INVALID_PARAM);
    }
    
    CHAR szAppBuff[16] = {0};
    CHAR szIPKeyBuff[16] = {0};
    CHAR szPortKeyBuff[16] = {0};
    
    WORD wCommType = CommType();
    switch(wCommType)
    {
        case COMMTYPE_ETH:
            memcpy(szAppBuff, ETH_CONFIG, sizeof(ETH_CONFIG));
            memcpy(szIPKeyBuff, ETH_P_HOSTIP, sizeof(ETH_P_HOSTIP));
            memcpy(szPortKeyBuff, ETH_P_HOSTPORT, sizeof(ETH_P_HOSTPORT));
            break;
            
        case COMMTYPE_WIFI:
            memcpy(szAppBuff, WIFI_CONFIG, sizeof(WIFI_CONFIG));
            memcpy(szIPKeyBuff, WIFI_P_HOSTIP, sizeof(WIFI_P_HOSTIP));
            memcpy(szPortKeyBuff, WIFI_P_PORT, sizeof(WIFI_P_PORT));
            break;
            
        case COMMTYPE_GPRS:
            memcpy(szAppBuff, GPRS_CONFIG, sizeof(GPRS_CONFIG));
            memcpy(szIPKeyBuff, GPRS_P_HOSTIP, sizeof(GPRS_P_HOSTIP));
            memcpy(szPortKeyBuff, GPRS_P_PORT, sizeof(GPRS_P_PORT));
            break;
    }

    //Write IP to CastlesPay 
    wRet = WriteXMLData((char*)DEF_CONFIG_FILE_PATH, 
                        (char*)DEF_CONFIG_XML_COMM_NODE, 
                        szAppBuff, szIPKeyBuff, m_szIP);

    //Read Port from NikelCFG
    wRet = ReadXMLData((char*)NICKEL_CFG_XML_NAME, (char*)NICKEL_CFG_IP_NODE,
                       m_szPortNodeName, (char*)NICKEL_CFG_VALUE,
                       m_szPort, sizeof(m_szPort));
    if(wRet != OK)
        return DEBUG_RETCODE("ERROR: ReadXMLData Error", wRet);

    // Check port format
    if(atoi(m_szPort) < MIN_PORT_NUMBER ||
       atoi(m_szPort) > MAX_PORT_NUMBER)
    {
        DEBUG_INFO("Error: Host port number error, error data is %s", m_szPort);
        return DEBUG_RETCODE("VerifyConfiguration", ERROR_INVALID_PARAM);
    }

    //Write port to CastlesPay 
    wRet = WriteXMLData((char*)DEF_CONFIG_FILE_PATH, 
                        (char*)DEF_CONFIG_XML_COMM_NODE, 
                        szAppBuff, szPortKeyBuff, m_szPort);

    return DEBUG_EXIT("LoadIPParam", OK);
}

/**
 * ReadXMLData
 * 
 * Function:
 *      Read data from speciafic node of configer xml file.
 * 
 * @Param
 *      [IN]pcstrFileName: The name of xml file
 *      [IN]pcstrMenuNode:The name of menu node
 *      [IN]pcstrKeyName: The Key name of the xml file need to open
 *      [IN]pcstrAppName: The App name of the xml file need to open
 *      [IN]uBufLen: The length of buffer
 *      [OUT]pcstrValBuf: A buffer to store data read from special node
 * 
 * @return 
 *      OK - Read XML data successful;
 *      Other values - please refer to the <ErrorCode.h>
 * 
 */
WORD CParamReader::ReadXMLData(_IN_ PCSTR pcstrFileName, _IN_ PCSTR pcstrMenuNode,
                               _IN_ PCSTR pcstrAppName, _IN_ PCSTR pcstrKeyName,
                               _OUT_ PSTR pstrValBuf, _IN_ WORD uBufLen)
{
    DEBUG_ENTRY("ReadXMLData");
    if(pcstrAppName == NULL || pcstrKeyName == NULL || pstrValBuf == NULL ||
       pcstrFileName == NULL || pcstrMenuNode == NULL || uBufLen == 0)
    {
        return DEBUG_RETCODE("ReadXml Param error", ERROR_INVALID_PARAM);
    }

    CProfile cProfile((PSTR)pcstrFileName, (PSTR)pcstrMenuNode);

    WORD wRet = cProfile.OpenConfigFile();
    if(OK != wRet)
    {
        return DEBUG_RETCODE("Open Confige File failed", wRet);
    }

    wRet = cProfile.GetKeyValue(pcstrAppName, pcstrKeyName, "", pstrValBuf, uBufLen);
    if(OK != wRet)
    {
        DEBUG_INFO("Get %s failed", pcstrKeyName);
        return DEBUG_RETCODE("Return ", wRet);
    }

    DEBUG_INFO("Read from xml is %s", pstrValBuf);

    wRet = cProfile.CloseConfigFile();
    if(OK != wRet)
    {
        return DEBUG_RETCODE("Close Confige File failed", wRet);
    }

    return DEBUG_EXIT("ReadXMLData", OK);
}

/**
 * WriteXMLData
 * 
 * Function:
 *      Write data into speciafic node of configer xml file.
 * 
 * @Param
 *      [IN]pcstrFileName: The name of xml file
 *      [IN]pcstrMenuNode:The name of menu node
 *      [IN]pcstrKeyName: The Key name of the xml file need to open
 *      [IN]pcstrAppName: The App name of the xml file need to open
 *      [OUT]pcstrValBuf: A buffer to store data read from special node
 * 
 * @return 
 *      OK - Write XML data successful;
 *      Other values - please refer to the <ErrorCode.h>
 * 
 */
WORD CParamReader::WriteXMLData(_IN_ PCSTR pcstrFileName, _IN_ PCSTR pcstrMenuNode,
                                _IN_ PCSTR pcstrAppName, _IN_ PCSTR pcstrKeyName,
                                _IN_ PCSTR pcstrInValBuf)
{
    DEBUG_ENTRY("WriteXMLData");
    if(pcstrFileName == NULL || pcstrMenuNode == NULL ||
       pcstrAppName == NULL || pcstrKeyName == NULL ||
       pcstrInValBuf == NULL)
    {
        return DEBUG_RETCODE("WriteXml Param error", ERROR_INVALID_PARAM);
    }

    CProfile cProfile((PSTR)pcstrFileName, (PSTR)pcstrMenuNode);

    WORD wRet = cProfile.OpenConfigFile();
    if(OK != wRet)
    {
        return DEBUG_RETCODE("Open Confige File failed", wRet);
    }

    DEBUG_INFO("Write into xml is %s", pcstrInValBuf);

    wRet = cProfile.SetKeyValue(pcstrAppName, pcstrKeyName, pcstrInValBuf);
    if(OK != wRet)
    {
        DEBUG_INFO("Set %s failed", pcstrKeyName);
        return DEBUG_RETCODE("Return ", wRet);
    }

    wRet = cProfile.CloseConfigFile();
    if(OK != wRet)
    {
        return DEBUG_RETCODE("Close Confige File failed", wRet);
    }

    return DEBUG_EXIT("WriteXMLData", OK);
}


/**
 * WriteXMLData
 * 
 * Function:
 *      Write data into speciafic node of configer xml file.
 * 
 * @Param
 *      [IN]pcstrFileName: The name of xml file
 *      [IN]pcstrMenuNode:The name of menu node
 *      [IN]pcstrKeyName: The Key name of the xml file need to open
 *      [IN]pcstrAppName: The App name of the xml file need to open
 *      [OUT]pcstrValBuf: A buffer to store data read from special node
 * 
 * @return 
 *      OK - Write XML data successful;
 *      Other values - please refer to the <ErrorCode.h>
 * 
 */
void CParamReader::SwitchIPType(WORD wIPType)
{
    switch(wIPType)
    {
        case PRIMARY_IP:
            memcpy(m_szIPNodeName, NICKEL_CFG_IP01, sizeof(NICKEL_CFG_IP01));
            memcpy(m_szPortNodeName, NICKEL_CFG_IP02, sizeof(NICKEL_CFG_IP02));
            break;

        case SECONDARY_IP:
            memcpy(m_szIPNodeName, NICKEL_CFG_IP03, sizeof(NICKEL_CFG_IP03));
            memcpy(m_szPortNodeName, NICKEL_CFG_IP04, sizeof(NICKEL_CFG_IP04));
            break;

        case VENDING_IP:
            memcpy(m_szIPNodeName, NICKEL_CFG_IP05, sizeof(NICKEL_CFG_IP05));
            memcpy(m_szPortNodeName, NICKEL_CFG_IP06, sizeof(NICKEL_CFG_IP06));
            break;

        default:
            break;
    }
}

/**
 * CommType
 * 
 * Function:
 *      Return default communication type.
 * 
 * @Param
 * 
 * 
 * @return 
 *      OK - Get default communication type successful;
 *      Other values - please refer to the <ErrorCode.h>
 */
WORD CParamReader::CommType(void)
{
    DEBUG_ENTRY("CommType");
    CHAR szComType[16] = {0};
    WORD wRet = ReadXMLData((char*)DEF_CONFIG_FILE_PATH, (char*)CONFIG_XML_PLATFORM_NODE,
                            (char*)PF_DEF_COMM_TYPE, (char*)PF_COMM_TYPE,
                            szComType, sizeof(szComType));
    if(wRet != OK)
        return DEBUG_RETCODE("ERROR: ReadXMLData Error", wRet);

    if(memcpy(szComType, "ETH", sizeof("ETH")))
    {
        return DEBUG_RETCODE("COMMTYPE_ETH ", COMMTYPE_ETH);
    }
    else if(memcpy(szComType, "WIFI", sizeof("WIFI")))
    {
        return DEBUG_RETCODE("COMMTYPE_WIFI ", COMMTYPE_WIFI);
    }
    else if(memcpy(szComType, "GPRS", sizeof("GPRS")))
    {
        return DEBUG_RETCODE("COMMTYPE_GPRS ", COMMTYPE_GPRS);
    }
}

/**
 * GetCurrentIP
 * 
 * Function:
 *      Return current IP type.
 * 
 * @Param
 * 
 * @return 
 *      OK - Get IP type successful;
 *      Other values - please refer to the <ErrorCode.h>
 */
WORD CParamReader::GetCurrentIP()
{
    return m_wCurIPType;
}

/**
 * GetRetryParam
 * 
 * Function:
 *      Get retry parameters.
 *      RE01 - message retry times
 *      RE02 - message retry timeout
 *      RE03 - session retry times
 *      RE04 - session retry timeout
 * 
 * @Param
 * 
 * @return 
 *      OK - Get retry parameters successful;
 *      Other values - please refer to the <ErrorCode.h>
 */
WORD CParamReader::GetRetryParam(_IN_ WORD wReParam)
{
    CHAR szReParam[16] = {0};
    CHAR szNode[16] = {0};
    
    switch(wReParam)
    {
        case RE01:
            memcpy(szNode, NICKEL_CFG_RE01, sizeof(NICKEL_CFG_RE01));
            break;
            
        case RE02:
            memcpy(szNode, NICKEL_CFG_RE02, sizeof(NICKEL_CFG_RE02));
            break;
            
        case RE03:
            memcpy(szNode, NICKEL_CFG_RE03, sizeof(NICKEL_CFG_RE03));
            break;
            
        case RE04:
            memcpy(szNode, NICKEL_CFG_RE04, sizeof(NICKEL_CFG_RE04));
            break;
            
        default:
            break;
    }
    
    WORD wRet = ReadXMLData((char*)NICKEL_CFG_XML_NAME, (char*)NICKEL_CFG_RETRY_NODE,
                            szNode, (char*)NICKEL_CFG_VALUE,
                            szReParam, sizeof(szReParam));
    
    if(wRet != OK)
    {
        DEBUG_INFO("ERROR: ReadXMLData Error. 0x%04x", wRet);
        return wRet;
    }
    
    CFunBase cFunBase;
    
    return cFunBase.ASCIIToDec(szReParam);
}

/**
 * GerCRTNParam
 * 
 * Function:
 *      Get CRTN parameters.
 *      Please refer to <ICGN Cashless Vending Configuration V1.3.5.pdf>
 * 
 * @Param
 * 
 * @return 
 *      OK - Get retry parameters successful;
 *      Other values - please refer to the <ErrorCode.h>
 */
WORD CParamReader::GetCNTRParam(WORD wParamType)
{
    CHAR szCNTRParam[16] = {0};
    CHAR szNode[16] = {0};
    
    switch(wParamType)
    {
        case CN01:
            memcpy(szNode, NICKEL_CFG_CN01, sizeof(NICKEL_CFG_CN01));
            break;
            
        case CN02:
            memcpy(szNode, NICKEL_CFG_CN02, sizeof(NICKEL_CFG_CN02));
            break;
            
        case CN03:
            memcpy(szNode, NICKEL_CFG_CN03, sizeof(NICKEL_CFG_CN03));
            break;
            
        case CN04:
            memcpy(szNode, NICKEL_CFG_CN04, sizeof(NICKEL_CFG_CN04));
            break;
            
        case CN05:
            memcpy(szNode, NICKEL_CFG_CN05, sizeof(NICKEL_CFG_CN05));
            break;
            
        case CN06:
            memcpy(szNode, NICKEL_CFG_CN06, sizeof(NICKEL_CFG_CN06));
            break;
            
        case CN07:
            memcpy(szNode, NICKEL_CFG_CN07, sizeof(NICKEL_CFG_CN07));
            break;
            
        case CN08:
            memcpy(szNode, NICKEL_CFG_CN08, sizeof(NICKEL_CFG_CN08));
            break;
            
        case CN09:
            memcpy(szNode, NICKEL_CFG_CN09, sizeof(NICKEL_CFG_CN09));
            break;
            
        case CN10:
            memcpy(szNode, NICKEL_CFG_CN10, sizeof(NICKEL_CFG_CN10));
            break;
            
        case CN11:
            memcpy(szNode, NICKEL_CFG_CN11, sizeof(NICKEL_CFG_CN11));
            break;
            
        case CN12:
            memcpy(szNode, NICKEL_CFG_CN12, sizeof(NICKEL_CFG_CN12));
            break;
            
        case CN13:
            memcpy(szNode, NICKEL_CFG_CN13, sizeof(NICKEL_CFG_CN13));
            break;
            
        case CN14:
            memcpy(szNode, NICKEL_CFG_CN14, sizeof(NICKEL_CFG_CN14));
            break;
            
        default:
            break;
    }
    
    WORD wRet = ReadXMLData((char*)NICKEL_CFG_XML_NAME, (char*)NICKEL_CFG_CNTR_NODE,
                            szNode, (char*)NICKEL_CFG_VALUE,
                            szCNTRParam, sizeof(szCNTRParam));
    
    if(wRet != OK)
    {
        DEBUG_INFO("ERROR: ReadXMLData Error. 0x%04x", wRet);
        return wRet;
    }
//        return DEBUG_RETCODE("ERROR: ReadXMLData Error", wRet);
    
    CFunBase cFunBase;
    
    return cFunBase.ASCIIToDec(szCNTRParam);
}

///////////////////////////////////////////////////////////////
// SetCNTRParam
//
// Function: Set data to configuration by input data.
//
// @param 
//       [IN] cInData - Input data . (CN01,10,CN02,1,CN03,1,CN04,0)     
//
//
// @return 
//      OK - Set successfully,
//      Other - Please refer to the ErrorCode
//
// @Author Silas Wei
//
///////////////////////////////////////////////////////////////
WORD CParamReader::SetCNTRParam(CByteStream cInData)
{
    DEBUG_ENTRY("SetCNTRParam");
    
    cInData.PushZero();
    WORD wRet = 0;
    INT nDataLen = 0;
    CByteStream cAppName, cValue, cMenuNode;
    nDataLen = cInData.GetLength();
    PBYTE pbyStart = cInData.GetBuffer();
    PBYTE pbyEnd = pbyStart + nDataLen;  
    
    while(pbyStart < pbyEnd)
    {   
        cAppName.Empty();
        cValue.Empty();
        while(*pbyStart != 0x2C)
        {   DEBUG_INFO("*pbyStart is %02x", *pbyStart);        
            cAppName << (BYTE)(*pbyStart);
            pbyStart++;
        }
        DEBUG_STREAM(&cAppName, "=====cAppName is");
        pbyStart++;
        
        while((*pbyStart != 0x2C) && (*pbyStart != 0x00))
        {   DEBUG_INFO("*pbyStart is %02x", *pbyStart);    
            cValue << (BYTE)(*pbyStart);
            pbyStart++;
            DEBUG_INFO("*pbyStart is %02x", *pbyStart);
        }        
        pbyStart++;
        DEBUG_STREAM(&cValue, "=====cValue is");
        
        wRet = GetXMLMenuNode(cAppName, cMenuNode);
        if(wRet != OK)
        {
            DEBUG_INFO("ERROR: GetXMLMenuNode Error. 0x%04x", wRet);
            return DEBUG_RETCODE("ERROR: GetXMLMenuNode fail", wRet);
        }
        wRet = WriteXMLData((char*)NICKEL_CFG_XML_NAME, (PCSTR)cMenuNode.GetBuffer(),
                      (PCSTR)cAppName.GetBuffer(), (char*)NICKEL_CFG_VALUE, cValue.PushZero());    
        if(wRet != OK)
        {
            DEBUG_INFO("ERROR: WriteXMLData Error. 0x%04x", wRet);
            return DEBUG_RETCODE("ERROR: WriteXMLData fail", wRet);
        }
    }    
    
    return DEBUG_EXIT("SetCNTRParam", OK);
}

///////////////////////////////////////////////////////////////
// GetXMLMenuNode
//
// Function: Get MunuNode by input data.
//
// @param 
//       [IN] cInData - Input data . (CN01,10,CN02,1,CN03,1,CN04,0)     
//       [OUT]cMenuNode - MenuNOde
//
// @return 
//      OK - Get successfully,
//      Other - Please refer to the ErrorCode
//
// @Author Silas Wei
//
///////////////////////////////////////////////////////////////
WORD CParamReader::GetXMLMenuNode(CByteStream cInData, CByteStream &cMenuNode)
{
    DEBUG_ENTRY("GetXMLMenuNode");    
    
    cMenuNode.Empty();
    CByteStream cTemp;
    cTemp.Write(cInData.GetBuffer(), 2);
    DEBUG_STREAM(&cTemp, "====cTemp is");
    if (0 == memcmp(cTemp.GetBuffer(), "IP", 2))
    {
        cMenuNode << "IP_Config";
    }
    else if (0 == memcmp(cTemp.GetBuffer(), "ST", 2))
    {
        cMenuNode << "Local_Config";
    }
    else if ((0 == memcmp(cTemp.GetBuffer(), "VI", 2)) ||
             (0 == memcmp(cTemp.GetBuffer(), "MC", 2)) ||
             (0 == memcmp(cTemp.GetBuffer(), "AX", 2)) ||
             (0 == memcmp(cTemp.GetBuffer(), "DS", 2)) ||
             (0 == memcmp(cTemp.GetBuffer(), "GT", 2)) ||
             (0 == memcmp(cTemp.GetBuffer(), "LC", 2)) ||
             (0 == memcmp(cTemp.GetBuffer(), "TC", 2)) ||
             (0 == memcmp(cTemp.GetBuffer(), "DC", 2)) ||
             (0 == memcmp(cTemp.GetBuffer(), "OM", 2)) ||
             (0 == memcmp(cTemp.GetBuffer(), "AD", 2)) ||
             (0 == memcmp(cTemp.GetBuffer(), "UD", 2)) ||
             (0 == memcmp(cTemp.GetBuffer(), "CC", 2)))
    {
        cMenuNode << "Card_BinRange_Config";
    }
    else if (0 == memcmp(cTemp.GetBuffer(), "RE", 2))
    {
        cMenuNode << "Retry_Config";
    }
    else if (0 == memcmp(cTemp.GetBuffer(), "CN", 2))
    {
        cMenuNode << "CNTR_Config";
    }
    else if (0 == memcmp(cTemp.GetBuffer(), "VE", 2))
    {
        cMenuNode << "VEND_Config";
    }
    else if (0 == memcmp(cTemp.GetBuffer(), "AP", 2))
    {
        cMenuNode << "APN_Config";
    }
    else if (0 == memcmp(cTemp.GetBuffer(), "FW", 2))
    {
        cMenuNode << "FW_Config";
    }
    else if (0 == memcmp(cTemp.GetBuffer(), "EC", 2))
    {
        cMenuNode << "ECHO_Config";
    }
    else if (0 == memcmp(cTemp.GetBuffer(), "CS", 2))
    {
        cMenuNode << "Customer_Config";
    }
    else if (0 == memcmp(cTemp.GetBuffer(), "CO", 2))
    {
        cMenuNode << "Config_Config";
    }
            
    cMenuNode.PushZero();
    DEBUG_INFO("cMenuNode is== %s", cMenuNode.GetBuffer());    
    
    return DEBUG_EXIT("GetXMLMenuNode", OK);
}

///////////////////////////////////////////////////////////////
// GetCC02Param
//
// Function: Get CC02 value from Card_BinRange_Config.
//
// @param 
//          
//       [OUT]cOutData - the value of return
//
// @return 
//      OK - Get successfully,
//      Other - Please refer to the ErrorCode
//
// @Author Silas Wei
//
///////////////////////////////////////////////////////////////
WORD CParamReader::GetCC02Param(CByteStream &cOutData)
{
    DEBUG_ENTRY("GetCC02Param");
    
    CHAR szCNTRParam[32] = {0};   
    cOutData.Empty();
    
    WORD wRet = ReadXMLData((char*)NICKEL_CFG_XML_NAME, (char*)NICKEL_CFG_CARDBIN_NODE,
                            (char*)NICKEL_CFG_CC02, (char*)NICKEL_CFG_VALUE,
                            szCNTRParam, sizeof(szCNTRParam));
    
    if(wRet != OK)
    {
        DEBUG_INFO("ERROR: ReadXMLData Error. 0x%04x", wRet);
        return DEBUG_RETCODE("ERROR:ReadXMLData fail ", wRet);
    }
    
    cOutData.Write(szCNTRParam, sizeof(szCNTRParam));
    DEBUG_STREAM(&cOutData, "====cOutData is");
    
    return DEBUG_EXIT("GetCC02Param", OK);
}

///////////////////////////////////////////////////////////////
// GetVENDParam
//
// Function: Get Vendparam value from VEND_Config by paramType.
//
// @param 
//       [IN] wParamType - param type
//       [OUT]cOutData - the value of return
//
// @return 
//      OK - Get successfully,
//      Other - Please refer to the ErrorCode
//
// @Author Silas Wei
//
///////////////////////////////////////////////////////////////
WORD CParamReader::GetVENDParam(WORD wParamType, CByteStream &cOutData)
{
    DEBUG_ENTRY("GetVENDParam");
    
    CHAR szCNTRParam[32] = {0};
    CHAR szNode[16] = {0};
    cOutData.Empty();
    
    switch(wParamType)
    {
        case VE01:
            memcpy(szNode, NICKEL_CFG_VE01, sizeof(NICKEL_CFG_VE01));
            break;
            
        case VE02:
            memcpy(szNode, NICKEL_CFG_VE02, sizeof(NICKEL_CFG_VE02));
            break;
            
        case VE03:
            memcpy(szNode, NICKEL_CFG_VE03, sizeof(NICKEL_CFG_VE03));
            break;
            
        case VE04:
            memcpy(szNode, NICKEL_CFG_VE04, sizeof(NICKEL_CFG_VE04));
            break;
            
        case VE05:
            memcpy(szNode, NICKEL_CFG_VE05, sizeof(NICKEL_CFG_VE05));
            break;
            
        case VE06:
            memcpy(szNode, NICKEL_CFG_VE06, sizeof(NICKEL_CFG_VE06));
            break;
            
        case VE07:
            memcpy(szNode, NICKEL_CFG_VE07, sizeof(NICKEL_CFG_VE07));
            break;
            
        case VE08:
            memcpy(szNode, NICKEL_CFG_VE08, sizeof(NICKEL_CFG_VE08));
            break;
            
        case VE09:
            memcpy(szNode, NICKEL_CFG_VE09, sizeof(NICKEL_CFG_VE09));
            break;
            
        case VE10:
            memcpy(szNode, NICKEL_CFG_VE10, sizeof(NICKEL_CFG_VE10));
            break;
            
        case VE11:
            memcpy(szNode, NICKEL_CFG_VE11, sizeof(NICKEL_CFG_VE11));
            break;
            
        default:
            break;
    }
    
    WORD wRet = ReadXMLData((char*)NICKEL_CFG_XML_NAME, (char*)NICKEL_CFG_VEND_NODE,
                            szNode, (char*)NICKEL_CFG_VALUE,
                            szCNTRParam, sizeof(szCNTRParam));
    
    if(wRet != OK)
    {
        DEBUG_INFO("ERROR: ReadXMLData Error. 0x%04x", wRet);
        return DEBUG_RETCODE("ERROR:ReadXMLData fail", wRet);
    }
    
    cOutData.Write(szCNTRParam, sizeof(szCNTRParam));
    DEBUG_STREAM(&cOutData, "====cOutData is");
    
    return DEBUG_EXIT("GetVENDParam", OK);
        
}

///////////////////////////////////////////////////////////////
// GetAPNParam
//
// Function: Get Apnparam value from APN_Config by paramType.
//
// @param 
//       [IN] wParamType - param type
//       [OUT]cOutData - the value of return
//
// @return 
//      OK - Get successfully,
//      Other - Please refer to the ErrorCode
//
// @Author Silas Wei
//
///////////////////////////////////////////////////////////////
WORD CParamReader::GetAPNParam(WORD wParamType, CByteStream &cOutData)
{
    DEBUG_ENTRY("GetAPNParam");
    
    CHAR szCNTRParam[32] = {0};
    CHAR szNode[16] = {0};
    cOutData.Empty();
    
    switch(wParamType)
    {
        case AP01:
            memcpy(szNode, NICKEL_CFG_AP01, sizeof(NICKEL_CFG_AP01));
            break;
            
        case AP02:
            memcpy(szNode, NICKEL_CFG_AP02, sizeof(NICKEL_CFG_AP02));
            break;
            
        case AP03:
            memcpy(szNode, NICKEL_CFG_AP03, sizeof(NICKEL_CFG_AP03));
            break;
            
        case AP04:
            memcpy(szNode, NICKEL_CFG_AP04, sizeof(NICKEL_CFG_AP04));
            break;
            
        case AP05:
            memcpy(szNode, NICKEL_CFG_AP05, sizeof(NICKEL_CFG_AP05));
            break;
            
        case AP06:
            memcpy(szNode, NICKEL_CFG_AP06, sizeof(NICKEL_CFG_AP06));
            break;
            
        default:
            break;
    }
    
    WORD wRet = ReadXMLData((char*)NICKEL_CFG_XML_NAME, (char*)NICKEL_CFG_APN_NODE,
                            szNode, (char*)NICKEL_CFG_VALUE,
                            szCNTRParam, sizeof(szCNTRParam));
    
    if(wRet != OK)
    {
        DEBUG_INFO("ERROR: ReadXMLData Error. 0x%04x", wRet);
        return DEBUG_RETCODE("ERROR:ReadXMLData fail", wRet);
    }
    
    cOutData.Write(szCNTRParam, sizeof(szCNTRParam));
    DEBUG_STREAM(&cOutData, "====cOutData is");
    
    return DEBUG_EXIT("GetAPNParam", OK);
        
}

///////////////////////////////////////////////////////////////
// GetFWParam
//
// Function: Get FWparam value from FW_Config by paramType.
//
// @param 
//       [IN] wParamType - param type
//       [OUT]cOutData - the value of return
//
// @return 
//      OK - Get successfully,
//      Other - Please refer to the ErrorCode
//
// @Author Silas Wei
//
///////////////////////////////////////////////////////////////
WORD CParamReader::GetFWParam(WORD wParamType, CByteStream &cOutData)
{
    DEBUG_ENTRY("GetFWParam");
    
    CHAR szCNTRParam[32] = {0};
    CHAR szNode[16] = {0};
    cOutData.Empty();
    
    switch(wParamType)
    {
        case FW01:
            memcpy(szNode, NICKEL_CFG_FW01, sizeof(NICKEL_CFG_FW01));
            break;
            
        case FW02:
            memcpy(szNode, NICKEL_CFG_FW02, sizeof(NICKEL_CFG_FW02));
            break;
            
        case FW03:
            memcpy(szNode, NICKEL_CFG_FW03, sizeof(NICKEL_CFG_FW03));
            break;
            
        case FW04:
            memcpy(szNode, NICKEL_CFG_FW04, sizeof(NICKEL_CFG_FW04));
            break;
            
        case FW05:
            memcpy(szNode, NICKEL_CFG_FW05, sizeof(NICKEL_CFG_FW05));
            break;
            
        case FW06:
            memcpy(szNode, NICKEL_CFG_FW06, sizeof(NICKEL_CFG_FW06));
            break;
            
        case FW07:
            memcpy(szNode, NICKEL_CFG_FW07, sizeof(NICKEL_CFG_FW07));
            break;

        case FW08:
            memcpy(szNode, NICKEL_CFG_FW08, sizeof(NICKEL_CFG_FW08));
            break;

        case FW09:
            memcpy(szNode, NICKEL_CFG_FW09, sizeof(NICKEL_CFG_FW09));
            break;
            
        default:
            break;
    }
    
    WORD wRet = ReadXMLData((char*)NICKEL_CFG_XML_NAME, (char*)NICKEL_CFG_FW_NODE,
                            szNode, (char*)NICKEL_CFG_VALUE,
                            szCNTRParam, sizeof(szCNTRParam));
    
    if(wRet != OK)
    {
        DEBUG_INFO("ERROR: ReadXMLData Error. 0x%04x", wRet);
        return DEBUG_RETCODE("ERROR:ReadXMLData fail", wRet);
    }
    
    cOutData.Write(szCNTRParam, sizeof(szCNTRParam));
    DEBUG_STREAM(&cOutData, "====cOutData is");
    
    return DEBUG_EXIT("GetFWParam", OK);
        
}

///////////////////////////////////////////////////////////////
// GetECHOParam
//
// Function: Get ECHOparam value from ECHO_Config by paramType.
//
// @param 
//       [IN] wParamType - param type
//       [OUT]cOutData - the value of return
//
// @return 
//      OK - Get successfully,
//      Other - Please refer to the ErrorCode
//
// @Author Silas Wei
//
///////////////////////////////////////////////////////////////
WORD CParamReader::GetECHOParam(WORD wParamType, CByteStream &cOutData)
{
    DEBUG_ENTRY("GetECHOParam");
    
    CHAR szCNTRParam[32] = {0};
    CHAR szNode[16] = {0};
    cOutData.Empty();
    
    switch(wParamType)
    {
        case EC01:
            memcpy(szNode, NICKEL_CFG_EC01, sizeof(NICKEL_CFG_EC01));
            break;
            
        case EC02:
            memcpy(szNode, NICKEL_CFG_EC02, sizeof(NICKEL_CFG_EC02));
            break; 
            
        default:
            break;
    }
    
    WORD wRet = ReadXMLData((char*)NICKEL_CFG_XML_NAME, (char*)NICKEL_CFG_ECHO_NODE,
                            szNode, (char*)NICKEL_CFG_VALUE,
                            szCNTRParam, sizeof(szCNTRParam));
    
    if(wRet != OK)
    {
        DEBUG_INFO("ERROR: ReadXMLData Error. 0x%04x", wRet);
        return DEBUG_RETCODE("ERROR:ReadXMLData fail", wRet);
    }
    
    cOutData.Write(szCNTRParam, sizeof(szCNTRParam));
    DEBUG_STREAM(&cOutData, "====cOutData is");
    
    return DEBUG_EXIT("GetECHOParam", OK);
        
}

///////////////////////////////////////////////////////////////
// GetCustomerParam
//
// Function: Get Customerparam value from Customer_Config by paramType.
//
// @param 
//       [IN] wParamType - param type
//       [OUT]cOutData - the value of return
//
// @return 
//      OK - Get successfully,
//      Other - Please refer to the ErrorCode
//
// @Author Silas Wei
//
///////////////////////////////////////////////////////////////
WORD CParamReader::GetCustomerParam(WORD wParamType, CByteStream &cOutData)
{
    DEBUG_ENTRY("GetCustomerParam");
    
    CHAR szCNTRParam[32] = {0};
    CHAR szNode[16] = {0};
    cOutData.Empty();
    
    switch(wParamType)
    {
        case CS01:
            memcpy(szNode, NICKEL_CFG_CS01, sizeof(NICKEL_CFG_CS01));
            break;
            
        case CS02:
            memcpy(szNode, NICKEL_CFG_CS02, sizeof(NICKEL_CFG_CS02));
            break; 
            
        case CS03:
            memcpy(szNode, NICKEL_CFG_CS03, sizeof(NICKEL_CFG_CS03));
            break;
            
        case CS04:
            memcpy(szNode, NICKEL_CFG_CS04, sizeof(NICKEL_CFG_CS04));
            break;
            
        case CS05:
            memcpy(szNode, NICKEL_CFG_CS05, sizeof(NICKEL_CFG_CS05));
            break; 
            
        case CS06:
            memcpy(szNode, NICKEL_CFG_CS06, sizeof(NICKEL_CFG_CS06));
            break;
            
        case CS07:
            memcpy(szNode, NICKEL_CFG_CS07, sizeof(NICKEL_CFG_CS07));
            break;
            
        case CS08:
            memcpy(szNode, NICKEL_CFG_CS08, sizeof(NICKEL_CFG_CS08));
            break;
            
        case CS09:
            memcpy(szNode, NICKEL_CFG_CS09, sizeof(NICKEL_CFG_CS09));
            break; 
            
        case CS10:
            memcpy(szNode, NICKEL_CFG_CS10, sizeof(NICKEL_CFG_CS10));
            break;
            
        default:
            break;
    }
    
    WORD wRet = ReadXMLData((char*)NICKEL_CFG_XML_NAME, (char*)NICKEL_CFG_CUSTOMER_NODE,
                            szNode, (char*)NICKEL_CFG_VALUE,
                            szCNTRParam, sizeof(szCNTRParam));
    
    if(wRet != OK)
    {
        DEBUG_INFO("ERROR: ReadXMLData Error. 0x%04x", wRet);
        return DEBUG_RETCODE("ERROR:ReadXMLData fail", wRet);
    }
    
    cOutData.Write(szCNTRParam, sizeof(szCNTRParam));
    DEBUG_STREAM(&cOutData, "====cOutData is");
    
    return DEBUG_EXIT("GetCustomerParam", OK);
        
}

///////////////////////////////////////////////////////////////
// GetConfigParam
//
// Function: Get Configparam value from Config_Config by paramType.
//
// @param 
//       [IN] wParamType - param type
//       [OUT]cOutData - the value of return
//
// @return 
//      OK - Get successfully,
//      Other - Please refer to the ErrorCode
//
// @Author Silas Wei
//
///////////////////////////////////////////////////////////////
WORD CParamReader::GetConfigParam(WORD wParamType, CByteStream &cOutData)
{
    DEBUG_ENTRY("GetConfigParam");
    
    CHAR szCNTRParam[32] = {0};
    CHAR szNode[16] = {0};
    cOutData.Empty();
    
    switch(wParamType)
    {
        case CO01:
            memcpy(szNode, NICKEL_CFG_CO01, sizeof(NICKEL_CFG_CO01));
            break;
            
        case CO02:
            memcpy(szNode, NICKEL_CFG_CO02, sizeof(NICKEL_CFG_CO02));
            break; 
            
        default:
            break;
    }
    
    WORD wRet = ReadXMLData((char*)NICKEL_CFG_XML_NAME, (char*)NICKEL_CFG_CONFIG_NODE,
                            szNode, (char*)NICKEL_CFG_VALUE,
                            szCNTRParam, sizeof(szCNTRParam));
    
    if(wRet != OK)
    {
        DEBUG_INFO("ERROR: ReadXMLData Error. 0x%04x", wRet);
        return DEBUG_RETCODE("ERROR:ReadXMLData fail", wRet);
    }
    
    cOutData.Write(szCNTRParam, sizeof(szCNTRParam));
    DEBUG_STREAM(&cOutData, "====cOutData is");
    
    return DEBUG_EXIT("GetConfigParam", OK);
        
}
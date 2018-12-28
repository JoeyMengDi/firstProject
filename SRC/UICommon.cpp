/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "../SRC/StdafxHead.h"
#include "../SRC/CPCommon.h"
#include "../SRC/UICommon.h"

#include "../SRC/ErrorCode.h"
#include "../SRC/Profile.h"
#include "../SRC/FunBase.h"

#define BUF_LEN                32
    
/**
 * DisplayPage : This function is use to display the UI.
 * 
 * @param pszApp         The App name of the xml file need to Read
 * @param pszKeyList    The Key name of the xml file need to Read
 * @param byLineNum  The number of lines that need to display 
 * 
 * @return 
 */
WORD DisplayPage(_IN_ PCSTR pszFilePath, _IN_ PCSTR pszNode, _IN_ PCSTR pszApp, _IN_ const char (*pszKeyList)[32], BYTE byLineNum)
{
    DEBUG_ENTRY("DisplayPage");
    
    if(pszApp == NULL || pszKeyList == NULL || byLineNum == 0)
    {
        return DEBUG_RETCODE("DisplayPage Ret:", ERROR_INVALID_PARAM);
    }
        
    //CProfile cProfile((PSTR)UI_CONFIG_PATH, (PSTR)CONFIG_UI_TYPE_NODE);
    CProfile cProfile((PSTR)pszFilePath, (PSTR)pszNode);
    CFunBase cFunBase;
    
    WORD wRet = cProfile.OpenConfigFile();
                if(wRet != OK)
                    return DEBUG_RETCODE("OpenConfigFile Failed", wRet);
    
    BYTE byValueBuf[BUF_LEN] = {0};
    BYTE byAttrBuf[BUF_LEN] = {0};
    
    for (BYTE byIndex = 0; byIndex < byLineNum; byIndex++)
    {
        memset(byAttrBuf, 0x00, sizeof(byAttrBuf));
        wRet = cProfile.GetKeyAttributeValue(pszApp, pszKeyList[byIndex], CONFIG_UI_KEY_ATTR_TYPE, (char*)byAttrBuf, BUF_LEN);
        if(wRet != OK)
            return DEBUG_RETCODE("GetKeyAttributValue Failed", wRet);
        
        if(!memcmp(byAttrBuf, CONFIG_UI_TYPE_EDIT, strlen(CONFIG_UI_TYPE_EDIT)))
        {
            //DEBUG_INFO("Skip edit line");
            continue;
        }
        else if(!memcmp(byAttrBuf, CONFIG_UI_TYPE_LABEL, strlen(CONFIG_UI_TYPE_LABEL)))
        {
            
        }
        else
        {
            return DEBUG_RETCODE("XML attribute ERROR", ERROR_INVALID_PARAM);
        }
        
        memset(byAttrBuf, 0x00, sizeof(byAttrBuf));
        wRet = cProfile.GetKeyAttributeValue(pszApp, pszKeyList[byIndex], CONFIG_UI_KEY_ATTR_ALIGN, (char*)byAttrBuf, BUF_LEN);
        if(wRet != OK)
            return DEBUG_RETCODE("GetKeyAttributValue Failed", wRet);

        //DEBUG_INFO("Attr value: %s", byAttrBuf);

        memset(byValueBuf, 0x00, sizeof(byValueBuf));
        wRet = cProfile.GetKeyValue(pszApp, pszKeyList[byIndex], "", (char*)byValueBuf, 32);
        if(wRet != OK)
            return DEBUG_RETCODE("GetKeyValue Failed", wRet);

        //DEBUG_INFO("KeyValue:%s", byValueBuf);
		
        BYTE byLine = cFunBase.ASCIIToDec((CHAR*)(pszKeyList[byIndex]+1));
        
        //DEBUG_INFO("KeyValue:%d", byLine);

        if(!memcmp(byAttrBuf, CONFIG_UI_ALIGN_LEFT, strlen(CONFIG_UI_ALIGN_LEFT)))
        {
            CTOS_LCDTPrintXY(1, byLine, byValueBuf);
        }
        else if(!memcmp(byAttrBuf, CONFIG_UI_ALIGN_RIGHT, strlen(CONFIG_UI_ALIGN_RIGHT)))
        {
            CTOS_LCDTPrintXY(1+(20 - strlen((const char*)byValueBuf)), byLine, byValueBuf);
        }
        else if(!memcmp(byAttrBuf, CONFIG_UI_ALIGN_CENTER, strlen(CONFIG_UI_ALIGN_CENTER)))
        {
            CTOS_LCDTPrintXY(1+((20 - strlen((const char*)byValueBuf)) / 2), byLine, byValueBuf);
        }
        else
        {
            DEBUG_INFO("Other option");
        }
    }
    
    wRet = cProfile.CloseConfigFile();
        if(wRet != OK)
            return DEBUG_RETCODE("Close Failed", wRet);
    
    return DEBUG_EXIT("DisplayPage, ret:", OK);
}

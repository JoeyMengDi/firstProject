
/* 
 * Copyright (c) Castles Technology Co., Ltd. 
 * 
 * File:   Profile.h
 * Author: Alan.Ren
 *
 * Created: 2017/06/21
 */
#include "StdafxHead.h"
#include "ErrorCode.h"
#include "../SRC/CPCommon.h"
//#include "../CommLib/CommBase.h"

#include "../SRC/Profile.h"
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#define MAX_PATH (256)



class CLocalPathInit
{
public:
    CLocalPathInit()
    {
        if (!CLocalPathInit::s_bInitLocalPath)
        {
            bzero(CLocalPathInit::s_szLocalPath,
                    sizeof(CLocalPathInit::s_szLocalPath));
            int nRet;
            nRet = readlink("/proc/self/exe",
                    CLocalPathInit::s_szLocalPath,
                    sizeof(CLocalPathInit::s_szLocalPath));
            if (nRet != -1)
            {
                CLocalPathInit::s_bInitLocalPath = TRUE;
            }
            else
            {
                s_errno = errno;
            }
        }
    }
    virtual ~CLocalPathInit()
    {
    }
    PCSTR GetLocalPath() const
    {
        return CLocalPathInit::s_szLocalPath;
    }
    BOOL GetInitResult() const
    {
        return CLocalPathInit::s_bInitLocalPath;
    }
    int GetErrno() const
    {
        return CLocalPathInit::s_errno;
    }

private:
    static int s_errno;
    static BOOL s_bInitLocalPath;
    static char s_szLocalPath[MAX_PATH];
};

BOOL CLocalPathInit::s_bInitLocalPath = FALSE;
int CLocalPathInit::s_errno = 0;
char CLocalPathInit::s_szLocalPath[MAX_PATH] = {0};

static CLocalPathInit cLocalPath;


/////////////////////////////////////////////////////////////////////////////////
// CProfile
// 
// Function:
//          Construct function.
//
// @param:
//          None
//
// @return:
//          None
/////////////////////////////////////////////////////////////////////////////////
CProfile::CProfile() : m_bIsInitXmlDoc(FALSE),
m_pszProfilePath(NULL),
m_pszConfigNodeName(NULL),
m_pXmlDoc(NULL)
{
    ConstructInit(DEF_CONFIG_FILE_PATH, DEF_CONFIG_XML_COMM_NODE);
}



/////////////////////////////////////////////////////////////////////////////////
// CProfile
// 
// Function:
//          Construct function.
//
// @param:
//          [IN] pszFileName: Need to open profile name.
//          [IN] pszConfigNodeName: XML config node name.
//
// @return:
//          None
/////////////////////////////////////////////////////////////////////////////////
CProfile::CProfile(_IN_ char *pszFileName, _IN_ char *pszConfigNodeName) :
m_bIsInitXmlDoc(FALSE),
m_pszProfilePath(NULL),
m_pszConfigNodeName(NULL),
m_pXmlDoc(NULL)
{
    ConstructInit(pszFileName, pszConfigNodeName);
}



/////////////////////////////////////////////////////////////////////////////////
// ConstructInit
//
// Function:
//          Initialize the path of the profile and xml node name.
//
// @param:
//          [IN] pszProfilefilePath, File path.
//          [IN] pszXmlNodeName, Xml file node element name.
//
// @return:
//          None
/////////////////////////////////////////////////////////////////////////////////
void CProfile::ConstructInit(_IN_ PCSTR pszProfilePath,
        _IN_ PCSTR pszXmlNodeName)
{
    char szTmpFilePath[MAX_PATH + 1];
    char *pChar = NULL;

    bzero(szTmpFilePath, sizeof(szTmpFilePath));
    if (cLocalPath.GetInitResult())
    {
        strcpy(szTmpFilePath, cLocalPath.GetLocalPath());
        pChar = strrchr(szTmpFilePath, '/');
        if (pChar != NULL)
        {
            *(pChar + 1) = '\0';
            const int c_nFilePathLen = strlen(szTmpFilePath) +
                    strlen(pszProfilePath) + 1;
            m_pszProfilePath = new char[c_nFilePathLen];
            if (NULL != m_pszProfilePath)
            {
                bzero(m_pszProfilePath, c_nFilePathLen);
                sprintf(m_pszProfilePath, "%s%s", szTmpFilePath,
                        pszProfilePath);
            }
        }
    }

    m_pszConfigNodeName = new char[strlen(pszXmlNodeName) + 1];
    if (NULL != m_pszConfigNodeName)
    {
        bzero(m_pszConfigNodeName, strlen(pszXmlNodeName) + 1);
        strcpy(m_pszConfigNodeName, pszXmlNodeName);
    }
}



/////////////////////////////////////////////////////////////////////////////////
// ~CProfile
//
// Function:
//          Destruct function, close the open file.
//
// @param:
//          None
//
// @return:
//          None
/////////////////////////////////////////////////////////////////////////////////
CProfile::~CProfile()
{
    if (m_bIsInitXmlDoc)
    {
        CloseConfigFile();
        m_bIsInitXmlDoc = FALSE;
    }

    if (NULL != m_pszProfilePath)
    {
        delete []m_pszProfilePath;
        m_pszProfilePath = NULL;
    }

    if (NULL != m_pszConfigNodeName)
    {
        delete []m_pszConfigNodeName;
        m_pszConfigNodeName = NULL;
    }
}



/////////////////////////////////////////////////////////////////////////////////
// OpenConfigFile
//
// Function:
//          Open the configuration file.
//
// @param:
//          None
//
// @return:
//          OK - Successfully open the configuration file.
//          Other values - Please refer to the ErrorCode.h file.
/////////////////////////////////////////////////////////////////////////////////
WORD CProfile::OpenConfigFile()
{
    if (m_bIsInitXmlDoc)
    {
        return DEBUG_RETCODE("OpenConfigFile", OK);
    }

    if (NULL == m_pszProfilePath ||
            NULL == m_pszConfigNodeName)
    {
        DEBUG_INFO("Error: Profile path or XML config node name is NULL");
        return DEBUG_RETCODE("OpenConfigFile", ERROR_XML);
    }

    m_pXmlDoc = new TiXmlDocument(m_pszProfilePath);
    if (NULL == m_pXmlDoc)
    {
        DEBUG_INFO("Error: New TiXmlDocument object failed.");
        return DEBUG_RETCODE("OpenConfigFile", ERROR_XML);
    }

    bool bLoadXml = m_pXmlDoc->LoadFile();
    if (!bLoadXml)
    {
        DEBUG_INFO("Error: XML file load failed, error info: %s",
                m_pXmlDoc->ErrorDesc());
        return DEBUG_RETCODE("OpenConfigFile", ERROR_XML);
    }

    m_bIsInitXmlDoc = TRUE;
    return OK;
}



/////////////////////////////////////////////////////////////////////////////////
// CloseConfigFile
//
// Function:
//          Close the configuration file.
//
// @param:
//          None
//
// @return:
//          OK - Successfully close the configuration file.
//          Other values - Please refer to the ErrorCode.h file.
/////////////////////////////////////////////////////////////////////////////////
WORD CProfile::CloseConfigFile()
{
    if (!m_bIsInitXmlDoc)
    {
        return OK;
    }

    delete m_pXmlDoc;
    m_pXmlDoc = NULL;

    m_bIsInitXmlDoc = FALSE;
    return OK;
}



/////////////////////////////////////////////////////////////////////////////////
// GetKeyValue
//
// Function:
//          Read data from the specified node from the XML file.
//
// @param:
//          [IN]  pszAppName, The parent node name.
//          [IN]  pszKeyName, The sub node name.
//          [IN]  pszDefVal,  If the pszKeyName node not exist, copy
//                the default string to the pszValBuf.
//          [OUT] pszValBuf, Pointer to the buffer that receives the 
//                the retrieved string.
//          [IN]  Specifies the size of the pszValBuf.
// @return:
//          OK - Successfully get data from XML file.
//          Other values - Please refer to the ErrorCode.h file.
/////////////////////////////////////////////////////////////////////////////////
WORD CProfile::GetKeyValue(_IN_ PCSTR pszAppName,
        _IN_ PCSTR pszKeyName,
        _IN_ PCSTR pszDefVal,
        _OUT_ char *pszValBuf,
        _IN_ WORD uBufLen)
{
    WORD wRet;
    wRet = examGetKeyFuncParam(pszAppName, pszKeyName, pszDefVal,
            pszValBuf, uBufLen);
    if (OK != wRet)
    {
        DEBUG_INFO("Error: Examine GetKeyValue function parameter failed.");
        return DEBUG_RETCODE("GetKeyValue", wRet);
    }

    strcpy(pszValBuf, pszDefVal);
    TiXmlElement *pAppNameEle = NULL;
    TiXmlElement *pKeyEle = NULL;

    pAppNameEle = this->getAppNameElement(pszAppName);
    if (NULL == pAppNameEle)
    {
        DEBUG_INFO("Error: %s node not exist.", pszAppName);
        return DEBUG_RETCODE("GetKeyValue", ERROR_XML);
    }

    pKeyEle = pAppNameEle->FirstChildElement(pszKeyName);
    if (NULL != pKeyEle && NULL != pKeyEle->GetText())
    {
        if ((strlen(pKeyEle->GetText()) + 1) <= uBufLen)
        {
            strcpy(pszValBuf, pKeyEle->GetText());
        }
        else
        {
            DEBUG_INFO("Error: The fourth argument size too small");
            return DEBUG_RETCODE("GetKeyValue", ERROR_INSUFFICIENT_BUFFERR);
        }
    }
    return OK;
}



/////////////////////////////////////////////////////////////////////////////////
// GetKeyAttributeValue
//
// Function:
//          Read data from the specified node attribute from the XML file.
//
// @param:
//          [IN]  pszAppName, The parent node name.
//          [IN]  pszKeyName, The sub node name.
//          [IN]  pszAttrName, The need read attribute name.
//          [OUT] pszValBuf, Pointer to the buffer that receives the 
//                the retrieved string.
//          [IN]  Specifies the size of the pszValBuf.
// @return:
//          OK - Successfully get data from XML file.
//          Other values - Please refer to the ErrorCode.h file.
/////////////////////////////////////////////////////////////////////////////////
WORD CProfile::GetKeyAttributeValue(_IN_ PCSTR pszAppName,
        _IN_ PCSTR pszKeyName,
        _IN_ PCSTR pszAttrName,
        _OUT_ char *pszValBuf,
        _IN_ USHORT uBufLen)
{
    if (!m_bIsInitXmlDoc)
    {
        DEBUG_INFO("Error: XML config file is not open.");
        return DEBUG_RETCODE("GetKeyAttributeValue", ERROR_XML);
    }

    if (pszAppName == NULL || pszKeyName == NULL ||
            pszAttrName == NULL || uBufLen == 0)
    {
        DEBUG_INFO("Error: Invalid parameter.");
        return DEBUG_RETCODE("GetKeyAttributeValue", ERROR_INVALID_PARAM);
    }

    TiXmlElement *pAppNameEle = NULL;
    TiXmlElement *pKeyEle = NULL;

    pAppNameEle = this->getAppNameElement(pszAppName);
    if (NULL == pAppNameEle)
    {
        DEBUG_INFO("Error: %s node not exist.", pszAppName);
        return DEBUG_RETCODE("GetKeyAttributeValue", ERROR_XML);
    }

    pKeyEle = pAppNameEle->FirstChildElement(pszKeyName);
    if (NULL == pKeyEle)
    {
        DEBUG_INFO("Error: %s node not exist.", pszKeyName);
        return DEBUG_RETCODE("GetKeyAttributeValue", ERROR_XML);
    }

    if ((NULL != pKeyEle->Attribute(pszAttrName)))
    {
        if ((strlen(pKeyEle->Attribute(pszAttrName)) + 1) <= uBufLen)
        {
            memcpy(pszValBuf, pKeyEle->Attribute(pszAttrName),
                    strlen(pKeyEle->Attribute(pszAttrName)));
        }
        else
        {
            DEBUG_INFO("Error: The fourth argument size too small");
            return DEBUG_RETCODE("GetKeyAttributeValue", ERROR_INSUFFICIENT_BUFFERR);
        }
    }
    else
    {
        DEBUG_INFO("Error: %s attribute not exist.", pszAttrName);
        return DEBUG_RETCODE("GetKeyAttributeValue", ERROR_XML);
    }
    return OK;
}


/////////////////////////////////////////////////////////////////////////////////
// SetKeyValue
//
// Function:
//          Write data to the XML file.
//
// @param:
//          [IN]  pszAppName, The parent node name.
//          [IN]  pszKeyName, The sub node name.
//          [IN]  pszKeyValue, Pointer to a string to be written to 
//                the XML file.
//
// @return:
//           OK - Successfully write date to the XML file.
//           Other values - Please refer to the ErrorCode.h file.
/////////////////////////////////////////////////////////////////////////////////
WORD CProfile::SetKeyValue(_IN_ PCSTR pszAppName,
        _IN_ PCSTR pszKeyName,
        _IN_ PCSTR pszKeyValue)
{
    BOOL bSaveRet;
    WORD wRet;

    wRet = examSetKeyFuncParam(pszAppName, pszKeyName, pszKeyValue);
    if (OK != wRet)
    {
        DEBUG_INFO("Error: Examine SetKeyValue function parameter failed.");
        return DEBUG_RETCODE("SetKeyValue", wRet);
    }

    TiXmlElement *pAppNameEle = NULL;
    TiXmlElement *pKeyEle = NULL;

    pAppNameEle = this->getAppNameElement(pszAppName);
    if (NULL == pAppNameEle)
    {
        DEBUG_INFO("Error: App Name not exist.");
        return DEBUG_RETCODE("SetKeyValue", ERROR_XML);
    }

    pKeyEle = pAppNameEle->FirstChildElement(pszKeyName);
    if (NULL == pKeyEle)
    {
        pKeyEle = new TiXmlElement(pszKeyName);
        if (NULL == pKeyEle)
        {
            DEBUG_INFO("Error: New TiXmlElement failed.");
            return DEBUG_RETCODE("SetKeyValue", ERROR_XML);
        }
        pAppNameEle->LinkEndChild(pKeyEle);
    }

    TiXmlText *pEleText = new TiXmlText(pszKeyValue);
    if (NULL == pEleText)
    {
        DEBUG_INFO("Error: New TiXmlText object failed.");
        return DEBUG_RETCODE("SetKeyValue", ERROR_XML);
    }

    pKeyEle->Clear();
    pKeyEle->LinkEndChild(pEleText);
    bSaveRet = m_pXmlDoc->SaveFile();
    if (!bSaveRet)
    {
        DEBUG_INFO("Error: Save TinyXmlDocument Save File failed, error %s",
                m_pXmlDoc->ErrorDesc());
        return DEBUG_RETCODE("SetKeyValue", ERROR_XML);
    }
    return OK;
}



/////////////////////////////////////////////////////////////////////////////////
// getAppNameElement
//
// Function:
//          Get the pointer of the TiXmlElement object.
//
// @param:
//          [IN]  pszAppName, The node name.
//
// @return:
//          If the node exist, return the TiXmlElement object pointer,
//          otherwise return NULL.
/////////////////////////////////////////////////////////////////////////////////
TiXmlElement *CProfile::getAppNameElement(PCSTR pszAppName)
{
    TiXmlElement *pRootEle = NULL;
    TiXmlElement *pCommConfigEle = NULL;

    pRootEle = m_pXmlDoc->RootElement();
    if (NULL == pRootEle)
    {
        return NULL;
    }
    pCommConfigEle = pRootEle->FirstChildElement(m_pszConfigNodeName);
    if (NULL == pCommConfigEle)
    {
        return NULL;
    }
    return pCommConfigEle->FirstChildElement(pszAppName);
}



/////////////////////////////////////////////////////////////////////////////////
// examSetKeyFuncParam
//
// Function:
//          Check whether the SetKeyValue function parameter is valid.
//
// @param:
//          Consistent with SetKeyValue function.
//
// @return:
//          OK - The parameter is valid.
//          Other values - Please refer to the ErrorCode.h file.
/////////////////////////////////////////////////////////////////////////////////
WORD CProfile::examSetKeyFuncParam(_IN_ PCSTR pszAppName,
        _IN_ PCSTR pszKeyName,
        _IN_ PCSTR pszKeyValue)
{
    if (!m_bIsInitXmlDoc)
    {
        DEBUG_INFO("Error: XML config file is not open.");
        return DEBUG_RETCODE("GetKeyValue", ERROR_XML);
    }

    if (pszAppName == NULL || pszKeyName == NULL || pszKeyValue == NULL)
    {
        DEBUG_INFO("Error: Function parameter invalid.");
        return DEBUG_RETCODE("examSetKeyFuncParam", ERROR_INVALID_PARAM);
    }
    return OK;
}



/////////////////////////////////////////////////////////////////////////////////
// examGetKeyFuncParam
//
// Function:
//          Check whether the GetKeyValue function parameter is valid.
//
// @param:
//          Consistent with GetKeyValue function.
//
// @return:
//          OK - The parameter is valid.
//          Other values - Please refer to the ErrorCode.h file.
/////////////////////////////////////////////////////////////////////////////////
WORD CProfile::examGetKeyFuncParam(_IN_ PCSTR pszAppName,
        _IN_ PCSTR pszKeyName,
        _IN_ PCSTR pszDefVal,
        _OUT_ char *pszValBuf,
        _IN_ USHORT uBufLen)
{
    if (!m_bIsInitXmlDoc)
    {
        DEBUG_INFO("Error: XML config file is not open.");
        return DEBUG_RETCODE("examGetKeyFuncParam", ERROR_XML);
    }

    if (NULL == pszAppName || NULL == pszKeyName ||
            NULL == pszDefVal || NULL == pszValBuf ||
            uBufLen == 0)
    {
        DEBUG_INFO("Error: Function parameter invalid.");
        return DEBUG_RETCODE("examGetKeyFuncParam", ERROR_INVALID_PARAM);
    }

    pszValBuf[0] = '\0';
    if ((strlen(pszDefVal) + 1) >= uBufLen)
    {
        DEBUG_INFO("Error: The fourth argument size too small");
        return DEBUG_RETCODE("examGetKeyFuncParam", ERROR_INSUFFICIENT_BUFFERR);
    }

    return OK;
}
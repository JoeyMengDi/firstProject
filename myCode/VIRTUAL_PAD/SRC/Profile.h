
/* 
 * Copyright (c) Castles Technology Co., Ltd. 
 * 
 * File:   Profile.h
 * Author: Alan.Ren
 *
 * Created: 2017/06/21
 */

#ifndef _H_H_PROFILE_H_
#define _H_H_PROFILE_H_

#include "../SRC/CPCommon.h"
#include "StdafxHead.h"
#include "tinyxml.h"



class CProfile
{
public:
    CProfile();
    CProfile(char *pszProfilePath, char *pszRootNodeName);
    virtual ~CProfile();

public:
    WORD OpenConfigFile();

    WORD CloseConfigFile();

    WORD GetKeyValue(_IN_ PCSTR pszAppName,
    _IN_ PCSTR pszKeyName,
    _IN_ PCSTR pszDefVal,
    _OUT_ char *pszValBuf,
    _IN_ WORD uBufLen);

    WORD SetKeyValue(_IN_ PCSTR pszAppName,
    _IN_ PCSTR pszKeyName,
    _IN_ PCSTR pszKeyValue);
    
     WORD GetKeyAttributeValue(_IN_ PCSTR pszAppName,
    _IN_ PCSTR pszKeyName,
    _IN_ PCSTR pszAttrName,
    _OUT_ char *pszValBuf,
    _IN_ USHORT uBufLen);

private:
    // Disable copy and assign construct function
    CProfile(const CProfile &cProfile) { }

    CProfile operator=(const CProfile &cProfile)
    {
        return (*this);
    }

    TiXmlElement *getAppNameElement(PCSTR pszAppName);

    WORD examSetKeyFuncParam(_IN_ PCSTR pszAppName,
    _IN_ PCSTR pszKeyName,
    _IN_ PCSTR pszKeyValue);

    WORD examGetKeyFuncParam(_IN_ PCSTR pszAppName,
    _IN_ PCSTR pszKeyName,
    _IN_ PCSTR pszDefVal,
    _OUT_ char *pszValBuf,
    _IN_ USHORT uBufLen);
    
    void ConstructInit(_IN_ PCSTR pszProfilePath, _IN_ PCSTR pszXmlNodeName);

private:
    TiXmlDocument *m_pXmlDoc;
    char *m_pszProfilePath;
    char *m_pszConfigNodeName;
    BOOL m_bIsInitXmlDoc;
};

#endif /* PROFILE_H */


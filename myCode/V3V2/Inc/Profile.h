
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

class CProfile
{
public:
    CProfile();
    CProfile(IN const char *pszProfilePath, IN const char *pszRootNodeName);
    virtual ~CProfile();

public:
    WORD OpenConfigFile();

    WORD CloseConfigFile();

    WORD GetKeyValue(IN PCSTR pszAppName,
    IN PCSTR pszKeyName,
    IN PCSTR pszDefVal,
    OUT char *pszValBuf,
    IN WORD uBufLen);

    WORD SetKeyValue(IN PCSTR pszAppName,
    IN PCSTR pszKeyName,
    IN PCSTR pszKeyValue);
    
     WORD GetKeyAttributeValue(IN PCSTR pszAppName,
    IN PCSTR pszKeyName,
    IN PCSTR pszAttrName,
    OUT char *pszValBuf,
    IN USHORT uBufLen);

private:
    // Disable copy and assign construct function
    CProfile(const CProfile &cProfile) { }

    CProfile operator=(const CProfile &cProfile)
    {
        return (*this);
    }

    TiXmlElement *getAppNameElement(PCSTR pszAppName);

    WORD examSetKeyFuncParam(IN PCSTR pszAppName,
    IN PCSTR pszKeyName,
    IN PCSTR pszKeyValue);

    WORD examGetKeyFuncParam(IN PCSTR pszAppName,
    IN PCSTR pszKeyName,
    IN PCSTR pszDefVal,
    OUT char *pszValBuf,
    IN USHORT uBufLen);
    
    void ConstructInit(IN PCSTR pszProfilePath, IN PCSTR pszXmlNodeName);

private:
    TiXmlDocument *m_pXmlDoc;
    char *m_pszProfilePath;
    char *m_pszConfigNodeName;
    BOOL m_bIsInitXmlDoc;
};

#endif /* PROFILE_H */


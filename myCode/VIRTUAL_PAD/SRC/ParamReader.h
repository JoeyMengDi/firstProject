/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParamReader.h
 * Author: Louis Lu
 *
 * Created on 2017年8月22日, 下午1:57
 */

#ifndef _H_PARAMREADER_H_
#define _H_PARAMREADER_H_

#include "../SRC/StdafxHead.h"
#include "../SRC/CPCommon.h"

#define BUF_LEN 32

class CParamReader
{
public:
    CParamReader();
    virtual ~CParamReader();
    
    WORD GetCommDebugMode(_IN_OUT_ PBYTE pbyDebugMode);

    WORD GetMenuDebugMode(_IN_OUT_ PBYTE pbyDebugMode);

    WORD GetMsgDebugMode(_IN_OUT_ PBYTE pbyDebugMode);

    WORD GetUIDebugMode(_IN_OUT_ PBYTE pbyDebugMode);

    WORD GetProtMode(_IN_OUT_ PBYTE pbyMode);
    
    WORD GetTXNDebugMode(_IN_OUT_ PBYTE pbyDebugMode);

    WORD GetUIMode(PBYTE pbyMode);
    
    WORD LoadIPParam(WORD wIPType);
    
    
    WORD ReadXMLData(_IN_ PCSTR pcstrFileName, _IN_ PCSTR pcstrMenuNode,
                     _IN_ PCSTR pcstrAppName, _IN_ PCSTR pcstrKeyName,
                     _OUT_ PSTR pstrValBuf, _IN_ WORD uBufLen);
    
    WORD WriteXMLData(_IN_ PCSTR pcstrFileName, _IN_ PCSTR pcstrMenuNode,
                      _IN_ PCSTR pcstrAppName, _IN_ PCSTR pcstrKeyName, 
                      _IN_ PCSTR pcstrInValBuf);
    
    WORD GetCurrentIP(void);
    
    WORD GetRetryParam(WORD wReParam);
    
    WORD GetCNTRParam(WORD wParamType);
    
    WORD SetCNTRParam(CByteStream cInData);
    
    WORD GetXMLMenuNode(CByteStream cInData, CByteStream &cMenuNode);    
    
    WORD GetCC02Param(CByteStream &cOutData);
    
    WORD GetVENDParam(WORD wParamType, CByteStream &cOutData);
    
    WORD GetAPNParam(WORD wParamType, CByteStream &cOutData);
    
    WORD GetFWParam(WORD wParamType, CByteStream &cOutData);
    
    WORD GetECHOParam(WORD wParamType, CByteStream &cOutData);
    
    WORD GetCustomerParam(WORD wParamType, CByteStream &cOutData);
    
    WORD GetConfigParam(WORD wParamType, CByteStream &cOutData);
    
private:
    void SwitchIPType(WORD wIPType);
    WORD CommType(void);
    
    
private:
    CHAR m_szIP[16];
    CHAR m_szPort[8];
    CHAR m_szIPNodeName[16];
    CHAR m_szPortNodeName[16];
    
    WORD m_wCurIPType;

};

#endif /* _H_PARAMREADER_H_ */


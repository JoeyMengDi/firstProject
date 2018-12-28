
/**
 * Copyright(c) Castles Technology Co,. Ltd
 *  
 * File:   ParamReader.h
 * Author: Louis Lu
 *
 * Created Date: 2017.08.22
 **/

#ifndef _H_PARAMREADER_H_
#define _H_PARAMREADER_H_

#define COMM_MOUDLE             0x01
#define MENU_MOUDLE             0x02
#define MSG_MOUDLE              0x03
#define UI_MOUDLE               0x04
#define TXN_MOUDLE              0x05
#define CLOUD_MODULE            0x06
#define UI_MODE_TEXT            0x01
#define UI_MODE_GRAPHIC         0x02


class CParamReader
{
public:
    CParamReader();
    virtual ~CParamReader();
    
    WORD GetCommDebugMode(OUT BYTE &byDebugMode);

    WORD GetMenuDebugMode(OUT BYTE &byDebugMode);

    WORD GetMsgDebugMode(OUT BYTE &byDebugMode);

    WORD GetUIDebugMode(OUT BYTE &byDebugMode);

    WORD GetProtMode(OUT BYTE &byMode);
    
    WORD GetTXNDebugMode(OUT BYTE &byDebugMode);
    
    WORD GetCloudDebugMode(OUT BYTE &pbyDebugMode);

    WORD GetUIMode(OUT BYTE &byMode);
    
    WORD GetDebugLevel(IN BYTE byModule, OUT DWORD &dwDebugLevel);

};

#endif /* _H_PARAMREADER_H_ */


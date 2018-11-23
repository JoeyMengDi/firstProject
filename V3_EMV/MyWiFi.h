/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyWiFi.h
 * Author: Joey Meng
 *
 * Created on 2018年11月21日, 下午3:21
 */

#ifndef MYWIFI_H
#define MYWIFI_H

#include "deftype.h"
#include "ByteStream.h"
#include <ctosapi.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class MyWiFi {
public:
    MyWiFi();
    MyWiFi(const MyWiFi& orig);
    USHORT OpenWiFi();
    void WifiSocktProcess(PCSTR pszIp, USHORT usPort, INT nTimeOut, const CByteStream& cbsIN, WORD wType, CByteStream& cbsOUT);
    USHORT CloseWiFi();
    virtual ~MyWiFi();
private:
    BYTE byNumInfo;
    CTOS_stWifiInfo *pstInfo;
    USHORT WifiScan();
    USHORT GetWifiInfo(BYTE* bNumInfo, CTOS_stWifiInfo** stInfo);
};

#endif /* MYWIFI_H */


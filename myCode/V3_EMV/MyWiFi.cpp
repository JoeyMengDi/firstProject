/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyWiFi.cpp
 * Author: Joey Meng
 * 
 * Created on 2018年11月21日, 下午3:21
 */

#include "MyWiFi.h"
#include "DbgMacro.h"

MyWiFi::MyWiFi() {
}

MyWiFi::MyWiFi(const MyWiFi& orig) {
}

MyWiFi::~MyWiFi() {
}

USHORT MyWiFi::OpenWiFi() {
    if (d_OK != CTOS_WifiOpen()) {
        //CTOS_LCDTPrintXY(3, 3, (BYTE*) "Open WiFi Fail!");
        DEBUG_INFO(DEBUGINFO_NORMAL, "Open WiFi Fail!\n");
        return -1;
    }
    return d_OK;
}

USHORT MyWiFi::WifiScan() {
    CTOS_WifiScan();
    usleep(1000 * 1000 * 3); //Sleep 3 seconds
    CTOS_WifiScan();
}

USHORT MyWiFi::GetWifiInfo(BYTE* bNumInfo, CTOS_stWifiInfo** stInfo) {
    if (d_OK != CTOS_WifiInfoGet(bNumInfo, stInfo)) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "WifiInfoGet Fail\n");
        return -1;
    }
    return d_OK;
}

void MyWiFi::WifiSocktProcess(PCSTR pszIp, USHORT usPort, INT nTimeOut, const CByteStream& cbsIN, WORD wType, CByteStream& cbsOUT) {

    DWORD dwState;
    BYTE byValue = 1;
    INT nNum = 0;
    USHORT uRet;
    CHAR ccWifiName[] = "Castles-2.4G";
    BYTE byPwd[] = "CastSz602";
    WifiScan();
    if (d_OK != GetWifiInfo(&byNumInfo, &pstInfo)) {
        return;
    }
    if (byNumInfo <= 0) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "WifiInfoGet Fail Info <= 0  byNumInfo : %d\n", byNumInfo);
        return;
    }
    CTOS_WifiConfigSet(d_WIFI_CONFIG_DHCP, &byValue, 1);
    CTOS_WifiConfigSet(d_WIFI_CONFIG_AUTOCON_AP, &byValue, 1);


    for (nNum = 0; nNum < byNumInfo; nNum++) {
        if (strncmp((CHAR*) pstInfo[nNum].ESSID, ccWifiName, 12) == 0) {
            break;
        }
    }
    if (nNum == byNumInfo) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "find Castles-2.4G fail\n");
        return;
    }
    uRet = CTOS_WifiConnectAP(&pstInfo[nNum], byPwd, strlen((CHAR*) byPwd));
    int i = 6;
    while (i--) {
        CTOS_WifiStatus(&dwState);
        if ((dwState & d_WIFI_STATE_AP_CONNECTED) > 0) {
            // CTOS_LCDTClearDisplay();
            break;
        }
        if ((dwState & d_WIFI_STATE_AP_CONNECTING) == 0 && (dwState & d_WIFI_STATE_AP_CONNECTED) == 0) {
            //CTOS_LCDTPrintXY(1, 9, (BYTE*) "WIFI Contect Fail");
            //DEBUG_INFO(DEBUGINFO_NORMAL, "WIFI Contect Fail\n");
            //CTOS_KBDGet(&key);
            break;
        }
        //CTOS_LCDTPrintXY(3, 5, (BYTE*) "Connecting....");
        DEBUG_INFO(DEBUGINFO_NORMAL, "WIFI Contecing.........\n");
        usleep(1000 * 1000 * 1);
    }
    
    if (i <= -4) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "WIFI Contect Fail\n");
    } else {
        DEBUG_INFO(DEBUGINFO_NORMAL, "WIFI Contect success\n");

        /**********************************************SOCKET******************************************************/
        INT BUFSIZ = 2048;
        int sockfd, numbytes;
        BYTE buf[BUFSIZ];
        struct sockaddr_in their_addr;
        //printf("break!");
        while ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1);
        //printf("We get the sockfd~\n");
        //CTOS_LCDTPrintXY(1, 1, (BYTE*) "We get the sockfd~\n");
        DEBUG_INFO(DEBUGINFO_NORMAL, "We get the sockfd~\n");
        their_addr.sin_family = AF_INET;
        their_addr.sin_port = htons(usPort);
        their_addr.sin_addr.s_addr = inet_addr(pszIp);
        bzero(&(their_addr.sin_zero), 8);

        while (connect(sockfd, (struct sockaddr*) &their_addr, sizeof (struct sockaddr)) == -1);
        //printf("Get the Server~Cheers!\n");
        //CTOS_LCDTPrintXY(1, 2, (BYTE*) "Get the Server~Cheers!\n");
        DEBUG_INFO(DEBUGINFO_NORMAL, "Get the Server~Cheers!\n");
        // buf = cbsIN.GetBuffer(0);
        send(sockfd, cbsIN.GetBuffer(0), cbsIN.GetLength(),0);
        DEBUG_INFO(DEBUGINFO_NORMAL, "watting DATA>>>!\n");
         memset(buf, 0, sizeof (buf));
        int len = recv(sockfd, buf, BUFSIZ, 0);
        cbsOUT.Write(buf, len);
        //numbytes = recv(sockfd, buf, BUFSIZ, 0); //接收服务器端信息  
        //buf[numbytes] = '\0';
        //CTOS_LCDTPrintXY(1, 3, (BYTE*) buf);
        //printf("%s", buf);
        //while (1) {
        //printf("Entersome thing:");
        //scanf("%s", buf);
        //            strcpy(buf, "hello I am WIFI\n");
        //            numbytes = send(sockfd, buf, strlen(buf), 0);
        //            numbytes = recv(sockfd, buf, BUFSIZ, 0);
        //            buf[numbytes] = '\0';
        //            //printf("received:%s\n", buf);
        //            CTOS_LCDTPrintXY(1, 4, (BYTE*) "received....");
        //            CTOS_LCDTPrintXY(1, 5, (BYTE*) "                                   ");
        //            CTOS_LCDTPrintXY(1, 5, (BYTE*) buf);
        //            if (strncmp(buf, "exit", 4) == 0) {
        //                break;
        //            }
        //}
        close(sockfd);

        /***********************************************SOCKET******************************************************/
    }
}

USHORT MyWiFi::CloseWiFi() {
    CTOS_WifiClose();
}


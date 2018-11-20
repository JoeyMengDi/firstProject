/** 
 **	A Template for developing new terminal application
 **/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>

BYTE key;

/* ====================================================================
 * FUNCTION NAME: InputString
 * DESCRIPTION: Continue to input two or more characters at a time, build a string
 * RETURN: none.
 * NOTES: none.
 *=================================================================== */
int InputString(USHORT usX, USHORT usY, BYTE isMask, BYTE *pbaStr, USHORT *usStrLen) {
    //Declare Local Variable 
    int i = 0;
    memset(pbaStr, 0x00, *usStrLen);
    CTOS_LCDTPutchXY(usX, usY, '_');
    while (1) {
        //Scan the keyboard to detect whether a key is pressed //
        CTOS_KBDHit(&key);
        //Cancel InputString() //
        if (key == d_KBD_CANCEL) {
            CTOS_LCDTPutchXY(usX + i, usY, ' ');
            memset(pbaStr, 0x00, *usStrLen);
            usStrLen = 0;
            return 0;
        }
        //Done input and output a string //
        if (key == d_KBD_ENTER) {
            CTOS_LCDTPutchXY(usX + i, usY, ' ');
            *usStrLen = (USHORT) strlen((char*) pbaStr);
            if (*usStrLen > 0) return 1;
            else return 0;
        } else if (key == d_KBD_CLEAR) { //Backspace //
            CTOS_LCDTPutchXY(usX + i, usY, ' ');
            i--;
            pbaStr[i] = 0x00;
            CTOS_LCDTPutchXY(usX + i, usY, '_');
        } else if (key == d_KBD_00) { //Clear all input data //
            memset(pbaStr, 0x00, *usStrLen);
            i = 0;
            CTOS_LCDTGotoXY(usX + i, usY);
            CTOS_LCDTClear2EOL();
            CTOS_LCDTPutchXY(usX, usY, '_');
        }
        if (i + 1 <= *usStrLen) {
            if ((key >= 0x30)&& (key <= 0x39)) {
                pbaStr[i] = key;
                if (isMask) CTOS_LCDTPutchXY(usX + i, usY, '*');
                else CTOS_LCDTPutchXY(usX + i, usY, pbaStr[i]);
                i++;
                CTOS_LCDTPutchXY(usX + i, usY, '_');
            }
        }
    }
}

void UiKeyPad(USHORT usX, USHORT usY, BYTE* byData) {
    //BYTE key;
    BYTE baBuff[256];
    //Define letter mapping to each key

    //normal english keyboard
    BYTE * keyboardLayoutEnglish[] = {(BYTE*) "0SPsp", (BYTE*) "1QZqz", (BYTE*) "2ABCabc", (BYTE*) "3DEFdef", (BYTE*) "4GHIghi", (BYTE*) "5JKLjkl",
        (BYTE*) "6MNOmno", (BYTE*) "7PRSprs", (BYTE*) "8TUVtuv", (BYTE*) "9WXYwxy", (BYTE*) ":;/\\|?,.<>", (BYTE*) ".!@#$%^&*()"};
    //
    //    //initial LCD screen and set font to Chinese_Taiwan 16x16
    //    CTOS_BackLightSet(d_BKLIT_LCD, d_ON); //turn on backlight
    //    CTOS_LanguageConfig(d_FONT_CHINESE_TAIWAN, d_FONT_16x16, 0, FALSE);
    //    CTOS_LanguageLCDFontSize(d_FONT_16x16, 0);
    //    CTOS_LCDTSelectFontSize(d_LCD_FONT_8x16);
    CTOS_UIKeypad(usX, usY, keyboardLayoutEnglish, 40, 80, d_TRUE, d_FALSE, 0, 0, baBuff,
            16);
    strcpy((CHAR*) byData, (CHAR*) baBuff);
}

void WifiSockt() {
    int sockfd, numbytes;
    char buf[BUFSIZ];
    struct sockaddr_in their_addr;
    //printf("break!");
    while ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1);
    //printf("We get the sockfd~\n");
    CTOS_LCDTPrintXY(1, 1, (BYTE*) "We get the sockfd~\n");
    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(8000);
    their_addr.sin_addr.s_addr = inet_addr("192.168.31.176");
    bzero(&(their_addr.sin_zero), 8);

    while (connect(sockfd, (struct sockaddr*) &their_addr, sizeof (struct sockaddr)) == -1);
    //printf("Get the Server~Cheers!\n");
    CTOS_LCDTPrintXY(1, 2, (BYTE*) "Get the Server~Cheers!\n");
    numbytes = recv(sockfd, buf, BUFSIZ, 0); //接收服务器端信息  
    buf[numbytes] = '\0';
    CTOS_LCDTPrintXY(1, 3, (BYTE*) buf);
    //printf("%s", buf);
    while (1) {
        //printf("Entersome thing:");
        //scanf("%s", buf);
        strcpy(buf, "hello I am WIFI\n");
        numbytes = send(sockfd, buf, strlen(buf), 0);
        numbytes = recv(sockfd, buf, BUFSIZ, 0);
        buf[numbytes] = '\0';
        //printf("received:%s\n", buf);
        CTOS_LCDTPrintXY(1, 4, (BYTE*) "received....");
        CTOS_LCDTPrintXY(1, 5, (BYTE*) "                                   ");
        CTOS_LCDTPrintXY(1, 5, (BYTE*) buf);
        if (strncmp(buf, "exit", 4) == 0) {
            break;
        }
    }
    close(sockfd);
}

ushort OpenWifi() {
    if (d_OK != CTOS_WifiOpen()) {
        CTOS_LCDTPrintXY(3, 3, (BYTE*) "Open WiFi Fail!");
        CTOS_KBDGet(&key);
        return -1;
    }
    return d_OK;
}

void WifiScan() {
    CTOS_WifiScan();
    usleep(1000 * 1000 * 3);
    CTOS_WifiScan();
}

USHORT GetWifiInfo(BYTE* bNumInfo, CTOS_stWifiInfo** stInfo) {
    if (d_OK != CTOS_WifiInfoGet(bNumInfo, stInfo)) {
        CTOS_LCDTPrintXY(3, 1, (BYTE*) "WifiInfoGet Fail");
        CTOS_KBDGet(&key);
        return -1;
    }
    return d_OK;
}

void ShowMenu(BYTE byPageNum, CTOS_stWifiInfo* stInfo) {
    CTOS_LCDTClearDisplay();
    BYTE byMessage[64] = {0};
    byPageNum *= 4;
    for (INT i = 1; i <= 4; i++) {
        snprintf((char*) byMessage, 63, "%d : %s\n", i, stInfo[byPageNum++].ESSID);
        CTOS_LCDTPrintXY(1, i, byMessage);
    }
    CTOS_LCDTPrintXY(1, 6, (BYTE*) "<- 7.Pre   9.Next ->  ");
}

void ShowInfo(BYTE byNum, CTOS_stWifiInfo* stInfo) {
    BYTE byPwd[16] = {0};
    //BYTE byMessage[64] = {0};
    USHORT usRet;
    BYTE byValue = 1;
    DWORD dwState;
    CTOS_LCDTClearDisplay();
    CTOS_LCDTPrintXY(3, 1, stInfo[byNum].ESSID);
    CTOS_LCDTPrintXY(3, 2, (BYTE*) "Plz In Pwd...");
    UiKeyPad(3, 3, byPwd);
    // CTOS_LCDTPrintXY(3, 4, byPwd);

    CTOS_WifiConfigSet(d_WIFI_CONFIG_DHCP, &byValue, 1);
    CTOS_WifiConfigSet(d_WIFI_CONFIG_AUTOCON_AP, &byValue, 1);

    usRet = CTOS_WifiConnectAP(&stInfo[byNum], byPwd, strlen((CHAR*) byPwd));
    if (d_OK == usRet) {
        CTOS_LCDTClearDisplay();
    }
    //    snprintf((char*) byMessage, 63, "usRet : 0x%04X\n", usRet);
    //    CTOS_LCDTPrintXY(3, 4, byMessage);

    int i = 6;
    while (i--) {
        CTOS_WifiStatus(&dwState);
        //snprintf((char*) byMessage, 63, "dwState : 0x%04X\n", dwState);
        //        if ((dwState & d_WIFI_STATE_AP_CONNECTING) > 0) {
        //            CTOS_LCDTPrintXY(3, 8, (BYTE*) "d_WIFI_STATE_CONNECTING");
        //        }
        if ((dwState & d_WIFI_STATE_AP_CONNECTED) > 0) {
            CTOS_LCDTClearDisplay();
            //CTOS_LCDTPrintXY(1, 5, (BYTE*) "WIFI Contect Success");
            break;
        }
        if ((dwState & d_WIFI_STATE_AP_CONNECTING) == 0 && (dwState & d_WIFI_STATE_AP_CONNECTED) == 0) {
            CTOS_LCDTPrintXY(1, 9, (BYTE*) "WIFI Contect Fail");
            //CTOS_KBDGet(&key);
            break;
        }
        CTOS_LCDTPrintXY(3, 5, (BYTE*) "Connecting....");
        usleep(1000 * 1000 * 1);
    }
    if (i <= 0) {
        CTOS_LCDTPrintXY(1, 9, (BYTE*) "WIFI Contect Fail");
    } else {
        WifiSockt();
    }
    CTOS_KBDGet(&key);
}

/** 
 ** The main entry of the terminal application 
 **/
int main(int argc, char *argv[]) {
    BYTE bNumInfo;
    CTOS_stWifiInfo *pstInfo;
    BYTE byCurPageNum = 0, byEndPage;
    // TODO: Add your program here //
    CTOS_LCDTClearDisplay();

    if (d_OK != OpenWifi()) {
        return -1;
    }

    WifiScan();

    if (d_OK != GetWifiInfo(&bNumInfo, &pstInfo)) {
        return -1;
    }
    byEndPage = (bNumInfo - 1) / 4;
    ShowMenu(byCurPageNum, pstInfo);
enter:
    while (1) {
        CTOS_KBDGet(&key);
        switch (key) {
            case d_KBD_1: ShowInfo(4 * byCurPageNum, pstInfo);
                break;
            case d_KBD_2: ShowInfo(4 * byCurPageNum + 1, pstInfo);
                break;
            case d_KBD_3: ShowInfo(4 * byCurPageNum + 2, pstInfo);
                break;
            case d_KBD_4: ShowInfo(4 * byCurPageNum + 3, pstInfo);
                break;
            case d_KBD_7:
            {
                byCurPageNum = byCurPageNum > 0 ? (byCurPageNum - 1) : 0;
            }
                break;
            case d_KBD_9:
            {
                byCurPageNum = byCurPageNum < byEndPage ? (byCurPageNum + 1) : byEndPage;
            }
                break;
            case d_KBD_CANCEL: goto end;
        }
        ShowMenu(byCurPageNum, pstInfo);
    }

end:
    free(pstInfo);
    CTOS_WifiClose();
    exit(0);
}


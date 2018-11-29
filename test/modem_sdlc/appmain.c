/** 
 **	A Template for developing new terminal application
 **/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>

void ModemSDLCTest(void) {
    const BYTE TestData[] ={
        0x60, 0x09, 0x50, 0x00, 0x00, 0x02, 0x00, 0x30, 0x24, 0x05, 0x80, 0x20, 0xC0, 0x00, 0x04, 0x00,
        0x30, 0x00, 0x00, 0x00, 0x00, 0x01, 0x68, 0x00, 0x00, 0x00, 0x59, 0x05, 0x12, 0x59, 0x02, 0x09,
        0x50, 0x00, 0x37, 0x49, 0x99, 0x37, 0x00, 0x00, 0x01, 0x31, 0x04, 0xD0, 0x51, 0x21, 0x01, 0x18,
        0x99, 0x15, 0x89, 0x45, 0x67, 0x80, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31,
        0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x00, 0x06, 0x30,
        0x30, 0x30, 0x30, 0x35, 0x39
    };

    BYTE const number[] = "87989368"; //"87989368";// "25617000";
    BYTE const ATX1[] = "ATX1";
    USHORT ret;
    USHORT value;
    DWORD status;
    DWORD start;
    BYTE key;
    BYTE str[17];
    BYTE response[2000];

    CTOS_LCDTPrintXY(1, 1, "---Modem SDLC---");

    ret = CTOS_ModemOpen(d_M_MODE_SDLC_FAST, d_M_HANDSHAKE_V22_ONLY, d_M_COUNTRY_TAIWAN);
    if (ret != d_OK) {
        CTOS_LCDTPrintXY(1, 2, "Modem Open Fail");
        return;
    }

    CTOS_LCDTPrintXY(1, 2, "Modem Open OK");

    CTOS_LCDTPrintXY(1, 3, "Dialing......");
    CTOS_LCDTPrintXY(1, 4, (BYTE*) number);
    start = CTOS_TickGet();
    ret = CTOS_ModemDialup((BYTE*) number, sizeof (number) - 1);
    while (1) {
        sprintf(str, "DTime %ld ms", (CTOS_TickGet() - start) * 10);
        CTOS_LCDTPrintXY(1, 7, str);
        CTOS_ModemStatus(&status);
        if (!(status & d_M_STATUS_DIALING)) {
            if (status & d_M_STATUS_MODEM_ONLINE) {
                break;
            } else {
                CTOS_LCDTPrintXY(1, 3, "Dialing Failed");
                CTOS_ModemClose();

                return;
            }
        }
    }
    CTOS_LCDTPrintXY(1, 3, "Dialing OK   ");

    CTOS_LCDTPrintXY(1, 4, "Wait SDLC Online");
    while (1) {
        sprintf(str, "STime %ld ms", (CTOS_TickGet() - start) * 10);
        CTOS_LCDTPrintXY(1, 8, str);
        CTOS_ModemStatus(&status);
        if (status & d_M_STATUS_SDLC_ONLINE) {
            break;
        }
    }
    
    CTOS_LCDTPrintXY(1, 4, "SDLC Online OK  ");

    do {
        CTOS_KBDHit(&key);
        if (key == d_KBD_CANCEL) {
            CTOS_ModemClose();
            return;
        }

        CTOS_LCDTPrintXY(1, 5, "Wait Tx Ready");
        while (CTOS_ModemTxReady() == d_MODEM_TX_BUSY);
        CTOS_LCDTPrintXY(1, 5, "Tx Ready     ");

        value = 2000;
        ret = CTOS_ModemRxData(response, &value);

        if (ret == d_OK && value) {
            sprintf(str, "Rx Data : %d", value);
            CTOS_LCDTPrintXY(1, 7, str);
            CTOS_KBDGet(&key);
        }

        if (status & d_M_STATUS_ALL_DATA_SENT) {
            CTOS_LCDTPrintXY(1, 6, "Tx Data");
            ret = CTOS_ModemTxData((BYTE*) TestData, sizeof (TestData));
            if (ret != d_OK) {
            }
        }

        CTOS_ModemStatus(&status);

    } while (status & d_M_STATUS_MODEM_ONLINE);

    CTOS_LCDTPrintXY(1, 7, "Modem Off Line");

    CTOS_ModemClose();
    CTOS_LCDTPrintXY(1, 8, "Modem Close   ");
}

/** 
 ** The main entry of the terminal application 
 **/
int main(int argc, char *argv[]) {
    BYTE key;

    CTOS_LCDTSelectFontSize(0x101E);

    ModemSDLCTest();
    CTOS_KBDGet(&key);

    exit(0);
}

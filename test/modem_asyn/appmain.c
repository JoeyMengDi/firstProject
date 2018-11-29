/** 
 **	A Template for developing new terminal application
 **/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>

/*==========================================*
 *            D E F I N E S                 *
 *==========================================*/
#define d_BUFF_SIZE 128 //Buffer Size
#define d_LINE_DOT 12   //A line is 12 dots

const BYTE baPhoneNO[] = "*603"; //Define phone number of call out
const BYTE TestData[] = //Define send data
{
    0x60, 0x09, 0x50, 0x00, 0x00, 0x02, 0x00, 0x30, 0x24, 0x05, 0x80, 0x20, 0xC0, 0x00, 0x04, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x00, 0x01, 0x68, 0x00, 0x00, 0x00, 0x59, 0x05, 0x12, 0x59, 0x02, 0x09,
    0x50, 0x00, 0x37, 0x49, 0x99, 0x37, 0x00, 0x00, 0x01, 0x31, 0x04, 0xD0, 0x51, 0x21, 0x01, 0x18,
    0x99, 0x15, 0x89, 0x45, 0x67, 0x80, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31,
    0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x00, 0x06, 0x30,
    0x30, 0x30, 0x30, 0x35, 0x39
};

//Declare Global Variable //
USHORT ret;
BYTE key;
BYTE babuff[d_BUFF_SIZE];
BYTE isDialUp, isListen, isSetOnfi;
DWORD dwStatus;

/* ==========================================================================
 *
 * FUNCTION NAME: show_screen
 *
 * DESCRIPTION:   Show on the LCD Display
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ========================================================================== */
void show_screen(int tag) {
    CTOS_LCDTClearDisplay();
    switch (tag) {
        case 0:
            CTOS_LCDTSetReverse(TRUE);
            CTOS_LCDTPrintXY(1, 1, "   MODEM TEST   ");
            CTOS_LCDTSetReverse(FALSE);
            if (!isDialUp) CTOS_LCDTPrintXY(1, 2, "1.Dial Up    ");
            else CTOS_LCDTPrintXY(1, 2, "1.Hang Up    ");

            if (!isListen)CTOS_LCDTPrintXY(1, 3, "2.Listen (OFF)");
            else CTOS_LCDTPrintXY(1, 3, "2.Listen (ON)  ");

            CTOS_LCDTPrintXY(1, 4, "3.TxData");
            CTOS_LCDTPrintXY(1, 5, "4.RxData");
            CTOS_LCDTPrintXY(1, 6, "5.Get Status");
            CTOS_LCDTPrintXY(1, 7, "6.Set Config");
            break;
        case 1:
            CTOS_LCDTPrintXY(1, 1, "    CONFIG    ");
            CTOS_LCDTPrintXY(1, 2, "1.Set");
            CTOS_LCDTPrintXY(1, 3, "2.Get");
            CTOS_LCDTPrintXY(1, 4, "3.SetDialPrecheck");
            CTOS_LCDTPrintXY(1, 5, "4.Hook OFF");
            CTOS_LCDTPrintXY(1, 6, "5.ATCommand");
            break;
    }
}

/* ==========================================================================
 *
 * FUNCTION NAME: ModemDialUp
 *
 * DESCRIPTION:   Dial up to connect the host or hang up
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ========================================================================== */
void ModemDialUp(BYTE isUP) {
    if (isUP) {

        //Dial up to connect the host //
        ret = CTOS_ModemDialup((BYTE *) baPhoneNO, strlen(baPhoneNO));
        CTOS_LCDTPrintXY(1, 8, "DialUp...");

        //Check whether connect success //
        while (1) {
            //Cancel connect the host
            CTOS_KBDHit(&key);
            if (key == d_KBD_CANCEL) {
                //Hang up
                CTOS_ModemHookOn();
                CTOS_LCDTPrintXY(11, 8, "Cancal");
                return;
            }
            //Get the status of modem //
            CTOS_ModemStatus(&dwStatus);
            if (!(dwStatus & d_M_STATUS_DIALING)) {
                //Connect success to the host //
                if (dwStatus & d_M_STATUS_MODEM_ONLINE) {
                    CTOS_LCDTPrintXY(11, 8, "OK");
                    CTOS_LCDTPrintXY(1, 2, "1.Hang Up    ");
                    isDialUp = TRUE;
                } else { //Connect fail to the host //
                    CTOS_LCDTPrintXY(11, 8, "Fail");
                    isDialUp = FALSE;
                }
                return;
            }
        }
        ///////////////////////////////////////////////
    } else {
        //Hook on the modem (Hang up) //
        ret = CTOS_ModemHookOn();
        if (ret == d_OK) {
            CTOS_LCDTPrintXY(1, 2, "1.Dial Up    ");
            CTOS_LCDTPrintXY(1, 8, "Hang UP         ");
            isDialUp = FALSE;
        }
    }
}

/* ==========================================================================
 *
 * FUNCTION NAME: ModemListen
 *
 * DESCRIPTION:   Listem & wait to host connecting
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ========================================================================== */
void ModemListen(BYTE isON) {

    //Declare Local Variable //
    BYTE baATCmd[d_BUFF_SIZE], baRep[d_BUFF_SIZE];
    USHORT usATCmdLen, usRepLen;

    //Listen Strart //
    if (isON) {
        CTOS_LCDTPrintXY(1, 8, "Listen...");

        //Wait to host connecting //
        ret = CTOS_ModemListen(1);
        while (1) {
            CTOS_KBDHit(&key);
            if (key == d_KBD_CANCEL) {
                CTOS_LCDTPrintXY(11, 8, "Cancal");
                return;
            }
            CTOS_ModemStatus(&dwStatus);
            if (dwStatus & d_M_STATUS_LISTENING) {
                CTOS_LCDTPrintXY(11, 8, "OK");
                CTOS_LCDTPrintXY(1, 3, "2.Listen (ON)  ");
                isListen = TRUE;
                return;
            } else {
                CTOS_LCDTPrintXY(11, 8, "Fail");
                isListen = FALSE;
                return;
            }
        }
    } else { //Listen Stop //

        CTOS_ModemClose();
        CTOS_Delay(500);
        CTOS_ModemOpen(d_M_MODE_AYNC_FAST, d_M_HANDSHAKE_V22_ONLY, d_M_COUNTRY_TAIWAN);
        CTOS_LCDTPrintXY(1, 3, "2.Listen (OFF)");
        CTOS_LCDTPrintXY(1, 8, "Listen Stop     ");
        isListen = FALSE;
    }
}

/* ==========================================================================
 *
 * FUNCTION NAME: ModemTxData
 *
 * DESCRIPTION:   Send data to the host via the modem channel
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ========================================================================== */
void ModemTxData(void) {
    //Declare Local Variable //
    DWORD dwStatus;
    int i, iLength = 0;

    CTOS_LCDTClearDisplay();
    CTOS_LCDTPrintXY(1, 1, "----Tx Data----");

    CTOS_LCDTPrintXY(1, 2, "Send Data....");
    CTOS_LCDTPrintXY(1, 3, "Length=");

    //Check modem whether ready to transmit data
    if (CTOS_ModemTxReady() == d_OK) {

        //Transmit data via the modem channel //
        CTOS_ModemTxData((BYTE *) TestData, sizeof (TestData));
        iLength = sizeof (TestData);
        sprintf(&babuff[100], "%dbyte", iLength);
        CTOS_LCDTPrintXY(8, 3, &babuff[100]);
        CTOS_Delay(1000);
    } else {
        CTOS_LCDTPrintXY(1, 7, "Tx Data Fail");
    }

    //Go back to main() //
    CTOS_LCDTPrintXY(1, 8, "Exit->'X'");
    CTOS_KBDGet(&key);
    if (key == d_KBD_CANCEL) {
        show_screen(0);
    }
}

/* ==========================================================================
 *
 * FUNCTION NAME: ModemRxData
 *
 * DESCRIPTION:   Receive data from the host via modem channel
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ========================================================================== */
void ModemRxData(void) {
    //Declare Local Variable //
    USHORT usr_Len = 0, usR_Len = 0;

    CTOS_LCDTClearDisplay();
    CTOS_LCDTPrintXY(1, 1, "----Rx Data----");
    CTOS_LCDTPrintXY(1, 8, "Exit->'X'");
    memset(babuff, 0x00, sizeof (babuff));
    usr_Len = sizeof (babuff);
    CTOS_LCDTPrintXY(1, 2, "Receive Data....");
    CTOS_LCDTPrintXY(1, 3, "Length=");

    while (1) {
        //Check if the data is currently available in Modem //
        ret = CTOS_ModemRxReady(&usr_Len);
        if (ret == d_OK) {
            //Receive data via the modem channel //
            CTOS_ModemRxData(&babuff[usR_Len], &usr_Len);
            usR_Len += usr_Len;
            sprintf(&babuff[100], "%dbytes", usR_Len);
            CTOS_LCDTPrintXY(8, 3, &babuff[100]);

            CTOS_Delay(1000);
        } else {
            CTOS_LCDTPrintXY(1, 8, "RxReady Failed");
        }

        CTOS_KBDHit(&key);

        //Go back to main() //
        if (key == d_KBD_CANCEL) {
            //Clear the receive buffer of Modem //
            CTOS_ModemFlushRxData();
            show_screen(0);
            return;
        }
    }
}

/* ==========================================================================
 *
 * FUNCTION NAME: GetModemStatus
 *
 * DESCRIPTION:   Get Modem current status
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ========================================================================== */
void GetModemStatus(void) {
    //Declare Local Variable //
    DWORD dwStatus;
    int i = 2;

    CTOS_LCDTClearDisplay();
    CTOS_LCDTPrintXY(1, 1, "  Modem Status  ");

    //Get the status of the modem //
    CTOS_ModemStatus(&dwStatus);
    if (dwStatus & d_M_STATUS_MODEM_ONLINE) {
        CTOS_LCDTPrintXY(1, i, "Modem Online");
        i++;
    }
    if (dwStatus & d_M_STATUS_SDLC_MODE) {
        CTOS_LCDTPrintXY(1, i, "SDLC Mode");
        i++;
    }
    if (dwStatus & d_M_STATUS_SDLC_ONLINE) {
        CTOS_LCDTPrintXY(1, i, "SDLC Online");
        i++;
    }
    if (dwStatus & d_M_STATUS_DIALING) {
        CTOS_LCDTPrintXY(1, i, "Dialing");
        i++;
    }
    if (dwStatus & d_M_STATUS_NO_DIAL_TONE) {
        CTOS_LCDTPrintXY(1, i, "No Dial Tone");
        i++;
    }
    if (dwStatus & d_M_STATUS_LINE_BUSY) {
        CTOS_LCDTPrintXY(1, i, "Line Busy");
        i++;
    }
    if (dwStatus & d_M_STATUS_RING_BACK) {
        CTOS_LCDTPrintXY(1, i, "Ring Back");
        i++;
    }
    if (dwStatus & d_M_STATUS_TX_BUSY) {
        CTOS_LCDTPrintXY(1, i, "Tx Busy");
        i++;
    }
    if (dwStatus & d_M_STATUS_REMOTE_NOT_ANSWER) {
        CTOS_LCDTPrintXY(1, i, "Remote Not Answer");
        i++;
    }
    if (dwStatus & d_M_STATUS_NO_CARRIER) {
        CTOS_LCDTPrintXY(1, i, "NO Carrier");
        i++;
    }
    if (dwStatus & d_M_STATUS_ALL_DATA_SENT) {
        CTOS_LCDTPrintXY(1, i, "All Data Sent");
        i++;
    }
    if (dwStatus & d_M_STATUS_RX_DATA_VALID) {
        CTOS_LCDTPrintXY(1, i, "Rx Data Vaild");
        i++;
    }
    if (dwStatus & d_M_STATUS_LISTENING) {
        CTOS_LCDTPrintXY(1, i, "Listening");
        i++;
    }
    if (dwStatus & d_M_STATUS_OTHER_ERROR) {
        CTOS_LCDTPrintXY(1, i, "Other Error");
        i++;
    }
    if (dwStatus & d_M_STATUS_DATA_SENT_ERROR) {
        CTOS_LCDTPrintXY(1, i, "Data Sent Error");
        i++;
    }

    CTOS_KBDGet(&key);
    show_screen(0);
}

/* ==========================================================================
 *
 * FUNCTION NAME: ModemConfig
 *
 * DESCRIPTION:   Set or get modem configuration
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ========================================================================== */
void ModemConfig(BYTE bConfigMode) { //bConfigMode = '1'->Set, '2'->Get

    //Declare Local Variable //
    USHORT usValue;

    if (bConfigMode == '1') { //Set the modem configuration //

        //After set the config, print the setting status //
        if (CTOS_ModemSetConfig(d_M_CONFIG_DAILING_DURATION, 30) == d_OK) CTOS_PrinterPutString("\nDailing Diration OK");
        else CTOS_PrinterPutString("\nDailing Diration Fail");

        if (CTOS_ModemSetConfig(d_M_CONFIG_MIN_ONHOOK_DURATION, 3) == d_OK) CTOS_PrinterPutString("\nMin OnHook Duration OK");
        else CTOS_PrinterPutString("\nMin OnHook Duration Fail");

        if (CTOS_ModemSetConfig(d_M_CONFIG_PREDIAL_DELAY_TIME, 0) == d_OK) CTOS_PrinterPutString("\nPreDial Delay Tiem OK");
        else CTOS_PrinterPutString("\nPreDial Delay Tiem Fail");

        if (CTOS_ModemSetConfig(d_M_CONFIG_DIAL_TONE_DETECT_DURATION, 7000) == d_OK) CTOS_PrinterPutString("\nDial Tone Detect Duration OK");
        else CTOS_PrinterPutString("\nDial Tone Detect Duration Fail");

        if (CTOS_ModemSetConfig(d_M_CONFIG_DIAL_TONE_MIN_ON_TIME, 14400) == d_OK) CTOS_PrinterPutString("\nDial Tone Min On Time OK");
        else CTOS_PrinterPutString("\nDial Tone Min On Time Fail");

        if (CTOS_ModemSetConfig(d_M_CONFIG_DTMF_ON_TIME, 100) == d_OK) CTOS_PrinterPutString("\nDTMF On Time OK");
        else CTOS_PrinterPutString("\nDTMF On Time Fail");

        if (CTOS_ModemSetConfig(d_M_CONFIG_DTMF_OFF_TIME, 100) == d_OK) CTOS_PrinterPutString("\nDTMF Off Time OK");
        else CTOS_PrinterPutString("\nDTMF Off Time Fail");

        if (CTOS_ModemSetConfig(d_M_CONFIG_BUSY_TONE_MIN_TOTAL_TIME, 1728) == d_OK) CTOS_PrinterPutString("\nBusy Tone Min Total Time OK");
        else CTOS_PrinterPutString("\nBusy Tone Min Total Time Fail");

        if (CTOS_ModemSetConfig(d_M_CONFIG_BUSY_TONE_DELTA_TIME, 7632) == d_OK) CTOS_PrinterPutString("\nBusy Tone Delta Time OK");
        else CTOS_PrinterPutString("\nBusy Tone Delta Time Fail");

        if (CTOS_ModemSetConfig(d_M_CONFIG_BUSY_TONE_MIN_ON_TIME, 864) == d_OK) CTOS_PrinterPutString("\nBusy Tone Min On Time OK");
        else CTOS_PrinterPutString("\nBusy Tone Min On Time Fail");

        if (CTOS_ModemSetConfig(d_M_CONFIG_RINGBACK_TONE_MIN_TOTAL_TIME, 18000) == d_OK) CTOS_PrinterPutString("\nRingBack Tone Min Total OK");
        else CTOS_PrinterPutString("\nRingBack Tone Min Total Fail");

        if (CTOS_ModemSetConfig(d_M_CONFIG_RINGBACK_TONE_DELTA_TIME, 61200) == d_OK) CTOS_PrinterPutString("\nRingBack Tone Delta Time OK");
        else CTOS_PrinterPutString("\nRingBack Tone Delta Time Fail");

        if (CTOS_ModemSetConfig(d_M_CONFIG_RINGBACK_TONE_MIN_ON_TIME, 4608) == d_OK) CTOS_PrinterPutString("\nRingBack Tone Delta Time OK");
        else CTOS_PrinterPutString("\nRingBack Tone Delta Time Fail");

        if (CTOS_ModemSetConfig(d_M_CONFIG_ANSWER_TONE_WAIT_DURATION, 50) == d_OK) CTOS_PrinterPutString("\nAnswer Tone Wait Duration OK");
        else CTOS_PrinterPutString("\nAnswer Tone Wait Duration Fail");

        if (CTOS_ModemSetConfig(d_M_CONFIG_BLIND_DIAL_DELAY_TIME, 2) == d_OK) CTOS_PrinterPutString("\nBlind Dial Delay Time OK");
        else CTOS_PrinterPutString("\nBlind Dial Delay Time Fail");

        if (CTOS_ModemSetConfig(d_M_CONFIG_CARRIER_PRESENT_TIME, 6) == d_OK) CTOS_PrinterPutString("\nCarrier Present Time OK");
        else CTOS_PrinterPutString("\nCarrier Present Time Fail");

    } else { //Read the modem configuration //

        //Print the configuration //
        CTOS_ModemReadConfig(d_M_CONFIG_DAILING_DURATION, &usValue);
        sprintf(babuff, "\nDailing Duration = \n%d", usValue);
        CTOS_PrinterPutString(babuff);
        CTOS_ModemReadConfig(d_M_CONFIG_MIN_ONHOOK_DURATION, &usValue);
        sprintf(babuff, "\nMin OnHook Duration = \n%d", usValue);
        CTOS_PrinterPutString(babuff);
        CTOS_ModemReadConfig(d_M_CONFIG_PREDIAL_DELAY_TIME, &usValue);
        sprintf(babuff, "\nPreDial Delay Tiem = \n%d", usValue);
        CTOS_PrinterPutString(babuff);
        CTOS_ModemReadConfig(d_M_CONFIG_DIAL_TONE_DETECT_DURATION, &usValue);
        sprintf(babuff, "\nDial Tone Detect Duration = \n%d", usValue);
        CTOS_PrinterPutString(babuff);
        CTOS_ModemReadConfig(d_M_CONFIG_DIAL_TONE_MIN_ON_TIME, &usValue);
        sprintf(babuff, "\nDial Tone Min On Time = \n%d", usValue);
        CTOS_PrinterPutString(babuff);
        CTOS_ModemReadConfig(d_M_CONFIG_DTMF_ON_TIME, &usValue);
        sprintf(babuff, "\nDTMF On Time = \n%d", usValue);
        CTOS_PrinterPutString(babuff);
        CTOS_ModemReadConfig(d_M_CONFIG_DTMF_OFF_TIME, &usValue);
        sprintf(babuff, "\nDTMF Off Time = \n%d", usValue);
        CTOS_PrinterPutString(babuff);
        CTOS_ModemReadConfig(d_M_CONFIG_BUSY_TONE_MIN_TOTAL_TIME, &usValue);
        sprintf(babuff, "\nBusy Tone Min Total Time = \n%d", usValue);
        CTOS_PrinterPutString(babuff);
        CTOS_ModemReadConfig(d_M_CONFIG_BUSY_TONE_DELTA_TIME, &usValue);
        sprintf(babuff, "\nBusy Tone Delta Time = \n%d", usValue);
        CTOS_PrinterPutString(babuff);
        CTOS_ModemReadConfig(d_M_CONFIG_BUSY_TONE_MIN_ON_TIME, &usValue);
        sprintf(babuff, "\nBusy Tone Min On Time = \n%d", usValue);
        CTOS_PrinterPutString(babuff);
        CTOS_ModemReadConfig(d_M_CONFIG_RINGBACK_TONE_MIN_TOTAL_TIME, &usValue);
        sprintf(babuff, "\nRingBack Tone Min Total Time = \n%d", usValue);
        CTOS_PrinterPutString(babuff);
        CTOS_ModemReadConfig(d_M_CONFIG_RINGBACK_TONE_DELTA_TIME, &usValue);
        sprintf(babuff, "\nRingBack Tone Delta Time = \n%d", usValue);
        CTOS_PrinterPutString(babuff);
        CTOS_ModemReadConfig(d_M_CONFIG_RINGBACK_TONE_MIN_ON_TIME, &usValue);
        sprintf(babuff, "\nRing Back Tone Min On Time = \n%d", usValue);
        CTOS_PrinterPutString(babuff);
        CTOS_ModemReadConfig(d_M_CONFIG_ANSWER_TONE_WAIT_DURATION, &usValue);
        sprintf(babuff, "\nAnswer Tone Wait Duration = \n%d", usValue);
        CTOS_PrinterPutString(babuff);
        CTOS_ModemReadConfig(d_M_CONFIG_BLIND_DIAL_DELAY_TIME, &usValue);
        sprintf(babuff, "\nBlind Dial Delay Time = \n%d", usValue);
        CTOS_PrinterPutString(babuff);
        CTOS_ModemReadConfig(d_M_CONFIG_CARRIER_PRESENT_TIME, &usValue);
        sprintf(babuff, "\nCarrier Present Time = \n%d", usValue);
        CTOS_PrinterPutString(babuff);
    }
    CTOS_PrinterFline(d_LINE_DOT * 10);
    show_screen(0);
}

/* ==========================================================================
 *
 * FUNCTION NAME: SetDialPrecheck
 *
 * DESCRIPTION:   Set precheck parameters
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ========================================================================== */
void SetDialPrecheck(void) {
    CTOS_LCDTClearDisplay();
    CTOS_LCDTPrintXY(1, 1, " Dial Precheck ");
    CTOS_LCDTPrintXY(1, 2, "1.No Dial Tone or Busy"); //No detect dial tone or busy //
    CTOS_LCDTPrintXY(1, 3, "2.Only Dial Tone"); //Only detect dial tone //
    CTOS_LCDTPrintXY(1, 4, "3.Only Busy"); //Only detect busy //
    CTOS_LCDTPrintXY(1, 5, "4.Dial Tone and Busy"); //Detect dial tone and busy (default) //
    CTOS_LCDTPrintXY(1, 6, "5.ALL"); //Detect dial tone, busy, and ringback //

    while (1) {
        CTOS_KBDGet(&key);
        switch (key) {
            case d_KBD_1:
            case d_KBD_2:
            case d_KBD_3:
            case d_KBD_4:
            case d_KBD_5:
                //Set precheck parameters for dialing up //
                ret = CTOS_ModemSetDialPrecheck(key - 0x31); //The hex value of key is 0x31, the mode of the dial precheck start 0x00 to 0x04, so (the hex value - 0x31 = dial precheck) //
                if (ret == d_OK) CTOS_LCDTPrintXY(1, 8, "Set.....OK");
                else CTOS_LCDTPrintXY(1, 8, "Set.....Fail");
                break;
            case d_KBD_CANCEL:

                //Go back to main() //
                show_screen(0);
                return;
                break;
        }
    }

}

/** 
 ** The main entry of the terminal application 
 **/
int main(int argc, char *argv[]) {
    BYTE baAt_cmd[d_BUFF_SIZE];
    USHORT usReqLen;

    // TODO: Add your program here //
    CTOS_LCDTSelectFontSize(0x101E);

    // Initial
    isDialUp = FALSE;
    isListen = FALSE;
    memset(baAt_cmd, 0x00, sizeof (baAt_cmd));

    // Open Modem channel
    CTOS_LCDTPrintXY(1, 1, " OPEN Modem ");
    ret = CTOS_ModemOpen(d_M_MODE_AYNC_NORMAL, d_M_HANDSHAKE_V90_AUTO_FB, d_M_COUNTRY_TAIWAN);
    if (ret != d_OK) {
        CTOS_LCDTPrintXY(1, 2, " OPEN Fail ");
        return 0;
    }
    CTOS_LCDTPrintXY(1, 1, " OPEN OK ");
    show_screen(0);

    while (1) {
        CTOS_KBDGet(&key);
        switch (key) {
            case d_KBD_1:
                // Dial up or hang up via modem channel
                ModemDialUp(!isDialUp);
                break;
            case d_KBD_2:
                // Start or Stop Listen
                ModemListen(!isListen);
                break;
            case d_KBD_3:
                ModemTxData();
                break;
            case d_KBD_4:
                ModemRxData();
                break;
            case d_KBD_5:
                GetModemStatus();
                break;
            case d_KBD_6:
                show_screen(1);
                CTOS_KBDGet(&key);
                switch (key) {
                    case d_KBD_1:
                    case d_KBD_2:
                        ModemConfig(key);
                        break;
                    case d_KBD_3:
                        SetDialPrecheck();
                        break;
                    case d_KBD_4:
                        ret = CTOS_ModemHookOff();
                        sprintf(babuff, "ret = 0x%04X", ret);
                        CTOS_LCDTPrintXY(1, 8, babuff);
                        break;
                    case d_KBD_5:
                        // AT Command: Disable V.42 bis and MNP5 data compression
                        // Wait for dial tone delay = 20 seconds
                        memcpy(baAt_cmd, "AT%C0\rATS14=20\r", strlen("AT%C0\rATS14=20\r"));
                        CTOS_LCDTPrintXY(1, 7, baAt_cmd);
                        CTOS_ModemATCommand(baAt_cmd, strlen(baAt_cmd), babuff, &usReqLen);
                        CTOS_LCDTPrintXY(1, 8, babuff);
                        break;
                    case d_KBD_CANCEL:
                        show_screen(0);
                        break;
                }
                break;
            case d_KBD_CANCEL:
                CTOS_ModemClose();
                return 0;
                break;
        }
    }

    exit(0);
}

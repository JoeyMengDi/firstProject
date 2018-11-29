/*=========================================*
 *             I N C L U D E S             *
 *=========================================*/
#include <string.h>
#include <stdio.h>
#include <ctosapi.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

#include <ctos_clapi.h>

#include "deftype.h"
#include "ByteStream.h"
#include "DbgMacro.h"

/*==========================================*
 *            D E F I N E S                 *
 *==========================================*/
#define d_BUFF_SIZE   128   //Buffer Size


CDebugInfo cDebug;

USHORT MultiCardGetCard(BYTE pbyATQA, BYTE pbySAK, BYTE pbyCSN, BYTE pbyCSNLen) {

    DEBUG_ENABLE(1, 0, DEBUGINFO_NORMAL, NULL);
    DEBUG_ENTRY();
    USHORT api_ret, api_2nd_try_ret, api_RAT_ret;
    BYTE local_ATQA[2];
    BYTE local_SAK;
    BYTE local_CSN_LEN;
    BYTE local_CSN[10];
    BYTE local2_ATQA[2];
    BYTE local2_SAK;
    BYTE local2_CSN_LEN;
    BYTE local2_CSN[10];
    CTOS_CLTypeAHalt();
    CTOS_CLDESELECT(); //add by sandy at 20110928 for 14443-3 & 14443-4 Switch
    CTOS_CLPowerOff();
    CTOS_Delay(5);
    CTOS_CLPowerOn();
    CTOS_Delay(5);
    // Detect any card?
    api_ret = CTOS_CLTypeAActiveFromIdle(0, local_ATQA, &local_SAK, local_CSN, &local_CSN_LEN);
    if (api_ret == 0x83E8)/*MULTI CARD*/ {
        return 1;
    }

    if (api_ret != d_OK) {
        //add by sandy at 20110928 for ezCube
        //U0Printf("1");
        CTOS_Delay(3);
        api_ret = CTOS_CLTypeAActiveFromIdle(0, local_ATQA, &local_SAK, local_CSN, &local_CSN_LEN);
        //end add
        if (api_ret == 0x83E8)/*MULTI CARD*/ {
            DEBUG_INFO(DEBUGINFO_NORMAL, "api_ret:%s\n", (BYTE*) "222");
            return 2;
        }

        if (api_ret != d_OK) {
            DEBUG_INFO(DEBUGINFO_NORMAL, "api_ret:%X\n", api_ret);
            //U0Printf("1-1=%04X",api_ret);   ERROR_PRET_RFID_ACCESS_FAIL
            return 3;
        }
        DEBUG_INFO(DEBUGINFO_NORMAL, "api_ret:%s\n", (BYTE*) "erro3");
    }


    // Ask the found card to sleep
    api_ret = CTOS_CLTypeAHalt();
    if (api_ret != d_OK) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "api_ret:%s\n", (BYTE*) "444");
        //U0Printf("2");
        return 4;
    }
    // Detect another card
    api_2nd_try_ret = CTOS_CLTypeAActiveFromIdle(0, local2_ATQA, &local2_SAK, local2_CSN, &local2_CSN_LEN);
    if (api_2nd_try_ret == 0x83E8)/*MULTI CARD*/ {
        DEBUG_INFO(DEBUGINFO_NORMAL, "api_ret:%s\n", (BYTE*) "555");
        return 5;
    }

    if (api_2nd_try_ret == d_OK) {
        // if we find another card, this is not what we want
        // shutdown the second card.
        //CTOS_CLDESELECT();
        CTOS_CLTypeAHalt();
        //U0Printf("3");
    }
    // activate the 1st card
    api_ret = CTOS_CLTypeAActiveFromHalt(0, local_ATQA, &local_SAK, local_CSN, local_CSN_LEN);
    if (api_ret == 0x83E8)/*MULTI CARD*/ {
        DEBUG_INFO(DEBUGINFO_NORMAL, "api_ret:%s\n", (BYTE*) "666");
        return 6;
    }

    if (api_ret != d_OK) {
        //U0Printf("4");
        DEBUG_INFO(DEBUGINFO_NORMAL, "api_ret:%s\n", (BYTE*) "777");
        return ( api_2nd_try_ret == d_OK) ? 5 : 6;
    }
    // if there are more than two cards, deactive them all and return error
    if (api_2nd_try_ret == d_OK) {
        // if we find another card, this is not what we want
        // shutdown the 1st card.
        // CTOS_CLDESELECT();
        CTOS_CLTypeAHalt();
        //U0Printf("5");
        DEBUG_INFO(DEBUGINFO_NORMAL, "api_ret:%s\n", (BYTE*) "888");
        return 7;
    }
    //    memcpy(&pbyATQA,local_ATQA,sizeof(local_ATQA));
    pbySAK = local_SAK;
    //    memcpy(&pbyCSN,local_CSN,sizeof(local_CSN));
    //    pbyCSNLen = local_CSN_LEN;


    DEBUG_BYTEBUF(DEBUGINFO_NORMAL, local_ATQA, sizeof (local_ATQA), "local_ATQA is");
    DEBUG_BYTEBUF(DEBUGINFO_NORMAL, local_CSN, sizeof (local_CSN), "local_CSN is");
    DEBUG_BYTEBUF(DEBUGINFO_NORMAL, &local_SAK, sizeof (local_SAK), "local_SAK is");

    return d_OK;
}

USHORT AntiCollisionSample(void) {
    USHORT r;
    BYTE baATQA1[20], bSAK1[20], baTCSN1[20];
    BYTE bTCSNLen1;
    BYTE baATQA2[20], bSAK2[20], baTCSN2[20];
    BYTE bTCSNLen2;
    BYTE bAutoBR;
    BYTE baATS[30];
    USHORT bATSLen;
    BYTE RxBuf[1024];
    USHORT RxLen;
    BYTE ShowTemp[64];
    //==========================================================================
    // Type A check
    CTOS_LCDTPrintXY(1, 1, (BYTE*) "Put Contactless Card");
    while (1) {
        bTCSNLen1 = sizeof (baTCSN1);
        r = CTOS_CLTypeAActiveFromIdle(0, baATQA1, bSAK1, baTCSN1, &bTCSNLen1);
        if (r == d_OK) break;
    }
    r = CTOS_CLTypeAHalt();
    if (r != d_OK) {
        CTOS_LCDTPrintXY(1, 2, (BYTE*) "Halt Error");
        return -1;
    }
    memset(ShowTemp, 0x00, sizeof (ShowTemp));
    int len = 3;
    //sprintf(ShowTemp,"%d",len);
    sprintf((CHAR*) ShowTemp, "%02X %02X %02X %02X", baTCSN1[0], baTCSN1[1], baTCSN1[2], baTCSN1[3]);
    CTOS_LCDTPrintXY(1, 2, (BYTE*) "Card 1 SN:");
    CTOS_LCDTPrintXY(1, 3, ShowTemp);
    bTCSNLen2 = sizeof (baTCSN2);
    r = CTOS_CLTypeAActiveFromIdle(0, baATQA2, bSAK2, baTCSN2, &bTCSNLen2);
    if (r != 0x83E5) {
        memset(ShowTemp, 0x00, sizeof (ShowTemp));
        sprintf((CHAR*) ShowTemp, "%02X %02X %02X %02X", baTCSN2[0], baTCSN2[1], baTCSN2[2],
                baTCSN2[3]);
        CTOS_LCDTPrintXY(1, 4, (BYTE*) "Card 2 SN:");
        CTOS_LCDTPrintXY(1, 5, ShowTemp);
        CTOS_LCDTPrintXY(1, 8, (BYTE*) "anti-collision");
        return -1;
    }
    r = CTOS_CLTypeAActiveFromHalt(0, baATQA1, bSAK1, baTCSN1, bTCSNLen1);
    if (r != d_OK) {
        CTOS_LCDTPrintXY(1, 7, (BYTE*) "Active Halt Error");
        return -1;
    }

    r = CTOS_CLRATS(bAutoBR, baATS, &bATSLen);
    if (r != d_OK) {
        CTOS_LCDTPrintXY(1, 7, (BYTE*) "RATS Error");
        return -1;
    }
    r = CTOS_CLDESELECT();
    if (r != d_OK) {
        CTOS_LCDTPrintXY(1, 7, (BYTE*) "Deselect Error");
        return -1;
    }
    r = CTOS_CLTypeAActiveFromHalt(0, baATQA1, bSAK1, baTCSN1, bTCSNLen1);
    if (r != d_OK) {
        CTOS_LCDTPrintXY(1, 7, (BYTE*) "Active Halt Error");
        return -1;
    }
    r = CTOS_CLRATS(bAutoBR, baATS, &bATSLen);
    if (r != d_OK) {
        CTOS_LCDTPrintXY(1, 7, (BYTE*) "RATS Error");
        return -1;
    }
    r = CTOS_CLAPDU((BYTE*) "\x00\x00\x00\x00\x00", 5, RxBuf, &RxLen);
    if (r != d_OK) {
        CTOS_LCDTPrintXY(1, 7, (BYTE*) "APDU Error");
        return -1;
    }
}

/* ==========================================================================
 *
 * FUNCTION NAME: main
 *
 * DESCRIPTION:   function main is responsible for all the tasks listed in the
 *                introduction to this demo.
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ========================================================================== */
int main(int argc, char *argv[]) {

    //    DEBUG_ENABLE(1, 0, DEBUGINFO_NORMAL, NULL);
    //    DEBUG_ENTRY();

    /************************************************************************/
    CTOS_LCDTSelectFontSize(d_LCD_FONT_8x8);
    while (1) {
        CTOS_LCDTSelectFontSize(d_LCD_FONT_8x8);
        while (1) {
            AntiCollisionSample();
            CTOS_Delay(2000);
            CTOS_LCDTClearDisplay();
        }
    }

    /************************************************************************/



















    //Declare Local Variable //
    BYTE key;
    BYTE bStatus;
    BYTE baATR[d_BUFF_SIZE], bATRLen, CardType;
    BYTE baSAPDU[d_BUFF_SIZE], baRAPDU[d_BUFF_SIZE];
    USHORT bSLen, bRLen;
    BYTE baMySAPDU[d_BUFF_SIZE] = {0}, baMyRAPDU[d_BUFF_SIZE] = {0}; //personal test data

    //sysheap_setup ( 256 * 1024 ); // initial newlib and create 256K heap

    // TODO: Add your program here //  
    CTOS_LCDTSelectFontSize(0x101E);
    CTOS_LCDTClearDisplay();

    CTOS_LCDTSetReverse(TRUE);
    CTOS_LCDTPrintXY(1, 1, (BYTE*) "Smart Card");
    CTOS_LCDTSetReverse(FALSE);

    CTOS_LCDTPrintXY(1, 2, (BYTE*) "Plz Ins Card");

    do {
        CTOS_KBDHit(&key);
        if (key == d_KBD_CANCEL) return -1;
        //Check the ICC status //
        CTOS_SCStatus(d_SC_USER, &bStatus);
    } while (!(bStatus & d_MK_SC_PRESENT)); //Break until the ICC Card is inserted //

    bATRLen = sizeof (baATR);
    CTOS_LCDTPrintXY(1, 3, (BYTE*) "Reset EMV..");
    //Power on the ICC and retrun the ATR contents metting the EMV2000 specification //
    if (CTOS_SCResetEMV(d_SC_USER, d_SC_5V, baATR, &bATRLen, &CardType) == d_OK) CTOS_LCDTPrintXY(13, 3, (BYTE*) "OK");
    else CTOS_LCDTPrintXY(13, 3, (BYTE*) "Fail");

    CTOS_Delay(1000);
    bATRLen = sizeof (baATR);
    CTOS_LCDTPrintXY(1, 4, (BYTE*) "Reset ISO..");
    //Power on the ICC and retrun the ATR content metting the ISO-7816 specification //
    if (CTOS_SCResetISO(d_SC_USER, d_SC_5V, baATR, &bATRLen, &CardType) == d_OK) CTOS_LCDTPrintXY(13, 4, (BYTE*) "OK");
    else CTOS_LCDTPrintXY(13, 4, (BYTE*) "Fail");

    CTOS_LCDTPrintXY(1, 5, (BYTE*) "Send APDU..");


    /*
    //APDU Data
    baSAPDU[0]=0x00; //CLA
    baSAPDU[1]=0xB2; //INS
    baSAPDU[2]=0x01; //P1
    baSAPDU[3]=0x0C; //P2
    baSAPDU[4]=0x00; //Le
     */


    /*00A4040000*/
    baMySAPDU[0] = 0x00;
    baMySAPDU[1] = 0xA4;
    baMySAPDU[2] = 0x04;
    baMySAPDU[3] = 0x00;
    baMySAPDU[4] = 0x00;


    bSLen = 5;
    bRLen = sizeof (baRAPDU);
    //Send out an APDU command and get the response from ICC //
    if (CTOS_SCSendAPDU(d_SC_USER, baMySAPDU, bSLen, baMyRAPDU, &bRLen) == d_OK) CTOS_LCDTPrintXY(13, 5, (BYTE*) "OK");
    else CTOS_LCDTPrintXY(13, 5, (BYTE*) "Fail");


    /*********************log information**************************/
    //   DEBUG_INFO(DEBUGINFO_NORMAL, "baRAPDU:%s\n", baMyRAPDU);
    //   DEBUG_INFO(DEBUGINFO_NORMAL, "null:%s\n", "");
    //   DEBUG_INFO(DEBUGINFO_NORMAL, "bRLen:%d\n", bRLen);

    //DEBUG_STREAM(DEBUGINFO_NORMAL, "baRAPDU:%s\n", baMyRAPDU);
    DEBUG_BYTEBUF(DEBUGINFO_NORMAL, baMyRAPDU, bRLen, "cSrcData is");
    //DEBUG_STREAM(DEBUGINFO_NORMAL, &cSrcData, "cSrcData is");
    /**************************************************************/



    //Turn off the power of ICC //
    if (CTOS_SCPowerOff(d_SC_USER) == d_OK) CTOS_LCDTPrintXY(1, 6, (BYTE*) "Power off OK");
    else CTOS_LCDTPrintXY(1, 6, (BYTE*) "Power off Fail");

    CTOS_LCDTPrintXY(1, 7, (BYTE*) "Pls Take ICC Out");
    do {
        CTOS_SCStatus(d_SC_USER, &bStatus);
    } while (bStatus & d_MK_SC_PRESENT); //Break until the ICC Card does not exist //


    exit(0);
}

/*=========================================*
 *             I N C L U D E S             *
 *=========================================*/
#include <string.h>
#include <stdio.h>
#include <ctosapi.h>
#include <stdlib.h>
#include <stdarg.h>
//#include <ctos_newlib_startup.h>

#include "deftype.h"
#include "ByteStream.h"
#include "DbgMacro.h"

CDebugInfo cDebug;

/*==========================================*
 *            D E F I N E S                 *
 *==========================================*/
#define d_BUFF_SIZE 128

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
    
    DEBUG_ENABLE(1, 0, DEBUGINFO_NORMAL, NULL);
    DEBUG_ENTRY();
    
    
    USHORT rtn;
    BYTE key;
    USHORT usTk1Len, usTk2Len, usTk3Len; //Track 1,2,3 length //
    BYTE baTk1Buf[d_BUFF_SIZE], baTk2Buf[d_BUFF_SIZE], baTk3Buf[d_BUFF_SIZE]; //Track 1,2,3 data buffer //
    BYTE baTk1Err, baTk2Err, baTk3Err; //Track 1,2,3 individual status //
    BYTE baBuff[d_BUFF_SIZE];

    CTOS_LCDTSelectFontSize(0x101E);
    CTOS_LCDTClearDisplay();
    CTOS_LCDTSetReverse(TRUE);
    CTOS_LCDTPrintXY(1, 1, (BYTE*) "----MSR Test----");
    CTOS_LCDTSetReverse(FALSE);
    CTOS_LCDTPrintXY(1, 3, (BYTE*) "Pls Swipe MSR...");

    CTOS_MSRRead(baTk1Buf, &usTk1Len, baTk2Buf, &usTk2Len, baTk3Buf, &usTk3Len);
    do {
        CTOS_KBDHit(&key);
        if (key == d_KBD_CANCEL) return 1;

        usTk1Len = usTk2Len = usTk3Len = d_BUFF_SIZE;
        rtn = CTOS_MSRRead(baTk1Buf, &usTk1Len, baTk2Buf, &usTk2Len, baTk3Buf, &usTk3Len);

    } while (rtn != d_OK || (usTk1Len == 0 && usTk2Len == 0 && usTk3Len == 0));
    
    /********************log information***********************/
    DEBUG_INFO(DEBUGINFO_NORMAL, "%s\n", baTk1Buf);
    DEBUG_INFO(DEBUGINFO_NORMAL, "%s\n", baTk2Buf);
    DEBUG_INFO(DEBUGINFO_NORMAL, "%s\n", baTk3Buf);
    /**********************************************************/
    
    
    
    memset(baBuff, 0x00, sizeof (baBuff));
    sprintf((CHAR*) baBuff, "Track 1 Len = %d", usTk1Len);
    CTOS_LCDTPrintXY(1, 2, baBuff); //Display the track 1 data length in the 2 line //

    sprintf((CHAR*) baBuff, "Track 2 Len = %d", usTk2Len);
    CTOS_LCDTPrintXY(1, 3, baBuff); //Display the track 2 data length in the 3 line //

    sprintf((CHAR*) baBuff, "Track 3 Len = %d", usTk3Len);
    CTOS_LCDTPrintXY(1, 4, baBuff); //Display the track 3 data length in the 4 line //

    //Get the individual status of each track of last swipe of magnetic card //
    rtn = CTOS_MSRGetLastErr(&baTk1Err, &baTk2Err, &baTk3Err);
    sprintf((CHAR*) baBuff, "Track1Err %02X", baTk1Err);
    CTOS_LCDTPrintXY(1, 5, baBuff); //Display the track 1 individual status in the 5 line //

    sprintf((CHAR*) baBuff, "Track2Err %02X", baTk2Err);
    CTOS_LCDTPrintXY(1, 6, baBuff); //Display the track 2 individual status in the 6 line //

    sprintf((CHAR*) baBuff, "Track3Err %02X", baTk3Err);
    CTOS_LCDTPrintXY(1, 7, baBuff); //Display the track 3 individual status in the 7 line //

    CTOS_LCDTPrintXY(1, 8, (BYTE*) "Press Any Key...");
    CTOS_KBDGet(&key);

    exit(0);
}

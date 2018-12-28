/** 
 **	A Template for developing new terminal application
 **/

#include "../SRC/StdafxHead.h"
#include "libVKBD.h"
#include "newfile.h"
#ifndef OK 
#define OK      00
#endif

#define TIMEOUT         0x2000
#define FAIl            0x2001

WORD HitKey(void);
WORD GetKey(void);
void GetBuf();



CDebugInfo cDebug;

/** 
 ** The main entry of the terminal application 
 **/
int main(int argc, char *argv[]) {
    DEBUG_ENABLE(1, 0, DEBUGINFO_NORMAL, NULL);
    DEBUG_ENTRY();

    BYTE byKey = d_KBD_INVALID;
    BOOL bTurnOn = TRUE;

    CTOS_LCDTClearDisplay();
    CTOS_LCDTPrintXY(1, 1, (BYTE*) "VirtualKBD Test AP");
    CTOS_LCDTPrintXY(1, 2, (BYTE*) "Select Default Mode");
    CTOS_LCDTPrintXY(1, 3, (BYTE*) "1:Number");
    CTOS_LCDTPrintXY(1, 4, (BYTE*) "2:Letter");
    CTOS_LCDTPrintXY(1, 5, (BYTE*) "3:CAP Letter");
    CTOS_LCDTPrintXY(1, 6, (BYTE*) "4:Special Character");

    byKey = d_KBD_INVALID;
    CTOS_KBDGet(&byKey);

    if (byKey == d_KBD_CANCEL)
        return DEBUG_RETCODE("exit", OK);

    switch (byKey) {
        case d_KBD_1:
            CTAP_VirtualKBDSetDefaultMode(VKBD_NUMBER_MODE);
            break;

        case d_KBD_2:
            CTAP_VirtualKBDSetDefaultMode(VKBD_LETTER_MODE);
            break;

        case d_KBD_3:
            CTAP_VirtualKBDSetDefaultMode(VKBD_CAP_LETTER_MODE);
            break;

        case d_KBD_4:
            CTAP_VirtualKBDSetDefaultMode(VKBD_SPECIAL_CHARACTER_MODE);
            break;

        default:
            CTAP_VirtualKBDSetDefaultMode(VKBD_NUMBER_MODE);
            break;
    }

    CTOS_LCDTClearDisplay();
    CTOS_LCDTPrintXY(1, 1, (BYTE*) "VirtualKBD Test AP");
    CTOS_LCDTPrintXY(1, 2, (BYTE*) "1:Open");
    CTOS_LCDTPrintXY(11, 2, (BYTE*) "2:Close");
    CTOS_LCDTPrintXY(1, 3, (BYTE*) "3:Show");
    CTOS_LCDTPrintXY(11, 3, (BYTE*) "4:Hide");
    CTOS_LCDTPrintXY(1, 4, (BYTE*) "5:Sound");
    CTOS_LCDTPrintXY(11, 4, (BYTE*) "6:ClearBuf");
    CTOS_LCDTPrintXY(1, 5, (BYTE*) "7:HitKey");
    CTOS_LCDTPrintXY(11, 5, (BYTE*) "8:GetKey");
    CTOS_LCDTPrintXY(1, 6, (BYTE*) "0:GetDisplay");

    while (1) {
        byKey = d_KBD_INVALID;
        CTOS_KBDGet(&byKey);

        if (byKey == d_KBD_CANCEL)
            break;

        //BYTE byKeyvalue;
        switch (byKey) {
            case d_KBD_1:
                CTAP_VirtualKBDOpen();
                break;

            case d_KBD_2:
                CTAP_VirtualKBDClose();
                break;

            case d_KBD_3:
                CTAP_VirtualKBDShow();
                break;

            case d_KBD_4:
                CTAP_VirtualKBDHide();
                break;

            case d_KBD_5:
                bTurnOn = !bTurnOn;
                CTAP_VirtualKBDSetSound(bTurnOn);
                break;

            case d_KBD_6:
                CTAP_VirtualKBDBufFlush();
                break;
            case d_KBD_7:
                HitKey();
                break;

            case d_KBD_8:
                GetKey();
                break;
            case d_KBD_0:
                GetBuf();
                break;
            default:
                break;
        }
    }

    return DEBUG_EXIT(OK);
}

WORD HitKey(void) {
    DEBUG_ENTRY();

    BYTE byKeyvalue;
    BYTE byKey;
    int n = 0;
    while (1) {
        n++;
        if (n > 3000)
            return DEBUG_RETCODE("Hit Key Timeout", TIMEOUT);

        CTOS_KBDHit(&byKey);
        if (byKey == d_KBD_CANCEL)
            break;

        CTAP_VirtualKBDHit(&byKeyvalue);
        if (byKeyvalue != d_KBD_INVALID) {
            DEBUG_INFO(DEBUGINFO_NORMAL, "-------------------");
            DEBUG_INFO(DEBUGINFO_NORMAL, "key is: %x", byKeyvalue);
            DEBUG_INFO(DEBUGINFO_NORMAL, "-------------------");
            break;
            //            if (byKeyvalue == d_KBD_CANCEL)
            //                break;
        }

        usleep(10000);
    }

    return DEBUG_EXIT(OK);
}

WORD GetKey(void) {
    DEBUG_ENTRY();

    int n = 0;
    while (1) {
        n++;
        if (n > 3000)
            return DEBUG_RETCODE("Hit Key Timeout", TIMEOUT);

        BYTE byKeyvalue;

        CTAP_VirtualKBDGet(&byKeyvalue);
        if (byKeyvalue != d_KBD_INVALID) {
            DEBUG_INFO(DEBUGINFO_NORMAL, "-------------------");
            DEBUG_INFO(DEBUGINFO_NORMAL, "key is: %x", byKeyvalue);
            DEBUG_INFO(DEBUGINFO_NORMAL, "-------------------");
            break;
            //            if (byKeyvalue == d_KBD_CANCEL)
            //                break;
        }

    }

    return DEBUG_EXIT(OK);
}

void GetBuf() {
    CByteStream cData;
    CTAP_VirtualKBDGetDisplayColumnData(cData);
    DEBUG_INFO(DEBUGINFO_NORMAL, "-------------------");
    DEBUG_INFO(1, "dispaly len : %d display: %s", cData.GetLength(), cData.GetBuffer());
    DEBUG_INFO(DEBUGINFO_NORMAL, "-------------------");
}






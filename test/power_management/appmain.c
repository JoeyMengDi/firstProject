/** 
 **	A Template for developing new terminal application
 **/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>

#define d_TIME_GOTO_STANDBY      (3*60) //sec 
#define d_TIME_GOTO_SLEEP        ((10*60)-d_TIME_GOTO_STANDBY) //sec 

USHORT GetIdleSec(CTOS_RTC *pstBase, OUT USHORT *pusIdleSec) {
    USHORT usIdle, usBase;
    CTOS_RTC stRTC;
    CTOS_RTCGet(&stRTC);
    
    usIdle = stRTC.bHour * 60 * 60 + stRTC.bMinute * 60 + stRTC.bSecond;
    usBase = pstBase->bHour * 60 * 60 + pstBase->bMinute * 60 + pstBase->bSecond;

    *pusIdleSec = usIdle - usBase;
}

USHORT SetWakeupTime(USHORT WakeupTime) {
    CTOS_RTC stRTC;
    USHORT sec, ret;
    BYTE buf[20 + 1];

    CTOS_RTCGet(&stRTC);

    sec = stRTC.bHour * 60 * 60 + stRTC.bMinute * 60 + stRTC.bSecond;
    sec += WakeupTime;

    stRTC.bHour = sec / (60 * 60);
    stRTC.bMinute = sec % (60 * 60) / 60;
    stRTC.bSecond = sec % 60;

    ret = CTOS_PowerAwakening((SHORT) stRTC.bSecond, (SHORT) stRTC.bMinute, (SHORT) stRTC.bHour, -1, -1, -1);
    if (ret != d_OK) {
        sprintf(buf, "power awake ret=%04X", ret);
        CTOS_LCDTPrintXY(1, 7, buf);
    }

    return ret;
}

/** 
 ** The main entry of the terminal application 
 **/
int main(int argc, char *argv[]) {
    BYTE key, buf[20 + 1];
    USHORT usIdleTime_sec, ret, usWake;
    CTOS_RTC stRTC;

    memset(&stRTC, 0, sizeof (CTOS_RTC));

    // TODO: Add your program here //
    CTOS_LCDTClearDisplay();

    CTOS_LCDTPrintXY(1, 1, "Power Mode Sample");
    CTOS_LCDTPrintXY(1, 8, "press key start");

    CTOS_KBDGet(&key);

    CTOS_LCDTGotoXY(1, 8);
    CTOS_LCDTClear2EOL();

    CTOS_RTCGet(&stRTC);

    while (1) {
        CTOS_KBDHit(&key);
        if (key == d_KBD_CANCEL) {
            exit(0);
        } else if (key != 0xFF) {
            //key hit
            CTOS_RTCGet(&stRTC);
        } else {
            //idle
            GetIdleSec(&stRTC, &usIdleTime_sec);
            sprintf(buf, "idle time(s): %04ds", usIdleTime_sec);
            CTOS_LCDTPrintXY(1, 8, buf);
            if (usIdleTime_sec >= d_TIME_GOTO_STANDBY) {
                CTOS_LCDTPrintXY(1, 2, "Last Status: Standby");

                ret = SetWakeupTime(d_TIME_GOTO_SLEEP);
                if (ret != d_OK) {
                    goto ERROR;
                }

                CTOS_BackLightSet(d_BKLIT_LCD, d_OFF);
                ret = CTOS_PowerModeEX(d_PWR_STANDBY_MODE, &usWake);
                if (ret == d_OK && usWake == d_MK_WAKE_RTC) {
                    CTOS_LCDTPrintXY(1, 2, "Last Status: Sleep  ");
                    ret = CTOS_PowerModeEX(d_PWR_SLEEP_MODE, &usWake);
                    if (ret != d_OK) {
                        goto ERROR;
                    }
                } else if (ret != d_OK) {
                    goto ERROR;
                }

                CTOS_BackLightSet(d_BKLIT_LCD, d_ON);
                CTOS_RTCGet(&stRTC);
            }
        }
    }

ERROR:
    CTOS_BackLightSet(d_BKLIT_LCD, d_ON);
    sprintf(buf, "Power mode ret=%04X", ret);
    CTOS_LCDTPrintXY(1, 4, buf);
    CTOS_KBDGet(&key);

    exit(0);
}

/** 
 **	A Template for developing new terminal application
 **/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>


#include "deftype.h"
#include "ByteStream.h"
#include "DbgMacro.h"
#include "MyCallBack.h"
#include "MyEmv.h"
#include "EMVBase.h"



CDebugInfo cDebug;
PAYMENT_DATA stPayData;

/** 
 ** The main entry of the terminal application 
 **/
int main(int argc, char *argv[]) {
    DEBUG_ENABLE(1, 1, 1, NULL);
    
//    DEBUG_BYTEBUF(DEBUGINFO_NORMAL,(BYTE*)"123456",7,"start:");
//    DEBUG_INFO(DEBUGINFO_NORMAL, "hello");
//    DEBUG_INFO(DEBUGINFO_NORMAL, "hello");
//    DEBUG_INFO(DEBUGINFO_NORMAL, "hello");
    
    BYTE byKey;
    USHORT usRet;
    BOOL bCardInserted;
    // TODO: Add your program here //
    CTOS_LCDTClearDisplay();

    CTOS_LCDTPrintXY(1, 1, (BYTE*) "Hello");
    MyEmv myemv;
    usRet = myemv.InitEmv();
    if (usRet != 0x0000) {
        return DEBUG_RETCODE("ret:", usRet);
    }
    myemv.StartEMV();

    do {
        CTOS_KBDHit(&byKey);
        if (byKey == d_KBD_CANCEL)
            return DEBUG_RETCODE("Main Cancel", 0);
        bCardInserted = myemv.IsCardInserted();

        if (bCardInserted) {
            usRet = myemv.SelectTxnApp();
            if (usRet != d_EMVAPLIB_OK) {
                return DEBUG_RETCODE("SelectTxnApp Failed, %04X", usRet);
            }
        }
    } while (!bCardInserted);
    USHORT usTVRLen = 1024;
    BYTE byTVRBuf[1024];

    USHORT usTSILen = 1024;
    BYTE byTSIBuf[1024];

    memset(byTVRBuf, 0x00, 1024);
    memset(byTSIBuf, 0x00, 1024);

    CByteStream cData;
    cData.Empty();

    EMV_DataGet(0x95, &usTVRLen, byTVRBuf);
    cData.Write(byTVRBuf, usTVRLen);
    DEBUG_STREAM(DEBUGINFO_NORMAL, &cData, "TVR ");

    cData.Empty();
    EMV_DataGet(0x9B, &usTSILen, byTSIBuf);
    cData.Write(byTSIBuf, usTSILen);
    DEBUG_STREAM(DEBUGINFO_NORMAL, &cData, "TSI ");

    CTOS_KBDGet(&byKey);
    myemv.StopEMV();
    CTOS_KBDGet(&byKey);
    exit(0);
}

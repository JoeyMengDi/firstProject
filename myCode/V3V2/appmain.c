/** 
 **	A Template for developing new terminal application
 **/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>

//#include "Inc/ByteStream.h"
//#include "Inc/DebugInfo.h"
//#include "DbgMacro.h"
//#include "ByteStream.h"



/** 
 ** The main entry of the terminal application 
 **/
int main(int argc, char *argv[]) {
    BYTE key;
    INT nCount = 0;
    BYTE byStr[17] = {0};
    // TODO: Add your program here //
    CTOS_LCDTPrintXY(1, 1, "My C++ Example");
    CTOS_LCDTPrintXY(1, 2, "1)add");
    CTOS_LCDTPrintXY(1, 3, "1)sub");
    CTOS_LCDTPrintXY(1, 4, "COUNT = 0");

    while (1) {
        //memset(byStr, 0, sizeof (byStr));
        CTOS_KBDGet(&key);
        if (key == d_KBD_CANCEL) {
            break;
        }
        switch (key) {
            case '1':
            {
                sprintf(byStr, "COUNT = %d\n", ++nCount);
                CTOS_LCDTPrintXY(1, 4, byStr);
                //DEBUG_INFO(DEBUGINFO_NORMAL, "wStatus: 0x%04X", wStatus);
            }
                break;
            case '2':
            {
                sprintf(byStr, "COUNT = %d\n", --nCount);
                CTOS_LCDTPrintXY(1, 4, byStr);
                //DEBUG_INFO(DEBUGINFO_NORMAL, "wStatus: 0x%04X", wStatus);
            }
                break;
            default:
                CTOS_Beep();
        }
    }

    exit(0);
}






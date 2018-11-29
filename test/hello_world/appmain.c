/** 
 **	A Template for developing new terminal application
 **/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>

/** 
 ** The main entry of the terminal application 
 **/
int main(int argc, char *argv[]) {
    BYTE key;

    // TODO: Add your program here //

    CTOS_LCDSelectMode(4);
    CTOS_LCDTTFSelect(d_FONT_DEFAULT_TTF, 0);
    CTOS_LCDFontSelectMode(d_FONT_TTF_MODE);
    CTOS_LCDTSelectFontSize(d_FONT_16x30);
    CTOS_LCDTClearDisplay();

    CTOS_LCDTPrintXY(1, 1, "Hello World");
    CTOS_KBDGet(&key);

    exit(0);
}

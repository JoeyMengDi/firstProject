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
    
    
    CTOS_LCDTClearDisplay();
    CTOS_LCDTPrintXY(2, 1, "\tHello\nhello");
    CTOS_KBDGet(&key);

    exit(0);
}

/** 
 **	A Template for developing new terminal application
 **/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>

#define d_LINE_DOT 12   //A line is 12 dots

/** 
 ** The main entry of the terminal application 
 **/
int main(int argc, char *argv[]) {
    BYTE key;
    USHORT res;

    // TODO: Add your program here //
    CTOS_LCDTClearDisplay();
    CTOS_LCDTSelectFontSize(0x101E);

    CTOS_PrinterPutString("CTOS_PrinterCode39Barcode");
    //Print the Code39 barcode //   
    //USHORT CTOS_PrinterCode39Barcode(IN USHORT x, IN USHORT y, IN BYTE *baCodeContent, IN BYTE bContentLen, IN BYTE bXExtend, IN BYTE bY8Extend, IN BOOL bShowChar);
    //X Horizontal position of paper.
    //Y Vertical position of paper. 
    //baCodeContent is Data
    //bContentLen The length of the baCodeContent. 
    //bXExtend The horizontal extend size. The range is 1~2.
    //bY8Extend The vertical extend size. The range is 1~3.
    //boShowChar Print the barcode content or not. 

    res = CTOS_PrinterCode39Barcode(2, 2, "*TEST8052*", 10, 2, 3, TRUE);
    if (res != d_OK) {
        CTOS_LCDTPrintXY(1, 1, " PrinterFailed");
        CTOS_KBDGet(&key);
        return 1;
    }
    //Note: the first and end character of context need to add "*" //                   
    res = CTOS_PrinterFline(d_LINE_DOT * 6); //a space 1 line      
    if (res != d_OK) {
        CTOS_LCDTPrintXY(1, 1, " PrinterFailed");
        CTOS_KBDGet(&key);
        return 1;
    }

    CTOS_LCDTPrintXY(1, 1, " PrinterOK");
    CTOS_KBDGet(&key);

    exit(0);
}

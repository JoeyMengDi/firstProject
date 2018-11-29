/** 
**	A Template for developing new terminal application
**/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>

#include <ctos_qrcode.h>

/** 
** The main entry of the terminal application 
**/
int main(int argc,char *argv[])
{
	BYTE key;
    USHORT res;
    char intext[] = "http://www.castech.com.tw";    
    char Version[10];
	CTOS_QRCODE_INFO qrcodeInfo;
    BYTE outputBuffer[384*20];
    CTOS_FONT_ATTRIB stFONT_ATTRIB;
    
    CTOS_LCDTClearDisplay();
    CTOS_LCDTSelectFontSize(0x101E);
    
    res = CTOS_PrinterBufferInit(outputBuffer, 8*20);
    if(res != d_OK)
    {
        CTOS_LCDTPrintXY(1, 8, "BufferInitFail");          
        CTOS_KBDGet(&key);
    	return 1;
    }
    
    //CTOS_QRcodePrinter(CTOS_QRCODE_INFO *pInfo, const char *pMessageText, USHORT usXstart);
    //typedef struct
    //  {
    //      DWORD InfoVersion;
    //      DWORD Version;
    //      DWORD Level;
    //      DWORD Size;
    //  }CTOS_QRCODE_INFO;;
    //Size range 1~10 
    //Version range QR_VERSION21X21 ~ QR_VERSION177X177 
    //Level range QR_LEVEL_L ~ QR_LEVEL_H  
    //usXstart is Horizontal position to start to print. Range from 0~383
    //pMessageText is Data
    
    qrcodeInfo.InfoVersion = QR_INFO_VERSION;
    qrcodeInfo.Size = 5;
    qrcodeInfo.Version = QR_VERSION21X21;
    qrcodeInfo.Level = QR_LEVEL_L;
    res = CTOS_QRCodePrinter(&qrcodeInfo, intext, 1);
    if(res != d_OK)
    {
        CTOS_LCDTPrintXY(1, 8, "PrinterFailed");          
        CTOS_KBDGet(&key);
        return 1;
    }
    
    res = CTOS_PrinterBufferSelectActiveAddress(outputBuffer);
    if(res != d_OK)
    {
        return 1;
    }
    
    //CTOS_QRcodeBufferPrinter(CTOS_QRCODE_INFO *pInfo, const char *pMessageText, USHORT usXPos, USHORT usYPos);
    //Put QRcode into Buffer
    res = CTOS_QRCodePrinterBuffer(&qrcodeInfo, intext, 250, 1);
    if(res != d_OK)
    {
        CTOS_LCDTPrintXY(1, 8, "PrinterFailed");          
        CTOS_KBDGet(&key);
        return 1;
    }
    
    // Set the font attribute
    stFONT_ATTRIB.FontSize = d_FONT_12x24;      // Font Size = 12x24
    stFONT_ATTRIB.X_Zoom = 1;                   // The width magnifies X_Zoom diameters
    stFONT_ATTRIB.Y_Zoom = 1;                   // The height magnifies Y_Zoom diameters
    stFONT_ATTRIB.X_Space = 0;                  // The width of the space between the font with next font
    stFONT_ATTRIB.Y_Space = 0;                  // The Height of the space between the font with next font
    
    //Put String into Buffer
    CTOS_PrinterBufferPutString((BYTE *)outputBuffer, 1, 100, "CASTLES Technology", &stFONT_ATTRIB);

    //Printer Buffer
    res = CTOS_PrinterBufferOutput(outputBuffer, 20);
    if(res != d_OK)
    {
        CTOS_LCDTPrintXY(1, 8, "PrinterFailed");          
        CTOS_KBDGet(&key);
        return 1;
    } 
    //USHORT CTOS_QRcodeDisplay(CTOS_QRCODE_INFO *pInfo, const char *pMessageText, USHORT X, USHORT Y);
    //X coordinate, the range is from 0 to d_LCD_CAVANS_X_SIZE-1. 
    //Y coordinate, the range is from 0 to d_LCD_CAVANS_Y_SIZE-1.
    //d_LCD_CAVANS_X_SIZE is 128
    //d_LCD_CAVANS_Y_SIZE is 256
    qrcodeInfo.InfoVersion = QR_INFO_VERSION;
    qrcodeInfo.Size = 2;
    qrcodeInfo.Version = QR_VERSION21X21;
    qrcodeInfo.Level = QR_LEVEL_L;
    res = CTOS_QRCodeDisplay(&qrcodeInfo, intext, 1, 1);
    if(res != d_OK)
    {
        CTOS_LCDTPrintXY(1, 8, "DisplayFailed");   
        CTOS_KBDGet(&key);
        return 1;
    }
   
    res = CTOS_LibQRCODEGetVersion(Version);
    if(res != d_OK)
    {
        CTOS_LCDTPrintXY(1, 1, "GetVersionFailed");   
        CTOS_KBDGet(&key);
        return 1;
    }
    CTOS_LCDTPrintXY(1, 8, Version); 
    
    
            
    CTOS_KBDGet(&key);
	
	exit(0);
}

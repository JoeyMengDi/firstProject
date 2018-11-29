#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>

#define d_BUFF_SIZE 2048
#define d_LCD_Width 16+1

int main(int argc,char *argv[])
{
    //Declare Local Variable //
    USHORT ret;
    USHORT len;
    BYTE key;	
    BYTE str[d_LCD_Width];
    BYTE buf[d_BUFF_SIZE];	
    
    CTOS_LCDTSelectFontSize(0x101E);
    
    CTOS_LCDTClearDisplay();
    CTOS_LCDTPrintXY(1, 1, "---RS232 ECHO---");
    
    // Open COM1 with baudrate 115200
    ret = CTOS_RS232Open(d_COM2, 115200, 'N', 8, 1); 
    if(ret != d_OK)
    {
        BYTE byStr[20]={0};
        sprintf(byStr,"ret=%X",ret);
        CTOS_LCDTPrintXY(1, 6, byStr);
        CTOS_LCDTPrintXY(1, 7, "Open Not OK");
        CTOS_LCDTPrintXY(1, 8, "Press any key");
        CTOS_KBDGet(&key);
        return 1;
    }
    
    CTOS_LCDTPrintXY(1, 2, "Baudrate: 115200");
    CTOS_RS232FlushRxBuffer(d_COM2);
    CTOS_LCDTPrintXY(1, 8, "Flush Rx Buffer");
    while(1)
    {
        CTOS_LCDTPrintXY(1, 3, "Start");
        
        // Check if data is available in COM1 port	//
        ret = CTOS_RS232RxReady(d_COM2, &len);
        if(len)
        {
           // Get Data from COM1 port
            CTOS_RS232RxData(d_COM2, buf, &len);			
            
            // Display
            sprintf(str, "Got Len = %d", len);			
            CTOS_LCDTPrintXY(1, 4, "                ");
            CTOS_LCDTPrintXY(1, 4, str);
            CTOS_LCDTPrintXY(1, 5, "                ");
            CTOS_LCDTPrintXY(1, 5, buf);
            
            // Check if COM1 is ready to send data  //
            while(CTOS_RS232TxReady(d_COM2) != d_OK);
            
            // Send data via COM2 port  //
            if(CTOS_RS232TxData(d_COM2, buf, len) != d_OK)
            {
                CTOS_LCDTPrintXY(1, 7, "TxData Not OK");
                CTOS_LCDTPrintXY(1, 8, "Press any key");
                CTOS_KBDGet(&key);
                CTOS_RS232Close ( d_COM2 );
                return 1;
            }
            
            sprintf(str, "Send Len = %d", len);			
            CTOS_LCDTPrintXY(1, 6, "                ");
            CTOS_LCDTPrintXY(1, 6, str);
            CTOS_LCDTPrintXY(1, 7, "                ");
            CTOS_LCDTPrintXY(1, 7, buf);
            CTOS_LCDTPrintXY(1, 8, "                ");
            CTOS_Delay(1000);
        }
        
        CTOS_KBDHit(&key);
        if(key == d_KBD_1)
        {
            while(CTOS_RS232TxReady(d_COM2) != d_OK);
            buf[0] = '1';
            buf[1] = '2';
            buf[2] = '3';
            buf[3] = '4';
            len = 4;
            CTOS_RS232TxData(d_COM2, buf, len);
        }
        else if(key == d_KBD_CANCEL)
        {
            CTOS_RS232Close(d_COM2);
            exit(0);
        }
    }
}

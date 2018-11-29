/** 
**	A Template for developing new terminal application
**/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>

/*==========================================*
 *            D E F I N E S                 *
 *==========================================*/
#define d_BUFF_SIZE (1024)				     // Buffer Size
#define Mode        d_M_MODE_AYNC_FAST 		// Mode type
#define HandShake   d_M_HANDSHAKE_V90_AUTO_FB  // HandShake type
#define CountryCode d_M_COUNTRY_TAIWAN		// CountryCode
#define TenSec      (10000)			         // 10 seconds
#define byteNUM     (4)				

/*===================================================================
 * FUNCTION NAME:   Open_Show
 * DESCRIPTION:   Open the modem device & show the return value
 * RETURN:        TRUE and FALSE
 * NOTES:         none
 *==================================================================*/
BOOL Open_Show(void)
{
    USHORT RET;
    BYTE str[30];
    memset(str, 0, sizeof(str));
    RET = CTOS_TCP_ModemOpen (Mode, HandShake, CountryCode);
    CTOS_LCDTPrintXY ( 1, 3, "Open:     " );
    sprintf(str, "ret:%x   ", RET);
    CTOS_LCDTPrintXY (1,4, str );
    if(RET != d_OK)
        return FALSE;
    return TRUE;
}

/*===================================================================
 * FUNCTION NAME:   status_show
 * DESCRIPTION:   Show the status & the return value of ModemStatus
 * RETURN:        The return value of ModemStatus
 * NOTES:         none
 *==================================================================*/
USHORT status_show(DWORD* Status, BYTE page)
{
    USHORT RET;
    BYTE str[30];
    page*=3;
    memset(str, 0, sizeof(str));
    RET = CTOS_TCP_ModemStatus(Status);
    sprintf(str, "Status:%x       ", *Status);
    CTOS_LCDTPrintXY (1,2+page, str );
    sprintf(str, "ret:%x          ", RET); 
    CTOS_LCDTPrintXY (1,3+page, str );
    return RET;
}

/*===================================================================
* FUNCTION NAME:    ContinueCheckStatus
* DESCRIPTION:   Check the status until out of the IO_PROCESSING situation
* RETURN:        The return value of ModemStatus
* NOTES:         none
*==================================================================*/
USHORT ContinueCheckStatus(USHORT statusRET, DWORD* Status, BYTE page)
{
    while(statusRET == d_TCP_IO_PROCESSING)
        {
            statusRET = status_show(Status, page);           
            if(statusRET == d_OK)
                return statusRET;
        }
    return statusRET;
}

/*===================================================================
* FUNCTION NAME:     Dialup_Show
* DESCRIPTION:    Dial up and show the return value of ModemDialup 
* RETURN:        TRUE and FALSE
* NOTES:         none
*==================================================================*/
BOOL Dialup_Show(BYTE* Phone, BYTE* ID, BYTE* PW, ULONG Timeout, DWORD* Status)
{
    USHORT DialRET;
    BYTE str[30],i;
    memset(str, 0, sizeof(str));
    CTOS_LCDTClearDisplay (  );
    CTOS_LCDTPrintXY ( 1, 1, "Dialup:     " );
    DialRET = CTOS_TCP_ModemDialup(Phone, ID, PW, Timeout);   
    sprintf(str, "ret:%x  ", DialRET);
    CTOS_LCDTPrintXY (1,3, str );
    for(i=0; i<30; i++)		
        {
            status_show(Status, 0);
            if(*Status == TCP_MODEM_STATE_ONLINE)
                return TRUE;
            CTOS_Delay(2000);
        }
    return FALSE;
}

/*===================================================================
 * FUNCTION NAME:      setBuffer
 * DESCRIPTION:    Set up the Buffer 
 * RETURN:        none
 * NOTES:         none
 *==================================================================*/
void setBuffer(BYTE* buf)
{
    BYTE RNG[10],i;
    for(i=0; i<128; i++)
    {
        CTOS_RNG (RNG);	          //Set 8 bytes random values//
        memcpy(buf + i*8, RNG, 8);
    }
    memcpy(buf, "\x03\xFE", 2);
}

/*===================================================================
* FUNCTION NAME:       Show_BinToHex
* DESCRIPTION:    Show the IP by Hex 
* RETURN:        none
* NOTES:         none
*==================================================================*/        
void Show_BinToHex(BYTE* localIP, BYTE NUM)
{
    BYTE i, str[30];
    for(i=0; i<NUM; i++)
    {
        sprintf(str, "%02x", localIP[i]);
        CTOS_LCDTPrintXY (7+i*2, 1, str );
    }
}

/** 
** The main entry of the terminal application 
**/
int main(int argc,char *argv[])
{
	BYTE key;
    BYTE baPhone [9] = "40508999";
    BYTE baID [6] = "yahoo";
    BYTE baPW [6] = "yahoo";
    ULONG ulTimeout = TenSec;
    BYTE ba_locaIP [] = { 0x00, 0x00, 0x00, 0x00 };
    BYTE bSocket;
    BYTE baIP[] = {0xDA, 0xD3, 0x23, 0xDB};
    USHORT usPort = 140;
    USHORT ret ,len;
    BYTE Str[30];
    DWORD dwStatus = 0;
    BYTE baBuffer_S[d_BUFF_SIZE];
    BYTE baBuffer_R[d_BUFF_SIZE];
    UINT Times;

    CTOS_LCDTSelectFontSize(0x101E);
START:
    memset(Str, 0, sizeof(Str));
    CTOS_TCP_ModemInit();
    CTOS_LCDTClearDisplay (  );
    CTOS_LCDTPrint ( "[AYNC_FAST]\n" );
    CTOS_LCDTPrint ( "[V90_AUTO_FB]\n" );
    CTOS_KBDGet ( &key );

    //Open the modem device//
    ret = Open_Show();                
    CTOS_KBDGet ( &key );
    if(ret != TRUE)
        goto END;

    // Set the local IP address of the connection//
    ret = CTOS_TCP_ModemSetIP(ba_locaIP);
    if(ret != d_OK)
    {
        CTOS_TCP_ModemClose ();
        goto END;
    }

    // Dial the number of ISP and get the IP address of this connection//
    ret = Dialup_Show(baPhone, baID, baPW, ulTimeout, &dwStatus);        
    CTOS_KBDGet ( &key );
    if(!ret)
    {
        goto END;
    }

    // Get the local IP address of the current connection//        
    CTOS_LCDTPrintXY ( 1, 2, "IPget:" );
    ret = CTOS_TCP_ModemGetIP(ba_locaIP);
    if(ret != d_OK)
    {
        CTOS_TCP_ModemClose ();
        goto END;
    }
    Show_BinToHex(ba_locaIP, byteNUM);
    CTOS_KBDGet ( &key );

    // Connect to the remote server//        
    CTOS_LCDTPrintXY ( 1, 1, "Connect:    " );
    ret = CTOS_TCP_ModemConnectEx (&bSocket, baIP, usPort);
    ContinueCheckStatus(ret, &dwStatus, 0);
    ret = status_show(&dwStatus, 0);
    if(ret != d_OK)
    {
        CTOS_TCP_ModemClose ();
        goto END;
    }
    setBuffer(baBuffer_S);          
    CTOS_KBDGet ( &key );

    // Send data out//
    memset(baBuffer_R, 0x00, sizeof(baBuffer_R));
    CTOS_LCDTPrintXY ( 1, 1, "Transmitting...    " );
    ret = CTOS_TCP_ModemTx(bSocket, baBuffer_S, d_BUFF_SIZE);
    ContinueCheckStatus(ret, &dwStatus, 0);
    status_show(&dwStatus, 0);

    // Receive data//
    len = d_BUFF_SIZE;
    CTOS_LCDTPrintXY ( 1, 1, "Receiving...    " );
    ret = CTOS_TCP_ModemRx(bSocket, baBuffer_R, &len);
    ContinueCheckStatus(ret, &dwStatus, 1);
    status_show(&dwStatus, 0);
    sprintf(Str, "len = %d     ", len); 
    CTOS_LCDTPrintXY (1,7, Str );
    CTOS_KBDGet ( &key );

    // Disconnect to the remote//
    CTOS_LCDTClearDisplay (  );
    CTOS_LCDTPrintXY ( 1, 1, "Disconnect    " );
    ret = CTOS_TCP_ModemDisconnect (bSocket);
    ContinueCheckStatus(ret, &dwStatus, 0);
    status_show(&dwStatus, 0);
    CTOS_KBDGet ( &key );

    // Hook on this connection//
    CTOS_LCDTPrintXY ( 1, 1, "OnHook        " );
    ret = CTOS_TCP_ModemOnHook();
    ContinueCheckStatus(ret, &dwStatus, 0);
    status_show(&dwStatus, 0);
    CTOS_KBDGet ( &key );

    // Close the modem device//
    CTOS_TCP_ModemClose (); 
END:    
    CTOS_LCDTClearDisplay (  );
    CTOS_LCDTPrint ( "END\n" );
    CTOS_LCDTPrint ( "CANCEL->Close\n" );
    CTOS_LCDTPrint ( "CLEAR->Restart\n" );        
    while(1)
    {
        CTOS_KBDGet ( &key );
        if( key == d_KBD_CANCEL )
            break;
        else if( key == d_KBD_CLEAR )
            goto START;
    }
	
	exit(0);
}

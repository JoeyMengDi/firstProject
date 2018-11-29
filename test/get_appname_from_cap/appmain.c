/** 
**	A Template for developing new terminal application
**/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>
#include "getappname.h"

const char d_MCI_PATH[] = "App.mci";


/** 
** The main entry of the terminal application 
**/
int main(int argc,char *argv[])
{
	BYTE key;
    char appname[128];
    char str[128];
    USHORT usRet;    
	// TODO: Add your program here //
    CTOS_LCDTSelectFontSize(0x101E);
	CTOS_LCDTClearDisplay();
    
	
    //if(LIB_GetAppNameFromCAP((char*) d_MCI_PATH, appname) != d_OK)
    usRet = LIB_GetAppNameFromCAP((char*) d_MCI_PATH, appname);
	if(usRet != d_OK)
	{
        return 0;
    }
    
    sprintf(str, "Cap Name:%s\n", appname);
    
    CTOS_LCDTPrintXY(1, 1, str);
            
    CTOS_KBDGet(&key);
	
	exit(0);
}

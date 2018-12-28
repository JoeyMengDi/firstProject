/** 
**	A Template for developing new terminal shared application
**/

#include <string.h>
#include <stdio.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>
#include "dynamiclib.h"

int DynamicLib_ShowHello(void)
{
		
    BYTE key;
    
    CTOS_LCDTPrintXY(1, 1, "DynamicLib_ShowHello");
    
    CTOS_KBDGet(&key);
    
    return 0;
}

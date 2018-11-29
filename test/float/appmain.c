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
int main(int argc,char *argv[])
{
	BYTE key;
    float a;
    float b;
    float c;
    BYTE str[17];
        
	// TODO: Add your program here //
    CTOS_LCDTSelectFontSize(0x101E);
	CTOS_LCDTClearDisplay();            
    CTOS_LCDTPrintXY(1, 1, "Float");
    
    //-------------------------------------------------
    a = 10.2;
    b = 2.3;
    
    sprintf(str, "a = %f\n", a);
    CTOS_LCDTPrintXY(1, 2, str);
    sprintf(str, "b = %f\n", b);
    CTOS_LCDTPrintXY(1, 3, str);
    
    c = a + b;
    sprintf(str, "a + b = %f\n", c);
    CTOS_LCDTPrintXY(1, 4, str);
    
    c = a - b;
    sprintf(str, "a - b = %f\n", c);
    CTOS_LCDTPrintXY(1, 5, str);
    
    c = a * b;
    sprintf(str, "a * b = %f\n", c);
    CTOS_LCDTPrintXY(1, 6, str);
    
    c = a / b;
    sprintf(str, "a / b = %f\n", c);
    CTOS_LCDTPrintXY(1, 7, str);
    
    CTOS_KBDGet(&key);
    
    CTOS_LCDTClearDisplay();            
    CTOS_LCDTPrintXY(1, 1, "Float");
    
    if(a > b)
    {
        CTOS_LCDTPrintXY(1, 2, "a > b\n");        
    }
    
    if(b < a)
    {
        CTOS_LCDTPrintXY(1, 3, "b < a\n");        
    }
    
    c = 10.2;
    sprintf(str, "a = %f\n", a);
    CTOS_LCDTPrintXY(1, 4, str);
    sprintf(str, "c = %f\n", c);
    CTOS_LCDTPrintXY(1, 5, str);
    
    if(a == c)
    {
        CTOS_LCDTPrintXY(1, 6, "a == c\n");   
    }
    
    CTOS_KBDGet(&key);
    
    //---------------------------------------------------
    CTOS_LCDTClearDisplay();            
    CTOS_LCDTPrintXY(1, 1, "Float");
    
    a = -10.2;
    b = -2.3;
    
    sprintf(str, "a = %f\n", a);
    CTOS_LCDTPrintXY(1, 2, str);
    sprintf(str, "b = %f\n", b);
    CTOS_LCDTPrintXY(1, 3, str);
    
    c = a + b;
    sprintf(str, "a + b = %f\n", c);
    CTOS_LCDTPrintXY(1, 4, str);
    
    c = a - b;
    sprintf(str, "a - b = %f\n", c);
    CTOS_LCDTPrintXY(1, 5, str);
    
    c = a * b;
    sprintf(str, "a * b = %f\n", c);
    CTOS_LCDTPrintXY(1, 6, str);
    
    c = a / b;
    sprintf(str, "a / b = %f\n", c);
    CTOS_LCDTPrintXY(1, 7, str);
    
    CTOS_KBDGet(&key);
    
    CTOS_LCDTClearDisplay();            
    CTOS_LCDTPrintXY(1, 1, "Float");
    
    if(a < b)
    {
        CTOS_LCDTPrintXY(1, 2, "a < b\n");        
    }
    
    if(b > a)
    {
        CTOS_LCDTPrintXY(1, 3, "b > a\n");        
    }
    
    c = -10.2;
    sprintf(str, "a = %f\n", a);
    CTOS_LCDTPrintXY(1, 4, str);
    sprintf(str, "c = %f\n", c);
    CTOS_LCDTPrintXY(1, 5, str);
    
    if(a == c)
    {
        CTOS_LCDTPrintXY(1, 6, "a == c\n");   
    }
    
    CTOS_KBDGet(&key);
	
    exit(0);
}

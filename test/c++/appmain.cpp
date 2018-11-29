/** 
**	A Template for developing new terminal application
**/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>
#include <iostream>

class CShow
{        
private:
    int count;            

protected:
    int version;
    int count2;
    
    void addc2(void)
    {
        count2++;
    }
    
public:
    
    CShow()
    {
        count = 0;
        version = 1;
    }
    
    void add(void)
    {
        count++;
    }

    void reset(void)
    {
        count = 0;
    }

    void show(BYTE x ,BYTE y)
    {
        BYTE str[17];
        
        sprintf((char*)str, "count = %d\n", count);
        CTOS_LCDTPrintXY(x, y, str);
    }
};

class CShow2 : CShow
{    
public:
    
    CShow2()
    {
        version = 2;
        count2 = 0;        
    }
    
    void add(void)
    {
        addc2();
    }
    
    void show(BYTE x, BYTE y)
    {
        BYTE str[17];
        sprintf((char*)str, "count2 = %d\n", count2);
        CTOS_LCDTPrintXY(x, y, str);
    }
};

/** 
** The main entry of the terminal application 
**/
int main(void)
{
    BYTE key;    
    CShow show;
    CShow2 show2;
    
    CTOS_LCDTSelectFontSize(0x101E);
    CTOS_LCDTPrintXY(1, 1, (BYTE *)"C++ Example");
                	    
	while(1)
    {
        show.show(1, 2);        
        show2.show(1, 3);        
        CTOS_LCDTPrintXY(1, 4,(BYTE *)"1) Add");
        CTOS_LCDTPrintXY(1, 5,(BYTE *)"2) Reset");        
        
        CTOS_KBDGet(&key);
        
        if(key == d_KBD_CANCEL)
        {
            break;
        }
        
        switch(key)
        {
            case '1': 
                show.add();
                show2.add();                
                break;
            case '2':
                show.reset();  
                
                break;            
            default:
                CTOS_Beep();
        }
    
    }
	
	exit(0);
}

/** 
**	A Linux Dynamic Load Library sample code
**/
#include <stdlib.h>		
#include <stdio.h>
#include <string.h>	
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/wait.h>
#include <ctosapi.h>
#include <ctosfd.h>
#include <dlfcn.h> //Note: Must add for dlopen/dlsym/dlerr/dlclose functions.

char gStr[256];
char gLIBPathName[128];
BYTE gBuf[512];

/* Functions in shared Library */
extern int TestAdd(int v1 , int v2 , int v3);
extern int TestSub(int v1 , int v2 , int v3);
extern int TestMultiple(int v1 , int v2);
extern int TestDiv(int v1 , int v2);

int (*TestFuncA)(int v1,int v2 , int v3);
int (*TestFuncB)(int v1,int v2 , int v3);
int (*TestFuncC)(int v1,int v2);
int (*TestFuncD)(int v1,int v2);

//=========================================================
void clearLCDAndShowMSG(char *theStr , BYTE IsWaitKey)
{
	BYTE key;
	CTOS_LCDTClearDisplay();
	CTOS_LCDTPrintXY(1,4,theStr);
	if (IsWaitKey==1)	{	
		CTOS_LCDTPrintXY(1,6,"Press any key...");
		CTOS_KBDGet(&key);
	}
	else	{
		CTOS_Delay(1500);	
	}
}

/*========================================================= 
 *     The main entry of the terminal application 
 *========================================================= */
int main(int argc,char *argv[])
{	
	int iret;
	void *handle ;	
			
	CTOS_LCDTSelectFontSize(0x101E);
	CTOS_LCDTClearDisplay();

	memset(gLIBPathName ,0 ,sizeof(gLIBPathName));
	
	/* The default folder of user shared library is /usr/local/lib/ */
	strcpy(gLIBPathName , "/usr/local/lib/libV3dll.so"); //

	clearLCDAndShowMSG("DLL Sample",0);	
	
	handle = dlopen(gLIBPathName , RTLD_NOW );
	if (!handle) // Fail
	{
		clearLCDAndShowMSG("Err:handle",0);
		return d_ERR_SYSTEM;	
	}
	else
	{
		clearLCDAndShowMSG("OK:handle",0);
	}		

	TestFuncA = dlsym(handle , "TestAdd");  //Function name string
	if (dlerror() != NULL)
	{
		clearLCDAndShowMSG("Err:TestFuncA",0);
		return d_ERR_SYSTEM + 1;	
	}
	else
	{
		clearLCDAndShowMSG("OK:TestFuncA",0);
	}	
	
	TestFuncB = dlsym(handle , "TestSub");  //Function name string
	if (dlerror() != NULL)
	{
		clearLCDAndShowMSG("Err:TestFuncB",0);
		return d_ERR_SYSTEM + 2;	
	}
	else
	{
		clearLCDAndShowMSG("OK:TestFuncB",0);
	}	
	
	TestFuncC = dlsym(handle , "TestMultiple"); //Function name string
	if (dlerror() != NULL)
	{
		clearLCDAndShowMSG("Err:TestFuncC",0);
		return d_ERR_SYSTEM + 3;	
	}
	else
	{
		clearLCDAndShowMSG("OK:TestFuncC",0);
	}	
	
	TestFuncD = dlsym(handle , "TestDiv"); //Function name string
	if (dlerror() != NULL)
	{
		clearLCDAndShowMSG("Err:TestFuncD",0);
		return d_ERR_SYSTEM + 4;	
	}
	else
	{
		clearLCDAndShowMSG("OK:TestFuncD",0);
	}	
		
	iret = TestFuncA(1000 , 100 , 10); // 1000 + 100 + 10 = 1110
	memset(gBuf ,0 ,sizeof(gBuf));
	sprintf(gBuf ,"Add: %d" ,iret );
	clearLCDAndShowMSG(gBuf , 0);		
	
	iret = TestFuncB(1000 , 100 , 1); // 1000 - 100 -10 = 899
	memset(gBuf ,0 ,sizeof(gBuf));
	sprintf(gBuf ,"Sub: %d" ,iret );
	clearLCDAndShowMSG(gBuf , 0);
	
	iret = TestFuncC(200 , 10); // 200 * 10 = 2000
	memset(gBuf ,0 ,sizeof(gBuf));
	sprintf(gBuf ,"Mul: %d" ,iret );
	clearLCDAndShowMSG(gBuf , 0);
	
	iret = TestFuncD(200 , 10); // 200 / 10 = 20
	memset(gBuf ,0 ,sizeof(gBuf));
	sprintf(gBuf ,"Div: %d" ,iret );
	clearLCDAndShowMSG(gBuf , 0);
	
	dlclose(handle);		

	
	return 0;
}



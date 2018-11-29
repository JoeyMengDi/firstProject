#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctosapi.h>
#include "getappname.h"

unsigned short LIB_GetAppNameFromCAP(char* MCI_FileName, char* AppNameStr)
{
    char strCAPName[128], appName[32], temp[32]; //buf 5M
    char *linefeed, type;
    unsigned long ulReadLen, ulfSeek;
	
    memset(strCAPName, 0x00, sizeof (strCAPName));
    memset(appName, 0x00, sizeof (appName));
    memset(temp, 0x00, sizeof (temp));

    FILE *fp = fopen(MCI_FileName, "r+");

    if (fp != NULL)
    {
        // get CAP name;
        fgets(strCAPName, 256, fp);
        fclose(fp);
    }
    else
    {
        perror(strCAPName);
        return MCI_NO_EXIST;
    }

	//------------------------------------------------------------------------------------
    // parser CAP file

    // check line feed
    linefeed = strpbrk(strCAPName, "\n");
    if (linefeed != NULL)
    {
        memset(&strCAPName[strlen(strCAPName) - 2], 0x00, 2);
    }

    // open CAP file
    FILE *fp_cap = fopen(strCAPName, "r+");

    if (fp_cap != NULL)
    {
        // get header1 name 
        fseek(fp_cap, 16, SEEK_SET);
        ulReadLen = 20;
        fread(appName, 1, ulReadLen, fp_cap);

        //get ELen
        fseek(fp_cap, 128, SEEK_SET);
        ulReadLen = 4;
        fread(temp, 1, ulReadLen, fp_cap);
        ulfSeek = (temp[0] << 24) | (temp[1] << 16) | (temp[2] << 8) | temp[3];
	
        //keylen
		ulfSeek = ulfSeek + 128 + 4;	
        fseek(fp_cap, ulfSeek, SEEK_SET);
        ulReadLen = 2;
        memset(temp, 0x00, sizeof (temp));
        fread(temp, 1, ulReadLen, fp_cap);	
		ulfSeek = ulfSeek + 2;
		ulfSeek = ulfSeek + ((unsigned char)temp[0] << 8 | (unsigned char)temp[1]);
		
        //slen      
        fseek(fp_cap, ulfSeek, SEEK_SET);
        ulReadLen = 2;
        memset(temp, 0x00, sizeof (temp));
        fread(temp, 1, ulReadLen, fp_cap);
		ulfSeek = ulfSeek + 2;
		ulfSeek = ulfSeek + ((unsigned char)temp[0] << 8 | (unsigned char) temp[1]);
		
        //get header2 name 
        ulfSeek = ulfSeek + 4 ;
        fseek(fp_cap, ulfSeek, SEEK_SET);
        ulReadLen = 20;
        memset(appName, 0x00, sizeof (appName));
        fread(appName, 1, ulReadLen, fp_cap);

        strcpy(AppNameStr, appName);


        //check the cap is appcation.
        ulfSeek += 22;
        fseek(fp_cap, ulfSeek, SEEK_SET);
		 
        ulReadLen = 1;
        fread(&type, 1, ulReadLen, fp_cap);
        if (type != 0x10)
            return NOT_APP_CAP;

        fclose(fp_cap);
        return d_OK;
    }
    else
    {
        printf("File no exist!\n");
        perror(strCAPName);
        printf("ERR:%s", strCAPName);
    }
    
    return CAP_NO_EXIST;
}

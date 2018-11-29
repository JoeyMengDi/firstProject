/** 
**	A Template for developing new terminal application
**/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/** These two files are necessary for calling CTOS API **/
#include <ctosapi.h>
#include"iso8583c.h"
#include"wub_lib.h"

static USHORT usPackDataAddr[64];
static BYTE baPackData[1024];  //2byte Len + 1byte mode + len byte Data
static BYTE baTxBuff[1024];

const BITMAP_CH BitMap_User[129] = 
{
/* FIELD  0 */ {  2, 0,t_n, ByRight, '0'},
/* FIELD  1 */ {  8, 0,t_b, ByRight, '0'},
///* FIELD  2 */ { 19, 2,t_n, ByLeft, 'F'}, //
/* FIELD  2 */ { 19, 2,t_n, ByRight, '0'},
/* FIELD  3 */ {  6, 0,t_n, ByRight, '0'}, //
/* FIELD  4 */ { 12, 0,t_n, ByRight, '0'}, //
/* FIELD  5 */ { 19, 2,t_n, ByLeft, 'F'}, //
/* FIELD  6 */ { 12, 0,t_n, ByRight, '0'},
/* FIELD  7 */ { 10, 0,t_n, ByRight, '0'},
/* FIELD  8 */ {  8, 0,t_n, ByRight, '0'}, //
/* FIELD  9 */ {  8, 0,t_n, ByRight, '0'},
/* FIELD 10 */ {  8, 0,t_n, ByRight, '0'},
/* FIELD 11 */ {  6, 0,t_n, ByRight, '0'}, //
/* FIELD 12 */ {  6, 0,t_n, ByRight, '0'}, //
/* FIELD 13 */ {  4, 0,t_n, ByRight, '0'}, //
/* FIELD 14 */ {  4, 0,t_n, ByRight, '0'},
/* FIELD 15 */ {  4, 0,t_n, ByRight, '0'},
/* FIELD 16 */ {  4, 0,t_n, ByRight, '0'},
/* FIELD 17 */ {  4, 0,t_n, ByRight, '0'},
/* FIELD 18 */ {  4, 0,t_n, ByRight, '0'},
/* FIELD 19 */ {  3, 0,t_n, ByRight, '0'},
/* FIELD 20 */ {  3, 0,t_n, ByRight, '0'},
/* FIELD 21 */ {  3, 0,t_n, ByRight, '0'},
/* FIELD 22 */ {  3, 0,t_n, ByRight, '0'},
/* FIELD 23 */ {  4, 0,t_n, ByRight, '0'},
/* FIELD 24 */ {  3, 0,t_n, ByRight, '0'},
/* FIELD 25 */ {  2, 0,t_n, ByRight, '0'},
/* FIELD 26 */ {  2, 0,t_n, ByRight, '0'},
/* FIELD 27 */ {  1, 0,t_n, ByRight, '0'},
/* FIELD 28 */ {  9, 0,t_xn, ByRight, '0'},
/* FIELD 29 */ {  9, 0,t_xn, ByRight, '0'},
/* FIELD 30 */ {  9, 0,t_xn, ByRight, '0'},
/* FIELD 31 */ {  9, 0,t_xn, ByRight, '0'},
/* FIELD 32 */ { 11, 2,t_n, ByRight, '0'},
/* FIELD 33 */ { 11, 2,t_n, ByRight, '0'},
/* FIELD 34 */ { 28, 2,t_ns, ByRight, '0'},
/* FIELD 35 */ { 37, 2,t_z, ByRight, 'F'},
/* FIELD 36 */ {104, 3,t_z, ByRight, '0'},
/* FIELD 37 */ { 12, 0,t_an, ByRight, 'F'},
/* FIELD 38 */ {  6, 0,t_an, ByRight, '0'},
/* FIELD 39 */ {  2, 0,t_an, ByRight, '0'}, //
/* FIELD 40 */ {  3, 0,t_an, ByRight, '0'},
/* FIELD 41 */ { 8, 0,t_ans, ByRight, '0'}, //
/* FIELD 42 */ { 15, 0,t_ans, ByRight, '0'}, //
/* FIELD 43 */ { 40, 0,t_ans, ByRight, '0'}, //
/* FIELD 44 */ { 20, 3, t_ans, ByRight, '0'},
/* FIELD 45 */ { 76, 2,t_ans, ByRight, '0'},
/* FIELD 46 */ {999, 3,t_ans, ByRight, '0'},
/* FIELD 47 */ { 37, 2,t_z, ByRight, 'F'},
/* FIELD 48 */ {999, 3,t_ans, ByLeft, '0'}, //
/* FIELD 49 */ {  3, 0,t_an, ByRight, '0'},
/* FIELD 50 */ { 99, 2,t_an, ByRight, '0'}, //
/* FIELD 51 */ {  3, 0,t_a, ByRight, '0'},
/* FIELD 52 */ { 64, 0,t_b, ByRight, '0'},  
/* FIELD 53 */ { 64, 0,t_b, ByRight, '0'},
/* FIELD 54 */ {20, 3,t_an, ByRight, '0'},
/* FIELD 55 */ {999, 3,t_ans, ByRight, '0'},
/* FIELD 56 */ {999, 3,t_ans, ByRight, '0'}, //
/* FIELD 57 */ {12, 0,t_n, ByRight, '0'},
/* FIELD 58 */ {128, 0,t_b, ByRight, '0'},
/* FIELD 59 */ {999, 3,t_ans, ByRight, '0'},
/* FIELD 60 */ {999, 3,t_ans, ByRight, '0'}, //
/* FIELD 61 */ {999, 3,t_ans, ByRight, '0'},
/* FIELD 62 */ {999, 3,t_ans, ByRight, '0'}, //
/* FIELD 63 */ {999, 3,t_ans, ByRight, '0'},
/* FIELD 64 */ { 64, 0,t_b, ByRight, '0'},
/* FIELD 65 */ {  8, 0,t_b, ByRight, '0'},
/* FIELD 66 */ {  1, 0,t_n, ByRight, '0'},
/* FIELD 67 */ {  2, 0,t_n, ByRight, '0'},
/* FIELD 68 */ {  3, 0,t_n, ByRight, '0'},
/* FIELD 69 */ {  3, 0,t_n, ByRight, '0'},
/* FIELD 70 */ {  3, 0,t_n, ByRight, '0'},
/* FIELD 71 */ {  4, 0,t_n, ByRight, '0'},
/* FIELD 72 */ {  4, 0,t_n, ByRight, '0'},
/* FIELD 73 */ {  6, 0,t_n, ByRight, '0'},
/* FIELD 74 */ { 10, 0,t_n, ByRight, '0'},
/* FIELD 75 */ { 10, 0,t_n, ByRight, '0'},
/* FIELD 76 */ { 10, 0,t_n, ByRight, '0'},
/* FIELD 77 */ { 10, 0,t_n, ByRight, '0'},
/* FIELD 78 */ { 10, 0,t_n, ByRight, '0'},
/* FIELD 79 */ { 10, 0,t_n, ByRight, '0'},
/* FIELD 80 */ { 10, 0,t_n, ByRight, '0'},
/* FIELD 81 */ { 10, 0,t_n, ByRight, '0'},
/* FIELD 82 */ { 12, 0,t_n, ByRight, '0'},
/* FIELD 83 */ { 12, 0,t_n, ByRight, '0'},
/* FIELD 84 */ { 12, 0,t_n, ByRight, '0'},
/* FIELD 85 */ { 12, 0,t_n, ByRight, '0'},
/* FIELD 86 */ { 16, 0,t_n, ByRight, '0'},
/* FIELD 87 */ { 16, 0,t_n, ByRight, '0'},
/* FIELD 88 */ { 16, 0,t_n, ByRight, '0'},
/* FIELD 89 */ { 16, 0,t_n, ByRight, '0'},
/* FIELD 90 */ { 42, 0,t_n, ByRight, '0'},
/* FIELD 91 */ {  1, 0,t_an, ByRight, '0'},
/* FIELD 92 */ {  2, 0,t_an, ByRight, '0'},
/* FIELD 93 */ {  5, 0,t_an, ByRight, '0'},
/* FIELD 94 */ {  7, 0,t_an, ByRight, '0'},
/* FIELD 95 */ { 42, 0,t_an, ByRight, '0'},
/* FIELD 96 */ {  8, 0,t_b, ByRight, '0'},
/* FIELD 97 */ { 17, 0,t_xn, ByRight, '0'},
/* FIELD 98 */ { 25, 0,t_ans, ByRight, '0'},
/* FIELD 99 */ { 11, 2,t_n, ByRight, '0'},
/* FIELD 100*/ { 11, 2,t_n, ByRight, '0'},
/* FIELD 101*/ { 17, 2,t_ans, ByRight, '0'},
/* FIELD 102*/ { 28, 2,t_ans, ByRight, '0'},
/* FIELD 103*/ { 28, 2,t_ans, ByRight, '0'},
/* FIELD 104*/ {100, 3,t_ans, ByRight, '0'},
/* FIELD 105*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 106*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 107*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 108*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 109*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 110*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 111*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 112*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 113*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 114*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 115*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 116*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 117*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 118*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 119*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 120*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 121*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 122*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 123*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 124*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 125*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 126*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 127*/ {999, 3,t_ans, ByRight, '0'},
/* FIELD 128*/ { 64, 0,t_b, ByRight, '0'}
};





BYTE PackTransMsg(void)
{
    int i;
        USHORT len, rtn = d_IS_OK;
        BYTE buff[1024];
        BYTE ErrBit[1];
        
        printf("\nPackTransMsg\n");
	// TODO: Add your program here //
	CTOS_LCDTClearDisplay();
            
        CTOS_LCDTPrintXY(1, 1, "Hello");
        
        ISO8583_Initial();
        ISO8583_BitMap_ChangeType(BM_USER, (BITMAP_CH *)&BitMap_User);
        
        len = sizeof(buff);
    
        if (ISO8583_BitMap_New(200) != d_IS_OK) return FALSE;

        ISO8583_Data_Set(3, 6, "000000");
        ISO8583_Data_SetULONG(4, 200);
        ISO8583_Data_SetULONG(11, 66);
        ISO8583_Data_Set(22, 3, "021");
        ISO8583_Data_Set(24, 3, "002");
        ISO8583_Data_Set(25, 2, "00");
        ISO8583_Data_Set(35, 37, "3fc6a36127a40e7e072012990000000000000f");          
        ISO8583_Data_Set(41, 8, "\x31\x30\x30\x33\x30\x30\x32\x33");                        //ISO8583_Data_Set(41, 8, "10030023");                  
        ISO8583_Data_Set(42, 15, "\x31\x31\x31\x31\x30\x30\x33\x30\x30\x30\x30\x30\x20\x20\x20");//ISO8583_Data_Set(42, 15, "111100300000   ");    
        ISO8583_Data_Set(48, 1, "\x06");
        ISO8583_Data_Set(52, 8, "\x4a\xde\x0f\x70\xe9\x0b\x64\xe0");
        ISO8583_Data_Set(58, 16, "\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00");
        ISO8583_Data_Set(64, 8, "\xc0\x0b\x07\x70\x00\x00\x00\x00");    

        memset(buff, 0, sizeof(buff));

        rtn = ISO8583_BitMap_Pack(ErrBit, &len, buff);  

        if(rtn != d_IS_OK)
        {
            printf("error\n");
            return ;
        }
        for(i=0;i<len;i++)
            printf("%02x ",buff[i]);
}


BYTE UnpackTransMsg(USHORT inlen, BYTE *indata, BYTE *ErrBit)
{
    USHORT recMsgType, ilen, ret = d_IS_OK;
    BYTE blen, baBitMap[16], rtn = 0x00;
    BYTE rsp_mac[9];
    BYTE buff[256];
    ULONG amount, stn;
    int count, i, j;
    
    printf("\nUnpackTransMsg\n");
    (*ErrBit) = 0;
    ret = ISO8583_BitMap_unPack(inlen, indata);
    if (ret != d_IS_OK)
        return 0x01;
        
            
    ret = ISO8583_Get_BitMapData(&recMsgType, &blen, baBitMap);
    if (ret != d_IS_OK)
        return 0x01;
    
    if (blen == 8)
        count = 64;
    else
        count = 128;
    
    for (i=1; i<=count; i++)
    {
        ilen = 0;
        if (!ISO8583_Check_BitSet(i)) continue;

        
        switch(i)
        {
            case 2:
                memset(buff, 0, sizeof(buff));
                ret = ISO8583_Data_Get(i, &ilen, buff);
                
                for(j=0;j<ilen;j++)
                        printf("%02x ",buff[j]);
                
                break;
            case 3:
                memset(buff, 0, sizeof(buff));
                printf("\n\n");
                ret = ISO8583_Data_Get(i, &ilen, buff);
                for(j=0;j<ilen;j++)
                        printf("%02x ",buff[j]);
               
                   
                break;
            case 4:
                printf("\n\n");
                ISO8583_Data_GetULONG(i, &amount);
                
                printf("%ld ",amount);
                
                break;
            case 11:
                printf("\n\n");
                ISO8583_Data_GetULONG(i, &stn);
                printf("%ld ",stn);
                break;
            case 12: //time hhmmss
                printf("\n\n");
                ret = ISO8583_Data_Get(i, &ilen, buff);
                for(j=0;j<ilen;j++)
                        printf("%02x ",buff[j]);
                break;
            case 13: //date MMDD
                printf("\n\n");
                ret = ISO8583_Data_Get(i, &ilen, buff);
                for(j=0;j<ilen;j++)
                        printf("%02x ",buff[j]);
                break;
            
            case 24:
                printf("\n\n");
                ret = ISO8583_Data_Get(i, &ilen, buff);
                for(j=0;j<ilen;j++)
                        printf("%02x ",buff[j]);
                break;
            case 37: 
                printf("\n\n");
                ret = ISO8583_Data_Get(i, &ilen, buff);
                for(j=0;j<ilen;j++)
                        printf("%02x ",buff[j]);
                break;
            case 38:
                printf("\n\n");
                ret = ISO8583_Data_Get(i, &ilen, buff);
                for(j=0;j<ilen;j++)
                        printf("%02x ",buff[j]);
                break;
            case 39:
                printf("\n\n");
                ret = ISO8583_Data_Get(i, &ilen, buff);
                for(j=0;j<ilen;j++)
                        printf("%02x ",buff[j]);
                break;
            case 41:
                printf("\n\n");
                ret = ISO8583_Data_Get(i, &ilen, buff);
                for(j=0;j<ilen;j++)
                        printf("%02x ",buff[j]);
               
                break;
            case 42:
                printf("\n\n");
                ret = ISO8583_Data_Get(i, &ilen, buff);
                for(j=0;j<ilen;j++)
                        printf("%02x ",buff[j]);
                break;
           
            case 63:
                printf("\n\n");
                ret = ISO8583_Data_Get(i, &ilen, buff);
                for(j=0;j<ilen;j++)
                        printf("%02x ",buff[j]);
                
                break;
            case 64:
                printf("\n\n");
                memset(buff, 0, sizeof(buff));
                ret = ISO8583_Data_Get(i, &ilen, buff);
                for(j=0;j<ilen;j++)
                        printf("%02x ",buff[j]);
               
                break;
        }
    }
    
    return rtn;
}

/** 
** The main entry of the terminal application 
**/
int main(int argc,char *argv[])
{
        BYTE ErrBit[1];

        //================================================
        PackTransMsg();
    
        //================================================

        BYTE baRxBuff[] = {
                   "\x02\x10\x70\x38\x01\x00\x0e\xc0\x00\x03"
                   "\x19\x00\x30\x30\x30\x30\x30\x30\x30"
                   "\x30\x30\x00\x30\x00\x00\x00\x00\x00\x02"
                   "\x00\x00\x00\x66\x14\x02\x59\x03\x07\x00"
                   "\x02\x20\x20\x20\x20\x20\x20\x30\x30\x30"
                   "\x30\x36\x36\x31\x34\x30\x32\x35\x39\x30"
                   "\x30\x31\x30\x30\x33\x30\x30\x32\x33\x31"
                   "\x31\x31\x31\x30\x30\x33\x30\x30\x30\x30"
                   "\x20\x20\x20\x20\x00\x20\x43\x41\x52\x44"
                   "\x20\x48\x4f\x4c\x44\x45\x52\x20\x54\x45"
                   "\x53\x54\x20\x20\x20\x20\x52\xf9\x00\x09"
                   "\x00\x00\x00\x00"};
        
        UnpackTransMsg(113, baRxBuff, ErrBit);
    
}

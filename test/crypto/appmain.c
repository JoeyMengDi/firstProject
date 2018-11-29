/*========================================*                                                                 
 *             I N C L U D E S            *                                                                
 *========================================*/                                                               
#include <string.h>                                                                                        
#include <stdio.h>                                                                                         
#include <ctosapi.h>                                                                                       
#include <stdlib.h>                                                                                        
#include <stdarg.h>                                                                                        
//#include <ctos_newlib_startup.h>                                                                           
#include "wub_lib.h"                                                                                       
                                                                                                           
/*==========================================*                                                              
 *            D E F I N E S                 *                                                              
 *==========================================*/                                                             
                                                                                                           
#define d_BUFF_SIZE 128  //Define buffer size                                                             
                                                                                                           
//Define Encryption Key                                                                                    
#define d_ISSUER_MMK        "\x01\x02\x03\x04\x05\x06\x07\x08"                                            
//The Encryption Key in DES or MAC                                                                         
                                                                                                           
#define d_AES_KEY       "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x10\x11\x12\x13\x14\x15\x16"                
//The Encryption Key in AES                                                                                
                                                                                                           
#define d_ICV_KEY       "\x08\x07\x06\x05\x04\x03\x02\x01"                                                
//The ICV Key in MAC                                                                                       
                                                                                                           
#define d_ENCRYPTION_DATA   "\x31\x32\x33\x34\x35\x36\x37\x38"                                            
//Define the Encryption Data                                                                               
                                                                                                           
#define d_LINE_DOT 12   //A line is 12 dots in Printer                                                    
                                                                                                           
//The Modulus parameter                                                                                    
const BYTE baModulus[] = {0xE4,0x3C,0x11,0x36,0xFB,0x66,0x3A,0x75,0xD9,0x13,                                  
                        0x19,0x4C,0x2A,0x6F,0x06,0x5C,0xC9,0x69,0x44,0x16,                                    
                        0x24,0x89,0x14,0x23,0x94,0x90,0x0E,0x0D,0xE4,0x98,                                    
                        0xF8,0xCF,0x02,0xBC,0xB5,0x57,0x8E,0x57,0x4D,0xB8,                                    
                        0x67,0x68,0x28,0x90,0x02,0x4E,0x98,0xA3,0xD4,0x68,                                    
                        0xBC,0x87,0xBC,0xF5,0x50,0x19,0xDD,0x99,0xF1,0xE6,                                    
                        0x62,0xE8,0xD4,0xD3                                                                   
};                                                                                                         
//The Deponent Parameter                                                                                   
const BYTE baDeponent[] = {0xCE,0xFB,0x12,0x79,0x94,0x60,0x4F,0x60,0x14,0xAE,                             
                         0xD7,0x60,0x55,0x93,0x3E,0x67,0xE3,0x58,0x8D,0xA0,                                   
                        0xAF,0x1D,0x89,0xA0,0x02,0xD8,0xE9,0x85,0xFB,0xEC,                                    
                        0x26,0xA6,0x8E,0xB0,0x44,0x55,0xDC,0x3B,0x99,0xFB,                                    
                        0x4C,0x3C,0x1B,0x07,0x0A,0x6F,0xBF,0x71,0x52,0x5B,                                    
                        0xB4,0x10,0xD5,0x02,0x78,0x01,0xBD,0xC6,0x6F,0x02,                                    
                        0x3D,0xEB,0xAD,0x21                                                                   
};                                                                                                         
//The Exponent Parameter                                                                                                           
const BYTE baExponent[] = {0x01,0x00,0x01};                                      
                                                                                                           
/* =================================================================                                       
 * FUNCTION NAME: main                                                                                     
 * DESCRIPTION:   function main is responsible for all the tasks listed in the introduction to this demo.                                                               
 * RETURN:      none.                                                                            
 * NOTES:       none.                                                                                                   
 *================================================================= */                                     
int main(int argc,char *argv[])                                                                                             
{                                                                                                          
  //Declare Local Variable //                                                                              
  BYTE key;                                                                                                
  BYTE babuff[d_BUFF_SIZE];                                                                                
  BYTE baRSA[d_BUFF_SIZE],baRNG[d_BUFF_SIZE],baDES[d_BUFF_SIZE];                                           
  BYTE baAES[d_BUFF_SIZE],baMAC[d_BUFF_SIZE],baSHA[d_BUFF_SIZE];                                           
  SHA_CTX SHA_CTX;                                                                                         
  int i;                                                                                                   
                                                                                                           
  CTOS_LCDTSelectFontSize(0x101E);
                                                                                                           
  CTOS_LCDTClearDisplay ();                                                                                
                                                                                                           
  CTOS_LCDTSetReverse(TRUE);                                                                               
  CTOS_LCDTPrintXY(1,1,"   Encrpytion   ");                                                                
  CTOS_LCDTSetReverse(FALSE);                                                                              
                                                                                                           
  /****************************************                                                                
  *   The RSA Encryption                  *                                                                
  *****************************************/                                                                
  CTOS_LCDTPrintXY(1,2,"RSA Encryption");                                                                  
  memset(babuff,0x00,sizeof(babuff));                                                                      
  memcpy(&babuff[sizeof(baModulus)-strlen(d_ENCRYPTION_DATA)],d_ENCRYPTION_DATA,strlen(d_ENCRYPTION_DATA));
                                                                                                           
  //Perform the RSA exponent operation for encryption //                                                   
  CTOS_RSA((BYTE *)baModulus,sizeof(baModulus),(BYTE *)baExponent,sizeof(baExponent),babuff,baRSA);       
                                                                                                          
  //Print ant display the RSA result for encryption //                                                    
  CTOS_PrinterPutString("RSA Encryption");                                                                
  wub_hex_2_str(&baRSA[0],babuff,15);   //Hex value change to string //                                   
  CTOS_PrinterPutString(babuff);                                                                          
  wub_hex_2_str(&baRSA[15],babuff,15);                                                                    
  CTOS_PrinterPutString(babuff);                                                                          
  wub_hex_2_str(&baRSA[30],babuff,15);                                                                    
  CTOS_PrinterPutString(babuff);                                                                          
  wub_hex_2_str(&baRSA[45],babuff,15);                                                                    
  CTOS_PrinterPutString(babuff);                                                                          
  wub_hex_2_str(&baRSA[60],babuff,4);                                                                     
  CTOS_PrinterPutString(babuff);                        
                                                                                                          
  /****************************************                                                               
  *   The RSA Decryption                 *                                                                
  ****************************************/                                                               
  CTOS_LCDTPrintXY(1,3,"RSA Decryption");                                                                 
                                                                                                          
  //Perform the RSA exponent operation for decryption //                                                  
  CTOS_RSA((BYTE *)baModulus,sizeof(baModulus),(BYTE *)baDeponent,sizeof(baDeponent),baRSA,babuff);       
                                                                                                          
  //Print and display the RSA result for decryption //                                                    
  CTOS_PrinterPutString("\nRSA Decryption");                                                              
  wub_hex_2_str(&babuff[0],baRSA,15);                                                                     
  CTOS_PrinterPutString(baRSA);                                                                           
  wub_hex_2_str(&babuff[15],baRSA,15);                                                                    
  CTOS_PrinterPutString(baRSA);                                                                           
  wub_hex_2_str(&babuff[30],baRSA,15);                                                                    
  CTOS_PrinterPutString(baRSA);                                                                           
  wub_hex_2_str(&babuff[45],baRSA,15);                                                                    
  CTOS_PrinterPutString(baRSA);                                                                           
  wub_hex_2_str(&babuff[60],baRSA,4);                                                                     
  CTOS_PrinterPutString(baRSA);                                                              
                                                                                                          
  /***************************************                                                               
  *   Genertate the RNG                  *                                                                 
  ****************************************/                                                               
  CTOS_LCDTPrintXY(1,4,"RNG:");                                                                           
  //Generate 8 bytes random number                                                                        
  CTOS_RNG(baRNG);                                                                                        
                                                                                                          
  //Print and display RNG result                                                                          
  wub_hex_2_str(baRNG,babuff,8);                                                                          
  CTOS_LCDTPrintXY(5,4,babuff);                                                                           
  CTOS_PrinterPutString("\nRNG");                                                                         
  CTOS_PrinterPutString(babuff);                                                         
                                                                                                          
  /****************************************                                                               
  *   The DES Encryption/Decryption       *                                                             
  *****************************************/                                                               
  CTOS_LCDTPrintXY(1,5,"DES:");                                                                           
                                                                                                          
  //This API perform the DES encryption/decryption calculation //                                         
  CTOS_DES(d_ENCRYPTION, d_ISSUER_MMK, 8, d_ENCRYPTION_DATA, 8, baDES);                                   
                                                                                                          
  //Print and display the DES result //                                                                   
  wub_hex_2_str(baDES,babuff,8);                                                                          
  CTOS_LCDTPrintXY(5,5,babuff);                                                                           
  CTOS_PrinterPutString("\nDES Encryption");                                                              
  CTOS_PrinterPutString(babuff);                                                                    
                                                                                                          
  /***************************************                                                               
  *   The AES Encryption/Decryption      *                                                                 
  ****************************************/                                                               
  CTOS_LCDTPrintXY(1,6,"AES");                                                                            
  memset(babuff,0x00,sizeof(babuff));                                                                     
  memcpy(babuff,d_ENCRYPTION_DATA,8);                                                                     
  memcpy(&babuff[8],d_ENCRYPTION_DATA,8);                                                                 
                                                                                                          
  //Perform the AES encryption/decryption calculation //                                                  
  CTOS_AES(d_ENCRYPTION, d_AES_KEY, babuff, 16, baAES);                                                   
                                                                                                          
  //Print and display the AES result //                                                                   
  wub_hex_2_str(baAES,babuff,8);                                                                          
  CTOS_LCDTPrintXY(5,6,babuff);                                                                           
  CTOS_PrinterPutString("\nAES Encryption");                                                              
  CTOS_PrinterPutString(babuff);                                                                          
  wub_hex_2_str(&baAES[8],babuff,8);                                                                      
  CTOS_PrinterPutString(babuff);                                                                
                                                                                                          
  /***************************************                                                               
  *   The MAC Calculation                *                                                                 
  ****************************************/                                                               
  CTOS_LCDTPrintXY(1,7,"MAC:");                                                                           
                                                                                                          
  //Perform MAC calculation //                                                                            
  CTOS_MAC(d_ISSUER_MMK, 8, d_ICV_KEY, d_ENCRYPTION_DATA, 8, baMAC);                                      
                                                                                                          
  //Print and display the MAC result //                                                                   
  wub_hex_2_str(baMAC,babuff,8);                                                                          
  CTOS_LCDTPrintXY(5,7,babuff);                                                                           
  CTOS_PrinterPutString("\nMAC Calculation");                                                             
  CTOS_PrinterPutString(babuff);                                                    
                                                                                                          
  /***************************************                                                               
  *   Generater the SHA1                 *                                                                 
  ****************************************/                                                               
  CTOS_LCDTPrintXY(1,8,"SHA1");                                                                           
                                                                                                          
  //Initialize the SHA_CTX structure and perpart for the SHA1 operation //                                
  CTOS_SHA1Init(&SHA_CTX);                                                                                
                                                                                                          
  //Perform the SHA1 algorithm with the input data //                                                     
  CTOS_SHA1Update(&SHA_CTX,d_ENCRYPTION_DATA,8);                                                          
                                                                                                          
  //Finalize the SA1 operation and retrun the result //                                                   
  CTOS_SHA1Final(baSHA,&SHA_CTX);                                                                         
                                                                                                          
  //Print and display the SHA1 result //                                                                  
  wub_hex_2_str(baSHA,babuff,15);                                                                         
  CTOS_PrinterPutString("\nSHA1");                                                                        
  CTOS_PrinterPutString(babuff);                                                                          
  wub_hex_2_str(&baSHA[15],babuff,5);                                                                     
  CTOS_PrinterPutString(babuff);                                                                  
                                                                                                          
  CTOS_PrinterFline(d_LINE_DOT*10);  //Print a space 1 line                                               
                                                                                                          
  CTOS_KBDGet(&key);                                                                                   
                                                                                                          
  exit(0);
}

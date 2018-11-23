#ifndef COMMON_H
#define COMMON_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define SRCFILE     __FILE__
#define CODELINE    __LINE__

#define Success(a)  (a==0)
#define Failure(a)  (a!=0)

typedef unsigned int UINT_PTR, *PUINT_PTR;
typedef long LONG_PTR, *PLONG_PTR;
typedef UINT_PTR WPARAM;
typedef LONG_PTR LPARAM;

#ifdef CTOS_API
#include <ctosapi.h>
#include <typedef.h>

//typedef BYTE* PBYTE;
//typedef const char* PCSTR;
//typedef char* PSTR;
//typedef WORD* PWORD;
//typedef DWORD* PDWORD;

//#define PBYTE unsigned char*
//#define PCSTR const char*
//#define PWORD unsigned short*
//#define PDWORD unsigned int*



// #define DATATYPE_ANS    0   //alpha, numeric, and special characters
// #define DATATYPE_N      1   //numeric
// #define DATATYPE_PWD    2   //Password

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define MAKEWORD(a, b)  (((WORD)(a<<8)) | ((WORD)(b)))
#define MAKEDWORD(a, b) (((DWORD)(a<<16)) | ((DWORD)(b)))
#define LOWORD(l)        ((WORD)((DWORD)(l) & 0xffff))
#define HIWORD(l)        ((WORD)( ((DWORD)(l>>16)) & 0xffff))
#define LOBYTE(w)        ((BYTE)(((WORD)(w)) & 0xff))
#define HIBYTE(w)        ((BYTE)((((WORD)(w)) >> 8) & 0xff))
#define RGB(r,g,b)          ((DWORD)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#endif

// Data type
#define DATATYPE_N        0x00000001   //numeric characters only
#define DATATYPE_ANS    0x00000002   //alpha, numeric, and special characters
#define DATATYPE_B        0x00000004   //binary data
#define DATATYPE_Z        0x00000008   //magnetic stripe track-2 or track-3 data
#define DATATYPE_AN     0x00000010   //alpha and numeric characters
#define DATATYPE_NS     0x00000020   //numeric and special characters
#define DATATYPE_PWD    0x00000040   //numeric and special characters
#define DATATYPE_IP       0x00000080   //IP :numeric and Splitting point

#define DATATYPE_CN        0x00000100   //binary coded decimal
#define JUSTIFIED_OPEN    0x00000200   //justified open
#define JUSTIFIED_LEFT    0x00000400   //left-justified
#define JUSTIFIED_RIGHT    0x00000800   //right-justified

#define LENGTH_FIXED    0x00001000   //Fixed length
#define LENGTH_LL        0x00002000   //LL indicates the number of positions in the variable-length data field that follows. Length may be 1 to 99, unless otherwise restricted
#define LENGTH_LLL        0x00004000   //LLL indicates the number of positions in the variable-length data field that follows. Length may be 1 to 999, unless otherwise restricted

#define FIELD_USED        0x00008000   //Indicates the current field state of used
#define FIELD_DATA        0x00010000   //Field Data
#define FIELD_HEX        0x00020000   //Field Data is Hex input from UI


//hex2str format
#define  FMT_SPACE   0x0001  //Space separate
#define  FMT_16NEWLINE  0x0002  //16 bytes and one line
#define  FMT_32NEWLINE  0x0004  //32 bytes and one line

//////////////////////////////////////////////////////////////////////////
//Call Back function type.
#define  CB_MSG     0x04000
#define  CB_DEBUGINFO   CB_MSG+1  //Degug infor export.wParam = LPSTR, lParam = NULL

//////////////////////////////////////////////////////////////////////////

#endif
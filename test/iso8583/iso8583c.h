/*
 * File:   iso8583c.h
 * Author: PeyJiun
 *
 * Created on 2008年11月11日, 上午 11:35
 */

//#define d_VERSION   "1.00"
#define d_VERSION   "1.01"  //change Class

#ifndef _ISO8583C_H
#define	_ISO8583C_H

enum em_datatype
{
    //each data element represents 1 bit (8 data element = 1 byte)
    t_b = 0x01,

    //each data element represents 1 nibble (2 data element = 1 byte)
    t_n,
    t_z,

    //each data element represents 1 byte.
    t_a,
    t_s,
    t_an,
    t_as,
    t_ns,
    t_ans,

    //Numeric data with a preceding sign of "c" for credit, "d" for debit, e.g. xn 17 in amount, net
    //reconciliation means prefix "c" or "d" and 16 digits of amount.

    t_xn,
};


#define BM_87           0
#define BM_93           1
#define BM_USER         2
    
//Return Code
#define d_IS_OK                 0x0000
#define d_BITMAP_NOT_INIT       0x0001
#define d_WRONG_PARA            0x0002
#define d_MSG_TYPE_NOT_SET      0x0003
#define d_DATA_EXIST            0x0004
#define d_DATA_NOT_EXIST        0x0005
#define d_DATA_LEN_DIFF         0x0006
#define d_DATA_LEN_EXCEED       0x0007
#define d_DATA_TYPE_WRONG       0x0008
#define d_EXCEED_BUFF_SIZE      0x0009
#define d_EXCEED_BITMAP_SIZE    0x000A
#define d_TPDU_NOT_SET          0x000B
#define d_TPDU_DIFF             0x000C
#define d_DATA_LEN_ERROR		0x000D

#define BUFFER_SIZE         4096
#define BITMAP_SIZE         128+1   //+BitMap flag
    
#define ByRight		0
#define ByLeft		1

typedef struct BITMAP_          //7 bytes
{
    BYTE bitflag;               // bit 是否 ON
    USHORT length;                // Field 的實際長度
    USHORT maxlen;                // Field 的最大長度
    BYTE variableflag;          // Field 是否為變動長度
                                // 0 : 固定長度
                                // 2 : 2位變長  LLVAR
                                // 3 : 3位變長  LLLVAR
    enum em_datatype datatype;              // Field 的資料型態 (0x01 ~ 0x0D)
    USHORT pos;
    BYTE align_by;              // 0 : by_Right
    BYTE fill_char;
																// 1 : by_Left 
} BITMAP_;

typedef struct BITMAP_CH_       //4 bytes
{
    USHORT maxlen;                // Field 的最大長度
    BYTE variableflag;          // Field 是否為變動長度
                                // 0 : 固定長度
                                // 2 : 2位變長
                                // 3 : 3位變長
    enum em_datatype datatype;              // Field 的資料型態 (0x01 ~ 0x0D)
    BYTE align_by;              // 0 : by_Right
    BYTE fill_char;
																// 1 : by_Left 
} BITMAP_CH;
//第 0 field 固定為 message type!!!!

typedef struct
{
    USHORT len;
    BYTE TPDU[8];
}_stTPDU;


void ISO8583_Initial(void);

USHORT ISO8583_BitMap_ChangeType(IN BYTE bBitMap_Type, IN BITMAP_CH *BitMap_User);
        
USHORT ISO8583_BitMap_New(IN USHORT usMsgType);

USHORT ISO8583_BitMap_Pack(OUT BYTE *pbErrBit, INOUT USHORT *pusOutLen, OUT BYTE *pbaOutBuffer);

USHORT ISO8583_BitMap_unPack(IN USHORT usInLen, IN BYTE *pbaInBuffer);  

USHORT ISO8583_Get_BitMapData(OUT USHORT *pusMsgType, OUT BYTE *pbLen, OUT BYTE *pbaBitMap);

USHORT ISO8583_Data_Get(IN BYTE bBit, OUT USHORT *pusOutLen, OUT BYTE *pbaOutData);

USHORT ISO8583_Data_GetULONG(IN BYTE bBit, OUT ULONG *pulOutValue);

USHORT ISO8583_Data_Set(IN BYTE bBit, IN USHORT usInLen, IN BYTE *pbaInData);

USHORT ISO8583_Data_SetULONG(IN BYTE bBit, IN ULONG ulInValue);

BOOL ISO8583_Check_BitSet(IN BYTE bBit);

USHORT ISO8583_Get_DataType(IN BYTE bBit, OUT BYTE *pbVariableFlag, OUT enum em_datatype *pemDatatype);

#ifdef	__cplusplus
}
#endif

#endif	/* _ISO8583C_H */


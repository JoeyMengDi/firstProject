/* 
 * File:   Base8583.h
 * Author: Sword_zhang
 *
 * Created on 2017.02.11 8:57
 * 
 * History:
 *           #2018.06.04, Alan.Ren
 *           1. Rename all export function name begin with CTAP_*;
 */

#ifndef BASE8583_H
#define	BASE8583_H

#ifdef	__cplusplus
extern "C" {
#endif

//Initialize base8583 data
void CTAP_Clear8583(void);

/////////////////////////////////////////////////
// SetHeadInfo 
// function: Set transaction header information
// Param	IN: pbTxnDes: transaction spec description string
//                       nTxnDesLen: description string length
// 	     wSkipLength: Total transaction data header length
//	     wDEType: Data Element type (64 or 128)
//
// Return: return code please view errorcode.h
/////////////////////////////////////////////////
WORD CTAP_SetHeadInfo(BYTE *pbyTxnDes, int nTxnDesLen, WORD wSkipLength, WORD wDEType);


/////////////////////////////////////////////////
// SetHeadData 
// function: Set transaction header data
// Param	IN: pbHeadData: transaction header data
//                      nDataLen: data length
//
// Return: return code please view errorcode.h
/////////////////////////////////////////////////
WORD CTAP_SetHeadData(BYTE *pbyHeadData, int nDataLen);


//Get Data element type (64 or 128)
WORD CTAP_GetDEType(void);

/////////////////////////////////////////////////
// SetFieldData 
// function: Set field data
// Param	IN: bField: filed(Data Element) index
//                        pbFieldData: Data pointer
//                        nDataLen: Data length
// Return: return code please view errorcode.h
/////////////////////////////////////////////////
WORD CTAP_SetFieldData(BYTE byField, BYTE *pbyFieldData, int nDataLen);

/////////////////////////////////////////////////
// ClearFieldData
// Function: Clear data from a data element
// Param	IN: byField: data element index
//
// Return: return code please view errorcode.h
/////////////////////////////////////////////////
WORD CTAP_ClearFieldData(BYTE byField);


/////////////////////////////////////////////////
// Pack
// Function: Pack all data element.
// Param	IN: pszXmlFile: XML file name
//                       pnDataLen: Buffer len
//                       pnErrLen: error buffer len
//
//              OUT: pbOutBuf: Output pack data buffer
//                       pnDataLen: output pack data length
//                       pbErrBuf:  Output error string
//                       pnErrLen:  error string length
//
// Return: return code please view errorcode.h
/////////////////////////////////////////////////
WORD CTAP_Pack(char *pszXmlFile, BYTE *pbyOutBuf, int *pnDataLen, BYTE *pbyErrBuf, int *pnErrLen);

/////////////////////////////////////////////////
// Unpack
// Function: Unpack raw data to data element.
// Param	IN: pszXmlFile: XML file name
//                       pbRawData: Raw data
//                       nRawDataLen: Raw data length
//                       pnErrorBufLen: error string buf length
//
//             OUT: pbErrorBuf: Output error string buffer
//                      pnErrorBufLen: error string length
//
// Return: return code please view errorcode.h
/////////////////////////////////////////////////
WORD CTAP_Unpack(char *pszXmlFile, BYTE *pbyRawData, int nRawDataLen, BYTE *pbyErrorBuf, int *pnErrorBufLen);


/////////////////////////////////////////////////
// GetHeadData
// Function: Get the head data from unpacker the raw data
// Param	IN: pbBuf: buffer
//                       pnBufLen: buffer length
//
//              OUT: pbBuf: Output header data
//                       pnBufLen: output header data length
//
// Return: return code please view errorcode.h
/////////////////////////////////////////////////
WORD CTAP_GetHeadData(BYTE *pbyBuf, int *pnBufLen);


/////////////////////////////////////////////////
// GetBitmap
// Function: Get the bitmap data
// Param	IN: pbBuf: buffer
//                       pnBufLen: buffer length
//
//              OUT: pbBuf: Output bitmap data
//                       pnBufLen: output bitmap data length
//
// Return: return code please view errorcode.h
/////////////////////////////////////////////////
WORD CTAP_GetBitmap(BYTE *pbyBuf, int *pnBufLen);

/////////////////////////////////////////////////
// GetFieldData
// Function: Get the bitmap data
// Param	IN: bField: DE index
//                       pbBuf: buffer
//                       pnLen: buffer length
//
//              OUT: pbBuf: Output DE data
//                       pnLen: output DE data length
//
// Return: return code please view errorcode.h
/////////////////////////////////////////////////
WORD CTAP_GetFieldData(BYTE byField, BYTE *pbyBuf,  int *pnLen);

#ifdef	__cplusplus
}
#endif

#endif	/* _DYNAMICLIB_H */


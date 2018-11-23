/*
 * Copyright: 2017, Castles
 * All rights reserved.
 *
 * File: CollisTLV.h
 * Version: 0.0.1
 * Author: Jeff
 */

#ifndef COLLIS_TLV_H
#define COLLIS_TLV_H

//#include "../StdafxHead.h"

/////////////////////////////////////////////////
// CollisTLVEnableDebug
// Function: Enable to debug 
// Param IN: bEnable:  flag of debug
/////////////////////////////////////////////////
void CollisTLVEnableDebug(BOOL bEnable);

/////////////////////////////////////////////////
// CollisTLVProcess
// Function: Convert requst TLV to Collis type, Get response by socket 
// Param IN: pszIp,     IP
//           nPort,     socket port
//           nTimeout,  socket connect/recv timeout
//           cTLVIn,    requst TLV
//           wType,     requst TLV type
//
//       OUT: cTLVOut: response TLV
//
// Return: return code please view defs.h
/////////////////////////////////////////////////
WORD CollisTLVProcess(const char *pszIp, int nPort, int nTimeout, const CByteStream& cTLVIn, 
                    WORD wType, CByteStream& cTLVOut);

#endif


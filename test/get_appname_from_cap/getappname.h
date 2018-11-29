/* 
 * File:   getappname.h
 * Author: Vic Liao
 *
 * Created on 2012
 */

#ifndef _LIB_GETAPPNAME_H
#define	_LIB_GETAPPNAME_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define d_OK            0x0000
#define MCI_NO_EXIST    0x0001
#define CAP_NO_EXIST    0x0002
#define NOT_APP_CAP     0x0003


unsigned short LIB_GetAppNameFromCAP(char* MCI_FileName, char* AppNameStr);

#ifdef	__cplusplus
}
#endif

#endif	/* _LIB_GETAPPNAME_H */


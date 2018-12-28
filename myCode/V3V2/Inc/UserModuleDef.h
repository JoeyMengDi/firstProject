
/*
 * File Name: UserModuleDef.h
 * Description: Define basic of type of user module.
 * 
 * Create Date: 2018.05.07
 * Author: Alan.Ren
 */

#ifndef _H_H_MODULE_DEF_H_H_
#define _H_H_MODULE_DEF_H_H_

#define WORD unsigned short

/**
 *  The maximum number of user modules.
 */
#define MAXIMUM_USER_MODULE     6


/**
 * USER_MODULEID
 * 
 * @note:
 *      1. Enum for User Module ID
 *      2. The eModule ID in the first params of the function Manage_UMRegister 
 *          must be an element of the following USER_MODULEID.
 *      3. The eModule ID is unique when register multiple user modules.
 *      4. The maximum number of user modules is USER_MODULE_INVALID
**/
typedef enum enum_USER_MODULETYPE
{
    USER_MODULE_ID1         = 1,
    USER_MODULE_ID2,
    USER_MODULE_ID3,
    USER_MODULE_ID4,
    USER_MODULE_ID5,
    USER_MODULE_ID6,
    USER_MODULE_INVALID     = (MAXIMUM_USER_MODULE + 1)
}USER_MODULEID;


/**
 * USER_MODULESTATE, PUSER_MODULESTATUS
 * 
 * @note:
 *      The current module's state
 *      eModuleID       : The current module's ID
 *      wModuleStatus   : The current module's status
**/
typedef struct stModuleStatus
{
    USER_MODULEID               eModuleID;
    WORD                        wModuleStatus;
}USER_MODULESTATE, *PUSER_MODULESTATUS;


/**
 * USER_MODULEINFO, PUSER_MODULEINFO
 * 
 * @note:
 *      All the user module's state
 *      wUserModuleNum  : The UserModule's number
 *      stModuleStatus  : See the USER_MODULESTATE
**/
typedef struct stModuleInfo
{
    WORD                        wUserModuleNum;
    USER_MODULESTATE            stModuleStatus[MAXIMUM_USER_MODULE];
}USER_MODULEINFO, *PUSER_MODULEINFO;


/**
 * USER_MODULE_INIT
 * 
 * Callback Function Point:
 *          The init function pointer for the user module
 * 
 * @param
 *          none
 * 
 * @return 
 *          0       : OK
 *          other   : Error code defined by the user module
 */  
typedef WORD (*USER_MODULE_INIT)(void);


/**
 * USER_MODULE_STOP
 * 
 * Callback Function Point:
 *          The stop function pointer for the user module
 * 
 * @param
 *          none
 * 
 * @return 
 *          0       : Stop user module OK
 *          other   : Error code defined by the user module
 */  
typedef WORD (*USER_MODULE_STOP)(void);


/**
 * USER_MODULE_GETSTATE
 * 
 * Callback Function Point:
 *          The GetStatus function pointer for the user module
 * 
 * @param
 *          [OUT]*pwStatus :
 *              0   : The module is not alive
 *              1   : The module is alive
 * 
 * @return 
 *          0       : Get the user module status OK.
 *          other   : Error code defined by the user module
 */  
typedef WORD (*USER_MODULE_GETSTATE)(OUT WORD *pwStatus);


/**
 * USER_MODULEENTRY, PUSER_MODULEENTRY
 * 
 * @note:
 *      eModuleID           : Must be an element of USER_MODULEID
 *      pModule_Init        : Refer to the definition of USER_MODULE_INIT above
 *      pModule_Stop        : Refer to the definition of USER_MODULE_STOP above
 *      pModule_GetState   : Refer to the definition of USER_MODULE_GETSTATE above
**/
typedef struct
{
    USER_MODULEID               eModuleID;
    USER_MODULE_INIT            pModule_Init;
    USER_MODULE_STOP            pModule_Stop;
    USER_MODULE_GETSTATE        pModule_GetState;
}USER_MODULEENTRY, *PUSER_MODULEENTRY;

#endif 
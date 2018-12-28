#include "../SRC/StdafxHead.h"
#include "libVKBD.h"
#include "CVKBD.h"

static CVKBD cVKBD;

/**
 * VirtualKBDOpen
 * Function: Open virtual KBD
 * 
 * @param
 *          none
 * 
 * @return 
 *          OK - successful
 *          others - failed
 * 
 * Auther: Tinker Han
 */
WORD CTAP_VirtualKBDOpen(void)
{
    DEBUG_ENTRY();
    
    USHORT usRet = cVKBD.VKBDOpen();
    if(usRet != OK)
        return DEBUG_RETCODE("ERROR: VKBDOpen fail", usRet);
    
    return DEBUG_EXIT(OK);
}

/**
 * VirtualKBDClose
 * Function: close virtual KBD
 * 
 * @param
 *          none
 * 
 * @return 
 *          OK - successful
 *          others - failed
 * 
 * Auther: Tinker Han
 */
WORD CTAP_VirtualKBDClose(void)
{
    DEBUG_ENTRY();
    
    USHORT usRet = cVKBD.VKBDClose();
    if(usRet != OK)
        return DEBUG_RETCODE("ERROR: VKBDClose fail", usRet);
    
    return DEBUG_EXIT(OK);    
}

/**
 * VirtualKBDShow
 * Function: show UI
 * 
 * @param
 *          none
 * 
 * @return 
 *          OK - successful
 *          others - failed
 * 
 * Auther: Tinker Han
 */
WORD CTAP_VirtualKBDShow(void)
{
    DEBUG_ENTRY();
    
    USHORT usRet = cVKBD.VKBDShowInterface();
    if(usRet != OK)
        return DEBUG_RETCODE("ERROR: VKBDShow fail", usRet);
    
    return DEBUG_EXIT(OK);
}

/**
 * VirtualKBDHide
 * Function: hide the UI
 * 
 * @param
 *          none
 * 
 * @return 
 *          OK - successful
 *          others - failed
 * 
 * Auther: Tinker Han
 */
WORD CTAP_VirtualKBDHide(void)
{
    DEBUG_ENTRY();
    
    USHORT usRet = cVKBD.VKBDHideInterface();
    if(usRet != OK)
        return DEBUG_RETCODE("ERROR: VKBDHide fail", usRet);
    
    return DEBUG_EXIT(OK);
}

/**
 * VirtualKBDBufFlush
 * Function: clear the all key buffer
 * 
 * @param
 *          none
 * 
 * @return 
 *          OK - successful
 *          others - failed
 * 
 * Auther: Tinker Han
 */
WORD CTAP_VirtualKBDBufFlush(void)
{
    DEBUG_ENTRY();
    
    USHORT usRet = cVKBD.VKBDBufFlush();
    if(usRet != OK)
        return DEBUG_RETCODE("ERROR: VKBDBufFlush fail", usRet);
    
    return DEBUG_EXIT(OK);
}

/**
 * VirtualKBDGet
 * Function: virtual KBD get a key
 * 
 * @param
 *          [OUT] pbyKey - return the key value
 * 
 * @return 
 *          OK - successful
 *          others - failed
 * 
 * Auther: Tinker Han
 */
WORD CTAP_VirtualKBDGet(BYTE* pbyKey)
{
    DEBUG_ENTRY();
    
    USHORT usRet = cVKBD.VKBDGet(pbyKey);
    if(usRet != OK)
        return DEBUG_RETCODE("ERROR: VKBDGetKey fail", usRet);
    
    return DEBUG_EXIT(OK);
}

/**
 * VirtualKBDHit
 * Function: virtual KBD hit a key
 * 
 * @param
 *          [OUT] pbyKey - return the key value
 * 
 * @return 
 *          OK - successful
 *          others - failed
 * 
 * Auther: Tinker Han
 */
WORD CTAP_VirtualKBDHit(BYTE* pbyKey)
{
    USHORT usRet = cVKBD.VKBDHit(pbyKey);
    if(usRet != OK)
    {
        DEBUG_INFO(DEBUGINFO_NORMAL, "ERROR: VKBDHitKey fail");
        return usRet;
    }
        
    return OK;
}

/**
 * VirtualKBDSetSound
 * Function: turn on or turn off sound for virtual KBD
 * 
 * @param
 *          [IN] bOnOff - sound switch flag
 *               TRUE: turn on  FALSE: turn off
 * 
 * @return 
 *          OK - successful
 *          others - failed
 * 
 * Auther: Tinker Han
 */
WORD CTAP_VirtualKBDSetSound(BOOL  bOnOff)
{
    DEBUG_ENTRY();
    
    USHORT usRet = cVKBD.VKBDSetSound(bOnOff);
    if(usRet != OK)
        return DEBUG_RETCODE("ERROR: VKBDSetSound fail", usRet);
    
    return DEBUG_EXIT(OK);
}

WORD CTAP_VirtualKBDSetDefaultMode(BYTE byDefMode)
{
    DEBUG_ENTRY();
    
    USHORT usRet = cVKBD.VKBDChooseInterface(byDefMode);
    if(usRet != OK)
        return DEBUG_RETCODE("ERROR: VKBDSetDefaultMode fail", usRet);
    
    return DEBUG_EXIT(OK);
}

WORD CTAP_VirtualKBDGetDisplayColumnData(CByteStream& cData)
{
    DEBUG_ENTRY();
    
    USHORT usRet = cVKBD.VKBDGetImportData(cData);
    if(usRet != OK)
        return DEBUG_RETCODE("ERROR: VKBDSetDefaultMode fail", usRet);
    
    return DEBUG_EXIT(OK);
}
    

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CVKBD.h"

static pthread_mutex_t s_cMutex = PTHREAD_MUTEX_INITIALIZER;

CVKBD::CVKBD() : m_bIsOpen(FALSE), m_bIsShowButton(FALSE),
m_bIsShow(FALSE), m_enMode(VKBD_MODE_NUMBER),
m_VKBDThreadID(INVALID_THREAD_ID), m_TouchDevHandle(INVALID_TOUCH_DEV_HANDLE),
m_lPressX(0), m_lPressY(0), m_lUpX(0), m_lUpY(0), m_byNowScope(SCOPE_VOID),
m_byLastScope(SCOPE_VOID), m_ulTime(0), m_byKeyChooseOneValue(d_KBD_INVALID),
m_byKeyChooseTwoValue(d_KBD_INVALID), m_byKeyChooseThreeValue(d_KBD_INVALID),
m_usDisplayColumnLen(0), m_byKeyBuf(d_KBD_INVALID), m_bBeepFlag(TRUE),
m_bIsShowDisplay(FALSE), m_usJudgeDsiplayColumnLen(0) {
    m_cDisplayColumn.Empty();
    CTOS_FontSelectMode(d_FONT_DEVICE_LCD_0, d_FONT_TTF_MODE);
    CTOS_FontTTFSelectFontFile(d_FONT_DEVICE_LCD_0, (BYTE*) "Inconsolata.ttf", 0);
}

CVKBD::~CVKBD() {
}

USHORT CVKBD::VKBDOpen() {
    DEBUG_ENTRY();

    if (m_bIsOpen)
        return DEBUG_RETCODE("Already open!", FAILED);

    int iRet = 0;
    USHORT usRet = 0;
    m_bIsOpen = TRUE;

    iRet = pthread_create(&m_VKBDThreadID, NULL, VKBDThreadFun, (void*) this);
    if (iRet != OK) {
        m_bIsOpen = FALSE;
        return FAILED;
    }

    usRet = VKBDInitButton();
    if (usRet != OK) {
        m_bIsOpen = FALSE;
        return FAILED;
    }

    return DEBUG_EXIT(OK);
}

USHORT CVKBD::VKBDClose() {
    DEBUG_ENTRY();

    VKBDHideInterface();
    m_bIsOpen = FALSE;
    m_bIsShowButton = FALSE;
    m_bIsShow = FALSE;
    m_enMode = VKBD_MODE_NUMBER;
    m_VKBDThreadID = INVALID_THREAD_ID;
    m_TouchDevHandle = INVALID_TOUCH_DEV_HANDLE;
    m_lPressX = m_lPressY = m_lUpX = m_lUpY = 0;
    m_byNowScope = m_byLastScope = SCOPE_VOID;
    m_ulTime = 0;
    m_byKeyChooseOneValue = m_byKeyChooseTwoValue = m_byKeyChooseThreeValue = d_KBD_INVALID;
    m_usDisplayColumnLen = 0;
    m_byKeyBuf = d_KBD_INVALID;
    m_bBeepFlag = TRUE;
    m_bIsShowDisplay = FALSE;
    m_usJudgeDsiplayColumnLen = 0;

    return DEBUG_EXIT(OK);
}

USHORT CVKBD::VKBDChooseInterface(BYTE byDefaultMode) {
    DEBUG_ENTRY();

    if (m_bIsOpen)
        return DEBUG_RETCODE("Already open!", FAILED);

    switch (byDefaultMode) {
        case 1:
            m_enMode = VKBD_MODE_NUMBER;
            break;

        case 2:
            m_enMode = VKBD_MODE_LETTER;
            break;

        case 3:
            m_enMode = VKBD_MODE_CAP_LETTER;
            break;

        case 4:
            m_enMode = VKBD_MODE_SPECIAL_CHARACTER;
            break;

        default:
            return DEBUG_RETCODE("ERROR: invalid mode", -1);
            break;
    }

    return DEBUG_EXIT(OK);
}

USHORT CVKBD::VKBDShowInterface() {
    DEBUG_ENTRY();

    if (!m_bIsOpen)
        return DEBUG_RETCODE("Already open or show!", FAILED);

    USHORT usRet = 0;

    if (!m_bIsShowDisplay) {
        usRet += m_cBtDisplayColumn.ShowButton();
        m_bIsShowDisplay = TRUE;
    }
    usRet += VKBDSetButtonCaption();
    usRet += m_cBtRow1Column1.ShowButton();
    usRet += m_cBtRow1Column2.ShowButton();
    usRet += m_cBtRow1Column3.ShowButton();
    usRet += m_cBtRow2Column1.ShowButton();
    usRet += m_cBtRow2Column2.ShowButton();
    usRet += m_cBtRow2Column3.ShowButton();
    usRet += m_cBtRow3Column1.ShowButton();
    usRet += m_cBtRow3Column2.ShowButton();
    usRet += m_cBtRow3Column3.ShowButton();
    usRet += m_cBtRow4Column1.ShowButton();
    usRet += m_cBtRow4Column2.ShowButton();
    usRet += m_cBtRow4Column3.ShowButton();
    usRet += m_cBtClear.ShowButton();
    usRet += m_cBtCancel.ShowButton();
    usRet += m_cBtOK.ShowButton();
    CTOS_LCDGShowPicEx(d_LCD_SHOWPIC_RGB, 241, 281, (BYTE *) by_PRESS_CANCEL_BRIGHT, sizeof (by_PRESS_CANCEL_BRIGHT), 79);
    CTOS_LCDGShowPicEx(d_LCD_SHOWPIC_RGB, 241, 331, (BYTE *) by_PRESS_CLEAR_BRIGHT, sizeof (by_PRESS_CLEAR_BRIGHT), 79);
    CTOS_LCDGShowPicEx(d_LCD_SHOWPIC_RGB, 241, 381, (BYTE *) by_PRESS_OK_BRIGHT, sizeof (by_PRESS_OK_BRIGHT), 78);

    if (usRet != OK)
        return DEBUG_RETCODE("Fail to show button!", usRet);

    m_bIsShow = TRUE;
    return DEBUG_EXIT(OK);
}

USHORT CVKBD::VKBDHideInterface(void) {
    DEBUG_ENTRY();

    m_bIsShow = FALSE;
    m_bIsShowDisplay = FALSE;
    usleep(500000);
    CTOS_LCDBackGndColor(WHITE_COLOR);
    WORD wRet = CTOS_LCDGSetBox(0, 240, 320, 240, 0); //clear virtual keyboard scope 
    if (wRet != OK)
        return DEBUG_RETCODE("ERROR: CTOS_LCDGClearWindow! hide fail", wRet);

    return DEBUG_EXIT(OK);
}

USHORT CVKBD::VKBDInitButton() {
    DEBUG_ENTRY();

    USHORT usRet = 0;

    usRet += m_cBtDisplayColumn.Init(0, 240, 320, 40);
    usRet += m_cBtDisplayColumn.ChangeForeGndColor(RGB(0, 255, 255));

    usRet += m_cBtRow1Column1.Init(0, 280, 80, 50);
    usRet += m_cBtRow1Column2.Init(80, 280, 80, 50);
    usRet += m_cBtRow1Column3.Init(160, 280, 80, 50);

    usRet += m_cBtRow2Column1.Init(0, 330, 80, 50);
    usRet += m_cBtRow2Column2.Init(80, 330, 80, 50);
    usRet += m_cBtRow2Column3.Init(160, 330, 80, 50);

    usRet += m_cBtRow3Column1.Init(0, 380, 80, 50);
    usRet += m_cBtRow3Column2.Init(80, 380, 80, 50);
    usRet += m_cBtRow3Column3.Init(160, 380, 80, 50);

    usRet += m_cBtRow4Column1.Init(0, 430, 80, 50);
    usRet += m_cBtRow4Column2.Init(80, 430, 80, 50);
    usRet += m_cBtRow4Column3.Init(160, 430, 80, 50);

    usRet += m_cBtCancel.Init(240, 280, 80, 50);
    usRet += m_cBtClear.Init(240, 330, 80, 50);
    usRet += m_cBtOK.Init(240, 380, 80, 100);

    if (usRet != OK) {
        CTOS_LCDForeGndColor(RGB(255, 255, 255));
        CTOS_LCDGSetBox(0, 280, 320, 200, 1);
        return DEBUG_RETCODE("Init Button failed!", FAILED);
    }

    return DEBUG_EXIT(OK);
}

USHORT CVKBD::VKBDSetButtonCaption() {
    DEBUG_ENTRY();

    USHORT usRet = 0;
    CByteStream cBuff;

    switch (m_enMode) {
        case VKBD_MODE_NUMBER:
            cBuff.Empty();
            cBuff.Write("1", 1);
            usRet += m_cBtRow1Column1.SetButtonCaption(cBuff, 1);
            cBuff.Empty();
            cBuff.Write("2", 1);
            usRet += m_cBtRow1Column2.SetButtonCaption(cBuff, 1);
            cBuff.Empty();
            cBuff.Write("3", 1);
            usRet += m_cBtRow1Column3.SetButtonCaption(cBuff, 1);
            cBuff.Empty();
            cBuff.Write("4", 1);
            usRet += m_cBtRow2Column1.SetButtonCaption(cBuff, 1);
            cBuff.Empty();
            cBuff.Write("5", 1);
            usRet += m_cBtRow2Column2.SetButtonCaption(cBuff, 1);
            cBuff.Empty();
            cBuff.Write("6", 1);
            usRet += m_cBtRow2Column3.SetButtonCaption(cBuff, 1);
            cBuff.Empty();
            cBuff.Write("7", 1);
            usRet += m_cBtRow3Column1.SetButtonCaption(cBuff, 1);
            cBuff.Empty();
            cBuff.Write("8", 1);
            usRet += m_cBtRow3Column2.SetButtonCaption(cBuff, 1);
            cBuff.Empty();
            cBuff.Write("9", 1);
            usRet += m_cBtRow3Column3.SetButtonCaption(cBuff, 1);
            cBuff.Empty();
            cBuff.Write("abc", 3);
            usRet += m_cBtRow4Column1.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("0", 1);
            usRet += m_cBtRow4Column2.SetFontSize(d_FONT_16x30);
            usRet += m_cBtRow4Column2.SetButtonCaption(cBuff, 1);
            cBuff.Empty();
            cBuff.Write(".", 1);
            usRet += m_cBtRow4Column3.SetButtonCaption(cBuff, 1);
            break;

        case VKBD_MODE_LETTER:
            DEBUG_ENTRY();
            cBuff.Empty();
            cBuff.Write("qz", 2);
            usRet += m_cBtRow1Column1.SetButtonCaption(cBuff, 2);
            cBuff.Empty();
            cBuff.Write("abc", 3);
            usRet += m_cBtRow1Column2.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("def", 3);
            usRet += m_cBtRow1Column3.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("ghi", 3);
            usRet += m_cBtRow2Column1.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("jkl", 3);
            usRet += m_cBtRow2Column2.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("mno", 3);
            usRet += m_cBtRow2Column3.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("prs", 3);
            usRet += m_cBtRow3Column1.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("tuv", 3);
            usRet += m_cBtRow3Column2.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("wxy", 3);
            usRet += m_cBtRow3Column3.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("#+=", 3);
            usRet += m_cBtRow4Column1.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("space", 4);
            usRet += m_cBtRow4Column2.SetFontSize(d_FONT_12x24);
            usRet += m_cBtRow4Column2.SetButtonCaption(cBuff, 4);
            cBuff.Empty();
            cBuff.Write("T/t", 3);
            usRet += m_cBtRow4Column3.SetButtonCaption(cBuff, 3);
            break;

        case VKBD_MODE_CAP_LETTER:
            cBuff.Empty();
            cBuff.Write("QZ", 2);
            usRet += m_cBtRow1Column1.SetButtonCaption(cBuff, 2);
            cBuff.Empty();
            cBuff.Write("ABC", 3);
            usRet += m_cBtRow1Column2.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("DEF", 3);
            usRet += m_cBtRow1Column3.SetButtonCaption(cBuff, 3);
            cBuff.Write("GHI", 3);
            usRet += m_cBtRow2Column1.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("JKL", 3);
            usRet += m_cBtRow2Column2.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("MNO", 3);
            usRet += m_cBtRow2Column3.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("PRS", 3);
            usRet += m_cBtRow3Column1.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("TUV", 3);
            usRet += m_cBtRow3Column2.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("WXY", 3);
            usRet += m_cBtRow3Column3.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("#+=", 3);
            usRet += m_cBtRow4Column1.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("space", 4);
            usRet += m_cBtRow4Column2.SetFontSize(d_FONT_12x24);
            usRet += m_cBtRow4Column2.SetButtonCaption(cBuff, 4);
            cBuff.Empty();
            cBuff.Write("T/t", 3);
            usRet += m_cBtRow4Column3.SetButtonCaption(cBuff, 3);
            break;

        case VKBD_MODE_SPECIAL_CHARACTER:
            cBuff.Empty();
            cBuff.Write("~!@", 3);
            usRet += m_cBtRow1Column1.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("#$%", 3);
            usRet += m_cBtRow1Column2.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("^&*", 3);
            usRet += m_cBtRow1Column3.SetButtonCaption(cBuff, 3);
            cBuff.Write("([{", 3);
            usRet += m_cBtRow2Column1.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write(")]}", 3);
            usRet += m_cBtRow2Column2.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("+-=", 3);
            usRet += m_cBtRow2Column3.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("_|\\", 3);
            usRet += m_cBtRow3Column1.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("\"'`", 3);
            usRet += m_cBtRow3Column2.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write(":;?", 3);
            usRet += m_cBtRow3Column3.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("123", 3);
            usRet += m_cBtRow4Column1.SetButtonCaption(cBuff, 3);
            cBuff.Empty();
            cBuff.Write("<>", 2);
            usRet += m_cBtRow4Column2.SetFontSize(d_FONT_16x30);
            usRet += m_cBtRow4Column2.SetButtonCaption(cBuff, 2);
            cBuff.Empty();
            cBuff.Write(",./", 3);
            usRet += m_cBtRow4Column3.SetButtonCaption(cBuff, 3);
            break;
        default:
            return FAILED;
    }

    if (usRet != OK)
        return DEBUG_RETCODE("Fail to show caption!", usRet);

    return DEBUG_EXIT(OK);
}

void* VKBDThreadFun(void* pVoid) {
    DEBUG_ENTRY();
    pthread_detach(pthread_self());
    CVKBD *cVKBD = ((CVKBD*) pVoid);

    USHORT usRet = 0;
    cVKBD->m_ulTime = GetSysTime();

    while (1) {
        if (!cVKBD->m_bIsOpen)
            break;

        if (!cVKBD->m_bIsShow) {
            DEBUG_INFO(DEBUGINFO_NORMAL, "Show flag is FALSE");
            usleep(100000);
            continue;
        }

        usRet = cVKBD->VKBDShowDisplayColumnLen();
        if (usRet != OK)
            continue;

        long lDownX = 0, lDownY = 0, lUpX = 0, lUpY = 0;
        WORD wRet = cVKBD->HandleTouch(lDownX, lDownY, lUpX, lUpY);
        if (wRet != OK || wRet == ERROR_VKBD_TOUCH_TIMEOUT) {
            usleep(10000);
            continue;
        }

        if (SCOPE_INVALID(lDownX, lDownY) && SCOPE_INVALID(lUpX, lUpY)) {
            DEBUG_INFO(DEBUGINFO_NORMAL, "Invalid scope");
            continue;
        }

        if (cVKBD->m_bBeepFlag) {
            wRet = CTOS_Beep();
            if (wRet != OK)
                DEBUG_RETCODE("ERROR: CTOS_Beep", wRet);
        }

        wRet = cVKBD->ClickScope(&lDownX, &lDownY, &lUpX, &lUpY);
        if (wRet != OK) {
            DEBUG_RETCODE("ERROR: ClickScope", wRet);
            continue;
        }
        cVKBD->HandleInterface();
    }
}

/**
 * HandleTouch
 * Function: get and handle touch information
 * 
 * @param   
 *       [OUT]long &lDownX -- X-axis's coordinate when down.
 *       [OUT]long &lDownY -- Y-axis's coordinate when down.
 *       [OUT]long &lUpX -- X-axis's coordinate when up.
 *       [OUT]long &lUpY -- Y-axis's coordinate when up.
 * 
 * @return 
 *          OK - successful
 *          others - refer to libVKBD.h
 * 
 * Auther: Tinker Han
 */
WORD CVKBD::HandleTouch(long &lDownX, long &lDownY, long &lUpX, long &lUpY) {
    BOOL bRet;
    bRet = TouchInit();
    if (!bRet) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "Touch Init fail");
        return ERROR_VKBD_TOUCH_INIT_FAIL;
    }

    int n = 0;
    while (1) {
        n++;
        bRet = TouchGetPosition(lDownX, lDownY, lUpX, lUpY);
        usleep(100);
        if (!bRet) {
            if (n >= 100) {
                break;
            } else {
                continue;
            }
        } else {
            if ((lDownX != 0) && (lDownY != 0) && (lUpX != 0) && (lUpY != 0))
                break;
        }
    }

    if (n >= 100) {
        TouchClose();
        return ERROR_VKBD_TOUCH_TIMEOUT;
    } else {
        DEBUG_INFO(DEBUGINFO_NORMAL, "----------------------------");
        DEBUG_INFO(DEBUGINFO_NORMAL, "lDownX is: %ld  lDownY is: %ld", lDownX, lDownY);
        DEBUG_INFO(DEBUGINFO_NORMAL, "lUpX   is: %ld  lUpY   is: %ld", lUpX, lUpY);
        DEBUG_INFO(DEBUGINFO_NORMAL, "----------------------------");
    }

    return OK;
}

/**
 * TouchInit
 * Function:  
 *      Initialize the Touch module.
 * 
 * @param 
 *          none.       
 * 
 * @return 
 *          TRUE - TouchInit success
 *         FALSE - TouchInit fail
 * 
 * @Modify Tinker Han
 */
BOOL CVKBD::TouchInit(void) {
    bTouchOK = FALSE;
    m_TouchDevHandle = open(TOUCH_DEVICE_NAME, O_RDONLY | O_NONBLOCK);
    if (m_TouchDevHandle < 0) {
        m_TouchDevHandle = INVALID_TOUCH_DEV_HANDLE;
        DEBUG_INFO(DEBUGINFO_NORMAL, "Touch Init NG");
        return bTouchOK;
    }

    bTouchOK = TRUE;
    return TRUE;
}

/**
 * TouchGetPosition
 * Function:  
 *      Get Touch Position from screen.
 * 
 * @param
 *       [OUT]long &lDownX -- X-axis's coordinate when down.
 *       [OUT]long &lDownY -- Y-axis's coordinate when down.
 *       [OUT]long &lUpX -- X-axis's coordinate when up.
 *       [OUT]long &lUpY -- Y-axis's coordinate when up.
 * 
 * @return 
 *          TRUE - Start the process successfully.
 *          Other values - Please see the <ErrorCode.h> for details.
 * 
 * @Modify Tinker Han
 */
BOOL CVKBD::TouchGetPosition(long &lDownX, long &lDownY, long &lUpX, long &lUpY) {
    struct input_absinfo absI;
    int nRet;
    struct input_event byData[TouchEventSize];

    nRet = read(m_TouchDevHandle, byData, sizeof (struct input_event)*TouchEventSize);
    if (nRet <= 0)
        return FALSE;

    for (int nItem = 0; nItem < nRet / sizeof (struct input_event); nItem++) {
        if (byData[nItem].type != EV_KEY)
            continue;

        if ((byData[nItem].code == BTN_TOUCH) & (byData[nItem].value == 1)) {
            ioctl(m_TouchDevHandle, EVIOCGABS(ABS_X), &absI);
            m_lPressX = absI.value;
            ioctl(m_TouchDevHandle, EVIOCGABS(ABS_Y), &absI);
            m_lPressY = absI.value;
            DEBUG_INFO(DEBUGINFO_NORMAL, "m_byPress = 1 EV_KEY, event = %s, value = %d", byData[nItem].code == BTN_TOUCH ? "BTN_TOUCH" : "Unkown", byData[nItem].value);
            return FALSE;
        }
        if ((byData[nItem].code == BTN_TOUCH) & (byData[nItem].value == 0)) {
            ioctl(m_TouchDevHandle, EVIOCGABS(ABS_X), &absI);
            lUpX = absI.value;
            ioctl(m_TouchDevHandle, EVIOCGABS(ABS_Y), &absI);
            lUpY = absI.value;

            lDownX = m_lPressX;
            lDownY = m_lPressY;
            DEBUG_INFO(DEBUGINFO_NORMAL, "m_byPress = 0 EV_KEY, event = %s, value = %d", byData[nItem].code == BTN_TOUCH ? "BTN_TOUCH" : "Unkown", byData[nItem].value);
            return TRUE;
        }
    }

    return FALSE;
}

/**
 * TouchInit
 * Function:  
 *      Close the Touch module.
 * 
 * @param 
 *          none.       
 * 
 * @return 
 *          none.
 * 
 * @Modify Tinker Han
 */
void CVKBD::TouchClose(void) {
    close(m_TouchDevHandle);
    m_TouchDevHandle = INVALID_TOUCH_DEV_HANDLE;
}

/**
 * ClickScope
 * Function: Detects whether the down coordinates and the up coordinates 
 *           are in the same Scope
 * 
 * @param   
 *       [OUT]long *lDownX -- X-axis's coordinate when down.
 *       [OUT]long *lDownY -- Y-axis's coordinate when down.
 *       [OUT]long *lUpX -- X-axis's coordinate when up.
 *       [OUT]long *lUpY -- Y-axis's coordinate when up.
 * 
 * @return 
 *          OK - successful
 *          others - refer to libVKBD.h
 * 
 * Auther: Tinker Han
 */
WORD CVKBD::ClickScope(long* lDownX, long* lDownY, long* lUpX, long* lUpY) {

    BYTE byDownScope = SCOPE_VOID;
    BYTE byUpScope = SCOPE_VOID;

    byDownScope = ScopeJudgment(*lDownX, *lDownY);
    byUpScope = ScopeJudgment(*lUpX, *lUpY);
    if (byDownScope != byUpScope) {
        m_byNowScope = SCOPE_VOID;
        DEBUG_INFO(DEBUGINFO_NORMAL, "The DOWN scope is different from the UP scope");
        return OK;
    } else {
        m_byNowScope = byDownScope;
    }

    return OK;
}

BYTE CVKBD::ScopeJudgment(long x, long y) {
    DEBUG_ENTRY();

    BYTE byRetScope = SCOPE_VOID;

    if (SCOPE_LN1_COL1(x, y))
        byRetScope = SCOPE_PARENT_1;
    else if (SCOPE_LN1_COL2(x, y))
        byRetScope = SCOPE_PARENT_2;
    else if (SCOPE_LN1_COL3(x, y))
        byRetScope = SCOPE_PARENT_3;
    else if (SCOPE_LN2_COL1(x, y))
        byRetScope = SCOPE_PARENT_4;
    else if (SCOPE_LN2_COL2(x, y))
        byRetScope = SCOPE_PARENT_5;
    else if (SCOPE_LN2_COL3(x, y))
        byRetScope = SCOPE_PARENT_6;
    else if (SCOPE_LN3_COL1(x, y))
        byRetScope = SCOPE_PARENT_7;
    else if (SCOPE_LN3_COL2(x, y))
        byRetScope = SCOPE_PARENT_8;
    else if (SCOPE_LN3_COL3(x, y))
        byRetScope = SCOPE_PARENT_9;
    else if (SCOPE_LN4_COL1(x, y))
        byRetScope = SCOPE_PARENT_SWITCH;
    else if (SCOPE_LN4_COL2(x, y))
        byRetScope = SCOPE_PARENT_0;
    else if (SCOPE_LN4_COL3(x, y))
        byRetScope = SCOPE_PARENT_CAP;
    else if (SCOPE_CANCEL(x, y))
        byRetScope = SCOPE_FUNC_CANCEL;
    else if (SCOPE_CLEAR(x, y))
        byRetScope = SCOPE_FUNC_CLEAR;
    else if (SCOPE_ENTER(x, y))
        byRetScope = SCOPE_FUNC_ENTER;
    else
        byRetScope = SCOPE_VOID;

    return DEBUG_EXIT(byRetScope);
}

USHORT CVKBD::HandleInterface() {
    DEBUG_ENTRY();

    USHORT usRet = 0;

    switch (m_byNowScope) {
        case SCOPE_PARENT_SWITCH:
            usRet = HandleSwitchButton();
            break;

        case SCOPE_PARENT_1:
        case SCOPE_PARENT_2:
        case SCOPE_PARENT_3:
        case SCOPE_PARENT_4:
        case SCOPE_PARENT_5:
        case SCOPE_PARENT_6:
        case SCOPE_PARENT_7:
        case SCOPE_PARENT_8:
        case SCOPE_PARENT_9:
            usRet = HandleOneToNineButton();
            break;

        case SCOPE_PARENT_0:
            usRet = HandlePARENTZeroButton();
            break;

        case SCOPE_PARENT_CAP:
            usRet = HandlePARENTCAPButton();
            break;

        case SCOPE_FUNC_CANCEL:
            usRet = HandleCancelButton();
            break;

        case SCOPE_FUNC_CLEAR:
            usRet = HandleClearButton();
            break;

        case SCOPE_FUNC_ENTER:
            usRet = HandleEnterButton();
            break;

        default:
            return FAILED;
    }

    if (usRet != OK)
        return FAILED;

    return DEBUG_EXIT(OK);
}

USHORT CVKBD::HandleSwitchButton() {
    DEBUG_ENTRY();
    m_cBtRow4Column1.ClickButton();

    USHORT usRet = 0;

    if (m_enMode == VKBD_MODE_NUMBER) {
        m_enMode = VKBD_MODE_LETTER;
        usRet = VKBDSetButtonCaption();
        if (usRet != OK)
            return DEBUG_RETCODE("Fail to HandleSwitchButton", usRet);

        usRet = VKBDShowInterface();
        if (usRet != OK)
            return DEBUG_RETCODE("Fail to HandleSwitchButton", usRet);
    } else if (m_enMode == VKBD_MODE_LETTER) {
        m_enMode = VKBD_MODE_SPECIAL_CHARACTER;
        usRet = VKBDSetButtonCaption();
        if (usRet != OK)
            return DEBUG_RETCODE("Fail to HandleSwitchButton", usRet);

        usRet = VKBDShowInterface();
        if (usRet != OK)
            return DEBUG_RETCODE("Fail to HandleSwitchButton", usRet);
    } else if (m_enMode == VKBD_MODE_CAP_LETTER) {
        m_enMode = VKBD_MODE_SPECIAL_CHARACTER;
        usRet = VKBDSetButtonCaption();
        if (usRet != OK)
            return DEBUG_RETCODE("Fail to HandleSwitchButton", usRet);

        usRet = VKBDShowInterface();
        if (usRet != OK)
            return DEBUG_RETCODE("Fail to HandleSwitchButton", usRet);
    } else if (m_enMode == VKBD_MODE_SPECIAL_CHARACTER) {
        m_enMode = VKBD_MODE_NUMBER;
        usRet = VKBDSetButtonCaption();
        if (usRet != OK)
            return DEBUG_RETCODE("Fail to HandleSwitchButton", usRet);

        usRet = VKBDShowInterface();
        if (usRet != OK)
            return DEBUG_RETCODE("Fail to HandleSwitchButton", usRet);
    }

    if (m_byKeyChooseOneValue != d_KBD_INVALID) {
        m_cDisplayColumn << m_byKeyChooseOneValue;
        m_usDisplayColumnLen += 1;
    } else if (m_byKeyChooseTwoValue != d_KBD_INVALID) {
        m_cDisplayColumn << m_byKeyChooseTwoValue;
        m_usDisplayColumnLen += 1;
    } else if (m_byKeyChooseThreeValue != d_KBD_INVALID) {
        m_cDisplayColumn << m_byKeyChooseThreeValue;
        m_usDisplayColumnLen += 1;
    }

    m_byKeyChooseOneValue = d_KBD_INVALID;
    m_byKeyChooseTwoValue = d_KBD_INVALID;
    m_byKeyChooseThreeValue = d_KBD_INVALID;
    m_byLastScope = SCOPE_VOID;
    m_byNowScope = SCOPE_VOID;

    return DEBUG_EXIT(OK);
}

USHORT CVKBD::HandleOneToNineButton() {
    DEBUG_ENTRY();

    CByteStream cCaption;
    USHORT usDataLen = 0;

    switch (m_byNowScope) {
        case SCOPE_PARENT_1:
            m_cBtRow1Column1.ClickButton();
            m_cBtRow1Column1.SendButtonCaption(cCaption, &usDataLen);
            break;
        case SCOPE_PARENT_2:
            m_cBtRow1Column2.ClickButton();
            m_cBtRow1Column2.SendButtonCaption(cCaption, &usDataLen);
            break;
        case SCOPE_PARENT_3:
            m_cBtRow1Column3.ClickButton();
            m_cBtRow1Column3.SendButtonCaption(cCaption, &usDataLen);
            break;
        case SCOPE_PARENT_4:
            m_cBtRow2Column1.ClickButton();
            m_cBtRow2Column1.SendButtonCaption(cCaption, &usDataLen);
            break;
        case SCOPE_PARENT_5:
            m_cBtRow2Column2.ClickButton();
            m_cBtRow2Column2.SendButtonCaption(cCaption, &usDataLen);
            break;
        case SCOPE_PARENT_6:
            m_cBtRow2Column3.ClickButton();
            m_cBtRow2Column3.SendButtonCaption(cCaption, &usDataLen);
            break;
        case SCOPE_PARENT_7:
            m_cBtRow3Column1.ClickButton();
            m_cBtRow3Column1.SendButtonCaption(cCaption, &usDataLen);
            break;
        case SCOPE_PARENT_8:
            m_cBtRow3Column2.ClickButton();
            m_cBtRow3Column2.SendButtonCaption(cCaption, &usDataLen);
            break;
        case SCOPE_PARENT_9:
            m_cBtRow3Column3.ClickButton();
            m_cBtRow3Column3.SendButtonCaption(cCaption, &usDataLen);
            break;
        default:
            return FAILED;
    }
    DEBUG_INFO(1, " data:%s -- Len:%d", cCaption.GetBuffer(), usDataLen);
    if (usDataLen == 1) {
        m_cDisplayColumn.Write(cCaption.GetBuffer(), 1);
        m_usDisplayColumnLen += 1;
        m_byNowScope = SCOPE_VOID;
        m_byLastScope = SCOPE_VOID;
        DEBUG_INFO(1, " data:%s -- Len:%d", m_cDisplayColumn.GetBuffer(), m_usDisplayColumnLen);
    } else if (usDataLen == 2) {
        if (m_byNowScope == m_byLastScope) {
            if (m_byKeyChooseOneValue != d_KBD_INVALID) {
                m_byKeyChooseTwoValue = *cCaption.GetBuffer(1);
                m_byKeyChooseOneValue = d_KBD_INVALID;
            } else if (m_byKeyChooseTwoValue != d_KBD_INVALID) {
                m_byKeyChooseOneValue = *cCaption.GetBuffer(0);
                m_byKeyChooseTwoValue = d_KBD_INVALID;
            } else {
                m_byKeyChooseOneValue = *cCaption.GetBuffer(0);
                m_byLastScope = m_byNowScope;
            }
        } else {
            EnsureButtonCaption();
            m_byKeyChooseOneValue = d_KBD_INVALID;
            m_byKeyChooseTwoValue = d_KBD_INVALID;
            m_byKeyChooseOneValue = *cCaption.GetBuffer(0);
            m_byLastScope = m_byNowScope;
        }
    } else if (usDataLen == 3) {
        if (m_byNowScope == m_byLastScope) {
            if (m_byKeyChooseOneValue != d_KBD_INVALID) {
                m_byKeyChooseTwoValue = *cCaption.GetBuffer(1);
                m_byKeyChooseOneValue = d_KBD_INVALID;
                m_byKeyChooseThreeValue = d_KBD_INVALID;
            } else if (m_byKeyChooseTwoValue != d_KBD_INVALID) {
                m_byKeyChooseThreeValue = *cCaption.GetBuffer(2);
                m_byKeyChooseTwoValue = d_KBD_INVALID;
                m_byKeyChooseOneValue = d_KBD_INVALID;
            } else if (m_byKeyChooseThreeValue != d_KBD_INVALID) {
                m_byKeyChooseOneValue = *cCaption.GetBuffer(0);
                m_byKeyChooseTwoValue = d_KBD_INVALID;
                m_byKeyChooseThreeValue = d_KBD_INVALID;
            } else {
                m_byKeyChooseOneValue = *cCaption.GetBuffer(0);
            }
            m_byLastScope = m_byNowScope;
        } else {
            EnsureButtonCaption();
            m_byKeyChooseOneValue = d_KBD_INVALID;
            m_byKeyChooseTwoValue = d_KBD_INVALID;
            m_byKeyChooseThreeValue = d_KBD_INVALID;
            m_byKeyChooseOneValue = *cCaption.GetBuffer(0);
            m_byLastScope = m_byNowScope;
        }
    }

    m_ulTime = GetSysTime();
    return DEBUG_EXIT(OK);
}

USHORT CVKBD::HandlePARENTZeroButton() {
    DEBUG_ENTRY();

    BYTE byCaption;
    USHORT usCaptionLen = 0;
    CByteStream cCaption;

    if (m_enMode == VKBD_MODE_NUMBER) {
        EnsureButtonCaption();
        m_cDisplayColumn << '0';
        m_usDisplayColumnLen += 1;
        m_byNowScope = SCOPE_VOID;
        m_byLastScope = SCOPE_VOID;
        m_byKeyChooseOneValue = d_KBD_INVALID;
        m_byKeyChooseTwoValue = d_KBD_INVALID;
        m_byKeyChooseThreeValue = d_KBD_INVALID;
    } else if (m_enMode == VKBD_MODE_LETTER) {
        EnsureButtonCaption();
        m_byKeyChooseOneValue = d_KBD_INVALID;
        m_byKeyChooseTwoValue = d_KBD_INVALID;
        m_byKeyChooseThreeValue = d_KBD_INVALID;
        m_byKeyChooseOneValue = ' ';
        m_byNowScope = SCOPE_VOID;
        m_byLastScope = SCOPE_VOID;
    } else if (m_enMode == VKBD_MODE_CAP_LETTER) {
        EnsureButtonCaption();
        m_byKeyChooseOneValue = d_KBD_INVALID;
        m_byKeyChooseTwoValue = d_KBD_INVALID;
        m_byKeyChooseThreeValue = d_KBD_INVALID;
        m_byKeyChooseOneValue = ' ';
        m_byNowScope = SCOPE_VOID;
        m_byLastScope = SCOPE_VOID;
    } else if (m_enMode == VKBD_MODE_SPECIAL_CHARACTER) {
        m_cBtRow4Column2.SendButtonCaption(cCaption, &usCaptionLen);
        if (m_byNowScope == m_byLastScope) {
            if (m_byKeyChooseOneValue != d_KBD_INVALID) {
                m_byKeyChooseTwoValue = *cCaption.GetBuffer(1);
                m_byKeyChooseOneValue = d_KBD_INVALID;
            } else if (m_byKeyChooseTwoValue != d_KBD_INVALID) {
                m_byKeyChooseOneValue = *cCaption.GetBuffer(0);
                m_byKeyChooseTwoValue = d_KBD_INVALID;
            } else {
                m_byKeyChooseOneValue = *cCaption.GetBuffer(0);
                m_byLastScope = m_byNowScope;
            }
        } else {
            EnsureButtonCaption();
            m_byKeyChooseOneValue = d_KBD_INVALID;
            m_byKeyChooseTwoValue = d_KBD_INVALID;
            m_byKeyChooseOneValue = *cCaption.GetBuffer(0);
            m_byLastScope = m_byNowScope;
        }
    }
    m_ulTime = GetSysTime();

    return DEBUG_EXIT(OK);
}

USHORT CVKBD::HandlePARENTCAPButton() {
    DEBUG_ENTRY();
    USHORT usRet = 0;
    USHORT usCaptionLen;
    CByteStream cCaption;

    if (m_enMode == VKBD_MODE_NUMBER) {
        EnsureButtonCaption();
        m_cDisplayColumn << '.';
        m_usDisplayColumnLen += 1;
        m_byNowScope = SCOPE_VOID;
        m_byLastScope = SCOPE_VOID;
        m_byKeyChooseOneValue = d_KBD_INVALID;
        m_byKeyChooseTwoValue = d_KBD_INVALID;
        m_byKeyChooseThreeValue = d_KBD_INVALID;
    } else if (m_enMode == VKBD_MODE_LETTER) {
        EnsureButtonCaption();
        m_byKeyChooseOneValue = d_KBD_INVALID;
        m_byKeyChooseTwoValue = d_KBD_INVALID;
        m_byKeyChooseThreeValue = d_KBD_INVALID;
        m_enMode = VKBD_MODE_CAP_LETTER;

        usRet = VKBDSetButtonCaption();
        if (usRet != OK)
            return DEBUG_RETCODE("Fail to HandleSwitchButton", usRet);

        usRet = VKBDShowInterface();
        if (usRet != OK)
            return DEBUG_RETCODE("Fail to HandleSwitchButton", usRet);
    } else if (m_enMode == VKBD_MODE_CAP_LETTER) {
        EnsureButtonCaption();
        m_byKeyChooseOneValue = d_KBD_INVALID;
        m_byKeyChooseTwoValue = d_KBD_INVALID;
        m_byKeyChooseThreeValue = d_KBD_INVALID;
        m_enMode = VKBD_MODE_LETTER;

        usRet = VKBDSetButtonCaption();
        if (usRet != OK)
            return DEBUG_RETCODE("Fail to HandleSwitchButton", usRet);

        usRet = VKBDShowInterface();
        if (usRet != OK)
            return DEBUG_RETCODE("Fail to HandleSwitchButton", usRet);
    } else if (m_enMode == VKBD_MODE_SPECIAL_CHARACTER) {
        m_cBtRow4Column3.SendButtonCaption(cCaption, &usCaptionLen);
        if (m_byNowScope == m_byLastScope) {
            if (m_byKeyChooseOneValue != d_KBD_INVALID) {
                m_byKeyChooseTwoValue = *cCaption.GetBuffer(1);
                m_byKeyChooseOneValue = d_KBD_INVALID;
                m_byKeyChooseThreeValue = d_KBD_INVALID;
            } else if (m_byKeyChooseTwoValue != d_KBD_INVALID) {
                m_byKeyChooseThreeValue = *cCaption.GetBuffer(2);
                m_byKeyChooseTwoValue = d_KBD_INVALID;
                m_byKeyChooseOneValue = d_KBD_INVALID;
            } else if (m_byKeyChooseThreeValue != d_KBD_INVALID) {
                m_byKeyChooseOneValue = *cCaption.GetBuffer(0);
                m_byKeyChooseTwoValue = d_KBD_INVALID;
                m_byKeyChooseThreeValue = d_KBD_INVALID;
            } else {
                m_byKeyChooseOneValue = *cCaption.GetBuffer(0);
            }
            m_byLastScope = m_byNowScope;
        } else {
            EnsureButtonCaption();
            m_byKeyChooseOneValue = d_KBD_INVALID;
            m_byKeyChooseTwoValue = d_KBD_INVALID;
            m_byKeyChooseThreeValue = d_KBD_INVALID;

            m_byKeyChooseOneValue = *cCaption.GetBuffer(0);
            m_byLastScope = m_byNowScope;
        }
    }
    m_ulTime = GetSysTime();

    return DEBUG_EXIT(OK);
}

USHORT CVKBD::HandleCancelButton() {
    DEBUG_ENTRY();

    USHORT usRet = 0;

    ClickCancelButton();
    usRet = VKBDHideInterface();
    if (usRet != OK)
        return FAILED;

    pthread_mutex_lock(&s_cMutex);
    m_byKeyBuf = d_KBD_CANCEL;
    pthread_mutex_unlock(&s_cMutex);

    m_bIsShow = FALSE;
    m_bIsShowDisplay = FALSE;
    m_enMode = VKBD_MODE_NUMBER;
    m_lPressX = 0;
    m_lPressY = 0;
    m_lUpX = 0;
    m_lUpY = 0;
    m_byNowScope = SCOPE_VOID;
    m_byLastScope = SCOPE_VOID;
    m_ulTime = 0;
    m_byKeyChooseOneValue = d_KBD_INVALID;
    m_byKeyChooseTwoValue = d_KBD_INVALID;
    m_byKeyChooseThreeValue = d_KBD_INVALID;
    m_usDisplayColumnLen = 0;
    m_cDisplayColumn.Empty();

    DEBUG_EXIT(OK);
}

USHORT CVKBD::HandleClearButton() {
    DEBUG_ENTRY();
    ClickClearButton();

    BYTE byPush;
    BYTE byBuf[2];
    USHORT usXCoordinate;

    byBuf[0] = ' ';
    byBuf[1] = '\0';
    usXCoordinate = 5 + (m_usDisplayColumnLen - 1) * 16;
    CTOS_LCDBackGndColor(BLUE_COLOR);
    CTOS_LCDForeGndColor(BLACK_COLOR);

    if (m_byKeyChooseOneValue != d_KBD_INVALID) {
        CTOS_LCDGTextOut(usXCoordinate + 16, 245, (BYTE*) byBuf, d_FONT_16x30, d_FALSE);
        m_byKeyChooseOneValue = d_KBD_INVALID;
    } else if (m_byKeyChooseTwoValue != d_KBD_INVALID) {
        CTOS_LCDGTextOut(usXCoordinate + 16, 245, (BYTE*) byBuf, d_FONT_16x30, d_FALSE);
        m_byKeyChooseTwoValue = d_KBD_INVALID;
    } else if (m_byKeyChooseThreeValue != d_KBD_INVALID) {
        CTOS_LCDGTextOut(usXCoordinate + 16, 245, (BYTE*) byBuf, d_FONT_16x30, d_FALSE);
        m_byKeyChooseThreeValue = d_KBD_INVALID;
    } else if (m_cDisplayColumn.GetLength() > 0) {
        CTOS_LCDGTextOut(usXCoordinate, 245, (BYTE*) byBuf, d_FONT_16x30, d_FALSE);
        m_cDisplayColumn >> &byPush;
        m_usDisplayColumnLen--;
    }

    DEBUG_INFO(1, "Display Column:%s", m_cDisplayColumn.GetBuffer());
    pthread_mutex_lock(&s_cMutex);
    m_byKeyBuf = d_KBD_CLEAR;
    pthread_mutex_unlock(&s_cMutex);

    DEBUG_EXIT(OK);
}

USHORT CVKBD::HandleEnterButton() {
    DEBUG_ENTRY();

    ClickOKButton();
    EnsureButtonCaption();

    m_cExport.Empty();
    m_byKeyChooseOneValue = d_KBD_INVALID;
    m_byKeyChooseTwoValue = d_KBD_INVALID;
    m_byKeyChooseThreeValue = d_KBD_INVALID;
    m_cExport = m_cDisplayColumn;
    m_cDisplayColumn.Empty();
    m_usDisplayColumnLen = 0;

    CTOS_LCDBackGndColor(BLUE_COLOR);
    CTOS_LCDForeGndColor(BLACK_COLOR);
    CTOS_LCDGTextOut(5, 245, (BYTE*) "                                  ", d_FONT_16x30, d_FALSE);

    pthread_mutex_lock(&s_cMutex);
    m_byKeyBuf = d_KBD_ENTER;
    pthread_mutex_unlock(&s_cMutex);

    DEBUG_EXIT(OK);
}

USHORT CVKBD::EnsureButtonCaption() {
    DEBUG_ENTRY();

    if (m_byKeyChooseOneValue != d_KBD_INVALID) {
        m_cDisplayColumn << m_byKeyChooseOneValue;
        m_usDisplayColumnLen += 1;
    } else if (m_byKeyChooseTwoValue != d_KBD_INVALID) {
        m_cDisplayColumn << m_byKeyChooseTwoValue;
        m_usDisplayColumnLen += 1;
    } else if (m_byKeyChooseThreeValue != d_KBD_INVALID) {
        m_cDisplayColumn << m_byKeyChooseThreeValue;
        m_usDisplayColumnLen += 1;
    }

    return DEBUG_EXIT(OK);
}

/**
 * VKBDSetSound
 * Function: turn on or turn off virtual keyboard sound
 * 
 * @param 
 *          [IN] bOnOff - TRUE: turn on sound
 *                        FALSE: turn off sound
 *  
 * @return 
 *          OK - successful
 *          others - failed
 * 
 * Auther: Tinker Han
 */
WORD CVKBD::VKBDSetSound(BOOL bOnOff) {
    DEBUG_ENTRY();

    if (bOnOff)//turn on
        m_bBeepFlag = TRUE;
    else//turn off
        m_bBeepFlag = FALSE;

    return DEBUG_EXIT(OK);
}

void CVKBD::ClickCancelButton() {
    CTOS_LCDGShowPicEx(d_LCD_SHOWPIC_RGB, 241, 281, (BYTE *) by_PRESS_CANCEL_DARK, sizeof (by_PRESS_CANCEL_DARK), 79);
    usleep(80000);
    CTOS_LCDGShowPicEx(d_LCD_SHOWPIC_RGB, 241, 281, (BYTE *) by_PRESS_CANCEL_BRIGHT, sizeof (by_PRESS_CANCEL_BRIGHT), 79);
}

void CVKBD::ClickClearButton() {
    CTOS_LCDGShowPicEx(d_LCD_SHOWPIC_RGB, 241, 331, (BYTE *) by_PRESS_CLEAR_DARK, sizeof (by_PRESS_CLEAR_DARK), 79);
    usleep(80000);
    CTOS_LCDGShowPicEx(d_LCD_SHOWPIC_RGB, 241, 331, (BYTE *) by_PRESS_CLEAR_BRIGHT, sizeof (by_PRESS_CLEAR_BRIGHT), 79);
}

void CVKBD::ClickOKButton() {
    CTOS_LCDGShowPicEx(d_LCD_SHOWPIC_RGB, 241, 381, (BYTE *) by_PRESS_OK_DARK, sizeof (by_PRESS_OK_DARK), 78);
    usleep(80000);
    CTOS_LCDGShowPicEx(d_LCD_SHOWPIC_RGB, 241, 381, (BYTE *) by_PRESS_OK_BRIGHT, sizeof (by_PRESS_OK_BRIGHT), 78);
}

USHORT CVKBD::VKBDShowDisplayColumnLen() {
    DEBUG_ENTRY();

    BYTE byPushZero;
    BYTE byBuf[2];
    USHORT usLen = 0;

    CByteStream cShowBuf;
    cShowBuf.Empty();

    if ((GetSysTime() - m_ulTime) > CHOOSE_CAPTION_TIMEOUT) {
        if (m_byKeyChooseOneValue != d_KBD_INVALID) {
            m_cDisplayColumn << m_byKeyChooseOneValue;
            m_byKeyChooseOneValue = d_KBD_INVALID;
            m_usDisplayColumnLen += 1;
        } else if (m_byKeyChooseTwoValue != d_KBD_INVALID) {
            m_cDisplayColumn << m_byKeyChooseTwoValue;
            m_byKeyChooseTwoValue = d_KBD_INVALID;
            m_usDisplayColumnLen += 1;
        } else if (m_byKeyChooseThreeValue != d_KBD_INVALID) {
            m_cDisplayColumn << m_byKeyChooseThreeValue;
            m_byKeyChooseThreeValue = d_KBD_INVALID;
            m_usDisplayColumnLen += 1;
        }

        if (m_usDisplayColumnLen > 0) {
            if (m_cDisplayColumn.GetLength() >= DisplayColumn_MAXLEN) {
                usLen = m_cDisplayColumn.GetLength() - DisplayColumn_MAXLEN;
                cShowBuf.Write(m_cDisplayColumn.GetBuffer(usLen), DisplayColumn_MAXLEN);
            } else {
                cShowBuf = m_cDisplayColumn;
            }
            CTOS_LCDBackGndColor(BLUE_COLOR);
            CTOS_LCDForeGndColor(BLACK_COLOR);
            CTOS_LCDGTextOut(5, 245, (BYTE*) cShowBuf.PushZero(), d_FONT_16x30, d_FALSE);
            DEBUG_INFO(1, "Show Buff:%s", cShowBuf.GetBuffer());
        }
        m_ulTime = GetSysTime();
    } else {
        if (m_usDisplayColumnLen > 0) {
            if ((m_byKeyChooseOneValue != d_KBD_INVALID || m_byKeyChooseTwoValue != d_KBD_INVALID ||
                    m_byKeyChooseThreeValue != d_KBD_INVALID) && (m_cDisplayColumn.GetLength() >= DisplayColumn_MAXLEN)) {
                usLen = m_cDisplayColumn.GetLength() - DisplayColumn_MAXLEN + 1;
                cShowBuf.Write(m_cDisplayColumn.GetBuffer(usLen), DisplayColumn_MAXLEN - 1);
                usLen = DisplayColumn_MAXLEN - 1;
            } else if (m_cDisplayColumn.GetLength() >= DisplayColumn_MAXLEN) {
                usLen = m_cDisplayColumn.GetLength() - DisplayColumn_MAXLEN;
                cShowBuf.Write(m_cDisplayColumn.GetBuffer(usLen), DisplayColumn_MAXLEN);
                usLen = DisplayColumn_MAXLEN;
            } else {
                usLen = m_cDisplayColumn.GetLength();
                cShowBuf = m_cDisplayColumn;
            }
            CTOS_LCDBackGndColor(BLUE_COLOR);
            CTOS_LCDForeGndColor(BLACK_COLOR);
            CTOS_LCDGTextOut(5, 245, (BYTE*) cShowBuf.PushZero(), d_FONT_16x30, d_FALSE);
            cShowBuf>>&byPushZero;
            DEBUG_INFO(1, "Show Buff:%s", cShowBuf.GetBuffer());

            CTOS_LCDBackGndColor(GREEN_COLOR);
            CTOS_LCDForeGndColor(BLACK_COLOR);
            if (m_byKeyChooseOneValue != d_KBD_INVALID) {
                byBuf[0] = m_byKeyChooseOneValue;
                byBuf[1] = '\0';
                CTOS_LCDGTextOut((usLen * 16) + 5, 245, byBuf, d_FONT_16x30, d_FALSE);
            } else if (m_byKeyChooseTwoValue != d_KBD_INVALID) {
                byBuf[0] = m_byKeyChooseTwoValue;
                byBuf[1] = '\0';
                CTOS_LCDGTextOut((usLen * 16) + 5, 245, byBuf, d_FONT_16x30, d_FALSE);
            } else if (m_byKeyChooseThreeValue != d_KBD_INVALID) {
                byBuf[0] = m_byKeyChooseThreeValue;
                byBuf[1] = '\0';
                CTOS_LCDGTextOut((usLen * 16) + 5, 245, byBuf, d_FONT_16x30, d_FALSE);
            }
        } else if (m_usDisplayColumnLen == 0) {
            CTOS_LCDBackGndColor(GREEN_COLOR);
            CTOS_LCDForeGndColor(BLACK_COLOR);
            if (m_byKeyChooseOneValue != d_KBD_INVALID) {
                byBuf[0] = m_byKeyChooseOneValue;
                byBuf[1] = '\0';
                CTOS_LCDGTextOut(5, 245, byBuf, d_FONT_16x30, d_FALSE);
            } else if (m_byKeyChooseTwoValue != d_KBD_INVALID) {
                byBuf[0] = m_byKeyChooseTwoValue;
                byBuf[1] = '\0';
                CTOS_LCDGTextOut(5, 245, byBuf, d_FONT_16x30, d_FALSE);
            } else if (m_byKeyChooseThreeValue != d_KBD_INVALID) {
                byBuf[0] = m_byKeyChooseThreeValue;
                byBuf[1] = '\0';
                CTOS_LCDGTextOut(5, 245, byBuf, d_FONT_16x30, d_FALSE);
            }
        }
    }

    if (m_usJudgeDsiplayColumnLen < m_usDisplayColumnLen) {
        VKBDGetKeyBuf();
    }
    m_usJudgeDsiplayColumnLen = m_usDisplayColumnLen;
    return DEBUG_EXIT(OK);
}

USHORT CVKBD::VKBDGetKeyBuf() {
    DEBUG_ENTRY();

    BYTE byKeyValue;
    byKeyValue = *m_cDisplayColumn.GetBuffer(m_usJudgeDsiplayColumnLen);
    DEBUG_INFO(1, "keybuf:%c", byKeyValue);

    if (m_enMode == VKBD_MODE_NUMBER) {
        switch (byKeyValue) {
            case '0':
                byKeyValue = d_KBD_0;
                break;
            case '1':
                byKeyValue = d_KBD_1;
                break;
            case '2':
                byKeyValue = d_KBD_2;
                break;
            case '3':
                byKeyValue = d_KBD_3;
                break;
            case '4':
                byKeyValue = d_KBD_4;
                break;
            case '5':
                byKeyValue = d_KBD_5;
                break;
            case '6':
                byKeyValue = d_KBD_6;
                break;
            case '7':
                byKeyValue = d_KBD_7;
                break;
            case '8':
                byKeyValue = d_KBD_8;
                break;
            case '9':
                byKeyValue = d_KBD_9;
                break;
            case '.':
                byKeyValue = d_KBD_PERIOD;
                break;
            default:
                break;
        }
    } else if (m_enMode == VKBD_MODE_LETTER) {
        switch (byKeyValue) {
            case 'q':
                byKeyValue = d_KBD_q;
                break;
            case 'w':
                byKeyValue = d_KBD_w;
                break;
            case 'e':
                byKeyValue = d_KBD_e;
                break;
            case 'r':
                byKeyValue = d_KBD_r;
                break;
            case 't':
                byKeyValue = d_KBD_t;
                break;
            case 'y':
                byKeyValue = d_KBD_y;
                break;
            case 'u':
                byKeyValue = d_KBD_u;
                break;
            case 'i':
                byKeyValue = d_KBD_i;
                break;
            case 'o':
                byKeyValue = d_KBD_o;
                break;
            case 'p':
                byKeyValue = d_KBD_p;
                break;
            case 'a':
                byKeyValue = d_KBD_a;
                break;
            case 's':
                byKeyValue = d_KBD_s;
                break;
            case 'd':
                byKeyValue = d_KBD_d;
                break;
            case 'f':
                byKeyValue = d_KBD_f;
                break;
            case 'g':
                byKeyValue = d_KBD_g;
                break;
            case 'h':
                byKeyValue = d_KBD_h;
                break;
            case 'j':
                byKeyValue = d_KBD_j;
                break;
            case 'k':
                byKeyValue = d_KBD_k;
                break;
            case 'l':
                byKeyValue = d_KBD_l;
                break;
            case 'z':
                byKeyValue = d_KBD_z;
                break;
            case 'x':
                byKeyValue = d_KBD_x;
                break;
            case 'c':
                byKeyValue = d_KBD_c;
                break;
            case 'v':
                byKeyValue = d_KBD_v;
                break;
            case 'b':
                byKeyValue = d_KBD_b;
                break;
            case 'n':
                byKeyValue = d_KBD_n;
                break;
            case 'm':
                byKeyValue = d_KBD_m;
                break;
            case ' ':
                byKeyValue = d_KBD_SPACE;
                break;
            default:
                break;
        }
    } else if (m_enMode == VKBD_MODE_CAP_LETTER) {
        switch (byKeyValue) {
            case 'Q':
                byKeyValue = d_KBD_Q;
                break;
            case 'W':
                byKeyValue = d_KBD_W;
                break;
            case 'E':
                byKeyValue = d_KBD_E;
                break;
            case 'R':
                byKeyValue = d_KBD_R;
                break;
            case 'T':
                byKeyValue = d_KBD_T;
                break;
            case 'Y':
                byKeyValue = d_KBD_Y;
                break;
            case 'U':
                byKeyValue = d_KBD_U;
                break;
            case 'I':
                byKeyValue = d_KBD_I;
                break;
            case 'O':
                byKeyValue = d_KBD_O;
                break;
            case 'P':
                byKeyValue = d_KBD_P;
                break;
            case 'A':
                byKeyValue = d_KBD_A;
                break;
            case 'S':
                byKeyValue = d_KBD_S;
                break;
            case 'D':
                byKeyValue = d_KBD_D;
                break;
            case 'F':
                byKeyValue = d_KBD_F;
                break;
            case 'G':
                byKeyValue = d_KBD_G;
                break;
            case 'H':
                byKeyValue = d_KBD_H;
                break;
            case 'J':
                byKeyValue = d_KBD_J;
                break;
            case 'K':
                byKeyValue = d_KBD_K;
                break;
            case 'L':
                byKeyValue = d_KBD_L;
                break;
            case 'Z':
                byKeyValue = d_KBD_Z;
                break;
            case 'X':
                byKeyValue = d_KBD_X;
                break;
            case 'C':
                byKeyValue = d_KBD_C;
                break;
            case 'V':
                byKeyValue = d_KBD_V;
                break;
            case 'B':
                byKeyValue = d_KBD_B;
                break;
            case 'N':
                byKeyValue = d_KBD_N;
                break;
            case 'M':
                byKeyValue = d_KBD_M;
                break;
            case ' ':
                byKeyValue = d_KBD_SPACE;
                break;
            default:
                break;
        }
    } else if (m_enMode == VKBD_MODE_SPECIAL_CHARACTER) {
        switch (byKeyValue) {
            case '~':
                byKeyValue = d_KBD_TILDE;
                break;
            case '!':
                byKeyValue = d_KBD_EXCLAMATION;
                break;
            case '@':
                byKeyValue = d_KBD_AT;
                break;
            case '#':
                byKeyValue = d_KBD_POUND;
                break;
            case '$':
                byKeyValue = d_KBD_DOLLAR;
                break;
            case '%':
                byKeyValue = d_KBD_PER;
                break;
            case '^':
                byKeyValue = d_KBD_CARET;
                break;
            case '&':
                byKeyValue = d_KBD_AMPERSAND;
                break;
            case '*':
                byKeyValue = d_KBD_STAR;
                break;
            case '(':
                byKeyValue = d_KBD_OPEN_PAREN;
                break;
            case ')':
                byKeyValue = d_KBD_CLOSE_PAREN;
                break;
            case '[':
                byKeyValue = d_KBD_OPEN_BRACKET;
                break;
            case ']':
                byKeyValue = d_KBD_CLOSE_BRACKET;
                break;
            case '{':
                byKeyValue = d_KBD_OPEN_BRACE;
                break;
            case '}':
                byKeyValue = d_KBD_CLOSE_BRACE;
                break;
            case '+':
                byKeyValue = d_KBD_PLUS;
                break;
            case '-':
                byKeyValue = d_KBD_MINUS;
                break;
            case '=':
                byKeyValue = d_KBD_EQUAL;
                break;
            case '_':
                byKeyValue = d_KBD_UNDERLINE;
                break;
            case '|':
                byKeyValue = d_KBD_VERTICAL_BAR;
                break;
            case '\\':
                byKeyValue = d_KBD_BACKSLASH;
                break;
            case '"':
                byKeyValue = d_KBD_DOUBLE_QUOTATION;
                break;
            case '\'':
                byKeyValue = d_KBD_QUOTATION;
                break;
            case '`':
                byKeyValue = d_KBD_APOSTROPHE;
                break;
            case ':':
                byKeyValue = d_KBD_COLON;
                break;
            case ';':
                byKeyValue = d_KBD_SEMICOLON;
                break;
            case '?':
                byKeyValue = d_KBD_QUESTION;
                break;
            case '<':
                byKeyValue = d_KBD_LESS_THAN;
                break;
            case '>':
                byKeyValue = d_KBD_GREATER_THAN;
                break;
            case '.':
                byKeyValue = d_KBD_PERIOD;
                break;
            case '/':
                byKeyValue = d_KBD_SLASH;
                break;
            case ',':
                byKeyValue = d_KBD_COMMA;
                break;
            default:
                break;
        }
    }

    pthread_mutex_lock(&s_cMutex);
    m_byKeyBuf = byKeyValue;
    DEBUG_INFO(DEBUGINFO_NORMAL, "keybuf is %x", m_byKeyBuf);
    pthread_mutex_unlock(&s_cMutex);

    return DEBUG_EXIT(OK);
}

USHORT CVKBD::VKBDGet(BYTE* pbyKey) {
    if (pbyKey == NULL) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "The Param is NULL");
        return ERROR_VKBD_PARAM_NULL;
    }

    BOOL bAlive = IsThreadAlive(m_VKBDThreadID);
    if (!bAlive) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "Thread is not alive");
        return ERROR_VKBD_THREAD_DEAD;
    }

    if (!m_bIsShow) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "UI is not showed");
        return ERROR_VKBD_WITHOUT_UI;
    }

    pthread_mutex_lock(&s_cMutex);
    m_byKeyBuf = d_KBD_INVALID;
    pthread_mutex_unlock(&s_cMutex);

    while (1) {
        pthread_mutex_lock(&s_cMutex);
        if (m_byKeyBuf != d_KBD_INVALID)//detected key in keybuf
            break;

        pthread_mutex_unlock(&s_cMutex);
        usleep(200000);
    }
    *pbyKey = m_byKeyBuf;
    m_byKeyBuf = d_KBD_INVALID;
    pthread_mutex_unlock(&s_cMutex);

    return OK;
}

USHORT CVKBD::VKBDBufFlush() {
    DEBUG_ENTRY();

    pthread_mutex_lock(&s_cMutex);
    m_byKeyBuf = d_KBD_INVALID;
    pthread_mutex_unlock(&s_cMutex);

    return DEBUG_EXIT(OK);
}

USHORT CVKBD::VKBDHit(BYTE* pbyKey) {
    if (pbyKey == NULL) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "The Param is NULL");
        return ERROR_VKBD_PARAM_NULL;
    }

    BOOL bAlive = IsThreadAlive(m_VKBDThreadID);
    if (!bAlive) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "Thread is not alive");
        return ERROR_VKBD_THREAD_DEAD;
    }

    if (!m_bIsShow) {
        DEBUG_INFO(DEBUGINFO_NORMAL, "UI is not showed");
        return ERROR_VKBD_WITHOUT_UI;
    }

    //lock
    pthread_mutex_lock(&s_cMutex);
    if (m_byKeyBuf == d_KBD_INVALID)//no keyvalue in keybuf
    {
        *pbyKey = d_KBD_INVALID;
    } else {
        *pbyKey = m_byKeyBuf;
        m_byKeyBuf = d_KBD_INVALID;
    }
    //unlock
    pthread_mutex_unlock(&s_cMutex);
    usleep(100000);

    return OK;
}

USHORT CVKBD::VKBDGetImportData(CByteStream& cImportData) {
    DEBUG_ENTRY();

    cImportData.Write(m_cExport.GetBuffer(), m_cExport.GetLength());
    m_cExport.Empty();

    return DEBUG_EXIT(OK);
}

BOOL CVKBD::IsThreadAlive(const pthread_t threadId) {
    BOOL bAlive = FALSE;
    if (threadId == INVALID_THREAD_ID)
        return bAlive;

    if (pthread_kill(threadId, 0) == 0) {
        bAlive = TRUE;
    }

    return bAlive;
}
















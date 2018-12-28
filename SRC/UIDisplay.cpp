#include "UIDisplay.h"
#include "KeyBoard.h"


CUIDisplay::CUIDisplay(void)
{
    CTOS_LCDTClearDisplay();
}



CUIDisplay::~CUIDisplay(void)
{
    CTOS_LCDTClearDisplay();
}



UINT CUIDisplay::MsgBox(PSTR pszDisText, UINT nRetCode)
{
    char szRetText[24] = {0}, szDisText[24] = {0};
    BYTE byKeyIn = 0;
    UINT nRet = 0;

    memset(szDisText, 0x20, 23);
    int nLen = strlen(pszDisText);

    memcpy(szDisText, pszDisText, (nLen > 20 ? 20 : nLen));
    CTOS_Beep();
    CTOS_LCDTClearDisplay();
    CTOS_LCDTSetReverse(TRUE);
    CTOS_LCDTPrintXY(1, 2, (UCHAR*) szDisText);
    CTOS_LCDTSetReverse(FALSE);

    sprintf(szRetText, "RetCode:0x%02X%02X", nRetCode / 256, nRetCode % 256);
    CTOS_LCDTPrintXY(1, 4, (UCHAR*) szRetText);

    while ((byKeyIn != d_KBD_CANCEL) && (byKeyIn != d_KBD_ENTER))
    {
        CTOS_KBDGet(&byKeyIn);
        switch (byKeyIn)
        {
            case d_KBD_CANCEL:
                nRet = d_KBD_CANCEL;
                break;
            case d_KBD_ENTER:
                nRet = d_KBD_ENTER;
                break;
        }
    }
    CTOS_LCDTClearDisplay();
    return nRet;
}


//-----------------------------------------------------------------
//pszTitle:     display UI title
//pszDisplay:   Edit box default display  string
//byMaxLength:  Input max length
//byDateType:   Data Type(DATATYPE_ANS, DATATYPE_N, DATATYPE_PWD)
//cOutData:     Return input data
//bIsFixed:     TURE(input data is fixed), FALSE(not fixed)
//-----------------------------------------------------------------



WORD CUIDisplay::GetUserInputData(PSTR pszTitle, PSTR pszDisplay, BYTE byMaxLength, BYTE byDateType, CByteStream &cOutData, BOOL bIsFixed)
{
    BOOL bFixed = TRUE;
    BYTE byCurrentPosition = 0;
    BYTE byCurrentKeyIn = 0xFF;
    BYTE byTempKeyIn = 0xFF;
    BYTE byKeyIn = 0;
    BYTE byBufferIndex = 0;
    BYTE byMasked = 0;
    WORD wRet = d_OK;
    int iTick = 0;
    BOOL bDotFlag = FALSE;
    BOOL bIPIptFg = FALSE;


    char *KeyboardLayout[] = {
        (PSTR) "0. _,*",
        (PSTR) "1QZqz",
        (PSTR) "2ABCabc",
        (PSTR) "3DEFdef",
        (PSTR) "4GHIghi",
        (PSTR) "5JKLjkl",
        (PSTR) "6MNOmno",
        (PSTR) "7PRSprs",
        (PSTR) "8TUVtuv",
        (PSTR) "9WXYwxy"
    };

    PSTR szInputBuffer = (PSTR) new char[byMaxLength + 1];
    memset(szInputBuffer, 0, byMaxLength + 1);

    strcpy(szInputBuffer, pszDisplay);
    byBufferIndex = strlen(pszDisplay);

    if (byDateType == DATATYPE_PWD)
        byMasked = 1;

    char szTitle[24] = {0};
    memset(szTitle, 0x20, 23);
    int nLen = strlen(pszTitle);
    memcpy(szTitle, pszTitle, (nLen > 20 ? 20 : nLen));
    ShowUI(szTitle, szInputBuffer, byMaxLength, byMasked, bFixed);
    CKeyBoard cKeyBoard;
    
    cKeyBoard.Lock(); 
    while ((byKeyIn != d_KBD_CANCEL) && (byKeyIn != d_KBD_ENTER))
    {
           
        cKeyBoard.KBDHit(&byKeyIn);
        //DEBUG_INFO("byKeyIn is %d", byKeyIn);
        if(byKeyIn == d_KBD_X || byKeyIn == d_KBD_DOWN ||  byKeyIn == d_KBD_DOT)
        {
            byKeyIn = d_KBD_X;
        }
        
        switch (byKeyIn)
        {
            case d_KBD_CANCEL:
            {
                delete [] szInputBuffer;
                CTOS_LCDTClearDisplay();
                return d_KBD_CANCEL;
            }

            case d_KBD_ENTER:
                if (bIsFixed)
                {
                    if (byBufferIndex != byMaxLength)
                        byKeyIn = 0;
                    else
                    {
                        cOutData.Empty();
                        cOutData.Write(szInputBuffer, byBufferIndex);
                        wRet = d_OK;
                    }
                }
                else
                {
                    if (strlen(szInputBuffer) > 0)
                    {
                        if(byDateType == DATATYPE_IP)
                        {
                            struct in_addr addr;
                            wRet = inet_pton(AF_INET, szInputBuffer, (void*)&addr);
                            if(0 == wRet)
                            {
                                wRet = MsgBox((PSTR)"IP Formate Error", 0xF001);
                                if(d_KBD_ENTER == wRet)
                                {
                                    memset(szInputBuffer, 0, byMaxLength + 1);
                                    strcpy(szInputBuffer, pszDisplay);
                                    ShowUI(szTitle, szInputBuffer, byMaxLength, byMasked, bFixed);
                                    bFixed = TRUE;
                                    byBufferIndex = strlen(pszDisplay);
                                    byCurrentKeyIn = 0xFF;
                                    byCurrentPosition = 20;
                                    byKeyIn = 0;
                                    continue;
                                }
                                else
                                {
                                    delete [] szInputBuffer;
                                    CTOS_LCDTClearDisplay();
                                    return d_KBD_CANCEL;
                                }
                            }
                        }
                        
                        cOutData.Empty();
                        cOutData.Write(szInputBuffer, byBufferIndex);
                        wRet = d_OK;
                    }
                    else
                    {
                        CTOS_Beep();
                        byKeyIn = 0;
                        CTOS_LCDTClearDisplay();
                        return d_OK;
                    }
                }
                break;

            case d_KBD_CLEAR:
                if (byBufferIndex > 0)
                    byBufferIndex--;

                memset(&szInputBuffer[byBufferIndex], 0x00, byMaxLength - byBufferIndex);
                bFixed = TRUE;
                bIPIptFg = FALSE;
                ShowUI(szTitle, szInputBuffer, byMaxLength, byMasked, bFixed);
                (szInputBuffer[strlen(szInputBuffer) - 1] == '.')?(bDotFlag = TRUE):(bDotFlag = FALSE);
                byCurrentKeyIn = 0xFF;
                byCurrentPosition = 20;
                break;

            case d_KBD_00:
                memset(szInputBuffer, 0x00, byMaxLength);
                bFixed = TRUE;
                ShowUI(szTitle, szInputBuffer, byMaxLength, byMasked, bFixed);
                byBufferIndex = 0;
                byCurrentKeyIn = 0xFF;
                byCurrentPosition = 20;
                break;
                
            case d_KBD_X :                      //Dot Key        
                if(byDateType == DATATYPE_IP)
                {
                    BYTE byDotNum = 0; //The numer of dots
                        
                    //Find the last dot in the buffer. 
                    for(BYTE byIndex = strlen(szInputBuffer); byIndex > 0; byIndex--)
                    {
                        if (szInputBuffer[byIndex] == '.')
                        {
                            byDotNum++;
                        }
                    }
                    
                    // User can't continuous input dots
                    //DEBUG_INFO("strlen(szInputBuffer) is %d", strlen(szInputBuffer));
                    if((bDotFlag == FALSE) && strlen(szInputBuffer)>0 && (byDotNum < 3))
                    {
                        szInputBuffer[byBufferIndex++] = '.';
                        bDotFlag = TRUE;
                        ShowUI(szTitle, szInputBuffer, byMaxLength, byMasked, TRUE);
                    }
                    else 
                    {
                        CTOS_Beep();
                    }
                }
                else if(byDateType == DATATYPE_ANS)
                {
                    szInputBuffer[byBufferIndex++] = '.';
                    ShowUI(szTitle, szInputBuffer, byMaxLength, byMasked, TRUE);
                }
                break;

            case d_KBD_0:
            case d_KBD_1:
            case d_KBD_2:
            case d_KBD_3:
            case d_KBD_4:
            case d_KBD_5:
            case d_KBD_6:
            case d_KBD_7:
            case d_KBD_8:
            case d_KBD_9:                
                if (byBufferIndex < byMaxLength)
                {
                    if (byDateType == DATATYPE_N)
                    {
                        szInputBuffer[byBufferIndex++] = byKeyIn;
                        ShowUI(szTitle, szInputBuffer, byMaxLength, byMasked, TRUE);
                    }
                    else if(byDateType == DATATYPE_IP )//IP Type
                    {
                        //If the input number is full, can't continue typing
                        if(bIPIptFg || ((byKeyIn == d_KBD_0) && !strlen(szInputBuffer)) || 
                           (szInputBuffer[strlen(szInputBuffer) - 2] == '.') && (szInputBuffer[strlen(szInputBuffer) - 1] == '0') )
                        {
                            CTOS_Beep();
                            break;
                        }                      
                        
                        BYTE byIP = 0;    //Current  IP Num
                        BYTE byLDotPost = 0;   //The position of last Dot in the buffer 
                        BYTE byDotNum = 0; //The numer of dots
                        
                        //Find the last dot in the buffer. 
                        for(BYTE byIndex = strlen(szInputBuffer); byIndex > 0; byIndex--)
                        {
                            if (szInputBuffer[byIndex] == '.')
                            {
                                if(byDotNum == 0)
                                {
                                    byLDotPost = byIndex;
                                }
                                byDotNum++;
                            }
                        }

                        //Calculate the Value of the last segment of IP
                        for(BYTE byIndex = (byLDotPost)?(byLDotPost+1):(byLDotPost); byIndex < strlen(szInputBuffer); byIndex++)
                        {
                            byIP *= 10;
                            byIP += (szInputBuffer[byIndex]) - 0x30;
                        }
                        
                        WORD wTempSum = byIP*10 + byKeyIn -0x30;
                        
                        if(wTempSum>255 )//&& byDotNum == DOTNUM
                        {
                            CTOS_Beep();
                        }
                        else if( wTempSum > 0 && wTempSum <= 255 && byDotNum <= DOTNUM)
                        {
                            szInputBuffer[byBufferIndex++] = byKeyIn;
                            ShowUI(szTitle, szInputBuffer, byMaxLength, byMasked, TRUE);
                            (byDotNum < DOTNUM)?(bDotFlag = FALSE):(0);
                        }
                        else if( wTempSum == 0 && byDotNum <= DOTNUM)
                        {
                            if(byDotNum < DOTNUM)
                            {
                                szInputBuffer[byBufferIndex++] = byKeyIn;
                                szInputBuffer[byBufferIndex++] = '.';
                                byLDotPost = byBufferIndex;
                                byDotNum++;
                                ShowUI(szTitle, szInputBuffer, byMaxLength, byMasked, TRUE);
                                bDotFlag = TRUE;
                                bIPIptFg = FALSE;
                            }
                            else if(bIPIptFg == FALSE && byDotNum == DOTNUM)
                            {
                                szInputBuffer[byBufferIndex++] = byKeyIn;
                                ShowUI(szTitle, szInputBuffer, byMaxLength, byMasked, TRUE);
                                bDotFlag = TRUE;
                                bIPIptFg = TRUE;
                            }
                        }
                        
                        if(((strlen(szInputBuffer) - byLDotPost >= MAXSUBLEN + 1) || 
                            (strlen(szInputBuffer) - byLDotPost >= MAXSUBLEN) && 
                            (!byLDotPost)) && byDotNum <= DOTNUM)
                        {
                            if(byDotNum != DOTNUM)
                            {
                                szInputBuffer[byBufferIndex++] = '.';
                                byLDotPost = byBufferIndex;
                                byDotNum++;
                                ShowUI(szTitle, szInputBuffer, byMaxLength, byMasked, TRUE);
                                bDotFlag = TRUE;
                            }
                        }
                        (byDotNum >= DOTNUM)?(bDotFlag = TRUE):(0);
                    }//End of IP Tape
                    else
                    {
                        byTempKeyIn = byKeyIn - '0';
                        if (byTempKeyIn != byCurrentKeyIn)
                        {
                            if (!bFixed)
                                byBufferIndex++;

                            byCurrentKeyIn = byTempKeyIn;
                            byCurrentPosition = 0;
                        }
                        else
                        {
                            if (++byCurrentPosition >= strlen(KeyboardLayout[byCurrentKeyIn]))
                                byCurrentPosition = 0;
                        }
                        bFixed = FALSE;

                        szInputBuffer[byBufferIndex] = KeyboardLayout[byCurrentKeyIn][byCurrentPosition];
                        //printf("CK%i,  CP:%i, sz:%02x\r\n", byCurrentKeyIn, byCurrentPosition, szInputBuffer[byBufferIndex]);
                        ShowUI(szTitle, szInputBuffer, byMaxLength, byMasked, bFixed);

                        iTick = CTOS_TickGet();
                    }
                }
                else
                {
                    CTOS_Beep();
                }
                break;

            default:
                if (byDateType == DATATYPE_N)
                    break;

                if (!bFixed && (CTOS_TickGet() - iTick > 80))
                {
                    if (byBufferIndex >= byMaxLength)
                        byBufferIndex = byMaxLength;
                    else
                        byBufferIndex += 1;
                    byTempKeyIn = 0xFF;
                    byCurrentPosition = 20;
                    bFixed = TRUE;
                    ShowUI(szTitle, szInputBuffer, byMaxLength, byMasked, bFixed);
                }
                break;
        }
    }
    cKeyBoard.Unlock();
    delete [] szInputBuffer;
    CTOS_LCDTClearDisplay();
    return wRet;
}



void CUIDisplay::ShowUI(PSTR pszTitle, PSTR pszDisplayStr, BYTE byMaxLength, BOOL byMasked, BOOL bFixed)
{
    char szDisplayBuffer[24] = {0};
    BYTE bIndex = 0;

    pszDisplayStr[byMaxLength] = 0;

    if (pszDisplayStr != NULL)
    {
        strcpy(szDisplayBuffer, pszDisplayStr);
    }

    if (byMasked)
    {
        for (bIndex = 0; bIndex < strlen(szDisplayBuffer); bIndex++)
        {
            if (bFixed || (bIndex < (strlen(szDisplayBuffer) - 1)))
            {
                szDisplayBuffer[bIndex] = '*';
            }
        }
    }

    if ((strlen(szDisplayBuffer) < byMaxLength) && bFixed)
    {
        szDisplayBuffer[strlen(szDisplayBuffer)] = '_';
    }

    CTOS_LCDTSetReverse(TRUE);
    CTOS_LCDTPrintXY(1, 1, (UCHAR*) pszTitle);
    CTOS_LCDTSetReverse(FALSE);
    CTOS_LCDTPrintXY(1, 2, (UCHAR*) "                     ");
    CTOS_LCDTPrintXY(1, 2, (UCHAR*) szDisplayBuffer);
}



BOOL CUIDisplay::GetYesNo(PSTR pszTitle, BYTE byYN)
{
    char szTitle[24] = {0};
    memset(szTitle, 0x20, 23);
    int nLen = strlen(pszTitle);
    memcpy(szTitle, pszTitle, (nLen > 20 ? 20 : nLen));

    CTOS_LCDTClearDisplay();
    CTOS_LCDTSetReverse(TRUE);
    CTOS_LCDTPrintXY(1, 4, (UCHAR*) szTitle);
    CTOS_LCDTSetReverse(FALSE);

    BYTE byDis = byYN;

    BYTE byKeyIn = 0;
    while (byKeyIn != d_KBD_ENTER)
    {
        if (byDis)
            CTOS_LCDTPrintXY(2, 5, (UCHAR*) "Y");
        else
            CTOS_LCDTPrintXY(2, 5, (UCHAR*) "N");

        CTOS_KBDGet(&byKeyIn);

        switch (byKeyIn)
        {
            case d_KBD_ENTER:
            {
                CTOS_LCDTClearDisplay();
                return byDis;
            }

            case d_KBD_UP:
            case d_KBD_DOWN:
                byDis = ~byDis;
                break;
        }
    }
}

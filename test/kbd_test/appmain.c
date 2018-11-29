/*========================================*
*             I N C L U D E S             *
*=========================================*/
#include <string.h>
#include <stdio.h>
#include <ctosapi.h>
#include <stdlib.h>
#include <stdarg.h>
#include "wub_lib.h"

/*==========================================*
 *            D E F I N E S                 *
 *==========================================*/
#define d_BUFF_SIZE 32	      //Buffer Size

//Declare Global Variable //
BYTE key;
BYTE babuff[d_BUFF_SIZE];
BYTE isSoundTurnON;

/* ==========================================================================
 *
 * FUNCTION NAME: show_screen
 *
 * DESCRIPTION:   Show on the LCD Display
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ========================================================================== */
void show_screen(int tag)
{
  //Clear LCD Display //
  CTOS_LCDTClearDisplay();
  
  switch(tag)
  {
    case 0:
      CTOS_LCDTSetReverse(TRUE);
      CTOS_LCDTPrintXY(1, 1, "    Key Board    ");
      CTOS_LCDTSetReverse(FALSE);
      CTOS_LCDTPrintXY(1, 2, "1.Get One Key");
      if (isSoundTurnON) CTOS_LCDTPrintXY(1, 3, "2.Sound Turn OFF");
      else CTOS_LCDTPrintXY(1, 3, "2.Sound Turn ON ");
      CTOS_LCDTPrintXY(1, 4, "3.Set Frequence");
      CTOS_LCDTPrintXY(1, 5, "4.Set RTC");
      break;
    case 1:
      CTOS_LCDTSetReverse(TRUE);
      CTOS_LCDTPrintXY(1, 1, "   InputString   ");
      CTOS_LCDTSetReverse(FALSE);
      break;
    case 2:
      CTOS_LCDTSetReverse(TRUE);
      CTOS_LCDTPrintXY(1, 1, "  Set Frequence  ");
      CTOS_LCDTSetReverse(FALSE);
      break;
  }
}

/* ==========================================================================
 *
 * FUNCTION NAME: GetOneKey
 *
 * DESCRIPTION:   Get one key from the keyboard and show key value on the 
 *		  LCD Display.
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ========================================================================== */
void GetOneKey(void)
{
  //Declare Local Variable //
  BOOL isKey;
  
  CTOS_LCDTClearDisplay();
  CTOS_LCDTSetReverse(TRUE);
  CTOS_LCDTPrintXY(1, 1, "   GetOneKey   ");
  CTOS_LCDTSetReverse(FALSE);
  CTOS_LCDTPrintXY(1, 8, "Key -> ");
  while (1){
    
    //Detect if any key is pressed //
    CTOS_KBDInKey(&isKey);
    if (isKey){ //If isKey is TRUE, represent key be pressed //
      
      //Get a key from keyboard //
      CTOS_KBDGet(&key);
    
      if (key == d_KBD_CANCEL){
	CTOS_LCDTPrintXY(8, 8, "X    ");
	CTOS_Delay(1000);
	show_screen(0);
	return;
      }else if (key == d_KBD_CLEAR){
	CTOS_LCDTPrintXY(8, 8, "<-   ");
      }else if (key == d_KBD_ENTER){
	CTOS_LCDTPrintXY(8, 8, "OK   ");
      }else if (key == d_KBD_DOT){
	CTOS_LCDTPrintXY(8, 8, "'.'  ");
      }else if (key  == d_KBD_F1){
	CTOS_LCDTPrintXY(8, 8, "F1   ");
      }else if (key == d_KBD_F2){
	CTOS_LCDTPrintXY(8, 8, "F2   ");
      }else if (key == d_KBD_F3){
	CTOS_LCDTPrintXY(8, 8, "F3   ");
      }else if (key == d_KBD_F4){
	CTOS_LCDTPrintXY(8, 8, "F4   ");
      }else if (key == d_KBD_UP){
	CTOS_LCDTPrintXY(8, 8, "UP   ");
      }else if (key == d_KBD_DOWN){
	CTOS_LCDTPrintXY(8, 8, "DOWN ");
      }else if ((key >=0x30)&&(key <=0x39)){
	CTOS_LCDTPutchXY(8, 8,key);
	CTOS_LCDTPrintXY(9, 8, "   ");
      }
    }
  }
}

/* ==========================================================================
 *
 * FUNCTION NAME: InputString
 *
 * DESCRIPTION:   Continue to input two or more characters at a time, build a string
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ========================================================================== */
int InputString(USHORT usX, USHORT usY, BYTE isMask, BYTE *pbaStr, USHORT *usStrLen){
  //Declare Local Variable //
  int i = 0;
  
  memset(pbaStr,0x00,*usStrLen);
  CTOS_LCDTPutchXY(usX, usY, '_');
  
  while(1){
    
    //Scan the keyboard to detect whether a key is pressed //
    CTOS_KBDHit(&key);
    
    //Cancel InputString() //
    if (key == d_KBD_CANCEL){
      CTOS_LCDTPutchXY(usX+i, usY, ' ');
      memset(pbaStr,0x00,*usStrLen);
      usStrLen = 0;
      return 0;
    }
    
    //Done input and output a string //
    if (key == d_KBD_ENTER){
      CTOS_LCDTPutchXY(usX+i, usY, ' ');
      *usStrLen = strlen(pbaStr);
      if (*usStrLen > 0) return 1;
      else return 0;
    }else if (key == d_KBD_CLEAR){  //Backspace //
      CTOS_LCDTPutchXY(usX+i, usY, ' ');
      i--;
      pbaStr[i] = 0x00;
      CTOS_LCDTPutchXY(usX+i, usY, '_');
    }else if(key == d_KBD_00){	//Clear all input data //
      memset(pbaStr,0x00,*usStrLen);
      i = 0;
      CTOS_LCDTGotoXY(usX+i,usY);
      CTOS_LCDTClear2EOL();
      CTOS_LCDTPutchXY(usX, usY, '_');
    }
    if (i+1 <= *usStrLen){  
      if ((key >=0x30)&& (key <=0x39)){
	pbaStr[i] = key;

	if (isMask) CTOS_LCDTPutchXY(usX+i, usY, '*');
	else  CTOS_LCDTPutchXY(usX+i, usY, pbaStr[i]);
	i++;
	CTOS_LCDTPutchXY(usX+i, usY, '_');
      }
    }
  }
}

/* ==========================================================================
 *
 * FUNCTION NAME: SetRTC
 *
 * DESCRIPTION:   Use this function to set the real-time clock's data and time.
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ========================================================================== */
void SetRTC(void)
{
  //Declare Local Variable //
  CTOS_RTC SetRTC;
  USHORT i;
  BYTE isSet = FALSE;
  BYTE baYear[4+1],baMonth[2+1],baDay[2+1],baHour[2+1],baMinute[2+1],baSecond[2+1];
  
  CTOS_LCDTClearDisplay();
  CTOS_LCDTSetReverse(TRUE);
  CTOS_LCDTPrintXY(1, 1, "     Set RTC     ");
  CTOS_LCDTSetReverse(FALSE);
  
  //Read the date and the time //
  CTOS_RTCGet(&SetRTC);
  
  //Show on the LCD Dispaly //
  CTOS_LCDTPrintXY(1, 2, "   Get   Set");
  sprintf(babuff,"YY:%04d",SetRTC.bYear + 2000);
  CTOS_LCDTPrintXY(1, 3, babuff);
  sprintf(babuff,"MM:%02d",SetRTC.bMonth);
  CTOS_LCDTPrintXY(1, 4, babuff);
  sprintf(babuff,"DD:%02d",SetRTC.bDay);
  CTOS_LCDTPrintXY(1, 5, babuff);
  sprintf(babuff,"hh:%02d",SetRTC.bHour);
  CTOS_LCDTPrintXY(1, 6, babuff);
  sprintf(babuff,"mm:%02d",SetRTC.bMinute);
  CTOS_LCDTPrintXY(1, 7, babuff);
  sprintf(babuff,"ss:%02d",SetRTC.bSecond);
  CTOS_LCDTPrintXY(1, 8, babuff);
  
  sprintf(babuff,"%02d",SetRTC.bDoW);
  CTOS_LCDTPrintXY(15, 8, babuff);
  
  //Input data for the setting //
  i = sizeof(baYear);
  if (InputString(10,3,FALSE, baYear, &i) == 1){    //Input Year //
    SetRTC.bYear = (wub_str_2_long(baYear) - 2000);
    isSet = TRUE;
  }
  i = sizeof(baMonth);
  if (InputString(10,4,FALSE, baMonth, &i) == 1){   //Input Month //
    SetRTC.bMonth = wub_str_2_long(baMonth);
    isSet = TRUE;
  }
  i = sizeof(baDay);
  if (InputString(10,5,FALSE, baDay, &i) == 1){	  //Input Day //
    SetRTC.bDay = wub_str_2_long(baDay);
    isSet = TRUE;
  }
  i = sizeof(baHour);
  if (InputString(10,6,FALSE, baHour, &i) == 1){  //Input Hour //
    SetRTC.bHour = wub_str_2_long(baHour);
    isSet = TRUE;
  }
  i = sizeof(baMinute);
  if (InputString(10,7,FALSE, baMinute, &i) == 1){  //Input Minute //
    SetRTC.bMinute = wub_str_2_long(baMinute);
    isSet = TRUE;
  }
  i = sizeof(baSecond);
  if (InputString(10,8,FALSE, baSecond, &i) == 1){  //Input Second //
    SetRTC.bSecond = wub_str_2_long(baSecond);
    isSet = TRUE;
  }
  ///////////////////////////////////////////////////////////
  
  
  if (isSet){
    //Set the date and time //
    if (CTOS_RTCSet(&SetRTC) == d_OK) CTOS_LCDTPrintXY(15, 2, "OK");
    else CTOS_LCDTPrintXY(13, 2, "Fail");
    isSet = FALSE;
  }
  
  CTOS_KBDGet ( &key );
  show_screen(0);
  return;
}

/* ==========================================================================
 *
 * FUNCTION NAME: main
 *
 * DESCRIPTION:   function main is responsible for all the tasks listed in the
 *                introduction to this demo.
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ========================================================================== */
int main (int argc, char *argv[])
{
  //Declare Local Variable //
  USHORT i, usFreq=0, usDur=0;
  BYTE isFreq = FALSE, isDur = FALSE;
  
  CTOS_LCDTSelectFontSize(0x101E);

  // TODO: Add your program here //
  //Initial //
  isSoundTurnON = TRUE;
  //Turn on the keyboard sound //
  CTOS_KBDSetSound(d_ON); //Default //
  
  show_screen(0);
  
  while(1){
    CTOS_KBDGet ( &key );
    switch(key){
      case d_KBD_1:
	GetOneKey();
	break;
      case d_KBD_2:
	if (isSoundTurnON){
	  //Turn off the keyboard sound //
	  CTOS_KBDSetSound(d_OFF);
	  isSoundTurnON = FALSE;
	  CTOS_LCDTPrintXY(1, 3, "2.Sound Turn ON ");
	}else{
	  //Turn on the keyboard sound //
	  CTOS_KBDSetSound(d_ON);
	  isSoundTurnON = TRUE;
	  CTOS_LCDTPrintXY(1, 3, "2.Sound Turn OFF");
	}
	break;
      case d_KBD_3:
	//Set the sound frequency and duration for keyboard //
	show_screen(2);
	i = sizeof(babuff);
	CTOS_LCDTPrintXY(1, 2, "Sound Frequency");
	//Input values for the settings //
	if (InputString(1,3,FALSE,babuff,&i) == 1){
	  usFreq = wub_str_2_long(babuff);
	  sprintf(babuff,"%d",usFreq);
	  CTOS_LCDTPrintXY(10, 3, babuff);
	  isFreq = TRUE;
	}
	CTOS_LCDTPrintXY(1, 4, "Duration");
	i = sizeof(babuff);
	if (InputString(1,5,FALSE,babuff,&i) == 1){
	  usDur = wub_str_2_long(babuff);
	  sprintf(babuff,"%d",usDur);
	  CTOS_LCDTPrintXY(10, 5, babuff);
	  isDur = TRUE;
	}
	if ((isFreq) && (isDur)){
	  //Set to the keyboard //
	  if (CTOS_KBDSetFrequence(usFreq, usDur) == d_OK){
	    isFreq = FALSE;
	    isDur = FALSE;
	    CTOS_LCDTPrintXY(1, 8, "Set....OK");
	  }else{
	    CTOS_LCDTPrintXY(1, 8, "Set....Fail");
	  }  
	}else{
	  CTOS_LCDTPrintXY(1, 8, "Set....Cancel");
	}
	CTOS_KBDGet ( &key );
	show_screen(0);
	break;
      case d_KBD_4:
	SetRTC();
	break;
      case d_KBD_CANCEL:
	return 0;
	break;
    }
  }
  exit(0);
}

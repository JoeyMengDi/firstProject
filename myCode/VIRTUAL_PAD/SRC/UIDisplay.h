#ifndef H_UIDISPLAY
#define H_UIDISPLAY
#include "StdafxHead.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>

#define MAXSUBLEN  3
#define DOTNUM       3

class CUIDisplay
{
public:
    CUIDisplay(void);
    ~CUIDisplay(void);

    UINT MsgBox(PSTR pszDisText, UINT nRetCode);
	WORD GetUserInputData(PSTR pszTitle, PSTR pszDisplay, BYTE byMaxLength, BYTE byDateType, CByteStream &cOutData, BOOL bIsFixed);
    void ShowUI(PSTR pszTitle, PSTR pszDisplayStr, BYTE byMaxLength, BOOL byMasked, BOOL bFixed);
	
	BOOL GetYesNo(PSTR pszTitle, BYTE byYN);
private:
    //WORD InPutIP(PSTR pszIN, BYTE byKeyIn, PSTR );
};
#endif
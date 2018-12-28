//---------------------------------------------------------------------------

#ifndef publicH
#define publicH

void Delay(DWORD DT);
//void ShowLogMsg(String Str,TColor Tc ,TRichEdit *TR);
void ShowLogMsg(String Str,TColor Tc ,BYTE bItem);
void ShowBufToHex(int iLen,BYTE *baBuf ,TMemo *TM);
void ShowBufToAsci(int iLen,BYTE *baBuf,TMemo *TM);
BYTE Cal_ConLRC(BYTE Olrc, BYTE *buf, int len);
BYTE Cal_LRC(BYTE *buf, int len);
ULONG Ed_PackAnyTo1(BYTE *BufIN,int AnyLen);
int Ed_Pack1ToAny(int ValueIN,int AnyLen,BYTE *OutBuf);
void GetFixedData(BYTE *bSrcBuf,USHORT uSrcLen,USHORT uStartAddr,USHORT uFixedLen,BYTE *bDestBuf);
                
//---------------------------------------------------------------------------
#endif

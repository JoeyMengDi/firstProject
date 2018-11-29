//---------------------------------------------------------------------------

#ifndef publicH
#define publicH

#define d_OS_WIN31      0
#define d_OS_WIN95      1
#define d_OS_WIN95R2    2
#define d_OS_WIN98      3
#define d_OS_WIN98SE    4
#define d_OS_WINME      5
#define d_OS_WINNT      6
#define d_OS_WIN2000    7
#define d_OS_WINXP      8
#define d_OS_WIN2003    9
#define d_OS_ADVANCE    10
#define d_OS_UNKNOWN    11

#define d_LOG_FILE_MAX_SIZE                  512*1024

//For File Save
#define d_SAVE_LOG_FILE_OPEN_FAIL            0x10
#define d_SAVE_LOG_FILE_SIZE_EXCEED          0x11
#define d_SAVE_LOG_FILE_OK                   0x12
//For File Read
#define d_READ_LOG_FILE_NOT_FOUND            0x13
#define d_READ_LOG_FILE_SIZE_EXCEED          0x14
#define d_READ_LOG_FILE_OPEN_FAIL            0x15
#define d_READ_LOG_FILE_OK                   0x16
//For INI File Write
#define d_WRITE_INI_FILE_EXIST               0x17
#define d_WRITE_INI_FILE_OK                  0x18
#define d_DEFAULT_PATH                       0x19
#define d_CUSTOM_PATH                        0x1A
#define d_NO_CHECK                           0x1B
#define d_CHECK                              0x1C
//For INI File Read
#define d_READ_INI_FILE_NOT_FOUND            0x1D
#define d_READ_INI_FILE_OK                   0x1E

void ED_Delay(DWORD DT);
int ED_GetCurrentSystem(void);
int ED_CheckFileSize(void);
void ED_DelTree(String dir);
void ED_CopyTree(String SourDir,String DestDir);
void ED_SetLogFilePath(String sDir,String sName);
int ED_SaveLogFile(int iLen,BYTE *baBuf);
int ED_ReadLogFile(void);
int ED_WriteIniFile(BYTE bPathType,BYTE bExistchk);
int ED_ReadIniFile(void);
int ED_DoesFileRunning(BYTE *baFileName);
int ED_CheckWindow(BYTE *baWindowCaption);
int ED_ConnectWebSite(BYTE *baWebSite);
int ED_ExecuteFile(BYTE *baFileNamePath);
void ED_SetFileAutoRun(AnsiString APPName,AnsiString Value);
void ED_ListAutoRunFile(void);
void ED_ListProcessNameAndID(DWORD processID);
void ED_ListProcess(void);
void ED_ShowLogMsg(String Str,TColor Tc);
void ED_ShowBufToHex(int iBufLen,BYTE *baBuf,TMemo *TM);
void ED_ShowBufToAsci(char *baTitle,BYTE *baBuf,int iLen,TColor Tc,TRichEdit *TR);
void ED_ShowTxShape(TShape *spTx);
void ED_ShowRxShape(TShape *spRx);
BYTE ED_AsciToDEC(BYTE *baBuf,int iBufLen);
int ED_PackPwd(BYTE *baInputBuf,int iBufLen,BYTE *baOutPutBuf,int iPackLen);
ULONG ED_PackAnyTo1(BYTE *baBufIN,int iAnyLen);
int ED_Pack1ToAny(ULONG ulValueIN,int iAnyLen,BYTE *baOutBuf);
void ED_GetFixedData(BYTE *bSrcBuf,USHORT uSrcLen,USHORT uStartAddr,USHORT uFixedLen,BYTE *bDestBuf);
void ED_RestartPC(void);
void ED_ShutdownPC(void);
void ED_LogoffPC(void);
void ED_GetProgramVersion(char *cVer);
extern char caDest[65535];
//---------------------------------------------------------------------------
#endif
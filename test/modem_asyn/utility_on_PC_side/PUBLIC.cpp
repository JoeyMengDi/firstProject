//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Main.h"
#include "PUBLIC.h"
#include "Version.h"
#include "inifiles.hpp"
#include "Registry.hpp"
#include "psapi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
FILE *iFileHandle;
HANDLE hMutex;
HWND hwDetect;
int iLogFileSize;
String DirNamePath,FileName,FileNamePath;
BYTE baReadLog[d_LOG_FILE_MAX_SIZE];
char caDest[65535];
//---------------------------------------------------------------------------
void ED_Delay(DWORD DT)
{
    long tt;
    tt=::GetTickCount();
    while (::GetTickCount()-tt<DT)
    {
        Application->ProcessMessages();
        if ((::GetTickCount()-tt)<=0)
            tt=::GetTickCount();
    }
}
//---------------------------------------------------------------------------
int ED_GetCurrentSystem(void)
{
   OSVERSIONINFOEX osvi;

   ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

   if( !GetVersionEx((OSVERSIONINFO *) &osvi))
   {
      // If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
      osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
      if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) )
         return d_OS_UNKNOWN;
   }
   switch (osvi.dwPlatformId)
   {
        case VER_PLATFORM_WIN32_NT:

            if(osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
                return d_OS_WIN2003;
            if(osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
                return d_OS_WINXP;
            if(osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
                return d_OS_WIN2000;
            if(osvi.dwMajorVersion <=4)
                return d_OS_WINNT;
            if(osvi.dwMajorVersion >=6)
                return d_OS_ADVANCE;
            break;

        case VER_PLATFORM_WIN32_WINDOWS:

            if(osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
            {
                if(osvi.szCSDVersion[1] == 'C' || osvi.szCSDVersion[1] == 'B')
                    return d_OS_WIN95R2;
                return d_OS_WIN95;
            }
            if(osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10)
            {
                if(osvi.szCSDVersion[1] == 'A')
                    return d_OS_WIN98SE;
                return d_OS_WIN98;
            }
            if(osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
                return d_OS_WINME;

        case VER_PLATFORM_WIN32s:
            return d_OS_WIN31;
        default:
                break;
   }
   return d_OS_UNKNOWN;
}
//---------------------------------------------------------------------------
int ED_CheckFileSize(void)
{
    TSearchRec SearchRec;

    if (!FileExists(FileNamePath))
        return 0;
    if (FindFirst(FileNamePath, faAnyFile, SearchRec) == 0)
        return SearchRec.Size;
    return 0;
}
//---------------------------------------------------------------------------
void ED_DelTree(String dir)
{
    String d=dir;
    String FileName;
    TSearchRec SearchRec;

    if (!DirectoryExists(dir))
        return;

    if (d.SubString(d.Length(),1)!="\\")
        d=d+"\\";

    if (FindFirst(d+"*.*", faAnyFile, SearchRec) == 0)
    {
        do {
                if (SearchRec.Attr == faDirectory)
                {
                    if ((SearchRec.Name!=".") && (SearchRec.Name!=".."))
                    {
                        ED_DelTree(d+SearchRec.Name); //遞迴呼叫
                        RemoveDir(d+SearchRec.Name);
                    }
                }
                else
                {
                    FileSetAttr(d+SearchRec.Name,faArchive);
                    DeleteFile(d+SearchRec.Name);
                }
            }while (FindNext(SearchRec) == 0);
        FindClose(SearchRec);
    }
    RemoveDir(d);
}
//---------------------------------------------------------------------------
void ED_CopyTree(String SourDir,String DestDir)
{
    String Sour;
    String Dest;
    TSearchRec FileRec;

    String Title = "EG_ATM 正在架構: ";
    Sour = SourDir;
    Dest = DestDir;

    if (Sour.SubString(Sour.Length(),1)!="\\")
        Sour=Sour+"\\";
    if (Dest.SubString(Dest.Length(),1)!="\\")
        Dest=Dest+"\\";

    if (!DirectoryExists(SourDir))
    {
        //ShowMessage("來源目錄不存在!!");
        return;
    }

    if (!DirectoryExists(DestDir))
    {
        ForceDirectories(DestDir);
    }
    if (FindFirst(Sour+"*.*", faAnyFile, FileRec) == 0)
    {
        do {
                if ((FileRec.Attr & faDirectory)!=0)//Copy 資料夾
                {
                    if ((FileRec.Name!=".") && (FileRec.Name!=".."))
                    {
                        frmMain->Caption = Title+(Sour+FileRec.Name).c_str();
                        ED_CopyTree(Sour+FileRec.Name,Dest+FileRec.Name); //遞迴呼叫
                    }
                }
                else//Copy 檔案
                {
                    CopyFile((Sour+FileRec.Name).c_str(),(Dest+FileRec.Name).c_str(),false);
                    frmMain->Caption = Title+(Sour+FileRec.Name).c_str();
                }
            }while (FindNext(FileRec) == 0);
        FindClose(FileRec);
    }
}
//---------------------------------------------------------------------------
void ED_SetLogFilePath(String sDir,String sName)
{
    DirNamePath = sDir;   //".\\Profiles"
    FileName = sName;     //"EGATM.dat"

    DirNamePath+="\\";
    FileNamePath = DirNamePath+FileName;
}
//---------------------------------------------------------------------------
//Please execute SetLogFilePath() func at first
int ED_SaveLogFile(int iLen,BYTE *baBuf)
{
    if(iLen+(int)ED_CheckFileSize()>d_LOG_FILE_MAX_SIZE)
        return d_SAVE_LOG_FILE_SIZE_EXCEED;

    if (!DirectoryExists(DirNamePath))
        ForceDirectories(DirNamePath);

    iFileHandle = fopen(FileNamePath.c_str(),"ab");//Open for binary writing at end-of-file or create for writing if the file does not exist.
    if(iFileHandle == NULL)
        return d_SAVE_LOG_FILE_OPEN_FAIL;
    else
        fwrite(baBuf,iLen,1,iFileHandle);
    fclose(iFileHandle);
    return d_SAVE_LOG_FILE_OK;
}
//---------------------------------------------------------------------------
int ED_ReadLogFile(void)
{
    if(!FileExists(FileNamePath))
        return d_READ_LOG_FILE_NOT_FOUND;

    iLogFileSize = ED_CheckFileSize();
    if(iLogFileSize>d_LOG_FILE_MAX_SIZE)
        return d_READ_LOG_FILE_SIZE_EXCEED;

    iFileHandle = fopen(FileNamePath.c_str(),"rb");
    if(iFileHandle == NULL)
        return d_READ_LOG_FILE_OPEN_FAIL;
    else
    {
        memset(baReadLog,0x00,d_LOG_FILE_MAX_SIZE);
        fseek(iFileHandle,SEEK_SET,0);
        fread(&baReadLog[0],iLogFileSize,1,iFileHandle);
        fclose(iFileHandle);
    }
    return d_READ_LOG_FILE_OK;
}
//---------------------------------------------------------------------------
//Please execute SetLogFilePath() func at first
int ED_WriteIniFile(BYTE bPathType,BYTE bExistchk)
{
    TIniFile *ini;
    switch(bPathType)
    {
        case d_DEFAULT_PATH:
            FileNamePath = ExtractFilePath(Application->ExeName);
            FileNamePath+=FileName;
            break;
        case d_CUSTOM_PATH:
            if (!DirectoryExists(DirNamePath))
                ForceDirectories(DirNamePath);
            break;
    }
    switch(bExistchk)
    {
        case d_CHECK:
            if(FileExists(FileNamePath))
                return d_WRITE_INI_FILE_EXIST;
        case d_NO_CHECK:
            break;
    }
    ini = new TIniFile(FileNamePath);

    //ini->WriteString("Download_1","TermID",frmMain->edtTermID->Text);

    delete ini;
    return d_WRITE_INI_FILE_OK;
}
//---------------------------------------------------------------------------
int ED_ReadIniFile(void)
{
    TIniFile *ini;
    if(!FileExists(FileNamePath))
        return d_READ_INI_FILE_NOT_FOUND;
    ini = new TIniFile(FileNamePath);
    //frmSetting->edtTMS_IP->Text = ini->ReadString("TMS_Server","IP","127.0.0.1");

    delete ini;
    return d_READ_INI_FILE_OK;
}
//---------------------------------------------------------------------------
//防止程式被重複執行
int ED_DoesFileRunning(BYTE *baFileName)
{
    hMutex = OpenMutex(MUTEX_ALL_ACCESS,FALSE,baFileName);
    // 檢查MutexName是否已經存在。
    if (hMutex)
        return (true);
    // 如果不存在, 新增MutexName。
    hMutex = CreateMutex(NULL, FALSE, baFileName);
    return (false);
}
//---------------------------------------------------------------------------
int ED_CheckWindow(BYTE *baWindowCaption)
{
    hwDetect = NULL;
    baWindowCaption = "PChome Online - Microsoft Internet Explorer";
    hwDetect = FindWindow("IEFrame",baWindowCaption);
    if (::IsWindow(hwDetect))
        return (true);
    return false;
}
//---------------------------------------------------------------------------
int ED_ConnectWebSite(BYTE *baWebSite)
{
    HINSTANCE hinst;
    baWebSite = "www.pchome.com.tw";
    hinst = ShellExecute(NULL,NULL,"C:\\Program Files\\Internet Explorer\\iexplore.exe",baWebSite,NULL,SW_SHOWMAXIMIZED);
    if((int)hinst<32)
    {
        ShowMessage("網頁連結發生錯誤: "+SysErrorMessage(GetLastError()));
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------
int ED_ExecuteFile(BYTE *baFileNamePath)
{
    HINSTANCE hinst;
    baFileNamePath = "C:\\WINDOWS\\Temp\\Uninstall_Prompt.exe";
    hinst = ShellExecute(NULL,"open",baFileNamePath,NULL,NULL,SW_SHOWNORMAL);

    if((int)hinst<32)
    {
        ShowMessage("開啟檔案錯誤: "+SysErrorMessage(GetLastError()));
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------
void ED_SetFileAutoRun(AnsiString APPName,AnsiString Value)
{
    int KeyGood;
    AnsiString sCurrentPath;
    TRegistry *Reg=new TRegistry;

    sCurrentPath = "\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    APPName = "EG_ATM.exe";
    Value = "C:\\Program Files\\EG_ATM\\EG_ATM.exe";
    
    Reg->RootKey = HKEY_LOCAL_MACHINE;
    //if(chkboxWinStart->Checked == true)
    //{
         KeyGood = Reg->OpenKey(sCurrentPath,false);
         if(KeyGood)
             Reg->WriteString(APPName,Value);
    //}
    //else
    //{
         KeyGood = Reg->OpenKey(sCurrentPath,false);
         if(KeyGood)
         {
             if(Reg->ValueExists(APPName))
             {
                 if(Reg->DeleteValue(APPName))
                     ;
             }
             else
                 ;
         }
    //}
    Reg->CloseKey();
    delete Reg;
}
//---------------------------------------------------------------------------
void ED_ListAutoRunFile(void)
{
   int KeyGood;
   TRegistry *reg=new TRegistry;
   TStringList *sl=new TStringList;

   AnsiString sCurrentPath,sCurrentKey,sValue;
   sCurrentPath = "\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";

   //Memo1->Lines->Clear();
   reg->RootKey=HKEY_LOCAL_MACHINE;
   KeyGood = reg->OpenKey(sCurrentPath,false);

   if(KeyGood)
   {
       //列舉出所有的鍵名
       reg->GetKeyNames(sl);
       for(int i=0; i<sl->Count; i++)
       {
           //Memo1->Lines->Add(sl->Strings[i]);
       }
       //列舉所有的值名
       reg->GetValueNames(sl);
       for(int i=0; i<sl->Count; i++)
       {
           //Memo1->Lines->Add(sl->Strings[i]);
           //讀取指定資料值
           sValue = reg->ReadString(sl->Strings[i]);
           //Memo1->Lines->Add(sValue);
           //Memo1->Lines->Add("----------------------------------------------------------------------------------------------------------------");
       }
   }
   reg->CloseKey();
   delete reg;
   delete sl;
}
//---------------------------------------------------------------------------
void ED_ListProcessNameAndID(DWORD processID)//only for WinNT/2000/XP
{
	char szProcessName[MAX_PATH]="unknown";
	//-----------------------------
	// Get a handle to the process.
	HANDLE hProcess=OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE, processID);   //---------------------------------------------------------------------------
	// Get the process name.
	if(NULL!=hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;
		if(EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName));
		}
		else
			return;
	   //---------------------------------------
	   // Print the process name and identifier.
	   //frmMain->Memo2->Lines->Add((AnsiString)szProcessName+", ID: "+IntToStr(processID));
       CloseHandle(hProcess);
       if((AnsiString)szProcessName == "AutoIndicator.exe")
       {
            ShowMessage("AutoIndicator.exe 已執行");
       }
	}
	else
		return;
}
//---------------------------------------------------------------------------
void ED_ListProcess(void)
{

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;
    //Memo2->Lines->Clear();
	 if(!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded ))
	 {      
	 	return;   
	 }   
	 //-------------------------------------------------------
     // Calculate how many process identifiers were returned.
	 cProcesses=cbNeeded/sizeof(DWORD);   
	 //-------------------------------------------------------
     // Print the name and process identifier for each process.   
	 for(i=0;i<cProcesses;i++)
	{      
		ED_ListProcessNameAndID(aProcesses[i]);
	}
}
//---------------------------------------------------------------------------
void ED_ShowLogMsg(String Str,TColor Tc)
{
    if(Str == "d_CLEAR")
    {
        frmMain->rchedt_TestInfo->Clear();
        return;
    }
    frmMain->rchedt_TestInfo->SelAttributes->Color = Tc;
    frmMain->rchedt_TestInfo->Lines->Add(Str);
    frmMain->rchedt_TestInfo->Perform(EM_SCROLLCARET, 0, 0);
}
//---------------------------------------------------------------------------
void ED_ShowBufToHex(int iBufLen,BYTE *baBuf,TMemo *TM)
{
    char caHex[5];
    int i;

    if(iBufLen>=21845)
    {
        ED_ShowLogMsg("Func. Err , Hex Buf Overfolw",clRed);
        TM->Perform(EM_SCROLLCARET, 0, 0);
        return;
    }
	memset(caDest,0x00,65535);
    for(i=0;i<iBufLen;i++)
    {
        sprintf(caHex,"%02X",baBuf[i]);
        strcat(caDest,caHex);
        //Application->ProcessMessages();
    }
    TM->Lines->Add((char *)caDest);
    TM->Perform(EM_SCROLLCARET, 0, 0);
}
//---------------------------------------------------------------------------
void ED_ShowBufToAsci(char *baTitle,BYTE *baBuf,int iBufLen,TColor Tc,TRichEdit *TR)
{
    char caAsci[5],caDest[65535];
    int i;

	if(String(baTitle).Length()>0)
    	ED_ShowLogMsg(String(baTitle),Tc);
    if(iBufLen>=65535)
    {
        ED_ShowLogMsg("Func. Err , Asci Buf Overfolw",clRed);
        TR->Perform(EM_SCROLLCARET, 0, 0);
        return;
    }
    memset(caDest,0x00,65535);
    for(i=0;i<iBufLen;i++)
    {
        sprintf(caAsci,"%c",baBuf[i]);
        strcat(caDest,caAsci);
        Application->ProcessMessages();
    }
    TR->SelAttributes->Color = Tc;
    TR->Lines->Add((char *)caDest);
    TR->Perform(EM_SCROLLCARET, 0, 0);
}
//---------------------------------------------------------------------------
void ED_ShowTxShape(TShape *spTx)
{
    spTx->Brush->Color = clRed;
    ED_Delay(50);
    spTx->Brush->Color = clWhite;
}
//---------------------------------------------------------------------------
void ED_ShowRxShape(TShape *spRx)
{
    spRx->Brush->Color = clLime;
    ED_Delay(50);
    spRx->Brush->Color = clWhite;
}
//---------------------------------------------------------------------------
ULONG PowSixteen(USHORT usP)
{
	ULONG pow;
	USHORT usT;
	pow = 1;
	for(usT=0 ; usT<usP ; usT++)
			pow*=16;
	return pow;
}
//---------------------------------------------------------------------------
BYTE ED_AsciToDEC(BYTE *baBuf,int iBufLen)//Only for ASCII
{
	int i;
    BYTE bDEC,bOutDEC;

	bOutDEC = 0;
	for(i=0 ; i<iBufLen ; i++)
		{
			bDEC = baBuf[i];
			if(bDEC<=70 && bDEC>=65)//A~F
				bDEC-=55;
			else if(bDEC<=57 && bDEC>=48)//0~9
				bDEC-=48;
			else if(bDEC<=102 && bDEC>=97)//a~f
				bDEC-=87;
			else
				bDEC=0;
			bOutDEC += bDEC*PowSixteen(iBufLen-(i+1));
		}
    return bOutDEC;
}
//---------------------------------------------------------------------------
int ED_PackPwd(BYTE *baInputBuf,int iBufLen,BYTE *baOutPutBuf,int iPackLen)
{
	int i,iPwdLen;

    iPwdLen = 0;
	for(i=0;i<iBufLen;i+=iPackLen)
		{
            if((iBufLen-i)>=iPackLen)
    			baOutPutBuf[iPwdLen++] = ED_AsciToDEC(&baInputBuf[i],iPackLen);
            if((iBufLen-i)<iPackLen)
    			baOutPutBuf[iPwdLen++] = ED_AsciToDEC(&baInputBuf[i],(iBufLen-i));
		}
	return iPwdLen;
}
//---------------------------------------------------------------------------
ULONG ED_PackAnyTo1(BYTE *baBufIN,int iAnyLen)
{
	ULONG ulOUT;

	ulOUT = 0;
	switch(iAnyLen)
	{
		case 1:
			ulOUT = (ULONG)baBufIN[0];
            //ulOUT = (ULONG)baBufIN[0];
			break;
		case 2:
			ulOUT = (ULONG)(baBufIN[0]*0x100)+(ULONG)(baBufIN[1]);
            //ulOUT = (ULONG)(baBufIN[0]<<8)+(ULONG)(baBufIN[1]);
			break;
		case 3:
			ulOUT = (ULONG)(baBufIN[0]*0x10000)+(ULONG)(baBufIN[1]*0x100)+(ULONG)(baBufIN[2]);
            //ulOUT = (ULONG)(baBufIN[0]<<16)+(ULONG)(baBufIN[1]<<8)+(ULONG)(baBufIN[2]);
			break;
		case 4:
			ulOUT = (ULONG)(baBufIN[0]*0x1000000)+(ULONG)(baBufIN[1]*0x10000)+(ULONG)(baBufIN[2]*0x100)+(ULONG)(baBufIN[3]);
            //ulOUT = (ULONG)(baBufIN[0]<<24)+(ULONG)(baBufIN[1]<<16)+(ULONG)(baBufIN[2]<<8)+(ULONG)(baBufIN[3]);
			break;
		default:
			break;
	}
	return ulOUT;
}
//---------------------------------------------------------------------------
int ED_Pack1ToAny(ULONG ulValueIN,int iAnyLen,BYTE *baOutBuf)
{
	int iOutBufLen;
	iOutBufLen=0;
	switch(iAnyLen)
	{
		case 1:
			baOutBuf[0] = ulValueIN%0x100;
            //baOutBuf[0] = ulValueIN&0x00FF;
			iOutBufLen=1;
			break;
		case 2:
			baOutBuf[0] = ulValueIN/0x100;
			baOutBuf[1] = ulValueIN%0x100;
			//baOutBuf[0] = ulValueIN>>8;
			//baOutBuf[1] = ulValueIN&0x00FF;
			iOutBufLen=2;
			break;
		case 3:
			baOutBuf[0] = ulValueIN/0x10000;
			baOutBuf[1] = ulValueIN/0x100;
			baOutBuf[2] = ulValueIN%0x100;
			//baOutBuf[0] = ulValueIN>>16;
			//baOutBuf[1] = ulValueIN>>8;
			//baOutBuf[2] = ulValueIN&0x00FF;
			iOutBufLen=3;
			break;
		case 4:
			baOutBuf[0] = ulValueIN/0x1000000;
			baOutBuf[1] = ulValueIN/0x10000;
			baOutBuf[2] = ulValueIN/0x100;
			baOutBuf[3] = ulValueIN%0x100;
			//>>8 = /0x100,>>16 = /0x10000,>>24 = /0x1000000
			//baOutBuf[0] = ulValueIN>>24;
			//baOutBuf[1] = ulValueIN>>16;
			//baOutBuf[2] = ulValueIN>>8;
			//baOutBuf[3] = ulValueIN&0x00FF;
			iOutBufLen=4;
			break;
		default:
			break;
	}
	return iOutBufLen;
}
//---------------------------------------------------------------------------
void ED_GetFixedData(BYTE *bSrcBuf,USHORT uSrcLen,USHORT uStartAddr,USHORT uFixedLen,BYTE *bDestBuf)
{
	USHORT i;
	BYTE bTemp[512];

	memset(bDestBuf,0x00,sizeof(bDestBuf));
	memset(bTemp,0x00,sizeof(bTemp));
	if((uSrcLen<=0) && (uFixedLen>0))
	{
		uFixedLen = 0;
		return;
	}
	if((uStartAddr+uFixedLen) > uSrcLen)
		uFixedLen = uSrcLen-uStartAddr;
	
	for(i=uStartAddr ; i<(uStartAddr+uFixedLen) ; i++)
			bTemp[i-uStartAddr] = bSrcBuf[i];
		memcpy(bDestBuf,bTemp,uFixedLen);
}
//---------------------------------------------------------------------------
ULONG  ToUnixTime(int iYear, int iMonth, int iDate, int iHour, int iMin, int iSec)
{
		int		iDaysofMonth[] = {  0,  31,  59,  90, 120, 151, 181, 212, 243, 273, 304, 334};		
		int		iTemp;
		ULONG	lSec;
		
		iTemp = iYear - 1970;
		if (iYear % 4 == 0)
			iDaysofMonth[iMonth-1]++;
		lSec = (iTemp+2)/4+iTemp*365 + iDaysofMonth[iMonth-1] + iDate-1;
		lSec = lSec * 24 + iHour;   //-8;
		lSec = lSec * 60 + iMin;
		lSec = lSec * 60 + iSec;
		return lSec;
}
//---------------------------------------------------------------------------
void GetUnixTime (BYTE *baTime)
{
	//CIT_RTC stRTC;
	ULONG	ulUT;
	
	//CIT_GetRealTimeClock(&stRTC);
	//ulUT = ToUnixTime(stRTC.bYear+2000, stRTC.bMonth, stRTC.bDay, stRTC.bHour, stRTC.bMinute, stRTC.bSecond);
	ED_Pack1ToAny(ulUT,4,baTime);
}
//---------------------------------------------------------------------------
// 重新開機
void ED_RestartPC(void)
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken);

    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges(hToken,false,&tkp,0,(PTOKEN_PRIVILEGES)NULL,0);
    ExitWindowsEx(EWX_REBOOT | EWX_FORCE,0);
}
//---------------------------------------------------------------------------
// 結束作業系統，並關閉電源 （僅支援ATX 規格）
void ED_ShutdownPC(void)
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken);

    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges(hToken,false,&tkp,0,(PTOKEN_PRIVILEGES)NULL,0);
    ExitWindowsEx(EWX_POWEROFF | EWX_FORCE,0);
}
//---------------------------------------------------------------------------
// 登出, 重新登入使用者
void ED_LogoffPC(void)
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken);

    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges(hToken,false,&tkp,0,(PTOKEN_PRIVILEGES)NULL,0);
    ExitWindowsEx(EWX_LOGOFF | EWX_FORCE,0);
}
//---------------------------------------------------------------------------
//取得程式版本
void ED_GetProgramVersion(char *cVer)
{
    strcpy(cVer,d_VERSION);
}
//---------------------------------------------------------------------------

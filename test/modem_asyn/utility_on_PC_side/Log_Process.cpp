//---------------------------------------------------------------------------


#pragma hdrstop
#include <vcl.h>
#include "Log_Process.h"
#include "Main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *iFileHandle;
#define d_MAX_LOG_FILE_SIZE 1048576  //1024k
//---------------------------------------------------------------------------
int CheckFileSize(String FileName)
{
    TSearchRec SearchRec;

    if (!FileExists(FileName))
    {
        //ShowMessage("File Not Found");
        return 0;
    }
    if (FindFirst(FileName, faAnyFile, SearchRec) == 0)
    {
        return SearchRec.Size;
    }
    return 0;
}
//---------------------------------------------------------------------------
void SaveLogFile(String Stitle,int iLen,BYTE *baBuf)
{
    int i,ibak;
    char caHex[10],caTemp[65535];
    memset(caTemp,0x00,65535);
    String DirNamePath,FileNamePath,NewFileNamePath;

    if(frmMain->ChkBox_SetLog->Checked == false)
        return;
    DirNamePath = ".\\Log";
    if (!DirectoryExists(DirNamePath))
        ForceDirectories(DirNamePath);
    DirNamePath+="\\";
    FileNamePath = DirNamePath+String(FormatDateTime("yyyymmdd", Now()))+".log";
    //Check Log File Size
    ibak = 1;
    if(CheckFileSize(FileNamePath)>=d_MAX_LOG_FILE_SIZE)
    {
        while(1)
        {
            NewFileNamePath = DirNamePath+String(FormatDateTime("yyyymmdd", Now()))+"_"+IntToStr(ibak)+".log";;
            if (FileExists(NewFileNamePath))
                ibak++;
            else
                break;
        }
        RenameFile(FileNamePath,NewFileNamePath);
    }

    for(i=0;i<iLen;i++)
    {
        sprintf(caHex,"%02X",baBuf[i]);
        strcat(caTemp,caHex);
    }
    iLen*=2;

    //Create and Write Log File
    iFileHandle = fopen(FileNamePath.c_str(),"at");//Open for Txt writing at end-of-file or create for writing if the file does not exist.
    if(iFileHandle != NULL)
    {
        fwrite(Stitle.c_str(),Stitle.Length(),1,iFileHandle);
        fwrite(caTemp,iLen,1,iFileHandle);
    }

    fclose(iFileHandle);
}
//---------------------------------------------------------------------------
void SaveAscIILogFile(String Stitle,int iLen,BYTE *baBuf)
{
    int i,ibak;
    char caHex[10],caTemp[65535];
    memset(caTemp,0x00,65535);
    String DirNamePath,FileNamePath,NewFileNamePath;

    if(frmMain->ChkBox_SetLog->Checked == false)
        return;
    DirNamePath = ".\\Log";
    if (!DirectoryExists(DirNamePath))
        ForceDirectories(DirNamePath);
    DirNamePath+="\\";
    FileNamePath = DirNamePath+String(FormatDateTime("yyyymmdd", Now()))+".log";
    //Check Log File Size
    ibak = 1;
    if(CheckFileSize(FileNamePath)>=d_MAX_LOG_FILE_SIZE)
    {
        while(1)
        {
            NewFileNamePath = DirNamePath+String(FormatDateTime("yyyymmdd", Now()))+"_"+IntToStr(ibak)+".log";;
            if (FileExists(NewFileNamePath))    
                ibak++;
            else
                break;
        }
        RenameFile(FileNamePath,NewFileNamePath);
    }
    //Create and Write Log File
    iFileHandle = fopen(FileNamePath.c_str(),"at");//Open for Txt writing at end-of-file or create for writing if the file does not exist.
    if(iFileHandle != NULL)
    {
        fwrite(Stitle.c_str(),Stitle.Length(),1,iFileHandle);
        fwrite(baBuf,iLen,1,iFileHandle);
    }

    fclose(iFileHandle);
}

#pragma package(smart_init)

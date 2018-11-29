//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "public.h"
#include "RS232.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
#define d_RX_MAX_LEN 20480
#define d_TX_MAX_LEN 2048
String sCOMPortA,sCOMPortB,sCOMPortC,sCOMPortD;
ULONG ulBaudRateA,ulBaudRateB,ulBaudRateC,ulBaudRateD;
BYTE bParityA,bDataBitA,bStopBitA;
BYTE bParityB,bDataBitB,bStopBitB;
BYTE bParityC,bDataBitC,bStopBitC;
BYTE bParityD,bDataBitD,bStopBitD;
BYTE baTmp[20];
int icounterA,icounterB,icounterC,icounterD;
int iRxLenA,iRxLenB,iRxLenC,iRxLenD;
int iTxLenA,iTxLenB,iTxLenC,iTxLenD;
int iRxTotalLenA,iRxTotalLenB,iRxTotalLenC,iRxTotalLenD;
char caTmpA[d_RX_MAX_LEN],caTmpB[d_RX_MAX_LEN],caTmpC[d_RX_MAX_LEN],caTmpD[d_RX_MAX_LEN];
char caTxBufA[d_TX_MAX_LEN],caTxBufB[d_TX_MAX_LEN],caTxBufC[d_TX_MAX_LEN],caTxBufD[d_TX_MAX_LEN];
char caRxBufA[d_RX_MAX_LEN],caRxBufB[d_RX_MAX_LEN],caRxBufC[d_RX_MAX_LEN],caRxBufD[d_RX_MAX_LEN];
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
    frmMain->Left=(Screen->Width-frmMain->Width)/2;
    frmMain->Top=(Screen->Height-frmMain->Height)/6;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::bbtn_OpenAClick(TObject *Sender)
{
    sCOMPortA = "COM"+IntToStr(rdgp_RS232A->ItemIndex+1);
    ulBaudRateA = StrToInt(cbox_BaudrateA->Text);
    memset(baTmp,0x00,20);
    memcpy(baTmp,cbox_ParityA->Text.c_str(),cbox_ParityA->Text.Length());
    bParityA = (BYTE)baTmp[0];
    memcpy(baTmp,cbox_DataBitA->Text.c_str(),cbox_DataBitA->Text.Length());
    bDataBitA = (BYTE)baTmp[0];
    memcpy(baTmp,cbox_StopBitA->Text.c_str(),cbox_StopBitA->Text.Length());
    bStopBitA = (BYTE)baTmp[0];
    if(Ed_InitialRS232(sCOMPortA,ulBaudRateA,bParityA,bDataBitA,bStopBitA)==d_OK)
    {
        ShowLogMsg("d_CLEAR",clGreen,0x41);
        ShowLogMsg(sCOMPortA+" Open OK",clGreen,0x41);
        ShowLogMsg("Baudrate: "+IntToStr(ulBaudRateA),clGreen,0x41);
        tmrRxA->Enabled = true;
        bbtn_OpenA->Enabled = false;
        bbtn_CloseA->Enabled = true;
    }
    else
    {
        ShowLogMsg("d_CLEAR",clGreen,0x41);
        ShowLogMsg(sCOMPortA+" Open NG",clRed,0x41);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::tmrRxATimer(TObject *Sender)
{
    //Rx
    if(Ed_CheckRS232(sCOMPortA)!=d_FAILED)
    {
        spRxA->Brush->Color = clLime;
        iRxLenA = Ed_ModemReadFile(sCOMPortA,caTmpA);
        memcpy(&caRxBufA[iRxTotalLenA],&caTmpA[0],iRxLenA);
        iRxTotalLenA+=iRxLenA;
        edt_RXLenA->Text = iRxTotalLenA;
        icounterA = 0;
    }
    else
    {
        icounterA++;
        spRxA->Brush->Color = clWhite;
        edt_counterA->Text = icounterA;
        if(icounterA == 1 && iRxTotalLenA>0)
        {
            ShowBufToHex(iRxTotalLenA,caRxBufA,mRxA);
        }
        if(RdoBtn_AutoReverseA->Checked == true && iRxTotalLenA>0 && icounterA == 5)
        {
            spTxA->Brush->Color = clRed;
            iTxLenA = Ed_ModemWriteFile(sCOMPortA,iRxTotalLenA,caRxBufA);
            ShowBufToHex(iTxLenA,caRxBufA,mTxA);
            edt_TXLenA->Text = iTxLenA;
            Delay(25);
            spTxA->Brush->Color = clWhite;
            memset(caRxBufA,0x00,d_RX_MAX_LEN);
            iRxTotalLenA = 0;
        }
        if(RdoBtn_AutoReverseA->Checked == false)
            iRxTotalLenA = 0;
        memset(caTmpA,0x00,d_RX_MAX_LEN);
    }
    if(mRxA->Lines->Count >=edt_ClearLinesA->Text.ToInt())
        mRxA->Clear();
    if(mTxA->Lines->Count >=edt_ClearLinesA->Text.ToInt())
        mTxA->Clear();
    tmrTxA->Interval = edt_DelayA->Text.ToInt()*1000;
    if(RdoBtn_AutoSendA->Checked == true)
        tmrTxA->Enabled = true;
    else
        tmrTxA->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::bbtn_CloseAClick(TObject *Sender)
{
    tmrRxA->Enabled = false;
    tmrTxA->Enabled = false;
    Ed_FlushTxRS232(sCOMPortA);
    Ed_FlushRxRS232(sCOMPortA);
    spTxA->Brush->Color = clWhite;
    spRxA->Brush->Color = clWhite;
    Ed_CloseRS232(sCOMPortA);
    icounterA = 0;
    ShowLogMsg("d_CLEAR",clGreen,0x41);
    ShowLogMsg(sCOMPortA+"  Close",clGreen,0x41);
    bbtn_OpenA->Enabled = true; 
    bbtn_CloseA->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::bbtn_ClearAClick(TObject *Sender)
{
    mRxA->Clear();
    mTxA->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tmrTxATimer(TObject *Sender)
{
    spTxA->Brush->Color = clRed;
    iTxLenA = Ed_ModemWriteFile(sCOMPortA,mTxA->Text.Length(),mTxA->Text.c_str());

    edt_TXLenA->Text = iTxLenA;
    Delay(25);
    spTxA->Brush->Color = clWhite;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mTxAKeyPress(TObject *Sender, char &Key)
{
    if (Key!=13) return;
    spTxA->Brush->Color = clRed;
    iTxLenA = Ed_ModemWriteFile(sCOMPortA,mTxA->Text.Length(),mTxA->Text.c_str());

    edt_TXLenA->Text = iTxLenA;
    Delay(25);
    spTxA->Brush->Color = clWhite;
}
//---------------------------------------------------------------------------




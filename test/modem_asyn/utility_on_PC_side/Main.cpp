//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "About.h"
#include "RS232.h"
#include "PUBLIC.h"
#include "Log_Process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;

#define d_RX_MAX_LEN 10240
#define d_TX_MAX_LEN 10240
#define d_TX_YES        0
#define d_TX_NO         1
#define d_AUTO_REVERSE  2
#define d_AUTO_SEND     3
#define d_INCREASE_LEN  4
#define d_FIXED_LEN     5
#define d_CUSTOM_LEN    6
BYTE bModemCheck, bDialUpCheck, bDialClose;
BYTE baTestData[2048];
BYTE baModemRxData[4096];
BYTE baEthernetBuf[4096];
int iInputLen, iTotalEthernetLen;
int iRSRxLen;
//**********232
String sCOMPort, sCOMPort1;
//ULONG ulBaudRate;
BYTE baTmp[20];
BYTE bParity, bDataBit, bStopBit;
//int iRxLen, iTxLen;
int iRxLenA;
//char caTmp[2048*5];
BYTE caTmpA[1024];
//***********232


HANDLE ModemhComm;
extern HANDLE hComm232[256];
extern int iSTOP;
int iTimer;
int iConnect,iListenOK,iDialupOK,iFlashMsg,iKeyPress,iSpeakerVol,iRedial,iRedialNow,iQuerySensitive,iDialupSpeed;
int icounter,iRxLen,iTxLen,iIncreaseTxLen,iFixedTxLen,iCustomTxLen,iRxTotalLen,iDLETxLen;
char caTmp[d_RX_MAX_LEN],caTxBuf[d_TX_MAX_LEN],caRxBuf[d_RX_MAX_LEN];
char caTxDLE[d_TX_MAX_LEN*2];
SHORT sC;
String sModemPort;
ULONG ulBaudRate;
BYTE bTxMode;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
    frmMain->Left=(Screen->Width-frmMain->Width)/2;
    frmMain->Top=(Screen->Height-frmMain->Height)/20;
    frmMain->Top=-10;
    tmrModemStatus->Enabled = true;
    tkbar_SpeakerVol->Position = 3;
    tkbar_QuerySensitive->Position = 29;
    tkbar_DialupSpeed->Position = 95;
    gpbox_Utility_Setting->Height = 0;
    bDialUpCheck = 0;
    bDialClose = 0;
    memset(baModemRxData, 0x0, 2048);
    //iRxTotalLen = 0;
}
//---------------------------------------------------------------------------
void GP_UnpackData(unsigned char *baSBuf,int uiLen,unsigned char *baTBuf)
{
  int i;
  char cMe[4];
  strcpy(baTBuf,"");
  for(i=0;i<uiLen;i++)
  {
     sprintf(cMe,"%02X ",baSBuf[i]);
     strcat(baTBuf,cMe);
  }
}

void MapTxData(void)
{
    BYTE LRC,Input[1024];
    int i,iC;
    int iMin,iMax;
    int iLoop;
    iMin = 0;
    iMax = 0;
    memset(Input,0x00,1024);
    memset(caTxBuf,0x00,d_TX_MAX_LEN);
    memset(caTxDLE,0x00,d_TX_MAX_LEN*2);
    //0x??~0x??
    if(frmMain->RdoBtn_Data1->Checked == true)
    {
        iMin = ED_AsciToDEC(frmMain->edt_Min->Text.c_str(),frmMain->edt_Min->Text.Length());
        iMax = ED_AsciToDEC(frmMain->edt_Max->Text.c_str(),frmMain->edt_Max->Text.Length());
        iC = iMin;
	    for(i=0;i<d_TX_MAX_LEN;i++)
	    {
            caTxBuf[i] = iC++;
	        if(iC>iMax)
	            iC = iMin;
	    }
    }
    //Fill data with 0x??
    if(frmMain->RdoBtn_Data2->Checked == true)
    {
        iC = ED_AsciToDEC(frmMain->edt_Fill->Text.c_str(),frmMain->edt_Fill->Text.Length());
        memset(caTxBuf,iC,d_TX_MAX_LEN);
    }                        
    //Input by manual
    if(frmMain->RdoBtn_CustomLen->Checked == true)
    {
        memcpy(&Input[0],frmMain->edt_CustomData->Text.c_str(),frmMain->edt_CustomData->Text.Length());
        for(i=0;i<frmMain->edt_CustomData->Text.Length();i+=2)
            caTxBuf[i/2] = ED_AsciToDEC(&Input[i],2);
        iCustomTxLen = (frmMain->edt_CustomData->Text.Length())/2;
    }
    //For DLE Protocol
    if(frmMain->chkbox_DLE_Data->Checked == true)
    {
        LRC = 0;
        iDLETxLen = 0;
        caTxDLE[iDLETxLen++] = 0x10;
        caTxDLE[iDLETxLen++] = 0x02;
        if(frmMain->RdoBtn_StartLen->Checked == true)
            iLoop = iIncreaseTxLen;
        if(frmMain->RdoBtn_FixedLen->Checked == true)
            iLoop = iFixedTxLen;
        if(frmMain->RdoBtn_CustomLen->Checked == true)
            iLoop = iCustomTxLen;
        for(i=0;i<iLoop;i++)
        {
            LRC^= caTxBuf[i];
            if(caTxBuf[i] != 0x10)
                caTxDLE[iDLETxLen++] = caTxBuf[i];
            else
            {
                caTxDLE[iDLETxLen++] = 0x10;
                caTxDLE[iDLETxLen++] = 0x10;
            }
        }
        caTxDLE[iDLETxLen++] = LRC;
        if (LRC == 0x10)
            caTxDLE[iDLETxLen++] = LRC;
        caTxDLE[iDLETxLen++] = 0x10;
        caTxDLE[iDLETxLen++] = 0x03;
    }
}
//---------------------------------------------------------------------------
void ChkTxMode(void)
{
    if(frmMain->chkbox_EnableTx->Checked == true || frmMain->chkbox_EnableTx_Directly->Checked == true)
    {
        if(frmMain->RdoBtn_AutoReverse->Checked == true && frmMain->RdoBtn_AutoReverse->Enabled == true)
            bTxMode = d_AUTO_REVERSE;
        else if(frmMain->RdoBtn_StartLen->Checked == true)
            bTxMode = d_INCREASE_LEN;
        else if(frmMain->RdoBtn_FixedLen->Checked == true)
            bTxMode = d_FIXED_LEN;
        else if(frmMain->RdoBtn_CustomLen->Checked == true)
            bTxMode = d_CUSTOM_LEN;
        return;
    }
    if(frmMain->chkbox_EnableTx->Checked == false && frmMain->chkbox_EnableTx_Directly->Checked == false)
    {
        if(frmMain->chkbox_TxYes->Checked == true)
            bTxMode = d_TX_YES;
        if(frmMain->chkbox_TxNo->Checked == true)
            bTxMode = d_TX_NO;
    }
}
//---------------------------------------------------------------------------
void Initial(void)
{
    icounter = 0;
    iRxTotalLen = 0;
    iRedialNow = 0;
    iRedial = false;
    iConnect = false;
    iListenOK = false;
    iDialupOK = false;
    iFlashMsg = false;
    frmMain->mTX->Clear();
    frmMain->mRX->Clear();
    frmMain->edt_RXLen->Text = "";
    frmMain->edt_TXLen->Text = "";
    frmMain->tmrQuery->Enabled = false;
    frmMain->tmrRx->Enabled = false;
    memset(caTmp,0x00,d_RX_MAX_LEN);
    memset(caTxBuf,0x00,d_TX_MAX_LEN);
    memset(caRxBuf,0x00,d_RX_MAX_LEN);
    sModemPort = "COM"+IntToStr(frmMain->rdgp_COM->ItemIndex+1);
    ulBaudRate = StrToInt(frmMain->cbox_Baudrate->Text);
    ModemhComm = hComm232[ED_GetCOMIndex(sModemPort)];
    ED_CloseRS232(sModemPort);
    iIncreaseTxLen = frmMain->edt_StartLen->Text.ToInt();
    iFixedTxLen = frmMain->edt_FixedLen->Text.ToInt();
    iCustomTxLen = (frmMain->edt_CustomData->Text.Length())/2;
    //MapTxData();
    ChkTxMode();
}
//---------------------------------------------------------------------------
void CheckLenSelect(void)
{
    if(frmMain->RdoBtn_StartLen->Checked == true)
    {
       frmMain->RdoBtn_Data1->Enabled = true;
       frmMain->RdoBtn_Data2->Enabled = true;
       frmMain->edt_StartLen->Enabled = true;
       frmMain->Label3->Enabled = true;
       frmMain->edt_FixedLen->Enabled = false;
       frmMain->Label4->Enabled = false;
       frmMain->edt_CustomData->Enabled = false;
    }
    else if(frmMain->RdoBtn_FixedLen->Checked == true)
    {
       frmMain->RdoBtn_Data1->Enabled = true;
       frmMain->RdoBtn_Data2->Enabled = true;
       frmMain->edt_StartLen->Enabled = false;
       frmMain->Label3->Enabled = false;
       frmMain->edt_FixedLen->Enabled = true;
       frmMain->Label4->Enabled = true;
       frmMain->edt_CustomData->Enabled = false;
    }
    else if(frmMain->RdoBtn_CustomLen->Checked == true)
    {
       frmMain->RdoBtn_Data1->Checked = false;
       frmMain->RdoBtn_Data2->Checked = false;
       frmMain->RdoBtn_Data1->Enabled = false;
       frmMain->RdoBtn_Data2->Enabled = false;
       frmMain->edt_StartLen->Enabled = false;
       frmMain->Label3->Enabled = false;
       frmMain->edt_FixedLen->Enabled = false;
       frmMain->Label4->Enabled = false;
       frmMain->edt_CustomData->Enabled = true;
       frmMain->edt_CustomData->SetFocus();
    }
}
//---------------------------------------------------------------------------
void EnableAutoSend(void)
{
    frmMain->RdoBtn_StartLen->Enabled = true;
    frmMain->RdoBtn_FixedLen->Enabled = true;
    frmMain->RdoBtn_CustomLen->Enabled = true;
    frmMain->chkbox_DLE_Data->Enabled = true;
    frmMain->RdoBtn_Data1->Enabled = true;
    frmMain->RdoBtn_Data2->Enabled = true;
    frmMain->edt_Min->Enabled = true;
    frmMain->Label6->Enabled = true;
    frmMain->edt_Max->Enabled = true;
    frmMain->edt_Fill->Enabled = true;
    CheckLenSelect();
}
//---------------------------------------------------------------------------
void DisableAutoSend(void)
{
    frmMain->RdoBtn_StartLen->Enabled = false;
    frmMain->RdoBtn_FixedLen->Enabled = false;
    frmMain->RdoBtn_CustomLen->Enabled = false;
    frmMain->edt_StartLen->Enabled = false;
    frmMain->Label3->Enabled = false;
    frmMain->edt_FixedLen->Enabled = false;
    frmMain->Label4->Enabled = false;
    frmMain->chkbox_DLE_Data->Checked = false;
    frmMain->chkbox_DLE_Data->Enabled = false;
    frmMain->RdoBtn_Data1->Enabled = false;
    frmMain->RdoBtn_Data2->Enabled = false;
    frmMain->edt_Min->Enabled = false;
    frmMain->Label6->Enabled = false;
    frmMain->edt_Max->Enabled = false;
    frmMain->edt_Fill->Enabled = false;
    frmMain->edt_CustomData->Enabled = false;
}
//---------------------------------------------------------------------------
void EnableTx(void)
{
    frmMain->RdoBtn_AutoReverse->Enabled = true;
    frmMain->RdoBtn_AutoSend->Enabled = true;
    frmMain->edt_TxDelayTime->Enabled = true;
    frmMain->chkbox_EnableTx_Directly->Checked = false;
    frmMain->chkbox_OnLineChat->Checked = false;
    if(frmMain->RdoBtn_AutoReverse->Checked == true)
        DisableAutoSend();
    if(frmMain->RdoBtn_AutoSend->Checked == true)
        EnableAutoSend();
}
//---------------------------------------------------------------------------
void DisableTx(void)
{
    frmMain->RdoBtn_AutoReverse->Enabled = false;
    frmMain->RdoBtn_AutoSend->Enabled = false;
    frmMain->edt_TxDelayTime->Enabled = false;
    DisableAutoSend();
}
//---------------------------------------------------------------------------
void EnableTxDirectly(void)
{
    DisableTx();
    frmMain->chkbox_OnLineChat->Checked = false;
    frmMain->chkbox_EnableTx->Checked = false;
    frmMain->Label1->Enabled = true;
    frmMain->edt_AutoSend_Time->Enabled = true;
    frmMain->Label2->Enabled = true;
    frmMain->RdoBtn_StartLen->Enabled = true;
    frmMain->RdoBtn_FixedLen->Enabled = true;
    frmMain->RdoBtn_CustomLen->Enabled = true;
    frmMain->chkbox_DLE_Data->Enabled = true;
    frmMain->RdoBtn_Data1->Enabled = true;
    frmMain->RdoBtn_Data2->Enabled = true;
    frmMain->edt_Min->Enabled = true;
    frmMain->Label6->Enabled = true;
    frmMain->edt_Max->Enabled = true;
    frmMain->edt_Fill->Enabled = true;
    CheckLenSelect();
}
//---------------------------------------------------------------------------
void DisableTxDirectly(void)
{
    frmMain->Label1->Enabled = false;
    frmMain->edt_AutoSend_Time->Enabled = false;
    frmMain->Label2->Enabled = false;
    frmMain->RdoBtn_StartLen->Enabled = false;
    frmMain->RdoBtn_FixedLen->Enabled = false;
    frmMain->RdoBtn_CustomLen->Enabled = false;
    frmMain->edt_StartLen->Enabled = false;
    frmMain->Label3->Enabled = false;
    frmMain->edt_FixedLen->Enabled = false;
    frmMain->Label4->Enabled = false;
    frmMain->tmrTx->Enabled = false;

    frmMain->chkbox_DLE_Data->Checked = false;
    frmMain->chkbox_DLE_Data->Enabled = false;
    frmMain->RdoBtn_Data1->Enabled = false;
    frmMain->RdoBtn_Data2->Enabled = false;
    frmMain->edt_Min->Enabled = false;
    frmMain->Label6->Enabled = false;
    frmMain->edt_Max->Enabled = false;
    frmMain->edt_Fill->Enabled = false;
    frmMain->edt_CustomData->Enabled = false;
}
//---------------------------------------------------------------------------
void WriteATCmd(String sComNo,String sATCmd)
{
    unsigned long lrc;

    ModemhComm = hComm232[ED_GetCOMIndex(sComNo)];
    if (ModemhComm==0) return;
    if(sATCmd!="+++")
    {
        sATCmd+="\r";
        WriteFile(ModemhComm,sATCmd.c_str(),sATCmd.Length(), &lrc, NULL);
    }
}
//---------------------------------------------------------------------------
BYTE ModemListen(String sComNo)
{
    int i,iOK;
    String sListenInitCmd,sATCmdBody,sRingCallNum,sSpeakerOnOff,sSpeakerVol;
    String sEndATCmd;
    sListenInitCmd = frmMain->edt_ListenInitCmd->Text.c_str();
    sRingCallNum = " S0="+frmMain->edt_RingCallNum->Text;

    if(frmMain->RdoBtn_Cmd1->Checked == true)
        sATCmdBody = frmMain->edt_ATCmd1->Text.c_str();
    if(frmMain->RdoBtn_Cmd2->Checked == true)
        sATCmdBody = frmMain->edt_ATCmd2->Text.c_str();

    switch(iSpeakerVol)
    {
        case 0:
            sSpeakerVol = " L0";
            break;
        case 1:
            sSpeakerVol = " L1";
            break;
        case 2:
            sSpeakerVol = " L2";
            break;
        case 3:
            sSpeakerVol = " L3";
            break;
    }
    if(frmMain->RdoBtn_SpeakerOn->Checked == true)
        sSpeakerOnOff = " M1";
    else
        sSpeakerOnOff = " M0";
    sEndATCmd = frmMain->edt_EndATCmd->Text.c_str();

    ED_FlushRxRS232(sComNo);
    frmMain->spTX->Brush->Color = clBlue;
    WriteATCmd(sComNo,sListenInitCmd+sRingCallNum);
    //WriteATCmd(sComNo,"AT &F E0 V1 &D2 &C1 S0=1");
    ED_Delay(200);
    frmMain->spRX->Brush->Color = clBlue;
    WriteATCmd(sComNo,sATCmdBody+sSpeakerVol+sSpeakerOnOff);

    /*
    if(frmMain->RdoBtn_SpeakerOn->Checked == true)
    {
        if(frmMain->RdoBtn_Cmd1->Checked == true)
            WriteATCmd(sComNo,"AT S07=150 S09=015 S10=023 S30=0 L1 M1");
        if(frmMain->RdoBtn_Cmd2->Checked == true)
            WriteATCmd(sComNo,"AT S7=40 S30=0 L1 M1");
    }
    else if(frmMain->RdoBtn_SpeakerOff->Checked == true)
    {
        if(frmMain->RdoBtn_Cmd1->Checked == true)
            WriteATCmd(sComNo,"AT S07=150 S09=015 S10=023 S30=0 L1 M0");
        if(frmMain->RdoBtn_Cmd2->Checked == true)
            WriteATCmd(sComNo,"AT S7=40 S30=0 L1 M0");
    }*/
    ED_Delay(200);
    //WriteATCmd(sComNo,"AT %C1 &K3 N1 X4");
    WriteATCmd(sComNo,sEndATCmd);
    frmMain->spTX->Brush->Color = clWhite;
    ED_Delay(200);

    iOK = 0;
    memset(caTmp,0x00,d_RX_MAX_LEN);
    iRxLen = ED_RS232ReadFile(sModemPort,caTmp);
    frmMain->edt_RXLen->Text = iRxLen;
    //frmMain->mRX->Text = frmMain->mRX->Text+caTmp;
    frmMain->spRX->Brush->Color = clWhite;
    for(i=0;i<iRxLen-2;i++)
    {
          if((caTmp[i]==0x4F) && (caTmp[i+1]==0x4B))
             iOK++;
    }
    if(iOK >= 3)
        return d_OK;
    return d_FAILED;
}
//---------------------------------------------------------------------------
void ModenHangUp(String sComNo)
{
  ModemhComm = hComm232[ED_GetCOMIndex(sComNo)];
  if (ModemhComm==0) return;
  WriteATCmd(sComNo,"+++");
  ED_Delay(200);
  WriteATCmd(sComNo,"AT H0");
}
//---------------------------------------------------------------------------
void ModemDialUp(String sComNo)
{
    String ATDTCmd,sSpeakersOnOff,sDialupInitCmd,sDialupSpeed;

    frmMain->spTX->Brush->Color = clBlue;
    if(frmMain->edt_DialupInitCmd->Text.Length()>0)
    {
        sDialupInitCmd = frmMain->edt_DialupInitCmd->Text.c_str();
        WriteATCmd(sComNo,sDialupInitCmd);
        ED_Delay(100);
    }
    if(frmMain->RdoBtn_SpeakerOn->Checked == true)
        sSpeakersOnOff = "AT M1";
        //WriteATCmd(sComNo,"AT M1");
    if(frmMain->RdoBtn_SpeakerOn->Checked == false)
        //WriteATCmd(sComNo,"AT M0");
        sSpeakersOnOff = "AT M0";
    sDialupSpeed = " S11="+IntToStr(iDialupSpeed);
    WriteATCmd(sComNo,sSpeakersOnOff+sDialupSpeed);
    ED_Delay(100);
    ATDTCmd = "ATDT"+frmMain->edt_PhoneNum->Text;
    WriteATCmd(sComNo,ATDTCmd);
    ED_Delay(100);
    frmMain->spTX->Brush->Color = clWhite;
}
//---------------------------------------------------------------------------
void ModemQuery(String sComNo)
{
    String sQuery;

    sQuery = frmMain->edt_QueryATCmd->Text.c_str();
    frmMain->mRX->Clear();
    ModemhComm = hComm232[ED_GetCOMIndex(sComNo)];
    if (ModemhComm==0) return;
    ED_SetDTR(sComNo,d_ON);
    ED_SetRTS(sComNo,d_ON);
    frmMain->spTX->Brush->Color = clBlue;
    ED_Delay(200);
    //WriteATCmd(sComNo,"AT E1 V1 I1 I2 I3 I4 I5 I6 I7");
    WriteATCmd(sComNo,sQuery);
    frmMain->spTX->Brush->Color = clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::bbtn_QueryClick(TObject *Sender)
{
    Initial();
    ED_ShowLogMsg("d_CLEAR",clLime);
    if(ED_ExInitialRS232(sModemPort,ulBaudRate)==d_OK)
    {
        ED_ShowLogMsg("\n"+sModemPort+" Open OK",clLime);
        ED_ShowLogMsg("Baudrate: "+IntToStr(ulBaudRate),clLime);
        edt_counter->Text = "";
        bbtn_Query->Enabled = false;
        tmrQuery->Enabled = true;
        ModemQuery(sModemPort);
    }
    else
    {
        ED_ShowLogMsg("\n"+sModemPort+" Open NG",clRed);
        ED_ShowLogMsg("Baudrate: "+IntToStr(ulBaudRate),clRed);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::tmrQueryTimer(TObject *Sender)
{
    if(ED_CheckRS232(sModemPort)!=d_FAILED)
    {
        sC = ED_GetRS232(sModemPort);
        if(sC!=d_NO_DATA)
        {
            spRX->Brush->Color = clBlue;
            memset(caTmp,0x00,1024);
            iRxLen = ED_RS232ReadFile(sModemPort,caTmp);
            mRX->Text = mRX->Text+caTmp;
            iRxTotalLen+=iRxLen;
            edt_RXLen->Text = iRxTotalLen;
        }
    }
    else
    {
        spRX->Brush->Color = clWhite;
        if(iRxTotalLen>iQuerySensitive)
        {
            ED_CloseRS232(sModemPort);
            tmrQuery->Enabled = false;
            bbtn_Query->Enabled = true;
            bbtn_Listen->Enabled = true;
            bbtn_DialUp->Enabled = true;
            ED_ShowLogMsg("Modem Found",clLime);
        }
        else
        {
            if(icounter>5)
            {
                ED_CloseRS232(sModemPort);
                tmrQuery->Enabled = false;
                bbtn_Query->Enabled = true;
                bbtn_Listen->Enabled = false;
                bbtn_DialUp->Enabled = false;
                ED_ShowLogMsg("Modem Not Found",clRed);
            }
        }
    }
    icounter++;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::bbtn_ListenClick(TObject *Sender)
{
    Initial();

    ED_ShowLogMsg("d_CLEAR",clLime);
    if(ED_ExInitialRS232(sModemPort,ulBaudRate)==d_OK)
    {
        ED_ShowLogMsg("\n"+sModemPort+" Open OK",clLime);
        ED_ShowLogMsg("Baudrate: "+IntToStr(ulBaudRate),clLime);
        if(ModemListen(sModemPort) == d_OK)
        {
            ED_ShowLogMsg("Listen Ready !",clLime);
            sp_AA->Brush->Color = clRed;
            tmrRx->Enabled = true;
            bbtn_Query->Enabled = false;
            bbtn_Listen->Enabled = false;
            bbtn_DialUp->Enabled = false;
            bbtn_Stop->Enabled = true;
            iListenOK = true;
        }
        else
        {
            ED_ShowLogMsg("Listen Not Ready.",clRed);
            sp_AA->Brush->Color = clWhite;
        }
    }
    else
    {
        ED_ShowLogMsg("\n"+sModemPort+" Open NG",clRed);
        ED_ShowLogMsg("Baudrate: "+IntToStr(ulBaudRate),clRed);
    }
}
void ClearRxBuf(void)
{
    //ED_ShowLogMsg("Clear Rx Buf",clRed);
    memset(caRxBuf,0x00,d_RX_MAX_LEN);
    iRxTotalLen = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::tmrRxTimer(TObject *Sender)
{
    char caDataBuf[1024];//0427
    bModemCheck = 0;//0428
    int i;
    ChkTxMode();
    iTimer++;


    //Check On Line
    if((ED_GetCD(sModemPort) == d_ON) && (iConnect == false))
    {
        ED_ShowLogMsg("d_CLEAR",clLime);
        iRxLen = ED_RS232ReadFile(sModemPort,caRxBuf);
        edt_RXLen->Text = iRxLen;
        ED_ShowLogMsg(caRxBuf,clLime);
        ED_ShowLogMsg("Modem ON Line",clLime);
        SaveAscIILogFile("\n[Modem ON Line]",0,"");
        SaveAscIILogFile("\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now())),iRxLen,caRxBuf);
        SaveAscIILogFile("\n================================",0,"");
        memset(caRxBuf,0x00,d_RX_MAX_LEN);
        mRX->Clear();
        icounter = 0;
        iRxTotalLen = 0;
        iConnect = true;
        iFlashMsg = false;
    }
    //Check Off Line
    if((ED_GetCD(sModemPort) == d_OFF) && (iConnect == true))
    {
        ED_ShowLogMsg("d_CLEAR",clLime);
        ED_ShowLogMsg("\nModem OFF Line",clRed);
        SaveLogFile("\n[Modem OFF Line]",0,"");
        SaveLogFile("\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now())),0,"");
        SaveLogFile("\n================================",0,"");
        iConnect = false;
        iFlashMsg = true;
        sp_OH->Brush->Color = clWhite;
        if(chkbox_AutoStop->Checked == true)
            bbtn_StopClick(Sender);
    }
    if(iFlashMsg && !iKeyPress)
    {
        if(iTimer/5 == 1)
        {
            rchedt_TestInfo->Font->Color = clBlack;
        }
        if(iTimer/10 == 1)
        {
            rchedt_TestInfo->Font->Color = clRed;
            iTimer = 0;
        }
        if(bbtn_Stop->Enabled == false)
        {
            rchedt_TestInfo->Font->Color = clLime;
            tmrRx->Enabled = false;
        }
    }
    else
    {
        iTimer = 0;
    }
    //If Data Come In
    if(ED_CheckRS232(sModemPort)!=d_FAILED)
    {
        iRxLen = 0;
        spRX->Brush->Color = clBlue;
        memset(caTmp,0x00,d_RX_MAX_LEN);

        iRxLen = ED_RS232ReadFile(sModemPort,caTmp);

        //If ON Line
        if(iConnect)
        {   //連線OK
            if(iRxTotalLen>d_RX_MAX_LEN)
            {
                ClearRxBuf();
            }
            memcpy(&caRxBuf[iRxTotalLen],&caTmp[0],iRxLen);
            iRxTotalLen+=iRxLen;

             //**************0502
            if (iRxTotalLen >= iInputLen)
            {
               if (memcmp(baTestData, &caRxBuf[0], iInputLen) != 0)
               {
                    Memo1->Lines->Add("PC Modem Rx CMP Error");
                    mRX->Lines->Add("PC Modem Rx CMP Error");
               }else
               {
                    //sprintf(caDataBuf,"TotalLen = %d\n",iRxTotalLen);
                    //Memo1->Lines->Add(caDataBuf);
                    Memo1->Lines->Add("PC    Modem Rx OK");
                    mRX->Lines->Add("PC Modem Rx OK");
                    ED_Delay(2000);
                    bModemCheck = 1;
                   // bbtn_StopClick(Sender);
                    Application->ProcessMessages();
               }
            }
            //**************0502
            edt_RXLen->Text = iRxTotalLen;
            icounter = 0;
        }
        //If OFF Line
        else
        {
            if(!iDialupOK)
                mRX->Text = mRX->Text+caTmp;
            mRX->SelStart = mRX->Text.Length();
            mRX->SelLength = 0;
            edt_RXLen->Text = iRxLen;
            if(!iKeyPress)
            {
			    for(i=0;i<iRxLen-4;i++)
			    {
	                  //Check Busy
			          if((caTmp[i]==0x42) && (caTmp[i+1]==0x55) && (caTmp[i+2]==0x53) && (caTmp[i+3]==0x59))
	                  {
	                     spRX->Brush->Color = clWhite;
	                     sp_OH->Brush->Color = clWhite;
	                     ED_ShowLogMsg("d_CLEAR",clRed);
	                     ED_ShowLogMsg("\nNum : "+edt_PhoneNum->Text,clRed);
	                     ED_ShowLogMsg("\nLine Busy !",clRed);
	                     SaveLogFile("\n[Line Busy]",0,"");
	                     SaveLogFile("\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now())),0,"");
	                     SaveLogFile("\n================================",0,"");
	                     iFlashMsg = true;
                         if(iDialupOK && chkbox_EnableRedial->Checked == true)
                            iRedial = true;
                         if(chkbox_AutoErrStop->Checked == true)
                            bbtn_StopClick(Sender);
	                  }
			    }
			    for(i=0;i<iRxLen-10;i++)
			    {
	                  //Check NO CARRIER
			          if((caTmp[i]==0x4E) && (caTmp[i+1]==0x4F) && (caTmp[i+3]==0x43) && (caTmp[i+4]==0x41) && (caTmp[i+5]==0x52) && (caTmp[i+6]==0x52) && (caTmp[i+7]==0x49) && (caTmp[i+8]==0x45) && (caTmp[i+9]==0x52))
	                  {
	                     spRX->Brush->Color = clWhite;
	                     if(iFlashMsg)
	                        ED_ShowLogMsg("\nNO CARRIER !",clRed);
	                     else
	                     {
	                         ED_ShowLogMsg("d_CLEAR",clRed);
	                         ED_ShowLogMsg("\n\nNO CARRIER !",clRed);
	                     }
	                     SaveLogFile("\n[NO CARRIER]",0,"");
	                     SaveLogFile("\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now())),0,"");
	                     SaveLogFile("\n================================",0,"");
	                     iFlashMsg = true;
                         if(iDialupOK && chkbox_EnableRedial->Checked == true)
                            iRedial = true;
                         if(chkbox_AutoErrStop->Checked == true)
                            bbtn_StopClick(Sender);
	                  }
			    }
			    for(i=0;i<iRxLen-11;i++)
			    {
	                  //Check NO DIALTONE
			          if((caTmp[i]==0x4E) && (caTmp[i+1]==0x4F) && (caTmp[i+3]==0x44) && (caTmp[i+4]==0x49) && (caTmp[i+5]==0x41) && (caTmp[i+6]==0x4C) && (caTmp[i+7]==0x54) && (caTmp[i+8]==0x4F) && (caTmp[i+9]==0x4E) && (caTmp[i+10]==0x45))
	                  {
	                     spRX->Brush->Color = clWhite;
	                     if(iFlashMsg)
	                        ED_ShowLogMsg("\nNO DIALTONE !",clRed);
	                     else
	                     {
	                         ED_ShowLogMsg("d_CLEAR",clRed);
	                         ED_ShowLogMsg("\n\nNO DIALTONE !",clRed);
	                     }
	                     SaveLogFile("\n[NO DIALTONE]",0,"");
	                     SaveLogFile("\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now())),0,"");
	                     SaveLogFile("\n================================",0,"");
	                     iFlashMsg = true;
                         if(iDialupOK && chkbox_EnableRedial->Checked == true)
                            iRedial = true;
                         if(chkbox_AutoErrStop->Checked == true)
                            bbtn_StopClick(Sender);
	                  }
			    }
            }
        }
    }
    //If No Data
    else
    {
        icounter++;
        spRX->Brush->Color = clWhite;
        edt_counter->Text = icounter;
        if(iConnect && chkbox_HangUp->Checked == true)
        {
            if(icounter>=(edt_OnLineIdleTime->Text.ToInt())*600)
                bbtn_StopClick(Sender);
        }
        if(!iConnect && iDialupOK && chkbox_StopDialup->Checked == true)
        {
            if(icounter==(edt_DialupIdleTime->Text.ToInt())*10)
            {
                ED_ShowLogMsg("d_CLEAR",clRed);
                ED_ShowLogMsg("\n\nDialup Timeout !",clRed);
                iFlashMsg = true;
                if(chkbox_EnableRedial->Checked == true)
                    iRedial = true;
            }
        }
        //Show Rx Data
        if(icounter == 10 && iRxTotalLen>0)
        {
            if(chkbox_OnLineChat->Checked == true)
            {
                mRX->Lines->Add(caRxBuf);
                SaveAscIILogFile("\n[Rx]\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now()))+"   Len:"+IntToStr(iRxTotalLen)+"\n",iRxTotalLen,caRxBuf);
                SaveAscIILogFile("\n================================",0,"");
            }
            else
            {
                ED_ShowBufToHex(iRxTotalLen,caRxBuf,mRX);
                SaveLogFile("\n[Rx]\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now()))+"   Len:"+IntToStr(iRxTotalLen)+"\n",iRxTotalLen,caRxBuf);
                SaveLogFile("\n",0,"");
            }
           
            if(bTxMode == d_TX_YES || bTxMode == d_TX_NO)
            {
                    ClearRxBuf();
            }
        }
        //For Auto Reverse

        //If data come in and Auto_Reverse checked then Tx after 0.5 sec.
        if(iConnect && bTxMode == d_AUTO_REVERSE && iRxTotalLen>0 && icounter == (edt_TxDelayTime->Text.ToInt())/100)
        {
            spTX->Brush->Color = clBlue;
            iTxLen = ED_RS232WriteFile(sModemPort,iRxTotalLen,caRxBuf);
            ED_ShowBufToHex(iTxLen,caRxBuf,mTX);
            SaveLogFile("\n[Tx]\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now()))+"   Len:"+IntToStr(iTxLen)+"\n",iTxLen,caRxBuf);
            SaveLogFile("\n================================",0,"");
            edt_TXLen->Text = iTxLen;
            ED_Delay(25);
            spTX->Brush->Color = clWhite;
            ClearRxBuf();
        }
        //For AutoSend
	    if(chkbox_EnableTx->Checked == true && RdoBtn_AutoSend->Checked == true)
	    {
	        MapTxData();
	        //If On Line and data come in and Increased_Len checked then Tx after 0.5sec.
		    if(iConnect && bTxMode == d_INCREASE_LEN  && iRxTotalLen>0 && icounter == (edt_TxDelayTime->Text.ToInt())/100)
		    {
		        spTX->Brush->Color = clBlue;
		        if(iIncreaseTxLen>d_TX_MAX_LEN)
		            iIncreaseTxLen = 1;
		        if(iDLETxLen>d_TX_MAX_LEN)
		            iDLETxLen = d_TX_MAX_LEN;
	            if(chkbox_DLE_Data->Checked == true)
	            {
	    	        iTxLen = ED_RS232WriteFile(sModemPort,iDLETxLen,caTxDLE);
	    	        ED_ShowBufToHex(iDLETxLen,caTxDLE,mTX);
	                SaveLogFile("\n[Tx]\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now()))+"   Len:"+IntToStr(iDLETxLen)+"\n",iTxLen,caTxDLE);
	                SaveLogFile("\n================================",0,"");
	    	        edt_TXLen->Text = iDLETxLen;
	                iIncreaseTxLen++;
	            }
	            else
	            {
	    	        iTxLen = ED_RS232WriteFile(sModemPort,iIncreaseTxLen++,caTxBuf);
	    	        ED_ShowBufToHex(iTxLen,caTxBuf,mTX);
	                SaveLogFile("\n[Tx]\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now()))+"   Len:"+IntToStr(iTxLen)+"\n",iTxLen,caTxBuf);
	                SaveLogFile("\n================================",0,"");
	    	        edt_TXLen->Text = iTxLen;
	            }
		        ED_Delay(25);
		        spTX->Brush->Color = clWhite;
                ClearRxBuf();
		    }
	        //If On Line and data come in and Fixed_Len checked then Tx after 0.5sec.
		    if(iConnect && bTxMode == d_FIXED_LEN  && iRxTotalLen>0 && icounter == (edt_TxDelayTime->Text.ToInt())/100)
		    {
		        spTX->Brush->Color = clBlue;
		        if(iFixedTxLen>d_TX_MAX_LEN)
		            iFixedTxLen = d_TX_MAX_LEN;
		        if(iDLETxLen>d_TX_MAX_LEN)
		            iDLETxLen = d_TX_MAX_LEN;
	            if(chkbox_DLE_Data->Checked == true)
	            {
	    	        iTxLen = ED_RS232WriteFile(sModemPort,iDLETxLen,caTxDLE);
	    	        ED_ShowBufToHex(iDLETxLen,caTxDLE,mTX);
	                SaveLogFile("\n[Tx]\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now()))+"   Len:"+IntToStr(iDLETxLen)+"\n",iTxLen,caTxDLE);
	                SaveLogFile("\n================================",0,"");
	    	        edt_TXLen->Text = iDLETxLen;
	            }
	            else
	            {
	    	        iTxLen = ED_RS232WriteFile(sModemPort,iFixedTxLen,caTxBuf);
	    	        ED_ShowBufToHex(iTxLen,caTxBuf,mTX);
	                SaveLogFile("\n[Tx]\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now()))+"   Len:"+IntToStr(iTxLen)+"\n",iTxLen,caTxBuf);
	                SaveLogFile("\n================================",0,"");
	    	        edt_TXLen->Text = iTxLen;
	            }
		        ED_Delay(25);
		        spTX->Brush->Color = clWhite;
                ClearRxBuf();
		    }
	        //If On Line and data come in and Custom_Len checked then Tx after 0.5sec.
		    if(iConnect && bTxMode == d_CUSTOM_LEN  && iRxTotalLen>0 && icounter == (edt_TxDelayTime->Text.ToInt())/100)
		    {
		        spTX->Brush->Color = clBlue;
		        if(iCustomTxLen>d_TX_MAX_LEN)
		            iCustomTxLen = d_TX_MAX_LEN;
		        if(iDLETxLen>d_TX_MAX_LEN)
		            iDLETxLen = d_TX_MAX_LEN;
	            if(chkbox_DLE_Data->Checked == true)
	            {
	    	        iTxLen = ED_RS232WriteFile(sModemPort,iDLETxLen,caTxDLE);
	    	        ED_ShowBufToHex(iDLETxLen,caTxDLE,mTX);
	                SaveLogFile("\n[Tx]\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now()))+"   Len:"+IntToStr(iDLETxLen)+"\n",iTxLen,caTxDLE);
	                SaveLogFile("\n================================",0,"");
	    	        edt_TXLen->Text = iDLETxLen;
	            }
	            else
	            {
	    	        iTxLen = ED_RS232WriteFile(sModemPort,iCustomTxLen,caTxBuf);
	    	        ED_ShowBufToHex(iTxLen,caTxBuf,mTX);
	                SaveLogFile("\n[Tx]\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now()))+"   Len:"+IntToStr(iTxLen)+"\n",iTxLen,caTxBuf);
	                SaveLogFile("\n================================",0,"");
	    	        edt_TXLen->Text = iTxLen;
	            }
		        ED_Delay(25);
		        spTX->Brush->Color = clWhite;
                ClearRxBuf();
		    }
	    }
        if(chkbox_EnableTx_Directly->Checked == true)
        {
            if(iConnect && icounter == 5)
                ClearRxBuf();
        }
        /*
        if(iConnect && iRxTotalLen>0 && icounter == 5)
        {
            ED_ShowLogMsg("Clear Rx Buf",clRed);
            memset(caRxBuf,0x00,d_RX_MAX_LEN);
            iRxTotalLen = 0;
        }*/
        //memset(caTmp,0x00,d_RX_MAX_LEN);
    }

    //If EnableTx_Directly checked then enable tmrTx(for Tx Directly)
    if(chkbox_EnableTx_Directly->Checked == true)
    {
        if(iConnect)
        {
            tmrTx->Interval = edt_AutoSend_Time->Text.ToInt();
            tmrTx->Enabled = true;
        }
        if(!iConnect)
        {
            tmrTx->Enabled = false;
        }
    }
    //Check Tx Rx lines
    if(ChkBox_ClearLines->Checked == true)
    {
        if(mRX->Lines->Count >= edt_Lines->Text.ToInt())
            mRX->Clear();
        if(mTX->Lines->Count >= edt_Lines->Text.ToInt())
            mTX->Clear();
    }
    if(iRedial)
    {
        tmrRx->Enabled = false;
        iRedialNow ++;
        bbtn_DialUpClick(Sender);
    }
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::bbtn_StopClick(TObject *Sender)
{
    frmMain->tmrQuery->Enabled = false;
    frmMain->tmrRx->Enabled = false;
    frmMain->tmrTx->Enabled = false;
    if(iConnect)
    {
        ModenHangUp(sModemPort);
        iConnect = false;
    }
    ED_Delay(200);
    WriteATCmd(sModemPort,"AT E0 V1 S0=0");
    ED_FlushTxRS232(sModemPort);
    ED_FlushRxRS232(sModemPort);
    ED_CloseRS232(sModemPort);
    ED_ShowLogMsg("d_CLEAR",clLime);
    if(sModemPort == "")
        ED_ShowLogMsg("\nCOM"+IntToStr(frmMain->rdgp_COM->ItemIndex+1)+"  Close",clLime);
    else
        ED_ShowLogMsg("\n"+sModemPort+"  Close",clLime);
    if(iListenOK)
        ED_ShowLogMsg("\nListen  Stop !",clLime);
    if(iDialupOK)
        ED_ShowLogMsg("\nDialup  Stop !",clLime);
    spTX->Brush->Color = clWhite;
    spRX->Brush->Color = clWhite;
    sp_AA->Brush->Color = clWhite;
    sp_OH->Brush->Color = clWhite;
    bbtn_Query->Enabled = true;
    bbtn_Listen->Enabled = true;
    bbtn_DialUp->Enabled = true;
    bbtn_Stop->Enabled = false;
    //GroupBox1->Caption = "<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>";
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::bbtn_ExitClick(TObject *Sender)
{
    if(iConnect)
        ModenHangUp(sModemPort);
    WriteATCmd(sModemPort,"AT E0 V1 S0=0");
    exit(0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkbox_EnableTxClick(TObject *Sender)
{
    if(chkbox_EnableTx->Checked == true)
        EnableTx();
    else
        DisableTx();
    ChkTxMode();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkbox_EnableTx_DirectlyClick(TObject *Sender)
{
    if(chkbox_EnableTx_Directly->Checked == true)
        EnableTxDirectly();
    else
        DisableTxDirectly();
    ChkTxMode();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::RdoBtn_AutoSendClick(TObject *Sender)
{
    if(RdoBtn_AutoSend->Checked == true)
        EnableAutoSend();
    ChkTxMode();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::RdoBtn_AutoReverseClick(TObject *Sender)
{
    if(RdoBtn_AutoReverse->Checked == true)
        DisableAutoSend();
    ChkTxMode();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RdoBtn_StartLenClick(TObject *Sender)
{
    CheckLenSelect();
    ChkTxMode();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RdoBtn_FixedLenClick(TObject *Sender)
{
    CheckLenSelect();
    ChkTxMode();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RdoBtn_CustomLenClick(TObject *Sender)
{
    CheckLenSelect();
    ChkTxMode();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::bbtn_AboutClick(TObject *Sender)
{
    frmAbout->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::bbtn_TxClearClick(TObject *Sender)
{
    mTX->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::bbtn_RxClearClick(TObject *Sender)
{
    mRX->Clear();    
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tmrTxTimer(TObject *Sender)
{
    MapTxData();
    if(bTxMode == d_INCREASE_LEN)
    {
        spTX->Brush->Color = clBlue;
        if(iIncreaseTxLen>d_TX_MAX_LEN)
            iIncreaseTxLen = 1;
        if(iDLETxLen>d_TX_MAX_LEN)
            iDLETxLen = d_TX_MAX_LEN;
        if(chkbox_DLE_Data->Checked == true)
        {
	        iTxLen = ED_RS232WriteFile(sModemPort,iDLETxLen,caTxDLE);
	        ED_ShowBufToHex(iDLETxLen,caTxDLE,mTX);
            SaveLogFile("\n[Tx]\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now()))+"   Len:"+IntToStr(iDLETxLen)+"\n",iTxLen,caTxDLE);
            SaveLogFile("\n================================",0,"");
	        edt_TXLen->Text = iDLETxLen;
            iIncreaseTxLen++;
        }
        else
        {
            iTxLen = ED_RS232WriteFile(sModemPort,iIncreaseTxLen++,caTxBuf);
            ED_ShowBufToHex(iTxLen,caTxBuf,mTX);
            SaveLogFile("\n[Tx]\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now()))+"   Len:"+IntToStr(iTxLen)+"\n",iTxLen,caTxBuf);
            SaveLogFile("\n================================",0,"");
            edt_TXLen->Text = iTxLen;
        }
        ED_Delay(25);
        spTX->Brush->Color = clWhite;
    }
    if(bTxMode == d_FIXED_LEN)
    {
        spTX->Brush->Color = clBlue;
        if(iFixedTxLen>d_TX_MAX_LEN)
            iFixedTxLen = d_TX_MAX_LEN;
        if(iDLETxLen>d_TX_MAX_LEN)
            iDLETxLen = d_TX_MAX_LEN;
        if(chkbox_DLE_Data->Checked == true)
        {
	        iTxLen = ED_RS232WriteFile(sModemPort,iDLETxLen,caTxDLE);
	        ED_ShowBufToHex(iDLETxLen,caTxDLE,mTX);
            SaveLogFile("\n[Tx]\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now()))+"   Len:"+IntToStr(iDLETxLen)+"\n",iTxLen,caTxDLE);
            SaveLogFile("\n================================",0,"");
	        edt_TXLen->Text = iDLETxLen;
        }
        else
        {
            iTxLen = ED_RS232WriteFile(sModemPort,iFixedTxLen,caTxBuf);
            ED_ShowBufToHex(iTxLen,caTxBuf,mTX);
            SaveLogFile("\n[Tx]\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now()))+"   Len:"+IntToStr(iTxLen)+"\n",iTxLen,caTxBuf);
            SaveLogFile("\n================================",0,"");
            edt_TXLen->Text = iTxLen;
        }
        ED_Delay(25);
        spTX->Brush->Color = clWhite;
    }
    if(bTxMode == d_CUSTOM_LEN)
    {
        spTX->Brush->Color = clBlue;
        if(iCustomTxLen>d_TX_MAX_LEN)
            iCustomTxLen = d_TX_MAX_LEN;
        if(iDLETxLen>d_TX_MAX_LEN)
            iDLETxLen = d_TX_MAX_LEN;
        if(chkbox_DLE_Data->Checked == true)
        {
	        iTxLen = ED_RS232WriteFile(sModemPort,iDLETxLen,caTxDLE);
	        ED_ShowBufToHex(iDLETxLen,caTxDLE,mTX);
            SaveLogFile("\n[Tx]\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now()))+"   Len:"+IntToStr(iDLETxLen)+"\n",iTxLen,caTxDLE);
            SaveLogFile("\n================================",0,"");
	        edt_TXLen->Text = iDLETxLen;
        }
        else
        {
	        iTxLen = ED_RS232WriteFile(sModemPort,iCustomTxLen,caTxBuf);
	        ED_ShowBufToHex(iTxLen,caTxBuf,mTX);
            //***************0430**************************************
            if (iTxLen == 8)
            {
                bbtn_StopClick(Sender);
                bDialClose = 1;
                return;
            }
            //*********************************************************
            SaveLogFile("\n[Tx]\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now()))+"   Len:"+IntToStr(iTxLen)+"\n",iTxLen,caTxBuf);
            SaveLogFile("\n================================",0,"");
	        edt_TXLen->Text = iTxLen;
        }
        ED_Delay(25);
        spTX->Brush->Color = clWhite;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tmrModemStatusTimer(TObject *Sender)
{
    iSpeakerVol = tkbar_SpeakerVol->Position;
    Label14->Caption = tkbar_SpeakerVol->Position;
    iQuerySensitive = tkbar_QuerySensitive->Position;
    Label13->Caption = tkbar_QuerySensitive->Position;
    iDialupSpeed = tkbar_DialupSpeed->Position;
    Label23->Caption = tkbar_DialupSpeed->Position;
    if(ED_GetDTR(sModemPort) == d_ON)
    {
        sp_DTR->Brush->Color = clRed;
        btn_DTROn->Enabled = false;
        btn_DTROff->Enabled = true;
    }
    else
    {
        sp_DTR->Brush->Color = clWhite;
        sp_OH->Brush->Color = clWhite;
        btn_DTROn->Enabled = true;
        btn_DTROff->Enabled = false;
    }

    if(ED_GetRTS(sModemPort) == d_ON)
    {
        sp_RTS->Brush->Color = clRed;
        btn_RTSOn->Enabled = false;
        btn_RTSOff->Enabled = true;
    }
    else
    {
        sp_RTS->Brush->Color = clWhite;
        sp_OH->Brush->Color = clWhite;
        btn_RTSOn->Enabled = true;
        btn_RTSOff->Enabled = false;
    }

    if(ED_GetDSR(sModemPort) == d_ON)
        sp_DSR->Brush->Color = clRed;
    else
        sp_DSR->Brush->Color = clWhite;

    if(ED_GetCTS(sModemPort) == d_ON)
        sp_CTS->Brush->Color = clRed;
    else
        sp_CTS->Brush->Color = clWhite;

    if(ED_GetRING(sModemPort) == d_ON)
    {
        sp_RING->Brush->Color = clRed;
        sp_AA->Brush->Color = clWhite;
        sp_OH->Brush->Color = clRed;
        SaveLogFile("\n[Ring]",0,"");
        SaveLogFile("\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now())),0,"");
        SaveLogFile("\n================================",0,"");
    }
    else
        sp_RING->Brush->Color = clWhite;

    if(ED_GetCD(sModemPort) == d_ON)
    {
        sp_CD->Brush->Color = clRed;
        sp_OH->Brush->Color = clRed;
    }
    else
        sp_CD->Brush->Color = clWhite;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::btn_DTROnClick(TObject *Sender)
{
    ED_SetDTR(sModemPort,d_ON);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btn_DTROffClick(TObject *Sender)
{
    ED_SetDTR(sModemPort,d_OFF);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btn_RTSOnClick(TObject *Sender)
{
    ED_SetRTS(sModemPort,d_ON);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btn_RTSOffClick(TObject *Sender)
{
    ED_SetRTS(sModemPort,d_OFF);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::chkbox_TxYesClick(TObject *Sender)
{
    if(chkbox_TxYes->Checked == true)
    {
        chkbox_EnableTx->Enabled = true;
        chkbox_EnableTx_Directly->Enabled = true;
        
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::chkbox_TxNoClick(TObject *Sender)
{
    if(chkbox_TxNo->Checked == true)
    {
        chkbox_EnableTx->Checked = false;
        chkbox_EnableTx_Directly->Checked = false;
        chkbox_EnableTx->Enabled = false;
        chkbox_EnableTx_Directly->Enabled = false;
        chkbox_OnLineChat->Checked = false;
        chkbox_ForceKeyPress->Checked = false;
        chkbox_DLE_Data->Checked = false;
        chkbox_DLE_Data->Enabled = false;
        RdoBtn_Data1->Enabled = false;
        RdoBtn_Data2->Enabled = false;
        edt_Min->Enabled = false;
        Label6->Enabled = false;
        edt_Max->Enabled = false;
        edt_Fill->Enabled = false;
        edt_CustomData->Enabled = false;
    }
}
//---------------------------------------------------------------------------
       
void __fastcall TfrmMain::bbtn_DialUpClick(TObject *Sender)
{
    
    if(!iRedial)
        Initial();

    if(edt_PhoneNum->Text=="")
    {
        MessageBox(NULL,"Please Input Phone Number!","Number Error",MB_ICONERROR);
        return;
    }
    if(iRedial)
    {
        if(iRedialNow > edt_RedialTimes->Text.ToInt() && chkbox_AlwaysRedial->Checked == false)
        {
            iRedial = false;
            iRedialNow = 0;
            tmrRx->Enabled = true;
            return;
        }
        ED_Delay((edt_RedialDelay->Text.ToInt())*1000);
        icounter = 0;
        iFlashMsg = false;
        ED_CloseRS232(sModemPort);
    }
    ED_ShowLogMsg("d_CLEAR",clLime);
    ED_Delay(100);
    if(ED_ExInitialRS232(sModemPort,ulBaudRate)==d_OK)
    {
        ED_ShowLogMsg("\n"+sModemPort+" Open OK",clLime);
        ED_ShowLogMsg("Baudrate: "+IntToStr(ulBaudRate),clLime);
        ModemDialUp(sModemPort);
        ED_ShowLogMsg("\nNum : "+edt_PhoneNum->Text,clLime);
        if(iRedial)
            ED_ShowLogMsg("Redialing..# "+IntToStr(iRedialNow),clLime);
        else
            ED_ShowLogMsg("Dialing..",clLime);
        sp_OH->Brush->Color = clRed;
        iDialupOK = true;
        tmrRx->Enabled = true;
        bbtn_Query->Enabled = false;
        bbtn_Listen->Enabled = false;
        bbtn_DialUp->Enabled = false;
        bbtn_Stop->Enabled = true;
        iRedial = false;
    }
    else
    {
        ED_ShowLogMsg("\n"+sModemPort+" Open NG",clRed);
        ED_ShowLogMsg("Baudrate: "+IntToStr(ulBaudRate),clRed);
    }    
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mTXKeyPress(TObject *Sender, char &Key)
{
    String Temp;
    int iTmpLen;
    
    if(Key==27)//ESC
        mTX->Clear();
    if (Key!=13) return;
    //if(bTxMode == d_TX_NO)
    //    return;
    if(!iConnect)
    {
        if(chkbox_ForceKeyPress->Checked == false)
        {                                
            MessageBox(NULL,"If you want to write AT cmd , please enable [ OFF Line AT Cmd Entry ] in the utility setting.","Information",MB_ICONWARNING);
            return;
        }
        else
        {
            if(hComm232[ED_GetCOMIndex(sModemPort)] == 0)
            {
                Initial();
                ED_ShowLogMsg("d_CLEAR",clLime);
                if(ED_ExInitialRS232(sModemPort,ulBaudRate)==d_OK)
                {
                    ED_ShowLogMsg("\n"+sModemPort+" Open OK",clLime);
                    ED_ShowLogMsg("Baudrate: "+IntToStr(ulBaudRate),clLime);
                    edt_counter->Text = "";
                    mTX->ScrollBars = ssVertical;
                    mRX->ScrollBars = ssVertical;
                    tmrRx->Enabled = true;
                    iDialupOK = false;
                    iKeyPress = true;
                }
                else
                {
                    ED_ShowLogMsg("\n"+sModemPort+" Open NG",clRed);
                    ED_ShowLogMsg("Baudrate: "+IntToStr(ulBaudRate),clRed);
                    iKeyPress = false;
                    return;
                }
            }
            if(bTxMode == d_TX_YES)
            {
                iFlashMsg = false;
                spTX->Brush->Color = clBlue;
                WriteATCmd(sModemPort,mTX->Lines->Strings[mTX->Lines->Count-1]);
                edt_TXLen->Text = mTX->Lines->Strings[mTX->Lines->Count-1].Length();
                ED_Delay(25);
                spTX->Brush->Color = clWhite;
                return;
            }
        }
    }
    //On Line Chat Mode
    if(iConnect && chkbox_OnLineChat->Checked == false)
    {
        MessageBox(NULL,"If you want to send messages by key_pressed , please enable [ On Line Chat Communication ] in the utility setting.","Information",MB_ICONWARNING);
        return;
    }
    if(iConnect && bTxMode == d_TX_YES && chkbox_OnLineChat->Checked == true)
    {
        Temp = mTX->Lines->Strings[mTX->Lines->Count-1];
        iTmpLen = mTX->Lines->Strings[mTX->Lines->Count-1].Length();
        spTX->Brush->Color = clBlue;
        iTxLen = ED_RS232WriteFile(sModemPort,iTmpLen,Temp.c_str());
        SaveAscIILogFile("\n[Tx]\n    "+String(FormatDateTime("yyyy/mm/dd/hh/mm/ss", Now()))+"   Len:"+IntToStr(iTxLen)+"\n",iTxLen,Temp.c_str());
        SaveAscIILogFile("\n================================",0,"");
        edt_TXLen->Text = iTxLen;
        ED_Delay(25);
        spTX->Brush->Color = clWhite;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edt_StartLenChange(TObject *Sender)
{
    if(edt_StartLen->Text == "")
        return;
    iIncreaseTxLen = frmMain->edt_StartLen->Text.ToInt();
    //ShowMessage(iIncreaseTxLen);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edt_FixedLenChange(TObject *Sender)
{
    if(edt_FixedLen->Text == "")
        return;
    iFixedTxLen = frmMain->edt_FixedLen->Text.ToInt();
    //ShowMessage(iFixedTxLen);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edt_CustomDataChange(TObject *Sender)
{
    if(edt_CustomData->Text == "")
        return;
    iCustomTxLen = (frmMain->edt_CustomData->Text.Length())/2;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Panel2Click(TObject *Sender)
{

    int i;
    i = 0;


    gpbox_Utility_Setting->Top = 250;
    i = gpbox_Utility_Setting->Height;
    if(Panel2->Caption == "↓")
    {
        while(1)
        {
            gpbox_Utility_Setting->Height = i++;
            if(gpbox_Utility_Setting->Height >= 437)
            {
                Panel2->Caption = "↑";
                break;
            }
            Application->ProcessMessages();
        }
    }
    else
    {
        while(1)
        {
            gpbox_Utility_Setting->Height = i--;
            if(gpbox_Utility_Setting->Height <= 0)
            {
                Panel2->Caption = "↓";
                break;
            }
            Application->ProcessMessages();
        }
    }     
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::mRXKeyPress(TObject *Sender, char &Key)
{
    if(Key==27)
        mRX->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Panel5Click(TObject *Sender)
{
    pnl_Switch_Control->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Panel6Click(TObject *Sender)
{
    pnl_Switch_Control->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::bbtn_Control_CloseClick(TObject *Sender)
{
    pnl_Switch_Control->Visible = false; 
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::chkbox_ForceKeyPressClick(TObject *Sender)
{
    Initial();
    ED_ShowLogMsg("d_CLEAR",clLime);
    if(chkbox_ForceKeyPress->Checked == true)
    {
        if(ED_ExInitialRS232(sModemPort,ulBaudRate)==d_OK)
        {
            ED_ShowLogMsg("\n"+sModemPort+" Open OK",clLime);
            ED_ShowLogMsg("Baudrate: "+IntToStr(ulBaudRate),clLime);
            edt_counter->Text = "";
            mTX->ScrollBars = ssVertical;
            mRX->ScrollBars = ssVertical;
            chkbox_TxYes->Checked = true;
            chkbox_TxNo->Checked = false;
            chkbox_EnableTx->Checked = false;
            chkbox_EnableTx_Directly->Checked = false;
            chkbox_EnableTx->Enabled = false;
            chkbox_EnableTx_Directly->Enabled = false;
            tmrRx->Enabled = true;
            iDialupOK = false;
            iKeyPress = true;
        }
        else
        {
            ED_ShowLogMsg("\n"+sModemPort+" Open NG",clRed);
            ED_ShowLogMsg("Baudrate: "+IntToStr(ulBaudRate),clRed);
            iKeyPress = false;
        }
    }
    else
    {
        ED_CloseRS232(sModemPort);
        ED_ShowLogMsg("d_CLEAR",clLime);
        ED_ShowLogMsg("\n\n"+sModemPort+"  Close",clLime);
        mTX->ScrollBars = ssNone;
        mRX->ScrollBars = ssNone;
        tmrRx->Enabled = false;
        iKeyPress = false;
        if(chkbox_OnLineChat->Checked == true)
            return;
        if(chkbox_TxYes->Checked == true)
        {
            chkbox_EnableTx->Enabled = true;
            chkbox_EnableTx_Directly->Enabled = true;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::chkbox_OnLineChatClick(TObject *Sender)
{
    if(chkbox_OnLineChat->Checked == true)
    {
        chkbox_TxYes->Checked = true;
        chkbox_TxNo->Checked = false;
        chkbox_EnableTx->Checked = false;
        chkbox_EnableTx_Directly->Checked = false;
        chkbox_EnableTx->Enabled = false;
        chkbox_EnableTx_Directly->Enabled = false;
    }
    else
    {
        if(chkbox_ForceKeyPress->Checked == true)
            return;
        if(chkbox_TxYes->Checked == true)
        {
            chkbox_EnableTx->Enabled = true;
            chkbox_EnableTx_Directly->Enabled = true;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::edt_CustomDataKeyPress(TObject *Sender,
      char &Key)
{
    if(Key==27)//ESC
        edt_CustomData->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::bbtn_ListenDefaultClick(TObject *Sender)
{
    edt_ListenInitCmd->Text = "AT &F E0 V1 &D2 &C1";
    edt_ATCmd1->Text = "AT S07=150 S09=015 S10=023 S30=0";
    edt_ATCmd2->Text = "AT S7=40 S30=0";
    edt_EndATCmd->Text = "AT %C1 &K3 N1 X4";
    edt_RingCallNum->Text = "1";
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::bbtn_DialupDefaultClick(TObject *Sender)
{
    //edt_DialupInitCmd->Text = "";
    tkbar_DialupSpeed->Position = 95;    
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::bbtn_QueryDefaultClick(TObject *Sender)
{
    edt_QueryATCmd->Text = "AT E1 V1 I1 I2 I3 I4 I5 I6 I7";
    tkbar_QuerySensitive->Position = 29;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::bbtn_VolDefaultClick(TObject *Sender)
{
    tkbar_SpeakerVol->Position = 3;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::edt_RedialTimesChange(TObject *Sender)
{
    if(edt_RedialTimes->Text.ToInt()>0)
        chkbox_AlwaysRedial->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::chkbox_AlwaysRedialClick(TObject *Sender)
{
    if(chkbox_AlwaysRedial->Checked == true)
        edt_RedialTimes->Enabled = false;
    else
        edt_RedialTimes->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::chkbox_EnableRedialClick(TObject *Sender)
{
    if(chkbox_EnableRedial->Checked == true)
    {
        chkbox_AlwaysRedial->Enabled = true;
        edt_RedialTimes->Enabled = true;
    }
    else
    {
        chkbox_AlwaysRedial->Enabled = false;
        edt_RedialTimes->Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RdoBtn_SpeakerOnClick(TObject *Sender)
{
    if(RdoBtn_SpeakerOn->Checked == true)
    {
        bbtn_VolDefault->Enabled = true;
        tkbar_SpeakerVol->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RdoBtn_SpeakerOffClick(TObject *Sender)
{
    if(RdoBtn_SpeakerOff->Checked == true)
    {
        bbtn_VolDefault->Enabled = false;
        tkbar_SpeakerVol->Enabled = false;
    }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::btnConnectionClick(TObject *Sender)
{
    sCOMPort = "COM" + IntToStr(cboxCOMPort->ItemIndex + 1);
    ulBaudRate = StrToInt(cboxBaud->Text);
    ZeroMemory(&baTmp, 20);

    memcpy(baTmp, cboxParity->Text.c_str(), cboxParity->Text.Length());
    bParity = (BYTE)baTmp[0];
    memcpy(baTmp, cboxDataBit->Text.c_str(), cboxDataBit->Text.Length());
    bDataBit = (BYTE)baTmp[0];
    memcpy(baTmp, cboxStopBit->Text.c_str(), cboxStopBit->Text.Length());
    bStopBit = (BYTE)baTmp[0];

    if(Ed_InitialRS232(sCOMPort, ulBaudRate, bParity, bDataBit, bStopBit) != d_OK)
    {
        Memo1->Lines->Add("PC    RS232 Tx Open Err");
    }
    else
    {
        Memo1->Lines->Add("PC    RS232 Tx Open Ok");
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnSendClick(TObject *Sender)
{
    BYTE baData[2048];
    char caDataBuf[512];
    AnsiString asData;

    iInputLen = StrToInt(edtInputLen->Text.c_str());//紀錄手動輸入資料長度
    memset(baTestData, 0x0, 2048);
    //Random User Data
    randomize();
    for (int i = 0; i < iInputLen; i++)
    {
        baData[i] = random(256);
    }

    memcpy(baTestData, baData, 2048);
    //sprintf(caDataBuf,"Random Data = %02X", baData[2047]);

    //Edit1->Text = (AnsiString)caDataBuf;
    //strcpy(Edit1->Text, caDataBuf);
    //Memo1->Lines->Add(caDataBuf);
    Memo1->Lines->Add("PC -> RS232 -> V7");
    iTxLen = ED_RS232WriteFile(sCOMPort, iInputLen, baData);  //"\x31\x32\x33\x34\x35\x36\x37\x38"
    ED_Delay(1000);
    if (iTxLen != iInputLen)
        Memo1->Lines->Add("RS232 Tx Len Error");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnCloseClick(TObject *Sender)
{
    ED_FlushTxRS232(sCOMPort);
    ED_FlushRxRS232(sCOMPort);
    ED_CloseRS232(sCOMPort);    
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnExitClick(TObject *Sender)
{
    ED_FlushTxRS232(sCOMPort);
    ED_FlushRxRS232(sCOMPort);
    ED_CloseRS232(sCOMPort);
    exit(0); 
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Button1Click(TObject *Sender)
{
    iRSRxLen = 0;
    iTotalEthernetLen = 0;
    Label25->Caption = "Testing";
    bbtn_Query->Click(); //modem listen
    bbtn_Listen->Click();
    btnConnectionClick(Sender);

    btnSendClick(Sender);
    ED_Delay(8000);
    //btnCloseClick(Sender);
    //close RS232 Tx
    ED_FlushTxRS232(sCOMPort);
    ED_FlushRxRS232(sCOMPort);
    ED_CloseRS232(sCOMPort);
    Memo1->Lines->Add("PC <- Modem <- V7");
    while (1)
    {
        ED_Delay(200);
        if (bModemCheck == 1)
           break;
        Application->ProcessMessages();
    }

    Application->ProcessMessages();
    ED_Delay(5000);
    Memo1->Lines->Add("PC -> Modem -> V7");
    bDialUpCheck = 1;
    bbtn_DialUpClick(Sender);
    while (1)
    {
        ED_Delay(200);
        if (iConnect == true)
           break;
        Application->ProcessMessages();
    }
    iTxLen = ED_RS232WriteFile(sModemPort,iInputLen ,baTestData);
    Application->ProcessMessages();
    bbtn_StopClick(Sender);

    Button2Click(Sender); //Run Ethernet Server

    while(1)
    {
        if (iTotalEthernetLen >= 2048)
            break;
        Application->ProcessMessages();
    }

    if (memcmp(baEthernetBuf, baTestData, 2048) != 0)
        Memo1->Lines->Add("PC Ethernet Rx Err");
    else
    {
        Memo1->Lines->Add("PC    Ethernet Rx OK");
        Button5Click(Sender);
        Memo1->Lines->Add("PC -> Ethernet -> V7");
        ED_Delay(1000);
        Button3Click(Sender); //Server Stop
        Button7Click(Sender); //Open RS232 Rx COM
    }

    while( ED_CheckRS232(sCOMPort1) == d_FAILED);

    Memo1->Lines->Add("PC <- RS232  <- V7");
    ED_Delay(2000);

    Button6Click(Sender); //Read RS232 Rx Data 
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::Button2Click(TObject *Sender)
{
    ServerSocket1->Port = atoi(LabeledEdit1->Text.c_str());
    ServerSocket1->Open();
    Memo1->Lines->Add("PC    Ethernet Server Running");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Button3Click(TObject *Sender)
{
    ServerSocket1->Close();
    Memo1->Lines->Add("PC    Ethernet Server Close");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Button5Click(TObject *Sender)
{
    /*char buf[6144];
  int rlen;
  AnsiString info;

    info = "";
    rlen =  Edit2->Text.Length();
    GP_UnpackData(Edit1->Text.c_str(),rlen,buf);
    info = info + "[Server_Sent] " + rlen + " bytes";
    Memo1->Lines->Add(info);
    Memo1->Lines->Add(buf);
    info = "";  */
    ServerSocket1->Socket->Connections[0]->SendBuf(baTestData, 2048);    
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ServerSocket1ClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
     Memo1->Lines->Add("PC    Ethernet Connect OK");
     Memo1->Lines->Add("PC <- Ethernet <- V7");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ServerSocket1ClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
    Memo1->Lines->Add("PC     Ethernet Disconnect..");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ServerSocket1ClientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
    ShowMessage("Connect Error!!");
  ErrorCode = 0;//防止跳出視窗
  Button1->Enabled = true;     
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ServerSocket1ClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
  //unsigned char cmd[4096];
  BYTE cmd[2048];
  char buf[6144];
  int rlen;
  AnsiString info;

  info = "";

  //Receive
  rlen = Socket->ReceiveLength();
  Socket->ReceiveBuf(cmd,rlen);
  memcpy(&baEthernetBuf[iTotalEthernetLen], cmd, rlen);
  iTotalEthernetLen +=  rlen;
  Application->ProcessMessages();
  GP_UnpackData(cmd,rlen,buf);
  info = info + "[Server_Receive] " + rlen + " bytes";
  Memo1->Lines->Add(info);
  Memo1->Lines->Add(buf);
  info = "";  
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::Button6Click(TObject *Sender)
{
    BYTE baRS232RxBuf[4096] = {0};

    USHORT  usss = ED_RS232ReadFile(sCOMPort1,baRS232RxBuf);
    memcpy(&baModemRxData[iRSRxLen], baRS232RxBuf, usss);
    iRSRxLen += usss;

    Memo1->Lines->Add("PC    RS232 Rx....");
    if (iRSRxLen >= 2048)
    {
        if (memcmp(baModemRxData, baTestData, 2048) == 0)
        {
            Memo1->Lines->Add("PC    RS232 Rx OK");
            Memo1->Lines->Add("----  End  ----");
            Label25->Caption = "OK";
        } else {
            Memo1->Lines->Add("PC    RS232 Rx Error");
            
            Label25->Caption = "Error";
        }
        ED_FlushTxRS232(sCOMPort1);
        ED_FlushRxRS232(sCOMPort1);
        ED_CloseRS232(sCOMPort1);
    }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Button7Click(TObject *Sender)
{
    sCOMPort1 = "COM" + IntToStr(ComboBox1->ItemIndex + 1);
    ulBaudRate = StrToInt(ComboBox2->Text);
    ZeroMemory(&baTmp, 20);

    memcpy(baTmp, ComboBox3->Text.c_str(), ComboBox3->Text.Length());
    bParity = (BYTE)baTmp[0];
    memcpy(baTmp, ComboBox4->Text.c_str(), ComboBox4->Text.Length());
    bDataBit = (BYTE)baTmp[0];
    memcpy(baTmp, ComboBox5->Text.c_str(), ComboBox5->Text.Length());
    bStopBit = (BYTE)baTmp[0];

    if(Ed_InitialRS232(sCOMPort1, ulBaudRate, bParity, bDataBit, bStopBit) != d_OK)
    {
        Memo1->Lines->Add("PC    RS232 Rx Open Err");
    }
    else
    {
        Memo1->Lines->Add("PC    RS232 Rx Open Ok");
    }    
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::Button4Click(TObject *Sender)
{
    exit(0);
}
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include<stdio.h>
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void GP_UnpackData(unsigned char *baSBuf,int uiLen,unsigned char *baTBuf)
{
  UINT i;
  char cMe[4];
  strcpy(baTBuf,"");
  for(i=0;i<uiLen;i++)
  {
     sprintf(cMe," %02X",baSBuf[i]);
     strcat(baTBuf,cMe);
  }
}
//---------------------------------------------------------------------------
//Server
//---------------------------------------------------------------------------
void __fastcall TForm1::ServerSocketClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
  unsigned char cmd[2048];
  char buf[6144];
  int rlen;
  rlen = Socket->ReceiveLength();
  Socket->ReceiveBuf(cmd,rlen);
  GP_UnpackData(cmd,rlen,buf);
  Memo_Log->Lines->Add("[Server_Receive]");
  Memo_Log->Lines->Add(buf);

  //ECHO
  Socket->SendBuf(cmd,rlen);
  GP_UnpackData(cmd,rlen,buf);
  Memo_Log->Lines->Add("[Server_Sent]");
  Memo_Log->Lines->Add(buf);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button_RunClick(TObject *Sender)
{
  ServerSocket->Port = atoi(LabeledEdit_ServerPort->Text.c_str());
  ServerSocket->Open();
  Button_Run->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button_StopClick(TObject *Sender)
{
  ServerSocket->Close();
  Shape_Server->Brush->Color = clRed;
  Button_Run->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ServerSocketClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
  Shape_Server->Brush->Color = clLime;
  /*
    unsigned char cmd[15]= {0x10,0x02,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x10,0x03};
  char buf[50];
  ServerSocket->Socket->Connections[0]->SendBuf(cmd,15);
  GP_UnpackData(cmd,15,buf);
  Memo_Log->Lines->Add("[Server_Sent]");
  Memo_Log->Lines->Add(buf);     */

}
//---------------------------------------------------------------------------
void __fastcall TForm1::ServerSocketClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
  Shape_Server->Brush->Color = clRed;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ServerSocketClientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
  ShowMessage("Connect Error!!");
  ErrorCode = 0;//¨¾¤î¸õ¥Xµøµ¡
  Button_Run->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ServerSocketClientWrite(TObject *Sender,
      TCustomWinSocket *Socket)
{ /*
  unsigned char cmd[10]={0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03};
  char buf[50];

  Memo_Log->Lines->Add("[Server_Sent]");
  GP_UnpackData(cmd,10,buf);
  Memo_Log->Lines->Add(buf);
  Socket->SendBuf(cmd,10);   */
}
//---------------------------------------------------------------------------
//Client
//---------------------------------------------------------------------------
void __fastcall TForm1::Button_ConnectClick(TObject *Sender)
{
  ClientSocket->Host = LabeledEdit_Host->Text;
  ClientSocket->Port = atoi(LabeledEdit_Port->Text.c_str());


  ClientSocket->Open();
  Button_Connect->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClientSocketConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
  Shape_Client->Brush->Color = clLime;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClientSocketDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
  Shape_Client->Brush->Color = clRed;
  Button_Connect->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_DisconnectClick(TObject *Sender)
{
  ClientSocket->Close();
  Button_Connect->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button_SendClick(TObject *Sender)
{
  unsigned char cmd[1024], SCode[13] = {0x10,0x02,0x0F,0x00,0x00,0x01,0x01,0x00,0x00,0x00, 0x0F,0x10,0x03};

  char buf[4096];
  int i;

  //ClientSocket->Socket->SendText(LabeledEdit_Message->Text);
  //i = LabeledEdit_Message->Text.Length();
  ClientSocket->Socket->SendBuf(SCode, 13);
  Memo_Log->Lines->Add("[Client_Sent]");
  //GP_UnpackData(cmd,i,buf);
  GP_UnpackData(SCode,13,buf);
  Memo_Log->Lines->Add(buf);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocketError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
  ShowMessage("Connect Error!!");
  ErrorCode = 0;//¨¾¤î¸õ¥Xµøµ¡
  Button_Connect->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocketRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
  unsigned char cmd[1024];
  unsigned char startup[13] = {0x10, 0x02, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x10, 0x03};
  unsigned char dialup[29] = {0x10,0x02,0x34,0x36,0x30,0x31,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x10,0x03};
  unsigned char startupR[13] = {0x10,0x02,0x0F,0x00,0x00,0x01,0x01,0x00,0x00,0x00, 0x0F,0x10,0x03};
  unsigned char dialupR[13] = {0x10,0x02,0x0F,0x01,0x00,0x00,0x00,0x00,0x00,0x00, 0x0E,0x10,0x03};
  char buf[4096];
  int i;

  if(Memo_Log->Lines->Count > 100) Memo_Log->Clear();
  
  i = Socket->ReceiveLength();
  Socket->ReceiveBuf(cmd,i);

  Memo_Log->Lines->Add("[Client_Receive]");
  GP_UnpackData(cmd,i,buf);
  Memo_Log->Lines->Add(buf);

  Sleep(100);
  Memo_Log->Lines->Add("[Client_Sent]");

  if(!memcmp(cmd, startup, 13))
  {
    ClientSocket->Socket->SendBuf(startupR, 13);
    GP_UnpackData(startupR,13,buf);
  }
  else if(!memcmp(cmd, dialup, 29))
  {
    ClientSocket->Socket->SendBuf(dialupR, 13);
    GP_UnpackData(dialupR,13,buf);
  }
  else 
  {
    ClientSocket->Socket->SendBuf(startupR, 13);
    GP_UnpackData(startupR,13,buf);
  }


  Memo_Log->Lines->Add(buf);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_ClearClick(TObject *Sender)
{
    Memo_Log->Clear();    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  unsigned char cmd[1024], SCode[13] = {0x10,0x02,0x0F,0x01,0x00,0x00,0x00,0x00,0x00,0x00, 0x0E,0x10,0x03};

  char buf[4096];
  int i;

  //ClientSocket->Socket->SendText(LabeledEdit_Message->Text);
  //i = LabeledEdit_Message->Text.Length();
  ClientSocket->Socket->SendBuf(SCode, 13);
  Memo_Log->Lines->Add("[Client_Sent]");
  //GP_UnpackData(cmd,i,buf);
  GP_UnpackData(SCode,13,buf);
  Memo_Log->Lines->Add(buf);
}
//---------------------------------------------------------------------------



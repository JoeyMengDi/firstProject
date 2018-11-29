//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ScktComp.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox_Server;
    TGroupBox *GroupBox_Client;
    TLabeledEdit *LabeledEdit_Host;
    TLabeledEdit *LabeledEdit_Port;
    TLabeledEdit *LabeledEdit_Message;
    TButton *Button_Connect;
    TButton *Button_Disconnect;
    TButton *Button_Send;
    TClientSocket *ClientSocket;
    TServerSocket *ServerSocket;
    TShape *Shape_Client;
    TMemo *Memo_Log;
    TLabeledEdit *LabeledEdit_ServerPort;
    TButton *Button_Run;
    TButton *Button_Stop;
    TShape *Shape_Server;
    TLabeledEdit *LabeledEdit_Name;
    TButton *Button_Clear;
    TButton *Button1;
    TButton *Button2;
    void __fastcall Button_ConnectClick(TObject *Sender);
    void __fastcall ClientSocketConnect(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ClientSocketDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ServerSocketClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall Button_DisconnectClick(TObject *Sender);
    void __fastcall Button_SendClick(TObject *Sender);
    void __fastcall Button_RunClick(TObject *Sender);
    void __fastcall Button_StopClick(TObject *Sender);
    void __fastcall ServerSocketClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ServerSocketClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ServerSocketClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
    void __fastcall ClientSocketError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
    void __fastcall ServerSocketClientWrite(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ClientSocketRead(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall Button_ClearClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdIPWatch.hpp>
#include <ScktComp.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TTimer *tmrQuery;
    TTimer *tmrRx;
    TTimer *tmrTx;
    TTimer *tmrModemStatus;
    TBitBtn *bbtn_TxClear;
    TBitBtn *bbtn_RxClear;
    TPanel *pnl_Switch_Control;
    TGroupBox *GroupBox9;
    TButton *btn_DTROn;
    TButton *btn_DTROff;
    TGroupBox *GroupBox8;
    TButton *btn_RTSOn;
    TButton *btn_RTSOff;
    TBitBtn *bbtn_Control_Close;
    TTabSheet *TabSheet4;
    TTabSheet *TabSheet5;
    TPanel *Panel1;
    TBitBtn *bbtn_Query;
    TBitBtn *bbtn_Listen;
    TBitBtn *bbtn_Stop;
    TBitBtn *bbtn_DialUp;
    TBitBtn *bbtn_About;
    TBitBtn *bbtn_Exit;
    TRadioGroup *rdgp_COM;
    TGroupBox *GroupBox1;
    TRichEdit *rchedt_TestInfo;
    TGroupBox *GroupBox2;
    TRadioButton *RdoBtn_SpeakerOn;
    TRadioButton *RdoBtn_SpeakerOff;
    TGroupBox *GroupBox3;
    TRadioButton *RdoBtn_Cmd1;
    TRadioButton *RdoBtn_Cmd2;
    TGroupBox *GroupBox6;
    TLabel *Label5;
    TEdit *edt_PhoneNum;
    TGroupBox *gpbox_Baudrate;
    TComboBox *cbox_Baudrate;
    TGroupBox *GroupBox12;
    TEdit *edt_Lines;
    TCheckBox *ChkBox_ClearLines;
    TCheckBox *ChkBox_SetLog;
    TPanel *Panel2;
    TMemo *mTX;
    TMemo *mRX;
    TGroupBox *GroupBox7;
    TShape *sp_RTS;
    TShape *sp_DSR;
    TShape *sp_CTS;
    TShape *sp_RING;
    TShape *sp_CD;
    TShape *sp_OH;
    TShape *sp_DTR;
    TShape *sp_AA;
    TShape *spTX;
    TShape *spRX;
    TPanel *Panel5;
    TPanel *Panel6;
    TPanel *Panel7;
    TPanel *Panel8;
    TPanel *Panel9;
    TPanel *Panel10;
    TPanel *Panel12;
    TPanel *Panel11;
    TPanel *Panel3;
    TEdit *edt_TXLen;
    TEdit *edt_RXLen;
    TPanel *Panel13;
    TEdit *edt_counter;
    TGroupBox *gpbox_Utility_Setting;
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TPanel *Panel14;
    TGroupBox *GroupBox5;
    TLabel *Label3;
    TLabel *Label4;
    TRadioButton *RdoBtn_StartLen;
    TRadioButton *RdoBtn_FixedLen;
    TEdit *edt_StartLen;
    TEdit *edt_FixedLen;
    TRadioButton *RdoBtn_CustomLen;
    TGroupBox *GroupBox4;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label18;
    TLabel *Label19;
    TRadioButton *RdoBtn_AutoReverse;
    TRadioButton *RdoBtn_AutoSend;
    TEdit *edt_AutoSend_Time;
    TCheckBox *chkbox_EnableTx;
    TPanel *Panel4;
    TCheckBox *chkbox_EnableTx_Directly;
    TEdit *edt_TxDelayTime;
    TGroupBox *GroupBox11;
    TLabel *Label6;
    TRadioButton *RdoBtn_Data1;
    TEdit *edt_Min;
    TEdit *edt_Max;
    TRadioButton *RdoBtn_Data2;
    TEdit *edt_Fill;
    TCheckBox *chkbox_DLE_Data;
    TGroupBox *GroupBox10;
    TRadioButton *chkbox_TxYes;
    TRadioButton *chkbox_TxNo;
    TEdit *edt_CustomData;
    TCheckBox *chkbox_OnLineChat;
    TCheckBox *chkbox_ForceKeyPress;
    TTabSheet *TabSheet2;
    TGroupBox *GroupBox15;
    TPanel *Panel15;
    TEdit *edt_ListenInitCmd;
    TPanel *Panel16;
    TEdit *edt_ATCmd1;
    TPanel *Panel17;
    TEdit *edt_ATCmd2;
    TPanel *Panel18;
    TEdit *edt_RingCallNum;
    TBitBtn *bbtn_ListenDefault;
    TPanel *Panel23;
    TEdit *edt_EndATCmd;
    TGroupBox *GroupBox16;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TEdit *edt_QueryATCmd;
    TPanel *Panel20;
    TTrackBar *tkbar_QuerySensitive;
    TPanel *Panel21;
    TBitBtn *bbtn_QueryDefault;
    TGroupBox *GroupBox17;
    TLabel *Label20;
    TLabel *Label21;
    TLabel *Label22;
    TLabel *Label23;
    TPanel *Panel24;
    TEdit *edt_DialupInitCmd;
    TBitBtn *bbtn_DialupDefault;
    TTrackBar *tkbar_DialupSpeed;
    TPanel *Panel25;
    TTabSheet *TabSheet3;
    TLabel *Label16;
    TLabel *Label17;
    TCheckBox *chkbox_AutoStop;
    TGroupBox *GroupBox13;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label14;
    TTrackBar *tkbar_SpeakerVol;
    TBitBtn *bbtn_VolDefault;
    TGroupBox *GroupBox14;
    TLabel *Label15;
    TCheckBox *chkbox_AlwaysRedial;
    TEdit *edt_RedialTimes;
    TPanel *Panel19;
    TCheckBox *chkbox_EnableRedial;
    TPanel *Panel22;
    TEdit *edt_RedialDelay;
    TCheckBox *chkbox_HangUp;
    TEdit *edt_OnLineIdleTime;
    TCheckBox *chkbox_StopDialup;
    TEdit *edt_DialupIdleTime;
    TCheckBox *chkbox_AutoErrStop;
    TMemo *Memo1;
    TServerSocket *ServerSocket1;
    TIdIPWatch *IdIPWatch1;
    TPanel *Panel26;
    TButton *Button1;
    TLabeledEdit *LabeledEdit1;
    TEdit *edtInputLen;
    TLabel *Label24;
    TButton *Button4;
    TGroupBox *GroupBox18;
    TComboBox *cboxCOMPort;
    TComboBox *cboxBaud;
    TComboBox *cboxParity;
    TComboBox *cboxDataBit;
    TComboBox *cboxStopBit;
    TGroupBox *GroupBox19;
    TComboBox *ComboBox1;
    TComboBox *ComboBox2;
    TComboBox *ComboBox3;
    TComboBox *ComboBox4;
    TComboBox *ComboBox5;
    TLabel *Label25;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall bbtn_ExitClick(TObject *Sender);
    void __fastcall bbtn_QueryClick(TObject *Sender);
    void __fastcall tmrQueryTimer(TObject *Sender);
    void __fastcall bbtn_ListenClick(TObject *Sender);
    void __fastcall tmrRxTimer(TObject *Sender);
    void __fastcall bbtn_StopClick(TObject *Sender);
    void __fastcall chkbox_EnableTxClick(TObject *Sender);
    void __fastcall RdoBtn_AutoSendClick(TObject *Sender);
    void __fastcall RdoBtn_AutoReverseClick(TObject *Sender);
    void __fastcall RdoBtn_StartLenClick(TObject *Sender);
    void __fastcall RdoBtn_FixedLenClick(TObject *Sender);
    void __fastcall bbtn_AboutClick(TObject *Sender);
    void __fastcall bbtn_TxClearClick(TObject *Sender);
    void __fastcall bbtn_RxClearClick(TObject *Sender);
    void __fastcall tmrTxTimer(TObject *Sender);
    void __fastcall chkbox_EnableTx_DirectlyClick(TObject *Sender);
    void __fastcall tmrModemStatusTimer(TObject *Sender);
    void __fastcall btn_DTROnClick(TObject *Sender);
    void __fastcall btn_DTROffClick(TObject *Sender);
    void __fastcall btn_RTSOnClick(TObject *Sender);
    void __fastcall btn_RTSOffClick(TObject *Sender);
    void __fastcall chkbox_TxYesClick(TObject *Sender);
    void __fastcall chkbox_TxNoClick(TObject *Sender);
    void __fastcall bbtn_DialUpClick(TObject *Sender);
    void __fastcall mTXKeyPress(TObject *Sender, char &Key);
    void __fastcall edt_StartLenChange(TObject *Sender);
    void __fastcall edt_FixedLenChange(TObject *Sender);
    void __fastcall Panel2Click(TObject *Sender);
    void __fastcall mRXKeyPress(TObject *Sender, char &Key);
    void __fastcall Panel5Click(TObject *Sender);
    void __fastcall Panel6Click(TObject *Sender);
    void __fastcall bbtn_Control_CloseClick(TObject *Sender);
    void __fastcall chkbox_ForceKeyPressClick(TObject *Sender);
    void __fastcall chkbox_OnLineChatClick(TObject *Sender);
    void __fastcall RdoBtn_CustomLenClick(TObject *Sender);
    void __fastcall edt_CustomDataChange(TObject *Sender);
    void __fastcall edt_CustomDataKeyPress(TObject *Sender, char &Key);
    void __fastcall bbtn_ListenDefaultClick(TObject *Sender);
    void __fastcall bbtn_QueryDefaultClick(TObject *Sender);
    void __fastcall bbtn_VolDefaultClick(TObject *Sender);
    void __fastcall edt_RedialTimesChange(TObject *Sender);
    void __fastcall chkbox_AlwaysRedialClick(TObject *Sender);
    void __fastcall chkbox_EnableRedialClick(TObject *Sender);
    void __fastcall RdoBtn_SpeakerOnClick(TObject *Sender);
    void __fastcall RdoBtn_SpeakerOffClick(TObject *Sender);
    void __fastcall bbtn_DialupDefaultClick(TObject *Sender);
    void __fastcall btnConnectionClick(TObject *Sender);
    void __fastcall btnSendClick(TObject *Sender);
    void __fastcall btnCloseClick(TObject *Sender);
    void __fastcall btnExitClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button5Click(TObject *Sender);
    void __fastcall ServerSocket1ClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ServerSocket1ClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall ServerSocket1ClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
    void __fastcall ServerSocket1ClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
    void __fastcall Button6Click(TObject *Sender);
    void __fastcall Button7Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif

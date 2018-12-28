//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TRichEdit *rchedt_TestInfoA;
    TRadioGroup *rdgp_RS232A;
    TGroupBox *GroupBox5;
    TLabel *Label1;
    TComboBox *cbox_BaudrateA;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TComboBox *cbox_ParityA;
    TComboBox *cbox_DataBitA;
    TComboBox *cbox_StopBitA;
    TGroupBox *GroupBox6;
    TRadioButton *RdoBtn_AutoReverseA;
    TRadioButton *RdoBtn_AutoSendA;
    TEdit *edt_DelayA;
    TLabel *Label6;
    TLabel *Label5;
    TMemo *mTxA;
    TMemo *mRxA;
    TLabel *Label10;
    TLabel *Label11;
    TBitBtn *bbtn_OpenA;
    TBitBtn *bbtn_CloseA;
    TBitBtn *bbtn_ClearA;
    TTimer *tmrRxA;
    TTimer *tmrTxA;
    TShape *spTxA;
    TShape *spRxA;
    TEdit *edt_RXLenA;
    TEdit *edt_TXLenA;
    TEdit *edt_counterA;
    TEdit *edt_ClearLinesA;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall bbtn_OpenAClick(TObject *Sender);
    void __fastcall tmrRxATimer(TObject *Sender);
    void __fastcall bbtn_CloseAClick(TObject *Sender);
    void __fastcall bbtn_ClearAClick(TObject *Sender);
    void __fastcall tmrTxATimer(TObject *Sender);
    void __fastcall mTxAKeyPress(TObject *Sender, char &Key);
    /*void __fastcall bbtn_OpenBClick(TObject *Sender);
    void __fastcall tmrRxBTimer(TObject *Sender);
    void __fastcall bbtn_CloseBClick(TObject *Sender);
    void __fastcall bbtn_ClearBClick(TObject *Sender);
    void __fastcall tmrTxBTimer(TObject *Sender);
    void __fastcall mTxBKeyPress(TObject *Sender, char &Key);
    void __fastcall bbtn_OpenCClick(TObject *Sender);
    void __fastcall tmrRxCTimer(TObject *Sender);
    void __fastcall bbtn_CloseCClick(TObject *Sender);
    void __fastcall bbtn_ClearCClick(TObject *Sender);
    void __fastcall tmrTxCTimer(TObject *Sender);
    void __fastcall mTxCKeyPress(TObject *Sender, char &Key);
    void __fastcall bbtn_OpenDClick(TObject *Sender);
    void __fastcall tmrRxDTimer(TObject *Sender);
    void __fastcall bbtn_CloseDClick(TObject *Sender);
    void __fastcall bbtn_ClearDClick(TObject *Sender);
    void __fastcall tmrTxDTimer(TObject *Sender);
    void __fastcall mTxDKeyPress(TObject *Sender, char &Key);*/
private:	// User declarations
public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif

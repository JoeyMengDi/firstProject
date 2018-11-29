//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "About.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TfrmAbout *frmAbout;
//---------------------------------------------------------------------------
__fastcall TfrmAbout::TfrmAbout(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TfrmAbout::FormCreate(TObject *Sender)
{
frmAbout->Left = (Screen->Width - frmAbout->Width)/2;
frmAbout->Top = (Screen->Height - frmAbout->Height)/2;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAbout::BitBtn1Click(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------

void __fastcall TfrmAbout::Label4MouseEnter(TObject *Sender)
{
  Label4->Cursor = crHandPoint;
}
//---------------------------------------------------------------------------


void __fastcall TfrmAbout::Label4Click(TObject *Sender)
{
     ShellExecute(NULL, NULL, "http://www.casauto.com.tw",NULL, NULL, SW_SHOW);
}
//---------------------------------------------------------------------------


object frmMain: TfrmMain
  Left = 188
  Top = 111
  BorderStyle = bsDialog
  Caption = 'RS232 '
  ClientHeight = 341
  ClientWidth = 430
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 8
    Width = 433
    Height = 345
    Caption = 'RS232 '
    Font.Charset = ANSI_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object Label10: TLabel
      Left = 32
      Top = 163
      Width = 17
      Height = 16
      Caption = 'TX'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label11: TLabel
      Left = 240
      Top = 163
      Width = 18
      Height = 16
      Caption = 'RX'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object spTxA: TShape
      Left = 8
      Top = 163
      Width = 17
      Height = 17
      Shape = stRoundSquare
    end
    object spRxA: TShape
      Left = 216
      Top = 163
      Width = 17
      Height = 17
      Shape = stRoundSquare
    end
    object rchedt_TestInfoA: TRichEdit
      Left = 264
      Top = 112
      Width = 161
      Height = 41
      Color = clSilver
      Font.Charset = CHINESEBIG5_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      ParentFont = False
      TabOrder = 0
    end
    object rdgp_RS232A: TRadioGroup
      Left = 8
      Top = 16
      Width = 81
      Height = 137
      Caption = 'COM Port'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ItemIndex = 0
      Items.Strings = (
        'COM1'
        'COM2'
        'COM3')
      ParentFont = False
      TabOrder = 1
    end
    object GroupBox5: TGroupBox
      Left = 96
      Top = 16
      Width = 161
      Height = 137
      Caption = 'COM Setting'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      object Label1: TLabel
        Left = 7
        Top = 25
        Width = 66
        Height = 16
        Caption = 'Baudrate :'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label7: TLabel
        Left = 7
        Top = 51
        Width = 45
        Height = 16
        Caption = 'Parity :'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label8: TLabel
        Left = 7
        Top = 75
        Width = 60
        Height = 16
        Caption = 'DataBits :'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label9: TLabel
        Left = 7
        Top = 101
        Width = 60
        Height = 16
        Caption = 'StopBits :'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object cbox_BaudrateA: TComboBox
        Left = 80
        Top = 25
        Width = 73
        Height = 24
        Color = clBlack
        Font.Charset = ANSI_CHARSET
        Font.Color = clYellow
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
        ItemHeight = 16
        ItemIndex = 0
        ParentFont = False
        TabOrder = 0
        Text = '115200'
        Items.Strings = (
          '115200'
          '57600'
          '38400'
          '19200'
          '9600'
          '4800'
          '2400'
          '1200'
          '600'
          '300')
      end
      object cbox_ParityA: TComboBox
        Left = 80
        Top = 49
        Width = 73
        Height = 24
        Color = clBlack
        Font.Charset = ANSI_CHARSET
        Font.Color = clYellow
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
        ItemHeight = 16
        ParentFont = False
        TabOrder = 1
        Text = 'N'
        Items.Strings = (
          'N'
          'O'
          'E'
          'M'
          'S')
      end
      object cbox_DataBitA: TComboBox
        Left = 80
        Top = 73
        Width = 73
        Height = 24
        Color = clBlack
        Font.Charset = ANSI_CHARSET
        Font.Color = clYellow
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
        ItemHeight = 16
        ItemIndex = 4
        ParentFont = False
        TabOrder = 2
        Text = '8'
        Items.Strings = (
          '4'
          '5'
          '6'
          '7'
          '8')
      end
      object cbox_StopBitA: TComboBox
        Left = 80
        Top = 97
        Width = 73
        Height = 24
        Color = clBlack
        Font.Charset = ANSI_CHARSET
        Font.Color = clYellow
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
        ItemHeight = 16
        ParentFont = False
        TabOrder = 3
        Text = '1'
        Items.Strings = (
          '1'
          '1.5'
          '2')
      end
    end
    object GroupBox6: TGroupBox
      Left = 264
      Top = 16
      Width = 161
      Height = 97
      Caption = 'Action'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      object Label6: TLabel
        Left = 9
        Top = 75
        Width = 80
        Height = 16
        Caption = 'Clear Lines :'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label5: TLabel
        Left = 9
        Top = 52
        Width = 44
        Height = 16
        Caption = 'Delay :'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object edt_ClearLinesA: TEdit
        Left = 104
        Top = 73
        Width = 41
        Height = 23
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'Arial'
        Font.Style = []
        ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
        ParentFont = False
        TabOrder = 0
        Text = '500'
      end
    end
    object RdoBtn_AutoReverseA: TRadioButton
      Left = 272
      Top = 32
      Width = 113
      Height = 17
      Caption = 'Auto Reverse'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
    end
    object RdoBtn_AutoSendA: TRadioButton
      Left = 272
      Top = 48
      Width = 113
      Height = 17
      Caption = 'Auto Send'
      Checked = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      TabStop = True
    end
    object edt_DelayA: TEdit
      Left = 368
      Top = 64
      Width = 41
      Height = 23
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'Arial'
      Font.Style = []
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      ParentFont = False
      TabOrder = 6
      Text = '2'
    end
    object mTxA: TMemo
      Left = 8
      Top = 182
      Width = 209
      Height = 121
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      Lines.Strings = (
        'abc')
      ParentFont = False
      ScrollBars = ssVertical
      TabOrder = 7
      OnKeyPress = mTxAKeyPress
    end
    object mRxA: TMemo
      Left = 216
      Top = 182
      Width = 209
      Height = 121
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      ParentFont = False
      ScrollBars = ssVertical
      TabOrder = 8
    end
    object bbtn_OpenA: TBitBtn
      Left = 32
      Top = 302
      Width = 75
      Height = 25
      Cursor = crHandPoint
      Caption = 'Open'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 9
      OnClick = bbtn_OpenAClick
    end
    object bbtn_CloseA: TBitBtn
      Left = 176
      Top = 302
      Width = 75
      Height = 25
      Cursor = crHandPoint
      Caption = 'Close'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 10
      OnClick = bbtn_CloseAClick
    end
    object bbtn_ClearA: TBitBtn
      Left = 320
      Top = 302
      Width = 75
      Height = 25
      Cursor = crHandPoint
      Caption = 'Clear'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 11
      OnClick = bbtn_ClearAClick
    end
    object edt_RXLenA: TEdit
      Left = 360
      Top = 158
      Width = 49
      Height = 22
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      ParentFont = False
      TabOrder = 12
    end
    object edt_TXLenA: TEdit
      Left = 152
      Top = 158
      Width = 49
      Height = 22
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      ParentFont = False
      TabOrder = 13
    end
    object edt_counterA: TEdit
      Left = 384
      Top = 128
      Width = 41
      Height = 22
      Color = clSilver
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = []
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      ParentFont = False
      TabOrder = 14
    end
  end
  object tmrRxA: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tmrRxATimer
    Left = 632
    Top = 568
  end
  object tmrTxA: TTimer
    Enabled = False
    OnTimer = tmrTxATimer
    Left = 664
    Top = 568
  end
end

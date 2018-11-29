object frmMain: TfrmMain
  Left = 30
  Top = 78
  BorderStyle = bsDialog
  Caption = 'Communication Utility'
  ClientHeight = 965
  ClientWidth = 1229
  Color = clBackground
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object bbtn_TxClear: TBitBtn
    Left = 8
    Top = 824
    Width = 65
    Height = 41
    Cursor = crHandPoint
    Caption = 'TX Clear'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnClick = bbtn_TxClearClick
  end
  object bbtn_RxClear: TBitBtn
    Left = 80
    Top = 824
    Width = 65
    Height = 41
    Cursor = crHandPoint
    Caption = 'RX Clear'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    OnClick = bbtn_RxClearClick
  end
  object pnl_Switch_Control: TPanel
    Left = 448
    Top = 829
    Width = 145
    Height = 129
    Caption = 'pnl_Switch_Control'
    Color = clBlack
    TabOrder = 2
    Visible = False
    object GroupBox9: TGroupBox
      Left = 16
      Top = 16
      Width = 113
      Height = 49
      Caption = 'DTR'
      Font.Charset = ANSI_CHARSET
      Font.Color = clLime
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      object btn_DTROn: TButton
        Left = 16
        Top = 16
        Width = 33
        Height = 25
        Cursor = crHandPoint
        Caption = 'ON'
        TabOrder = 0
        OnClick = btn_DTROnClick
      end
      object btn_DTROff: TButton
        Left = 64
        Top = 16
        Width = 33
        Height = 25
        Cursor = crHandPoint
        Caption = 'OFF'
        TabOrder = 1
        OnClick = btn_DTROffClick
      end
    end
    object GroupBox8: TGroupBox
      Left = 16
      Top = 64
      Width = 113
      Height = 49
      Caption = 'RTS'
      Font.Charset = ANSI_CHARSET
      Font.Color = clLime
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      object btn_RTSOn: TButton
        Left = 16
        Top = 16
        Width = 33
        Height = 25
        Cursor = crHandPoint
        Caption = 'ON'
        TabOrder = 0
        OnClick = btn_RTSOnClick
      end
      object btn_RTSOff: TButton
        Left = 64
        Top = 16
        Width = 33
        Height = 25
        Cursor = crHandPoint
        Caption = 'OFF'
        TabOrder = 1
        OnClick = btn_RTSOffClick
      end
    end
    object bbtn_Control_Close: TBitBtn
      Left = 128
      Top = 0
      Width = 17
      Height = 17
      Caption = 'X'
      TabOrder = 2
      OnClick = bbtn_Control_CloseClick
    end
  end
  object TPageControl
    Left = 8
    Top = 8
    Width = 1217
    Height = 809
    ActivePage = TabSheet4
    TabIndex = 0
    TabOrder = 3
    object TabSheet4: TTabSheet
      Caption = 'Modem'
      object Panel1: TPanel
        Left = 8
        Top = 5
        Width = 801
        Height = 65
        BorderStyle = bsSingle
        Color = clBlack
        TabOrder = 0
        object bbtn_Query: TBitBtn
          Left = 24
          Top = 8
          Width = 113
          Height = 41
          Cursor = crHandPoint
          Caption = '&Query'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnClick = bbtn_QueryClick
          Glyph.Data = {
            DE010000424DDE01000000000000760000002800000024000000120000000100
            0400000000006801000000000000000000001000000000000000000000000000
            80000080000000808000800000008000800080800000C0C0C000808080000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333444444
            33333333333F8888883F33330000324334222222443333388F3833333388F333
            000032244222222222433338F8833FFFFF338F3300003222222AAAAA22243338
            F333F88888F338F30000322222A33333A2224338F33F8333338F338F00003222
            223333333A224338F33833333338F38F00003222222333333A444338FFFF8F33
            3338888300003AAAAAAA33333333333888888833333333330000333333333333
            333333333333333333FFFFFF000033333333333344444433FFFF333333888888
            00003A444333333A22222438888F333338F3333800003A2243333333A2222438
            F38F333333833338000033A224333334422224338338FFFFF8833338000033A2
            22444442222224338F3388888333FF380000333A2222222222AA243338FF3333
            33FF88F800003333AA222222AA33A3333388FFFFFF8833830000333333AAAAAA
            3333333333338888883333330000333333333333333333333333333333333333
            0000}
          NumGlyphs = 2
        end
        object bbtn_Listen: TBitBtn
          Left = 152
          Top = 8
          Width = 113
          Height = 41
          Cursor = crHandPoint
          Caption = '&Listen'
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          OnClick = bbtn_ListenClick
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF003B3000000000
            003B37F77777777777F73BB09111111110BB3777F3F3F3F3F777311098080808
            10B33777F7373737377313309999999910337F373F3F3F3F3733133309808089
            03337F3373737373733313333099999033337FFFF7FFFFF7FFFFB011B0000000
            BBBB7777777777777777B01110BBBBB0BBBB77F37777777777773011108BB333
            333337F337377F3FFFF33099111BB3010033373F33777F77773F331999100101
            11033373FFF77773337F33300099991999033337773FFFF33373333BB7100199
            113333377377773FF7F333BB333BB7011B33337733377F7777FF3BB3333BB333
            3BB3377333377F33377FBB33333BB33333BB7733333773333377}
          NumGlyphs = 2
        end
        object bbtn_Stop: TBitBtn
          Left = 280
          Top = 8
          Width = 113
          Height = 41
          Cursor = crHandPoint
          Caption = 'Sto&p'
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          OnClick = bbtn_StopClick
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000130B0000130B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
            3333333333FFFFF3333333333999993333333333F77777FFF333333999999999
            33333337777FF377FF3333993370739993333377FF373F377FF3399993000339
            993337777F777F3377F3393999707333993337F77737333337FF993399933333
            399377F3777FF333377F993339903333399377F33737FF33377F993333707333
            399377F333377FF3377F993333101933399377F333777FFF377F993333000993
            399377FF3377737FF7733993330009993933373FF3777377F7F3399933000399
            99333773FF777F777733339993707339933333773FF7FFF77333333999999999
            3333333777333777333333333999993333333333377777333333}
          NumGlyphs = 2
        end
        object bbtn_DialUp: TBitBtn
          Left = 408
          Top = 8
          Width = 113
          Height = 41
          Cursor = crHandPoint
          Caption = '&Dialup'
          Enabled = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
          OnClick = bbtn_DialUpClick
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333000000000
            003333377777777777F3333091111111103333F7F3F3F3F3F7F3311098080808
            10333777F737373737F313309999999910337F373F3F3F3F3733133309808089
            03337FFF7F7373737FFF1000109999901000777777FFFFF77777701110000000
            111037F337777777F3373099901111109990373F373333373337330999999999
            99033373FFFFFFFFFF7333310000000001333337777777777733333333333333
            3333333333333333333333333333333333333333333333333333333333333333
            3333333333333333333333333333333333333333333333333333333333333333
            3333333333333333333333333333333333333333333333333333}
          NumGlyphs = 2
        end
        object bbtn_About: TBitBtn
          Left = 536
          Top = 8
          Width = 113
          Height = 41
          Cursor = crHandPoint
          Caption = '&About'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
          OnClick = bbtn_AboutClick
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
            3333333333FFFFF3333333333F797F3333333333F737373FF333333BFB999BFB
            33333337737773773F3333BFBF797FBFB33333733337333373F33BFBFBFBFBFB
            FB3337F33333F33337F33FBFBFB9BFBFBF3337333337F333373FFBFBFBF97BFB
            FBF37F333337FF33337FBFBFBFB99FBFBFB37F3333377FF3337FFBFBFBFB99FB
            FBF37F33333377FF337FBFBF77BF799FBFB37F333FF3377F337FFBFB99FB799B
            FBF373F377F3377F33733FBF997F799FBF3337F377FFF77337F33BFBF99999FB
            FB33373F37777733373333BFBF999FBFB3333373FF77733F7333333BFBFBFBFB
            3333333773FFFF77333333333FBFBF3333333333377777333333}
          NumGlyphs = 2
        end
        object bbtn_Exit: TBitBtn
          Left = 664
          Top = 8
          Width = 113
          Height = 41
          Cursor = crHandPoint
          Caption = 'E&xit'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 5
          OnClick = bbtn_ExitClick
          Glyph.Data = {
            76010000424D7601000000000000760000002800000020000000100000000100
            04000000000000010000120B0000120B00001000000000000000000000000000
            800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0033BBBBBBBBBB
            BB33337777777777777F33BB00BBBBBBBB33337F77333333F37F33BB0BBBBBB0
            BB33337F73F33337FF7F33BBB0BBBB000B33337F37FF3377737F33BBB00BB00B
            BB33337F377F3773337F33BBBB0B00BBBB33337F337F7733337F33BBBB000BBB
            BB33337F33777F33337F33EEEE000EEEEE33337F3F777FFF337F33EE0E80000E
            EE33337F73F77773337F33EEE0800EEEEE33337F37377F33337F33EEEE000EEE
            EE33337F33777F33337F33EEEEE00EEEEE33337F33377FF3337F33EEEEEE00EE
            EE33337F333377F3337F33EEEEEE00EEEE33337F33337733337F33EEEEEEEEEE
            EE33337FFFFFFFFFFF7F33EEEEEEEEEEEE333377777777777773}
          NumGlyphs = 2
        end
      end
      object rdgp_COM: TRadioGroup
        Left = 8
        Top = 77
        Width = 537
        Height = 57
        Caption = 'Port'
        Columns = 6
        Font.Charset = ANSI_CHARSET
        Font.Color = clLime
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ItemIndex = 0
        Items.Strings = (
          'COM1'
          'COM2'
          'COM3'
          'COM4'
          'COM5'
          'COM6')
        ParentFont = False
        TabOrder = 1
      end
      object GroupBox1: TGroupBox
        Left = 552
        Top = 85
        Width = 257
        Height = 137
        Caption = #9679' '#9679' '#9679' '#9679' '#9679' '#9679' '#9679' '#9679' '#9679' '#9679' '#9679' '#9679' '#9679' '#9679' '#9679' '#9679' '#9679' '#9679' '#9679' '#9679' '
        Color = clGray
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentColor = False
        ParentFont = False
        TabOrder = 2
        object rchedt_TestInfo: TRichEdit
          Left = 8
          Top = 16
          Width = 241
          Height = 113
          Alignment = taCenter
          Color = clBlack
          Font.Charset = CHINESEBIG5_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
          ParentFont = False
          TabOrder = 0
        end
      end
      object GroupBox2: TGroupBox
        Left = 8
        Top = 149
        Width = 73
        Height = 73
        Caption = 'Speaker'
        Font.Charset = ANSI_CHARSET
        Font.Color = clLime
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        object RdoBtn_SpeakerOn: TRadioButton
          Left = 8
          Top = 24
          Width = 57
          Height = 17
          Caption = 'ON'
          Checked = True
          TabOrder = 0
          TabStop = True
          OnClick = RdoBtn_SpeakerOnClick
        end
        object RdoBtn_SpeakerOff: TRadioButton
          Left = 8
          Top = 48
          Width = 57
          Height = 17
          Caption = 'OFF'
          TabOrder = 1
          OnClick = RdoBtn_SpeakerOffClick
        end
      end
      object GroupBox3: TGroupBox
        Left = 80
        Top = 149
        Width = 81
        Height = 73
        Caption = 'AT Cmd'
        Font.Charset = ANSI_CHARSET
        Font.Color = clLime
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 4
        object RdoBtn_Cmd1: TRadioButton
          Left = 8
          Top = 24
          Width = 57
          Height = 17
          Caption = 'Cmd1'
          TabOrder = 0
        end
        object RdoBtn_Cmd2: TRadioButton
          Left = 8
          Top = 48
          Width = 57
          Height = 17
          Caption = 'Cmd2'
          Checked = True
          TabOrder = 1
          TabStop = True
        end
      end
      object GroupBox6: TGroupBox
        Left = 160
        Top = 149
        Width = 105
        Height = 73
        Caption = 'Dial Up'
        Font.Charset = ANSI_CHARSET
        Font.Color = clLime
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 5
        object Label5: TLabel
          Left = 8
          Top = 24
          Width = 78
          Height = 16
          Caption = 'Phone Num.'
          Font.Charset = ANSI_CHARSET
          Font.Color = clLime
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold, fsUnderline]
          ParentFont = False
        end
        object edt_PhoneNum: TEdit
          Left = 8
          Top = 44
          Width = 89
          Height = 24
          Color = clBlack
          Font.Charset = ANSI_CHARSET
          Font.Color = clLime
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
          ParentFont = False
          TabOrder = 0
          Text = '*604'
        end
      end
      object gpbox_Baudrate: TGroupBox
        Left = 264
        Top = 149
        Width = 105
        Height = 73
        Caption = 'Baudrate'
        Font.Charset = ANSI_CHARSET
        Font.Color = clLime
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 6
        object cbox_Baudrate: TComboBox
          Left = 5
          Top = 33
          Width = 97
          Height = 24
          Color = clBlack
          Font.Charset = ANSI_CHARSET
          Font.Color = clLime
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
          ItemHeight = 16
          ItemIndex = 2
          ParentFont = False
          TabOrder = 0
          Text = '38400'
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
      end
      object GroupBox12: TGroupBox
        Left = 368
        Top = 149
        Width = 177
        Height = 73
        Caption = 'Log'
        Font.Charset = ANSI_CHARSET
        Font.Color = clLime
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 7
        object edt_Lines: TEdit
          Left = 104
          Top = 20
          Width = 65
          Height = 24
          Color = clBlack
          Font.Charset = ANSI_CHARSET
          Font.Color = clLime
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
          ParentFont = False
          TabOrder = 0
          Text = '500'
        end
        object ChkBox_ClearLines: TCheckBox
          Left = 8
          Top = 24
          Width = 97
          Height = 17
          Caption = 'Clear Lines'
          Checked = True
          Font.Charset = ANSI_CHARSET
          Font.Color = clLime
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          State = cbChecked
          TabOrder = 1
        end
        object ChkBox_SetLog: TCheckBox
          Left = 8
          Top = 48
          Width = 89
          Height = 17
          Caption = 'Save Log'
          Font.Charset = ANSI_CHARSET
          Font.Color = clLime
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
        end
      end
      object Panel2: TPanel
        Left = 8
        Top = 229
        Width = 801
        Height = 17
        Cursor = crHandPoint
        Caption = #8595
        Color = clBlack
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 8
        OnClick = Panel2Click
      end
      object mTX: TMemo
        Left = 800
        Top = 269
        Width = 401
        Height = 201
        BevelKind = bkSoft
        BorderStyle = bsNone
        Color = clBlack
        Font.Charset = CHINESEBIG5_CHARSET
        Font.Color = clFuchsia
        Font.Height = -16
        Font.Name = 'System'
        Font.Style = [fsBold]
        ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
        ParentFont = False
        TabOrder = 9
        OnKeyPress = mTXKeyPress
      end
      object mRX: TMemo
        Left = 800
        Top = 476
        Width = 401
        Height = 209
        BevelKind = bkSoft
        BorderStyle = bsNone
        Color = clBlack
        Font.Charset = CHINESEBIG5_CHARSET
        Font.Color = clYellow
        Font.Height = -16
        Font.Name = 'System'
        Font.Style = [fsBold]
        ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
        ParentFont = False
        TabOrder = 10
        OnKeyPress = mRXKeyPress
      end
      object GroupBox7: TGroupBox
        Left = 8
        Top = 700
        Width = 801
        Height = 69
        Caption = 'Modem Status'
        Font.Charset = ANSI_CHARSET
        Font.Color = clLime
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 11
        object sp_RTS: TShape
          Left = 70
          Top = 24
          Width = 41
          Height = 17
          Shape = stSquare
        end
        object sp_DSR: TShape
          Left = 126
          Top = 24
          Width = 41
          Height = 17
          Shape = stSquare
        end
        object sp_CTS: TShape
          Left = 182
          Top = 24
          Width = 41
          Height = 17
          Shape = stSquare
        end
        object sp_RING: TShape
          Left = 236
          Top = 23
          Width = 41
          Height = 17
          Shape = stSquare
        end
        object sp_CD: TShape
          Left = 292
          Top = 23
          Width = 41
          Height = 17
          Shape = stSquare
        end
        object sp_OH: TShape
          Left = 348
          Top = 23
          Width = 41
          Height = 17
          Shape = stSquare
        end
        object sp_DTR: TShape
          Left = 14
          Top = 24
          Width = 41
          Height = 17
          Shape = stSquare
        end
        object sp_AA: TShape
          Left = 404
          Top = 23
          Width = 41
          Height = 17
          Shape = stSquare
        end
        object spTX: TShape
          Left = 460
          Top = 24
          Width = 41
          Height = 17
          Shape = stSquare
        end
        object spRX: TShape
          Left = 516
          Top = 24
          Width = 41
          Height = 17
          Shape = stSquare
        end
        object Panel5: TPanel
          Left = 14
          Top = 39
          Width = 41
          Height = 17
          Cursor = crHandPoint
          Caption = 'DTR'
          Color = clBlack
          Font.Charset = ANSI_CHARSET
          Font.Color = clYellow
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnClick = Panel5Click
        end
        object Panel6: TPanel
          Left = 70
          Top = 39
          Width = 41
          Height = 17
          Cursor = crHandPoint
          Caption = 'RTS'
          Color = clBlack
          Font.Charset = ANSI_CHARSET
          Font.Color = clYellow
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          OnClick = Panel6Click
        end
        object Panel7: TPanel
          Left = 126
          Top = 39
          Width = 41
          Height = 17
          Caption = 'DSR'
          Color = clBlack
          Font.Charset = ANSI_CHARSET
          Font.Color = clYellow
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
        end
        object Panel8: TPanel
          Left = 182
          Top = 39
          Width = 41
          Height = 17
          Caption = 'CTS'
          Color = clBlack
          Font.Charset = ANSI_CHARSET
          Font.Color = clYellow
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
        end
        object Panel9: TPanel
          Left = 236
          Top = 39
          Width = 41
          Height = 17
          Caption = 'RI'
          Color = clBlack
          Font.Charset = ANSI_CHARSET
          Font.Color = clYellow
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
        end
        object Panel10: TPanel
          Left = 292
          Top = 39
          Width = 41
          Height = 17
          Caption = 'CD'
          Color = clBlack
          Font.Charset = ANSI_CHARSET
          Font.Color = clYellow
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 5
        end
        object Panel12: TPanel
          Left = 348
          Top = 39
          Width = 41
          Height = 17
          Caption = 'OH'
          Color = clBlack
          Font.Charset = ANSI_CHARSET
          Font.Color = clYellow
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 6
        end
        object Panel11: TPanel
          Left = 404
          Top = 39
          Width = 41
          Height = 17
          Caption = 'AA'
          Color = clBlack
          Font.Charset = ANSI_CHARSET
          Font.Color = clYellow
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 7
        end
        object Panel3: TPanel
          Left = 460
          Top = 40
          Width = 41
          Height = 16
          Caption = 'TX'
          Color = clBlack
          Font.Charset = ANSI_CHARSET
          Font.Color = clYellow
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 8
        end
        object edt_TXLen: TEdit
          Left = 568
          Top = 24
          Width = 73
          Height = 32
          Color = clBlack
          Font.Charset = ANSI_CHARSET
          Font.Color = clFuchsia
          Font.Height = -21
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
          ParentFont = False
          TabOrder = 9
        end
        object edt_RXLen: TEdit
          Left = 640
          Top = 24
          Width = 73
          Height = 32
          Color = clBlack
          Font.Charset = ANSI_CHARSET
          Font.Color = clYellow
          Font.Height = -21
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
          ParentFont = False
          TabOrder = 10
        end
        object Panel13: TPanel
          Left = 516
          Top = 39
          Width = 41
          Height = 17
          Caption = 'RX'
          Color = clBlack
          Font.Charset = ANSI_CHARSET
          Font.Color = clYellow
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 11
        end
        object edt_counter: TEdit
          Left = 712
          Top = 24
          Width = 81
          Height = 32
          Color = clBlack
          Font.Charset = ANSI_CHARSET
          Font.Color = clAqua
          Font.Height = -21
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
          ParentFont = False
          TabOrder = 12
        end
      end
      object gpbox_Utility_Setting: TGroupBox
        Left = 0
        Top = 260
        Width = 793
        Height = 437
        Caption = 'Utility Setting'
        Color = clBlack
        Font.Charset = ANSI_CHARSET
        Font.Color = clYellow
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentColor = False
        ParentFont = False
        TabOrder = 12
        object PageControl1: TPageControl
          Left = 8
          Top = 24
          Width = 777
          Height = 393
          ActivePage = TabSheet1
          TabIndex = 0
          TabOrder = 0
          object TabSheet1: TTabSheet
            Caption = 'Tx Data'
            object Panel14: TPanel
              Left = 16
              Top = 273
              Width = 137
              Height = 33
              BorderStyle = bsSingle
              Caption = 'Custom Data ( HEX )'
              Color = clBlack
              TabOrder = 0
            end
            object GroupBox5: TGroupBox
              Left = 368
              Top = 104
              Width = 353
              Height = 81
              Caption = 'Tx Len'
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -13
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
              TabOrder = 1
              object Label3: TLabel
                Left = 168
                Top = 20
                Width = 49
                Height = 16
                Caption = '( bytes )'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object Label4: TLabel
                Left = 168
                Top = 52
                Width = 49
                Height = 16
                Caption = '( bytes )'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object RdoBtn_StartLen: TRadioButton
                Left = 8
                Top = 24
                Width = 81
                Height = 17
                Caption = 'Start Len'
                Checked = True
                Enabled = False
                TabOrder = 0
                TabStop = True
                OnClick = RdoBtn_StartLenClick
              end
              object RdoBtn_FixedLen: TRadioButton
                Left = 8
                Top = 56
                Width = 89
                Height = 17
                Caption = 'Fixed Len'
                Enabled = False
                TabOrder = 1
                OnClick = RdoBtn_FixedLenClick
              end
              object edt_StartLen: TEdit
                Left = 104
                Top = 16
                Width = 57
                Height = 24
                Color = clBlack
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
                ParentFont = False
                TabOrder = 2
                Text = '256'
                OnChange = edt_StartLenChange
              end
              object edt_FixedLen: TEdit
                Left = 104
                Top = 48
                Width = 57
                Height = 24
                Color = clBlack
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
                ParentFont = False
                TabOrder = 3
                Text = '256'
                OnChange = edt_FixedLenChange
              end
              object RdoBtn_CustomLen: TRadioButton
                Left = 240
                Top = 16
                Width = 105
                Height = 25
                Caption = 'Custom Len'
                Enabled = False
                TabOrder = 4
                OnClick = RdoBtn_CustomLenClick
              end
            end
            object GroupBox4: TGroupBox
              Left = 16
              Top = 104
              Width = 353
              Height = 81
              Caption = 'Tx Style'
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -13
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
              TabOrder = 2
              object Label1: TLabel
                Left = 232
                Top = 52
                Width = 21
                Height = 16
                Caption = 'per'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object Label2: TLabel
                Left = 304
                Top = 52
                Width = 34
                Height = 16
                Caption = '( ms )'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object Label18: TLabel
                Left = 8
                Top = 40
                Width = 36
                Height = 16
                Caption = 'Delay'
              end
              object Label19: TLabel
                Left = 136
                Top = 40
                Width = 74
                Height = 16
                Caption = '( ms ) To Tx'
              end
              object RdoBtn_AutoReverse: TRadioButton
                Left = 8
                Top = 60
                Width = 105
                Height = 17
                Caption = 'Auto Reverse'
                Checked = True
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 0
                TabStop = True
                OnClick = RdoBtn_AutoReverseClick
              end
              object RdoBtn_AutoSend: TRadioButton
                Left = 120
                Top = 60
                Width = 97
                Height = 17
                Caption = 'Auto Send'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 1
                OnClick = RdoBtn_AutoSendClick
              end
              object edt_AutoSend_Time: TEdit
                Left = 264
                Top = 46
                Width = 41
                Height = 24
                Color = clBlack
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
                ParentFont = False
                TabOrder = 2
                Text = '6000'
              end
              object chkbox_EnableTx: TCheckBox
                Left = 8
                Top = 16
                Width = 89
                Height = 17
                Caption = 'Rx  '#8594' Tx'
                Color = clBlack
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentColor = False
                ParentFont = False
                TabOrder = 3
                OnClick = chkbox_EnableTxClick
              end
              object Panel4: TPanel
                Left = 224
                Top = 12
                Width = 3
                Height = 65
                TabOrder = 4
              end
              object chkbox_EnableTx_Directly: TCheckBox
                Left = 232
                Top = 16
                Width = 97
                Height = 17
                Caption = 'Tx Directly'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 5
                OnClick = chkbox_EnableTx_DirectlyClick
              end
              object edt_TxDelayTime: TEdit
                Left = 56
                Top = 35
                Width = 73
                Height = 24
                Color = clBlack
                Enabled = False
                ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
                TabOrder = 6
                Text = '500'
              end
            end
            object GroupBox11: TGroupBox
              Left = 16
              Top = 200
              Width = 537
              Height = 57
              Caption = 'Tx Data ( HEX )'
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -13
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
              TabOrder = 3
              object Label6: TLabel
                Left = 264
                Top = 24
                Width = 23
                Height = 16
                Caption = '~0x'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object RdoBtn_Data1: TRadioButton
                Left = 208
                Top = 24
                Width = 33
                Height = 17
                Caption = '0x'
                Checked = True
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 0
                TabStop = True
              end
              object edt_Min: TEdit
                Left = 240
                Top = 21
                Width = 25
                Height = 24
                Color = clBlack
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
                ParentFont = False
                TabOrder = 1
                Text = '00'
              end
              object edt_Max: TEdit
                Left = 288
                Top = 21
                Width = 25
                Height = 24
                Color = clBlack
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
                ParentFont = False
                TabOrder = 2
                Text = 'FF'
              end
              object RdoBtn_Data2: TRadioButton
                Left = 360
                Top = 24
                Width = 73
                Height = 17
                Caption = 'Fill in 0x'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 3
              end
              object edt_Fill: TEdit
                Left = 432
                Top = 21
                Width = 25
                Height = 24
                Color = clBlack
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
                ParentFont = False
                TabOrder = 4
                Text = 'FF'
              end
              object chkbox_DLE_Data: TCheckBox
                Left = 8
                Top = 24
                Width = 169
                Height = 17
                Caption = 'Pack To DLE Protocol'
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 5
              end
            end
            object GroupBox10: TGroupBox
              Left = 16
              Top = 8
              Width = 73
              Height = 81
              Caption = 'EnableTx'
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -13
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
              TabOrder = 4
              object chkbox_TxYes: TRadioButton
                Left = 8
                Top = 24
                Width = 49
                Height = 17
                Caption = 'YES'
                TabOrder = 0
                OnClick = chkbox_TxYesClick
              end
              object chkbox_TxNo: TRadioButton
                Left = 8
                Top = 56
                Width = 49
                Height = 17
                Caption = 'NO'
                Checked = True
                TabOrder = 1
                TabStop = True
                OnClick = chkbox_TxNoClick
              end
            end
            object edt_CustomData: TEdit
              Left = 16
              Top = 322
              Width = 769
              Height = 24
              Color = clBlack
              Enabled = False
              Font.Charset = ANSI_CHARSET
              Font.Color = clWhite
              Font.Height = -13
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              ParentFont = False
              TabOrder = 5
              Text = '010203040506070809111213141516171819'
              OnChange = edt_CustomDataChange
              OnKeyPress = edt_CustomDataKeyPress
            end
            object chkbox_OnLineChat: TCheckBox
              Left = 120
              Top = 24
              Width = 385
              Height = 17
              Caption = 'Enable ON   Line Chat Communication . ( Key Press )'
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -13
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
              TabOrder = 6
              OnClick = chkbox_OnLineChatClick
            end
            object chkbox_ForceKeyPress: TCheckBox
              Left = 120
              Top = 64
              Width = 273
              Height = 17
              Caption = 'Enable OFF Line AT Cmd  Entry .'
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -13
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
              TabOrder = 7
              OnClick = chkbox_ForceKeyPressClick
            end
          end
          object TabSheet2: TTabSheet
            Caption = 'AT Cmd'
            ImageIndex = 1
            object GroupBox15: TGroupBox
              Left = 16
              Top = 104
              Width = 705
              Height = 137
              Caption = 'Listen'
              TabOrder = 0
              object Panel15: TPanel
                Left = 16
                Top = 24
                Width = 105
                Height = 25
                BorderStyle = bsSingle
                Caption = 'Initial Cmd'
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 0
              end
              object edt_ListenInitCmd: TEdit
                Left = 128
                Top = 24
                Width = 321
                Height = 24
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clRed
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
                ParentFont = False
                TabOrder = 1
                Text = 'AT &F E0 V1 &D2 &C1'
              end
              object Panel16: TPanel
                Left = 16
                Top = 46
                Width = 105
                Height = 25
                BorderStyle = bsSingle
                Caption = 'Body Cmd 1'
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 2
              end
              object edt_ATCmd1: TEdit
                Left = 128
                Top = 46
                Width = 321
                Height = 24
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clRed
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
                ParentFont = False
                TabOrder = 3
                Text = 'AT S07=150 S09=015 S10=023 S30=0'
              end
              object Panel17: TPanel
                Left = 16
                Top = 68
                Width = 105
                Height = 25
                BorderStyle = bsSingle
                Caption = 'Body Cmd 2'
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 4
              end
              object edt_ATCmd2: TEdit
                Left = 128
                Top = 68
                Width = 321
                Height = 24
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clRed
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
                ParentFont = False
                TabOrder = 5
                Text = 'AT S7=40 S30=0'
              end
              object Panel18: TPanel
                Left = 456
                Top = 22
                Width = 201
                Height = 25
                BorderStyle = bsSingle
                Caption = 'Auto Answer Ring Call Num'
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 6
              end
              object edt_RingCallNum: TEdit
                Left = 664
                Top = 22
                Width = 41
                Height = 24
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clRed
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
                ParentFont = False
                TabOrder = 7
                Text = '1'
              end
              object bbtn_ListenDefault: TBitBtn
                Left = 456
                Top = 88
                Width = 73
                Height = 25
                Cursor = crHandPoint
                Caption = 'Default'
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlack
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 8
                OnClick = bbtn_ListenDefaultClick
              end
              object Panel23: TPanel
                Left = 16
                Top = 90
                Width = 105
                Height = 25
                BorderStyle = bsSingle
                Caption = 'End Cmd'
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 9
              end
              object edt_EndATCmd: TEdit
                Left = 128
                Top = 90
                Width = 321
                Height = 24
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clRed
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
                ParentFont = False
                TabOrder = 10
                Text = 'AT %C1 &K3 N1 X4'
              end
            end
            object GroupBox16: TGroupBox
              Left = 16
              Top = 0
              Width = 457
              Height = 105
              Caption = 'Query'
              TabOrder = 1
              object Label10: TLabel
                Left = 280
                Top = 80
                Width = 8
                Height = 16
                Caption = 'L'
              end
              object Label11: TLabel
                Left = 212
                Top = 80
                Width = 11
                Height = 16
                Caption = 'M'
              end
              object Label12: TLabel
                Left = 145
                Top = 80
                Width = 9
                Height = 16
                BiDiMode = bdRightToLeft
                Caption = 'H'
                ParentBiDiMode = False
              end
              object Label13: TLabel
                Left = 312
                Top = 56
                Width = 14
                Height = 16
                Caption = '29'
              end
              object edt_QueryATCmd: TEdit
                Left = 128
                Top = 24
                Width = 321
                Height = 24
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clRed
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
                ParentFont = False
                TabOrder = 0
                Text = 'AT E1 V1 I1 I2 I3 I4 I5 I6 I7'
              end
              object Panel20: TPanel
                Left = 16
                Top = 24
                Width = 105
                Height = 25
                BorderStyle = bsSingle
                Caption = 'AT Cmd'
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 1
              end
              object tkbar_QuerySensitive: TTrackBar
                Left = 144
                Top = 56
                Width = 150
                Height = 25
                Cursor = crHandPoint
                Max = 120
                Orientation = trHorizontal
                Frequency = 1
                Position = 29
                SelEnd = 0
                SelStart = 0
                TabOrder = 2
                TickMarks = tmBottomRight
                TickStyle = tsAuto
              end
              object Panel21: TPanel
                Left = 16
                Top = 64
                Width = 105
                Height = 25
                BorderStyle = bsSingle
                Caption = 'Sensitive'
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 3
              end
              object bbtn_QueryDefault: TBitBtn
                Left = 360
                Top = 64
                Width = 75
                Height = 25
                Cursor = crHandPoint
                Caption = 'Default'
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlack
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 4
                OnClick = bbtn_QueryDefaultClick
              end
            end
            object GroupBox17: TGroupBox
              Left = 16
              Top = 240
              Width = 457
              Height = 113
              Caption = 'DialUp'
              TabOrder = 2
              object Label20: TLabel
                Left = 288
                Top = 88
                Width = 8
                Height = 16
                Caption = 'L'
              end
              object Label21: TLabel
                Left = 212
                Top = 88
                Width = 11
                Height = 16
                Caption = 'M'
              end
              object Label22: TLabel
                Left = 138
                Top = 88
                Width = 9
                Height = 16
                BiDiMode = bdRightToLeft
                Caption = 'H'
                ParentBiDiMode = False
              end
              object Label23: TLabel
                Left = 320
                Top = 64
                Width = 7
                Height = 16
                Caption = '0'
              end
              object Panel24: TPanel
                Left = 16
                Top = 24
                Width = 105
                Height = 25
                BorderStyle = bsSingle
                Caption = 'Initial Cmd'
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 0
              end
              object edt_DialupInitCmd: TEdit
                Left = 128
                Top = 24
                Width = 321
                Height = 24
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clRed
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
                ParentFont = False
                TabOrder = 1
              end
              object bbtn_DialupDefault: TBitBtn
                Left = 360
                Top = 72
                Width = 75
                Height = 25
                Cursor = crHandPoint
                Caption = 'Default'
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlack
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 2
                OnClick = bbtn_DialupDefaultClick
              end
              object tkbar_DialupSpeed: TTrackBar
                Left = 128
                Top = 64
                Width = 177
                Height = 25
                Cursor = crHandPoint
                Max = 255
                Min = 50
                Orientation = trHorizontal
                Frequency = 1
                Position = 95
                SelEnd = 0
                SelStart = 0
                TabOrder = 3
                TickMarks = tmBottomRight
                TickStyle = tsAuto
              end
              object Panel25: TPanel
                Left = 16
                Top = 72
                Width = 105
                Height = 25
                BorderStyle = bsSingle
                Caption = 'Dialup Speed'
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 4
              end
            end
          end
          object TabSheet3: TTabSheet
            Caption = 'Advanced'
            ImageIndex = 2
            object Label16: TLabel
              Left = 280
              Top = 80
              Width = 40
              Height = 16
              Caption = '( min )'
            end
            object Label17: TLabel
              Left = 440
              Top = 109
              Width = 37
              Height = 16
              Caption = '( sec )'
            end
            object chkbox_AutoStop: TCheckBox
              Left = 16
              Top = 16
              Width = 233
              Height = 17
              Caption = 'Auto Stop After Modem OFF Line .'
              Font.Charset = ANSI_CHARSET
              Font.Color = clYellow
              Font.Height = -13
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ParentFont = False
              TabOrder = 0
            end
            object GroupBox13: TGroupBox
              Left = 16
              Top = 152
              Width = 201
              Height = 81
              Caption = 'Speaker Volume'
              TabOrder = 1
              object Label7: TLabel
                Left = 16
                Top = 56
                Width = 8
                Height = 16
                Caption = 'L'
              end
              object Label8: TLabel
                Left = 105
                Top = 56
                Width = 9
                Height = 16
                BiDiMode = bdRightToLeft
                Caption = 'H'
                ParentBiDiMode = False
              end
              object Label9: TLabel
                Left = 60
                Top = 56
                Width = 11
                Height = 16
                Caption = 'M'
              end
              object Label14: TLabel
                Left = 152
                Top = 24
                Width = 7
                Height = 16
                Caption = '3'
              end
              object tkbar_SpeakerVol: TTrackBar
                Left = 8
                Top = 24
                Width = 113
                Height = 25
                Cursor = crHandPoint
                Max = 3
                Orientation = trHorizontal
                Frequency = 1
                Position = 0
                SelEnd = 0
                SelStart = 0
                TabOrder = 0
                TickMarks = tmBottomRight
                TickStyle = tsAuto
              end
              object bbtn_VolDefault: TBitBtn
                Left = 128
                Top = 48
                Width = 57
                Height = 25
                Cursor = crHandPoint
                Caption = 'Default'
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlack
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 1
                OnClick = bbtn_VolDefaultClick
              end
            end
            object GroupBox14: TGroupBox
              Left = 232
              Top = 152
              Width = 337
              Height = 81
              Caption = 'Redial '
              TabOrder = 2
              object Label15: TLabel
                Left = 288
                Top = 53
                Width = 37
                Height = 16
                Caption = '( sec )'
              end
              object chkbox_AlwaysRedial: TCheckBox
                Left = 152
                Top = 24
                Width = 121
                Height = 17
                Caption = 'Always Redial'
                Enabled = False
                TabOrder = 0
                OnClick = chkbox_AlwaysRedialClick
              end
              object edt_RedialTimes: TEdit
                Left = 80
                Top = 48
                Width = 57
                Height = 24
                Color = clBlack
                Enabled = False
                Font.Charset = ANSI_CHARSET
                Font.Color = clAqua
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
                ParentFont = False
                TabOrder = 1
                Text = '5'
                OnChange = edt_RedialTimesChange
              end
              object Panel19: TPanel
                Left = 16
                Top = 48
                Width = 57
                Height = 25
                BorderStyle = bsSingle
                Caption = 'Times'
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 2
              end
              object chkbox_EnableRedial: TCheckBox
                Left = 16
                Top = 24
                Width = 121
                Height = 17
                Caption = 'Enable Redial'
                Checked = True
                State = cbChecked
                TabOrder = 3
                OnClick = chkbox_EnableRedialClick
              end
              object Panel22: TPanel
                Left = 152
                Top = 48
                Width = 57
                Height = 25
                BorderStyle = bsSingle
                Caption = 'Delay'
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clYellow
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ParentFont = False
                TabOrder = 4
              end
              object edt_RedialDelay: TEdit
                Left = 216
                Top = 48
                Width = 65
                Height = 24
                Color = clBlack
                Font.Charset = ANSI_CHARSET
                Font.Color = clAqua
                Font.Height = -13
                Font.Name = 'Arial'
                Font.Style = [fsBold]
                ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
                ParentFont = False
                TabOrder = 5
                Text = '2'
              end
            end
            object chkbox_HangUp: TCheckBox
              Left = 16
              Top = 80
              Width = 201
              Height = 17
              Caption = 'Hang Up If Out Of Idle Time'
              TabOrder = 3
            end
            object edt_OnLineIdleTime: TEdit
              Left = 216
              Top = 72
              Width = 49
              Height = 24
              Color = clBlack
              Font.Charset = ANSI_CHARSET
              Font.Color = clAqua
              Font.Height = -13
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              ParentFont = False
              TabOrder = 4
              Text = '10'
            end
            object chkbox_StopDialup: TCheckBox
              Left = 16
              Top = 112
              Width = 369
              Height = 17
              Caption = 'Stop Dialup If Modem Still Off Line In The Duration Of '
              TabOrder = 5
            end
            object edt_DialupIdleTime: TEdit
              Left = 384
              Top = 104
              Width = 49
              Height = 24
              Color = clBlack
              Font.Charset = ANSI_CHARSET
              Font.Color = clAqua
              Font.Height = -13
              Font.Name = 'Arial'
              Font.Style = [fsBold]
              ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
              ParentFont = False
              TabOrder = 6
              Text = '60'
            end
            object chkbox_AutoErrStop: TCheckBox
              Left = 16
              Top = 48
              Width = 169
              Height = 17
              Caption = 'Auto Modem Error Stop'
              TabOrder = 7
            end
          end
        end
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'Communication'
      ImageIndex = 1
      object Memo1: TMemo
        Left = 8
        Top = 168
        Width = 801
        Height = 377
        Color = clGradientInactiveCaption
        Font.Charset = ANSI_CHARSET
        Font.Color = clNavy
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssVertical
        TabOrder = 0
      end
      object Panel26: TPanel
        Left = 8
        Top = 16
        Width = 801
        Height = 137
        Caption = 'Panel26'
        Color = clSkyBlue
        TabOrder = 1
        object Label24: TLabel
          Left = 192
          Top = 48
          Width = 44
          Height = 13
          Caption = 'DataLen:'
        end
        object Label25: TLabel
          Left = 184
          Top = 80
          Width = 111
          Height = 37
          Caption = 'START'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clLime
          Font.Height = -32
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Button1: TButton
          Left = 328
          Top = 12
          Width = 305
          Height = 117
          Caption = 'AUTO'
          TabOrder = 0
          OnClick = Button1Click
        end
        object LabeledEdit1: TLabeledEdit
          Left = 240
          Top = 12
          Width = 65
          Height = 21
          EditLabel.Width = 65
          EditLabel.Height = 13
          EditLabel.Caption = 'Ethernet Port:'
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 1
          Text = '5000'
        end
        object edtInputLen: TEdit
          Left = 240
          Top = 44
          Width = 65
          Height = 21
          ReadOnly = True
          TabOrder = 2
          Text = '2048'
        end
        object Button4: TButton
          Left = 664
          Top = 12
          Width = 113
          Height = 117
          Caption = 'EXIT'
          TabOrder = 3
          OnClick = Button4Click
        end
        object GroupBox18: TGroupBox
          Left = 8
          Top = 8
          Width = 137
          Height = 57
          Caption = 'RS232 Tx Setting'
          Color = clInactiveBorder
          ParentColor = False
          TabOrder = 4
          object cboxCOMPort: TComboBox
            Left = 16
            Top = 24
            Width = 105
            Height = 21
            ItemHeight = 13
            ItemIndex = 6
            TabOrder = 0
            Text = 'COM7'
            Items.Strings = (
              'COM1'
              'COM2'
              'COM3'
              'COM4'
              'COM5'
              'COM6'
              'COM7'
              'COM8'
              'COM9'
              'COM10')
          end
          object cboxBaud: TComboBox
            Left = 16
            Top = 62
            Width = 105
            Height = 21
            ItemHeight = 13
            ItemIndex = 0
            TabOrder = 1
            Text = '115200'
            Items.Strings = (
              '115200'
              '38400'
              '19200'
              '9600'
              '4800')
          end
          object cboxParity: TComboBox
            Left = 16
            Top = 94
            Width = 105
            Height = 21
            ItemHeight = 13
            TabOrder = 2
            Text = 'N'
            Items.Strings = (
              'N'
              'E'
              'O')
          end
          object cboxDataBit: TComboBox
            Left = 16
            Top = 126
            Width = 105
            Height = 21
            ItemHeight = 13
            ItemIndex = 0
            TabOrder = 3
            Text = '8'
            Items.Strings = (
              '8')
          end
          object cboxStopBit: TComboBox
            Left = 16
            Top = 158
            Width = 105
            Height = 21
            ItemHeight = 13
            ItemIndex = 0
            TabOrder = 4
            Text = '1'
            Items.Strings = (
              '1')
          end
        end
        object GroupBox19: TGroupBox
          Left = 8
          Top = 68
          Width = 137
          Height = 61
          Caption = 'RS232 Rx Setting'
          Color = clInactiveBorder
          ParentColor = False
          TabOrder = 5
          object ComboBox1: TComboBox
            Left = 16
            Top = 24
            Width = 105
            Height = 21
            ItemHeight = 13
            ItemIndex = 4
            TabOrder = 0
            Text = 'COM5'
            Items.Strings = (
              'COM1'
              'COM2'
              'COM3'
              'COM4'
              'COM5'
              'COM6'
              'COM7'
              'COM8'
              'COM9'
              'COM10')
          end
          object ComboBox2: TComboBox
            Left = 16
            Top = 67
            Width = 105
            Height = 21
            ItemHeight = 13
            ItemIndex = 0
            TabOrder = 1
            Text = '115200'
            Items.Strings = (
              '115200'
              '38400'
              '19200'
              '9600'
              '4800')
          end
          object ComboBox3: TComboBox
            Left = 16
            Top = 99
            Width = 105
            Height = 21
            ItemHeight = 13
            TabOrder = 2
            Text = 'N'
            Items.Strings = (
              'N'
              'E'
              'O')
          end
          object ComboBox4: TComboBox
            Left = 16
            Top = 131
            Width = 105
            Height = 21
            ItemHeight = 13
            ItemIndex = 0
            TabOrder = 3
            Text = '8'
            Items.Strings = (
              '8')
          end
          object ComboBox5: TComboBox
            Left = 16
            Top = 163
            Width = 105
            Height = 21
            ItemHeight = 13
            ItemIndex = 0
            TabOrder = 4
            Text = '1'
            Items.Strings = (
              '1')
          end
        end
      end
    end
  end
  object tmrQuery: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tmrQueryTimer
    Left = 288
    Top = 832
  end
  object tmrRx: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tmrRxTimer
    Left = 320
    Top = 832
  end
  object tmrTx: TTimer
    Enabled = False
    OnTimer = tmrTxTimer
    Left = 352
    Top = 832
  end
  object tmrModemStatus: TTimer
    Enabled = False
    Interval = 100
    OnTimer = tmrModemStatusTimer
    Left = 256
    Top = 832
  end
  object ServerSocket1: TServerSocket
    Active = False
    Port = 0
    ServerType = stNonBlocking
    OnClientConnect = ServerSocket1ClientConnect
    OnClientDisconnect = ServerSocket1ClientDisconnect
    OnClientRead = ServerSocket1ClientRead
    OnClientError = ServerSocket1ClientError
    Left = 384
    Top = 832
  end
  object IdIPWatch1: TIdIPWatch
    HistoryFilename = 'iphist.dat'
    Left = 416
    Top = 832
  end
end

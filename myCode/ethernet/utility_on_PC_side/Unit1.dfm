object Form1: TForm1
  Left = 192
  Top = 107
  Width = 870
  Height = 533
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox_Server: TGroupBox
    Left = 8
    Top = 8
    Width = 849
    Height = 321
    Caption = 'Server'
    TabOrder = 0
    object Shape_Server: TShape
      Left = 632
      Top = 288
      Width = 25
      Height = 25
      Brush.Color = clRed
    end
    object Memo_Log: TMemo
      Left = 8
      Top = 24
      Width = 825
      Height = 257
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -16
      Font.Name = 'Courier'
      Font.Style = []
      ParentFont = False
      ScrollBars = ssVertical
      TabOrder = 0
    end
    object LabeledEdit_ServerPort: TLabeledEdit
      Left = 64
      Top = 288
      Width = 89
      Height = 21
      EditLabel.Width = 46
      EditLabel.Height = 22
      EditLabel.Caption = 'Port:'
      EditLabel.Font.Charset = ANSI_CHARSET
      EditLabel.Font.Color = clWindowText
      EditLabel.Font.Height = -19
      EditLabel.Font.Name = 'Arial'
      EditLabel.Font.Style = [fsBold]
      EditLabel.ParentFont = False
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 1
      Text = '4000'
    end
    object Button_Run: TButton
      Left = 672
      Top = 288
      Width = 73
      Height = 25
      Caption = 'Run'
      TabOrder = 2
      OnClick = Button_RunClick
    end
    object Button_Stop: TButton
      Left = 760
      Top = 288
      Width = 73
      Height = 25
      Caption = 'Stop'
      TabOrder = 3
      OnClick = Button_StopClick
    end
  end
  object GroupBox_Client: TGroupBox
    Left = 8
    Top = 368
    Width = 849
    Height = 129
    Caption = 'Client'
    TabOrder = 1
    object Shape_Client: TShape
      Left = 784
      Top = 88
      Width = 25
      Height = 25
      Brush.Color = clRed
    end
    object LabeledEdit_Host: TLabeledEdit
      Left = 64
      Top = 32
      Width = 177
      Height = 21
      EditLabel.Width = 49
      EditLabel.Height = 22
      EditLabel.Caption = 'Host:'
      EditLabel.Font.Charset = ANSI_CHARSET
      EditLabel.Font.Color = clWindowText
      EditLabel.Font.Height = -19
      EditLabel.Font.Name = 'Arial'
      EditLabel.Font.Style = [fsBold]
      EditLabel.ParentFont = False
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 0
      Text = '192.120.100.127'
    end
    object LabeledEdit_Port: TLabeledEdit
      Left = 312
      Top = 32
      Width = 81
      Height = 21
      EditLabel.Width = 46
      EditLabel.Height = 22
      EditLabel.Caption = 'Port:'
      EditLabel.Font.Charset = ANSI_CHARSET
      EditLabel.Font.Color = clWindowText
      EditLabel.Font.Height = -19
      EditLabel.Font.Name = 'Arial'
      EditLabel.Font.Style = [fsBold]
      EditLabel.ParentFont = False
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 1
      Text = '4000'
    end
    object LabeledEdit_Message: TLabeledEdit
      Left = 105
      Top = 72
      Width = 288
      Height = 21
      EditLabel.Width = 91
      EditLabel.Height = 22
      EditLabel.Caption = 'Message:'
      EditLabel.Font.Charset = ANSI_CHARSET
      EditLabel.Font.Color = clWindowText
      EditLabel.Font.Height = -19
      EditLabel.Font.Name = 'Arial'
      EditLabel.Font.Style = [fsBold]
      EditLabel.ParentFont = False
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 2
    end
    object Button_Connect: TButton
      Left = 760
      Top = 16
      Width = 73
      Height = 25
      Caption = 'Connect'
      TabOrder = 3
      OnClick = Button_ConnectClick
    end
    object Button_Disconnect: TButton
      Left = 760
      Top = 48
      Width = 73
      Height = 25
      Caption = 'Disconnect'
      TabOrder = 4
      OnClick = Button_DisconnectClick
    end
    object Button_Send: TButton
      Left = 408
      Top = 64
      Width = 105
      Height = 25
      Caption = 'Send Startup ACK'
      TabOrder = 5
      OnClick = Button_SendClick
    end
    object LabeledEdit_Name: TLabeledEdit
      Left = 464
      Top = 32
      Width = 121
      Height = 21
      EditLabel.Width = 59
      EditLabel.Height = 22
      EditLabel.Caption = 'Name:'
      EditLabel.Font.Charset = ANSI_CHARSET
      EditLabel.Font.Color = clWindowText
      EditLabel.Font.Height = -19
      EditLabel.Font.Name = 'Arial'
      EditLabel.Font.Style = [fsBold]
      EditLabel.ParentFont = False
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 6
      Text = 'Bruce'
    end
    object Button1: TButton
      Left = 409
      Top = 96
      Width = 104
      Height = 25
      Caption = 'Button Dialup ACK'
      TabOrder = 7
      OnClick = Button1Click
    end
  end
  object Button_Clear: TButton
    Left = 8
    Top = 336
    Width = 89
    Height = 25
    Caption = 'ClearLog'
    TabOrder = 2
    OnClick = Button_ClearClick
  end
  object Button2: TButton
    Left = 392
    Top = 336
    Width = 89
    Height = 25
    Caption = 'Button2'
    TabOrder = 3
  end
  object ClientSocket: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 0
    OnConnect = ClientSocketConnect
    OnDisconnect = ClientSocketDisconnect
    OnRead = ClientSocketRead
    OnError = ClientSocketError
    Left = 728
    Top = 384
  end
  object ServerSocket: TServerSocket
    Active = False
    Port = 0
    ServerType = stNonBlocking
    OnClientConnect = ServerSocketClientConnect
    OnClientDisconnect = ServerSocketClientDisconnect
    OnClientRead = ServerSocketClientRead
    OnClientWrite = ServerSocketClientWrite
    OnClientError = ServerSocketClientError
    Left = 600
    Top = 296
  end
end

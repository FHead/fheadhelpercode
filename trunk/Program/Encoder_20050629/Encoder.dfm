object Form1: TForm1
  Left = 530
  Top = 262
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Encoder 2005/06/29'
  ClientHeight = 130
  ClientWidth = 353
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object InputEdit: TEdit
    Left = 16
    Top = 16
    Width = 297
    Height = 21
    TabOrder = 0
  end
  object Button1: TButton
    Left = 320
    Top = 16
    Width = 17
    Height = 17
    Caption = '...'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 320
    Top = 40
    Width = 17
    Height = 17
    Caption = '...'
    TabOrder = 2
    OnClick = Button2Click
  end
  object OutputEdit: TEdit
    Left = 16
    Top = 40
    Width = 297
    Height = 21
    TabOrder = 3
  end
  object Button3: TButton
    Left = 16
    Top = 96
    Width = 75
    Height = 17
    Caption = 'Encode'
    TabOrder = 4
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 104
    Top = 96
    Width = 75
    Height = 17
    Caption = 'Decode'
    TabOrder = 5
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 192
    Top = 96
    Width = 75
    Height = 17
    Caption = 'Exit'
    TabOrder = 6
    OnClick = Button5Click
  end
  object PasswordEdit: TEdit
    Left = 16
    Top = 64
    Width = 297
    Height = 21
    PasswordChar = '#'
    TabOrder = 7
    Text = 'Password'
  end
  object OpenDialog1: TOpenDialog
    Left = 168
    Top = 72
  end
  object SaveDialog1: TSaveDialog
    Left = 200
    Top = 72
  end
end

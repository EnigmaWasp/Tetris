object Form1: TForm1
  Left = 188
  Top = 111
  BorderStyle = bsSingle
  Caption = #1058#1077#1090#1088#1080#1089
  ClientHeight = 540
  ClientWidth = 550
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnKeyUp = FormKeyUp
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 325
    Top = 225
    Width = 86
    Height = 31
    Caption = #1054#1095#1082#1080':0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clPurple
    Font.Height = -27
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object SpeedButton1: TSpeedButton
    Left = 395
    Top = 380
    Width = 136
    Height = 106
    Caption = #1047#1072#1085#1086#1074#1086
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -33
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    OnClick = SpeedButton1Click
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 500
    OnTimer = Timer1Timer
  end
end

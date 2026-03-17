object Form1: TForm1
  Left = 0
  Top = 0
  Caption = #1057#1086#1088#1090#1080#1088#1086#1074#1082#1072' '#1084#1072#1089#1089#1080#1074#1086#1074
  ClientHeight = 844
  ClientWidth = 1470
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object paintBox: TPaintBox
    Left = 560
    Top = 144
    Width = 881
    Height = 569
  end
  object Label1: TLabel
    Left = 24
    Top = 25
    Width = 505
    Height = 391
    Caption = 
      '                        '#1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1084#1072#1089#1089#1080#1074#1072#13#10#13#10#1056#1072#1079#1084#1077#1088' '#1084#1072#1089#1089#1080#1074#1072':'#13#10#13#10 +
      #1052#1080#1085'. '#1079#1085#1072#1095#1077#1085#1080#1077':'#13#10#13#10#1052#1072#1082#1089'. '#1079#1085#1072#1095#1077#1085#1080#1077':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -22
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 560
    Top = 26
    Width = 234
    Height = 40
    Caption = #1057#1082#1086#1088#1086#1089#1090#1100' '#1072#1085#1080#1084#1072#1094#1080#1080':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 24
    Top = 422
    Width = 505
    Height = 31
    Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090#1099':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 560
    Top = 72
    Width = 881
    Height = 49
    Caption = #1042#1080#1079#1091#1072#1083#1080#1079#1072#1094#1080#1103' ( '#1088#1072#1073#1086#1090#1072#1077#1090' '#1090#1086#1083#1100#1082#1086' '#1087#1088#1080' '#1074#1082#1083#1102#1095#1077#1085#1085#1086#1081' '#1075#1072#1083#1086#1095#1082#1077' )'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object btnGenerate: TButton
    Left = 24
    Top = 262
    Width = 497
    Height = 67
    Cursor = crHandPoint
    Caption = #1057#1043#1045#1053#1045#1056#1048#1056#1054#1042#1040#1058#1068
    TabOrder = 0
    OnClick = btnGenerateClick
  end
  object btnSortSelected: TButton
    Left = 560
    Top = 735
    Width = 442
    Height = 74
    Cursor = crHandPoint
    Caption = #1057#1054#1056#1058#1048#1056#1054#1042#1040#1058#1068' '#13#10#1042#1067#1041#1056#1040#1053#1053#1067#1052' '#1056#1045#1046#1048#1052#1054#1052
    TabOrder = 1
    OnClick = btnSortSelectedClick
  end
  object btnSortAll: TButton
    Left = 1008
    Top = 735
    Width = 433
    Height = 74
    Cursor = crHandPoint
    Caption = #1057#1054#1056#1058#1048#1056#1054#1042#1050#1040' '#13#10#1042#1057#1045#1052#1048' '#1056#1045#1046#1048#1052#1040#1052#1048
    TabOrder = 2
    OnClick = btnSortAllClick
  end
  object btnSaveSorted: TButton
    Left = 264
    Top = 735
    Width = 257
    Height = 74
    Cursor = crHandPoint
    Caption = #1057#1054#1061#1056#1040#1053#1048#1058#1068#13#10#1054#1058#1057#1054#1056#1058#1048#1056#1054#1042#1040#1053#1053#1067#1049' '#1052#1040#1057#1057#1048#1042
    TabOrder = 3
    OnClick = btnSaveSortedClick
  end
  object btnSaveResults: TButton
    Left = 24
    Top = 735
    Width = 234
    Height = 74
    Cursor = crHandPoint
    Caption = #1057#1054#1061#1056#1040#1053#1048#1058#1068' '#1056#1045#1047#1059#1051#1068#1058#1040#1058#1067
    TabOrder = 4
    OnClick = btnSaveResultsClick
  end
  object btnLoad: TButton
    Left = 24
    Top = 335
    Width = 497
    Height = 66
    Cursor = crHandPoint
    Caption = #1047#1040#1043#1056#1059#1047#1048#1058#1068' '#1052#1040#1057#1057#1048#1042
    TabOrder = 5
    OnClick = btnLoadClick
  end
  object cbAlgorithms: TComboBox
    Left = 1136
    Top = 72
    Width = 281
    Height = 33
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -18
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
    Text = #1042#1099#1073#1088#1072#1090#1100' '#1089#1086#1088#1090#1080#1088#1086#1074#1082#1091
    Items.Strings = (
      'Bubble Sort'
      'Insertion Sort'
      'Selection Sort'
      'Shell Sort'
      'Quick Sort')
  end
  object editSize: TEdit
    Left = 256
    Top = 89
    Width = 265
    Height = 49
    AutoSize = False
    TabOrder = 7
    TextHint = #1056#1072#1079#1084#1077#1088' '#1084#1072#1089#1089#1080#1074#1072
  end
  object editMin: TEdit
    Left = 256
    Top = 144
    Width = 265
    Height = 49
    Cursor = crArrow
    AutoSize = False
    TabOrder = 8
    TextHint = #1052#1080#1085#1080#1084#1072#1083#1100#1085#1086#1077' '#1079#1085#1072#1095#1077#1085#1080#1077
  end
  object editMax: TEdit
    Left = 256
    Top = 199
    Width = 265
    Height = 49
    AutoSize = False
    TabOrder = 9
    TextHint = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1086#1077' '#1079#1085#1072#1095#1077#1085#1080#1077
  end
  object MemoResults: TMemo
    Left = 24
    Top = 453
    Width = 497
    Height = 268
    Cursor = crNo
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = []
    Lines.Strings = (
      'memoResults')
    ParentFont = False
    ReadOnly = True
    TabOrder = 10
  end
  object trackSpeed: TTrackBar
    Left = 800
    Top = 26
    Width = 465
    Height = 36
    Max = 100
    Min = 1
    Position = 30
    TabOrder = 11
  end
  object cbAnimation: TCheckBox
    Left = 1288
    Top = 16
    Width = 153
    Height = 50
    Caption = ' '#1040#1085#1080#1084#1072#1094#1080#1103
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 12
  end
  object OpenDialog1: TOpenDialog
    Left = 1376
    Top = 640
  end
  object SaveDialog1: TSaveDialog
    Left = 1296
    Top = 648
  end
end

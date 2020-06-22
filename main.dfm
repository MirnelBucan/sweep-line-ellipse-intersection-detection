object Forma: TForma
  Left = 0
  Top = 0
  Caption = 'Aplikacija'
  ClientHeight = 588
  ClientWidth = 1090
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Slika: TImage
    Left = 8
    Top = 8
    Width = 961
    Height = 565
    OnMouseDown = SlikaMouseDown
    OnMouseMove = SlikaMouseMove
  end
  object LabelKoordinate: TLabel
    Left = 975
    Top = 147
    Width = 52
    Height = 13
    Caption = 'Koordinate'
  end
  object labelBrojElipsi: TLabel
    Left = 975
    Top = 8
    Width = 49
    Height = 13
    Caption = 'Broj elipsi:'
  end
  object LabelBrojTestova: TLabel
    Left = 976
    Top = 208
    Width = 63
    Height = 13
    Caption = 'Broj testova:'
  end
  object EditKoordinate: TEdit
    Left = 975
    Top = 166
    Width = 95
    Height = 21
    ReadOnly = True
    TabOrder = 0
    Text = '(0,0)'
  end
  object Clear: TButton
    Left = 975
    Top = 116
    Width = 95
    Height = 25
    Caption = 'Clear'
    TabOrder = 1
    OnClick = ClearClick
  end
  object presjekElipsi: TButton
    Left = 975
    Top = 85
    Width = 95
    Height = 25
    Caption = 'Presjek elipsi'
    TabOrder = 2
    OnClick = presjekElipsiClick
  end
  object EditBrojElipsi: TEdit
    Left = 975
    Top = 27
    Width = 96
    Height = 21
    NumbersOnly = True
    TabOrder = 3
    Text = '1'
  end
  object genElipse: TButton
    Left = 975
    Top = 54
    Width = 95
    Height = 25
    Caption = 'Generisanje elipsi'
    TabOrder = 4
    OnClick = genElipseClick
  end
  object testPresjekElipsi: TButton
    Left = 975
    Top = 256
    Width = 95
    Height = 25
    Caption = 'Test presjek elipsi'
    TabOrder = 5
    OnClick = testPresjekElipsiClick
  end
  object EditBrojTestova: TEdit
    Left = 975
    Top = 229
    Width = 96
    Height = 21
    NumbersOnly = True
    TabOrder = 6
    Text = '1'
  end
end

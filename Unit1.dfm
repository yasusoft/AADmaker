object Form1: TForm1
  Left = 192
  Top = 107
  AutoScroll = False
  Caption = 'AADmaker'
  ClientHeight = 300
  ClientWidth = 450
  Color = clBtnFace
  Font.Charset = SHIFTJIS_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = '�l�r �o�S�V�b�N'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  Position = poScreenCenter
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 12
  object PageControl: TPageControl
    Left = 0
    Top = 0
    Width = 450
    Height = 300
    ActivePage = TabVocabulary
    Align = alClient
    MultiLine = True
    TabOrder = 0
    TabPosition = tpBottom
    OnChange = PageControlChange
    object TabVocabulary: TTabSheet
      Caption = '�P��̈ꗗ'
      object PanelTop: TPanel
        Left = 0
        Top = 0
        Width = 442
        Height = 25
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object LabelYomi: TLabel
          Left = 5
          Top = 5
          Width = 12
          Height = 12
          Caption = '��'
          FocusControl = EditYomi
        end
        object LabelGoku: TLabel
          Left = 130
          Top = 5
          Width = 12
          Height = 12
          Caption = '��'
          FocusControl = EditGoku
        end
        object LabelKind: TLabel
          Left = 270
          Top = 5
          Width = 12
          Height = 12
          Anchors = [akTop, akRight]
          Caption = '��'
          FocusControl = ComboKind
        end
        object EditYomi: TEdit
          Left = 20
          Top = 0
          Width = 105
          Height = 20
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '�l�r �S�V�b�N'
          Font.Style = []
          MaxLength = 20
          ParentFont = False
          TabOrder = 0
        end
        object EditGoku: TEdit
          Left = 145
          Top = 0
          Width = 120
          Height = 20
          Anchors = [akLeft, akTop, akRight]
          Font.Charset = SHIFTJIS_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = '�l�r �S�V�b�N'
          Font.Style = []
          MaxLength = 50
          ParentFont = False
          TabOrder = 1
        end
        object ComboKind: TComboBox
          Left = 285
          Top = 0
          Width = 65
          Height = 20
          Style = csDropDownList
          Anchors = [akTop, akRight]
          ItemHeight = 12
          TabOrder = 2
          Items.Strings = (
            '����'
            '1'
            '�l��'
            '�ŗL����'
            '�Ж�'
            '5'
            '6'
            '7'
            '8'
            '��^��'
            '�當��'
            '11'
            '12'
            '13'
            '14'
            '�ڔ���'
            '����'
            '17'
            '18'
            '19'
            '20'
            '21'
            '22'
            '23'
            '24'
            '25'
            '26'
            '27'
            '28'
            '29'
            '30'
            '31')
        end
        object ButtonAdd: TButton
          Left = 355
          Top = 0
          Width = 40
          Height = 20
          Anchors = [akTop, akRight]
          Caption = '�ǉ�'
          Default = True
          TabOrder = 3
          OnClick = ButtonAddClick
        end
        object ButtonChange: TButton
          Left = 400
          Top = 0
          Width = 40
          Height = 20
          Anchors = [akTop, akRight]
          Caption = '�ύX'
          TabOrder = 4
          OnClick = ButtonChangeClick
        end
      end
      object ListView: TListView
        Left = 0
        Top = 25
        Width = 442
        Height = 248
        Align = alClient
        Columns = <
          item
            Caption = '�ǂ�'
            Width = 105
          end
          item
            Caption = '���'
            Width = 200
          end
          item
            Caption = '���'
            Width = 60
          end>
        ColumnClick = False
        Font.Charset = SHIFTJIS_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '�l�r �S�V�b�N'
        Font.Style = []
        GridLines = True
        HideSelection = False
        MultiSelect = True
        ReadOnly = True
        RowSelect = True
        ParentFont = False
        PopupMenu = PopupMenu
        SortType = stBoth
        TabOrder = 1
        ViewStyle = vsReport
        OnCompare = ListViewCompare
        OnSelectItem = ListViewSelectItem
      end
    end
    object TabInfo: TTabSheet
      Caption = '�����̏��'
      ImageIndex = 1
      object LabelAuthor: TLabel
        Left = 5
        Top = 40
        Width = 65
        Height = 12
        Alignment = taCenter
        AutoSize = False
        Caption = '��Җ�(&A)'
        FocusControl = EditAuthor
      end
      object LabelName: TLabel
        Left = 5
        Top = 10
        Width = 65
        Height = 12
        Alignment = taCenter
        AutoSize = False
        Caption = '������(&N)'
        FocusControl = EditName
      end
      object LabelDate: TLabel
        Left = 5
        Top = 70
        Width = 65
        Height = 12
        Alignment = taCenter
        AutoSize = False
        Caption = '�쐬����(&D)'
        FocusControl = EditDate
      end
      object LabelCount: TLabel
        Left = 5
        Top = 100
        Width = 65
        Height = 12
        Alignment = taCenter
        AutoSize = False
        Caption = '�P�ꐔ(&C)'
        FocusControl = EditCount
      end
      object EditAuthor: TEdit
        Left = 75
        Top = 35
        Width = 350
        Height = 20
        Anchors = [akLeft, akTop, akRight]
        MaxLength = 64
        TabOrder = 1
        Text = 'yasu'
      end
      object EditName: TEdit
        Left = 75
        Top = 5
        Width = 350
        Height = 20
        Anchors = [akLeft, akTop, akRight]
        MaxLength = 64
        TabOrder = 0
        Text = '�T���v������'
      end
      object EditDate: TEdit
        Left = 75
        Top = 65
        Width = 325
        Height = 20
        Anchors = [akLeft, akTop, akRight]
        Font.Charset = SHIFTJIS_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '�l�r �S�V�b�N'
        Font.Style = []
        ImeMode = imDisable
        MaxLength = 28
        ParentFont = False
        TabOrder = 2
        Text = '2005/01/01 00:00:00'
      end
      object ButtonNow: TButton
        Left = 400
        Top = 65
        Width = 25
        Height = 20
        Anchors = [akTop, akRight]
        Caption = '��'
        TabOrder = 3
        OnClick = ButtonNowClick
      end
      object EditCount: TEdit
        Left = 75
        Top = 95
        Width = 310
        Height = 20
        Anchors = [akLeft, akTop, akRight]
        ImeMode = imDisable
        TabOrder = 4
        Text = '0'
      end
      object ButtonSetCount: TButton
        Left = 385
        Top = 95
        Width = 40
        Height = 20
        Anchors = [akTop, akRight]
        Caption = '�؋l'
        TabOrder = 5
        OnClick = ButtonSetCountClick
      end
    end
    object TabError: TTabSheet
      Caption = '�G���['
      ImageIndex = 2
      TabVisible = False
      object MemoError: TMemo
        Left = 0
        Top = 25
        Width = 442
        Height = 248
        Align = alClient
        Font.Charset = SHIFTJIS_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = '�l�r �S�V�b�N'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 1
        WantTabs = True
        WordWrap = False
      end
      object PanelError: TPanel
        Left = 0
        Top = 0
        Width = 442
        Height = 25
        Align = alTop
        BevelOuter = bvNone
        Caption = '�ǉ��ł��Ȃ��������X�g'
        TabOrder = 0
      end
    end
  end
  object StatusBar: TStatusBar
    Left = 300
    Top = 281
    Width = 150
    Height = 19
    Align = alNone
    Anchors = [akLeft, akRight, akBottom]
    Panels = <>
    SimplePanel = True
  end
  object ProgressBar: TProgressBar
    Left = 150
    Top = 283
    Width = 150
    Height = 17
    Anchors = [akLeft, akBottom]
    Min = 0
    Max = 100
    Smooth = True
    Step = 1
    TabOrder = 2
  end
  object MainMenu: TMainMenu
    Left = 10
    Top = 40
    object KeyFile: TMenuItem
      Caption = '�t�@�C��(&F)'
      object KeyNew: TMenuItem
        Caption = '�V�K(&N)'
        ShortCut = 16462
        OnClick = KeyNewClick
      end
      object KeyOpen: TMenuItem
        Caption = '�J��(&O)'
        ShortCut = 16463
        OnClick = KeyOpenClick
      end
      object KeySave: TMenuItem
        Caption = '�ۑ�(&S)'
        ShortCut = 16467
        OnClick = KeySaveClick
      end
      object KeyBar01: TMenuItem
        Caption = '-'
      end
      object KeyImport: TMenuItem
        Caption = '�C���|�[�g(&I)'
        OnClick = KeyImportClick
      end
      object KeyExport: TMenuItem
        Caption = '�G�N�X�|�[�g(&E)'
        OnClick = KeyExportClick
      end
      object KeyBar02: TMenuItem
        Caption = '-'
      end
      object KeyExit: TMenuItem
        Caption = '�I��(&X)'
        ShortCut = 32883
        OnClick = KeyExitClick
      end
    end
    object KeyEdit: TMenuItem
      Caption = '�ҏW(&E)'
      OnClick = KeyEditClick
      object KeyFind: TMenuItem
        Caption = '�ǂ݂Ō���(&F)'
        ShortCut = 16454
        OnClick = KeyFindClick
      end
      object KeyFindNext: TMenuItem
        Caption = '��������(&N)'
        ShortCut = 114
        OnClick = KeyFindNextClick
      end
      object KeyBar: TMenuItem
        Caption = '�L�΂��_(&B)'
        object KeyBarAdd: TMenuItem
          Caption = '�ꉹ�ɂ��Ēǉ�(&A)'
          OnClick = KeyBarAddClick
        end
        object KeyBarChange: TMenuItem
          Caption = '�ꉹ�ɕύX(&C)'
          OnClick = KeyBarChangeClick
        end
      end
      object KeyDelMulti: TMenuItem
        Caption = '�d�����폜(&M)'
        OnClick = KeyDelMultiClick
      end
      object KeyBar11: TMenuItem
        Caption = '-'
      end
      object KeyCut: TMenuItem
        Caption = '�؂���(&T)'
        OnClick = KeyCutClick
      end
      object KeyCopy: TMenuItem
        Caption = '�R�s�[(&C)'
        OnClick = KeyCopyClick
      end
      object KeyPaste: TMenuItem
        Caption = '�\��t��(&P)'
        OnClick = KeyPasteClick
      end
      object KeyDelete: TMenuItem
        Caption = '�폜(&D)'
        OnClick = KeyDeleteClick
      end
      object KeyBar12: TMenuItem
        Caption = '-'
      end
      object KeySelectAll: TMenuItem
        Caption = '���ׂđI��(&A)'
        OnClick = KeySelectAllClick
      end
    end
  end
  object OpenDialog: TOpenDialog
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Left = 10
    Top = 70
  end
  object SaveDialog: TSaveDialog
    Options = [ofHideReadOnly, ofPathMustExist, ofNoReadOnlyReturn, ofEnableSizing]
    Left = 10
    Top = 100
  end
  object PopupMenu: TPopupMenu
    AutoHotkeys = maManual
    OnPopup = KeyEditClick
    Left = 10
    Top = 130
    object KeyCut2: TMenuItem
      Caption = '�؂���(&T)'
      ShortCut = 16472
      OnClick = KeyCutClick
    end
    object KeyCopy2: TMenuItem
      Caption = '�R�s�[(&C)'
      ShortCut = 16451
      OnClick = KeyCopyClick
    end
    object KeyPaste2: TMenuItem
      Caption = '�\��t��(&P)'
      ShortCut = 16470
      OnClick = KeyPasteClick
    end
    object KeyDelete2: TMenuItem
      Caption = '�폜(&D)'
      ShortCut = 46
      OnClick = KeyDeleteClick
    end
    object KeyBar1: TMenuItem
      Caption = '-'
    end
    object KeySelectAll2: TMenuItem
      Caption = '���ׂđI��(&A)'
      ShortCut = 16449
      OnClick = KeySelectAllClick
    end
  end
end

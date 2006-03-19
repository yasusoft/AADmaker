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
  Font.Name = #65325#65331' '#65328#12468#12471#12483#12463
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  Position = poScreenCenter
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  DesignSize = (
    450
    300)
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
    TabIndex = 0
    TabOrder = 0
    TabPosition = tpBottom
    OnChange = PageControlChange
    object TabVocabulary: TTabSheet
      Caption = #21336#35486#12398#19968#35239
      object PanelTop: TPanel
        Left = 0
        Top = 0
        Width = 442
        Height = 25
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        DesignSize = (
          442
          25)
        object LabelYomi: TLabel
          Left = 5
          Top = 5
          Width = 12
          Height = 12
          Caption = #35501
          FocusControl = EditYomi
        end
        object LabelGoku: TLabel
          Left = 130
          Top = 5
          Width = 12
          Height = 12
          Caption = #35486
          FocusControl = EditGoku
        end
        object LabelKind: TLabel
          Left = 270
          Top = 5
          Width = 12
          Height = 12
          Anchors = [akTop, akRight]
          Caption = #31278
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
          Font.Name = #65325#65331' '#12468#12471#12483#12463
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
          Font.Name = #65325#65331' '#12468#12471#12483#12463
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
            #21517#35422
            '1'
            #20154#21517
            #22266#26377#21517#35422
            #31038#21517
            '5'
            '6'
            '7'
            '8'
            #23450#22411#25991
            #38996#25991#23383
            '11'
            '12'
            '13'
            '14'
            #25509#23614#35486
            #25968#23383
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
          Caption = #36861#21152
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
          Caption = #22793#26356
          TabOrder = 4
          OnClick = ButtonChangeClick
        end
      end
      object ListView: TListView
        Left = 0
        Top = 25
        Width = 442
        Height = 250
        Align = alClient
        Columns = <
          item
            Caption = #35501#12415
            Width = 105
          end
          item
            Caption = #35486#21477
            Width = 200
          end
          item
            Caption = #31278#39006
            Width = 60
          end>
        ColumnClick = False
        Font.Charset = SHIFTJIS_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #65325#65331' '#12468#12471#12483#12463
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
      Caption = #36766#26360#12398#24773#22577
      ImageIndex = 1
      DesignSize = (
        442
        275)
      object LabelAuthor: TLabel
        Left = 5
        Top = 40
        Width = 65
        Height = 12
        Alignment = taCenter
        AutoSize = False
        Caption = #20316#32773#21517'(&A)'
        FocusControl = EditAuthor
      end
      object LabelName: TLabel
        Left = 5
        Top = 10
        Width = 65
        Height = 12
        Alignment = taCenter
        AutoSize = False
        Caption = #36766#26360#21517'(&N)'
        FocusControl = EditName
      end
      object LabelDate: TLabel
        Left = 5
        Top = 70
        Width = 65
        Height = 12
        Alignment = taCenter
        AutoSize = False
        Caption = #20316#25104#26085#26178'(&D)'
        FocusControl = EditDate
      end
      object LabelCount: TLabel
        Left = 5
        Top = 100
        Width = 65
        Height = 12
        Alignment = taCenter
        AutoSize = False
        Caption = #21336#35486#25968'(&C)'
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
        Text = #12469#12531#12503#12523#36766#26360
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
        Font.Name = #65325#65331' '#12468#12471#12483#12463
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
        Caption = #20170
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
        Caption = #20999#35440
        TabOrder = 5
        OnClick = ButtonSetCountClick
      end
    end
    object TabError: TTabSheet
      Caption = #12456#12521#12540
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
        Font.Name = #65325#65331' '#12468#12471#12483#12463
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
        Caption = #36861#21152#12391#12365#12394#12363#12387#12383#12522#12473#12488
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
      Caption = #12501#12449#12452#12523'(&F)'
      object KeyNew: TMenuItem
        Caption = #26032#35215'(&N)'
        ShortCut = 16462
        OnClick = KeyNewClick
      end
      object KeyOpen: TMenuItem
        Caption = #38283#12367'(&O)'
        ShortCut = 16463
        OnClick = KeyOpenClick
      end
      object KeySave: TMenuItem
        Caption = #20445#23384'(&S)'
        ShortCut = 16467
        OnClick = KeySaveClick
      end
      object KeyBar01: TMenuItem
        Caption = '-'
      end
      object KeyImport: TMenuItem
        Caption = #12452#12531#12509#12540#12488'(&I)'
        object KeyImportCSV: TMenuItem
          Caption = 'CSV'#24418#24335'(&C)'
          OnClick = KeyImportCSVClick
        end
        object KeyImportPBX: TMenuItem
          Caption = 'PBX'#24418#24335'(&P)'
          OnClick = KeyImportPBXClick
        end
      end
      object KeyExport: TMenuItem
        Caption = #12456#12463#12473#12509#12540#12488'(&E)'
        object KeyExportCSV: TMenuItem
          Caption = 'CSV'#24418#24335'(&C)'
          OnClick = KeyExportCSVClick
        end
        object KeyExportPBX: TMenuItem
          Caption = 'PBX'#24418#24335'(&P)'
          OnClick = KeyExportPBXClick
        end
      end
      object KeyBar02: TMenuItem
        Caption = '-'
      end
      object KeyExit: TMenuItem
        Caption = #32066#20102'(&X)'
        ShortCut = 32883
        OnClick = KeyExitClick
      end
    end
    object KeyEdit: TMenuItem
      Caption = #32232#38598'(&E)'
      OnClick = KeyEditClick
      object KeyFind: TMenuItem
        Caption = #35501#12415#12391#26908#32034'(&F)'
        ShortCut = 16454
        OnClick = KeyFindClick
      end
      object KeyFindNext: TMenuItem
        Caption = #27425#12434#26908#32034'(&N)'
        ShortCut = 114
        OnClick = KeyFindNextClick
      end
      object KeyBar: TMenuItem
        Caption = #20280#12400#12375#26834'(&B)'
        object KeyBarAdd: TMenuItem
          Caption = #27597#38899#12395#12375#12390#36861#21152'(&A)'
          OnClick = KeyBarAddClick
        end
        object KeyBarChange: TMenuItem
          Caption = #27597#38899#12395#22793#26356'(&C)'
          OnClick = KeyBarChangeClick
        end
      end
      object KeyDelMulti: TMenuItem
        Caption = #37325#35079#12434#21066#38500'(&M)'
        OnClick = KeyDelMultiClick
      end
      object KeyBar11: TMenuItem
        Caption = '-'
      end
      object KeyCut: TMenuItem
        Caption = #20999#12426#21462#12426'(&T)'
        OnClick = KeyCutClick
      end
      object KeyCopy: TMenuItem
        Caption = #12467#12500#12540'(&C)'
        OnClick = KeyCopyClick
      end
      object KeyPaste: TMenuItem
        Caption = #36028#12426#20184#12369'(&P)'
        OnClick = KeyPasteClick
      end
      object KeyDelete: TMenuItem
        Caption = #21066#38500'(&D)'
        OnClick = KeyDeleteClick
      end
      object KeyBar12: TMenuItem
        Caption = '-'
      end
      object KeySelectAll: TMenuItem
        Caption = #12377#12409#12390#36984#25246'(&A)'
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
      Caption = #20999#12426#21462#12426'(&T)'
      ShortCut = 16472
      OnClick = KeyCutClick
    end
    object KeyCopy2: TMenuItem
      Caption = #12467#12500#12540'(&C)'
      ShortCut = 16451
      OnClick = KeyCopyClick
    end
    object KeyPaste2: TMenuItem
      Caption = #36028#12426#20184#12369'(&P)'
      ShortCut = 16470
      OnClick = KeyPasteClick
    end
    object KeyDelete2: TMenuItem
      Caption = #21066#38500'(&D)'
      ShortCut = 46
      OnClick = KeyDeleteClick
    end
    object KeyBar1: TMenuItem
      Caption = '-'
    end
    object KeySelectAll2: TMenuItem
      Caption = #12377#12409#12390#36984#25246'(&A)'
      ShortCut = 16449
      OnClick = KeySelectAllClick
    end
  end
end

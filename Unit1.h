//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
        TMainMenu *MainMenu;
        TMenuItem *KeyFile;
        TMenuItem *KeyOpen;
        TMenuItem *KeySave;
        TMenuItem *KeyNew;
        TMenuItem *KeyBar01;
        TMenuItem *KeyExit;
        TMenuItem *KeyBar02;
        TMenuItem *KeyImport;
        TMenuItem *KeyExport;
        TPageControl *PageControl;
        TTabSheet *TabVocabulary;
        TTabSheet *TabInfo;
        TLabel *LabelAuthor;
        TEdit *EditAuthor;
        TEdit *EditName;
        TLabel *LabelName;
        TLabel *LabelDate;
        TEdit *EditDate;
        TButton *ButtonNow;
        TOpenDialog *OpenDialog;
        TSaveDialog *SaveDialog;
        TMenuItem *KeyEdit;
        TPanel *PanelTop;
        TLabel *LabelYomi;
        TEdit *EditYomi;
        TLabel *LabelGoku;
        TEdit *EditGoku;
        TLabel *LabelKind;
        TComboBox *ComboKind;
        TListView *ListView;
        TButton *ButtonAdd;
        TButton *ButtonChange;
        TMenuItem *KeyDelete;
        TMenuItem *KeySelectAll;
        TLabel *LabelCount;
        TEdit *EditCount;
        TPopupMenu *PopupMenu;
        TMenuItem *KeyDelete2;
        TMenuItem *KeySelectAll2;
        TMenuItem *KeyCut;
        TMenuItem *KeyCopy;
        TMenuItem *KeyPaste;
        TMenuItem *KeyCut2;
        TMenuItem *KeyCopy2;
        TMenuItem *KeyPaste2;
        TMenuItem *KeyBar1;
        TMenuItem *KeyBar11;
        TStatusBar *StatusBar;
        TButton *ButtonSetCount;
        TProgressBar *ProgressBar;
        TMenuItem *KeyFind;
        TMenuItem *KeyBar12;
        TMenuItem *KeyFindNext;
        TMenuItem *KeyDelMulti;
        TMenuItem *KeyBarAdd;
        TMenuItem *KeyBar;
        TMenuItem *KeyBarChange;
        TTabSheet *TabError;
        TMemo *MemoError;
        TPanel *PanelError;
        void __fastcall KeyExitClick(TObject *Sender);
        void __fastcall KeyNewClick(TObject *Sender);
        void __fastcall KeyOpenClick(TObject *Sender);
        void __fastcall KeySaveClick(TObject *Sender);
        void __fastcall KeyImportClick(TObject *Sender);
        void __fastcall KeyExportClick(TObject *Sender);
        void __fastcall ButtonNowClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall ButtonChangeClick(TObject *Sender);
        void __fastcall ButtonAddClick(TObject *Sender);
        void __fastcall KeyDeleteClick(TObject *Sender);
        void __fastcall KeySelectAllClick(TObject *Sender);
        void __fastcall ListViewSelectItem(TObject *Sender,
          TListItem *Item, bool Selected);
        void __fastcall PageControlChange(TObject *Sender);
        void __fastcall KeyEditClick(TObject *Sender);
        void __fastcall KeyCopyClick(TObject *Sender);
        void __fastcall KeyCutClick(TObject *Sender);
        void __fastcall KeyPasteClick(TObject *Sender);
        void __fastcall ListViewCompare(TObject *Sender, TListItem *Item1,
          TListItem *Item2, int Data, int &Compare);
        void __fastcall ButtonSetCountClick(TObject *Sender);
        void __fastcall KeyFindClick(TObject *Sender);
        void __fastcall KeyFindNextClick(TObject *Sender);
        void __fastcall KeyDelMultiClick(TObject *Sender);
        void __fastcall KeyBarAddClick(TObject *Sender);
        void __fastcall KeyBarChangeClick(TObject *Sender);
private:	// ユーザー宣言
        bool modify;
        AnsiString findkey;
        int findpos;
        AnsiString __fastcall ConvertString(AnsiString str, DWORD flag);
        unsigned char GetVowel(unsigned char *s, int p);
        void __fastcall LoadFromFile(AnsiString filename);
        void __fastcall LoadFromStringList(TStringList *lines);
        void __fastcall SaveToStringList(TStringList *lines, bool only = false);
        bool __fastcall CheckInput();
protected:
	void __fastcall WMDropFiles(TWMDropFiles &Msg);

#pragma warn -8027
        BEGIN_MESSAGE_MAP
        VCL_MESSAGE_HANDLER(WM_DROPFILES, TWMDropFiles, WMDropFiles)
        END_MESSAGE_MAP(TForm)
#pragma warn .8027
public:		// ユーザー宣言
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

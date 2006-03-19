//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "crc.h"
#include <Clipbrd.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::ConvertString(AnsiString str, DWORD flag)
{
  char *buf;
  int len = str.Length();
  buf = (char*)GlobalAlloc(GPTR, len*2+1);
  LCMapString(GetUserDefaultLCID(), flag,
        str.c_str(), len, buf, len*2+1);
  str = buf;
  GlobalFree(buf);
  return str;
}
//---------------------------------------------------------------------------
unsigned char TForm1::GetVowel(unsigned char *s, int p)
{
  unsigned char c = s[p];
  switch (c)
  {
    case 0xA6: // ヲ
      return 0xB5; // オ
    case 0xAC: // ャ
      return 0xB1; // ア
    case 0xAD: // ュ
      return 0xB3; // ウ
    case 0xAE: // ョ
      return 0xB5; // オ
    case 0xAF: // ッ
      return 0xB3; // ウ
    case 0xD5: // ユ
      return 0xB3; // ウ
    case 0xD6: // ヨ
      return 0xB5; // オ
    case 0xB0: // ー
    case 0xDE: // ゛
    case 0xDF: // ゜
      if (p > 0)
        return GetVowel(s, p-1);
      else
        return 0;
  }
  if (c <= 0xA6)
    return 0;
  if (c <= 0xAB) // 小文字
    return c + 0x0A;
  if (c <= 0xD4)
    return 0xB1 + ((c - 0xB1) % 5);
  if (c <= 0xDC)
    return 0xB1 + ((c - 0xD7) % 5);
  return 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::WMDropFiles(TWMDropFiles &Msg)
{
  HDROP hDrop = (HDROP)Msg.Drop;
  //int n = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
  char buf[MAX_PATH];
  DragQueryFile(hDrop, 0, buf, MAX_PATH);

  AnsiString filename = buf;
  if (ExtractFileExt(filename).LowerCase() == ".aad")
  {
    if (modify)
      switch (Application->MessageBox("辞書データは変更されています。\n保存しますか？", "終了", MB_YESNOCANCEL | MB_ICONQUESTION))
      {
        case IDYES:
          KeySaveClick(NULL);
          break;
        case IDNO:
          modify = false;
          break;
      }
    if (!modify)
      LoadFromFile(filename);
  }
  else
  {
    TStringList *lines = new TStringList();
    try
    {
      lines->LoadFromFile(filename);
      if (ExtractFileExt(filename).LowerCase() == ".pbx")
      {
        while (lines->Count > 0 && lines->Strings[0] != "DicBegin:")
          lines->Delete(0);
        if (lines->Count > 0)
          lines->Delete(0);
      }
      LoadFromStringList(lines);
    }
    __finally
    {
      delete lines;
    }
  }

  DragFinish(hDrop);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
  DragAcceptFiles(Handle, true);
  modify = false;
  KeyNewClick(Sender);

  if (ParamCount() >= 1 && FileExists(ParamStr(1)))
  {
    if (ExtractFileExt(ParamStr(1)).LowerCase() == ".aad")
      LoadFromFile(ParamStr(1));
    else
    {
      TStringList *lines = new TStringList();
      try
      {
        lines->LoadFromFile(ParamStr(1));
        if (ExtractFileExt(ParamStr(1)).LowerCase() == ".pbx")
        {
          while (lines->Count > 0 && lines->Strings[0] != "DicBegin:")
            lines->Delete(0);
          if (lines->Count > 0)
            lines->Delete(0);
        }
        LoadFromStringList(lines);
      }
      __finally
      {
        delete lines;
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  KeyNewClick(Sender);
  CanClose = !modify;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
  //
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyNewClick(TObject *Sender)
{
  if (modify)
    switch (Application->MessageBox("辞書データは変更されています。\n保存しますか？", "終了", MB_YESNOCANCEL | MB_ICONQUESTION))
    {
      case IDYES:
        KeySaveClick(Sender);
        if (modify)
          return;
        break;
      case IDCANCEL:
        return;
    }
  ListView->Items->BeginUpdate();
  ListView->Items->Clear();
  ListView->Items->EndUpdate();
  EditYomi->Text = "";
  EditGoku->Text = "";
  EditName->Text = "辞書";
  EditAuthor->Text = "名無しさん";
  ButtonNowClick(Sender);
  EditCount->Text = "0";
  modify = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LoadFromFile(AnsiString filename)
{
  TMemoryStream *mem = new TMemoryStream();
  try
  {
    unsigned int tempi;
    unsigned char buf[256];
    int num;

    mem->LoadFromFile(filename);

    // シグネチャ
    mem->Read(buf, 4);
    if (buf[0] != 'D' || buf[1] != 'A' || buf[2] != 'T' || buf[3] != 'A')
    {
      Application->MessageBox((filename + " ファイルは辞書ファイルではありません").c_str(), "エラー", MB_OK | MB_ICONERROR);
      return;
    }

    modify = false;
    KeyNewClick(NULL);

    // ファイルサイズ
    mem->Seek(4, soFromCurrent);
    // ？
    mem->Seek(4, soFromCurrent);
    // 辞書名
    mem->Read(buf, 0x40);
    buf[0x40] = 0;
    EditName->Text = (char*)buf;
    // ？
    mem->Seek(4, soFromCurrent);
    // 単語数
    mem->Read(&num, 4);
    // 作者名
    mem->Read(buf, 0x40);
    buf[0x40] = 0;
    EditAuthor->Text = (char*)buf;
    if (EditAuthor->Text.SubString(1, 5) == "yasu/")
      EditAuthor->Text = EditAuthor->Text.SubString(6, EditAuthor->Text.Length() - 5);
    // 作成日時
    mem->Read(buf, 0x1C);
    buf[0x1C] = 0;
    EditDate->Text = (char*)buf;
    // ？？の番地
    mem->Seek(4, soFromCurrent);
    // ？？のサイズ
    mem->Seek(4, soFromCurrent);
    // インデックスの番地
    mem->Seek(4, soFromCurrent);
    // インデックスのサイズ
    mem->Seek(4, soFromCurrent);
    // 辞書の番地
    mem->Read(&tempi, 4);
    // 辞書のサイズ
    //mem->Seek(4, soFromCurrent);

    mem->Seek(tempi, soFromBeginning);
    // 辞書
    ListView->Items->BeginUpdate();
    ListView->SortType = Comctrls::stNone;
    ProgressBar->Max = num;
    AnsiString yomi = "\xFF";
    unsigned char bufy[0x20], leny;
    for (int i = 0; i < num; i ++)
    {
      unsigned char len1, opt;
      AnsiString goku;
      int kind = -1;

      // 全体の長さ
      mem->Read(&len1, 1);
      if (len1 & 0x80) kind = 0; // 種類はなし
      len1 &= 0x7F;

      // 読みの長さ
      mem->Read(buf, 1);
      opt = (buf[0] & 0xE0) >> 4;
      // 読み
      mem->Read(buf+1, buf[0] & 0x1F);
      if ((buf[0]&0x1F) != 1 || buf[1] != 0xFF)
      { // 読みを読み込む
        leny = buf[0] & 0x1F;
        CopyMemory(bufy, buf+1, leny);
        bufy[leny] = 0;
        yomi = (char*)bufy;
        len1 = len1 - 1 - leny;
      }
      else // 読みは前と同じ
        len1 = len1 - 1 - 1;

      mem->Read(buf, len1);
      // 種類
      if (kind != 0)
      {
        len1 --;
        kind = buf[len1];
      }
      // 語句
      buf[len1] = 0;
      goku = (char*)buf;
      if (0x10 <= buf[len1-1] && buf[len1-1] <= 0x1F)
      { // 最後は読みと同じ
        if (buf[len1-1] & 0x08)
          goku = goku.SubString(1, goku.Length() - 1) + ConvertString((char*)(bufy + leny - (buf[len1-1]&0x07) - 1), LCMAP_FULLWIDTH | LCMAP_KATAKANA);
        else
          goku = goku.SubString(1, goku.Length() - 1) + ConvertString((char*)(bufy + leny - (buf[len1-1]&0x07) - 1), LCMAP_FULLWIDTH | LCMAP_HIRAGANA);
      }
      if (0x10 <= buf[0] && buf[0] <= 0x1F)
      { // 先頭は読みと同じ
        bufy[(buf[0]&0x07)+1] = 0;
        if (buf[0] & 0x08)
          goku = ConvertString((char*)bufy, LCMAP_FULLWIDTH | LCMAP_KATAKANA) + goku.SubString(2, goku.Length() - 1);
        else
          goku = ConvertString((char*)bufy, LCMAP_FULLWIDTH | LCMAP_HIRAGANA) + goku.SubString(2, goku.Length() - 1);
      }

      // 追加
      TListItem *item = ListView->Items->Add();
      item->Caption = yomi;
      if (opt == 0x0A) // 読みをカタカナに
      {
        // 半角→全角
        goku = ConvertString(yomi, LCMAP_FULLWIDTH);
        item->SubItems->Add(goku);
      }
      else if (opt == 0x0E) // 読みをひらがなに
      {
        // 半角→全角
        goku = ConvertString(yomi, LCMAP_FULLWIDTH | LCMAP_HIRAGANA);
        item->SubItems->Add(goku);
      }
      else if (opt == 0x08) // 語句をカタカナに
      {
        // 半角カナ→全角カナ
        goku = ConvertString(goku, LCMAP_FULLWIDTH | LCMAP_KATAKANA);
        item->SubItems->Add(goku);
      }
      else if (opt == 0x0C) // 語句をひらがなに
      {
        // 半角カナ→全角かな
        goku = ConvertString(goku, LCMAP_FULLWIDTH | LCMAP_HIRAGANA);
        item->SubItems->Add(goku);
      }
      else
        item->SubItems->Add(goku);
      if (kind < ComboKind->Items->Count)
        item->SubItems->Add(ComboKind->Items->Strings[kind]);
      else
        item->SubItems->Add(IntToStr(kind));
       item->ImageIndex = kind;

      //StatusBar->SimpleText = "処理中... " + IntToStr(100 * i / num) + "%";
      //StatusBar->Update();
      ProgressBar->Position = i;
      ProgressBar->Update();
    }
    ListView->SortType = Comctrls::stData;
    //StatusBar->SimpleText = "";
    ProgressBar->Position = 0;
    ListView->Items->EndUpdate();
    PageControlChange(NULL);
    modify = false;
  }
  __finally
  {
    delete mem;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyOpenClick(TObject *Sender)
{
  if (modify)
    switch (Application->MessageBox("辞書データは変更されています。\n保存しますか？", "終了", MB_YESNOCANCEL | MB_ICONQUESTION))
    {
      case IDYES:
        KeySaveClick(Sender);
        if (modify)
          return;
        break;
      case IDCANCEL:
        return;
    }
  OpenDialog->FileName = "*.aad";
  OpenDialog->Filter = "辞書ファイル(*.aad)|*.aad|すべてのファイル(*.*)|*.*";
  OpenDialog->Title = "開く";
  if (OpenDialog->Execute())
    LoadFromFile(OpenDialog->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeySaveClick(TObject *Sender)
{
  SaveDialog->FileName = "*.aad";
  SaveDialog->Filter = "辞書ファイル(*.aad)|*.aad|すべてのファイル(*.*)|*.*";
  SaveDialog->Title = "名前を付けて保存";
  if (SaveDialog->Execute())
  {
    if (ExtractFileExt(SaveDialog->FileName) == "")
      SaveDialog->FileName = ChangeFileExt(SaveDialog->FileName, ".aad");
    if (FileExists(SaveDialog->FileName))
      if (Application->MessageBox((SaveDialog->FileName + " ファイルは既に存在します。\n上書きしますか？").c_str(), "名前を付けて保存", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
        return;

    TMemoryStream *mem = new TMemoryStream();
    try
    {
      unsigned int tempi;
      unsigned short tempsi;
      unsigned char buf[256];

      // シグネチャ
      mem->Write("DATA", 4);
      // ファイルサイズ(保留 0x0004)
      ZeroMemory(buf, 4);
      mem->Write(buf, 4);
      // 0x00000000 or 0x00000001？
      mem->Write("\x01\x00\x00\x00", 4);
      // 辞書名
      if (EditName->Text.Length() > 0x40)
        mem->Write(EditName->Text.c_str(), 0x40);
      else
      {
        mem->Write(EditName->Text.c_str(), EditName->Text.Length());
        ZeroMemory(buf, 0x40 - EditName->Text.Length());
        mem->Write(buf, 0x40 - EditName->Text.Length());
      }
      // 内容のばーじょん？0x00000001～5
      mem->Write("\x01\x00\x00\x00", 4);
      // 単語数
      tempi = ListView->Items->Count;
      mem->Write(&tempi, 4);
      // 作者名
      AnsiString author = EditAuthor->Text;
      if (author == "")
        author = "yasu";
      else if (author != "yasu" && author.SubString(1, 5) != "yasu/")
        author = "yasu/" + author;
      if (author.Length() > 0x40)
        mem->Write(author.c_str(), 0x40);
      else
      {
        mem->Write(author.c_str(), author.Length());
        ZeroMemory(buf, 0x40 - author.Length());
        mem->Write(buf, 0x40 - author.Length());
      }
      // 作成日時
      if (EditDate->Text.Length() > 0x1C)
        mem->Write(EditDate->Text.c_str(), 0x1C);
      else
      {
        mem->Write(EditDate->Text.c_str(), EditDate->Text.Length());
        ZeroMemory(buf, 0x1C - EditDate->Text.Length());
        mem->Write(buf, 0x1C - EditDate->Text.Length());
      }

      TStringList *index = new TStringList();
      TMemoryStream *dic = new TMemoryStream();
      try
      {
        // インデックスと辞書の作成
        char c = 0;
        for (int i = 0; i < ListView->Items->Count; i ++)
        {
          AnsiString yomi = ListView->Items->Item[i]->Caption;
          AnsiString goku = ListView->Items->Item[i]->SubItems->Strings[0];
          unsigned char kind = ListView->Items->Item[i]->ImageIndex;
          unsigned char opt = 0x00;
          int j;

          // 全角かなor全角カナのみかチェック
          AnsiString tgoku = goku;
          // 全角かな,全角カナを半角カナに変換
          tgoku = ConvertString(tgoku, LCMAP_HALFWIDTH | LCMAP_KATAKANA);
          // 半角カナのみになったかチェック
          for (j = tgoku.Length(); j > 0; j --)
          {
            unsigned char c = tgoku[j];
            if (c < 0xA5 || 0xDF < c)
              break;
          }
          if (j == 0)
          { // 全角かな,全角カナのみ
            if (ConvertString(tgoku, LCMAP_FULLWIDTH | LCMAP_HIRAGANA) == goku)
            { // 全角かなに戻して元通りなら全角かなのみ
              if (tgoku == yomi)
              { // 読みを全角かなにするだけ
                opt = 0xE0;
                goku = "";
              }
              else
              { // 語句は全角かな
                opt = 0xC0;
                goku = tgoku;
              }
            }
            else if (ConvertString(tgoku, LCMAP_FULLWIDTH | LCMAP_KATAKANA) == goku)
            { // 全角カナに戻して元通りなら全角カナのみ
              if (tgoku == yomi)
              { // 読みを全角カナにするだけ
                opt = 0xA0;
                goku = "";
              }
              else
              { // 語句は全角カナ
                opt = 0x80;
                goku = tgoku;
              }
            }
            // else かなカナ混じり
          }

          AnsiString yomik = ConvertString(yomi, LCMAP_FULLWIDTH | LCMAP_KATAKANA);
          AnsiString yomih = ConvertString(yomi, LCMAP_FULLWIDTH | LCMAP_HIRAGANA);
          int yomilen = yomik.Length(), gokulen = goku.Length();
          // 最後がカタカナ読みと同じかチェック
          for (j = 1; j < yomilen && j < gokulen; j += 2)
            if (yomik[yomilen-j] != goku[gokulen-j] || yomik[yomilen-j+1] != goku[gokulen-j+1])
              break;
          j = (j - 1) / 2;
          //if (j > 0 && yomik.SubString(yomilen - j*2 + 1, 2) == "ー")
          //  j --;
          if (j > 0)
          {
            int k;
            do
              k = ConvertString(yomik.SubString(yomilen - j*2 + 1, yomilen), LCMAP_HALFWIDTH).Length() - 1;
            while (k > 7 && --j > 0);
            if (j > 0) goku = goku.SubString(1, gokulen - j*2) + AnsiString((char)(0x18 | k));
          }
          else
          {
            // 最後がひらがな読みと同じかチェック
            for (j = 1; j < yomilen && j < gokulen; j += 2)
              if (yomih[yomilen-j] != goku[gokulen-j] || yomih[yomilen-j+1] != goku[gokulen-j+1])
                break;
            j = (j - 1) / 2;
            if (j > 0 && yomik.SubString(yomilen - j*2 + 1, 2) == "ー")
              j --;
            if (j > 0)
            {
              int k;
              do
                k = ConvertString(yomik.SubString(yomilen - j*2 + 1, yomilen), LCMAP_HALFWIDTH).Length() - 1;
              while (k > 7 && --j > 0);
              if (j > 0) goku = goku.SubString(1, gokulen - j*2) + AnsiString((char)(0x10 | k));
            }
          }
          // 先頭がカタカナ読みと同じかチェック
          for (j = 1; j < yomilen && j < goku.Length(); j += 2)
            if (yomik[j] != goku[j] || yomik[j+1] != goku[j+1])
              break;
          j = (j - 1) / 2;
          if (j)
          {
            int k;
            do
              k = ConvertString(yomik.SubString(1, j * 2), LCMAP_HALFWIDTH).Length() - 1;
            while (k > 7 && --j > 0);
            if (j > 0) goku = AnsiString((char)(0x18 | k)) + goku.SubString(j * 2 + 1, goku.Length());
          }
          else
          {
            // 先頭がひらがな読みと同じかチェック
            for (j = 1; j < yomilen && j < goku.Length(); j += 2)
              if (yomih[j] != goku[j] || yomih[j+1] != goku[j+1])
                break;
            j = (j - 1) / 2;
            if (j)
            {
              int k;
              do
                k = ConvertString(yomik.SubString(1, j * 2), LCMAP_HALFWIDTH).Length() - 1;
              while (k > 7 && --j > 0);
              if (j > 0) goku = AnsiString((char)(0x10 | k)) + goku.SubString(j * 2 + 1, goku.Length());
            }
          }
          
          if (yomi[1] != c)
          { // 読みの１文字目が変わった
            c = yomi[1];
            index->AddObject(yomi, (TObject*)dic->Position);
          }
          if (i > 0 && yomi.Length() > 1 && yomi == ListView->Items->Item[i-1]->Caption)
          { // 読みが前と一緒なら省略(但し1バイトより長い時)
            if (kind != 0)
              buf[0] = 1 + 1 + goku.Length() + 1;
            else
              buf[0] = 0x80 | (1 + 1 + goku.Length());
            buf[1] = opt | 0x01;
            buf[2] = 0xFF;
            dic->Write(buf, 3);
            dic->Write(goku.c_str(), goku.Length());
            if (kind != 0)
              dic->Write(&kind, 1);
          }
          else
          {
            if (kind != 0)
              buf[0] = 1 + yomi.Length() + goku.Length() + 1;
            else
              buf[0] = 0x80 | (1 + yomi.Length() + goku.Length());
            buf[1] = opt | yomi.Length();
            dic->Write(buf, 2);
            dic->Write(yomi.c_str(), yomi.Length());
            dic->Write(goku.c_str(), goku.Length());
            if (kind != 0)
              dic->Write(&kind, 1);
          }
        }

        // ？？の番地
        mem->Write("\xD8\x00\x00\x00", 4);
        // ？？のサイズ
        mem->Write("\xB0\x00\x00\x00", 4);
        // インデックスの番地
        mem->Write("\x88\x01\x00\x00", 4);
        // インデックスのサイズ
        tempi = 256 + 2 + index->Count * 2;
        mem->Write(&tempi, 4);
        // 辞書の番地
        tempi = 0x00000188 + tempi;
        mem->Write(&tempi, 4);
        // 辞書のサイズ
        tempi = dic->Size;
        mem->Write(&tempi, 4);
        // ？
        ZeroMemory(buf, 0x10);
        mem->Write(buf, 0x10);
        // ？？
        ZeroMemory(buf, 0x000000B0);
        mem->Write(buf, 0x000000B0);

        // インデックス
        ZeroMemory(buf, 256);
        for (int i = 0; i < index->Count; i ++)
          buf[(unsigned char)index->Strings[i][1]] = i+1;
        mem->Write(buf, 256);
        mem->Write("\xFF\xFF", 2);
        for (int i = 0; i < index->Count; i ++)
        {
          tempsi = (unsigned int)index->Objects[i];
          mem->Write(&tempsi, 2);
        }

        // 辞書
        mem->Write(dic->Memory, dic->Size);
      }
      __finally
      {
        delete index;
        delete dic;
      }

      // ファイルサイズ
      mem->Seek(0x00000004, soFromBeginning);
      tempi = mem->Size + 4;
      mem->Write(&tempi, 4);

      // CRC
      mem->Seek(0, soFromEnd);
      tempi = crc((unsigned char *)mem->Memory, mem->Size);
      buf[0] = tempi >> 24;
      buf[1] = tempi >> 16;
      buf[2] = tempi >> 8;
      buf[3] = tempi & 0xFF;
      mem->Write(buf, 4);

      mem->SaveToFile(SaveDialog->FileName);
      modify = false;
    }
    __finally
    {
      delete mem;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LoadFromStringList(TStringList *lines)
{
  TStringList *line = new TStringList();
  try
  {
    int err = 0;
    MemoError->Clear();

    ListView->Items->BeginUpdate();
    ListView->SortType = Comctrls::stNone;
    ProgressBar->Max = lines->Count;
    for (int i = 0; i < lines->Count; i ++)
    {
      if (lines->Strings[i].SubString(1, 2) == "//")
        continue;
      line->CommaText = lines->Strings[i];

      // チェック
      if (line->Count < 2)
      {
        err ++;
        MemoError->Lines->Add(lines->Strings[i]);
        continue;
      }
      // まな→カナ＆全角→半角
      line->Strings[0] = ConvertString(line->Strings[0], LCMAP_KATAKANA | LCMAP_HALFWIDTH);
      // 半角カナのみかチェック
      int j;
      for (j = line->Strings[0].Length(); j > 0; j --)
      {
        unsigned char c = line->Strings[0][j];
        if (c < 0xA6 || 0xDF < c)
          break;
      }
      if (j != 0)
      {
        err ++;
        MemoError->Lines->Add(lines->Strings[i]);
        continue;
      }
      // 最初の文字
      unsigned char c = line->Strings[0][1];
      if (c < 0xB1 || 0xDC < c)
      {
        err ++;
        MemoError->Lines->Add(lines->Strings[i]);
        continue;
      }
      // チェック
      if (line->Strings[0] == "" || line->Strings[0].Length() > 0x10)
      {
        err ++;
        MemoError->Lines->Add(lines->Strings[i]);
        continue;
      }
      if (line->Strings[1] == "" || line->Strings[1].Length() > 50)
      {
        err ++;
        MemoError->Lines->Add(lines->Strings[i]);
        continue;
      }

      // 追加
      TListItem *item = ListView->Items->Add();
      item->Caption = line->Strings[0];
      item->SubItems->Add(line->Strings[1]);
      if (line->Count >= 3)
      {
        int n = StrToIntDef(line->Strings[2], 0);
        if (n < ComboKind->Items->Count)
          item->SubItems->Add(ComboKind->Items->Strings[n]);
        else
          item->SubItems->Add(IntToStr(n));
        item->ImageIndex = n;
      }
      else
      {
        item->SubItems->Add(ComboKind->Items->Strings[0]);
        item->ImageIndex = 0;
      }
      //StatusBar->SimpleText = "処理中... " + IntToStr(100 * i / lines->Count) + "%";
      //StatusBar->Update();
      ProgressBar->Position = i;
      ProgressBar->Update();
    }
    ListView->SortType = Comctrls::stData;
    //StatusBar->SimpleText = "";
    ProgressBar->Position = 0;
    ListView->Items->EndUpdate();
    PageControlChange(NULL);
    modify = (ListView->Items->Count != 0);

    if (err != 0)
    {
      if (Application->MessageBox((IntToStr(lines->Count) + "行中、" + IntToStr(err) + "個の単語が規定外により登録できませんでした\n追加できなかったリストを表示しますか？").c_str(), "警告", MB_YESNO | MB_ICONWARNING) == IDYES)
        PageControl->ActivePage = TabError;
    }
  }
  __finally
  {
    delete line;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyImportCSVClick(TObject *Sender)
{
  OpenDialog->FileName = "*.csv";
  OpenDialog->Filter = "CSVファイル(*.csv)|*.csv|すべてのファイル(*.*)|*.*";
  OpenDialog->Title = "インポート";
  if (OpenDialog->Execute())
  {
    TStringList *lines = new TStringList();
    try
    {
      lines->LoadFromFile(OpenDialog->FileName);
      LoadFromStringList(lines);
    }
    __finally
    {
      delete lines;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyImportPBXClick(TObject *Sender)
{
  OpenDialog->FileName = "*.pbx";
  OpenDialog->Filter = "POBox辞書ファイル(*.pbx)|*.pbx|すべてのファイル(*.*)|*.*";
  OpenDialog->Title = "インポート";
  if (OpenDialog->Execute())
  {
    TStringList *lines = new TStringList();
    try
    {
      lines->LoadFromFile(OpenDialog->FileName);
      while (lines->Count > 0 && lines->Strings[0] != "DicBegin:")
        lines->Delete(0);
      if (lines->Count > 0)
        lines->Delete(0);
      LoadFromStringList(lines);
    }
    __finally
    {
      delete lines;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SaveToStringList(TStringList *lines, bool only)
{
  TStringList *line = new TStringList();
  try
  {
    for (int i = 0; i < ListView->Items->Count; i ++)
    {
      if (only && !ListView->Items->Item[i]->Selected)
        continue;
      line->Clear();
      line->Add(ListView->Items->Item[i]->Caption);
      line->Add(ListView->Items->Item[i]->SubItems->Strings[0]);
      line->Add(IntToStr(ListView->Items->Item[i]->ImageIndex));
      lines->Add(line->CommaText);
    }
  }
  __finally
  {
    delete line;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyExportCSVClick(TObject *Sender)
{
  SaveDialog->FileName = "*.csv";
  SaveDialog->Filter = "CSVファイル(*.csv)|*.csv|すべてのファイル(*.*)|*.*";
  SaveDialog->Title = "エクスポート";
  if (SaveDialog->Execute())
  {
    if (ExtractFileExt(SaveDialog->FileName) == "")
      SaveDialog->FileName = ChangeFileExt(SaveDialog->FileName, ".csv");
    if (FileExists(SaveDialog->FileName))
      if (Application->MessageBox((SaveDialog->FileName + " ファイルは既に存在します。\n上書きしますか？").c_str(), "エクスポート", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
        return;

    TStringList *lines = new TStringList();
    try
    {
      SaveToStringList(lines);
      lines->SaveToFile(SaveDialog->FileName);
      modify = false;
    }
    __finally
    {
      delete lines;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyExportPBXClick(TObject *Sender)
{
  SaveDialog->FileName = "*.pbx";
  SaveDialog->Filter = "POBox辞書ファイル(*.pbx)|*.pbx|すべてのファイル(*.*)|*.*";
  SaveDialog->Title = "エクスポート";
  if (SaveDialog->Execute())
  {
    if (ExtractFileExt(SaveDialog->FileName) == "")
      SaveDialog->FileName = ChangeFileExt(SaveDialog->FileName, ".pbx");
    if (FileExists(SaveDialog->FileName))
      if (Application->MessageBox((SaveDialog->FileName + " ファイルは既に存在します。\n上書きしますか？").c_str(), "エクスポート", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDNO)
        return;

    TStringList *lines = new TStringList();
    try
    {
      lines->Add("DicVer:SEMC_01001001");
      lines->Add("DicChr:Shift_JIS");
      lines->Add("DicDate:" + StringReplace(EditDate->Text, "/", "", TReplaceFlags()<<rfReplaceAll).SubString(1, 8));
      lines->Add("DicTitle:" + EditName->Text);
      AnsiString author = EditAuthor->Text;
      if (author == "")
        author = "yasu";
      else if (author != "yasu" && author.SubString(1, 5) != "yasu/")
        author = "yasu/" + author;
      lines->Add("DicMaker:" + author);
      lines->Add("DicProtect:");
      lines->Add("DicOperator:au_KDDI");
      lines->Add("DicSoftware:AADmaker");
      lines->Add("DicBegin:");
      for (int i = 0; i < ListView->Items->Count; i ++)
        lines->Add(ConvertString(ListView->Items->Item[i]->Caption, LCMAP_HIRAGANA | LCMAP_FULLWIDTH) + "\t" + ListView->Items->Item[i]->SubItems->Strings[0]);
      lines->SaveToFile(SaveDialog->FileName);
      modify = false;
    }
    __finally
    {
      delete lines;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonNowClick(TObject *Sender)
{
  EditDate->Text = TDateTime::CurrentDateTime().FormatString("yyyy/mm/dd hh:nn:ss");
}
//---------------------------------------------------------------------------
bool __fastcall TForm1::CheckInput()
{
  if (EditYomi->Text == "")
  {
    Application->MessageBox("読みを入力して下さい", "エラー", MB_OK | MB_ICONERROR);
    EditYomi->SetFocus();
    return false;
  }
  if (EditGoku->Text == "")
  {
    Application->MessageBox("語句を入力して下さい", "エラー", MB_OK | MB_ICONERROR);
    EditGoku->SetFocus();
    return false;
  }
  if (ComboKind->ItemIndex == -1)
  {
    ComboKind->ItemIndex = 0;
    //Application->MessageBox("種類を選択して下さい", "エラー", MB_OK | MB_ICONERROR);
    //ComboKind->SetFocus();
    //return false;
  }

  // まな→カナ＆全角→半角
  EditYomi->Text = ConvertString(EditYomi->Text, LCMAP_KATAKANA | LCMAP_HALFWIDTH);
  // 半角カナのみか
  for (int i = EditYomi->Text.Length(); i > 0; i --)
  {
    unsigned char c = EditYomi->Text[i];
    if (c < 0xA6 || 0xDF < c)
    {
      Application->MessageBox("読みが不正です。使用できる文字は半角カタカナのみです", "エラー", MB_OK | MB_ICONERROR);
      EditYomi->SetFocus();
      return false;
    }
  }
  // 最初の文字
  unsigned char c = EditYomi->Text[1];
  if (c < 0xB1 || 0xDC < c)
  {
    Application->MessageBox("読みの最初の文字が不正です。最初の文字はア～ワである必要があります", "エラー", MB_OK | MB_ICONERROR);
    EditYomi->SetFocus();
    return false;
  }
  // 長さチェック
  if (EditYomi->Text.Length() > 0x10)
  {
    Application->MessageBox("読みが長すぎます。半角カタカナで10文字までです。", "エラー", MB_OK | MB_ICONERROR);
    EditYomi->SetFocus();
    return false;
  }
  if (EditGoku->Text.Length() > 50)
  {
    Application->MessageBox("語句が長すぎます。半角で50文字、全角で25文字でです。", "エラー", MB_OK | MB_ICONERROR);
    EditGoku->SetFocus();
    return false;
  }

  return true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonAddClick(TObject *Sender)
{
  if (!CheckInput())
    return;

  TListItem *item = ListView->Items->Add();
  item->Caption = EditYomi->Text;
  item->SubItems->Add(EditGoku->Text);
  item->SubItems->Add(ComboKind->Text);
  item->ImageIndex = ComboKind->ItemIndex;
  ListView->Selected = NULL;
  ListView->Selected = item;
  item->MakeVisible(false);
  modify = true;

  EditYomi->Text = "";
  EditGoku->Text = "";
  EditYomi->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonChangeClick(TObject *Sender)
{
  if (ListView->Selected == NULL)
    return;
  if (!CheckInput())
    return;

  TListItem *item = ListView->Selected;
  item->Caption = EditYomi->Text;
  item->SubItems->Strings[0] = EditGoku->Text;
  item->SubItems->Strings[1] = ComboKind->Text;
  item->ImageIndex = ComboKind->ItemIndex;
  ListView->Selected = NULL;
  ListView->Selected = item;
  item->MakeVisible(false);
  modify = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyDeleteClick(TObject *Sender)
{
  ListView->Items->BeginUpdate();
  ProgressBar->Max = ListView->Items->Count;
  for (int i = ListView->Items->Count - 1, j = 0; i >= 0; i --, j ++)
  {
    //StatusBar->SimpleText = "処理中... " + IntToStr(100 - 100 * i / ListView->Items->Count) + "%";
    //StatusBar->Update();
    if (ListView->Items->Item[i]->Selected)
      ListView->Items->Delete(i);
    ProgressBar->Position = j;
    ProgressBar->Update();
  }
  //StatusBar->SimpleText = "";
  ProgressBar->Position = 0;
  ListView->Items->EndUpdate();
  PageControlChange(Sender);
  modify = (ListView->Items->Count != 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeySelectAllClick(TObject *Sender)
{
  ListView->Items->BeginUpdate();
  for (int i = ListView->Items->Count - 1; i >= 0; i --)
    ListView->Items->Item[i]->Selected = true;
  ListView->Items->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ListViewSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
  if (Selected)
  {
    EditYomi->Text = Item->Caption;
    EditGoku->Text = Item->SubItems->Strings[0];
    ComboKind->ItemIndex = Item->ImageIndex;
  }
  else
  {
    EditYomi->Text = "";
    EditGoku->Text = "";
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PageControlChange(TObject *Sender)
{
  EditCount->Text = IntToStr(ListView->Items->Count);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyEditClick(TObject *Sender)
{
  KeyCut->Enabled = (ListView->Selected != NULL);
  KeyCopy->Enabled = (ListView->Selected != NULL);
  KeyPaste->Enabled = Clipboard()->HasFormat(CF_TEXT);
  KeyDelete->Enabled = (ListView->Selected != NULL);
  KeyCut2->Enabled = KeyCut->Enabled;
  KeyCopy2->Enabled = KeyCopy->Enabled;
  KeyPaste2->Enabled = KeyPaste->Enabled;
  KeyDelete2->Enabled = KeyDelete->Enabled;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyCopyClick(TObject *Sender)
{
  TStringList *lines = new TStringList();
  try
  {
    SaveToStringList(lines, true);
    Clipboard()->AsText = lines->Text;
  }
  __finally
  {
    delete lines;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyCutClick(TObject *Sender)
{
  KeyCopyClick(Sender);
  KeyDeleteClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyPasteClick(TObject *Sender)
{
  if (!Clipboard()->HasFormat(CF_TEXT))
    return;

  if (ListView->Selected != NULL)
    KeyDeleteClick(Sender);

  TStringList *lines = new TStringList();
  try
  {
    lines->Text = Clipboard()->AsText;
    LoadFromStringList(lines);
  }
  __finally
  {
    delete lines;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ListViewCompare(TObject *Sender, TListItem *Item1,
      TListItem *Item2, int Data, int &Compare)
{
  int len1 = Item1->Caption.Length();
  int len2 = Item2->Caption.Length();
  int len = len1 < len2 ? len1 : len2;
  for (int i = 1; i <= len; i ++)
  {
    int j = Item1->Caption[i] - Item2->Caption[i];
    if (j != 0)
    {
      Compare = j;
      return;
    }
  }
  Compare = len1 - len2;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonSetCountClick(TObject *Sender)
{
  int n = StrToIntDef(EditCount->Text, ListView->Items->Count);
  if (n < 0)
  {
    n = 0;
    EditCount->Text = "0";
  }
  int m = ListView->Items->Count - n;
  ListView->Items->BeginUpdate();
  ProgressBar->Max = m;
  for (int i = ListView->Items->Count - 1, j = 0; i >= n; i --, j ++)
  {
    ListView->Items->Delete(i);
    //StatusBar->SimpleText = "処理中... " + IntToStr(100 - 100 * (i - n) / m) + "%";
    //StatusBar->Update();
    ProgressBar->Position = j;
    ProgressBar->Update();
  }
  //StatusBar->SimpleText = "";
  ProgressBar->Position = 0;
  ListView->Items->EndUpdate();
  modify = (ListView->Items->Count != 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyFindClick(TObject *Sender)
{
  findkey = "";
  KeyFindNextClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyFindNextClick(TObject *Sender)
{
  if (findkey == "")
  {
    if (!InputQuery("読みの検索", "検索文字列", findkey) || findkey == "")
      return;
    findpos = 0;
    findkey = ConvertString(findkey, LCMAP_KATAKANA | LCMAP_HALFWIDTH);
  }

  TListItem *item = ListView->FindCaption(findpos, findkey, true, true, false);
  ListView->Selected = NULL;
  if (item == NULL)
  {
    if (findpos == 0)
      findkey = "";
    else
      findpos = 0;
    Application->MessageBox("最後まで検索しました", "検索", MB_OK | MB_ICONINFORMATION);
  }
  else
  {
    ListView->Selected = item;
    item->MakeVisible(false);
    findpos = item->Index + 1;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyDelMultiClick(TObject *Sender)
{
  ListView->Items->BeginUpdate();
  int st = ListView->Items->Count;
  for (int i = 0; i < ListView->Items->Count; i ++)
  {
    //StatusBar->SimpleText = "処理中... " + IntToStr(100 * i / ListView->Items->Count) + "%";
    //StatusBar->Update();
    ProgressBar->Position = i;
    ProgressBar->Max = ListView->Items->Count;
    ProgressBar->Update();
    for (int j = i + 1; j < ListView->Items->Count; j ++)
    {
      if (ListView->Items->Item[i]->Caption != ListView->Items->Item[j]->Caption)
        break;
      if (ListView->Items->Item[i]->ImageIndex == ListView->Items->Item[j]->ImageIndex
        && ListView->Items->Item[i]->SubItems->Strings[0] == ListView->Items->Item[j]->SubItems->Strings[0])
        ListView->Items->Delete(j --);
    }
  }
  //StatusBar->SimpleText = "";
  ProgressBar->Position = 0;
  ListView->Items->EndUpdate();
  PageControlChange(Sender);
  modify = modify || (ListView->Items->Count != st);
  Application->MessageBox((IntToStr(st - ListView->Items->Count) + "件の重複を削除しました").c_str(), "重複を削除", MB_OK | MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyBarAddClick(TObject *Sender)
{
  ListView->Items->BeginUpdate();
  ListView->SortType = Comctrls::stNone;
  int n = ListView->Items->Count;
  ProgressBar->Max = n;
  for (int i = 0; i < n; i ++)
  {
    AnsiString s = ListView->Items->Item[i]->Caption;
    int len = s.Length();
    bool f = false;
    for (int j = 2; j <= len; j ++)
    {
      if ((unsigned char)s[j] == 0xB0) // ー
      {
        s[j] = GetVowel(s.c_str(), j-2);
        f = true;
      }
    }

    if (f)
    {
      // 追加
      TListItem *item = ListView->Items->Add();
      item->Caption = s;
      item->SubItems->Add(ListView->Items->Item[i]->SubItems->Strings[0]);
      item->SubItems->Add(ListView->Items->Item[i]->SubItems->Strings[1]);
      item->ImageIndex = ListView->Items->Item[i]->ImageIndex;
    }

    //StatusBar->SimpleText = "処理中... " + IntToStr(100 * i / ListView->Items->Count) + "%";
    //StatusBar->Update();
    ProgressBar->Position = i;
    ProgressBar->Update();
  }
  //StatusBar->SimpleText = "";
  ProgressBar->Position = 0;
  ListView->SortType = Comctrls::stData;
  ListView->Items->EndUpdate();
  PageControlChange(Sender);
  modify = modify || (ListView->Items->Count != n);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::KeyBarChangeClick(TObject *Sender)
{
  ListView->Items->BeginUpdate();
  ListView->SortType = Comctrls::stNone;
  ProgressBar->Max = ListView->Items->Count;
  for (int i = 0; i < ListView->Items->Count; i ++)
  {
    AnsiString s = ListView->Items->Item[i]->Caption;
    int len = s.Length();
    bool f = false;
    for (int j = 2; j <= len; j ++)
    {
      if ((unsigned char)s[j] == 0xB0) // ー
      {
        s[j] = GetVowel(s.c_str(), j-2);
        f = true;
      }
    }
    if (f)
    {
      ListView->Items->Item[i]->Caption = s;
      modify = modify || f;
    }

    //StatusBar->SimpleText = "処理中... " + IntToStr(100 * i / ListView->Items->Count) + "%";
    //StatusBar->Update();
    ProgressBar->Position = i;
    ProgressBar->Update();
  }
  //StatusBar->SimpleText = "";
  ProgressBar->Position = 0;
  ListView->SortType = Comctrls::stData;
  ListView->Items->EndUpdate();
  PageControlChange(Sender);
}
//---------------------------------------------------------------------------


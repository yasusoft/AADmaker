//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("AADmaker.res");
USEFORM("Unit1.cpp", Form1);
USEUNIT("crc.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "AADmaker";
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------

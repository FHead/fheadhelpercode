//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Encoder.h"
#include "LSC.h"
#include "FileProcess.h"
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
void __fastcall TForm1::Button5Click(TObject *Sender)
{
   exit(0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
   if(OpenDialog1->Execute() == false)
      return;

   InputEdit->Text = OpenDialog1->FileName;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
   if(SaveDialog1->Execute() == false)
      return;

   OutputEdit->Text = SaveDialog1->FileName;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
   if(InputEdit->Text == "")
      return;
   if(OutputEdit->Text == "")
      return;
   if(PasswordEdit->Text == "")
      return;

   double x0 = GetX0();
   double mju = Getmju();

   LSCDecrypt(InputEdit->Text.c_str(), "temp1.temp", x0, mju, 1e8, LSC_MODE_JUMPED);
   LSCEncrypt("temp1.temp", "temp2.temp", x0, mju, 1e8, LSC_MODE_ORIGINAL);
   LSCDecrypt("temp2.temp", OutputEdit->Text.c_str(), x0, mju, 1e8, LSC_MODE_JUMPED);

   ClearFile("temp1.temp");
   ClearFile("temp2.temp");

   ShowMessage("Done");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
   if(InputEdit->Text == "")
      return;
   if(OutputEdit->Text == "")
      return;
   if(PasswordEdit->Text == "")
      return;

   double x0 = GetX0();
   double mju = Getmju();

   LSCEncrypt(InputEdit->Text.c_str(), "temp2.temp", x0, mju, 1e8, LSC_MODE_JUMPED);
   LSCDecrypt("temp2.temp", "temp1.temp", x0, mju, 1e8, LSC_MODE_ORIGINAL);
   LSCEncrypt("temp1.temp", OutputEdit->Text.c_str(), x0, mju, 1e8, LSC_MODE_JUMPED);

   ClearFile("temp1.temp");
   ClearFile("temp2.temp");

   ShowMessage("Done");
}
//---------------------------------------------------------------------------
double TForm1::GetX0()
{
   int sum = 0;
   for(int i = 1; i <= PasswordEdit->Text.Length(); i++)
      sum = sum + PasswordEdit->Text[i] * i;

   sum = sum % 1000000;

   if(sum == 750000 || sum == 250000)
      sum = sum + 1;

   return (double)(sum) / 1000000;
}
//---------------------------------------------------------------------------
double TForm1::Getmju()
{
   long long product = 1;
   for(int i = 1; i <= PasswordEdit->Text.Length(); i++)
      product = (product * (PasswordEdit->Text[i] + i) + i) % 1000000;

   return 4.0 - (double)(product) / 10000000;
}
//---------------------------------------------------------------------------

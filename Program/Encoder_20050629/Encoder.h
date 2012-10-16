//---------------------------------------------------------------------------

#ifndef EncoderH
#define EncoderH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
   TEdit *InputEdit;
   TButton *Button1;
   TButton *Button2;
   TEdit *OutputEdit;
   TButton *Button3;
   TButton *Button4;
   TButton *Button5;
   TEdit *PasswordEdit;
   TOpenDialog *OpenDialog1;
   TSaveDialog *SaveDialog1;
   void __fastcall Button5Click(TObject *Sender);
   void __fastcall Button1Click(TObject *Sender);
   void __fastcall Button2Click(TObject *Sender);
   void __fastcall Button3Click(TObject *Sender);
   void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
   double GetX0();
   double Getmju();
public:		// User declarations
   __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

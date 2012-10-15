//---------------------------------------------------------------------------
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
//---------------------------------------------------------------------------
#include "ProgressBar.h"
#include "LSC.h"
//---------------------------------------------------------------------------
LargeInteger NextNumber(LargeInteger previous, LargeInteger mu)
{
   static LargeInteger max(1);
   static bool FirstTime = true;
   if(FirstTime == true)
   {
      for(int i = 0; i < XPRECISION; i++)
         max = max * 10;
      FirstTime = false;
   }

   LargeInteger next = mu * previous * (max - previous);

   return next.ShiftOutDigits(MUPRECISION + XPRECISION);
}
//---------------------------------------------------------------------------
LargeInteger IterateNumber(LargeInteger previous, LargeInteger mu, int iteration)
{
   LargeInteger x0 = previous;
   for(int i = 0; i < iteration; i++)
      x0 = NextNumber(x0, mu);
   return x0;
}
//---------------------------------------------------------------------------
int GetNumber(LargeInteger x)
{
   return x % 256;
}
//---------------------------------------------------------------------------
void CopyFile(string SourceFileName, string TargetFileName)
{
   ifstream in(SourceFileName.c_str(), ios::binary);

   ofstream out(TargetFileName.c_str(), ios::binary | ios::trunc);

   while(in)
   {
      char c = '\0';
      in.get(c);

      if(!in)
         break;

      out.put(c);
   }

   out.close();

   in.close();
}
//---------------------------------------------------------------------------
void EncryptFile(string FileName, LargeInteger x0, LargeInteger mu, bool jump)
{
   fstream file(FileName.c_str(), ios::in | ios::out | ios::binary);

   file.seekg(0, ifstream::end);
   long long size = file.tellg();

   file.seekg(ios_base::beg);
   file.seekp(ios_base::beg);

   ProgressBar Bar(cout, size);
   Bar.SetStyle(1);
   Bar.Update(0);

   for(long long i = 0; i < size; i++)
   {
      if(size < 1000 || i % (size / 1000) == 0)
      {
         Bar.Update((double)i);
         Bar.Print();
      }

      char c = '\0';

      file.seekg(ios_base::beg + i);
      file.get(c);

      c = (unsigned int)c ^ GetNumber(x0);

      int current = c;
      if(current < 0)
         current = current + 256;

      if(jump == false)
         x0 = NextNumber(x0, mu);
      else
         x0 = IterateNumber(x0, mu, current);

      file.seekp(ios_base::beg + i);
      file.put(c);
   }

   Bar.Update(size);
   Bar.Print();
   Bar.PrintLine();

   file.close();
}
//---------------------------------------------------------------------------
void DecryptFile(string FileName, LargeInteger x0, LargeInteger mu, bool jump)
{
   fstream file(FileName.c_str(), ios::in | ios::out | ios::binary);

   file.seekg(0, ifstream::end);
   long long size = file.tellg();

   file.seekg(ios_base::beg);
   file.seekp(ios_base::beg);

   ProgressBar Bar(cout, size);
   Bar.SetStyle(1);

   for(long long i = 0; i < size; i++)
   {
      if(size < 1000 || i % (size / 1000) == 0)
      {
         Bar.Update(i);
         Bar.Print();
      }

      char c = '\0';

      file.seekg(ios_base::beg + i);
      file.get(c);

      int current = (int)c;
      if(current < 0)
         current = current + 256;

      c = (unsigned int)c ^ GetNumber(x0);

      if(jump == false)
         x0 = NextNumber(x0, mu);
      else
         x0 = IterateNumber(x0, mu, current);

      file.seekp(ios_base::beg + i);
      file.put(c);
   }

   Bar.Update(size);
   Bar.Print();
   Bar.PrintLine();

   file.close();
}
//---------------------------------------------------------------------------


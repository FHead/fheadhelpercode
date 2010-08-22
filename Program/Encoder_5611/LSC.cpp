//---------------------------------------------------------------------------
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
//---------------------------------------------------------------------------
#include "LSC.h"
//---------------------------------------------------------------------------
double NextNumber(double previous, double mu, double precision)
{
   double next = mu * previous * (1 - previous);

   next = (long long)(next * precision);

   return next / precision;
}
//---------------------------------------------------------------------------
double IterateNumber(double previous, double mu, double precision, int iteration)
{
   double x0 = previous;
   for(int i = 0; i < iteration; i++)
      x0 = NextNumber(x0, mu, precision);
   return x0;
}
//---------------------------------------------------------------------------
int GetNumber(double x, double precision)
{
   return (long long)(x * precision) % 256;
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
void EncryptFile(string FileName, double x0, double mu, double precision, bool jump)
{
   fstream file(FileName.c_str(), ios::in | ios::out | ios::binary);

   file.seekg(0, ifstream::end);
   long long size = file.tellg();

   file.seekg(ios_base::beg);
   file.seekp(ios_base::beg);

   for(long long i = 0; i < size; i++)
   {
      char c = '\0';

      file.seekg(ios_base::beg + i);
      file.get(c);

      c = (unsigned int)c ^ GetNumber(x0, precision);

      int current = c;
      if(current < 0)
         current = current + 256;

      if(jump == false)
         x0 = NextNumber(x0, mu, precision);
      else
         x0 = IterateNumber(x0, mu, precision, current);

      file.seekp(ios_base::beg + i);
      file.put(c);
   }

   file.close();
}
//---------------------------------------------------------------------------
void DecryptFile(string FileName, double x0, double mu, double precision, bool jump)
{
   fstream file(FileName.c_str(), ios::in | ios::out | ios::binary);

   file.seekg(0, ifstream::end);
   long long size = file.tellg();

   file.seekg(ios_base::beg);
   file.seekp(ios_base::beg);

   for(long long i = 0; i < size; i++)
   {
      char c = '\0';

      file.seekg(ios_base::beg + i);
      file.get(c);

      int current = (int)c;
      if(current < 0)
         current = current + 256;

      c = (unsigned int)c ^ GetNumber(x0, precision);

      if(jump == false)
         x0 = NextNumber(x0, mu, precision);
      else
         x0 = IterateNumber(x0, mu, precision, current);

      file.seekp(ios_base::beg + i);
      file.put(c);
   }

   file.close();
}
//---------------------------------------------------------------------------


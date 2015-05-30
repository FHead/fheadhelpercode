#include <iostream>
using namespace std;

int main();
int CharacterSaved(string Number);
int CountCharacters(string Number);
int RomanToInteger(string Number);
string IntegerToRoman(int Number);

int main()
{
   int Result = 0;

   while(cin)
   {
      string Number = "";
      cin >> Number;
      if(Number.size() == 0)
         continue;

      int Saved = CharacterSaved(Number);
      Result = Result + Saved;
      cout << Saved << endl;
   }

   cout << endl;

   cout << Result << endl;

   return 0;
}

int CharacterSaved(string Number)
{
   return (int)Number.size() - CountCharacters(Number);
}

int CountCharacters(string Number)
{
   int Value = RomanToInteger(Number);
   string BestForm = IntegerToRoman(Value);

   return BestForm.size();
}

int RomanToInteger(string Number)
{
   int Value = 0;
   int Length = Number.size();

   for(int i = 0; i < Length; i++)
   {
      if(Number[i] == 'I')
      {
         if(i != Length - 1 && Number[i+1] == 'V')
         {
            Value = Value + 4;
            i = i + 1;
         }
         else if(i != Length - 1 && Number[i+1] == 'X')
         {
            Value = Value + 9;
            i = i + 1;
         }
         else
            Value = Value + 1;
      }
      else if(Number[i] == 'V')
         Value = Value + 5;
      else if(Number[i] == 'X')
      {
         if(i != Length - 1 && Number[i+1] == 'L')
         {
            Value = Value + 40;
            i = i + 1;
         }
         else if(i != Length - 1 && Number[i+1] == 'C')
         {
            Value = Value + 90;
            i = i + 1;
         }
         else
            Value = Value + 10;
      }
      else if(Number[i] == 'L')
         Value = Value + 50;
      else if(Number[i] == 'C')
      {
         if(i != Length - 1 && Number[i+1] == 'D')
         {
            Value = Value + 400;
            i = i + 1;
         }
         else if(i != Length - 1 && Number[i+1] == 'M')
         {
            Value = Value + 900;
            i = i + 1;
         }
         else
            Value = Value + 100;
      }
      else if(Number[i] == 'D')
         Value = Value + 500;
      else if(Number[i] == 'M')
         Value = Value + 1000;
      else
         cerr << "Meow!" << endl;
   }

   return Value;
}

string IntegerToRoman(int Number)
{
   string Result = "";

   int D0 = (Number / 1) % 10;
   int D1 = (Number / 10) % 10;
   int D2 = (Number / 100) % 10;
   int D3 = (Number / 1000) % 10;

   for(int i = 0; i < D3; i++)
      Result = Result + "M";

   if(D2 == 9)
      Result = Result + "CM";
   else if(D2 == 4)
      Result = Result + "CD";
   else
   {
      if(D2 >= 5)
         Result = Result + "D";
      for(int i = 0; i < D2 % 5; i++)
         Result = Result + "C";
   }
   
   if(D1 == 9)
      Result = Result + "XC";
   else if(D1 == 4)
      Result = Result + "XL";
   else
   {
      if(D1 >= 5)
         Result = Result + "L";
      for(int i = 0; i < D1 % 5; i++)
         Result = Result + "X";
   }
   
   if(D0 == 9)
      Result = Result + "IX";
   else if(D0 == 4)
      Result = Result + "IV";
   else
   {
      if(D0 >= 5)
         Result = Result + "V";
      for(int i = 0; i < D0 % 5; i++)
         Result = Result + "I";
   }

   return Result;
}



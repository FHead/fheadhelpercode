#include <iostream>
using namespace std;

bool IsGood(int Number);
int main();

bool IsGood(int Number)
{
   int OriginalNumber = Number;
   int Sum = 0;

   for(int i = 0; i < 10; i++)
   {
      int Digit = Number % 10;
      Number = Number / 10;
      Sum = Sum + Digit * Digit * Digit * Digit * Digit;
   }

   if(Sum == OriginalNumber)
      return true;
   return false;
}

int main()
{
   int Sum = 0;
   for(int i = 10; i < 10000000; i++)
      if(IsGood(i) == true)
         Sum = Sum + i;

   cout << Sum << endl;

   return 0;
}




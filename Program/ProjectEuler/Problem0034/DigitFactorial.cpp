#include <iostream>
using namespace std;

int main();
bool CheckIfGood(int Number);

int main()
{
   long long Total = 0;

   for(int i = 10; i < 10000000; i++)
   {
      if(CheckIfGood(i) == true)
      {
         Total = Total + i;
         cout << "Detected: " << i << endl;
      }
   }

   cout << Total << endl;

   return 0;
}

bool CheckIfGood(int Number)
{
   int Factorials[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

   int FactorialSum = 0;
   int Temp = Number;
   while(Temp > 0)
   {
      FactorialSum = FactorialSum + Factorials[Temp%10];
      Temp = Temp / 10;
   }

   if(FactorialSum == Number)
      return true;
   return false;
}





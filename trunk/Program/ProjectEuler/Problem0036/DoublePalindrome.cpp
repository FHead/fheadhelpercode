#include <iostream>
#include <vector>
using namespace std;

int main();
bool CheckBase10(int Number);
bool CheckBase2(int Number);
bool CheckBaseN(int Number, int N);

int main()
{
   int Total = 0;

   for(int i = 1; i < 1000000; i++)
   {
      if(CheckBase10(i) == false)
         continue;
      if(CheckBase2(i) == false)
         continue;

      cout << i << endl;

      Total = Total + i;
   }

   cout << "Total of all numbers: " << Total << endl;

   return 0;
}

bool CheckBase10(int Number)
{
   return CheckBaseN(Number, 10);
}

bool CheckBase2(int Number)
{
   return CheckBaseN(Number, 2);
}

bool CheckBaseN(int Number, int N)
{
   vector<int> Digits;

   int Temp = Number;
   while(Temp > 0)
   {
      Digits.push_back(Temp % N);
      Temp = Temp / N;
   }

   for(int i = 0; i < (int)Digits.size(); i++)
      if(Digits[i] != Digits[Digits.size()-1-i])
         return false;

   return true;
}



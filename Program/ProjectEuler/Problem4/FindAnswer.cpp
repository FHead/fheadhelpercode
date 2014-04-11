#include <cmath>
#include <iostream>
using namespace std;

int main();
bool IsPalindrome(int Number);

int main()
{
   int MaxResult = 0;

   for(int i = 100; i <= 999; i++)
   {
      for(int j = i; j <= 999; j++)
      {
         if(IsPalindrome(i * j) == false)
            continue;

         if(i * j > MaxResult)
            MaxResult = i * j;
      }
   }

   cout << MaxResult << endl;

   return 0;
}

bool IsPalindrome(int Number)
{
   if((Number / 1) % 10 != (Number / 100000) % 10)
      return false;
   if((Number / 10) % 10 != (Number / 10000) % 10)
      return false;
   if((Number / 100) % 10 != (Number / 1000) % 10)
      return false;

   return true;
}




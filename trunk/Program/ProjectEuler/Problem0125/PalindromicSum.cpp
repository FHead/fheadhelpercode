#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main();
bool CheckPalindrome(int Sum);

int main()
{
   int Threshold = 100000000;

   vector<int> Valid;

   for(int i = 0; i < 100000000; i++)
   {
      bool First = true;

      for(int j = i + 2; j < 100000000; j++)
      {
         int Sum = ((long long)j * (j + 1) * (2 * j + 1) - (long long)i * (i + 1) * (2 * i + 1)) / 6;
         if(Sum > Threshold)
            break;

         First = false;

         if(CheckPalindrome(Sum) == true)
         {
            // cout << "PALINDROME " << i << " " << j << " " << Sum << endl;
            Valid.push_back(Sum);
         }
      }

      if(First == true)
         break;
   }

   sort(Valid.begin(), Valid.end());
   vector<int>::iterator iter = unique(Valid.begin(), Valid.end());
   Valid.erase(iter, Valid.end());

   long long Total = 0;
   for(int i = 0; i < Valid.size(); i++)
      Total = Total + Valid[i];
   cout << Total << endl;

   return 0;
}

bool CheckPalindrome(int Sum)
{
   int Original = Sum;
   vector<int> Digits;

   while(Sum > 0)
   {
      Digits.push_back(Sum % 10);
      Sum = Sum / 10;
   }
   reverse(Digits.begin(), Digits.end());

   // cout << Original << "  ";
   // for(int i = 0; i < (int)Digits.size(); i++)
   //    cout << Digits[i] << " ";
   // cout << endl;

   for(int i = 0; i < (int)Digits.size(); i++)
   {
      if(Digits[i] != Digits[Digits.size()-i-1])
         return false;
   }

   return true;
}





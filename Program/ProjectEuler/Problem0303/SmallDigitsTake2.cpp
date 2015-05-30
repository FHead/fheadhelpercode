#include <algorithm>
#include <iostream>
#include <deque>
using namespace std;

#include "../Utilities/BigNumber.h"

int main();
BigNumber F(int N);
bool Check(BigNumber N);

int main()
{
   cout << F(122101202) << endl;
   cout << F(2) * 2 << endl;
   cout << F(3) * 3 << endl;
   cout << F(7) * 7 << endl;
   cout << F(42) * 42 << endl;
   cout << F(89) * 89 << endl;

   BigNumber Total = 0;
   for(int i = 1; i <= 100; i++)
      Total = Total + F(i);
   cout << Total << endl;
   
   Total = 0;
   for(int i = 1; i <= 10000; i++)
   {
      if(i == 9999)
         continue;

      BigNumber Answer = F(i);
      cout << i << " " << Answer << " " << BigNumber(i) * Answer << endl;
      Total = Total + Answer;
   }
   cout << Total << endl;

   return 0;
}

BigNumber F(int N)
{
   bool Good = Check(BigNumber(N));
   if(Good == true)
      return 1;

   while(N % 10 == 0 && N > 0)
      N = N / 10;

   deque<BigNumber> PotentialN;
   for(int i = 1; i < 10; i++)
      if((N * i) % 10 <= 2)
         PotentialN.push_back(i);

   int Digit = 1;
   BigNumber Power = 1;
   BigNumber FinalAnswer = -1;

   bool Terminate = false;
   while(Terminate == false)
   {
      cout << Digit << ", " << PotentialN.size() << endl;

      deque<BigNumber> Answers;
      for(int i = 0; i < (int)PotentialN.size(); i++)
         if(Check(BigNumber(N) * PotentialN[i]) == true)
            Answers.push_back(PotentialN[i]);
      if(Answers.size() > 0)
      {
         Terminate = true;
         sort(Answers.begin(), Answers.end());
         FinalAnswer = Answers[0];
      }

      Digit = Digit + 1;
      Power = Power * 10;

      deque<BigNumber> NextNs;
      for(int i = 0; i < (int)PotentialN.size(); i++)
      {
         for(int j = 0; j < 10; j++)
         {
            BigNumber X = PotentialN[i] + Power * j;
            if((X * N)[Digit-1] % 10 <= 2)
               NextNs.push_back(X);
         }
      }

      PotentialN = NextNs;
   }

   return FinalAnswer;
}

bool Check(BigNumber N)
{
   bool Good = true;
   for(int i = 0; i < (int)N.Digits.size(); i++)
      if(N.Digits[i] > 2)
         Good = false;
   return Good;
}





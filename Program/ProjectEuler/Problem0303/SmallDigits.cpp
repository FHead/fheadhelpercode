#include <algorithm>
#include <iostream>
#include <deque>
using namespace std;

int main();
__int64_t F(__int64_t N);
bool Check(__int64_t N);

int main()
{
   cout << F(122101202) << endl;
   cout << F(2) * 2 << endl;
   cout << F(3) * 3 << endl;
   cout << F(7) * 7 << endl;
   cout << F(42) * 42 << endl;
   cout << F(89) * 89 << endl;

   __int64_t Total = 0;
   for(__int64_t i = 1; i <= 100; i++)
      Total = Total + F(i);
   cout << Total << endl;
   
   Total = 0;
   for(__int64_t i = 1; i <= 10000; i++)
   {
      __int64_t Answer = F(i);
      cout << i << " " << Answer << " " << i * Answer << endl;
      Total = Total + Answer;
   }
   cout << Total << endl;

   return 0;
}

__int64_t F(__int64_t N)
{
   bool Good = Check(N);
   if(Good == true)
      return 1;

   deque<__int64_t> PotentialN;
   for(__int64_t i = 1; i < 10; i++)
      if((N * i) % 10 <= 2)
         PotentialN.push_back(i);

   __int64_t Digit = 1;
   __int64_t Power = 1;
   __int64_t FinalAnswer = -1;

   bool Terminate = false;
   while(Terminate == false)
   {
      deque<__int64_t> Answers;
      for(__int64_t i = 0; i < (__int64_t)PotentialN.size(); i++)
         if(Check(N * PotentialN[i]) == true)
            Answers.push_back(PotentialN[i]);
      if(Answers.size() > 0)
      {
         Terminate = true;
         sort(Answers.begin(), Answers.end());
         FinalAnswer = Answers[0];
      }

      Digit = Digit + 1;
      Power = Power * 10;

      deque<__int64_t> NextNs;
      for(__int64_t i = 0; i < (__int64_t)PotentialN.size(); i++)
      {
         for(__int64_t j = 0; j < 10; j++)
         {
            __int64_t X = PotentialN[i] + j * Power;
            if(((X * N) / Power) % 10 <= 2)
               NextNs.push_back(X);
         }
      }

      PotentialN = NextNs;
   }

   return FinalAnswer;
}

bool Check(__int64_t N)
{
   bool Good = true;
   __int64_t Temp = N;
   while(Temp > 0)
   {
      if(Temp % 10 > 2)
         Good = false;
      Temp = Temp / 10;
   }

   return Good;
}





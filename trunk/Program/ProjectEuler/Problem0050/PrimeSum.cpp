#include <iostream>
#include <vector>
using namespace std;

vector<int> ListPrimes();
int main();

vector<int> ListPrimes()
{
   vector<int> Result;
   Result.push_back(2);
   Result.push_back(3);
   Result.push_back(5);
   Result.push_back(7);
   Result.push_back(11);
   Result.push_back(13);

   for(int i = 17; i < 1000000; i = i + 2)
   {
      bool Good = true;
      for(int j = 0; j < (int)Result.size(); j++)
      {
         if(i % Result[j] == 0)
            Good = false;
         if(Result[j] * Result[j] > i)
            break;
      }

      if(Good == true)
         Result.push_back(i);
   }

   return Result;
}

int main()
{
   vector<int> Primes = ListPrimes();
   vector<int> SumPrimes(Primes.size());

   SumPrimes[0] = Primes[0];
   for(int i = 1; i < (int)Primes.size(); i++)
      SumPrimes[i] = SumPrimes[i-1] + Primes[i];
   SumPrimes.insert(SumPrimes.begin(), 0);

   int Answer = 2;
   int Length = 1;

   for(int i = 0; i < (int)Primes.size(); i++)
   {
      int Target = Primes[i];

      int BestSoFar = -1;
      int Left = 0;
      int Right = 1;

      while(Right < (int)SumPrimes.size())
      {
         int Sum = SumPrimes[Right] - SumPrimes[Left];

         if(Sum < Target)
            Right = Right + 1;
         else if(Sum > Target)
            Left = Left + 1;
         else
         {
            if(Right - Left > BestSoFar)
               BestSoFar = Right - Left;
            Left = Left + 1;
            Right = Right + 1;
         }
      }

      // cout << Target << " " << BestSoFar << endl;

      if(BestSoFar > Length)
      {
         Answer = Target;
         Length = BestSoFar;
      }
   }

   cout << Answer << endl;

   return 0;
}





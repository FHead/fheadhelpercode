#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main();
bool IsAbundant(int N);
bool CheckSum(int N);

int main()
{
   int Total = 0;

   for(int i = 1; i < 29000; i++)
   {
      bool Result = CheckSum(i);
      if(Result == false)
      {
         cout << i << " " << CheckSum(i) << endl;
         Total = Total + i;
      }
   }

   cout << "Total = " << Total << endl;

   return 0;
}

bool IsAbundant(int N)
{
   static map<int, bool> Cache;

   if(Cache.find(N) != Cache.end())
      return Cache[N];

   static vector<int> Primes;
   if(Primes.size() == 0)
   {
      Primes.push_back(2);
      Primes.push_back(3);
      Primes.push_back(5);
      Primes.push_back(7);
      for(int i = 11; i < 10000; i = i + 2)
      {
         bool Good = true;
         for(int j = 0; j < (int)Primes.size() && Primes[j] * Primes[j] <= i; j++)
            if(i % Primes[j] == 0)
               Good = false;
         if(Good == true)
            Primes.push_back(i);
      }
   }

   int Temp = N;
   vector<int> Factors(Primes.size());
   for(int i = 0; i < (int)Primes.size() && Temp > 1; i++)
   {
      while(Temp % Primes[i] == 0)
      {
         Temp = Temp / Primes[i];
         Factors[i] = Factors[i] + 1;
      }
   }

   int Sum = 1;
   for(int i = 0; i < (int)Factors.size(); i++)
   {
      if(Factors[i] == 0)
         continue;

      int Meow = 1;
      for(int j = 0; j <= Factors[i]; j++)
         Meow = Meow * Primes[i];
      Sum = Sum * (Meow - 1) / (Primes[i] - 1);
   }

   if(Sum - N > N)
      return true;
   return false;
}

bool CheckSum(int N)
{
   if(N < 23)
      return false;

   for(int i = 12; i <= N / 2; i++)
      if(IsAbundant(i) == true && IsAbundant(N - i) == true)
         return true;

   return false;
}




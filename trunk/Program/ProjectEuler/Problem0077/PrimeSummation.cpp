#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main();
vector<int> PrimesSieve();

int main()
{
   vector<int> P = PrimesSieve();
   cout << P.size() << endl;

   int Ways[100] = {0};
   Ways[0] = 1;

   for(int i = 0; i < (int)P.size(); i++)
   {
      int TempWays[100] = {0};
      for(int j = 0; j < 100; j++)
         TempWays[j] = Ways[j];

      for(int j = 0; j < 100; j++)
      {
         if(Ways[j] > 0)
         {
            for(int k = 1; P[i] * k < 100; k++)
               TempWays[j+P[i]*k] = TempWays[j+P[i]*k] + Ways[j];
         }
      }
      
      for(int j = 0; j < 100; j++)
         Ways[j] = TempWays[j];
   }

   for(int i = 0; i < 100; i++)
      cout << i << " " << Ways[i] << endl;

   return 0;
}

vector<int> PrimesSieve()
{
   bool Primes[100];
   for(int i = 0; i < 100; i++)
      Primes[i] = true;

   Primes[0] = false;
   Primes[1] = false;

   for(int i = 2; i < 100; i++)
   {
      if(Primes[i] == false)
         continue;

      for(int j = 2; i * j < 100; j++)
         Primes[i*j] = false;
   }

   vector<int> Result;
   for(int i = 0; i < 100; i++)
      if(Primes[i] == true)
         Result.push_back(i);

   return Result;
}











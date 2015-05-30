#include <iostream>
#include <vector>
using namespace std;

int main();
long long CountResilience(long long N);

int main()
{
   cout << CountResilience(12) << "/" << 12 - 1 << endl;
   
   for(long long i = 10; i < 1000000000; i++)
   {
      if(i % 10000 == 0)
         cout << "Hello!  Now running N = " << i << endl;

      if((double)CountResilience(i) / (i - 1) < (double)15499 / 94744)
         cout << i << " " << CountResilience(i) << "/" << i - 1 << endl;
   }

   return 0;
}

long long CountResilience(long long N)
{
   if(N == 1)
      return 0;

   static vector<long long> Primes;
   if(Primes.size() == 0)
   {
      Primes.push_back(2);
      Primes.push_back(3);
      Primes.push_back(5);
      Primes.push_back(7);
      for(long long i = 11; i < 1000000; i = i + 2)
      {
         bool Good = true;
         for(long long j = 0; j < (long long)Primes.size() && Primes[j] * Primes[j] <= i; j++)
            if(i % Primes[j] == 0)
               Good = false;
         if(Good == true)
            Primes.push_back(i);
      }
   }

   if(find(Primes.begin(), Primes.end(), N) != Primes.end())
      return N - 2;

   long long Answer = N;
   long long Temp = N;
   for(long long i = 0; i < (long long)Primes.size() && Temp > 1; i++)
   {
      if(Primes[i] * Primes[i] > Temp)
         break;
      if(Temp % Primes[i] == 0)
      {
         Answer = Answer / Primes[i] * (Primes[i] - 1);
         while(Temp % Primes[i] == 0)
            Temp = Temp / Primes[i];
      }
   }

   if(Temp > 1)
      Answer = Answer / Temp * (Temp - 1);

   if(Answer == N)
      return N - 2;

   return Answer;
}






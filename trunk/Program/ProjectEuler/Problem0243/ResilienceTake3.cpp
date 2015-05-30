#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main();
long long CountResilience(long long N);

int main()
{
   cout << "Target: " << setprecision(20) << 15499.0 / 94744.0 << endl;

   long long N = 2;

   cout << N << " " << (double)CountResilience(N) / (N - 1) << endl;
   
   N = N * 3;
   cout << N << " " << (double)CountResilience(N) / (N - 1) << endl;
   
   N = N * 5;
   cout << N << " " << (double)CountResilience(N) / (N - 1) << endl;
   
   N = N * 7;
   cout << N << " " << (double)CountResilience(N) / (N - 1) << endl;
   
   N = N * 11;
   cout << N << " " << (double)CountResilience(N) / (N - 1) << endl;
   
   N = N * 13;
   cout << N << " " << (double)CountResilience(N) / (N - 1) << endl;
   
   N = N * 17;
   cout << N << " " << (double)CountResilience(N) / (N - 1) << endl;
   
   N = N * 19;
   cout << N << " " << (double)CountResilience(N) / (N - 1) << endl;
   
   N = N * 23;
   cout << N << " " << (double)CountResilience(N) / (N - 1) << endl;
   
   cout << N * 2 << " " << (double)CountResilience(N * 2) / (N * 2 - 1) << endl;
   cout << N * 3 << " " << (double)CountResilience(N * 3) / (N * 3 - 1) << endl;
   cout << N * 4 << " " << (double)CountResilience(N * 4) / (N * 4 - 1) << endl;
   cout << N * 5 << " " << (double)CountResilience(N * 5) / (N * 5 - 1) << endl;
   cout << N * 6 << " " << (double)CountResilience(N * 6) / (N * 6 - 1) << endl;
   
   N = N * 29;
   cout << N << " " << (double)CountResilience(N) / (N - 1) << endl;
   
   N = N * 31;
   cout << N << " " << (double)CountResilience(N) / (N - 1) << endl;
   
   N = N * 37;
   cout << N << " " << (double)CountResilience(N) / (N - 1) << endl;

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






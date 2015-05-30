#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
   vector<long long> Primes;
   Primes.push_back(2);
   Primes.push_back(3);
   Primes.push_back(5);
   Primes.push_back(7);
   for(long long i = 11; i < 50000000LL; i = i + 2)
   {
      if(i % 10000000 == 1)
         cout << i << endl;

      bool Good = true;
      for(int j = 0; j < (int)Primes.size() && Primes[j] * Primes[j] <= i && Good == true; j++)
         if(i % Primes[j] == 0)
            Good = false;

      if(Good == true)
         Primes.push_back(i);
   }

   cout << "Number of primes below 50000000 = " << Primes.size() << endl;

   int Count = 0;
   for(int i = (int)Primes.size() - 1; i >= 0; i--)
   {
      for(int j = 0; j < (int)Primes.size() && j <= i; j++)
      {
         if(Primes[i] * Primes[j] < 100000000LL)
            Count = Count + 1;
         else
            break;
      }
   }

   cout << Count << endl;

   return 0;
}





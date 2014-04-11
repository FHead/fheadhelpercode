#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<int> GetPrimes();
int main();

vector<int> GetPrimes()
{
   vector<int> Result;
   Result.push_back(2);
   Result.push_back(3);
   Result.push_back(5);
   Result.push_back(7);
   Result.push_back(11);

   for(int i = 13; i < 1000000; i = i + 2)
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
   vector<int> Primes = GetPrimes();

   map<int, int> PrimeMap;
   for(int i = 0; i < (int)Primes.size(); i++)
      PrimeMap.insert(pair<int, int>(Primes[i], 1));

   cout << Primes.size() << endl;

   int MaxProduct = 0;
   int MaxSize = 0;

   for(int iB = 0; Primes[iB] < 1000; iB++)
   {
      for(int iA = -999; iA <= 999; iA++)
      {
         int iC = 0;

         for(iC = 0; iC < 1000; iC++)
            if(PrimeMap.find(iC * iC + iA * iC + Primes[iB]) == PrimeMap.end())
               break;

         if(iC > 60)
            cout << iA << " " << Primes[iB] << " " << iC << endl;

         if(MaxSize < iC)
         {
            MaxSize = iC;
            MaxProduct = iA * Primes[iB];
         }
      }
   }

   cout << MaxSize << " " << MaxProduct << endl;

   return 0;
}





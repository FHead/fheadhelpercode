#include <map>
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

vector<int> ListPrimes();
map<int, int> Factorize(vector<int> &PrimeList, int Number);
int main();

vector<int> ListPrimes()
{
   vector<int> Result;
   Result.push_back(2);
   Result.push_back(3);
   Result.push_back(5);
   Result.push_back(7);

   for(int i = 11; i < 1000000; i = i + 2)
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

map<int, int> Factorize(vector<int> &PrimeList, long long Number)
{
   map<int, int> Result;

   for(int i = 0; i < (int)PrimeList.size() && Number > 1; i++)
   {
      if(Number % PrimeList[i] != 0)
         continue;

      int Count = 0;
      while(Number % PrimeList[i] == 0)
      {
         Number = Number / PrimeList[i];
         Count = Count + 1;
      }

      Result.insert(pair<int, int>(PrimeList[i], Count));
   }

   // if(Number > 1)
   //    cerr << "Warning!  Prime list not long enough!  Number = " << Number << endl;

   return Result;
}

int main()
{
   int Result = 0;
   long long Bound = 110000000;
   // long long Bound = 1000000;

   vector<int> Primes = ListPrimes();

   for(long long A = 2; A < 110000000 && A < Bound; A = A + 3)   // ensures modulus 27
   {
      if(A % 10000 == 0)
      {
         cout << A << " " << Result << endl;
      }

      long long APlus1 = (A + 1) / 3;
      long long OtherFactor = (8 * A - 1) / 3;

      map<int, int> Factors1 = Factorize(Primes, APlus1);
      map<int, int> Factors2 = Factorize(Primes, OtherFactor);
      for(map<int, int>::iterator iter = Factors2.begin(); iter != Factors2.end(); iter++)
      {
         Factors1[iter->first] += iter->second / 2;
         iter->second = iter->second % 2;
      }

      vector<long long> PossibleBs;
      PossibleBs.push_back(1);
      for(map<int, int>::iterator iter = Factors1.begin(); iter != Factors1.end(); iter++)
      {
         int Count = iter->second;
         if(Count == 0)
            continue;

         int CurrentSize = PossibleBs.size();
         for(int i = 0; i < CurrentSize; i++)
         {
            int Factor = 1;
            for(int j = 0; j < Count; j++)
            {
               Factor = Factor * iter->first;
               PossibleBs.push_back(PossibleBs[i] * Factor);
            }
         }
      }

      int Size = PossibleBs.size();
      for(int i = 0; i < Size; i++)
      {
         long long B = PossibleBs[i];
         long long C = OtherFactor * APlus1 / B * APlus1 / B;

         if(A + B + C <= Bound)
            Result = Result + 1;
      }
   }

   cout << Result << endl;

   return 0;
}









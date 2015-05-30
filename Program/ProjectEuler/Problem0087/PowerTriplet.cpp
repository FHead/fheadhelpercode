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

   vector<int> Total4;
   for(int i = 0; P[i] * P[i] * P[i] * P[i] < 50000000; i++)
      Total4.push_back(P[i] * P[i] * P[i] * P[i]);

   cout << Total4.size() << endl;

   vector<int> Total34;
   for(int i = 0; P[i] * P[i] * P[i] < 50000000; i++)
   {
      for(int j = 0; j < (int)Total4.size(); j++)
      {
         int Total = Total4[j] + P[i] * P[i] * P[i];
         if(Total < 50000000)
            Total34.push_back(Total);
      }
   
      sort(Total34.begin(), Total34.end());
      vector<int>::iterator iter = unique(Total34.begin(), Total34.end());
      Total34.erase(iter, Total34.end());
   }

   cout << Total34.size() << endl;

   vector<int> Total234;
   for(int i = 0; P[i] * P[i] < 50000000; i++)
   {
      for(int j = 0; j < (int)Total34.size(); j++)
      {
         int Total = Total34[j] + P[i] * P[i];
         if(Total < 50000000)
            Total234.push_back(Total);
      }

      sort(Total234.begin(), Total234.end());
      vector<int>::iterator iter = unique(Total234.begin(), Total234.end());
      Total234.erase(iter, Total234.end());
   }

   cout << Total234.size() << endl;

   for(int i = 0; i < (int)Total234.size(); i++)
      cout << i << " " << Total234[i] << endl;

   return 0;
}

vector<int> PrimesSieve()
{
   bool Primes[10000];
   for(int i = 0; i < 10000; i++)
      Primes[i] = true;

   Primes[0] = false;
   Primes[1] = false;

   for(int i = 2; i < 10000; i++)
   {
      if(Primes[i] == false)
         continue;

      for(int j = 2; i * j < 10000; j++)
         Primes[i*j] = false;
   }

   vector<int> Result;
   for(int i = 0; i < 10000; i++)
      if(Primes[i] == true)
         Result.push_back(i);

   return Result;
}











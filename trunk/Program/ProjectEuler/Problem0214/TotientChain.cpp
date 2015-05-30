#include <map>
#include <vector>
#include <iostream>
using namespace std;

int main();
int GetLength(int N, const vector<int> &Primes);
int GetNext(int N, const vector<int> &Primes);

int main()
{
   vector<int> Primes;
   Primes.push_back(2);
   Primes.push_back(3);
   Primes.push_back(5);
   Primes.push_back(7);
   for(int i = 11; i < 40000000; i = i + 2)
   {
      bool Good = true;
      for(int j = 0; j < (int)Primes.size() && Primes[j] * Primes[j] <= i && Good == true; j++)
         if(i % Primes[j] == 0)
            Good = false;
      if(Good == true)
         Primes.push_back(i);
   }

   cout << "Done generating primes" << endl;

   int Sum = 0;

   for(int i = 0; i < (int)Primes.size(); i++)
   {
      if(i % 10000 == 0)
         cout << "Now checking number " << Primes[i] << endl;

      int L = GetLength(Primes[i], Primes);
      // cout << Primes[i] << " " << L << endl;

      if(L == 25)
         cout << "L25 " << Primes[i] << endl;
      if(L == 4)
         cout << "L4  " << Primes[i] << endl;
   }

   return 0;
}

int GetLength(int N, const vector<int> &Primes)
{
   if(N == 1)
      return 1;

   static map<int, int> Lengths;

   if(Lengths.find(N) != Lengths.end())
      return Lengths[N];

   int Next = GetNext(N, Primes);

   int Answer = GetLength(Next, Primes) + 1;
   Lengths[N] = Answer;

   return Answer;
}

int GetNext(int N, const vector<int> &Primes)
{
   static map<int, int> Result;

   if(Result.find(N) != Result.end())
      return Result[N];

   int Temp = N;
   int Answer = N;

   for(int i = 0; i < (int)Primes.size(); i++)
   {
      if(Temp % Primes[i] == 0)
      {
         while(Temp % Primes[i] == 0)
            Temp = Temp / Primes[i];
         Answer = Answer / Primes[i] * (Primes[i] - 1);
      }

      if(Temp == 1)
         break;
   }

   // Result[N] = Answer;

   return Answer;
}



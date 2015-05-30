#include <iostream>
#include <algorithm>
using namespace std;

int main();
int Length(int *FactorialNext, int N);

int main()
{
   int Factorials[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
   int *FactorialNext = new int[20000001];

   for(int i = 0; i <= 20000000; i++)
   {
      FactorialNext[i] = 0;

      int Temp = i;
      while(Temp > 0)
      {
         FactorialNext[i] = FactorialNext[i] + Factorials[Temp%10];
         Temp = Temp / 10;
      }
   }

   cout << FactorialNext[69] << endl;

   cout << "L(69) = " << Length(FactorialNext, 69) << endl;
   cout << "L(78) = " << Length(FactorialNext, 78) << endl;
   cout << "L(540) = " << Length(FactorialNext, 540) << endl;
   cout << "L(145) = " << Length(FactorialNext, 145) << endl;

   int Count = 0;
   for(int i = 1; i < 1000000; i++)
   {
      if(Length(FactorialNext, i) == 60)
      {
         cout << "L(" << i << ") = 60" << endl;
         Count = Count + 1;
      }
   }

   cout << Count << endl;

   delete[] FactorialNext;

   return 0;
}

int Length(int *FactorialNext, int N)
{
   int Visited[100] = {0};
   for(int i = 0; i < 100; i++)
      Visited[i] = -1;

   int Count = 0;

   while(Count == 0 || find(Visited, Visited + Count, N) == Visited + Count)
   {
      Visited[Count] = N;
      Count = Count + 1;
      N = FactorialNext[N];
   }

   return Count;
}









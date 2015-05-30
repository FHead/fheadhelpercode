#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int main();
long long PuttingThingsTogether(int N, int M);
long long AllCombinations(int N, int M);
long long CountFourInALine(int N, int M);
long long GCD(long long a, long long b);
long long Cnm(int n, int m);

int main()
{
   cout << "Q(1, 1) = " << PuttingThingsTogether(1, 1) << endl;
   cout << "Q(1, 2) = " << PuttingThingsTogether(1, 2) << endl;
   cout << "Q(1, 3) = " << PuttingThingsTogether(1, 3) << endl;
   cout << "Q(1, 4) = " << PuttingThingsTogether(1, 4) << endl;
   cout << "Q(1, 5) = " << PuttingThingsTogether(1, 5) << endl;

   return 0;
}

long long PuttingThingsTogether(int N, int M)
{
   return AllCombinations(N, M) - CountFourInALine(N, M);
}

long long AllCombinations(int N, int M)
{
   long long Points = (N + 1) * (M + 1);

   return Cnm(Points, 4);
}

long long CountFourInALine(int N, int M)
{
   long long Result = 0;

   Result = Result + Cnm(N, 4) * M;
   Result = Result + Cmn(M, 4) * N;

   for(int x = 1; x <= N; x++)
   {
      for(int y = 1; y <= M; y++)
      {
         if(GCD(x, y) != 1)
            continue;

         if(y * N < x * M)   // shallower than diagonal - hit vertical wall first
         {
            bool WallIsInteger = ((N * y) % x == 0);

            if(WallIsInteger == true)
            {
               int Height = N * y / x;
               int C = N + 1 - Height;
               int P = N / x + 1;
               Result = Result + Cnm(P, 4) * C;

               for(int i = 2; P - i > 0; i = i + 2)
                  Result = Result + 2 * Cnm(P - i, 4);
            }
         }
         else   // hit horizontal wall first
         {
         }
         
         int FullCount = 0;

         int P = min(N / x + 1, M / y + 1);
         Result = Result + P * (P - 1) * (P - 2) * (P - 3) / 1 / 2 / 3 / 4 * ();
      }
   }

   return Result;
}

long long GCD(long long a, long long b)
{
   if(a < b)
      swap(a, b);

   if(a - b == 1)
      return 1;
   if(b == 0)
      return a;

   return GCD(b, a % b);
}

long long Cnm(int n, int m)
{
   if(m == 1)
      return n;
   if(m == 2)
      return n * (n - 1) / 2;
   if(m == 3)
      return n * (n - 1) * (n - 2) / 6;
   if(m == 4)
      return n * (n - 1) * (n - 2) * (n - 3) / 24;

   cerr << "m > 4 not implemented in Cnm due to lazy coders!" << endl;

   return -1;
}

 

#include <iostream>
#include <map>
#include <cmath>
using namespace std;

int main();
long long BestDenominator(int N, long long D);

int main()
{
   cout << "13, 20 = " << BestDenominator(13, 20) << endl;
   cout << "13, 30 = " << BestDenominator(13, 30) << endl;

   long long Sum = 0;

   for(int i = 2; i <= 100000; i++)
   {
      long long Best = BestDenominator(i, 1000000000000LL);
      cout << i << " " << Best << endl;
      Sum = Sum + Best;
   }

   cout << Sum << endl;

   return 0;
}

long long BestDenominator(int N, long long D)
{
   if((int)sqrt(N) * (int)sqrt(N) == N)   // we skip square cases
      return 0;

   int n = (int)sqrt(N);
   long double T = sqrt((long double)N) - n;

   pair<long long, long long> Left(0, 1);
   pair<long long, long long> Right(1, 1);
   bool Terminate = false;

   while(Terminate == false)
   {
      pair<long long, long long> Middle(Left.first + Right.first, Left.second + Right.second);

      if(N == 54045)
         cout << Left.second << " " << Right.second << " " << Middle.second << endl;
      
      if(Middle.second > D)
      {
         Terminate = true;
         break;
      }

      long long a = Middle.first;
      long long b = Middle.second;

      if((a + b * n) * (a + b * n) < N * b * b)
         Left = Middle;
      else
         Right = Middle;
   }

   long double DL = T - (long double)Left.first / (long double)Left.second;
   long double DR = (long double)Right.first / (long double)Right.second - T;

   if(DL < DR)
      return Left.second;
   else
      return Right.second;

   // shouldn't reach here!
   return 0;
}









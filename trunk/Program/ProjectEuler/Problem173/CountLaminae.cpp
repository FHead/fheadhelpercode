#include <iostream>
using namespace std;

long long FindCount(int Sum, double Bound);

int main()
{
   long long Total = 0;
   double N = 1000000;

   for(int i = 2; i <= N / 4 + 1; i++)
   {
      Total = Total + FindCount(i, N / 4 / i);
      Total = Total + FindCount(i, N / 4 / (i - 1));
   }

   cout << Total << endl;

   return 0;
}

long long FindCount(int Sum, double Bound)
{
   int IntBound = (int)Bound;

   if(IntBound % 2 == 1 && Sum % 2 == 1)
      return min((IntBound + 1) / 2, (Sum - 1) / 2);
   else if(IntBound % 2 == 1 && Sum % 2 == 0)
      return min((IntBound - 1) / 2, Sum / 2 - 1);
   else if(IntBound % 2 == 0 && Sum % 2 == 1)
      return min(IntBound / 2, (Sum - 1) / 2);
   else if(IntBound % 2 == 0 && Sum % 2 == 0)
      return min(IntBound / 2, Sum / 2 - 1);

   return 0;
}






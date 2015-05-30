#include <iostream>
using namespace std;

int main()
{
   int Array[1000][1000] = {{0}};

   long long t = 0;
   for(int i = 0; i < 1000; i++)
   {
      for(int j = 0; j <= i; j++)
      {
         t = (615949 * t + 797807) % 1048576;
         Array[i][j] = t - 524288;
      }
   }

   int RowCumulative[1001][1001] = {{0}};
   for(int i = 1; i < 1001; i++)
      for(int j = 1; j <= i; j++)
         RowCumulative[i][j] = RowCumulative[i][j-1] + Array[i-1][j-1];

   int BestSoFar = Array[0][0];
   for(int i = 1; i < 1001; i++)
   {
      for(int j = 1; j <= i; j++)
      {
         int Sum = Array[i-1][j-1];
         if(Sum < BestSoFar)
            BestSoFar = Sum;

         for(int k = 1; i + k < 1001; k++)
         {
            Sum = Sum + RowCumulative[i+k][j+k] - RowCumulative[i+k][j-1];
            if(Sum < BestSoFar)
               BestSoFar = Sum;
         }
      }
   }

   cout << BestSoFar << endl;

   return 0;
}





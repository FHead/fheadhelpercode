#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

long long Counts(int X, int Y);
int main();

long long Counts(int X, int Y)
{
   if(X < Y)
      swap(X, Y);

   if(X == 1)
      return Y + 1;
   if(Y == 1)
      return X + 1;
   
   static long long Cache[50][50] = {{0}};

   if(Cache[X][Y] != 0)
      return Cache[X][Y];

   Cache[X][Y] = Counts(X - 1, Y) + Counts(X, Y - 1);

   return Cache[X][Y];
}

int main()
{
   cout << Counts(20, 20) << endl;
   
   return 0;
}



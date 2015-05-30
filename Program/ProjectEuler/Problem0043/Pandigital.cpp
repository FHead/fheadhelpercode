#include <algorithm>
#include <iostream>
using namespace std;

int main()
{
   int X[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   do
   {
      if((X[1] * 100 + X[2] * 10 + X[3]) % 2 != 0)   continue;
      if((X[2] * 100 + X[3] * 10 + X[4]) % 3 != 0)   continue;
      if((X[3] * 100 + X[4] * 10 + X[5]) % 5 != 0)   continue;
      if((X[4] * 100 + X[5] * 10 + X[6]) % 7 != 0)   continue;
      if((X[5] * 100 + X[6] * 10 + X[7]) % 11 != 0)   continue;
      if((X[6] * 100 + X[7] * 10 + X[8]) % 13 != 0)   continue;
      if((X[7] * 100 + X[8] * 10 + X[9]) % 17 != 0)   continue;

      for(int i = 0; i < 10; i++)
         cout << X[i];
      cout << endl;
   } while(next_permutation(X, X + 10));

   return 0;
}






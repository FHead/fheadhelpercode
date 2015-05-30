#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
   vector<int> P;
   P.push_back(2);
   P.push_back(3);
   P.push_back(5);
   P.push_back(7);
   for(int i = 11; i < 10000; i = i + 2)
   {
      bool Good = true;
      for(int j = 0; j < (int)P.size() && P[j] * P[j] <= i && Good == true; j++)
         if(i % P[j] == 0)
            Good = false;

      if(Good == true)
         P.push_back(i);
   }

   int X[] = {1, 2, 3, 4, 5, 6, 7};
   do
   {
      int N = X[0] * 1000000 + X[1] * 100000 + X[2] * 10000 + X[3] * 1000 + X[4] * 100 + X[5] * 10 + X[6];

      bool Good = true;
      for(int i = 0; i < (int)P.size() && P[i] * P[i] <= N && Good == true; i++)
         if(N % P[i] == 0)
            Good = false;

      if(Good == true)
         cout << N << endl;
   } while(next_permutation(X, X + 7));

   return 0;
}







#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
   int X[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   for(int i = 0; i < 999999; i++)
      next_permutation(X, X + 10);

   for(int i = 0; i < 10; i++)
      cout << X[i];
   cout << endl;

   return 0;
}





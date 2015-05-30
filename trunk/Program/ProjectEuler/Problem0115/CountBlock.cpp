#include <iostream>
using namespace std;

int main()
{
   int m = 3;

   long long Count[100] = {0};
   for(int i = 0; i < m; i++)
      Count[i] = 0;
   Count[1] = 1;

   for(int i = 2; i < 100 && Count[i-1] < 5000000; i++)
   {
      Count[i] = 0;

      for(int j = m + 1; i - j > 1; j++)
         Count[i] = Count[i] + Count[i-j] * (i - (m + 1) + 1);
      if(i >= m + 1)
         Count[i] = Count[i] + (i - (m + 1) + 1);
   }

   for(int i = 0; i < 100; i++)
      cout << i << " " << Count[i] << endl;

   return 0;
}










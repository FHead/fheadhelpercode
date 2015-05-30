#include <iostream>
using namespace std;

int main()
{
   long long Result = 0;

   for(int i = 1; i < 1000; i++)
   {
      long long SubResult = 1;
      for(int j = 0; j < i; j++)
         SubResult = (SubResult * i) % 10000000000;
      Result = Result + SubResult;
      Result = Result % 10000000000;
   }

   cout << Result << endl;

   return 0;
}











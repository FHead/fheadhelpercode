#include <iostream>
using namespace std;

int main()
{
   long long Digit = 1;
   for(int i = 0; i < 7830457; i++)
      Digit = (Digit * 2) % 10000000000LL;

   Digit = (Digit * 28433) % 10000000000LL;

   Digit = Digit + 1;

   cout << Digit << endl;

   return 0;
}




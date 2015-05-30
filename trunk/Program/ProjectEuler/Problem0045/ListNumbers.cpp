#include <iostream>
using namespace std;

int main();
long long T(long long i);
long long P(long long i);
long long H(long long i);

int main()
{
   long long iT = 286, iP = 166, iH = 143;

   while(true)
   {
      long long vT = T(iT), vP = P(iP), vH = H(iH);

      // cout << "Testing " << iT << " " << iP << " " << iH << " " << vT << " " << vP << " " << vH << endl;

      if(vT == vP && vP == vH)
      {
         cout << vT << endl;
         break;
      }

      if(vT <= vP && vT <= vH)
         iT = iT + 1;
      else if(vP <= vH)
         iP = iP + 1;
      else
         iH = iH + 1;
   }

   return 0;
}

long long T(long long i)
{
   return i * (i + 1) / 2;
}

long long P(long long i)
{
   return i * (3 * i - 1) / 2;
}

long long H(long long i)
{
   return i * (2 * i - 1);
}




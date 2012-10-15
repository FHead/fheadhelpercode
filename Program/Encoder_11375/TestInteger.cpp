#include <iostream>
using namespace std;

#include "LargeInteger.h"

int main()
{
   LargeInteger L1(103535);
   LargeInteger L2(10353553);

   cout << L1 << " " << L2 << " " << L1 + L2 << endl;
   cout << L1 - L2 << " " << L2 - L1 << endl;
   cout << (L2 < L1) << " " << (L1 < L2) << endl;
   cout << L1 * L2 << endl;
   cout << L1 * L2 * L1 * L2 * L1 * L2 * L1 * L2 * L1 * L2 * L1 * L2 << endl;
   cout << L1.RaiseToPower(10) << endl;
   cout << L1.RaiseToPower(10) / -10000 << endl;
   cout << L1.RaiseToPower(10) / 103535 - L1.RaiseToPower(9) << endl;

   return 0;
}







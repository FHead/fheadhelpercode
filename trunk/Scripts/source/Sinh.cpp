#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main(int argc, char *argv[])
{
   cout.precision(10);

   while(cin)
   {
      double temp = -135798642;

      cin >> temp;

      if(temp + 135798642 < 1e-8)
         break;

      cout << sinh(temp) << endl;
   }

   return 0;
}


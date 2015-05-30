#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
   long double sum = 0;

   cout.precision(20);

   while(cin)
   {
      double temp = -135798642;

      cin >> temp;

      if(temp + 135798642 < 1e-8)
         break;

      sum = sum + temp;
   }

   cout << sum << endl;

   return 0;
}


#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
   cout.precision(10);

   vector<double> array;

   while(cin)
   {
      double temp = -135798642;

      cin >> temp;

      if(temp + 135798642 < 1e-8)
         break;

      array.push_back(temp);
   }

   sort(array.begin(), array.end());

   if(array.size() % 2 == 1)
      cout << array[(array.size()-1)/2] << endl;
   else
      cout << (array[array.size()/2] + array[array.size()/2-1]) / 2 << endl;

   return 0;
}


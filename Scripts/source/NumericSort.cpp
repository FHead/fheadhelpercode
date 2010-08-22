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

   for(int i = 0; i < (int)array.size(); i++)
      cout << array[i] << endl;

   return 0;
}


#include <iostream>
#include <vector>
using namespace std;

int main()
{
   vector<int> All;
   All.push_back(2);
   All.push_back(3);

   int Bound = 12000;

   bool Good = false;
   while(Good == false)
   {
      Good = true;
      for(int i = 0; i < (int)All.size() - 1; i++)
      {
         if(All[i] + All[i+1] <= Bound)
         {
            int Sum = All[i] + All[i+1];
            All.insert(All.begin() + i + 1, Sum);
            Good = false;
         }
      }
   }

   cout << All.size() - 2 << endl;

   return 0;
}



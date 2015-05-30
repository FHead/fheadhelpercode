#include <iostream>
#include <vector>
using namespace std;

vector<int> IncludeNewCoins(vector<int> UpToNow, int Value);
int main();

vector<int> IncludeNewCoins(vector<int> UpToNow, int Value)
{
   vector<int> Result(UpToNow.size());

   for(int i = 0; i < UpToNow.size(); i++)
   {
      for(int j = i; j >= 0; j = j - Value)
         Result[i] = Result[i] + UpToNow[j];
   }

   return Result;
}

int main()
{
   vector<int> Counts(300);
   for(int i = 0; i < Counts.size(); i++)
      Counts[i] = 1;

   Counts = IncludeNewCoins(Counts, 2);
   Counts = IncludeNewCoins(Counts, 5);
   Counts = IncludeNewCoins(Counts, 10);
   Counts = IncludeNewCoins(Counts, 20);
   Counts = IncludeNewCoins(Counts, 50);
   Counts = IncludeNewCoins(Counts, 100);
   Counts = IncludeNewCoins(Counts, 200);

   cout << Counts[200] << endl;
}






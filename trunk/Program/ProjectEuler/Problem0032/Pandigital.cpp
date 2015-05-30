#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main();
vector<int> ListValidResults(vector<int> &Digits);
int ToNumber(vector<int>::iterator begin, vector<int>::iterator end);

int main()
{
   vector<int> Digits;
   Digits.push_back(1);
   Digits.push_back(2);
   Digits.push_back(3);
   Digits.push_back(4);
   Digits.push_back(5);
   Digits.push_back(6);
   Digits.push_back(7);
   Digits.push_back(8);
   Digits.push_back(9);

   vector<int> Results;

   do
   {
      vector<int> Valid = ListValidResults(Digits);
      if(Valid.size() > 0)
         cout << Valid.size() << " " << Valid[0] << endl;

      Results.insert(Results.end(), Valid.begin(), Valid.end());
   } while(next_permutation(Digits.begin(), Digits.end()) == true);

   sort(Results.begin(), Results.end());
   vector<int>::iterator iter = unique(Results.begin(), Results.end());
   Results.erase(iter, Results.end());

   int Total = 0;
   for(int i = 0; i < (int)Results.size(); i++)
      Total = Total + Results[i];
   cout << Total << endl;

   return 0;
}

vector<int> ListValidResults(vector<int> &Digits)
{
   vector<int> Result;

   for(int i = 1; i < (int)Digits.size() - 1; i++)
   {
      for(int j = i + 1; j < (int)Digits.size() - 1; j++)
      {
         int N1 = ToNumber(Digits.begin(), Digits.begin() + i);
         int N2 = ToNumber(Digits.begin() + i, Digits.begin() + j);
         int N3 = ToNumber(Digits.begin() + j, Digits.end());

         if(N1 * N2 == N3)
            Result.push_back(N3);
      }
   }

   return Result;
}

int ToNumber(vector<int>::iterator begin, vector<int>::iterator end)
{
   int Result = 0;
   for(vector<int>::iterator iter = begin; iter != end; iter++)
      Result = Result * 10 + *iter;
   return Result;
}




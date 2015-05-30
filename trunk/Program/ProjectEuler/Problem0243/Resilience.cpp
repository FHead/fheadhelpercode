#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main();
void CountFraction(pair<int, int> &Left, pair<int, int> &Right, int Threshold, vector<int> &Counter);

int main()
{
   int Threshold = 10000;
   vector<int> Counter;
   Counter.resize(Threshold);

   for(int i = Threshold; i > 2; i--)
   {
      pair<int, int> Left(1, i);
      pair<int, int> Right(1, i - 1);
      CountFraction(Left, Right, Threshold, Counter);
   }

   for(int i = Threshold; i > 2; i--)
   {
      pair<int, int> Left(i - 1, i);
      pair<int, int> Right(i - 2, i - 1);
      CountFraction(Left, Right, Threshold, Counter);
   }

   Counter[2-1] = 1;
   for(int i = 2; i < (int)Counter.size(); i++)
      Counter[i] = Counter[i] + 2;

   for(int i = 2; i < (int)Counter.size(); i++)
   {
      // if((long long)Counter[i] * 10 < 4 * i)
      //    cout << i + 1 << " " << Counter[i] << endl;
      if((long long)Counter[i] * 94744LL < 15499LL * i)
         cout << i + 1 << " " << Counter[i] << endl;
   }

   return 0;
}

void CountFraction(pair<int, int> &Left, pair<int, int> &Right, int Threshold, vector<int> &Counter)
{
   if(Left.second + Right.second > Threshold)
      return;
   if(Left.second + Right.second - 1 >= (int)Counter.size())
      return;

   Counter[Left.second+Right.second-1] = Counter[Left.second+Right.second-1] + 1;
   
   pair<int, int> Center(Left.first + Right.first, Left.second + Right.second);

   CountFraction(Left, Center, Threshold, Counter);
   CountFraction(Center, Right, Threshold, Counter);
}


 

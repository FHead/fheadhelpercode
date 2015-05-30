#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main();
int FindAnswer(int L, int R, int Bound);

int main()
{
   cout << FindAnswer(3, 2, 12000) << endl;

   return 0;
}

int FindAnswer(int L, int R, int Bound)
{
   if(L + R > Bound)
      return 0;
   if(L + R == Bound)
      return 1;

   if(L > R)
      swap(L, R);

   static map<pair<int, int>, int> Cache;

   if(Cache.find(pair<int,int>(L, R)) != Cache.end())
      return Cache[pair<int,int>(L,R)];

   int Left = FindAnswer(L, L + R, Bound);
   int Right = FindAnswer(L + R, R, Bound);
   Cache[pair<int,int>(L,R)] = Left + Right + 1;

   return Left + Right + 1;
}


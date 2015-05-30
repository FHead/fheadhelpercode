#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main();
__int128 CountNumber(__int128 N, int UpToIndex);
ostream &operator <<(ostream &out, __int128 x);

int main()
{
   cout << CountNumber(10, 3) << endl;

   __int128 x = 1;
   for(int i = 0; i < 25; i++)
      x = x * 10;

   // cout << x << endl;
   cout << CountNumber(x, 90) << endl;

   return 0;
}

__int128 CountNumber(__int128 N, int UpToIndex)
{
   static __int128 Powers[100] = {0};
   if(Powers[0] == 0)
   {
      Powers[0] = 1;
      for(int i = 1; i < 100; i++)
         Powers[i] = Powers[i-1] * 2;
   }

   static map<pair<__int128, int>, __int128> Cache;

   if(Cache.find(pair<__int128, int>(N, UpToIndex)) != Cache.end())
      return Cache[pair<__int128, int>(N, UpToIndex)];

   // cout << N << " " << UpToIndex << " " << Powers[UpToIndex] << endl;

   if(N < 0)
      return 0;
   if(N == 0)
      return 1;
   if(N > (Powers[UpToIndex] * 2 - 1) * 2)
      return 0;
   if(N == (Powers[UpToIndex] * 2 - 1) * 2)
      return 1;
   if(UpToIndex == 0)
   {
      if(N == 1)
         return 1;
      if(N == 2)
         return 1;
      return 0;
   }

   __int128 Answer = CountNumber(N, UpToIndex - 1);
   Answer = Answer + CountNumber(N - Powers[UpToIndex], UpToIndex - 1);
   Answer = Answer + CountNumber(N - 2 * Powers[UpToIndex], UpToIndex - 1);

   Cache[pair<__int128, int>(N, UpToIndex)] = Answer;

   // cout << N << " " << UpToIndex << " " << Powers[UpToIndex] << " " << Answer << endl;

   return Answer;
}

ostream &operator <<(ostream &out, __int128 x)
{
   if(x == 0)
   {
      out << 0;
      return out;
   }

   vector<int> Digits;
   while(x > 0)
   {
      Digits.push_back(x % 10);
      x = x / 10;
   }

   for(int i = (int)Digits.size() - 1; i >= 0; i--)
      out << Digits[i];

   return out;
}





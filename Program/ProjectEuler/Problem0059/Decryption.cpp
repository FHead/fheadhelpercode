#include <iostream>
#include <vector>
using namespace std;

int main()
{
   vector<int> Cipher;
   while(cin)
   {
      int X = -1;
      cin >> X;
      if(X >= 0)
         Cipher.push_back(X);
   }

   for(int i1 = (int)'a'; i1 <= (int)'z'; i1++)
   {
      for(int i2 = (int)'a'; i2 <= (int)'z'; i2++)
      {
         for(int i3 = (int)'a'; i3 <= (int)'z'; i3++)
         {
            int Total = 0;

            for(int j = 0; j < (int)Cipher.size(); j++)
            {
               int K;
               if(j % 3 == 0)   K = i1;
               if(j % 3 == 1)   K = i2;
               if(j % 3 == 2)   K = i3;

               cout << (char)(Cipher[j] ^ K);

               Total = Total + Cipher[j] ^ K;
            }
            cout << " ---------- " << Total << endl;
         }
      }
   }

   return 0;
}





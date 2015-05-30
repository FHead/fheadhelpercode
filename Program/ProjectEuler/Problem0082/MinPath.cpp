#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
   int S[80][80] = {{0}};
   
   ifstream in("Matrix.txt");
   for(int y = 0; y < 80; y++)
      for(int x = 0; x < 80; x++)
         in >> S[x][y];
   in.close();

   int B[80][80] = {{0}};

   for(int y = 1; y < 80; y++)
      B[0][y] = S[0][y];

   for(int x = 1; x < 80; x++)
   {
      for(int y = 0; y < 80; y++)
      {
         int Best = B[x-1][y] + S[x][y];

         for(int py = 0; py < 80; py++)
         {
            int y1 = py;
            int y2 = y;

            if(y1 > y2)
               swap(y1, y2);

            int V = B[x-1][py];
            for(int iy = y1; iy <= y2; iy++)
               V = V + S[x][iy];

            if(V < Best)
               Best = V;
         }

         B[x][y] = Best;
      }
   }

   int Result = B[79][0];
   for(int y = 1; y < 80; y++)
      if(B[79][y] < Result)
         Result = B[79][y];

   cout << Result << endl;

   return 0;
}






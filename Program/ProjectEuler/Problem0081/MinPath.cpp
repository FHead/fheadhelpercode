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
   B[0][0] = S[0][0];

   for(int x = 1; x < 80; x++)
      B[x][0] = B[x-1][0] + S[x][0];
   for(int y = 1; y < 80; y++)
      B[0][y] = B[0][y-1] + S[0][y];

   for(int y = 1; y < 80; y++)
      for(int x = 1; x < 80; x++)
         B[x][y] = min(B[x-1][y], B[x][y-1]) + S[x][y];

   cout << B[79][79] << endl;

   return 0;
}






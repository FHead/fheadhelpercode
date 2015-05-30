#include <iostream>
using namespace std;

int main()
{
   int W[40][40] = {{0}};
   for(int i = 0; i < 40; i++)
      for(int j = 0; j < 40; j++)
         cin >> W[i][j];

   int MinI = -1, MinJ = -1;
   for(int i = 0; i < 40; i++)
   {
      for(int j = 0; j < 40; j++)
      {
         if(W[i][j] == 0)
            continue;
         if(MinI == -1 || MinJ == -1)
            MinI = i, MinJ = j;
         if(W[i][j] < W[MinI][MinJ])
            MinI = i, MinJ = j;
      }
   }

   bool Group[40] = {false};
   for(int i = 0; i < 40; i++)
      Group[i] = false;
   Group[MinI] = true;
   Group[MinJ] = true;

   double Total = W[MinI][MinJ];
   cout << W[MinI][MinJ] << endl;

   for(int k = 2; k < 40; k++)
   {
      MinI = -1, MinJ = -1;

      for(int i = 0; i < 40; i++)
      {
         for(int j = 0; j < 40; j++)
         {
            if(Group[i] == true && Group[j] == true)
               continue;
            if(Group[i] == false && Group[j] == false)
               continue;

            if(W[i][j] == 0)
               continue;
            if(MinI == -1 || MinJ == -1)
               MinI = i, MinJ = j;
            if(W[i][j] < W[MinI][MinJ])
               MinI = i, MinJ = j;
         }
      }
      
      cout << MinI << " " << MinJ << endl;

      cout << Group[MinI] << " " << Group[MinJ] << " " << W[MinI][MinJ] << endl;

      Total = Total + W[MinI][MinJ];
      Group[MinI] = true;
      Group[MinJ] = true;
   }

   cout << "Group";
   for(int i = 0; i < 40; i++)
      cout << " " << (Group[i] ? "1" : "0");
   cout << endl;

   cout << Total << endl;

   return 0;
}





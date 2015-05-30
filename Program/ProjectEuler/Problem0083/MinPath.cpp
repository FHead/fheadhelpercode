#include <algorithm>
#include <iostream>
#include <fstream>
#include <deque>
#include <map>
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
   deque<pair<int, int> > Queue;
   Queue.push_back(pair<int, int>(0, 1));
   Queue.push_back(pair<int, int>(1, 0));
   while(Queue.size() > 0)
   {
      int BestIndex = -1;
      int OverallBest = -1;

      for(int i = 0; i < Queue.size(); i++)
      {
         int XL = Queue[i].first - 1;
         int X = Queue[i].first;
         int XR = Queue[i].first + 1;
         int YL = Queue[i].second - 1;
         int Y = Queue[i].second;
         int YR = Queue[i].second + 1;

         int Best = 9999999;
         if(XL >= 0 && B[XL][Y] > 0 && B[XL][Y] < Best)   Best = B[XL][Y];
         if(YL >= 0 && B[X][YL] > 0 && B[X][YL] < Best)   Best = B[X][YL];
         if(XR < 80 && B[XR][Y] > 0 && B[XR][Y] < Best)   Best = B[XR][Y];
         if(YR < 80 && B[X][YR] > 0 && B[X][YR] < Best)   Best = B[X][YR];

         Best = Best + S[X][Y];

         if(OverallBest < 0 || Best < OverallBest)
         {
            BestIndex = i;
            OverallBest = Best;
         }
      }

      int X = Queue[BestIndex].first;
      int Y = Queue[BestIndex].second;
      B[X][Y] = OverallBest;
         
      int XL = Queue[BestIndex].first - 1;
      int XR = Queue[BestIndex].first + 1;
      int YL = Queue[BestIndex].second - 1;
      int YR = Queue[BestIndex].second + 1;

      if(XL >= 0 && B[XL][Y] <= 0)   Queue.push_back(pair<int, int>(XL, Y));
      if(YL >= 0 && B[X][YL] <= 0)   Queue.push_back(pair<int, int>(X, YL));
      if(XR >= 0 && B[XR][Y] <= 0)   Queue.push_back(pair<int, int>(XR, Y));
      if(YR >= 0 && B[X][YR] <= 0)   Queue.push_back(pair<int, int>(X, YR));

      Queue.erase(Queue.begin() + BestIndex);
      
      for(int i = 0; i < (int)Queue.size(); i++)
      {
         int X = Queue[i].first;
         int Y = Queue[i].second;
         if(B[X][Y] > 0)
         {
            Queue.erase(Queue.begin() + i);
            i = i - 1;
         }
      }
   }

   cout << B[79][79] << endl;

   return 0;
}






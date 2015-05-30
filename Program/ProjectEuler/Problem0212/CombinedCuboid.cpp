#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct Cube;
int main();
vector<int> GetSequence();
vector<Cube> GetCoordinates(vector<int> Sequence);

struct Cube
{
   int X;
   int Y;
   int Z;
   int DX;
   int DY;
   int DZ;
};

int main()
{
   int MaxN = 50000;

   vector<int> Sequence = GetSequence();
   vector<Cube> Cubes = GetCoordinates(Sequence);

   vector<int> ZBreakPoints;

   for(int i = 0; i < MaxN; i++)
   {
      ZBreakPoints.push_back(Cubes[i].Z);
      ZBreakPoints.push_back(Cubes[i].Z + Cubes[i].DZ);
   }
   sort(ZBreakPoints.begin(), ZBreakPoints.end());
   vector<int>::iterator iter = unique(ZBreakPoints.begin(), ZBreakPoints.end());
   ZBreakPoints.erase(iter, ZBreakPoints.end());

   cout << "Number of breakpoints in Z direction: " << ZBreakPoints.size() << endl;

   long long Answer = 0;

   for(int iZ = 0; iZ < (int)ZBreakPoints.size() - 1; iZ++)
   {
      if(iZ % 500 == 0)
         cout << iZ << "/" << ZBreakPoints.size() << endl;

      double CenterZ = (ZBreakPoints[iZ] + ZBreakPoints[iZ+1]) * 0.5;
      int ZWidth = ZBreakPoints[iZ+1] - ZBreakPoints[iZ];

      vector<Cube *> RelevantCubes;

      for(int i = 0; i < MaxN; i++)
         if(Cubes[i].Z <= CenterZ && Cubes[i].Z + Cubes[i].DZ >= CenterZ)
            RelevantCubes.push_back(&Cubes[i]);

      if(RelevantCubes.size() == 0)
         continue;
      if(RelevantCubes.size() == 1)
      {
         Answer = Answer + RelevantCubes[0]->DX * RelevantCubes[0]->DY * ZWidth;
         continue;
      }
      
      // cout << "iZ = " << iZ << ", relevant cubes: " << RelevantCubes.size() << endl;

      vector<int> YBreakPoints;

      for(int i = 0; i < (int)RelevantCubes.size(); i++)
      {
         YBreakPoints.push_back(RelevantCubes[i]->Y);
         YBreakPoints.push_back(RelevantCubes[i]->Y + RelevantCubes[i]->DY);
      }
      sort(YBreakPoints.begin(), YBreakPoints.end());
      vector<int>::iterator iter = unique(YBreakPoints.begin(), YBreakPoints.end());
      YBreakPoints.erase(iter, YBreakPoints.end());

      // cout << "   Y breakpoints: " << YBreakPoints.size() << endl;

      for(int iY = 0; iY < (int)YBreakPoints.size() - 1; iY++)
      {
         double CenterY = (YBreakPoints[iY] + YBreakPoints[iY+1]) * 0.5;
         int YWidth = YBreakPoints[iY+1] - YBreakPoints[iY];

         vector<Cube *> Segments;

         for(int i = 0; i < (int)RelevantCubes.size(); i++)
            if(RelevantCubes[i]->Y <= CenterY && RelevantCubes[i]->Y + RelevantCubes[i]->DY >= CenterY)
               Segments.push_back(RelevantCubes[i]);

         // cout << "   iY: " << iY << ", number of segments: " << Segments.size() << endl;

         // cout << "      CenterY: " << CenterY << endl;
         // for(int i = 0; i < (int)RelevantCubes.size(); i++)
         //    cout << "         Y range " << RelevantCubes[i]->Y << ", " << RelevantCubes[i]->Y + RelevantCubes[i]->DY << endl;

         if(Segments.size() == 0)
            continue;
         if(Segments.size() == 1)
         {
            Answer = Answer + Segments[0]->DX * YWidth * ZWidth;
            continue;
         }

         vector<pair<int, int> > Occupied;
         for(int i = 0; i < (int)Segments.size(); i++)
            Occupied.push_back(pair<int, int>(Segments[i]->X, Segments[i]->X + Segments[i]->DX));
         sort(Occupied.begin(), Occupied.end());

         for(int i = 0; i < (int)Occupied.size() - 1; i++)
         {
            if(Occupied[i].second >= Occupied[i+1].first)
            {
               Occupied[i].second = max(Occupied[i].second, Occupied[i+1].second);
               Occupied.erase(Occupied.begin() + i + 1);
               i = i - 1;
            }
         }

         int XLength = 0;
         for(int i = 0; i < (int)Occupied.size(); i++)
            XLength = XLength + Occupied[i].second - Occupied[i].first;

         Answer = Answer + XLength * YWidth * ZWidth;
      }
   }

   cout << "Total volume: " << Answer << endl;

   return 0;
}

vector<int> GetSequence()
{
   vector<int> Result;

   for(int i = 0; i < 55; i++)
      Result.push_back((100003LL - 200003LL * (i + 1) + 300007LL * (i + 1) * (i + 1) * (i + 1)) % 1000000);

   for(int i = 55; i < 300000; i++)
      Result.push_back((Result[i-24] + Result[i-55]) % 1000000);

   return Result;
}

vector<Cube> GetCoordinates(vector<int> Sequence)
{
   vector<Cube> Result;

   for(int i = 0; i < 50000; i++)
   {
      // x0, y0, z0, dx, dy, dz
      Cube NewCube;
      
      NewCube.X = Sequence[6*i+0] % 10000;
      NewCube.Y = Sequence[6*i+1] % 10000;
      NewCube.Z = Sequence[6*i+2] % 10000;
      NewCube.DX = 1 + (Sequence[6*i+3] % 399);
      NewCube.DY = 1 + (Sequence[6*i+4] % 399);
      NewCube.DZ = 1 + (Sequence[6*i+5] % 399);

      Result.push_back(NewCube);
   }

   return Result;
}


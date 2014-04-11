#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int main();
long long NothingMiddle(int N, int M);
long long OneMiddle(int N, int M);
long long TwoMiddle(int N, int M);
long long PutThingsTogether(int N, int M);
long long TwoTimesTriangleArea(int x1, int y1, int x2, int y2, int x3, int y3);
long long LatticePointsOnSegment(int x1, int y1, int x2, int y2);
long long LatticePointsOnRay(int x1, int y1, int x2, int y2, int wall, bool WallIsX);
long long LatticePointsInArea(int x1, int y1, int x2, int y2, int x3, int y3);
long long LatticePointsInAreaPrime(int xL, int xR, int y1, int y2, double y3);
long long GCD(int a, int b);

int main()
{
   cout << "Q(1, 1)  = " << PutThingsTogether(1, 1) << endl;
   cout << "Q(1, 2)  = " << PutThingsTogether(1, 2) << endl;
   cout << "Q(1, 3)  = " << PutThingsTogether(1, 3) << endl;
   cout << "Q(1, 4)  = " << PutThingsTogether(1, 4) << endl;
   cout << "Q(1, 5)  = " << PutThingsTogether(1, 5) << endl;
   cout << "Q(2, 2)  = " << PutThingsTogether(2, 2) << endl;
   cout << "Q(2, 3)  = " << PutThingsTogether(2, 3) << endl;
   cout << "Q(2, 4)  = " << PutThingsTogether(2, 4) << endl;
   cout << "Q(2, 5)  = " << PutThingsTogether(2, 5) << endl;
   cout << "Q(3, 7)  = " << PutThingsTogether(3, 7) << endl;
   cout << "Q(12, 3) = " << PutThingsTogether(12, 3) << endl;
   cout << "Q(123, 45) = " << PutThingsTogether(123, 45) << endl;
   cout << "Q(12345, 6789) = " << PutThingsTogether(12345, 6789) << endl;

   cout << "TwoMiddle(2, 3) = " << TwoMiddle(2, 3) << endl;
   cout << "TwoMiddle(2, 4) = " << TwoMiddle(2, 4) << endl;
   cout << "TwoMiddle(2, 5) = " << TwoMiddle(2, 5) << endl;

   return 0;
}

long long NothingMiddle(int N, int M)
{
   long long Result = 0;

   Result = Result + 1;                                       // 4 corners
   Result = Result + 4 * ((N - 1) + (M - 1));                 // 3 corners
   Result = Result + 8 * (N - 1) * (M - 1);                   // consecutive corners + 2 sides
   Result = Result + 2 * (N - 1) * (N - 2) / 2;               // consecutive corners + two on opposite
   Result = Result + 2 * (M - 1) * (M - 2) / 2;               // same as above
   Result = Result + 2 * (4 * (N - 1) * (M - 1) + (N - 1) * (N - 1) + (M - 1) * (M - 1));
                                                              // diagonal corners
   Result = Result + ((N - 1) * (N - 1) * (M - 1)
      + (M - 1) * (M - 1) * (N - 1)) * 4;                     // one corner!
   Result = Result + (N - 1) * (N - 1) * (M - 1) * (M - 1);   // no corners

   return Result;
}

long long OneMiddle(int N, int M)
{
   // Shouldn't be needed, but could speed up things a bit
   if(N == 1 || M == 1)   // there's no inside point
      return 0;

   // Result
   long long Result = 0;

   // Temporary book-keepers
   long long PointsInside = 0;
   long long PointsToExclude = 0;
   long long TotalPoints = (N - 1) * (M - 1);

   // Case 1: Three corners
   PointsInside = LatticePointsInArea(0, 0, N, 0, 0, M);
   PointsToExclude = LatticePointsOnSegment(N, 0, 0, M) - 2;
   Result = Result + (TotalPoints - PointsToExclude - PointsInside + PointsInside * 3) * 4;

   // Case 2: Consecutive corners on N side and then M side
   for(int x = 1; x <= N - 1; x++)
   {
      PointsInside = LatticePointsInArea(0, 0, N, 0, x, M);
      PointsToExclude = LatticePointsOnSegment(0, 0, x, M) + LatticePointsOnSegment(x, M, N, 0) - 4;
      Result = Result + (TotalPoints - PointsToExclude - PointsInside + PointsInside * 3) * 2;
   }
   for(int y = 1; y <= M - 1; y++)
   {
      PointsInside = LatticePointsInArea(0, 0, 0, M, N, y);
      PointsToExclude = LatticePointsOnSegment(0, 0, N, y) + LatticePointsOnSegment(N, y, 0, M) - 4;
      Result = Result + (TotalPoints - PointsToExclude - PointsInside + PointsInside * 3) * 2;
   }

   // Case 3: Diagonal corners, one on N side, and then one on M side
   for(int x = 1; x <= N - 1; x++)
   {
      PointsInside = LatticePointsInArea(0, 0, x, 0, N, M);
      PointsToExclude = LatticePointsOnSegment(0, 0, N, M) + LatticePointsOnSegment(x, 0, N, M) - 4;
      Result = Result + (TotalPoints - PointsToExclude - PointsInside + PointsInside * 3) * 2;
   }
   for(int y = 1; y <= M - 1; y++)
   {
      PointsInside = LatticePointsInArea(0, 0, 0, y, N, M);
      PointsToExclude = LatticePointsOnSegment(0, 0, N, M) + LatticePointsOnSegment(0, y, N, M) - 4;
      Result = Result + (TotalPoints - PointsToExclude - PointsInside + PointsInside * 3) * 2;
   }

   // Case 4: One corner, two sides opposite
   for(int x = 1; x <= N - 1; x++)
   {
      for(int y = 1; y <= M - 1; y++)
      {
         PointsInside = LatticePointsInArea(0, 0, N, y, x, M);
         PointsToExclude = LatticePointsOnSegment(0, 0, x, M)
            + LatticePointsOnSegment(x, M, N, y)
            + LatticePointsOnSegment(N, y, 0, 0) - 6;
         Result = Result + (TotalPoints - PointsToExclude - PointsInside + PointsInside * 3) * 4;
      }
   }

   return Result;
}

long long TwoMiddle(int N, int M)
{
   // let's brute force it first and see how it goes.
   // only one case: diagonal corners with two in the middle

   long long Result = 0;

   long long TotalPoints = (N - 1) * (M - 1);
   long long PointsToExclude = 0;
   long long PointsInside = 0;

   for(int x = 1; x <= N - 1; x++)
   {
      for(int y = 1; y <= M - 1; y++)
      {
         if(x * M <= N * y)   // This point is on the wrong side.  Skip!
            continue;

         PointsInside = LatticePointsInArea(0, 0, N, M, x, y)       // inside triangle
            + LatticePointsInAreaPrime(x, N, 0, y, (double)y / x * N)
            + LatticePointsInAreaPrime(y, 0, N, x, M - (double)(N - x) / (M - y) * M)
            + LatticePointsOnSegment(x, y, N, 0) - 2;               // inside corner
         PointsToExclude = LatticePointsOnSegment(0, 0, N, M) - 2   // on the diagonal
            + LatticePointsOnRay(N, M, x, y, 0, false) - 1          // ray 1
            + LatticePointsOnRay(0, 0, x, y, N, true) - 1           // ray 2
            - 1;                                                    // overlap between rays
         Result = Result + (TotalPoints - PointsToExclude - PointsInside + PointsInside * 3);

         // cout << N << " " << M << " " << x << " " << y << " " << TotalPoints << " " << PointsToExclude << " " << PointsInside
         //    << " --- " << TotalPoints - PointsToExclude + PointsInside * 2 << endl;
         // cout << LatticePointsInAreaPrime(x, N, 0, y, (double)y / x * N) << " "
         //    << LatticePointsInAreaPrime(y, 0, N, x, M - (double)(N - x) / (M - y) * M) << " "
         //    << LatticePointsOnSegment(x, y, N, 0) - 2 << endl;
      }
   }

   return Result * 2;
}

long long PutThingsTogether(int N, int M)
{
   long long Result = 0;

   for(int x = 1; x <= N; x++)
   {
      for(int y = 1; y <= M; y++)
      {
         long long SubResult = 0;
         SubResult = SubResult + NothingMiddle(x, y);
         SubResult = SubResult + OneMiddle(x, y);
         SubResult = SubResult + TwoMiddle(x, y);

         Result = Result + SubResult * (N - x + 1) * (M - y + 1);
      }
   }

   return Result;
}

long long TwoTimesTriangleArea(int x1, int y1, int x2, int y2, int x3, int y3)
{
   long long Area = x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2;
   if(Area < 0)
      Area = -Area;
   return Area;
}

long long LatticePointsOnSegment(int x1, int y1, int x2, int y2)
{
   int DX = x1 - x2;
   int DY = y1 - y2;

   if(DX < 0)   DX = -DX;
   if(DY < 0)   DY = -DY;

   return GCD(DX, DY) + 1;
}

long long LatticePointsOnRay(int x1, int y1, int x2, int y2, int wall, bool WallIsX)
{
   if(WallIsX == false)
      return LatticePointsOnRay(y1, x1, y2, x2, wall, true);

   if(wall < x1)
      return LatticePointsOnRay(-x1, y1, -x2, y2, -wall, WallIsX);

   int DX = x1 - x2;
   int DY = y1 - y2;

   if(DX < 0)   DX = -DX;
   if(DY < 0)   DY = -DY;

   int Factor = GCD(DX, DY);
   int StepX = (x2 - x1) / Factor;

   if(StepX < 0)   StepX = -StepX;

   int PointCount = (wall - x1) / StepX + 1;
   if((wall - x1) % StepX == 0)   // wall doesn't count
      PointCount = PointCount - 1;

   return PointCount;
}

long long LatticePointsInArea(int x1, int y1, int x2, int y2, int x3, int y3)
{
   // pick's theorem
   //    Area = Interior point + boundary point / 2 - 1

   long long AreaTimesTwo = TwoTimesTriangleArea(x1, y1, x2, y2, x3, y3);
   long long LatticePointCount = LatticePointsOnSegment(x1, y1, x2, y2)
      + LatticePointsOnSegment(x2, y2, x3, y3)
      + LatticePointsOnSegment(x3, y3, x1, y1) - 3;

   return (AreaTimesTwo + 2 - LatticePointCount) / 2;
}

long long LatticePointsInAreaPrime(int xL, int xR, int y1, int y2, double y3)
{
   if(y3 < y1)
      return LatticePointsInAreaPrime(xL, xR, -y1, -y2, -y3);
   if(xR < xL)
      return LatticePointsInAreaPrime(-xL, -xR, y1, y2, y3);

   if(fabs(floor(y3) - y3) < 1e-10)
      return LatticePointsInArea(xL, y2, xR, y1, xR, y3);

   long long BaseCount = LatticePointsInArea(xL, y2, xR, y1, xR, floor(y3));
   long long SegmentCount = LatticePointsOnSegment(xL, y2, xR, floor(y3)) - 2;
   long long ExtraCount = 0;

   for(int x = xL + 1; x < xR; x++)
   {
      double Upper = (y3 - y2) * (x - xL) / (xR - xL) + y2;
      double Lower = ((double)(floor(y3)) - y2) * (x - xL) / (xR - xL) + y2;

      ExtraCount = ExtraCount + floor(Upper) - floor(Lower);
   }

   return BaseCount + SegmentCount + ExtraCount;
}

long long GCD(int a, int b)
{
   if(a < b)
      swap(a, b);

   if(a - b == 1)
      return 1;
   if(b == 0)
      return a;

   return GCD(b, a % b);
}








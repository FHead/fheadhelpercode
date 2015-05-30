#include <iostream>
using namespace std;

#define NONSENSE 10000

int main();
double Crossing(double x1, double y1, double x2, double y2);

int main()
{
   int Count = 0;

   while(cin)
   {
      double x1 = NONSENSE, y1 = NONSENSE, x2 = NONSENSE, y2 = NONSENSE, x3 = NONSENSE, y3 = NONSENSE;
      cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

      if(x1 == NONSENSE || y1 == NONSENSE || x2 == NONSENSE || y2 == NONSENSE || x3 == NONSENSE || y3 == NONSENSE)
         continue;

      double C12 = Crossing(x1, y1, x2, y2);
      double C23 = Crossing(x2, y2, x3, y3);
      double C31 = Crossing(x3, y3, x1, y1);

      int PositiveCount = 0;
      if(C12 != NONSENSE && C12 > 0)   PositiveCount = PositiveCount + 1;
      if(C23 != NONSENSE && C23 > 0)   PositiveCount = PositiveCount + 1;
      if(C31 != NONSENSE && C31 > 0)   PositiveCount = PositiveCount + 1;

      Count = Count + 1;
      if(PositiveCount == 1)
         cout << Count << " " << "Yes" << endl;
      else
         cout << Count << " " << "No" << endl;
   }

   return 0;
}

double Crossing(double x1, double y1, double x2, double y2)
{
   // check if segment crosses the y axis
   
   // Not implemented ;)
   if(x1 == 0 || x2 == 0)
   {
      cerr << "Warning!  Starting point at x = 0!  Please implement this case!!!" << endl;
      return NONSENSE;
   }

   // Same point sanity check
   if(x1 == x2 && y1 == y2)
      return NONSENSE;

   // First rule out the case where it's a vertical line
   if(x1 == x2)
      return NONSENSE;

   // Then for simplicity let's remove case where it's a horizontal line
   if(y1 == y2)
   {
      if(x1 * x2 < 0)
         return y1;
      else
         return NONSENSE;
   }

   // Now get the slope and do some arithmetic
   double Slope = (y2 - y1) / (x2 - x1);
   double Intersect = y1 - x1 * Slope;

   // There's a potential boundary problem here.  Revisit if needed
   if(Intersect > min(y1, y2) && Intersect <= max(y1, y2))
      return Intersect;

   return NONSENSE;
}




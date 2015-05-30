#include <iostream>
using namespace std;

int main();
int GetGCD(int x, int y);

int main()
{
   int S = 50;

   // number of triangles with tip at (0, 0) is simply S * S
   int TipZero = S * S;

   // now counting number of triangles with left foot at (0, 0)
   int FootZero = 0;

   // loop over tip locations
   for(int y = 1; y <= S; y++)
   {
      for(int x = 0; x <= S; x++)
      {
         int GCD = GetGCD(x, y);
         int StepX = x / GCD;
         int StepY = y / GCD;

         bool Good = true;
         for(int i = 1; Good == true; i++)
         {
            int FootX = x + StepY * i;
            int FootY = y - StepX * i;

            if(FootX < 0 || FootY < 0)
               Good = false;
            if(FootX > S || FootY > S)
               Good = false;
            if(Good == false)
               break;

            // cout << x << " " << y << ", " << FootX << " " << FootY << endl;

            FootZero = FootZero + 1;
         }
      }
   }

   cout << TipZero << " " << FootZero << " " << TipZero + FootZero * 2 << endl;

   return 0;
}

int GetGCD(int x, int y)
{
   if(x < y)
      return GetGCD(y, x);

   if(x == 0)
      return y;
   if(y == 0)
      return x;

   if(x == 1 || y == 1)
      return 1;
   if(x % y == 0)
      return y;

   return GetGCD(y, x % y);
}








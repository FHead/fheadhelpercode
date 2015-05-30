#include <iostream>
using namespace std;

int main()
{
   int Target = 2000000;
   int Best = -1;

   for(int i = 1; i <= 1000; i++)
   {
      for(int j = 1; j <= i; j++)
      {
         int Result = i * (i + 1) / 2 * j * (j + 1) / 2;
         
         int Difference = Result - Target;
         if(Difference < 0)
            Difference = -Difference;

         if(Best < 0 || Difference < Best)
         {
            Best = Difference;
            cout << i << " " << j << " " << i * j << " " << Difference << endl;
         }
      }
   }

   return 0;
}





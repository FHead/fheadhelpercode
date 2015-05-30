#include <iostream>
using namespace std;

int main()
{
   int Turns = 15;
   int Combinations = 1;
   for(int i = 0; i < Turns; i++)
      Combinations = Combinations * 2;

   long long GrandTotal = 0;
   long long Factorial = 1;

   for(int i = 1; i <= Turns; i++)
      Factorial = Factorial * (i + 1);

   for(int i = 1; i < Combinations; i++)
   {
      int Count = 0;
      long long Total = 1;

      int Temp = i;

      for(int j = 0; j < Turns; j++)   // j + 2 is the demoninator
      {
         if(Temp % 2 == 1)
         {
            Count = Count + 1;
            Total = Total * 1;
         }
         else
            Total = Total * (j + 2 - 1);

         Temp = Temp / 2;
      }

      // cout << i << " " << Count << " " << Total << endl;

      if(Count > (double)Turns / 2)
         GrandTotal = GrandTotal + Total;
   }

   cout << GrandTotal << "/" << Factorial << " = " << (double)GrandTotal / Factorial << endl;
   cout << "Inverse: " << (double)Factorial / GrandTotal << endl;

   return 0;
}





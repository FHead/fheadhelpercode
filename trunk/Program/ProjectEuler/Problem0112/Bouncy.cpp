#include <iostream>
#include <iomanip>
using namespace std;

int main();
bool IsBouncy(int Number);

int main()
{
   int Yes = 0, No = 0;

   for(int i = 1; i <= 10000000; i++)
   {
      if(IsBouncy(i) == true)
         Yes = Yes + 1;
      else
         No = No + 1;

      cout << i << " " << Yes << " " << No << " " << setprecision(20) << (double)Yes / (Yes + No) << endl;
   }

   return 0;
}

bool IsBouncy(int Number)
{
   if(Number < 100)
      return false;

   bool HasIncreased = false;
   bool HasDecreased = false;

   int LastNumber = Number % 10;
   Number = Number / 10;

   while(Number > 0)
   {
      int Temp = Number % 10;
      Number = Number / 10;

      if(Temp > LastNumber)
         HasIncreased = true;
      if(Temp < LastNumber)
         HasDecreased = true;

      LastNumber = Temp;
   }

   if(HasIncreased == true && HasDecreased == true)
      return true;
   return false;
}







#include <iostream>
using namespace std;

int main()
{
   for(int Up = 11; Up <= 99; Up++)
   {
      if(Up % 10 == 0)
         continue;

      for(int Down = Up + 1; Down <= 99; Down++)
      {
         if(Down % 10 == 0)
            continue;

         int Up1 = Up / 10;
         int Up2 = Up % 10;
         int Down1 = Down / 10;
         int Down2 = Down % 10;

         bool Good = false;

         if(Up1 == Down1)
            if(Up * Down2 == Down * Up2)
               Good = true;
         if(Up2 == Down1)
            if(Up * Down2 == Down * Up1)
               Good = true;
         if(Up1 == Down2)
            if(Up * Down1 == Down * Up2)
               Good = true;
         if(Up2 == Down2)
            if(Up * Down1 == Down * Up1)
               Good = true;

         if(Good == true)
            cout << Up << "/" << Down << endl;
      }
   }

   return 0;
}





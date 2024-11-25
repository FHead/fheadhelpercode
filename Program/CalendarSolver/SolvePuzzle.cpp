#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

#include "Board.h"

int main(int argc, char *argv[])
{
   string DateString = "20241124";
   if(argc > 1)
      DateString = argv[1];

   int Year = 2024, Month = 11, Day = 24, WDay = 0;
   Year  = stoi(DateString.substr(0, 4));
   Month = stoi(DateString.substr(4, 2));
   Day   = stoi(DateString.substr(6, 2));

   tm time_in = {0, 0, 0, Day, Month - 1, Year - 1900}; // 1-based day, 0-based month, year since 1900
   time_t time_temp = mktime(&time_in);
   const tm *time_out = localtime(&time_temp);

   WDay  = time_out->tm_wday;   // 0 = Sunday, 1 = Monday, etc

   vector<string> MonthString{"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                              "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
   vector<string> WDayString{"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

   cout << endl;
   cout << "Solving for " << MonthString[Month-1] << " " << Day << ", " << Year
      << " (" << WDayString[WDay] << ")" << endl;
   cout << endl;

   // cout << "Solving for " << Year << " " << Month << "/" << Day << " (MM/DD), day in week " << WDay << endl;

   vector<Shape> Shapes;

   Shapes.push_back(Shape(0, {0, 0, 0, 1, 2}, {0, 1, 2, 0, 0}, 4));
   Shapes.push_back(Shape(1, {0, 0, 0, 0, 1}, {0, 1, 2, 3, 0}, 4));
   Shapes.push_back(Shape(2, {0, 0, 1, 2, 2}, {0, 1, 1, 1, 2}, 2));
   Shapes.push_back(Shape(3, {0, 0, 0, 0, 0}, {0, 1, 2, 3, 4}, 2));
   Shapes.push_back(Shape(4, {0, 0, 0, 1, 2}, {0, 1, 2, 1, 1}, 4));
   Shapes.push_back(Shape(5, {0, 1, 2, 2, 3}, {0, 0, 0, 1, 0}, 4));
   Shapes.push_back(Shape(6, {0, 1, 1, 2, 3}, {0, 0, 1, 1, 1}, 4));
   Shapes.push_back(Shape(7, {0, 1, 1, 1, 2}, {0, 0, 1, 2, 1}, 4));
   Shapes.push_back(Shape(8, {0, 0, 1, 2, 2}, {0, 1, 0, 0, 1}, 4));
   Shapes.push_back(Shape(9, {0, 1, 1, 2, 2}, {0, 0, 1, 0, 1}, 4));

   vector<int> WDayX{8, 7, 8, 7, 7, 7, 8};
   vector<int> WDayY{1, 5, 5, 4, 3, 2, 2};
   vector<int> DayX{4, 5, 6, 1, 2, 3, 4, 5, 6, 1,
                     2, 3, 4, 7, 6, 1, 2, 3, 4, 5,
                     6, 1, 2, 3, 4, 5, 6, 4, 5, 6,
                     5};
   vector<int> DayY{5, 5, 5, 4, 4, 4, 4, 4, 4, 3,
                     3, 3, 3, 0, 3, 2, 2, 2, 2, 2,
                     2, 1, 1, 1, 1, 1, 1, 0, 0, 0,
                     3};
   vector<int> MonthX{0, 1, 2, 3, 0, 0, 0, 0, 0, 1, 2, 3};
   vector<int> MonthY{5, 5, 5, 5, 4, 3, 2, 1, 0, 0, 0, 0};

   Board Initial;
   // Initial.State[0][0] = STATE_FORBIDDEN;
   // Initial.State[2][4] = STATE_FORBIDDEN;
   // Initial.State[7][3] = STATE_FORBIDDEN;
   Initial.State[DayX[Day-1]][DayY[Day-1]] = STATE_FORBIDDEN;
   Initial.State[MonthX[Month-1]][MonthY[Month-1]] = STATE_FORBIDDEN;
   Initial.State[WDayX[WDay]][WDayY[WDay]] = STATE_FORBIDDEN;

   /*
   cout << "Shape test" << endl;
   cout << endl;
   for(int i = 0; i < (int)Shapes.size(); i++)
   {
      cout << "Shape #" << i << endl;
      cout << endl;

      Shape X = Shapes[i];
      for(int r = 0; r < X.RotatePeriod; r++)
      {
         cout << X.RotatePeriod << endl;
         cout << X << endl;
         X = X.Rotate();
      }

      cout << endl;
   }
   */

   cout << "Initial setup" << endl;
   cout << Initial << endl;

   Board Final = Solve(Initial, Shapes);

   cout << "Final setup" << endl;
   cout << Final << endl;

   return 0;
}


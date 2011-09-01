//-------------------------------------------------------------------------
#include <sstream>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

//-------------------------------------------------------------------------
int main(int argc, char *argv[]);
string DateString(time_t date);
string PMDateString(time_t date);
time_t Get1111();
time_t PMToDate(string str);
time_t ToDate(string str);
//-------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   // no parameter = print today && (1111) && usage
   // with parameter = conversion from ((0) 1111) to 20061023 or vise versa
   //    depends on the format
   
   if(argc == 1)
   {
      cout << "Usage: " << argv[0] << " 2532" << endl;
      cout << "       " << argv[0] << " 0,2532" << endl;
      cout << "       " << argv[0] << " 20070501" << endl;
      cout << "Note the date format is assumed to be YYYYMMDD" << endl << endl;
   
      time_t day1111 = Get1111();
      cout << "[" << PMDateString(day1111) << "] = " << DateString(day1111) << endl;   

      time_t today = time(NULL);
      cout << "[" << PMDateString(today) << "] = " << DateString(today) << endl;
   }
   else
   {
      for(int i = 1; i < argc; i++)
      {
         time_t inputdate;
         
         string arg = argv[i];
         if(arg.size() == 4)
            inputdate = PMToDate(arg);
         else if(arg.size() > 4 && arg[arg.size()-1-4] == ',')
            inputdate = PMToDate(arg);
         else if(arg.size() == 8)
            inputdate = ToDate(arg);
         else
            continue;
         
         cout << "[" << PMDateString(inputdate) << "] = " << DateString(inputdate) << endl;   
      }
   }
   
   return 0;
}
//-------------------------------------------------------------------------
string DateString(time_t date)
{
   string datestr = ctime(&date);
   stringstream str(datestr);

   string weekday;
   string month;
   string day;
   string timestr;
   string year;

   str >> weekday;   // discard week day
   str >> month;
   str >> day;
   str >> timestr;   // discard time of the day
   str >> year;
   
   return (weekday + " " + month + " " + day + ", " + year);
}
//-------------------------------------------------------------------------
string PMDateString(time_t date)
{
   stringstream str;

   time_t day1111 = Get1111();
   long long diffseconds = difftime(date, day1111) + 3532;

   if(diffseconds < 0 || diffseconds >= 2401 * 60 * 60 * 24)
   {
      int period = diffseconds / 2401 / 60 / 60 / 24;
      if(diffseconds < 0)
         period = period - 1;
      diffseconds = diffseconds - period * 2401 * 60 * 60 * 24;

      str << "(" << period << ") ";
   }
   
   long diffdays = (long)(diffseconds / 60 / 60 / 24);

   str << (diffdays / 343) % 7 + 1
      << (diffdays / 49) % 7 + 1
      << (diffdays / 7) % 7 + 1
      << diffdays % 7 + 1;

   return str.str();
}
//-------------------------------------------------------------------------
time_t Get1111()
{
   tm day1711info;
   day1711info.tm_sec = 1;
   day1711info.tm_min = 0;
   day1711info.tm_hour = 0;
   day1711info.tm_mon = 8 - 1;   // August
   day1711info.tm_mday = 14;   // 14th
   day1711info.tm_year = 106;   // 2006 - 1900 = 106
   time_t day1711 = mktime(&day1711info);
   
   time_t day1111 = day1711 - (60 * 60 * 24) * 7 * 7 * (7 - 1);

   return day1111;
}
//-------------------------------------------------------------------------
time_t PMToDate(string str)
{
   time_t day1111 = Get1111();

   int period = 0;

   if(str.size() > 4)
   {
      stringstream periodstr(str.substr(0, str.size() - 5));
      periodstr >> period;
      str = str.substr(str.size() - 4, 4);
   }

   long daydiff = (int)(str[0] - '1') * 343
      + (int)(str[1] - '1') * 49
      + (int)(str[2] - '1') * 7
      + (int)(str[3] - '1') * 1;
   daydiff = daydiff + 2401 * period;

   // cout << "daydiff " << daydiff << endl;

   time_t day = day1111 + daydiff * 24 * 60 * 60 + 1234;
   
   return day;
}
//-------------------------------------------------------------------------
time_t ToDate(string str)
{
   int year = 2007;
   int month = 2;
   int monthday = 14;
   
   str.insert(str.begin() + 6, ' ');
   str.insert(str.begin() + 4, ' ');
   stringstream stream(str);
   stream >> year >> month >> monthday;

   tm dayinfo;
   dayinfo.tm_sec = 1;
   dayinfo.tm_min = 0;
   dayinfo.tm_hour = 3;
   dayinfo.tm_mon = month - 1;
   dayinfo.tm_mday = monthday;
   dayinfo.tm_year = year - 1900;
   time_t day = mktime(&dayinfo);
   
   return day;
}
//-------------------------------------------------------------------------

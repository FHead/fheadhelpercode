#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[]);
vector<string> ParseByComma(string Input);

int main(int argc, char *argv[])
{
   if(argc == 1)
   {
      cerr << "Usage: " << argv[0] << " ListOfNumbers" << endl;
      return -1;
   }

   vector<string> NumberStrings = ParseByComma(argv[1]);

   vector<int> Numbers;
   for(int i = 0; i < (int)NumberStrings.size(); i++)
   {
      int Location = NumberStrings[i].find('-');
      if(Location == string::npos)
         Numbers.push_back(atoi(NumberStrings[i].c_str()));
      else
      {
         string SubString1 = NumberStrings[i].substr(0, Location);
         string SubString2 = NumberStrings[i].substr(Location + 1, string::npos);

         if(SubString1 == "" && SubString2.size() > 0)
            Numbers.push_back(atoi(SubString2.c_str()));
         else if(SubString2 == "" && SubString1.size() > 0)
            Numbers.push_back(atoi(SubString1.c_str()));
         else if(SubString1.size() > 0 && SubString2.size() > 0)
         {
            int Min = atoi(SubString1.c_str());
            int Max = atoi(SubString2.c_str());

            if(Min > Max)
               swap(Min, Max);

            for(int j = Min; j <= Max; j++)
               Numbers.push_back(j);
         }
      }
   }

   sort(Numbers.begin(), Numbers.end());
   vector<int>::iterator iter = unique(Numbers.begin(), Numbers.end());
   Numbers.erase(iter, Numbers.end());

   iter = find(Numbers.begin(), Numbers.end(), 3001);
   if(iter != Numbers.end())
      Numbers.erase(iter);

   int Start = Numbers[0];
   int End = Numbers[0];
   for(int i = 1; i < (int)Numbers.size(); i++)
   {
      if(i % 500 == 0)
      {
         if(Start == End)
            cout << Start << endl;
         else
            cout << Start << "-" << End << endl;
         Start = Numbers[i];
         End = Numbers[i];
      }
      else if(Numbers[i] - 1 == End)
         End = Numbers[i];
      else
      {
         if(Start == End)
            cout << Start << ",";
         else
            cout << Start << "-" << End << ",";
         Start = Numbers[i];
         End = Numbers[i];
      }
   }
   if(Start == End)
      cout << Start << endl;
   else
      cout << Start << "-" << End << endl;

   return 0;
}

vector<string> ParseByComma(string Input)
{
   vector<string> Result;

   int Index = 0;
   while(Input.find(',', Index) != string::npos)
   {
      int NextIndex = Input.find(',', Index);
      Result.push_back(Input.substr(Index, NextIndex - Index));
      Index = NextIndex + 1;
   }
   Result.push_back(Input.substr(Index));

   for(int i = 0; i < (int)Result.size(); i++)
   {
      if(Result[i] == "")
      {
         Result.erase(Result.begin() + i);
         i = i - 1;
      }
   }
   
   return Result;
}






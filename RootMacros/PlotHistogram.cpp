#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

#include "TH1D.h"
#include "TCanvas.h"

int main(int argc, char *argv[])
{
   for(int i = 1; i < argc; i++)
   {
      if(string(argv[i]) == "-h" || string(argv[i]) == "--h" || string(argv[i]) == "--help")
      {
         cout << "Usage: " << argv[0] << endl;
         cout << "   " << argv[0] << " FileBase" << endl;
         cout << "   " << argv[0] << " NumberOfBins FileBase" << endl;
         cout << "   " << argv[0] << " NumberOfBins Maximum FileBase" << endl;
         cout << "   " << argv[0] << " NumberOfBins Minimum Maximum FileBase" << endl;
         cout << "If things are not given, default to 100 bins from 0 to 1, with base name \"Plot\"" << endl;
         return 0;
      }
   }

   int BinCount = 100;
   double Min = 0;
   double Max = 1;
   string FileBase = "Plot";

   if(argc == 2)
      FileBase = argv[1];
   else if(argc == 3)
   {
      BinCount = atoi(argv[1]);
      FileBase = argv[2];
   }
   else if(argc == 4)
   {
      BinCount = atoi(argv[1]);
      Max = atof(argv[2]);
      FileBase = argv[3];
   }
   else if(argc >= 5)
   {
      BinCount = atoi(argv[1]);
      Min = atof(argv[2]);
      Max = atof(argv[3]);
      FileBase = argv[4];
   }

   TH1D HPlot("HPlot", "Plot!", BinCount, Min, Max);

   while(cin)
   {
      double Number = -99999;
      cin >> Number;
      if(Number < -99998)
         continue;

      HPlot.Fill(Number);
   }

   TCanvas C("C", "C", 0, 0, 1024, 1024);

   HPlot.Draw();

   C.SaveAs((FileBase + ".C").c_str());
   C.SaveAs((FileBase + ".png").c_str());
   C.SaveAs((FileBase + ".eps").c_str());
   C.SaveAs((FileBase + ".pdf").c_str());

   return 0;
}








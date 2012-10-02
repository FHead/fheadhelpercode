#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

#include "TH2D.h"
#include "TCanvas.h"

int main(int argc, char *argv[])
{
   for(int i = 1; i < argc; i++)
   {
      if(string(argv[i]) == "-h" || string(argv[i]) == "--h" || string(argv[i]) == "--help")
      {
         cout << "Usage: " << argv[0] << endl;
         cout << "   " << argv[0] << " FileBase" << endl;
         cout << "   " << argv[0] << " NumberOfBinsX NumberOfBinsY FileBase" << endl;
         cout << "   " << argv[0] << " NumberOfBinsX MaximumX NumberOfBinsY MaximumY FileBase" << endl;
         cout << "   " << argv[0] << " NumberOfBinsX MinimumX MaximumX NumberOfBinsY MinimumY MaximumY FileBase" << endl;
         cout << "If things are not given, default to 100 bins from 0 to 1, with base name \"Plot\"" << endl;
         return 0;
      }
   }

   int BinCountX = 100, BinCountY = 100;
   double MinX = 0, MinY = 0;
   double MaxX = 1, MaxY = 1;
   string FileBase = "Plot";

   if(argc < 8 && argc % 2 == 1)
   {
      cerr << "Bad input.  Execute '" << argv[0] << " -h' for usage";
      return -1;
   }

   if(argc == 2)
      FileBase = argv[1];
   else if(argc == 4)
   {
      BinCountX = atoi(argv[1]);
      BinCountY = atoi(argv[2]);
      FileBase = argv[3];
   }
   else if(argc == 6)
   {
      BinCountX = atoi(argv[1]);
      MaxX = atof(argv[2]);
      BinCountY = atoi(argv[3]);
      MaxY = atof(argv[4]);
      FileBase = argv[5];
   }
   else if(argc >= 8)
   {
      BinCountX = atoi(argv[1]);
      MinX = atof(argv[2]);
      MaxX = atof(argv[3]);
      BinCountY = atoi(argv[4]);
      MinY = atof(argv[5]);
      MaxY = atof(argv[6]);
      FileBase = argv[7];
   }

   TH2D HPlot("HPlot", "Plot!", BinCountX, MinX, MaxX, BinCountY, MinY, MaxY);

   while(cin)
   {
      double Number1 = -99999, Number2 = -99999, Number3 = -99999;
      cin >> Number1 >> Number2 >> Number3;
      if(Number1 < -99998 || Number2 < -99998 || Number3 < -99998)
         continue;

      HPlot.Fill(Number1, Number2, Number3);
   }

   TCanvas C("C", "C", 0, 0, 1024, 1024);

   HPlot.Draw("colz");

   C.SaveAs((FileBase + ".C").c_str());
   C.SaveAs((FileBase + ".png").c_str());
   C.SaveAs((FileBase + ".eps").c_str());
   C.SaveAs((FileBase + ".pdf").c_str());

   C.SetLogz();
   
   C.SaveAs((FileBase + "_Log.C").c_str());
   C.SaveAs((FileBase + "_Log.png").c_str());
   C.SaveAs((FileBase + "_Log.eps").c_str());
   C.SaveAs((FileBase + "_Log.pdf").c_str());

   HPlot.Draw("lego20z");

   C.SetLogz(false);

   C.SaveAs((FileBase + "_Lego.C").c_str());
   C.SaveAs((FileBase + "_Lego.png").c_str());
   C.SaveAs((FileBase + "_Lego.eps").c_str());
   C.SaveAs((FileBase + "_Lego.pdf").c_str());

   C.SetLogz(true);
   
   C.SaveAs((FileBase + "_LegoLog.C").c_str());
   C.SaveAs((FileBase + "_LegoLog.png").c_str());
   C.SaveAs((FileBase + "_LegoLog.eps").c_str());
   C.SaveAs((FileBase + "_LegoLog.pdf").c_str());

   return 0;
}








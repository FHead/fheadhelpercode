#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

#include "TGraph.h"
#include "TCanvas.h"

int main(int argc, char *argv[])
{
   for(int i = 1; i < argc; i++)
   {
      if(string(argv[i]) == "-h" || string(argv[i]) == "--h" || string(argv[i]) == "--help")
      {
         cout << "Usage: " << argv[0] << endl;
         cout << "   " << argv[0] << " FileBase" << endl;
         cout << "If things are not given, default to 100 bins from 0 to 1, with base name \"Plot\"" << endl;
         return 0;
      }
   }

   string FileBase = "Plot";

   if(argc < 2)
   {
      cerr << "Bad input.  Execute '" << argv[0] << " -h' for usage";
      return -1;
   }

   FileBase = argv[1];

   TGraph Graph;
   int PointCount = 0;

   while(cin)
   {
      double Number1 = -99999, Number2 = -99999;
      cin >> Number1 >> Number2;
      if(Number1 < -99998 || Number2 < -99998)
         continue;

      Graph.SetPoint(PointCount, Number1, Number2);
      PointCount = PointCount + 1;
   }

   TCanvas C("C", "C", 0, 0, 1024, 1024);

   Graph.SetMarkerStyle(7);
   Graph.Draw("ap");

   C.SaveAs((FileBase + ".C").c_str());
   C.SaveAs((FileBase + ".png").c_str());
   C.SaveAs((FileBase + ".eps").c_str());
   C.SaveAs((FileBase + ".pdf").c_str());

   return 0;
}








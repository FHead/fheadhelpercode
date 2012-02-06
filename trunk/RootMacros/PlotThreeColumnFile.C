#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TGraphErrors.h"

void PlotThreeColumnFile(char *filename, char *outputfilename);

void PlotThreeColumnFile(char *filename, char *outputfilename)
{
   ifstream in(filename);

   TFile out(outputfilename, "RECREATE");

   vector<double> xData;
   vector<double> yData;
   vector<double> errorData;

   while(in)
   {
      double xTemp = 0;
      double yTemp = 0;
      double errorTemp = 0;

      in >> xTemp >> yTemp >> errorTemp;

      xData.push_back(xTemp);
      yData.push_back(yTemp);
      errorData.push_back(errorTemp);
   }

   double *xArray = new double[xData.size()];
   double *yArray = new double[yData.size()];
   double *errorArray = new double[errorData.size()];

   for(int i = 0; i < (int)xData.size(); i++)
   {
      xArray[i] = xData[i];
      yArray[i] = yData[i];
      errorArray[i] = errorData[i];
   }

   TGraphErrors graph(xData.size(), xArray, yArray, 0, errorArray);
   graph.Write();

   delete[] errorArray;
   delete[] yArray;
   delete[] xArray;

   out.Close();

   in.close();
}








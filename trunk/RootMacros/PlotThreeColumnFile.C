#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TGraphErrors.h"
#include "TH2D.h"

void PlotThreeColumnFile(char *filename, char *outputfilename);
void PlotThreeColumnFile2D(char *filename, char *outputfilename, int BinCount = 50);

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

void PlotThreeColumnFile2D(char *filename, char *outputfilename, int BinCount)
{
   ifstream in(filename);

   TFile out(outputfilename, "RECREATE");

   vector<double> xData;
   vector<double> yData;
   vector<double> zData;

   double MinX = 99999;
   double MaxX = -99999;
   double MinY = 99999;
   double MaxY = -99999;

   while(in)
   {
      double xTemp = 0;
      double yTemp = 0;
      double zTemp = 0;

      in >> xTemp >> yTemp >> zTemp;

      xData.push_back(xTemp);
      yData.push_back(yTemp);
      zData.push_back(zTemp);

      if(MinX > xTemp)   MinX = xTemp;
      if(MaxX < xTemp)   MaxX = xTemp;
      if(MinY > yTemp)   MinY = yTemp;
      if(MaxY < yTemp)   MaxY = yTemp;
   }

   TH2D histogram("histogram", "histogram", BinCount, MinX, MaxX, BinCount, MinY, MaxY);

   for(int i = 0; i < (int)xData.size(); i++)
      histogram.Fill(xData[i], yData[i], zData[i]);

   histogram.Write();

   out.Close();

   in.close();
}













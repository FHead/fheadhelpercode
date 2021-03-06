#ifndef PlotHelper6612
#ifndef PlotHelperForward6612
#define PlotHelperForward6612

// Plot helper, 6612 version
// Intended to help organizing plots and to avoid cluttering
// The main idea is to write a plot both to a pdf and to a TFile at the same time,
//    so that we can check quickly using pdf and come back to TFile later if needed
//    the helper functions here will be mostly on *.ps files
// Added feature compared to 6152: being able to insert a table of contents (and it's clickable!)
//    automatic home button
//    automatic page number
// Developer: Yi Chen, 6612

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

#include "TCanvas.h"
#include "TLatex.h"
#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TGraph.h"
#include "TVirtualPad.h"
#include "TVirtualPS.h"
#include "TStyle.h"

class PsFileHelper
{
private:
   string FileName;
   string Option;
   bool Status;   // false - file not opened; true - file good and ongoing
private:
   bool AutomaticHomeButton;
   double HomeButtonX;
   double HomeButtonY;
   double HomeButtonSize;
   string HomeButtonDestination;
   bool PrintPageNumber;
   int NextPageNumber;
public:
   PsFileHelper();
   PsFileHelper(string filename);
   PsFileHelper(string filename, string option);
   ~PsFileHelper();
   void Open(string filename);
   void Close(bool Convert = true);
   string GetFileName();
   void SetOption(string option);
   string GetOption();
   template <class PlotType> void AddPlot(PlotType *Histogram, string PlotOption = "",
      bool LogY = false, bool LogZ = false, bool Grid = false, bool LogX = false);
   template <class PlotType> void Add4PanelPlot(PlotType *Histogram1, PlotType *Histogram2,
      PlotType *Histogram3, PlotType *Histogram4, string PlotOption = "",
      bool LogY = false, bool LogZ = false, bool Grid = false, bool LogX = false);
   template <class PlotType> void AddPlot(PlotType &Histogram, string PlotOption = "",
      bool LogY = false, bool LogZ = false, bool Grid = false, bool LogX = false);
   template <class PlotType> void Add4PanelPlot(PlotType &Histogram1, PlotType &Histogram2,
      PlotType &Histogram3, PlotType &Histogram4, string PlotOption = "",
      bool LogY = false, bool LogZ = false, bool Grid = false, bool LogX = false);
   template <class PlotType> void AddNormalizedPlot(PlotType *Histogram, string PlotOption = "",
      bool LogY = false, bool LogZ = false, bool Grid = false);
   template <class PlotType> void AddNormalizedPlot(PlotType &Histogram, string PlotOption = "",
      bool LogY = false, bool LogZ = false, bool Grid = false);
   template <class PlotType> void AddPlotWithText(PlotType *Histogram, string Text,
      string PlotOption = "", double X = 0.1, double Y = 0.9, double TextSize = 0.03);
   template <class PlotType> void AddPlotWithText(PlotType &Histogram, string Text,
      string PlotOption = "", double X = 0.1, double Y = 0.9, double TextSize = 0.03);
   void AddHistogramFromFile(TFile &File, string HistogramName,
      string PlotOption = "", bool LogY = false, bool LogZ = false, bool Grid = false, bool LogX = false);
   void Add4PanelHistogramFromFile(TFile &File, string HistogramName1, string HistogramName2,
      string HistogramName3, string HistogramName4,
      string PlotOption = "", bool LogY = false, bool LogZ = false, bool Grid = false, bool LogX = false);
   void AddGraphFromFile(TFile &File, string GraphName,
      string PlotOption = "", bool LogY = false, bool LogZ = false, bool Grid = false, bool LogX = false);
   void AddCanvas(TCanvas *Canvas);
   void AddCanvas(TCanvas &Canvas);
   void AddCanvasWithText(TCanvas *Canvas, string Text, double X = 0.1, double Y = 0.9, double TextSize = 0.03);
   void AddCanvasWithText(TCanvas &Canvas, string Text, double X = 0.1, double Y = 0.9, double TextSize = 0.03);
   void AddTextPage(string Text, double X = 0.15, double Y = 0.5, double TextSize = 0.05);
   void AddTextPage(vector<string> Text, double X = 0.1, double Y = 0.9, double TextSize = 0.04);
   void AddTimeStampPage();
   void AddTableOfContentPage(vector<string> Items, vector<string> Destinations,
      double X = 0.11, double Y = 0.8, double TextSize = 0.03);
public:
   void PrintStringToPSFile(string String);
   void PrintLineToPSFile(string Line);
   void InsertNamedDestination(string Name);
   void InsertBallLinkAbsolute(int X, int Y, int Radius, string Destination);
   void InsertHomeButtonAbsolute(double X, double Y, double Size, string Destination);
   void SetAutomaticHomeButton(bool newvalue = true, string Destination = "HomePage",
      double X = 50, double Y = 50, double Size = 75);
   void SetPageNumber(bool printnumber);
   void InsertPageNumber(TCanvas &Canvas, int PageNumber = -1);
};

#endif
#endif



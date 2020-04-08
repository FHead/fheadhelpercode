#ifndef PlotHelper17544
#ifndef PlotHelper17544Forward
#define PlotHelper17544Forward

// Plot helper, (1) 5653 version
// Intended to help organizing plots and to avoid cluttering
// The main idea is to write a plot both to a pdf and to a TFile at the same time,
//    so that we can check quickly using pdf and come back to TFile later if needed
//    the helper functions here will be mostly on *.pdf files
// Added feature compared to 6152: being able to insert a table of contents (and it's clickable!)
//    automatic home button
//    automatic page number
// Developer: Yi Chen, (1) 5653

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
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TGraph.h"
#include "TVirtualPad.h"
#include "TPDF.h"
#include "TStyle.h"

class PdfFileHelper
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
   PdfFileHelper();
   PdfFileHelper(string filename);
   PdfFileHelper(string filename, string option);
   ~PdfFileHelper();
   void Open(string filename);
   void Close();
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
   void AddPlot(TTree *Tree, string ToPlot, string Selection, string PlotOption = "", string Titles = ";;",
      int Bin = 100, double Min = 0, double Max = 100,
      bool LogY = false, bool LogZ = false, bool Grid = false, bool LogX = false);
   void AddPlotProfile(TTree *Tree, string ToPlot, string Selection, string PlotOption = "prof", string Titles = ";;",
      int Bin = 100, double Min = 0, double Max = 100,
      bool LogY = false, bool LogZ = false, bool Grid = false, bool LogX = false);
   void AddPlot2D(TTree *Tree, string ToPlot, string Selection, string PlotOption = "", string Titles = ";;",
      int BinX = 100, double MinX = 0, double MaxX = 100,
      int BinY = 100, double MinY = 0, double MaxY = 100,
      bool LogY = false, bool LogZ = false, bool Grid = false, bool LogX = false);
   void AddPlotProfile2D(TTree *Tree, string ToPlot, string Selection, string PlotOption = "colz", string Titles = ";;",
      int BinX = 100, double MinX = 0, double MaxX = 100,
      int BinY = 100, double MinY = 0, double MaxY = 100,
      bool LogY = false, bool LogZ = false, bool Grid = false, bool LogX = false);
   void AddCanvas(TCanvas *Canvas);
   void AddCanvas(TCanvas &Canvas);
   void AddCanvasWithText(TCanvas *Canvas, string Text, double X = 0.1, double Y = 0.9, double TextSize = 0.03);
   void AddCanvasWithText(TCanvas &Canvas, string Text, double X = 0.1, double Y = 0.9, double TextSize = 0.03);
   void AddTextPage(string Text, double TextSize = 0.05);
   void AddTextPage(string Text, double X, double Y, double TextSize = 0.05);
   void AddTextPage(vector<string> Text, double X = 0.1, double Y = 0.9, double TextSize = 0.04);
   void AddTimeStampPage();
   void AddTableOfContentPage(vector<string> Items, vector<string> Destinations,
      double X = 0.11, double Y = 0.8, double TextSize = 0.03);
public:
   void PrintStringToPdfFile(string String);
   void PrintLineToPdfFile(string Line);
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


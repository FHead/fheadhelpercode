#ifndef PlotHelper6125
#define PlotHelper6125

// Plot helper, version 0 - 6125 version
// Intended to help organizing plots and to avoid cluttering
// The main idea is to write a plot both to a pdf and to a TFile at the same time,
//    so that we can check quickly using pdf and come back to TFile later if needed
//    the helper functions here will be mostly on *.ps files
// Developer: Yi Chen, 6125

#include <iostream>
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

class PsFileHelper
{
private:
   string FileName;
   string Option;
   bool Status;   // false - file not opened; true - file good and ongoing
public:
   PsFileHelper();
   PsFileHelper(string filename);
   PsFileHelper(string filename, string option);
   ~PsFileHelper();
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
   void AddCanvas(TCanvas *Canvas);
   void AddCanvas(TCanvas &Canvas);
   void AddCanvasWithText(TCanvas *Canvas, string Text, double X = 0.1, double Y = 0.9, double TextSize = 0.03);
   void AddCanvasWithText(TCanvas &Canvas, string Text, double X = 0.1, double Y = 0.9, double TextSize = 0.03);
   void AddTextPage(string Text, double X = 0.15, double Y = 0.5, double TextSize = 0.05);
   void AddTextPage(vector<string> Text, double X = 0.1, double Y = 0.9, double TextSize = 0.04);
   void AddTimeStampPage();
};

PsFileHelper::PsFileHelper()
{
   Status = false;
   FileName = "";
   Option = "Landscape";
}

PsFileHelper::PsFileHelper(string filename)
{
   Option = "Landscape";

   Open(filename);
}

PsFileHelper::PsFileHelper(string filename, string option)
{
   Option = option;

   Open(filename);
}

PsFileHelper::~PsFileHelper()
{
   if(Status == true)
      Close();
}

void PsFileHelper::Open(string filename)
{
   FileName = filename;

   Status = true;

   TCanvas canvas;
   canvas.Print((FileName + "[").c_str(), Option.c_str());
}

void PsFileHelper::Close()
{
   TCanvas canvas;
   canvas.Print((FileName + "]").c_str(), Option.c_str());

   gROOT->ProcessLine((".! ps2pdf " + FileName).c_str());
   gROOT->ProcessLine((".! rm " + FileName).c_str());

   Status = false;
   FileName = "";
}

string PsFileHelper::GetFileName()
{
   return FileName;
}

void PsFileHelper::SetOption(string option)
{
   Option = option;
}

string PsFileHelper::GetOption()
{
   return Option;
}

template <class PlotType> void PsFileHelper::AddPlot(PlotType *Histogram, string PlotOption, bool LogY, bool LogZ, bool Grid, bool LogX)
{
   if(Histogram == NULL)
      return;

   TCanvas canvas;

   Histogram->Draw(PlotOption.c_str());

   if(LogX == true)
      canvas.SetLogx();
   if(LogY == true)
      canvas.SetLogy();
   if(LogZ == true)
      canvas.SetLogz();

   if(Grid == true)
   {
      canvas.SetGridx();
      canvas.SetGridy();
   }

   AddCanvas(canvas);
}

template <class PlotType> void PsFileHelper::Add4PanelPlot(PlotType *Histogram1, PlotType *Histogram2,
   PlotType *Histogram3, PlotType *Histogram4, string PlotOption, bool LogY, bool LogZ, bool Grid, bool LogX)
{
   TCanvas canvas;

   canvas.Divide(2, 2);

   PlotType *Histograms[4] = {Histogram1, Histogram2, Histogram3, Histogram4};

   for(int i = 0; i < 4; i++)
   {
      if(Histograms[i] == NULL)
         continue;

      TVirtualPad *Pad = canvas.cd(i + 1);

      Histograms[i]->Draw(PlotOption.c_str());

      if(LogX == true)
         Pad->SetLogx();
      if(LogY == true)
         Pad->SetLogy();
      if(LogZ == true)
         Pad->SetLogz();

      if(Grid == true)
      {
         Pad->SetGridx();
         Pad->SetGridy();
      }
   }

   AddCanvas(canvas);
}

template <class PlotType> void PsFileHelper::AddPlot(PlotType &Histogram, string PlotOption, bool LogY, bool LogZ, bool Grid, bool LogX)
{
   AddPlot(&Histogram, PlotOption, LogY, LogZ, Grid, LogX);
}

template <class PlotType> void Add4PanelPlot(PlotType &Histogram1, PlotType &Histogram2,
   PlotType &Histogram3, PlotType &Histogram4, string PlotOption, bool LogY, bool LogZ, bool Grid, bool LogX)
{
   Add4PanelPlot(&Histogram1, &Histogram2, &Histogram3, &Histogram4, PlotOption, LogY, LogZ, Grid, LogX);
}

template <class PlotType> void PsFileHelper::AddNormalizedPlot(PlotType *Histogram, string PlotOption,
   bool LogY, bool LogZ, bool Grid)
{
   if(Histogram == NULL)
      return;

   TCanvas canvas;

   Histogram->DrawNormalized(PlotOption.c_str());

   if(Histogram->GetMaximum() > 1e-10)
   {
      if(LogY == true)
         canvas.SetLogy();
      if(LogZ == true)
         canvas.SetLogz();
   }
   if(Grid == true)
   {
      canvas.SetGridx();
      canvas.SetGridy();
   }

   AddCanvas(canvas);
}

template <class PlotType> void PsFileHelper::AddNormalizedPlot(PlotType &Histogram, string PlotOption,
   bool LogY, bool LogZ, bool Grid)
{
   AddNormalizedPlot(&Histogram, PlotOption, LogY, LogZ, Grid);
}

template <class PlotType> void PsFileHelper::AddPlotWithText(PlotType *Histogram, string Text,
   string PlotOption, double X, double Y, double TextSize)
{
   TCanvas canvas;

   Histogram->Draw(PlotOption.c_str());

   AddCanvasWithText(canvas, Text, X, Y, TextSize);
}

template <class PlotType> void PsFileHelper::AddPlotWithText(PlotType &Histogram, string Text,
   string PlotOption, double X, double Y, double TextSize)
{
   AddPlotWithText(&Histogram, Text, PlotOption, X, Y, TextSize);
}

void PsFileHelper::AddHistogramFromFile(TFile &File, string HistogramName, string PlotOption, bool LogY,
   bool LogZ, bool Grid, bool LogX)
{
   TH1 *Histogram = (TH1 *)File.Get(HistogramName.c_str());
   if(Histogram == NULL)
      return;

   AddPlot(Histogram, PlotOption, LogY, LogZ, Grid, LogX);
}

void PsFileHelper::Add4PanelHistogramFromFile(TFile &File, string HistogramName1, string HistogramName2,
   string HistogramName3, string HistogramName4, string PlotOption, bool LogY, bool LogZ, bool Grid, bool LogX)
{
   TH1 *Histograms[4];

   Histograms[0] = (TH1 *)File.Get(HistogramName1.c_str());
   Histograms[1] = (TH1 *)File.Get(HistogramName2.c_str());
   Histograms[2] = (TH1 *)File.Get(HistogramName3.c_str());
   Histograms[3] = (TH1 *)File.Get(HistogramName4.c_str());

   Add4PanelPlot(Histograms[0], Histograms[1], Histograms[2], Histograms[3], PlotOption, LogY, LogZ, Grid, LogX);
}

void PsFileHelper::AddGraphFromFile(TFile &File, string GraphName, string PlotOption, bool LogY, bool LogZ,
   bool Grid, bool LogX)
{
   TGraph *Graph = (TGraph *)File.Get(GraphName.c_str());
   if(Graph == NULL)
      return;

   AddPlot(Graph, PlotOption, LogY, LogZ, Grid, LogX);
}

void PsFileHelper::AddCanvas(TCanvas *Canvas)
{
   if(Canvas == NULL)
      return;

   Canvas->Print(FileName.c_str(), Option.c_str());
}

void PsFileHelper::AddCanvas(TCanvas &Canvas)
{
   AddCanvas(&Canvas);
}

void PsFileHelper::AddCanvasWithText(TCanvas *Canvas, string Text, double X, double Y, double TextSize)
{
   Canvas->cd();

   TLatex text(X, Y, Text.c_str());
   text.SetTextSize(TextSize);
   text.Draw();

   Canvas->Print(FileName.c_str(), Option.c_str());
}

void PsFileHelper::AddCanvasWithText(TCanvas &Canvas, string Text, double X, double Y, double TextSize)
{
   AddCanvasWithText(&Canvas, Text, X, Y, TextSize);
}

void PsFileHelper::AddTextPage(string Text, double X, double Y, double TextSize)
{
   TCanvas canvas;

   TLatex text(X, Y, Text.c_str());
   text.SetTextSize(TextSize);
   text.Draw();

   canvas.Print(FileName.c_str(), Option.c_str());
}

void PsFileHelper::AddTextPage(vector<string> Text, double X, double Y, double TextSize)
{
   TCanvas canvas;

   vector<TLatex *> texts;

   for(unsigned int i = 0; i < Text.size(); i++)
   {
      texts.push_back(new TLatex(X, Y - i * 0.07, Text[i].c_str()));
      texts[i]->SetName(Form("TextLine%d", i));
      texts[i]->SetTextSize(TextSize);
   }

   for(unsigned int i = 0; i < Text.size(); i++)
      texts[i]->Draw();

   canvas.Print(FileName.c_str(), Option.c_str());

   for(unsigned int i = 0; i < Text.size(); i++)
      delete texts[i];
   texts.clear();
}

void PsFileHelper::AddTimeStampPage()
{
   time_t CurrentTime = time(NULL);

   string str = "Generated at ";
   str = str + ctime(&CurrentTime);

   AddTextPage(str, 0.03);
}

#endif



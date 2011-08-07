//---------------------------------------------------------------------------
#ifndef SlidePreparationHelper_6671_AQJAHNWIGTJAWKRJCVEKSDHNVKHNCGVKFEANFEWK
#define SlidePreparationHelper_6671_AQJAHNWIGTJAWKRJCVEKSDHNVKHNCGVKFEANFEWK
//---------------------------------------------------------------------------
// Slide preparation helper, 6671 version
// An attempt to simplify time needed to do the same repetitive tasks
//    in making basic adjustments to the Figures (SetStats(0), etc.)
//---------------------------------------------------------------------------
#include <string>
using namespace std;   // meow!
//---------------------------------------------------------------------------
#include "TFile.h"
#include "TH1.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TClass.h"
//---------------------------------------------------------------------------
class PlotRecord;
class PlotList;
//---------------------------------------------------------------------------
void CreateOnePanelPlot(PlotList Plot, string FileNameBase);
void CreateTwoPanelPlot(PlotList Left, PlotList Right, string FileNameBase);
void CreateThreePanelPlot(PlotList Left, PlotList Middle, PlotList Right, string FileNameBase);
void CreateTwoByTwoPanelPlot(PlotList UpperLeft, PlotList UpperRight, PlotList LowerLeft, PlotList LowerRight,
   string FileNameBase);
void CreateTwoByThreePanelPlot(PlotList UpperLeft, PlotList UpperCentral, PlotList UpperRight,
   PlotList LowerLeft, PlotList LowerCentral, PlotList LowerRight, string FileNameBase);
//---------------------------------------------------------------------------
class PlotRecord
{
public:
   bool IsHistogram;
   TObject *Figure;
   string Title;
   string XTitle;
   string YTitle;
   string Label;
   string Option;
   bool LogY;
   bool LogZ;
   bool LogX;
   bool Grid;
public:
   PlotRecord();
   PlotRecord(TFile *f, string name, string title, string xtitle, string ytitle,
      string label, string option = "", bool logy = false, bool logz = false, bool grid = false,
      bool logx = false);
   PlotRecord(TH1 *h, string title, string xtitle, string ytitle,
      string label, string option = "", bool logy = false, bool logz = false, bool grid = false,
      bool logx = false);
   PlotRecord(TGraph *g, string title, string xtitle, string ytitle,
      string label, string option = "", bool logy = false, bool logz = false, bool grid = false,
      bool logx = false);
   ~PlotRecord() {}
   void Draw(TCanvas *Canvas, int SubPad = -1);
};
//---------------------------------------------------------------------------
class PlotList
{
public:
   vector<PlotRecord> PlotRecords;
   bool WantLegend;
   TLegend *Legend;
   double X1, X2, Y1, Y2;
public:
   PlotList(bool legend = false, double x1 = 0.5, double y1 = 0.8, double x2 = 0.8, double y2 = 0.5);
   PlotList(PlotRecord r1, bool legend = false,
      double x1 = 0.5, double y1 = 0.8, double x2 = 0.8, double y2 = 0.5);
   PlotList(PlotRecord r1, PlotRecord r2, bool legend = false,
      double x1 = 0.5, double y1 = 0.8, double x2 = 0.8, double y2 = 0.5);
   PlotList(PlotRecord r1, PlotRecord r2, PlotRecord r3, bool legend = false,
      double x1 = 0.5, double y1 = 0.8, double x2 = 0.8, double y2 = 0.5);
   PlotList(PlotRecord r1, PlotRecord r2, PlotRecord r3, PlotRecord r4, bool legend = false,
      double x1 = 0.5, double y1 = 0.8, double x2 = 0.8, double y2 = 0.5);
   PlotList(PlotRecord r1, PlotRecord r2, PlotRecord r3, PlotRecord r4, PlotRecord r5, bool legend = false,
      double x1 = 0.5, double y1 = 0.8, double x2 = 0.8, double y2 = 0.5);
   PlotList(PlotRecord r1, PlotRecord r2, PlotRecord r3, PlotRecord r4, PlotRecord r5, PlotRecord r6,
      bool legend = false, double x1 = 0.5, double y1 = 0.8, double x2 = 0.8, double y2 = 0.5);
   ~PlotList();
   void Draw(TCanvas *Canvas, int SubPad = -1);
};
//---------------------------------------------------------------------------
PlotRecord::PlotRecord()
{
   Figure = NULL;
   Title = "";
   XTitle = "";
   YTitle = "";
   Label = "";
   Option = "";
   LogY = false;
   LogZ = false;
   Grid = false;
   LogX = false;
}
//---------------------------------------------------------------------------
PlotRecord::PlotRecord(TFile *f, string name, string title, string xtitle, string ytitle,
   string label, string option, bool logy, bool logz, bool grid, bool logx)
{
   Figure = NULL;

   if(f == NULL)
      return;

   Figure = (TObject *)f->Get(name.c_str());

   string ClassName = Figure->IsA()->GetName();
   if(ClassName[0] == 'T' && ClassName[1] == 'H')   // not rigorous!
      IsHistogram = true;
   else
      IsHistogram = false;
   
   Title = title;
   XTitle = xtitle;
   YTitle = ytitle;
   Label = label;
   Option = option;
   LogY = logy;
   LogZ = logz;
   Grid = grid;
   LogX = logx;
}
//---------------------------------------------------------------------------
PlotRecord::PlotRecord(TH1 *h, string title, string xtitle, string ytitle,
   string label, string option, bool logy, bool logz, bool grid, bool logx)
{
   IsHistogram = true;
   Figure = h;
   Title = title;
   XTitle = xtitle;
   YTitle = ytitle;
   Label = label;
   Option = option;
   LogY = logy;
   LogZ = logz;
   Grid = grid;
   LogX = logx;
}
//---------------------------------------------------------------------------
PlotRecord::PlotRecord(TGraph *g, string title, string xtitle, string ytitle,
   string label, string option, bool logy, bool logz, bool grid, bool logx)
{
   IsHistogram = false;
   Figure = g;
   Title = title;
   XTitle = xtitle;
   YTitle = ytitle;
   Label = label;
   Option = option;
   LogY = logy;
   LogZ = logz;
   Grid = grid;
   LogX = logx;
}
//---------------------------------------------------------------------------
void PlotRecord::Draw(TCanvas *Canvas, int SubPad)
{
   if(Figure != NULL)
   {
      if(SubPad > 0)
         Canvas->cd(SubPad);

      if(IsHistogram == true)
      {
         if(Title != "")    ((TH1D *)Figure)->SetTitle(Title.c_str());
         if(XTitle != "")   ((TH1D *)Figure)->GetXaxis()->SetTitle(XTitle.c_str());
         if(YTitle != "")   ((TH1D *)Figure)->GetYaxis()->SetTitle(YTitle.c_str());

         ((TH1D *)Figure)->Draw(Option.c_str());
         ((TH1D *)Figure)->SetStats(0);
      }
      else
      {
         if(Title != "")    ((TGraph *)Figure)->SetTitle(Title.c_str());
         if(XTitle != "")   ((TGraph *)Figure)->GetXaxis()->SetTitle(XTitle.c_str());
         if(YTitle != "")   ((TGraph *)Figure)->GetYaxis()->SetTitle(YTitle.c_str());

         ((TGraph *)Figure)->Draw(Option.c_str());
      }

      if(LogX == true)   Canvas->cd(SubPad)->SetLogx();
      if(LogY == true)   Canvas->cd(SubPad)->SetLogy();
      if(LogZ == true)   Canvas->cd(SubPad)->SetLogz();
      
      if(SubPad > 0 && LogX == true)   Canvas->SetLogx();
      if(SubPad > 0 && LogY == true)   Canvas->SetLogy();
      if(SubPad > 0 && LogZ == true)   Canvas->SetLogz();
   }
}
//---------------------------------------------------------------------------
PlotList::PlotList(bool legend, double x1, double y1, double x2, double y2)
{
   WantLegend = legend;
   Legend = NULL;

   X1 = x1;   X2 = x2;
   Y1 = y1;   Y2 = y2;
}
//---------------------------------------------------------------------------
PlotList::PlotList(PlotRecord r1, bool legend, double x1, double y1, double x2, double y2)
{
   PlotRecords.push_back(r1);
   WantLegend = legend;
   Legend = NULL;

   X1 = x1;   X2 = x2;
   Y1 = y1;   Y2 = y2;
}
//---------------------------------------------------------------------------
PlotList::PlotList(PlotRecord r1, PlotRecord r2, bool legend, double x1, double y1, double x2, double y2)
{
   PlotRecords.push_back(r1);
   PlotRecords.push_back(r2);
   WantLegend = legend;
   Legend = NULL;

   X1 = x1;   X2 = x2;
   Y1 = y1;   Y2 = y2;
}
//---------------------------------------------------------------------------
PlotList::PlotList(PlotRecord r1, PlotRecord r2, PlotRecord r3, bool legend,
   double x1, double y1, double x2, double y2)
{
   PlotRecords.push_back(r1);
   PlotRecords.push_back(r2);
   PlotRecords.push_back(r3);
   WantLegend = legend;
   Legend = NULL;

   X1 = x1;   X2 = x2;
   Y1 = y1;   Y2 = y2;
}
//---------------------------------------------------------------------------
PlotList::PlotList(PlotRecord r1, PlotRecord r2, PlotRecord r3, PlotRecord r4,
   bool legend, double x1, double y1, double x2, double y2)
{
   PlotRecords.push_back(r1);
   PlotRecords.push_back(r2);
   PlotRecords.push_back(r3);
   PlotRecords.push_back(r4);
   WantLegend = legend;
   Legend = NULL;

   X1 = x1;   X2 = x2;
   Y1 = y1;   Y2 = y2;
}
//---------------------------------------------------------------------------
PlotList::PlotList(PlotRecord r1, PlotRecord r2, PlotRecord r3, PlotRecord r4, PlotRecord r5,
   bool legend, double x1, double y1, double x2, double y2)
{
   PlotRecords.push_back(r1);
   PlotRecords.push_back(r2);
   PlotRecords.push_back(r3);
   PlotRecords.push_back(r4);
   PlotRecords.push_back(r5);
   WantLegend = legend;
   Legend = NULL;

   X1 = x1;   X2 = x2;
   Y1 = y1;   Y2 = y2;
}
//---------------------------------------------------------------------------
PlotList::PlotList(PlotRecord r1, PlotRecord r2, PlotRecord r3, PlotRecord r4, PlotRecord r5, PlotRecord r6,
   bool legend, double x1, double y1, double x2, double y2)
{
   PlotRecords.push_back(r1);
   PlotRecords.push_back(r2);
   PlotRecords.push_back(r3);
   PlotRecords.push_back(r4);
   PlotRecords.push_back(r5);
   PlotRecords.push_back(r6);
   WantLegend = legend;
   Legend = NULL;

   X1 = x1;   X2 = x2;
   Y1 = y1;   Y2 = y2;
}
//---------------------------------------------------------------------------
void PlotList::Draw(TCanvas *Canvas, int SubPad)
{
   if(PlotRecords.size() == 0)
      return;

   for(int i = 0; i < (int)PlotRecords.size(); i++)
   {
      string OptionTemp = PlotRecords[i].Option;

      if(PlotRecords[i].IsHistogram == true)
      {
         if(i != 0 && OptionTemp != "")
            PlotRecords[i].Option = PlotRecords[i].Option + " same";
         else if(i != 0 && OptionTemp == "")
            PlotRecords[i].Option = "same";
      }

      if(PlotRecords[i].IsHistogram == true)
         ((TH1D *)PlotRecords[i].Figure)->SetLineColor(i + 1);
      else
         ((TGraph *)PlotRecords[i].Figure)->SetLineColor(i + 1);
      PlotRecords[i].Draw(Canvas, SubPad);

      PlotRecords[i].Option = OptionTemp;
   }

   if(WantLegend == true)
   {
      if(Legend != NULL)
         delete Legend;

      Legend = new TLegend(X1, Y1, X2, Y2);

      Legend->SetFillColor(0);

      for(int i = 0; i < (int)PlotRecords.size(); i++)
         Legend->AddEntry(PlotRecords[i].Figure, PlotRecords[i].Label.c_str(), "lpf");

      Legend->Draw();
   }
}
//---------------------------------------------------------------------------
PlotList::~PlotList()
{
   if(Legend != NULL)
      delete Legend;
}
//---------------------------------------------------------------------------
void CreateOnePanelPlot(PlotList Plot, string FileNameBase)
{
   TCanvas Canvas("C", "C", 1024, 1024);

   Plot.Draw(&Canvas, 1);

   Canvas.SaveAs((FileNameBase + ".png").c_str());
   Canvas.SaveAs((FileNameBase + ".C").c_str());
   Canvas.SaveAs((FileNameBase + ".eps").c_str());
}
//---------------------------------------------------------------------------
void CreateTwoPanelPlot(PlotList Left, PlotList Right, string FileNameBase)
{
   TCanvas Canvas("C", "C", 1024, 512);

   Canvas.Divide(2);

   Left.Draw(&Canvas, 1);
   Right.Draw(&Canvas, 2);

   Canvas.SaveAs((FileNameBase + ".png").c_str());
   Canvas.SaveAs((FileNameBase + ".C").c_str());
   Canvas.SaveAs((FileNameBase + ".eps").c_str());
}
//---------------------------------------------------------------------------
void CreateThreePanelPlot(PlotList Left, PlotList Middle, PlotList Right, string FileNameBase)
{
   TCanvas Canvas("C", "C", 512 * 3, 512);

   Canvas.Divide(3);

   Left.Draw(&Canvas, 1);
   Middle.Draw(&Canvas, 2);
   Right.Draw(&Canvas, 3);

   Canvas.SaveAs((FileNameBase + ".png").c_str());
   Canvas.SaveAs((FileNameBase + ".C").c_str());
   Canvas.SaveAs((FileNameBase + ".eps").c_str());
}
//---------------------------------------------------------------------------
void CreateTwoByTwoPanelPlot(PlotList UpperLeft, PlotList UpperRight, PlotList LowerLeft, PlotList LowerRight,
   string FileNameBase)
{
   TCanvas Canvas("C", "C", 1024, 1024);

   Canvas.Divide(2, 2);

   UpperLeft.Draw(&Canvas, 1);
   UpperRight.Draw(&Canvas, 2);
   LowerLeft.Draw(&Canvas, 3);
   LowerRight.Draw(&Canvas, 4);

   Canvas.SaveAs((FileNameBase + ".png").c_str());
   Canvas.SaveAs((FileNameBase + ".C").c_str());
   Canvas.SaveAs((FileNameBase + ".eps").c_str());
}
//---------------------------------------------------------------------------
void CreateTwoByThreePanelPlot(PlotList UpperLeft, PlotList UpperCentral, PlotList UpperRight,
   PlotList LowerLeft, PlotList LowerCentral, PlotList LowerRight, string FileNameBase)
{
   TCanvas Canvas("C", "C", 512 * 3, 512 * 2);

   Canvas.Divide(3, 2);

   UpperLeft.Draw(&Canvas, 1);
   UpperCentral.Draw(&Canvas, 2);
   UpperRight.Draw(&Canvas, 3);
   LowerLeft.Draw(&Canvas, 4);
   LowerCentral.Draw(&Canvas, 5);
   LowerRight.Draw(&Canvas, 6);

   Canvas.SaveAs((FileNameBase + ".png").c_str());
   Canvas.SaveAs((FileNameBase + ".C").c_str());
   Canvas.SaveAs((FileNameBase + ".eps").c_str());
}
//---------------------------------------------------------------------------
#endif



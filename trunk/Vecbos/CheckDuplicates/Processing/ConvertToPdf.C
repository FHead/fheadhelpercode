#include <vector>
#include <string>
using namespace std;

#include "TFile.h"
#include "TList.h"
#include "TROOT.h"
#include "TStyle.h"

#include "PlotHelper.h"

void ConvertToPdf()
{
   gROOT->SetStyle("Plain");
   TStyle gStyle;
   gStyle.SetOptStat("roumen");

   TFile F("AllRootFiles.root");
   PsFileHelper PsFile("AllRootFiles.ps");

   PsFile.AddTextPage("Monitoring duplicate events");

   vector<string> ExplanationText;
   ExplanationText.push_back("Each entry is one event, and the x axis is");
   ExplanationText.push_back("   the number of times that event occurs in the vecbos ntuple set.");
   ExplanationText.push_back("Each histogram is one run.");
   PsFile.AddTextPage(ExplanationText);

   TIter next(F.GetListOfKeys());

   for(TObject *object = next(); object != NULL; object = next())
      PsFile.AddHistogramFromFile(F, object->GetName(), "hist text00", true);

   PsFile.AddTimeStampPage();

   PsFile.Close();
}


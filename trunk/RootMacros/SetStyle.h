#ifndef SetStyle_h_ikdofqwjito3jgthyqiwko3jhigtyq2jghufolqjgthy
#define SetStyle_h_ikdofqwjito3jgthyqiwko3jhigtyq2jghufolqjgthy

#include "TStyle.h"
#include "TROOT.h"
#include "TColor.h"

void SetStyle()
{
   gStyle->SetFrameBorderMode(0);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetPadBorderMode(0);
   gStyle->SetPadColor(0);
   gStyle->SetCanvasColor(0);
   gStyle->SetStatColor(0);
   gStyle->SetFillColor(0);

   gStyle->SetPaperSize(20,26);
   gStyle->SetPadTopMargin(0.05);
   gStyle->SetPadRightMargin(0.05);
   gStyle->SetPadBottomMargin(0.16);
   gStyle->SetPadLeftMargin(0.12);

   gStyle->SetTextFont(132);
   gStyle->SetTextSize(0.08);
   gStyle->SetLabelFont(132,"x");
   gStyle->SetLabelFont(132,"y");
   gStyle->SetLabelFont(132,"z");
   gStyle->SetLabelSize(0.05,"x");
   gStyle->SetTitleSize(0.06,"x");
   gStyle->SetLabelSize(0.05,"y");
   gStyle->SetTitleSize(0.06,"y");
   gStyle->SetLabelSize(0.05,"z");
   gStyle->SetTitleSize(0.06,"z");

   gStyle->SetMarkerStyle(20);
   gStyle->SetHistLineWidth(1.85);
   // gStyle->SetHistLineWidth(3.85);
   gStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

   gStyle->SetErrorX(0.001);

   gStyle->SetOptTitle(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(0);

   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);

   gROOT->SetStyle("Plain");
   gStyle->SetOptStat(1100);
   gStyle->SetOptStat(1);
   gStyle->SetOptFit(1111);
   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);

   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);
}

#endif

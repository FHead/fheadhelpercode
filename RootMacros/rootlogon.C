{
   cout << endl;
   cout << "Welcome to FHead-customized ROOT!!" << endl;
   cout << endl;

   // gROOT->SetStyle("Plain");
   gROOT->ProcessLine(".include $HOME/RootMacros");

   gStyle->SetFrameBorderMode(0);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetPadBorderMode(0);
   gStyle->SetPadColor(0);
   gStyle->SetCanvasColor(0);
   gStyle->SetStatColor(0);

   gStyle->SetPaperSize(20,26);
   gStyle->SetCanvasDefH(1024);
   gStyle->SetCanvasDefW(1024 * 1.05);
   gStyle->SetPadTopMargin(0.1);
   gStyle->SetPadRightMargin(0.15 / 1.05);
   gStyle->SetPadBottomMargin(0.1);
   gStyle->SetPadLeftMargin(0.1);

   // gStyle->SetTextFont(42);
   // gStyle->SetTextSize(0.08);
   gStyle->SetLabelFont(42,"x");
   gStyle->SetLabelFont(42,"y");
   gStyle->SetLabelFont(42,"z");
   gStyle->SetLabelSize(0.035,"x");
   gStyle->SetTitleSize(0.035,"x");
   gStyle->SetLabelSize(0.035,"y");
   gStyle->SetTitleSize(0.035,"y");
   gStyle->SetLabelSize(0.035,"z");
   gStyle->SetTitleSize(0.035,"z");
   gStyle->SetTitleOffset(1.10,"x");
   gStyle->SetTitleOffset(1.20,"y");
   gStyle->SetTitleOffset(1.28,"z");

   gStyle->SetMarkerStyle(20);
   gStyle->SetHistLineWidth(1);
   // gStyle->SetHistLineWidth(1.85);
   // gStyle->SetHistLineWidth(3.85);
   gStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

   gStyle->SetErrorX(0.001);

   // gStyle->SetOptTitle(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(0);

   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);

   gStyle->SetOptStat(1100);
   gStyle->SetOptStat(1);
   gStyle->SetOptFit(1111);
   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);

   gStyle->SetLegendFont(42);
   gStyle->SetLegendBorderSize(0);
   gStyle->SetLegendFillColor(0);

   // nice palette!
   // courtesy of Segev, http://ultrahigh.org/2007/08/20/making-pretty-root-color-palettes/

   const Int_t NRGBs = 5;
   const Int_t NCont = 99;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);

   // pythia 8 environmental variables
   // gSystem->ExpandPathName("$PYTHIA8DATA");
   // gSystem->Load("$PYTHIA8/lib/libpythia8");
   // gSystem->Load("libEG");
   // gSystem->Load("libEGPythia8");

   gStyle->SetOptFit(111);
   // gStyle->SetPaperSize(24, 16);
}

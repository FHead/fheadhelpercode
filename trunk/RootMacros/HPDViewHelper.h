//----------------------------------------------------------------------------
#ifndef HPDVIEWHELPER_6714_AIWEHNGVKHRGKIKGVAIKGKRAJHSKAHRGWIP
#define HPDVIEWHELPER_6714_AIWEHNGVKHRGKIKGVAIKGKRAJHSKAHRGWIP
//----------------------------------------------------------------------------
// HPDViewHelper class --- upgraded to TH2Poly!
// Author: Yi Chen.  April 28, 2011 (old version some time in mid-2010)
//
// A class that contains bins that correspond to every channel in HB/HE
// Simple syntax:
//    HPDViewHelper Histograms;
//    Histograms.InitializeHistograms() --- makes bins, titles, etc.; called automatically in constructor
//    Histograms.Fill(ieta, iphi, depth, energy = 1) --- fills some energy in the right bin
//    Histograms[RBXIndex][HPDIndex] --- returns individual histograms
//    Histograms.ClearContents() --- clears all bin contents
//----------------------------------------------------------------------------
#include <string>
#include <cmath>
#include <cassert>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;
//----------------------------------------------------------------------------
#include "TH2Poly.h"
//----------------------------------------------------------------------------
struct ChannelIndex;
class HPDViewHelper;
//----------------------------------------------------------------------------
struct ChannelIndex
{
   int AbsIEta;
   int Depth;
   bool operator <(const ChannelIndex other) const
   {
      if(AbsIEta < other.AbsIEta)   return true;
      if(AbsIEta > other.AbsIEta)   return false;
      
      if(Depth < other.Depth)   return true;
      if(Depth > other.Depth)   return false;

      return false;
   }
};
//----------------------------------------------------------------------------
class HPDViewHelper
{
public:
   string Name;
   TH2Poly HPDs[72][4];
   map<ChannelIndex, int> BinIndexMapping[2][4];   // HB/HE, Scheme
public:
   HPDViewHelper();
   ~HPDViewHelper();
   void ReadBinIndexMapping(string FileName = "HPDMapping.txt");
   void InitializeHistograms();
   void CleanHistograms();
   TH2Poly *operator [](int RBXIndex);
   int IsBarrel(int IEta, int IPhi, int Depth);
   int GetRBXIndex(int IEta, int IPhi, int Depth);
   int GetHPDIndex(int IEta, int IPhi, int Depth);
   int GetBinIndex(int IEta, int IPhi, int Depth, int Scheme = -1);
   void Fill(int IEta, int IPhi, int Depth, double Weight = 1);
   void UnifyMaxBin();
   double GetMaxValue();
   double GetMaxValue(int RBXIndex, int HPDIndex);
   void SetMaxValue(double Value);
};
//----------------------------------------------------------------------------
HPDViewHelper::HPDViewHelper()
{
   Name = "";
   InitializeHistograms();
   ReadBinIndexMapping("HPDMapping.txt");
}
//----------------------------------------------------------------------------
HPDViewHelper::~HPDViewHelper()
{
}
//----------------------------------------------------------------------------
void HPDViewHelper::ReadBinIndexMapping(string FileName)
{
   ifstream in(FileName.c_str());

   char chtemp[10240];
   while(in)
   {
      in.getline(chtemp, 10239, '\n');

      if(chtemp[0] == '\0' || chtemp[0] == '#' || chtemp[0] == '\n')   // either empty line or comments
         continue;

      stringstream str(chtemp);

      string SubDetector = "";
      int Scheme = -1;
      int Bin = -1;
      int IEta = -1;
      int Depth = -1;
      
      str >> SubDetector >> Scheme >> Bin >> IEta >> Depth;

      int SubDetectorIndex = 0;
      if(SubDetector == "HB")
         SubDetectorIndex = 0;
      else if(SubDetector == "HE")
         SubDetectorIndex = 1;
      else
         continue;   // something is wrong

      ChannelIndex Index;
      Index.AbsIEta = abs(IEta);
      Index.Depth = Depth;

      BinIndexMapping[SubDetectorIndex][Scheme-1].insert(pair<ChannelIndex, int>(Index, Bin));
   }

   in.close();
}
//----------------------------------------------------------------------------
void HPDViewHelper::InitializeHistograms()
{
   double CellCenterDistance = 1;
   double CellSize = 0.9 / sqrt(3);

   double CellPositionX[18] = {-2, -2, -2, -1, -1, -1, -1, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2};
   double CellPositionY[18] = {1, 0, -1, 1.5, 0.5, -0.5, -1.5, 2, 1, -1, -2, 1.5, 0.5, -0.5, -1.5, 1, 0, -1};
   for(int i = 0; i < 18; i++)
   {
      CellPositionX[i] = CellPositionX[i] * CellCenterDistance * sqrt(3) / 2;
      CellPositionY[i] = CellPositionY[i] * CellCenterDistance;
   }

   double CellVertexDisplacementX[6] = {0.5, -0.5, -1, -0.5, 0.5, 1};
   double CellVertexDisplacementY[6] = {-1, -1, 0, 1, 1, 0};
   for(int i = 0; i < 6; i++)
   {
      CellVertexDisplacementX[i] = CellVertexDisplacementX[i] * CellSize;
      CellVertexDisplacementY[i] = CellVertexDisplacementY[i] * CellSize * sqrt(3) / 2;
   }

   for(int i = 0; i < 72; i++)
   {
      for(int j = 0; j < 4; j++)
      {
         for(int k = 0; k < 18; k++)
         {
            double CellCoordinatesX[6] = {0};
            double CellCoordinatesY[6] = {0};

            for(int l = 0; l < 6; l++)
            {
               CellCoordinatesX[l] = CellPositionX[k] + CellVertexDisplacementX[l];
               CellCoordinatesY[l] = CellPositionY[k] + CellVertexDisplacementY[l];
            }

            HPDs[i][j].AddBin(6, CellCoordinatesX, CellCoordinatesY);
         }

         double SetMaxBinX[3] = {0, 0.00001, 0};
         double SetMaxBinY[3] = {0, 0.00001, 0.00001};
         HPDs[i][j].AddBin(3, SetMaxBinX, SetMaxBinY);
      }
   }

   for(int i = 0; i < 72; i++)
   {
      string SubDetectorString = "";
      if(i < 18)   SubDetectorString = "HBP";
      else if(i < 36)   SubDetectorString = "HBM";
      else if(i < 54)   SubDetectorString = "HEP";
      else if(i < 72)   SubDetectorString = "HEM";
      else              SubDetectorString = "Unknown";

      for(int j = 0; j < 4; j++)
      {
         HPDs[i][j].SetTitle(Form("%s %d, HPD %d", SubDetectorString.c_str(), i % 18 + 1, j + 1));
         HPDs[i][j].SetStats(0);
         HPDs[i][j].SetMarkerSize(2);
      }
   }

   CleanHistograms();
}
//----------------------------------------------------------------------------
void HPDViewHelper::CleanHistograms()
{
   for(int i = 0; i < 72; i++)
      for(int j = 0; j < 4; j++)
         HPDs[i][j].ClearBinContents();
}
//----------------------------------------------------------------------------
TH2Poly *HPDViewHelper::operator [](int RBXIndex)
{
   if(RBXIndex < 0 || RBXIndex >= 72)
      return NULL;
   return HPDs[RBXIndex];
}
//----------------------------------------------------------------------------
int HPDViewHelper::IsBarrel(int IEta, int IPhi, int Depth)
{
   bool Result = true;
   if(fabs(IEta) > 16)
      Result = false;
   if(fabs(IEta) == 16 && Depth > 2)
      Result = false;

   return Result;
}
//----------------------------------------------------------------------------
int HPDViewHelper::GetRBXIndex(int IEta, int IPhi, int Depth)
{
   int Side = 1;
   if(IEta < 0)
      Side = -1;

   if(IPhi >= 71)
      IPhi = IPhi - 72;

   int Serial = (IPhi + 1) / 4;

   if(IsBarrel(IEta, IPhi, Depth) == true)
   {
      if(Side > 0)   return Serial;
      else           return Serial + 18;
   }
   else
   {
      if(Side > 0)   return Serial + 36;
      else           return Serial + 54;
   }

   return -1;
}
//----------------------------------------------------------------------------
int HPDViewHelper::GetHPDIndex(int IEta, int IPhi, int Depth)
{
   if(IsBarrel(IEta, IPhi, Depth) == true || abs(IEta) <= 20)   // part of HE is easy too
   {
      if(IPhi >= 71)
         IPhi = IPhi - 72;

      return (IPhi + 1) % 4;
   }
   else   // use HPD mapping to do the trick
   {
      bool ExistInRM1 = true;

      ChannelIndex index;
      index.AbsIEta = abs(IEta);
      index.Depth = Depth;

      if(BinIndexMapping[1][0].find(index) != BinIndexMapping[1][0].end())
         ExistInRM1 = true;
      else if(BinIndexMapping[1][1].find(index) != BinIndexMapping[1][1].end())
         ExistInRM1 = false;
      else
         return -1;   // something is wrong

      if(IPhi >= 71)
         IPhi = IPhi - 72;
      IPhi = IPhi + 1;
      IPhi = IPhi % 4;

      if(IPhi < 2)   // first half: RM 1, 2
      {
         if(ExistInRM1 == true)    return 0;
         else                      return 1;
      }
      else           // second half: RM 3, 4; ps. RM1 similar to RM4, RM2 similar to RM3
      {
         if(ExistInRM1 == false)   return 2;
         else                      return 3;
      }
   }

   return -1;
}
//----------------------------------------------------------------------------
int HPDViewHelper::GetBinIndex(int IEta, int IPhi, int Depth, int Scheme)
{
   int HPDIndex = GetHPDIndex(IEta, IPhi, Depth);

   if(Scheme < 0)
      Scheme = HPDIndex;

   assert(Scheme >= 0 && Scheme < 4);

   ChannelIndex Index;
   Index.AbsIEta = abs(IEta);
   Index.Depth = Depth;

   int SubdetectorIndex = 0;
   if(IsBarrel(IEta, IPhi, Depth) == false)
      SubdetectorIndex = 1;

   return BinIndexMapping[SubdetectorIndex][Scheme][Index];
}
//----------------------------------------------------------------------------
void HPDViewHelper::Fill(int IEta, int IPhi, int Depth, double Weight)
{
   int RBXIndex = GetRBXIndex(IEta, IPhi, Depth);
   int HPDIndex = GetHPDIndex(IEta, IPhi, Depth);
   int BinIndex = GetBinIndex(IEta, IPhi, Depth);

   double BinContent = HPDs[RBXIndex][HPDIndex].GetBinContent(BinIndex);
   HPDs[RBXIndex][HPDIndex].SetBinContent(BinIndex, BinContent + Weight);
}
//----------------------------------------------------------------------------
void HPDViewHelper::UnifyMaxBin()
{
   double MaxValue = 0;
   for(int i = 0; i < 72; i++)
      for(int j = 0; j < 4; j++)
         for(int k = 1; k <= 18; k++)
            if(MaxValue < HPDs[i][j].GetBinContent(k))
               MaxValue = HPDs[i][j].GetBinContent(k);

   for(int i = 0; i < 72; i++)
      for(int j = 0; j < 4; j++)
         HPDs[i][j].SetBinContent(19, MaxValue);
}
//----------------------------------------------------------------------------
double HPDViewHelper::GetMaxValue()
{
   double MaxValue = 0;
   for(int i = 0; i < 72; i++)
      for(int j = 0; j < 4; j++)
         for(int k = 1; k <= 18; k++)
            if(MaxValue < HPDs[i][j].GetBinContent(k))
               MaxValue = HPDs[i][j].GetBinContent(k);
   return MaxValue;
}
//----------------------------------------------------------------------------
double HPDViewHelper::GetMaxValue(int RBXIndex, int HPDIndex)
{
   double MaxValue = 0;
   for(int k = 1; k <= 18; k++)
      if(MaxValue < HPDs[RBXIndex][HPDIndex].GetBinContent(k))
         MaxValue = HPDs[RBXIndex][HPDIndex].GetBinContent(k);
   return MaxValue;
}
//----------------------------------------------------------------------------
void HPDViewHelper::SetMaxValue(double Value)
{
   for(int i = 0; i < 72; i++)
      for(int j = 0; j < 4; j++)
         HPDs[i][j].SetBinContent(19, Value);
}
//----------------------------------------------------------------------------
#endif


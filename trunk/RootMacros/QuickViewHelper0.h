//-------------------------------------------------------------------------
#ifndef QuickViewHelper_6641_OAGJNGGERNJGKIBSSSSSSSSSSSGADFHAF
#define QuickViewHelper_6641_OAGJNGGERNJGKIBSSSSSSSSSSSGADFHAF
//-------------------------------------------------------------------------
// Quick view helper, 6441 version (version 0.0, pre-alpha)
//
// Author: Yi Chen, 6641
//
// This is a wonderful helper class designed to make "quick looks" much easier
//-------------------------------------------------------------------------
#include <map>
#include <string>
#include <vector>
#include <iostream>
//-------------------------------------------------------------------------
#include "TTree.h"
#include "TObjArray.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH1.h"
//-------------------------------------------------------------------------
#define BranchType_Double 0
#define BranchType_Integer 1
#define BranchType_Boolean 2
//-------------------------------------------------------------------------
struct HistogramRecord;
class QuickViewHelper;
//-------------------------------------------------------------------------
struct HistogramRecord
{
   std::string Name;
   bool Is1D;
   std::string Variable1;
   std::string Variable2;
   std::string Selection;
};
//-------------------------------------------------------------------------
class QuickViewHelper
{
private:
   TTree *Tree;
   std::map<std::string, double *> DoubleBranches;
   std::map<std::string, int *> IntegerBranches;
   std::map<std::string, bool *> BooleanBranches;
   std::map<std::string, int> BranchType;
   std::map<std::string, int> BranchSize;
private:
   std::map<std::string, TH1D *> Histogram1D;
   std::map<std::string, TH2D *> Histogram2D;
   std::map<std::string, HistogramRecord> HistogramRecords;
public:
   QuickViewHelper();
   ~QuickViewHelper();
   void Clear();
   bool LoadTree(TTree *tree);
   void PrintBranches();
   void Execute();
public:
   void RegisterHistogram1DSimple(std::string HistogramName, std::string Variable,
      int NumberOfBins, double Minimum, double Maximum, std::string Title = "",
      std::string Selection = "");
   void RegisterHistogram2DSimple(std::string HistogramName, std::string Variable1,
      int NumberOfBins1, double Minimum1, double Maximum1,
      std::string Variable2, int NumberOfBins2, double Minimum2, double Maximum2, std::string Title = "",
      std::string Selection = "");
   std::map<std::string, TH1D *> GetHistogram1D();
   std::map<std::string, TH2D *> GetHistogram2D();
   TH1 *GetHistogram(std::string HistogramName);
   TH1 *operator [](std::string HistogramName);
};
//-------------------------------------------------------------------------
QuickViewHelper::QuickViewHelper()
{
   Clear();
}
//-------------------------------------------------------------------------
QuickViewHelper::~QuickViewHelper()
{
   Clear();
}
//-------------------------------------------------------------------------
void QuickViewHelper::Clear()
{
   Tree = NULL;

   for(std::map<std::string, double *>::iterator iter = DoubleBranches.begin();
      iter != DoubleBranches.end(); iter++)
   {
      if(iter->second != NULL)
      {
         delete[] iter->second;
         iter->second = NULL;
      }
   }
   
   for(std::map<std::string, int *>::iterator iter = IntegerBranches.begin();
      iter != IntegerBranches.end(); iter++)
   {
      if(iter->second != NULL)
      {
         delete[] iter->second;
         iter->second = NULL;
      }
   }
   
   for(std::map<std::string, bool *>::iterator iter = BooleanBranches.begin();
      iter != BooleanBranches.end(); iter++)
   {
      if(iter->second != NULL)
      {
         delete[] iter->second;
         iter->second = NULL;
      }
   }
   
   DoubleBranches.clear();
   IntegerBranches.clear();
   BooleanBranches.clear();

   for(std::map<std::string, TH1D *>::iterator iter = Histogram1D.begin(); iter != Histogram1D.end(); iter++)
   {
      if(iter->second != NULL)
      {
         delete iter->second;
         iter->second = NULL;
      }
   }
   for(std::map<std::string, TH2D *>::iterator iter = Histogram2D.begin(); iter != Histogram2D.end(); iter++)
   {
      if(iter->second != NULL)
      {
         delete iter->second;
         iter->second = NULL;
      }
   }

   Histogram1D.clear();
   Histogram2D.clear();
}
//-------------------------------------------------------------------------
bool QuickViewHelper::LoadTree(TTree *tree)
{
   if(tree == NULL)
      return false;

   Clear();

   Tree = tree;

   // Loop over branches and leaves and allocate variables for getting stuff out of the tree
   TObjArray *BranchList = Tree->GetListOfBranches();
   int NumberOfBranches = BranchList->GetEntries();
   for(int i = 0; i < NumberOfBranches; i++)
   {
      if(BranchList->At(i)->IsA()->GetName() != TString("TBranch"))
         continue;
      
      TBranch *CurrentBranch = Tree->GetBranch(BranchList->At(i)->GetName());

      TObjArray *LeafList = CurrentBranch->GetListOfLeaves();
      int NumberOfLeaves = LeafList->GetEntries();
      for(int j = 0; j < NumberOfLeaves; j++)
      {
         TLeaf *CurrentLeaf = CurrentBranch->GetLeaf(LeafList->At(j)->GetName());
         
         if(NumberOfLeaves == 1)
         {
            if(CurrentLeaf->GetTypeName() == TString("Double_t"))
            {
               DoubleBranches.insert(std::pair<std::string, double *>(CurrentLeaf->GetName(),
                  new double[CurrentLeaf->GetLenStatic()]));
               BranchType.insert(std::pair<std::string, int>(CurrentLeaf->GetName(), BranchType_Double));
               BranchSize.insert(std::pair<std::string, int>(CurrentLeaf->GetName(), CurrentLeaf->GetLenStatic()));
            }
            if(CurrentLeaf->GetTypeName() == TString("Int_t"))
            {
               IntegerBranches.insert(std::pair<std::string, int *>(CurrentLeaf->GetName(),
                  new int[CurrentLeaf->GetLenStatic()]));
               BranchType.insert(std::pair<std::string, int>(CurrentLeaf->GetName(), BranchType_Integer));
               BranchSize.insert(std::pair<std::string, int>(CurrentLeaf->GetName(), CurrentLeaf->GetLenStatic()));
            }
            if(CurrentLeaf->GetTypeName() == TString("Bool_t"))
            {
               BooleanBranches.insert(std::pair<std::string, bool *>(CurrentLeaf->GetName(),
                  new bool[CurrentLeaf->GetLenStatic()]));
               BranchType.insert(std::pair<std::string, int>(CurrentLeaf->GetName(), BranchType_Boolean));
               BranchSize.insert(std::pair<std::string, int>(CurrentLeaf->GetName(), CurrentLeaf->GetLenStatic()));
            }

         }
      }
   }

   // Set branches
   for(int i = 0; i < NumberOfBranches; i++)
   {
      TBranch *CurrentBranch = Tree->GetBranch(BranchList->At(i)->GetName());
      
      if(CurrentBranch->GetListOfLeaves()->GetEntries() == 1)
      {
         TString LeafName = CurrentBranch->GetListOfLeaves()->At(0)->GetName();
         std::string Name = LeafName.Data();
         
         TLeaf *CurrentLeaf = CurrentBranch->GetLeaf(LeafName);

         if(CurrentLeaf->GetLenStatic() == 1 && CurrentLeaf->GetTypeName() == TString("Double_t"))
            Tree->SetBranchAddress(CurrentBranch->GetName(), &DoubleBranches[Name][0]);
         if(CurrentLeaf->GetLenStatic() == 1 && CurrentLeaf->GetTypeName() == TString("Int_t"))
            Tree->SetBranchAddress(CurrentBranch->GetName(), &IntegerBranches[Name][0]);
         if(CurrentLeaf->GetLenStatic() == 1 && CurrentLeaf->GetTypeName() == TString("Bool_t"))
            Tree->SetBranchAddress(CurrentBranch->GetName(), &BooleanBranches[Name][0]);
         if(CurrentLeaf->GetLenStatic() > 1 && CurrentLeaf->GetTypeName() == TString("Double_t"))
            Tree->SetBranchAddress(CurrentBranch->GetName(), DoubleBranches[Name]);
         if(CurrentLeaf->GetLenStatic() > 1 && CurrentLeaf->GetTypeName() == TString("Int_t"))
            Tree->SetBranchAddress(CurrentBranch->GetName(), IntegerBranches[Name]);
         if(CurrentLeaf->GetLenStatic() > 1 && CurrentLeaf->GetTypeName() == TString("Bool_t"))
            Tree->SetBranchAddress(CurrentBranch->GetName(), BooleanBranches[Name]);
      }
   }

   return true;
}
//-------------------------------------------------------------------------
void QuickViewHelper::PrintBranches()
{
   std::cout << "Double Branches: " << std::endl;
   for(std::map<std::string, double *>::iterator iter = DoubleBranches.begin();
      iter != DoubleBranches.end(); iter++)
   {
      if(BranchSize[iter->first] == 1)
         std::cout << "   " << iter->first << std::endl;
      else
         std::cout << "   " << iter->first << "[" << BranchSize[iter->first] << "]" << std::endl;
   }
   std::cout << std::endl;
   
   std::cout << "Integer Branches: " << std::endl;
   for(std::map<std::string, int *>::iterator iter = IntegerBranches.begin();
      iter != IntegerBranches.end(); iter++)
   {
      if(BranchSize[iter->first] == 1)
         std::cout << "   " << iter->first << std::endl;
      else
         std::cout << "   " << iter->first << "[" << BranchSize[iter->first] << "]" << std::endl;
   }
   std::cout << std::endl;
   
   std::cout << "Boolean Branches: " << std::endl;
   for(std::map<std::string, bool *>::iterator iter = BooleanBranches.begin();
      iter != BooleanBranches.end(); iter++)
   {
      if(BranchSize[iter->first] == 1)
         std::cout << "   " << iter->first << std::endl;
      else
         std::cout << "   " << iter->first << "[" << BranchSize[iter->first] << "]" << std::endl;
   }
   std::cout << std::endl;
}
//-------------------------------------------------------------------------
void QuickViewHelper::Execute()
{
   if(Tree == NULL)
      return;

   int NumberOfEntries = Tree->GetEntries();
   for(int iEntry = 0; iEntry < NumberOfEntries; iEntry++)
   {
      Tree->GetEntry(iEntry);

      for(std::map<std::string, HistogramRecord>::iterator iter = HistogramRecords.begin();
         iter != HistogramRecords.end(); iter++)
      {
         if(iter->second.Is1D == true)
         {
            TH1D *H = Histogram1D[iter->first];
            if(H == NULL)
               continue;

            for(int i = 0; i < BranchSize[iter->second.Variable1]; i++)
            {
               if(BranchType[iter->second.Variable1] == BranchType_Double)
                  H->Fill(DoubleBranches[iter->second.Variable1][i]);
               if(BranchType[iter->second.Variable1] == BranchType_Integer)
                  H->Fill(IntegerBranches[iter->second.Variable1][i]);
               if(BranchType[iter->second.Variable1] == BranchType_Boolean)
                  H->Fill(BooleanBranches[iter->second.Variable1][i]);
            }
         }
         else   // 2D
         {
            TH2D *H = Histogram2D[iter->first];
            if(H == NULL)
               continue;

            for(int i = 0; i < BranchSize[iter->second.Variable1]; i++)
            {
               double Variable1 = 1000000;
               double Variable2 = 1000000;

               if(BranchType[iter->second.Variable1] == BranchType_Double)
                  Variable1 = DoubleBranches[iter->second.Variable1][i];
               if(BranchType[iter->second.Variable1] == BranchType_Integer)
                  Variable1 = IntegerBranches[iter->second.Variable1][i];
               if(BranchType[iter->second.Variable1] == BranchType_Boolean)
                  Variable1 = BooleanBranches[iter->second.Variable1][i];

               if(BranchType[iter->second.Variable2] == BranchType_Double)
                  Variable2 = DoubleBranches[iter->second.Variable2][i];
               if(BranchType[iter->second.Variable2] == BranchType_Integer)
                  Variable2 = IntegerBranches[iter->second.Variable2][i];
               if(BranchType[iter->second.Variable2] == BranchType_Boolean)
                  Variable2 = BooleanBranches[iter->second.Variable2][i];

               H->Fill(Variable1, Variable2);
            }
         }
      }
   }
}
//-------------------------------------------------------------------------
void QuickViewHelper::RegisterHistogram1DSimple(std::string HistogramName, std::string Variable,
   int NumberOfBins, double Minimum, double Maximum, std::string Title,
   std::string Selection)
{
   HistogramRecord NewHistogram;

   NewHistogram.Name = HistogramName;
   NewHistogram.Is1D = true;
   NewHistogram.Variable1 = Variable;
   NewHistogram.Variable2 = "";
   NewHistogram.Selection = Selection;

   HistogramRecords.insert(std::pair<std::string, HistogramRecord>(HistogramName, NewHistogram));

   if(Title == "")
      Title = "A QuickViewHelper histogram of " + Variable + ";" + Variable;

   Histogram1D.insert(std::pair<std::string, TH1D *>(HistogramName,
      new TH1D(HistogramName.c_str(), Title.c_str(), NumberOfBins, Minimum, Maximum)));
}
//-------------------------------------------------------------------------
void QuickViewHelper::RegisterHistogram2DSimple(std::string HistogramName, std::string Variable1,
   int NumberOfBins1, double Minimum1, double Maximum1,
   std::string Variable2, int NumberOfBins2, double Minimum2, double Maximum2, std::string Title,
   std::string Selection)
{
   HistogramRecord NewHistogram;

   NewHistogram.Name = HistogramName;
   NewHistogram.Is1D = false;
   NewHistogram.Variable1 = Variable1;
   NewHistogram.Variable2 = Variable2;
   NewHistogram.Selection = Selection;

   HistogramRecords.insert(std::pair<std::string, HistogramRecord>(HistogramName, NewHistogram));
   
   if(Title == "")
      Title = "A QuickViewHelper histogram of " + Variable1 + " and " + Variable2
         + ";" + Variable1 + ";" + Variable2;

   Histogram2D.insert(std::pair<std::string, TH2D *>(HistogramName,
      new TH2D(HistogramName.c_str(), Title.c_str(), NumberOfBins1, Minimum1, Maximum1,
      NumberOfBins2, Minimum2, Maximum2)));
}
//-------------------------------------------------------------------------
std::map<std::string, TH1D *> QuickViewHelper::GetHistogram1D()
{
   return Histogram1D;
}
//-------------------------------------------------------------------------
std::map<std::string, TH2D *> QuickViewHelper::GetHistogram2D()
{
   return Histogram2D;
}
//-------------------------------------------------------------------------
TH1 *QuickViewHelper::GetHistogram(std::string HistogramName)
{
   if(Histogram1D.find(HistogramName) != Histogram1D.end())
      return Histogram1D[HistogramName];
   else if(Histogram2D.find(HistogramName) != Histogram2D.end())
      return Histogram2D[HistogramName];

   return NULL;
}
//-------------------------------------------------------------------------
TH1 *QuickViewHelper::operator [](std::string HistogramName)
{
   return GetHistogram(HistogramName);
}
//-------------------------------------------------------------------------
#endif






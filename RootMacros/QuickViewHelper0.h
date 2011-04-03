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
#include <cassert>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <deque>
//-------------------------------------------------------------------------
#include "TTree.h"
#include "TObjArray.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH1.h"
//-------------------------------------------------------------------------
#define VerbosityLevel_Quiet 0
#define VerbosityLevel_Information 1
#define VerbosityLevel_Noisy 2
//-------------------------------------------------------------------------
class HistogramRecord;
class ExpressionNode;
class QuickViewHelper;
//-------------------------------------------------------------------------
class HistogramRecord
{
public:
   std::string Name;
   bool Is1D;
   std::string Variable1;
   std::string Variable2;
   std::string Selection;
public:
   HistogramRecord() {}
};
//-------------------------------------------------------------------------
class ExpressionNode
{
public:
   enum ExpressionType
   {
      Expression_Plus = 1, Expression_Minus, Expression_Multiply, Expression_Divide, Expression_Negative,
      Expression_Sine, Expression_Cosine, Expression_Tangent, Expression_Cotangent,
      Expression_Second, Expression_Cosecond, Expression_Sinh, Expression_Cosh, Expression_Tanh,
      Expression_Exp, Expression_Log, Expression_ASin, Expression_ACos, Expression_ATan, Expression_Instance,
      Expression_Sqrt, Expression_Greater, Expression_GreaterEqual, Expression_Equal, Expression_NotEqual,
      Expression_Less, Expression_LessEqual
   };
public:
   std::string ID;
   std::string Name;
   ExpressionNode *ChildNode1;
   ExpressionNode *ChildNode2;
   bool IsLeaf;
   QuickViewHelper *OwnerLink;
   bool IsConstant;
   double ConstantNumber;
   ExpressionType Action;
public:
   ExpressionNode();
   ~ExpressionNode();
   void Initialize(QuickViewHelper *Link, std::string Expression);
   double Evaluate(int Instance = 0);
   std::vector<std::string> GetSizedDependencies();
   void ExportToDotFormat(std::ofstream &out);
};
//-------------------------------------------------------------------------
class QuickViewHelper
{
private:
   enum BranchTypes {BranchType_Double, BranchType_Integer, BranchType_Float,
      BranchType_Boolean, BranchType_Expression};
private:
   TTree *Tree;
   std::map<std::string, double *> DoubleBranches;
   std::map<std::string, float *> FloatBranches;
   std::map<std::string, int *> IntegerBranches;
   std::map<std::string, bool *> BooleanBranches;
   std::map<std::string, std::vector<double> > ExpressionBranches;
   std::vector<ExpressionNode *> ExpressionCommands;
   std::map<std::string, BranchTypes> BranchType;
   std::map<std::string, int> BranchSize;
private:
   std::map<std::string, TH1D *> Histogram1D;
   std::map<std::string, TH2D *> Histogram2D;
   std::map<std::string, HistogramRecord> HistogramRecords;
private:
   int VerbosityLevel;
public:
   QuickViewHelper();
   ~QuickViewHelper();
   void Clear();
   bool LoadTree(TTree *tree);
   void PrintBranches();
   void Execute();
   void SetVerbosityLevel(int NewLevel);
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
public:
   bool BuildExpression(std::string ExpressionName, std::string ExpressionFormula);
private:
   friend class ExpressionNode;
   double GetValue(const std::string Name, int Instance = 0);
   std::deque<std::string> LastBranches;
   std::deque<void *> LastBranchPointers;
   std::deque<int> LastBranchTypes;
};
//-------------------------------------------------------------------------
QuickViewHelper::QuickViewHelper()
{
   Clear();

   VerbosityLevel = VerbosityLevel_Information;
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
   
   for(std::map<std::string, float *>::iterator iter = FloatBranches.begin();
      iter != FloatBranches.end(); iter++)
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
   FloatBranches.clear();
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

   for(int i = 0; i < (int)ExpressionCommands.size(); i++)
      if(ExpressionCommands[i] != NULL)
         delete ExpressionCommands[i];
   ExpressionCommands.clear();
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
                  new double[CurrentLeaf->GetNdata()]));
               BranchType.insert(std::pair<std::string, BranchTypes>(CurrentLeaf->GetName(), BranchType_Double));
               BranchSize.insert(std::pair<std::string, int>(CurrentLeaf->GetName(), CurrentLeaf->GetNdata()));
            }
            if(CurrentLeaf->GetTypeName() == TString("Float_t"))
            {
               FloatBranches.insert(std::pair<std::string, float *>(CurrentLeaf->GetName(),
                  new float[CurrentLeaf->GetNdata()]));
               BranchType.insert(std::pair<std::string, BranchTypes>(CurrentLeaf->GetName(), BranchType_Float));
               BranchSize.insert(std::pair<std::string, int>(CurrentLeaf->GetName(), CurrentLeaf->GetNdata()));
            }
            if(CurrentLeaf->GetTypeName() == TString("Int_t"))
            {
               IntegerBranches.insert(std::pair<std::string, int *>(CurrentLeaf->GetName(),
                  new int[CurrentLeaf->GetNdata()]));
               BranchType.insert(std::pair<std::string, BranchTypes>(CurrentLeaf->GetName(), BranchType_Integer));
               BranchSize.insert(std::pair<std::string, int>(CurrentLeaf->GetName(), CurrentLeaf->GetNdata()));
            }
            if(CurrentLeaf->GetTypeName() == TString("Bool_t"))
            {
               BooleanBranches.insert(std::pair<std::string, bool *>(CurrentLeaf->GetName(),
                  new bool[CurrentLeaf->GetNdata()]));
               BranchType.insert(std::pair<std::string, BranchTypes>(CurrentLeaf->GetName(), BranchType_Boolean));
               BranchSize.insert(std::pair<std::string, int>(CurrentLeaf->GetName(), CurrentLeaf->GetNdata()));
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
         if(CurrentLeaf->GetLenStatic() == 1 && CurrentLeaf->GetTypeName() == TString("Float_t"))
            Tree->SetBranchAddress(CurrentBranch->GetName(), &FloatBranches[Name][0]);
         if(CurrentLeaf->GetLenStatic() == 1 && CurrentLeaf->GetTypeName() == TString("Int_t"))
            Tree->SetBranchAddress(CurrentBranch->GetName(), &IntegerBranches[Name][0]);
         if(CurrentLeaf->GetLenStatic() == 1 && CurrentLeaf->GetTypeName() == TString("Bool_t"))
            Tree->SetBranchAddress(CurrentBranch->GetName(), &BooleanBranches[Name][0]);
         if(CurrentLeaf->GetLenStatic() > 1 && CurrentLeaf->GetTypeName() == TString("Double_t"))
            Tree->SetBranchAddress(CurrentBranch->GetName(), DoubleBranches[Name]);
         if(CurrentLeaf->GetLenStatic() > 1 && CurrentLeaf->GetTypeName() == TString("Float_t"))
            Tree->SetBranchAddress(CurrentBranch->GetName(), FloatBranches[Name]);
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
   
   std::cout << "Float Branches: " << std::endl;
   for(std::map<std::string, float *>::iterator iter = FloatBranches.begin();
      iter != FloatBranches.end(); iter++)
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
      if(VerbosityLevel >= VerbosityLevel_Information && (iEntry + 1) % 10000 == 0)
         std::cout << "Processing entry " << iEntry + 1 << "/" << NumberOfEntries << std::endl;

      Tree->GetEntry(iEntry);

      int ExpressionCommandSize = ExpressionCommands.size();
      for(int i = 0; i < ExpressionCommandSize; i++)
      {
         if(ExpressionCommands[i] == NULL)
            continue;

         std::string ID = ExpressionCommands[i]->ID;

         int Size = BranchSize[ID];
         std::vector<double> &CurrentBranch = ExpressionBranches[ID];
         for(int j = 0; j < Size; j++)
            CurrentBranch[j] = ExpressionCommands[i]->Evaluate(j);
      }

      for(std::map<std::string, HistogramRecord>::iterator iter = HistogramRecords.begin();
         iter != HistogramRecords.end(); iter++)
      {
         if(iter->second.Is1D == true)
         {
            TH1D *H = Histogram1D[iter->first];
            if(H == NULL)
               continue;

            for(int i = 0; i < BranchSize[iter->second.Variable1]; i++)
               H->Fill(GetValue(iter->second.Variable1, i));
         }
         else   // 2D
         {
            TH2D *H = Histogram2D[iter->first];
            if(H == NULL)
               continue;

            for(int i = 0; i < BranchSize[iter->second.Variable1] && i < BranchSize[iter->second.Variable2]; i++)
            {
               double Variable1 = GetValue(iter->second.Variable1, i);
               double Variable2 = GetValue(iter->second.Variable2, i);

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
bool QuickViewHelper::BuildExpression(std::string ExpressionName, std::string ExpressionFormula)
{
   ExpressionNode *NewNode = new ExpressionNode;
   NewNode->Initialize(this, ExpressionFormula);

   int MinSize = 1;
   std::vector<std::string> SizedDependencies = NewNode->GetSizedDependencies();
   for(int i = 0; i < (int)SizedDependencies.size(); i++)
   {
      if(MinSize == 1 && BranchSize[SizedDependencies[i]] > 1)
         MinSize = BranchSize[SizedDependencies[i]];
      if(BranchSize[SizedDependencies[i]] > 1 && MinSize > BranchSize[SizedDependencies[i]])
         MinSize = BranchSize[SizedDependencies[i]];
   }

   ExpressionCommands.push_back(NewNode);
   ExpressionBranches.insert(std::pair<std::string, std::vector<double> >(ExpressionName,
      std::vector<double>(MinSize)));

   BranchType.insert(std::pair<std::string, BranchTypes>(ExpressionName, BranchType_Expression));
   BranchSize.insert(std::pair<std::string, int>(ExpressionName, MinSize));

   NewNode->ID = ExpressionName;

   return false;
}
//-------------------------------------------------------------------------
double QuickViewHelper::GetValue(const std::string Name, int Instance)
{
   for(int i = 0; i < (int)LastBranches.size(); i++)
   {
      if(LastBranches[i] == Name)
      {
         if(LastBranchTypes[i] == BranchType_Double)
            return ((double *)LastBranchPointers[i])[Instance];
         if(LastBranchTypes[i] == BranchType_Integer)
            return ((int *)LastBranchPointers[i])[Instance];
         if(LastBranchTypes[i] == BranchType_Boolean)
            return ((bool *)LastBranchPointers[i])[Instance];
         if(LastBranchTypes[i] == BranchType_Float)
            return ((float *)LastBranchPointers[i])[Instance];
         if(LastBranchTypes[i] == BranchType_Expression)
            return (*((std::vector<double> *)LastBranchPointers[i]))[Instance];
      }
   }

   if(BranchType.find(Name) == BranchType.end())
   {
      std::cerr << "Unknown branch requested: " << Name << std::endl;
      return -100000;
   }
   if(Instance >= BranchSize[Name] || Instance < 0)
   {
      std::cerr << "Instance " << Instance << " requested for branch " << Name << std::endl;
      return -100000;
   }
   
   if(BranchType[Name] == BranchType_Double)
   {
      LastBranches.push_back(Name);
      LastBranchTypes.push_back(BranchType_Double);
      LastBranchPointers.push_back(DoubleBranches[Name]);
   }
   if(BranchType[Name] == BranchType_Integer)
   {
      LastBranches.push_back(Name);
      LastBranchTypes.push_back(BranchType_Integer);
      LastBranchPointers.push_back(IntegerBranches[Name]);
   }
   if(BranchType[Name] == BranchType_Boolean)
   {
      LastBranches.push_back(Name);
      LastBranchTypes.push_back(BranchType_Boolean);
      LastBranchPointers.push_back(BooleanBranches[Name]);
   }
   if(BranchType[Name] == BranchType_Float)
   {
      LastBranches.push_back(Name);
      LastBranchTypes.push_back(BranchType_Float);
      LastBranchPointers.push_back(FloatBranches[Name]);
   }
   if(BranchType[Name] == BranchType_Expression)
   {
      LastBranches.push_back(Name);
      LastBranchTypes.push_back(BranchType_Expression);
      LastBranchPointers.push_back(&ExpressionBranches[Name]);
   }
   
   if(BranchType[Name] == BranchType_Double)
      return DoubleBranches[Name][Instance];
   if(BranchType[Name] == BranchType_Float)
      return FloatBranches[Name][Instance];
   if(BranchType[Name] == BranchType_Integer)
      return IntegerBranches[Name][Instance];
   if(BranchType[Name] == BranchType_Boolean)
      return BooleanBranches[Name][Instance];
   if(BranchType[Name] == BranchType_Expression)
      return ExpressionBranches[Name][Instance];
   
   return -100000;
}
//-------------------------------------------------------------------------
ExpressionNode::ExpressionNode()
{
   Name = "";
   ChildNode1 = NULL;
   ChildNode2 = NULL;
   IsLeaf = false;
   OwnerLink = NULL;
   IsConstant = false;
   ConstantNumber = 0;
}
//-------------------------------------------------------------------------
ExpressionNode::~ExpressionNode()
{
   if(ChildNode1 != NULL)   delete ChildNode1;
   if(ChildNode2 != NULL)   delete ChildNode2;

   ChildNode1 = NULL;
   ChildNode2 = NULL;
   OwnerLink = NULL;
}
//-------------------------------------------------------------------------
void ExpressionNode::Initialize(QuickViewHelper *Link, std::string Expression)
{
   std::stringstream idstr;
   idstr << clock() << rand() << rand() << rand() << rand();
   idstr >> ID;

   OwnerLink = Link;

   // First step: prune out white spaces
   for(int i = 0; i < (int)Expression.size(); i++)
   {
      if(Expression[i] == ' ')
      {
         Expression.erase(Expression.begin() + i);
         i = i - 1;
      }
   }

   assert(Expression != "-");

   // If empty, this expression is always zero
   if(Expression == "" || Expression == "-")
   {
      IsLeaf = true;
      IsConstant = true;
      ConstantNumber = 0;
      return;
   }

   // If first is negative sign, take note and remove it from the expression
   bool FirstNegative = false;
   if(Expression[0] == '-')
   {
      FirstNegative = true;
      Expression.erase(Expression.begin());
   }

   assert(Expression[0] != '-');

   // Step 2: Parse into parts
   std::vector<std::string> Parts;
   std::vector<std::string> Operators;
   int QuoteLevel = 0;
   int MaxQuoteLevel = 0;
   int StartTemp = 0;
   for(int i = 0; i < (int)Expression.size(); i++)
   {
      if(Expression[i] == '(')
         QuoteLevel = QuoteLevel + 1;
      else if(Expression[i] == ')')
      {
         QuoteLevel = QuoteLevel - 1;
         assert(QuoteLevel >= 0);
      }
      else if((Expression.substr(i, 2) == "==" || Expression.substr(i, 2) == "!="
         || Expression.substr(i, 2) == "!=" || Expression.substr(i, 2) == "<="
         || Expression.substr(i, 2) == ">=") && QuoteLevel == 0)
      {
         assert(i != StartTemp);

         Parts.push_back(Expression.substr(StartTemp, i - StartTemp));
         Operators.push_back(Expression.substr(i, 2));
         StartTemp = i + 2;
      }
      else if((Expression[i] == '+' || Expression[i] == '-' || Expression[i] == '*'
         || Expression[i] == '/' || Expression[i] == '<' || Expression[i] == '>')
         && QuoteLevel == 0)
      {
         assert(i != StartTemp);

         Parts.push_back(Expression.substr(StartTemp, i - StartTemp));
         Operators.push_back(Expression.substr(i, 1));
         StartTemp = i + 1;
      }

      if(QuoteLevel > MaxQuoteLevel)
         MaxQuoteLevel = QuoteLevel;
   }
   Parts.push_back(Expression.substr(StartTemp, (int)Expression.size() - StartTemp));

   assert(QuoteLevel == 0);
   assert(Parts.size() == Operators.size() + 1);
   
   // for(int i = 0; i < (int)Operators.size(); i++)
   //    std::cout << Parts[i] << " [" << Operators[i] << "] ";
   // std::cout << Parts[Parts.size()-1] << std::endl;

   if(Parts.size() == 1)
   {
      if(FirstNegative == true)
      {
         ChildNode1 = new ExpressionNode;
         ChildNode1->Initialize(Link, Expression);
         Action = Expression_Negative;
      }
      else
      {
         if((Parts[0][0] <= '9' && Parts[0][0] >= '0') || Parts[0][0] == '.')
         {
            std::stringstream str(Parts[0]);
            str >> ConstantNumber;
            IsLeaf = true;
            IsConstant = true;
         }
         else if(MaxQuoteLevel == 0)
         {
            int LeftBracketIndex = -1;
            int RightBracketIndex = -1;

            for(int i = 0; i < Parts[0].size(); i++)
            {
               if(Parts[0][i] == '[')
               {
                  LeftBracketIndex = i;
                  break;
               }
            }

            int BracketLevel = 1;
            if(LeftBracketIndex == -1)
               BracketLevel = 0;
            for(int i = LeftBracketIndex + 1; i < (int)Parts[0].size(); i++)
            {
               if(Parts[0][i] == ']')
                  BracketLevel = BracketLevel - 1;
               if(Parts[0][i] == '[')
                  BracketLevel = BracketLevel + 1;

               assert(BracketLevel >= 0);

               if(BracketLevel == 0)
               {
                  RightBracketIndex = i;
                  break;
               }
            }

            assert(BracketLevel == 0);
            assert((LeftBracketIndex == -1) || (RightBracketIndex + 1 == (int)Parts[0].size()));

            if(LeftBracketIndex == -1)
            {
               Name = Parts[0];
               IsLeaf = true;
               IsConstant = false;
            }
            else
            {
               std::string Variable = Parts[0].substr(0, LeftBracketIndex);
               std::string Inside = Parts[0].substr(LeftBracketIndex + 1,
                  RightBracketIndex - LeftBracketIndex - 1);

               Name = Variable;
               IsLeaf = false;
               IsConstant = false;
               Action = Expression_Instance;

               ChildNode1 = new ExpressionNode;
               ChildNode1->Initialize(Link, Inside);
            }
         }
         else
         {
            IsLeaf = false;
            IsConstant = false;

            int LeftQuoteIndex = -1;
            int RightQuoteIndex = -1;

            for(int i = 0; i < (int)Parts[0].size(); i++)
            {
               if(Parts[0][i] == '(')
               {
                  LeftQuoteIndex = i;
                  break;
               }
            }

            assert(LeftQuoteIndex >= 0 && LeftQuoteIndex < Parts[0].size());

            QuoteLevel = 1;
            for(int i = LeftQuoteIndex + 1; i < (int)Parts[0].size() && QuoteLevel > 0; i++)
            {
               if(Parts[0][i] == '(')
                  QuoteLevel = QuoteLevel + 1;
               if(Parts[0][i] == ')')
                  QuoteLevel = QuoteLevel - 1;

               if(QuoteLevel == 0)
                  RightQuoteIndex = i;
            }

            assert(RightQuoteIndex + 1 == Parts[0].size());   // trailing stuff = bad

            if(LeftQuoteIndex == 0)
            {
               Parts[0].erase(Parts[0].begin());
               Parts[0].erase(Parts[0].begin() + ((int)Parts[0].size() - 1));

               Initialize(Link, Parts[0]);
            }
            else
            {
               std::string Function = Parts[0].substr(0, LeftQuoteIndex);
               std::string Inside = Parts[0].substr(LeftQuoteIndex + 1, RightQuoteIndex - LeftQuoteIndex - 1);

               // std::cout << Function << " [[ " << Inside << " ]] " << std::endl;

               if(Function == "sin")
                  Action = Expression_Sine;
               else if(Function == "cos")
                  Action = Expression_Cosine;
               else if(Function == "tan")
                  Action = Expression_Tangent;
               else if(Function == "cot")
                  Action = Expression_Cotangent;
               else if(Function == "sec")
                  Action = Expression_Second;
               else if(Function == "csc")
                  Action = Expression_Cosecond;
               else if(Function == "sinh")
                  Action = Expression_Sinh;
               else if(Function == "cosh")
                  Action = Expression_Cosh;
               else if(Function == "tanh")
                  Action = Expression_Tanh;
               else if(Function == "exp")
                  Action = Expression_Exp;
               else if(Function == "log")
                  Action = Expression_Log;
               else if(Function == "asin")
                  Action = Expression_ASin;
               else if(Function == "acos")
                  Action = Expression_ACos;
               else if(Function == "atan")
                  Action = Expression_ATan;
               else if(Function == "sqrt")
                  Action = Expression_Sqrt;
               else
                  assert(false);

               ChildNode1 = new ExpressionNode;
               ChildNode1->Initialize(Link, Inside);
            }
         }
      }

      return;
   }

   // comparison operators
   for(int i = (int)Operators.size() - 1; i >= 0; i--)
   {
      if(Operators[i] != "<" && Operators[i] != ">" && Operators[i] != "<=" && Operators[i] != ">="
         && Operators[i] != "==" && Operators[i] != "!=")
         continue;

      std::string FirstPart = Parts[0];
      std::string SecondPart = "";

      for(int j = 0; j < i; j++)
         FirstPart = FirstPart + Operators[j] + Parts[j+1];
      for(int j = i + 1; j < Operators.size(); j++)
         SecondPart = SecondPart + Parts[j] + Operators[j];

      SecondPart = SecondPart + Parts[Parts.size()-1];

      if(FirstNegative == true)
         FirstPart = "-" + FirstPart;
         
      ChildNode1 = new ExpressionNode;
      ChildNode2 = new ExpressionNode;

      ChildNode1->Initialize(Link, FirstPart);
      ChildNode2->Initialize(Link, SecondPart);

      if(Operators[i] == "<")    Action = Expression_Less;
      if(Operators[i] == "<=")   Action = Expression_LessEqual;
      if(Operators[i] == ">")    Action = Expression_Greater;
      if(Operators[i] == ">=")   Action = Expression_GreaterEqual;
      if(Operators[i] == "==")   Action = Expression_Equal;
      if(Operators[i] == "!=")   Action = Expression_NotEqual;

      return;
   }

   // +, -, *, /
   std::vector<std::string> OperatorsToConsider;
   OperatorsToConsider.push_back("+");
   OperatorsToConsider.push_back("-");
   OperatorsToConsider.push_back("*");
   OperatorsToConsider.push_back("/");

   for(int k = 0; k < (int)OperatorsToConsider.size(); k++)
   {
      for(int i = 0; i < (int)Operators.size(); i++)
      {
         if(Operators[i] != OperatorsToConsider[k])
            continue;
         
         std::string FirstPart = Parts[0];
         std::string SecondPart = "";

         for(int j = 0; j < i; j++)
            FirstPart = FirstPart + Operators[j] + Parts[j+1];
         for(int j = i + 1; j < Operators.size(); j++)
         {
            SecondPart = SecondPart + Parts[j];

            if(Operators[i] == "-" && Operators[j] == "+")        SecondPart = SecondPart + "-";
            else if(Operators[i] == "-" && Operators[j] == "-")   SecondPart = SecondPart + "+";
            else if(Operators[i] == "/" && Operators[j] == "*")   SecondPart = SecondPart + "/";
            else if(Operators[i] == "/" && Operators[j] == "/")   SecondPart = SecondPart + "*";
            else                                                  SecondPart = SecondPart + Operators[j];
         }

         SecondPart = SecondPart + Parts[Parts.size()-1];

         if(FirstNegative == true)
            FirstPart = "-" + FirstPart;

         ChildNode1 = new ExpressionNode;
         ChildNode2 = new ExpressionNode;

         ChildNode1->Initialize(Link, FirstPart);
         ChildNode2->Initialize(Link, SecondPart);

         if(Operators[i] == "+")   Action = Expression_Plus;
         if(Operators[i] == "-")   Action = Expression_Minus;
         if(Operators[i] == "*")   Action = Expression_Multiply;
         if(Operators[i] == "/")   Action = Expression_Divide;

         return;
      }
   }

   assert(std::string("Unsupported operator detected") == "ERROR");
}
//-------------------------------------------------------------------------
double ExpressionNode::Evaluate(int Instance)
{
   if(IsLeaf == true && IsConstant == true)
      return ConstantNumber;
   if(IsLeaf == true && IsConstant == false)
      return OwnerLink->GetValue(Name, Instance);

   if(IsLeaf == false && IsConstant == false && Action == Expression_Instance)
      return OwnerLink->GetValue(Name, ChildNode1->Evaluate(Instance));
   
   // Not a leaf node, do evaluation
   if(Action == Expression_Plus)
      return ChildNode1->Evaluate(Instance) + ChildNode2->Evaluate(Instance);
   if(Action == Expression_Minus)
      return ChildNode1->Evaluate(Instance) - ChildNode2->Evaluate(Instance);
   if(Action == Expression_Multiply)
      return ChildNode1->Evaluate(Instance) * ChildNode2->Evaluate(Instance);
   if(Action == Expression_Divide)
      return ChildNode1->Evaluate(Instance) / ChildNode2->Evaluate(Instance);
   if(Action == Expression_Negative)
      return -ChildNode1->Evaluate(Instance);
   if(Action == Expression_Sine)
      return sin(ChildNode1->Evaluate(Instance));
   if(Action == Expression_Cosine)
      return cos(ChildNode1->Evaluate(Instance));
   if(Action == Expression_Tangent)
      return tan(ChildNode1->Evaluate(Instance));
   if(Action == Expression_Cotangent)
      return 1.0 / tan(ChildNode1->Evaluate(Instance));
   if(Action == Expression_Second)
      return 1.0 / cos(ChildNode1->Evaluate(Instance));
   if(Action == Expression_Cosecond)
      return 1.0 / sin(ChildNode1->Evaluate(Instance));
   if(Action == Expression_Sinh)
      return sinh(ChildNode1->Evaluate(Instance));
   if(Action == Expression_Cosh)
      return cosh(ChildNode1->Evaluate(Instance));
   if(Action == Expression_Tanh)
      return tanh(ChildNode1->Evaluate(Instance));
   if(Action == Expression_Exp)
      return exp(ChildNode1->Evaluate(Instance));
   if(Action == Expression_Log)
      return log(ChildNode1->Evaluate(Instance));
   if(Action == Expression_ASin)
      return asin(ChildNode1->Evaluate(Instance));
   if(Action == Expression_ACos)
      return acos(ChildNode1->Evaluate(Instance));
   if(Action == Expression_ATan)
      return atan(ChildNode1->Evaluate(Instance));
   if(Action == Expression_Sqrt)
      return sqrt(ChildNode1->Evaluate(Instance));
   if(Action == Expression_Less)
      return ChildNode1->Evaluate(Instance) < ChildNode2->Evaluate(Instance);
   if(Action == Expression_LessEqual)
      return ChildNode1->Evaluate(Instance) <= ChildNode2->Evaluate(Instance);
   if(Action == Expression_Equal)
      return ChildNode1->Evaluate(Instance) == ChildNode2->Evaluate(Instance);
   if(Action == Expression_NotEqual)
      return ChildNode1->Evaluate(Instance) != ChildNode2->Evaluate(Instance);
   if(Action == Expression_Greater)
      return ChildNode1->Evaluate(Instance) > ChildNode2->Evaluate(Instance);
   if(Action == Expression_GreaterEqual)
      return ChildNode1->Evaluate(Instance) >= ChildNode2->Evaluate(Instance);

   return 0;
}
//-------------------------------------------------------------------------
std::vector<std::string> ExpressionNode::GetSizedDependencies()
{
   std::vector<std::string> Result;

   if(IsLeaf == true && IsConstant == true)
      return Result;
   else if(IsLeaf == true && IsConstant == false)
   {
      Result.push_back(Name);
      return Result;
   }
   else if(IsLeaf == false && IsConstant == false && Action == Expression_Instance)
      return Result;
   else
   {
      std::vector<std::string> ResultTemp;

      if(ChildNode1 != NULL)
         ResultTemp = ChildNode1->GetSizedDependencies();
      Result.insert(Result.end(), ResultTemp.begin(), ResultTemp.end());
      
      if(ChildNode2 != NULL)
         ResultTemp = ChildNode2->GetSizedDependencies();
      Result.insert(Result.end(), ResultTemp.begin(), ResultTemp.end());
   }

   return Result;
}
//-------------------------------------------------------------------------
void ExpressionNode::ExportToDotFormat(std::ofstream &out)
{
   std::stringstream str;
   str << "   " << ID << " [ label = \"";

   if(IsLeaf == true && IsConstant == true)         str << ConstantNumber;
   else if(IsLeaf == true && IsConstant == false)   str << Name;
   else if(Action == Expression_Instance)           str << Name << "[]";
   else if(Action == Expression_Plus)               str << "+";
   else if(Action == Expression_Minus)              str << "-";
   else if(Action == Expression_Multiply)           str << "*";
   else if(Action == Expression_Divide)             str << "/";
   else if(Action == Expression_Negative)           str << "-";
   else if(Action == Expression_Sine)               str << "sin";
   else if(Action == Expression_Cosine)             str << "cos";
   else if(Action == Expression_Tangent)            str << "tan";
   else if(Action == Expression_Cotangent)          str << "cot";
   else if(Action == Expression_Second)             str << "sec";
   else if(Action == Expression_Cosecond)           str << "csc";
   else if(Action == Expression_Sinh)               str << "sinh";
   else if(Action == Expression_Cosh)               str << "cosh";
   else if(Action == Expression_Tanh)               str << "tanh";
   else if(Action == Expression_Exp)                str << "exp";
   else if(Action == Expression_Log)                str << "log";
   else if(Action == Expression_ASin)               str << "asin";
   else if(Action == Expression_ACos)               str << "acos";
   else if(Action == Expression_ATan)               str << "atan";
   else if(Action == Expression_Sqrt)               str << "sqrt";
   else if(Action == Expression_Greater)            str << ">";
   else if(Action == Expression_GreaterEqual)       str << ">=";
   else if(Action == Expression_Equal)              str << "==";
   else if(Action == Expression_NotEqual)           str << "!=";
   else if(Action == Expression_Less)               str << "<";
   else if(Action == Expression_LessEqual)          str << "<=";
   else                                             str << "none";

   str << "\" ] ";

   out << str.str() << std::endl;

   if(ChildNode1 != NULL)
      out << "   " << ID << " -> " << ChildNode1->ID << std::endl;
   if(ChildNode2 != NULL)
      out << "   " << ID << " -> " << ChildNode2->ID << std::endl;

   if(ChildNode1 != NULL)
      ChildNode1->ExportToDotFormat(out);
   if(ChildNode2 != NULL)
      ChildNode2->ExportToDotFormat(out);
}
//-------------------------------------------------------------------------
#endif






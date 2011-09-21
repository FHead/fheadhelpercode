#include <cmath>
#include <algorithm>
#include <ostream>
using namespace std;

struct ValueWithError;
ostream &operator <<(ostream &out, ValueWithError value);
ValueWithError CalculatePoissonError(double Count, double BestGuess, double ErrorOnBestGuess,
   double Confidence = 0.95, bool Flat = false);
double EstimateLogIntegral(double Count, double BestGuess, double ErrorOnBestGuess, double Min, double Max,
   double CentralValue, bool Flat);
double FindLowerPosition(double CentralValue, double Count, double BestGuess, double ErrorOnBestGuess, double Height,
   bool Flat);
double FindUpperPosition(double CentralValue, double Count, double BestGuess, double ErrorOnBestGuess, double Height,
   bool Flat);
double PlugFormula(double Value, double Count, double BestGuess, double ErrorOnBestGuess);
double PlugFormulaFlat(double Value, double Count);


struct ValueWithError
{
   double CentralValue;
   double UpperBound;
   double LowerBound;
};

ostream &operator <<(ostream &out, ValueWithError value)
{
   out << "(" << value.LowerBound << ", " << value.CentralValue << ", " << value.UpperBound << ")";
   return out;
}

ValueWithError CalculatePoissonError(double Count, double BestGuess, double ErrorOnBestGuess,
   double Confidence, bool Flat)
{
   // P(Theta|x) = P(x|Theta) P(Theta) / P(x)
   // Theta: theory parameter
   // x: observed count
   // P(x) is constant across all cases, ignore
   // P(Theta) assumed to be a gaussian centered around best guess....(Is this fine?)
   // P(x|Theta) is poissonian
   // Return the 90% C.L. band

   // How do I calculate this......?

   // Central value - impose that it is positive --- note that -4AC > 0
   double Error2OnBestGuess = ErrorOnBestGuess * ErrorOnBestGuess;
   double A = 1;
   double B = -(BestGuess - Error2OnBestGuess);
   double C = -Error2OnBestGuess * Count;
   double CentralValue = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);   // constrain central value to be positive
   if(Count < 1e-5)
      CentralValue = BestGuess - Error2OnBestGuess;

   if(Flat == true)
      CentralValue = Count;

   // Now try to find the bounds....
   double LogHeight = 0;
   if(Flat == false)
      LogHeight = PlugFormula(CentralValue, Count, BestGuess, ErrorOnBestGuess);
   else
      LogHeight = PlugFormulaFlat(CentralValue, Count);

   double AreaMin = 0;
   double AreaMax = max(CentralValue * 5 + 200, BestGuess + ErrorOnBestGuess * 20);
   double TotalArea = EstimateLogIntegral(Count, BestGuess, ErrorOnBestGuess, AreaMin, AreaMax, CentralValue, Flat);

   double HeightGuess = LogHeight - log(1.1);
   double LowerGuess = FindLowerPosition(CentralValue, Count, BestGuess, ErrorOnBestGuess, HeightGuess, Flat);
   double HigherGuess = FindUpperPosition(CentralValue, Count, BestGuess, ErrorOnBestGuess, HeightGuess, Flat);
   double GuessArea = EstimateLogIntegral(Count, BestGuess, ErrorOnBestGuess, LowerGuess, HigherGuess,
      CentralValue, Flat);
   double CurrentStep = log(1.10);

   while(exp(GuessArea - TotalArea) < Confidence)
   {
      HeightGuess = HeightGuess - CurrentStep;
      LowerGuess = FindLowerPosition(CentralValue, Count, BestGuess, ErrorOnBestGuess, HeightGuess, Flat);
      HigherGuess = FindUpperPosition(CentralValue, Count, BestGuess, ErrorOnBestGuess, HeightGuess, Flat);
      GuessArea = EstimateLogIntegral(Count, BestGuess, ErrorOnBestGuess, LowerGuess, HigherGuess, CentralValue,
         Flat);
   }

   CurrentStep = (LogHeight - HeightGuess) / 2; 

   while(fabs(exp(GuessArea - TotalArea) - Confidence) > 0.00001)
   {
      if(exp(GuessArea - TotalArea) > Confidence)
         HeightGuess = HeightGuess + CurrentStep;
      else
         HeightGuess = HeightGuess - CurrentStep;

      LowerGuess = FindLowerPosition(CentralValue, Count, BestGuess, ErrorOnBestGuess, HeightGuess, Flat);
      HigherGuess = FindUpperPosition(CentralValue, Count, BestGuess, ErrorOnBestGuess, HeightGuess, Flat);
      GuessArea = EstimateLogIntegral(Count, BestGuess, ErrorOnBestGuess, LowerGuess, HigherGuess, CentralValue,
         Flat);
      CurrentStep = CurrentStep / 2;
   }

   ValueWithError result;
   result.CentralValue = CentralValue;
   result.UpperBound = HigherGuess;
   result.LowerBound = LowerGuess;
   return result;
}

double EstimateLogIntegral(double Count, double BestGuess, double ErrorOnBestGuess, double Min, double Max,
   double CentralValue, bool Flat)
{
   if(Min > Max)
      swap(Min, Max);

   int Segmentation = 1000000;

   double LogMaxHeight = Count * log(CentralValue) - CentralValue
      - (CentralValue - BestGuess) * (CentralValue - BestGuess) / (2 * ErrorOnBestGuess * ErrorOnBestGuess);

   if(Flat == false)
      LogMaxHeight = PlugFormula(CentralValue, Count, BestGuess, ErrorOnBestGuess);
   else
      LogMaxHeight = PlugFormulaFlat(CentralValue, Count);

   double Integral = 0;

   for(int i = 0; i < Segmentation; i++)
   {
      double BinCenter = Min + (Max - Min) / Segmentation * (i + 0.5);
      
      double LogHeight = 0;
      if(Flat == false)
         LogHeight = PlugFormula(BinCenter, Count, BestGuess, ErrorOnBestGuess);
      else
         LogHeight = PlugFormulaFlat(BinCenter, Count);

      if(LogHeight - LogMaxHeight < -20)
         continue;

      double Height = exp(LogHeight - LogMaxHeight);
      Integral = Integral + Height * (Max - Min) / Segmentation;
   }

   return LogMaxHeight + log(Integral);
}

double FindLowerPosition(double CentralValue, double Count, double BestGuess, double ErrorOnBestGuess, double Height,
   bool Flat)
{
   if(Count < 1e-5)
      return 0;

   double CurrentStep = 0.1;
   double CurrentGuess = CentralValue - CurrentStep;
   if(CurrentGuess <= 0)
      CurrentGuess = 1e-5;

   double CurrentHeight = 0;
   
   if(Flat == false)
      CurrentHeight = PlugFormula(CurrentGuess, Count, BestGuess, ErrorOnBestGuess);
   else
      CurrentHeight = PlugFormulaFlat(CurrentGuess, Count);

   while(CurrentHeight > Height)
   {
      CurrentGuess = CurrentGuess / 2;

      if(Flat == false)
         CurrentHeight = PlugFormula(CurrentGuess, Count, BestGuess, ErrorOnBestGuess);
      else
         CurrentHeight = PlugFormulaFlat(CurrentGuess, Count);
   }

   CurrentStep = (CentralValue - CurrentGuess) / 2;

   while(fabs(CurrentHeight - Height) > 0.000001)
   {
      if(CurrentHeight > Height)
         CurrentGuess = CurrentGuess - CurrentStep;
      else
         CurrentGuess = CurrentGuess + CurrentStep;
      
      if(Flat == false)
         CurrentHeight = PlugFormula(CurrentGuess, Count, BestGuess, ErrorOnBestGuess);
      else
         CurrentHeight = PlugFormulaFlat(CurrentGuess, Count);

      CurrentStep = CurrentStep / 2;
   }

   return CurrentGuess;
}

double FindUpperPosition(double CentralValue, double Count, double BestGuess, double ErrorOnBestGuess, double Height,
   bool Flat)
{
   double CurrentStep = 0.1;
   double CurrentGuess = CentralValue + CurrentStep;

   double CurrentHeight = 0;
   if(Flat == false)
      CurrentHeight = PlugFormula(CurrentGuess, Count, BestGuess, ErrorOnBestGuess);
   else
      CurrentHeight = PlugFormulaFlat(CurrentGuess, Count);

   while(CurrentHeight > Height - log(2))
   {
      CurrentGuess = CurrentGuess + CurrentStep;

      if(Flat == false)
         CurrentHeight = PlugFormula(CurrentGuess, Count, BestGuess, ErrorOnBestGuess);
      else
         CurrentHeight = PlugFormulaFlat(CurrentGuess, Count);
   }

   CurrentStep = (CurrentGuess - CentralValue) / 2;

   while(fabs(CurrentHeight - Height) > 0.000001)
   {
      if(CurrentHeight > Height)
         CurrentGuess = CurrentGuess + CurrentStep;
      else
         CurrentGuess = CurrentGuess - CurrentStep;
      
      if(Flat == false)
         CurrentHeight = PlugFormula(CurrentGuess, Count, BestGuess, ErrorOnBestGuess);
      else
         CurrentHeight = PlugFormulaFlat(CurrentGuess, Count);

      CurrentStep = CurrentStep / 2;
   }

   return CurrentGuess;
}

double PlugFormula(double Value, double Count, double BestGuess, double ErrorOnBestGuess)
{
   return Count * log(Value) - Value
      - (Value - BestGuess) * (Value - BestGuess) / (2 * ErrorOnBestGuess * ErrorOnBestGuess);
}

double PlugFormulaFlat(double Value, double Count)
{
   if(Value == 0)
      return 0;
   return Count * log(Value) - Value;
}




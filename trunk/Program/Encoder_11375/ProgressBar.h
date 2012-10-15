#ifndef PROGRESSBAR_H_ASDFJKASDFJK
#define PROGRESSBAR_H_ASDFJKASDFJK
// Progress bar class
// Author: Yi Chen

#include <iostream>
#include <iomanip>
#include <ostream>
#include <cstdlib>

class ProgressBar
{
private:
   double Min;
   double Max;
   double Progress;
   int Column;
   int Style;
   std::ostream *Out;
   void SanityCheck();
public:
   ProgressBar(std::ostream &out, double max = 100, double min = 0, int column = 80)
      : Out(&out), Max(max), Min(min), Column(column), Progress(0), Style(0) {srand(time(NULL));   SanityCheck();}
   ProgressBar(std::ostream *out, double max = 100, double min = 0, int column = 80)
      : Out(out), Max(max), Min(min), Column(column), Progress(0), Style(0) {srand(time(NULL));   SanityCheck();}
   ~ProgressBar() {}
   void Print();
   void Print(double progress);
   void ChangeLine() {*Out << std::endl;}
   void PrintLine() {*Out << std::endl;}
   void Update(double progress) {SetProgress(progress);}
   void Increment(double change = 1) {Progress = Progress + change;}
public:
   double GetMin() {return Min;}
   double GetMax() {return Max;}
   double GetProgress() {return Progress;}
   int GetColumn() {return Column;}
   int GetStyle() {return Style;}
   std::ostream *GetStream() {return Out;}
   double GetPercentage() {return (Progress - Min) / (Max - Min);}
public:
   void SetMin(double min) {Min = min;   SanityCheck();}
   void SetMax(double max) {Max = max;   SanityCheck();}
   void SetProgress(double progress) {Progress = progress;   SanityCheck();}
   void SetColumn(int column) {Column = column;   SanityCheck();}
   void SetStyle(int style) {if(style == -1) Style = rand() % 6; else Style = style;   SanityCheck();}
   void SetStream(std::ostream &out) {Out = &out;   SanityCheck();}
   void SetStream(std::ostream *out) {Out = out;   SanityCheck();}
};

#endif

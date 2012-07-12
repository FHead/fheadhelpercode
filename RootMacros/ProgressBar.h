#include <iostream>
#include <iomanip>
#include <ostream>
using namespace std;

class ProgressBar
{
private:
   double Min;
   double Max;
   double Progress;
   int Column;
   int Style;
   ostream *Out;
   void SanityCheck();
public:
   ProgressBar(ostream &out, double max = 100, double min = 0, int column = 80)
      : Out(&out), Max(max), Min(min), Column(column), Progress(0), Style(0) {srand(time(NULL));   SanityCheck();}
   ProgressBar(ostream *out, double max = 100, double min = 0, int column = 80)
      : Out(out), Max(max), Min(min), Column(column), Progress(0), Style(0) {srand(time(NULL));   SanityCheck();}
   ~ProgressBar() {}
   void Print();
   void Print(double progress);
   void ChangeLine() {*Out << endl;}
   void PrintLine() {*Out << endl;}
   void Update(double progress) {SetProgress(progress);}
   void Increment(double change = 1) {Progress = Progress + change;}
public:
   double GetMin() {return Min;}
   double GetMax() {return Max;}
   double GetProgress() {return Progress;}
   int GetColumn() {return Column;}
   int GetStyle() {return Style;}
   ostream *GetStream() {return Out;}
   double GetPercentage() {return (Progress - Min) / (Max - Min);}
public:
   void SetMin(double min) {Min = min;   SanityCheck();}
   void SetMax(double max) {Max = max;   SanityCheck();}
   void SetProgress(double progress) {Progress = progress;   SanityCheck();}
   void SetColumn(int column) {Column = column;   SanityCheck();}
   void SetStyle(int style) {if(style == -1) Style = rand() % 6; else Style = style;   SanityCheck();}
   void SetStream(ostream &out) {Out = &out;   SanityCheck();}
   void SetStream(ostream *out) {Out = out;   SanityCheck();}
};

void ProgressBar::SanityCheck()
{
   if(Min == Max)
   {
      cerr << "[ProgressBar] Sanity check on range failed.  Resetting to 0-100" << endl;
      Min = 0;
      Max = 100;
      Progress = 0;
   }
   if(Max < Min)
   {
      cerr << "[ProgressBar] Min > Max!  Reversing the role of the two" << endl;
      swap(Min, Max);
   }

   if(Progress < Min)
   {
      cerr << "[ProgressBar] Negative progress.  Resetting to minimum value" << endl;
      Progress = Min;
   }
   if(Progress > Max)
   {
      cerr << "[ProgressBar] Past-complete progress.  Resetting to maximum value" << endl;
      Progress = Max;
   }

   if(Column < 15)
   {
      cerr << "[ProgressBar] Too few columns to display the progress bar.  Set to 20" << endl;
      Column = 20;
   }
   if(Column > 100)
   {
      cerr << "[ProgressBar] Too many columns to display the progress bar.  Set to 100" << endl;
      Column = 100;
   }

   if(Style < 0 || Style > 5)
   {
      cerr << "[ProgressBar] Style invalid.  Set to a random style." << endl;
      cerr << endl;
      cerr << "FYI: available styles look like these" << endl;
      cerr << "0: [==============================>                 ]  55%" << endl;
      cerr << "1: [                            ><>                 ]  55%" << endl;
      cerr << "2: [ooooooooooooooooooooooooooooooo                 ]  55%" << endl;
      cerr << "3: [~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|                 ]  55%" << endl;
      cerr << "4: [                  <=============================]  55%" << endl;
      cerr << "5: [                  <><                           ]  55%" << endl;
      cerr << endl;

      Style = rand() % 6;
   }

   if(Out == NULL)
   {
      cerr << "[ProgressBar] Output stream is NULL.  Set to cout" << endl;
      Out = &cout;
   }
}

void ProgressBar::Print()
{
   Print(Progress);
}

void ProgressBar::Print(double progress)
{
   if(Style == 0)
   {
      int AvailableColumn = Column - 2 - 5;
      int FilledColumn = (int)(AvailableColumn * (progress - Min) / (Max - Min));

      *Out << "\033[1G[";
      for(int i = 0; i < FilledColumn - 1; i++)
         *Out << "=";
      if(FilledColumn >= 1)
         *Out << ">";
      for(int i = 0; i < AvailableColumn - FilledColumn; i++)
         *Out << " ";
      *Out << "] ";
      *Out << setw(3) << setfill(' ') << (int)((progress - Min) / (Max - Min) * 100 + 0.5);
      *Out << "\%" << flush;
   }
   if(Style == 1)
   {
      int AvailableColumn = Column - 2 - 5;
      int FilledColumn = (int)(AvailableColumn * (progress - Min) / (Max - Min));

      *Out << "\033[1G[";
      for(int i = 0; i < FilledColumn - 3; i++)
         *Out << " ";
      if(FilledColumn >= 3)
         *Out << ">";
      if(FilledColumn >= 2)
         *Out << "<";
      if(FilledColumn >= 1)
         *Out << ">";
      for(int i = 0; i < AvailableColumn - FilledColumn; i++)
         *Out << " ";
      *Out << "] ";
      *Out << setw(3) << setfill(' ') << (int)((progress - Min) / (Max - Min) * 100 + 0.5);
      *Out << "\%" << flush;
   }
   if(Style == 2)
   {
      int AvailableColumn = Column - 2 - 5;
      int FilledColumn = (int)(AvailableColumn * (progress - Min) / (Max - Min));

      *Out << "\033[1G[";
      for(int i = 0; i < FilledColumn; i++)
         *Out << "o";
      for(int i = 0; i < AvailableColumn - FilledColumn; i++)
         *Out << " ";
      *Out << "] ";
      *Out << setw(3) << setfill(' ') << (int)((progress - Min) / (Max - Min) * 100 + 0.5);
      *Out << "\%" << flush;
   }
   if(Style == 3)
   {
      int AvailableColumn = Column - 2 - 5;
      int FilledColumn = (int)(AvailableColumn * (progress - Min) / (Max - Min));

      *Out << "\033[1G[";
      for(int i = 0; i < FilledColumn - 1; i++)
         *Out << "~";
      if(FilledColumn >= 1)
         *Out << "|";
      for(int i = 0; i < AvailableColumn - FilledColumn; i++)
         *Out << " ";
      *Out << "] ";
      *Out << setw(3) << setfill(' ') << (int)((progress - Min) / (Max - Min) * 100 + 0.5);
      *Out << "\%" << flush;
   }
   if(Style == 4)
   {
      int AvailableColumn = Column - 2 - 5;
      int FilledColumn = (int)(AvailableColumn * (progress - Min) / (Max - Min));

      *Out << "\033[1G[";
      for(int i = 0; i < AvailableColumn - FilledColumn; i++)
         *Out << " ";
      if(FilledColumn >= 1)
         *Out << "<";
      for(int i = 0; i < FilledColumn - 1; i++)
         *Out << "=";
      *Out << "] ";
      *Out << setw(3) << setfill(' ') << (int)((progress - Min) / (Max - Min) * 100 + 0.5);
      *Out << "\%" << flush;
   }
   if(Style == 5)
   {
      int AvailableColumn = Column - 2 - 5;
      int FilledColumn = (int)(AvailableColumn * (progress - Min) / (Max - Min));

      *Out << "\033[1G[";
      for(int i = 0; i < AvailableColumn - FilledColumn; i++)
         *Out << " ";
      if(FilledColumn >= 1)
         *Out << "<";
      if(FilledColumn >= 2)
         *Out << ">";
      if(FilledColumn >= 3)
         *Out << "<";
      for(int i = 0; i < FilledColumn - 3; i++)
         *Out << " ";
      *Out << "] ";
      *Out << setw(3) << setfill(' ') << (int)((progress - Min) / (Max - Min) * 100 + 0.5);
      *Out << "\%" << flush;
   }
}







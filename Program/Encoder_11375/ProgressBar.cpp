// Progress bar class
// Author: Yi Chen

#include <iostream>
#include <iomanip>
#include <ostream>
#include <cstdlib>

#include "ProgressBar.h"

void ProgressBar::SanityCheck()
{
   if(Min == Max)
   {
      std::cerr << "[ProgressBar] Sanity check on range failed.  Resetting to 0-100" << std::endl;
      Min = 0;
      Max = 100;
      Progress = 0;
   }
   if(Max < Min)
   {
      std::cerr << "[ProgressBar] Min > Max!  Reversing the role of the two" << std::endl;
      std::swap(Min, Max);
   }

   if(Progress < Min)
   {
      std::cerr << "[ProgressBar] Negative progress.  Resetting to minimum value" << std::endl;
      Progress = Min;
   }
   if(Progress > Max)
   {
      std::cerr << "[ProgressBar] Past-complete progress.  Resetting to maximum value" << std::endl;
      Progress = Max;
   }

   if(Column < 15)
   {
      std::cerr << "[ProgressBar] Too few columns to display the progress bar.  Set to 20" << std::endl;
      Column = 20;
   }
   if(Column > 100)
   {
      std::cerr << "[ProgressBar] Too many columns to display the progress bar.  Set to 100" << std::endl;
      Column = 100;
   }

   if(Style < 0 || Style > 5)
   {
      std::cerr << "[ProgressBar] Style invalid.  Set to a random style." << std::endl;
      std::cerr << std::endl;
      std::cerr << "FYI: available styles look like these" << std::endl;
      std::cerr << "0: [==============================>                 ]  55%" << std::endl;
      std::cerr << "1: [                            ><>                 ]  55%" << std::endl;
      std::cerr << "2: [ooooooooooooooooooooooooooooooo                 ]  55%" << std::endl;
      std::cerr << "3: [~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|                 ]  55%" << std::endl;
      std::cerr << "4: [                  <=============================]  55%" << std::endl;
      std::cerr << "5: [                  <><                           ]  55%" << std::endl;
      std::cerr << std::endl;

      Style = std::rand() % 6;
   }

   if(Out == NULL)
   {
      std::cerr << "[ProgressBar] Output stream is NULL.  Set to cout" << std::endl;
      Out = &std::cout;
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
      *Out << std::setw(3) << std::setfill(' ') << (int)((progress - Min) / (Max - Min) * 100 + 0.5);
      *Out << "\%" << std::flush;
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
      *Out << std::setw(3) << std::setfill(' ') << (int)((progress - Min) / (Max - Min) * 100 + 0.5);
      *Out << "\%" << std::flush;
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
      *Out << std::setw(3) << std::setfill(' ') << (int)((progress - Min) / (Max - Min) * 100 + 0.5);
      *Out << "\%" << std::flush;
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
      *Out << std::setw(3) << std::setfill(' ') << (int)((progress - Min) / (Max - Min) * 100 + 0.5);
      *Out << "\%" << std::flush;
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
      *Out << std::setw(3) << std::setfill(' ') << (int)((progress - Min) / (Max - Min) * 100 + 0.5);
      *Out << "\%" << std::flush;
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
      *Out << std::setw(3) << std::setfill(' ') << (int)((progress - Min) / (Max - Min) * 100 + 0.5);
      *Out << "\%" << std::flush;
   }
}







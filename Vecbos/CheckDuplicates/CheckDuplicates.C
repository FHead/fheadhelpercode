#include <map>
#include <iostream>

using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TChain.h"

#include "ChainAll.h"
#include "PlotHelper.h"

struct EventIndex;
void CheckDuplicates(char *FileList, char *Tag, char *OutputFileName = "Output.root");

struct EventIndex
{
   int RunNumber;
   int EventNumber;

   EventIndex() : RunNumber(0), EventNumber(0) {}

   bool operator <(const EventIndex &other) const
   {
      if(RunNumber < other.RunNumber)
         return true;
      if(RunNumber > other.RunNumber)
         return false;

      if(EventNumber < other.EventNumber)
         return true;
      if(EventNumber > other.EventNumber)
         return false;

      return false;
   }
};

void CheckDuplicates(char *FileList, char *Tag, char *OutputFileName)
{
   TChain *ch = ChainAll(FileList, "ntp1");

   EventIndex index;

   ch->SetBranchAddress("runNumber", &index.RunNumber);
   ch->SetBranchAddress("eventNumber", &index.EventNumber);

   ch->SetBranchStatus("*", 0);
   ch->SetBranchStatus("runNumber", 1);
   ch->SetBranchStatus("eventNumber", 1);

   map<EventIndex, int> EventCounts;

   int EntryCount = ch->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      ch->GetEntry(i, 0);

      if(i % 1000 == 0)
         cout << "Processing entry " << i << "/" << EntryCount << endl;

      if(index.RunNumber < 0 || index.EventNumber < 0)
         continue;

      if(EventCounts.find(index) == EventCounts.end())
         EventCounts.insert(pair<EventIndex, int>(index, 1));
      else
         EventCounts[index] = EventCounts[index] + 1;

      index.RunNumber = -1;
      index.EventNumber = -1;
   }

   TFile F(OutputFileName, "RECREATE");

   TH1D EventCountHistogram(Form("EventCountHistogram_%s", Tag),
      Form("%s;Number of times for events appearing", Tag), 5, -0.5, 4.5);

   for(map<EventIndex, int>::iterator iter = EventCounts.begin(); iter != EventCounts.end(); iter++)
   {
      EventCountHistogram.Fill(iter->second);

      if(iter->second > 1)
         cout << "Duplicate event!  Run = " << iter->first.RunNumber << ", Event = "
            << iter->first.EventNumber << ", Count = " << iter->second << endl;
   }

   EventCountHistogram.Write();

   // PsFileHelper PsFile("Output.ps");
   // PsFile.AddPlot(EventCountHistogram, "", true);
   // PsFile.Close();

   F.Close();

   return;
}



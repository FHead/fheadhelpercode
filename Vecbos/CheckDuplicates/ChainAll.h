#include <string>
#include <fstream>
#include <iostream>
using namespace std;

#include "TChain.h"
#include "TFile.h"

TChain *ChainAll(string list, string treename)
{
   TChain *chain = new TChain(treename.c_str());

   ifstream in(list.c_str());

   while(in)
   {
      char ch[1024] = "";
      ch[0] = '\0';

      in.getline(ch, 1023, '\n');

      if(ch[0] != '\0')
      {
         chain->AddFile(ch);
         cerr << "Chaining file " << ch << endl;
      }
   }

   in.close();

   cerr << "All files chained." << endl;

   return chain;
}


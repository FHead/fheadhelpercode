#include <iostream>
using namespace std;

#include "DataHelper.h"

int main(int argc, char *argv[])
{
   if(argc != 6)
   {
      cerr << "Usage: " << argv[0] << " DHFile State Key ValueType Value" << endl;
      return -1;
   }

   DataHelper DHFile(argv[1]);

   string ValueType = string(argv[4]);

   if(ValueType == "int" || ValueType == "integer")
      DHFile[argv[2]][argv[3]] = atoi(argv[5]);
   else if(ValueType == "int" || ValueType == "float")
      DHFile[argv[2]][argv[3]] = atof(argv[5]);
   else
      DHFile[argv[2]][argv[3]] = string(argv[5]);

   DHFile.SaveToFile();

   return 0;
}






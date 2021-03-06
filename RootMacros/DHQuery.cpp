#include <iostream>
using namespace std;

#include "DataHelper.h"

int main(int argc, char *argv[])
{
   if(argc != 4)
   {
      cerr << "Usage: " << argv[0] << " DHFile State Key" << endl;
      return -1;
   }

   DataHelper DHFile(argv[1]);

   if(DHFile.Exist(argv[2]) == false)
   {
      cerr << "State \"" << argv[2] << "\" does not exist" << endl;
      return -1;
   }

   if(DHFile[argv[2]].Exist(argv[3]) == false)
   {
      cerr << "Key \"" << argv[3] << "\" does not exist" << endl;
      return -1;
   }

   cout << DHFile[argv[2]][argv[3]].GetRepresentation() << endl;

   return 0;
}






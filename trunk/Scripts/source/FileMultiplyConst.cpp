#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cout << "Usage: FileMultiplyConst file constant outfile" << endl;
      return -1;
   }

   stringstream extractnumber(argv[2]);
   double constant = 0;
   extractnumber >> constant;

   ifstream in(argv[1]);

   ofstream out(argv[3]);
   out.precision(10);

   while(in)
   {
      double temp = -135798642;

      in >> temp;

      if(temp + 135798642 < 1e-8)
         break;

      out << temp * constant << endl;
   }

   out.close();

   in.close();

   return 0;
}


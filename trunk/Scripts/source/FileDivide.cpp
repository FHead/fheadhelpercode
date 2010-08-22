#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cout << "Usage: FileDivide file1 file2 outfile" << endl;
      return -1;
   }

   ifstream in1(argv[1]);
   ifstream in2(argv[2]);

   ofstream out(argv[3]);
   out.precision(10);

   while(in1 && in2)
   {
      double temp1 = -135798642;
      double temp2 = -135798642;

      in1 >> temp1;
      in2 >> temp2;

      if(temp1 + 135798642 < 1e-8 || temp2 + 135798642 < 1e-8)
         break;

      out << temp1 / temp2 << endl;
   }

   out.close();

   in2.close();
   in1.close();
}


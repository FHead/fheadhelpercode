#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cout << "Usage: FileInverse file outfile" << endl;
      return -1;
   }

   ifstream in(argv[1]);

   ofstream out(argv[2]);
   out.precision(10);

   while(in)
   {
      double temp = -135798642;

      in >> temp;

      if(temp + 135798642 < 1e-8)
         break;

      out << 1 / temp << endl;
   }

   out.close();

   in.close();
}


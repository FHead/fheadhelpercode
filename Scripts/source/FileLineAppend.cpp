#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cout << "Usage: FileLineAppend input1 input2 output" << endl;
      return -1;
   }

   string blocker = " ";
   if(argc == 5)
      blocker = argv[4];

   ifstream in1(argv[1]);
   ifstream in2(argv[2]);

   ofstream out(argv[3]);

   while(in1 || in2)
   {
      char text[102400] = "";

      in1.getline(text, 102399, '\n');
      out << text;

      out << blocker;

      text[0] = '\0';
      in2.getline(text, 102399, '\n');
      out << text;

      out << endl;
   }

   out.close();

   in2.close();
   in1.close();

   return 0;
}

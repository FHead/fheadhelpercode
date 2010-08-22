#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
   string usage = "Usage: meow!";

   if(argc <= 1)
   {
      cerr << usage << endl;
      return -1;
   }

   char character = '\0';

   if(argc >= 3)
      character = argv[2][0];

   fstream file(argv[1], ios::in | ios::out | ios::binary);

   file.seekg(0, ifstream::end);
   long long size = file.tellg();
   
   for(long long i = 0; i < size; i++)
   {
      file.seekp(ios_base::beg + i);
      file.put(character);
   }

   return 0;
}


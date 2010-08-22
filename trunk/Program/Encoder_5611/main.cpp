#include <iostream>
#include <cstdio>
#include <termios.h>
#include <string>
using namespace std;

#include "LSC.h"

int main(int argc, char *argv[]);
string GetPassword(string prompt);
double GetX0(string password);
double GetMu(string password);

int main(int argc, char *argv[])
{
   // command line parsing
   string UsageString = "Usage: " + string(argv[0]) + " [ED][S] InputFileName [OutputFileName] [Scheme]\n\nOptions:\n\tE\tEncrypt File\n\tD\tDecrypt File\n\tS\tOverwrite input file with encrypted file\n\nScheme is a string consists of 4 characters: eEdD.\n\te\tNormal encryption\n\tE\tJump encryption\n\td\tNormal decryption\n\tD\tJump decryption";

   if(argc <= 2)
   {
      cerr << UsageString << endl;
      return -1;
   }

   string option = argv[1];
   string inputfile = argv[2];
   string outputfile = "";
   string scheme = "eDe";

   bool encode = true;
   bool decode = true;

   if(find(option.begin(), option.end(), 'E') == option.end() && find(option.begin(), option.end(), 'e') == option.end())
      encode = false;
   if(find(option.begin(), option.end(), 'D') == option.end() && find(option.begin(), option.end(), 'd') == option.end())
      decode = false;

   if((encode == false && decode == false) ||
      (encode == true && decode == true))
   {
      cerr << UsageString << endl;
      return -1;
   }

   if(find(option.begin(), option.end(), 'S') != option.end())
   {
      outputfile = argv[2];

      if(argc >= 4)
         scheme = argv[3];
   }
   else
   {
      if(argc <= 3)
      {
         cerr << UsageString << endl;
         return -1;
      }

      outputfile = argv[3];

      if(argc >= 5)
         scheme = argv[4];
   }

   for(int i = 0; i < (int)scheme.size(); i++)
   {
      if(scheme[i] != 'e' && scheme[i] != 'E' && scheme[i] != 'd' && scheme[i] != 'D')
      {
         cerr << UsageString << endl;
         return -1;
      }
   }

   // passwords
   string password1 = GetPassword("Please enter password: ");
   string password2 = GetPassword("Please enter again: ");

   if(password1 != password2)
   {
      cerr << "Passwords do not match!" << endl;
      return -1;
   }

   // some outputs
   cout << endl;
   cout << "Encoding scheme: " << scheme << endl;

   // get initial values
   double x0 = GetX0(password1);
   double mu = GetMu(password1);

   // same file?
   if(inputfile != outputfile)
      CopyFile(inputfile, outputfile);

   // encode/decode
   if(encode == true)
   {
      for(int i = 0; i < (int)scheme.size(); i++)
      {
         bool jump = false;
         if(scheme[i] == 'E' || scheme[i] == 'D')
            jump = true;

         if(scheme[i] == 'e' || scheme[i] == 'E')
            EncryptFile(outputfile, x0, mu, 100000000, jump);
         else if(scheme[i] == 'd' || scheme[i] == 'D')
            DecryptFile(outputfile, x0, mu, 100000000, jump);

         cout << ".";
      }

      cout << "...Done." << endl;
   }
   else   // decode file
   {
      for(int i = (int)scheme.size() - 1; i >= 0; i--)
      {
         bool jump = false;
         if(scheme[i] == 'E' || scheme[i] == 'D')
            jump = true;

         if(scheme[i] == 'e' || scheme[i] == 'E')
            DecryptFile(outputfile, x0, mu, 100000000, jump);
         else if(scheme[i] == 'd' || scheme[i] == 'D')
            EncryptFile(outputfile, x0, mu, 100000000, jump);

         cout << ".";
      }

      cout << "...Done." << endl;
   }

   return 0;
}

string GetPassword(string prompt)
{
   cout << prompt;

   char password[10240] = "";
   int length = 0;

   struct termios oldt, newt;
   tcgetattr(STDIN_FILENO, &oldt);
   newt = oldt;
   newt.c_lflag &= ~(ICANON | ECHO);
   tcsetattr(STDIN_FILENO, TCSANOW, &newt);

   for(int i = 0; i < 10240; i++)
   {
      password[i] = getchar();

      if(password[i] == '\n')
      {
         length = i;
         break;
      }

      cerr << "*";
   }

   tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

   password[length] = '\0';

   cout << endl;

   return password;
}

double GetX0(string password)
{
   long long sum = 0;
   for(int i = 0; i < (int)password.size(); i++)
      sum = sum + password[i] * (i + 1);
   sum = sum % 100000000;
   if(sum < 0)
      sum = sum + 100000000;

   if(sum == 25000000 || sum == 50000000 || sum == 75000000 || sum == 0)
      sum = sum + 4;

   return (double)sum / 100000000;
}

double GetMu(string password)
{
   long long product = 1;
   for(int i = 0; i < (int)password.size(); i++)
      product = (product * (password[i] + i) + i) % 100000000;

   return 4 - (double)product / 100000000 / 4;
}



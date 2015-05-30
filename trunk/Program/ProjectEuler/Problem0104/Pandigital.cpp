#include <iostream>
#include <vector>
using namespace std;

int main();
bool IsTailPandigital(vector<int> &N);
bool IsHeadPandigital(vector<int> &N);
vector<int> Addition(vector<int> &N1, vector<int> &N2);
void PrintNumber(vector<int> &N);

int main()
{
   vector<int> NPrevious;
   vector<int> NCurrent;

   NPrevious.push_back(1);
   NCurrent.push_back(1);

   for(int N = 3; N < 1000000; N++)
   {
      vector<int> NNext = Addition(NPrevious, NCurrent);

      // cout << N << " ";
      // PrintNumber(NNext);
      
      bool Tail = IsTailPandigital(NNext);
      bool Head = IsHeadPandigital(NNext);

      if(Tail == true || Head == true)
         cout << N << (Head == true ? " head" : "") << (Tail == true ? " tail" : "") << endl;

      NPrevious = NCurrent;
      NCurrent = NNext;
   }

   return 0;
}

bool IsTailPandigital(vector<int> &N)
{
   if(N.size() < 9)
      return false;

   vector<bool> Log(10);

   for(int i = 0; i < 9; i++)
      Log[N[i]] = true;

   bool Result = true;
   for(int i = 1; i <= 9; i++)
      if(Log[i] == false)
         Result = false;

   return Result;
}

bool IsHeadPandigital(vector<int> &N)
{
   if(N.size() < 9)
      return false;

   vector<bool> Log(10);

   for(int i = (int)N.size() - 9; i < (int)N.size(); i++)
      Log[N[i]] = true;

   bool Result = true;
   for(int i = 1; i <= 9; i++)
      if(Log[i] == false)
         Result = false;

   return Result;
}

vector<int> Addition(vector<int> &N1, vector<int> &N2)
{
   int Digit = max(N1.size(), N2.size());

   vector<int> N(Digit);

   for(int i = 0; i < Digit; i++)
   {
      if(i < N1.size())   N[i] = N[i] + N1[i];
      if(i < N2.size())   N[i] = N[i] + N2[i];
   }

   for(int i = 0; i < Digit - 1; i++)
   {
      N[i+1] = N[i+1] + N[i] / 10;
      N[i] = N[i] % 10;
   }

   if(N[Digit-1] >= 10)
   {
      N.push_back(N[Digit-1] / 10);
      N[Digit-1] = N[Digit-1] % 10;
   }

   return N;
}

void PrintNumber(vector<int> &N)
{
   for(int i = (int)N.size() - 1; i >= 0; i--)
      cout << N[i];
   cout << endl;
}




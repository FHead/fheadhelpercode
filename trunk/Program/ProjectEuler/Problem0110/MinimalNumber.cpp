#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main();
vector<int> PrimeNumbers();
long long CountSolution(const vector<int> &N);
double GetLogNumber(const vector<int> &P, const vector<int> &N);
vector<int> FindBest(const vector<int> &P, const vector<int> &N, int Index, int Target);
void PrintN(const vector<int> &N, const vector<int> &P);

int main()
{
   vector<int> P = PrimeNumbers();
   vector<int> N(P.size());

   long long Target = 4000000;

   vector<int> BestN = FindBest(P, N, 0, Target);
   cout << exp(GetLogNumber(P, BestN)) << ", " << CountSolution(BestN) << endl;

   PrintN(BestN, P);

   return 0;
}

vector<int> PrimeNumbers()
{
   vector<int> Result;

   Result.push_back(2);
   Result.push_back(3);
   Result.push_back(5);
   Result.push_back(7);
   Result.push_back(11);

   for(int i = 13; i < 1000000; i = i + 2)
   {
      bool Prime = true;

      for(int j = 0; Result[j] * Result[j] <= i && Prime == true; j++)
         if(i % Result[j] == 0)
            Prime = false;

      if(Prime == true)
         Result.push_back(i);
   }

   return Result;
}

long long CountSolution(const vector<int> &N)
{
   long long Result = 1;
   for(int i = 0; i < (int)N.size(); i++)
      Result = Result * (2 * N[i] + 1);
   return (Result + 1) / 2;
}

double GetLogNumber(const vector<int> &P, const vector<int> &N)
{
   double Result = 0;
   for(int i = 0; i < (int)N.size(); i++)
      Result = Result + N[i] * log(P[i]);
   return Result;
}

vector<int> FindBest(const vector<int> &P, const vector<int> &N, int Index, int Target)
{
   // cout << "Index = " << Index << ", Target = " << Target << endl;
   // PrintN(N, P);

   vector<int> Current(N.size());

   if(Index == 0)
   {
      double BestNumber = -1;
      vector<int> BestN;

      for(int i = 0; i < (int)N.size(); i++)
         Current[i] = 0;

      int Max = Target;

      for(int i = 1; i <= Max; i++)
      {
         Current[0] = i;
         vector<int> Temp = FindBest(P, Current, Index + 1, Target);

         double Number = GetLogNumber(P, Temp);
         if(BestNumber < 0 || Number < BestNumber)
         {
            BestNumber = Number;
            BestN = Temp;
         }
         
         cout << "Progress: " << i << " / " << Max << endl;
         cout << "Best so far: " << CountSolution(BestN) << endl;
         PrintN(BestN, P);
      }

      return BestN;
   }
   else
   {
      for(int i = 0; i < (int)N.size(); i++)
         Current[i] = N[i];
      for(int i = Index; i < (int)N.size(); i++)
         Current[i] = 0;

      long long UpUntilNow = 1;
      for(int i = 0; i < Index; i++)
         UpUntilNow = UpUntilNow * (2 * N[i] + 1);
      // cout << UpUntilNow << endl;

      int Max = Current[Index-1];
      int TargetMax = (((double)Target * 2 - 1) / UpUntilNow - 1) / 2 + 1;

      // cout << Max << " " << TargetMax << endl;

      Max = min(Max, TargetMax);

      if(Max == 0)   // what is passed in is already good - return directly
         return Current;
      else   // otherwise loop and iterate
      {
         double BestNumber = -1;
         vector<int> BestN(N.size());

         for(int i = 1; i <= Max; i++)
         {
            Current[Index] = i;
            vector<int> Temp = FindBest(P, Current, Index + 1, Target);
            
            double Number = GetLogNumber(P, Temp);
            if(BestNumber < 0 || Number < BestNumber)
            {
               BestNumber = Number;
               BestN = Temp;
            }
         }

         return BestN;
      }
   }

   cerr << "You shall never reach here!" << endl;
   return vector<int>(N.size());
}

void PrintN(const vector<int> &N, const vector<int> &P)
{
   double LogNumber = GetLogNumber(P, N) / log(10);
   int Exponential = (int)LogNumber;
   double Remainder = LogNumber - Exponential;

   cout << "N =";
   for(int i = 0; i < (int)N.size() && N[i] > 0; i++)
      cout << " " << N[i];
   cout << " (" << exp(Remainder * log(10)) << " x 10^" << Exponential << ")" << endl;
}



// 4: 600x4 = 2400 = 3 points
// 2: 800x2 = 1600 = 2 points




#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

struct State;
ostream &operator <<(ostream &out, State S);
int main();
int CalculatePeriod(int N);

struct State
{
   // [sqrt(N) - C] / D
public:
   int N;
   int C;
   int D;
public:
   State Evolve()
   {
      State NewState;
      NewState.N = N;

      NewState.D = (N - C * C) / D;
      // if((N - C * C) % D != 0)
      //    cerr << "Warning!  Not divisible! " << N << " " << D << " " << C << endl;

      double Value = (sqrt(N) + C) / NewState.D;
      int IntValue = (int)Value;

      NewState.C = -(C - IntValue * NewState.D);

      return NewState;
   }
   bool operator ==(const State &other)
   {
      if(N != other.N)   return false;
      if(C != other.C)   return false;
      if(D != other.D)   return false;
      return true;
   }
   void Print(ostream &out)
   {
      out << "(" << N << ", " << C << ", " << D << ")";
   }
};

ostream &operator <<(ostream &out, State S)
{
   S.Print(out);

   return out;
}

int main()
{
   int Count = 0;

   for(int i = 1; i < 10000; i++)
   {
      // cout << "Starting " << i << endl;
      int Period = CalculatePeriod(i);
      // cout << "Period = " << Period << endl;

      if(Period % 2 == 1)
         Count = Count + 1;
   }

   cout << Count << endl;

   return 0;
}

int CalculatePeriod(int N)
{
   if((int)sqrt(N) * (int)sqrt(N) == N)
      return 0;

   State Temp;
   Temp.N = N;
   Temp.C = (int)sqrt(N);
   Temp.D = 1;

   // cout << Temp << endl;

   vector<State> SoFar;
   SoFar.push_back(Temp);

   bool Unique = true;
   while(Unique == true)
   {
      Temp = Temp.Evolve();
      
      if(find(SoFar.begin(), SoFar.end(), Temp) == SoFar.end())
         SoFar.push_back(Temp);
      else
         Unique = false;
      
      // cout << Temp << endl;
   }

   return SoFar.size();
}






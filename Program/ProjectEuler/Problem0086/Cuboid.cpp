#include <iostream>
#include <deque>
using namespace std;

struct Triple
{
   int A, B, C;
   Triple(int a, int b, int c)
      : A(a), B(b), C(c)
   {
      if(B > C)   swap(B, C);
      if(A > B)   swap(A, B);
      if(B > C)   swap(B, C);
   }
   bool operator <(const Triple &other) const
   {
      if(A < other.A)   return true;
      if(A > other.A)   return false;
      if(B < other.B)   return true;
      if(B > other.B)   return false;
      if(C < other.C)   return true;
      if(C > other.C)   return false;
      return false;
   }
   bool operator ==(const Triple &other) const
   {
      if(A != other.A)   return false;
      if(B != other.B)   return false;
      if(C != other.C)   return false;
      return false;
   }
   void Print(ostream &out)
   {
      out << "(" << A << ", " << B << ", " << C << ")";
   }
};

int main(int argc, char *argv[])
{
   deque<Triple> ToBeProcessed;
   deque<Triple> All;

   ToBeProcessed.push_back(Triple(3, 4, 5));
   
   int N = 2000;
   if(argc > 1)
      N = atoi(argv[1]);
   
   int Threshold = N * 2;

   while(ToBeProcessed.size() > 0)
   {
      Triple T = ToBeProcessed[0];
      ToBeProcessed.pop_front();
      All.push_back(T);

      Triple New1(1 * T.A - 2 * T.B + 2 * T.C, 2 * T.A - 1 * T.B + 2 * T.C, 2 * T.A - 2 * T.B + 3 * T.C);
      Triple New2(1 * T.A + 2 * T.B + 2 * T.C, 2 * T.A + 1 * T.B + 2 * T.C, 2 * T.A + 2 * T.B + 3 * T.C);
      Triple New3(-1 * T.A + 2 * T.B + 2 * T.C, -2 * T.A + 1 * T.B + 2 * T.C, -2 * T.A + 2 * T.B + 3 * T.C);

      if(New1.A <= Threshold && New1.B <= Threshold)   ToBeProcessed.push_back(New1);
      if(New2.A <= Threshold && New2.B <= Threshold)   ToBeProcessed.push_back(New2);
      if(New3.A <= Threshold && New3.B <= Threshold)   ToBeProcessed.push_back(New3);
   }

   // cout << All.size() << endl;

   deque<Triple> Cuboid;

   for(int i = 0; i < (int)All.size(); i++)
   {
      // cout << i << "/" << All.size() << endl;
      // All[i].Print(cout);
      // cout << endl;

      Triple TPrimitive = All[i];

      for(int j = 1; TPrimitive.B * j <= N || TPrimitive.A * j <= N; j++)
      {
         Triple T(TPrimitive.A * j, TPrimitive.B * j, TPrimitive.C * j);

         if(T.A <= N)
         {
            for(int k = 1; k <= T.B / 2; k++)
               if(k <= T.A && T.B - k <= T.A)
                  Cuboid.push_back(Triple(T.A, k, T.B - k));
         }
         if(T.B <= N)
         {
            for(int k = 1; k <= T.A / 2; k++)
               if(k <= T.B && T.A - k <= T.B)
                  Cuboid.push_back(Triple(T.B, k, T.A - k));
         }

         if(Cuboid.size() > 1000000)
         {
            sort(Cuboid.begin(), Cuboid.end());
            deque<Triple>::iterator iter = unique(Cuboid.begin(), Cuboid.end());
            Cuboid.erase(iter, Cuboid.end());
         }
      }
   }

   cout << Cuboid.size() << endl;

   deque<int> Tally(N + 1);
   for(int i = 0; i < (int)Cuboid.size(); i++)
      Tally[Cuboid[i].C] = Tally[Cuboid[i].C] + 1;

   deque<int> Total(N + 1);
   Total[0] = Tally[0];
   for(int i = 1; i < N + 1; i++)
      Total[i] = Total[i-1] + Tally[i];

   for(int i = 0; i < N + 1; i++)
      cout << i << " " << Total[i] << endl;

   return 0;
}







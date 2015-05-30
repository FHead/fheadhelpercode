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
};

int main()
{
   deque<Triple> ToBeProcessed;
   deque<int> Length;

   ToBeProcessed.push_back(Triple(3, 4, 5));
   
   int Threshold = 1500000;

   while(ToBeProcessed.size() > 0)
   {
      Triple T = ToBeProcessed[0];
      ToBeProcessed.pop_front();

      Length.push_back(T.A + T.B + T.C);

      Triple New1(1 * T.A - 2 * T.B + 2 * T.C, 2 * T.A - 1 * T.B + 2 * T.C, 2 * T.A - 2 * T.B + 3 * T.C);
      Triple New2(1 * T.A + 2 * T.B + 2 * T.C, 2 * T.A + 1 * T.B + 2 * T.C, 2 * T.A + 2 * T.B + 3 * T.C);
      Triple New3(-1 * T.A + 2 * T.B + 2 * T.C, -2 * T.A + 1 * T.B + 2 * T.C, -2 * T.A + 2 * T.B + 3 * T.C);

      if(New1.A + New1.B + New1.C <= Threshold)   ToBeProcessed.push_back(New1);
      if(New2.A + New2.B + New2.C <= Threshold)   ToBeProcessed.push_back(New2);
      if(New3.A + New3.B + New3.C <= Threshold)   ToBeProcessed.push_back(New3);
   }

   cout << Length.size() << endl;

   sort(Length.begin(), Length.end());

   int Log[1500001] = {0};

   for(int i = 0; i < (int)Length.size(); i++)
   {
      int L = Length[i];

      for(int j = 1; j * L <= Threshold; j++)
         Log[j*L] = Log[j*L] + 1;
   }

   int Count = 0;
   for(int i = 0; i <= Threshold; i++)
   {
      if(Log[i] == 1)
      {
         Count = Count + 1;
         cout << Count << " " << i << endl;
      }
   }

   cout << "Total is " << Count << endl;

   return 0;
}







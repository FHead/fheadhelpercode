#include <iostream>
#include <deque>
using namespace std;

struct Triple
{
   long long A, B, C;
   Triple(long long a, long long b, long long c)
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
   deque<long long> Length;

   ToBeProcessed.push_back(Triple(3, 4, 5));
   
   long long Threshold = 1000000000LL;

   while(ToBeProcessed.size() > 0)
   {
      Triple T = ToBeProcessed[0];
      ToBeProcessed.pop_front();

      if(T.C == T.B * 2 - 1 || T.C == T.B * 2 + 1 || T.C == T.B * 2)
      {
         cout << T.C << " " << T.C << " " << T.B * 2 << endl;
         Length.push_back(T.B * 2 + T.C * 2);
      }
      if(T.C == T.A * 2 - 1 || T.C == T.A * 2 + 1 || T.C == T.A * 2)
      {
         cout << T.C << " " << T.C << " " << T.A * 2 << endl;
         Length.push_back(T.A * 2 + T.C * 2);
      }

      Triple New1(1 * T.A - 2 * T.B + 2 * T.C, 2 * T.A - 1 * T.B + 2 * T.C, 2 * T.A - 2 * T.B + 3 * T.C);
      Triple New2(1 * T.A + 2 * T.B + 2 * T.C, 2 * T.A + 1 * T.B + 2 * T.C, 2 * T.A + 2 * T.B + 3 * T.C);
      Triple New3(-1 * T.A + 2 * T.B + 2 * T.C, -2 * T.A + 1 * T.B + 2 * T.C, -2 * T.A + 2 * T.B + 3 * T.C);

      if(New1.C <= Threshold / 2 + 10)   ToBeProcessed.push_front(New1);
      if(New2.C <= Threshold / 2 + 10)   ToBeProcessed.push_front(New2);
      if(New3.C <= Threshold / 2 + 10)   ToBeProcessed.push_front(New3);
   }

   cout << "Number of triangles found = " << Length.size() << endl;
   for(int i = 0; i < (int)Length.size(); i++)
      cout << Length[i] << endl;

   return 0;
}







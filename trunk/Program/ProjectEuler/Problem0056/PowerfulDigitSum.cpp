#include <iostream>
#include <vector>
using namespace std;

class BigNumber;
ostream &operator <<(ostream &out, BigNumber N);
int main();

class BigNumber
{
public:
   vector<int> Digits;
public:
   BigNumber()
   {
      Digits.clear();
      Digits.push_back(0);
   }
   BigNumber(int Value)
   {
      Digits.clear();
      while(Value > 0)
      {
         Digits.push_back(Value % 10);
         Value = Value / 10;
      }
   }
   ~BigNumber()
   {
      Digits.clear();
   }
   BigNumber operator +(const BigNumber &other)
   {
      BigNumber Result;
      Result.Digits = Digits;
      Result.Digits.resize(other.Digits.size());

      for(int i = 0; i < (int)Result.Digits.size(); i++)
         if(i < other.Digits.size())
            Result.Digits[i] = Result.Digits[i] + other.Digits[i];

      Result.Reorder();

      return Result;
   }
   BigNumber operator *(const BigNumber &other)
   {
      BigNumber Result;
      Result.Digits.resize(Digits.size() + other.Digits.size() + 1);

      for(int i = 0; i < (int)Digits.size(); i++)
         for(int j = 0; j < (int)other.Digits.size(); j++)
            Result.Digits[i+j] = Result.Digits[i+j] + Digits[i] * other.Digits[j];

      Result.Reorder();

      return Result;
   }
   void Reorder()
   {
      for(int i = 0; i < (int)Digits.size() - 1; i++)
      {
         if(Digits[i] >= 10)
         {
            Digits[i+1] = Digits[i+1] + Digits[i] / 10;
            Digits[i] = Digits[i] % 10;
         }
      }
      while(Digits[Digits.size()-1] == 0 && Digits.size() > 1)
         Digits.erase(Digits.begin() + ((int)Digits.size() - 1));
      while(Digits[Digits.size()-1] >= 10)
      {
         Digits.push_back(Digits[Digits.size()-1] / 10);
         Digits[Digits.size()-2] = Digits[Digits.size()-2] % 10;
      }
   }
   void Print(ostream &out)
   {
      for(int i = (int)Digits.size() - 1; i >= 0; i--)
         out << Digits[i];
   }
   int DigitSum()
   {
      int Sum = 0;
      for(int i = 0; i < (int)Digits.size(); i++)
         Sum = Sum + Digits[i];
      return Sum;
   }
};

ostream &operator <<(ostream &out, BigNumber N)
{
   N.Print(out);
   return out;
}

int main()
{
   int MaxSum = 0;

   for(int a = 1; a < 100; a++)
   {
      for(int b = 1; b < 100; b++)
      {
         BigNumber N(1);
         BigNumber A(a);

         for(int i = 0; i < b; i++)
            N = N * A;

         cout << a << " " << b << " " << N << " " << N.DigitSum() << endl;

         int DigitSum = N.DigitSum();

         if(DigitSum > MaxSum)
            MaxSum = DigitSum;
      }
   }

   cout << "Maximum: " << MaxSum << endl;

   return 0;
}



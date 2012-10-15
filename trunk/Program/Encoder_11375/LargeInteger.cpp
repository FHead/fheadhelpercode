//----------------------------------------------------------------------------
#include <iostream>
#include <vector>
//----------------------------------------------------------------------------
#include "LargeInteger.h"
//----------------------------------------------------------------------------
LargeInteger::LargeInteger()
{
   Sign = true;
   Value.push_back(0);
}
//----------------------------------------------------------------------------
LargeInteger::LargeInteger(int value)
{
   Value.clear();
   Value.push_back(abs(value));

   if(value >= 0)
      Sign = true;
   else
      Sign = false;

   SortOutDigits();
}
//----------------------------------------------------------------------------
void LargeInteger::SortOutDigits()
{
   if(Value.size() == 0)
   {
      Sign = true;
      Value.clear();
      Value.push_back(0);
      return;
   }

   // Destroy leading zeros
   while(Value.size() > 0 && Value[Value.size()-1] == 0)
      Value.erase(Value.begin() + (Value.size() - 1));
   if(Value.size() == 0)
   {
      Sign = true;
      Value.push_back(0);
      return;
   }

   // Deal with negative and large entries
   for(int i = 0; i < (int)Value.size() - 1; i++)
   {
      if(Value[i] < 0)
      {
         int N = abs(Value[i]) / LargeIntegerDigitLimit;
         Value[i] = Value[i] + LargeIntegerDigitLimit * (N + 1);
         Value[i+1] = Value[i+1] - (N + 1);
      }
      if(Value[i] >= LargeIntegerDigitLimit)
      {
         int N = Value[i] / LargeIntegerDigitLimit;
         Value[i] = Value[i] - LargeIntegerDigitLimit * N;
         Value[i+1] = Value[i+1] + N;
      }
   }
   if(Value[Value.size()-1] < 0)
   {
      Sign = !Sign;
      for(int i = 0; i < (int)Value.size(); i++)
         Value[i] = -Value[i];

      for(int i = 0; i < (int)Value.size() - 1; i++)
      {
         if(Value[i] < 0)
         {
            int N = abs(Value[i]) / LargeIntegerDigitLimit;
            Value[i] = Value[i] + LargeIntegerDigitLimit * (N + 1);
            Value[i+1] = Value[i+1] - (N + 1);
         }
         if(Value[i] >= LargeIntegerDigitLimit)
         {
            int N = Value[i] / LargeIntegerDigitLimit;
            Value[i] = Value[i] - LargeIntegerDigitLimit * N;
            Value[i+1] = Value[i+1] + N;
         }
      }
   }
   while(Value[Value.size()-1] >= LargeIntegerDigitLimit)
   {
      int N = Value[Value.size()-1] / LargeIntegerDigitLimit;
      Value[Value.size()-1] = Value[Value.size()-1] - LargeIntegerDigitLimit * N;
      Value.push_back(N);
   }
}
//----------------------------------------------------------------------------
LargeInteger &LargeInteger::operator =(const LargeInteger &other)
{
   Sign = other.Sign;
   Value = other.Value;

   return *this;
}
//----------------------------------------------------------------------------
LargeInteger LargeInteger::operator +(const LargeInteger &other) const
{
   if(Sign != other.Sign)
   {
      LargeInteger MinusOther = other;
      MinusOther.Sign = !MinusOther.Sign;

      return *this - MinusOther;
   }

   LargeInteger Result;
   Result.Sign = Sign;
   Result.Value.resize(std::max(Value.size(), other.Value.size()));

   for(int i = 0; i < (int)Result.Value.size(); i++)
   {
      int A = 0;
      int B = 0;
      if(i < (int)Value.size())         A = Value[i];
      if(i < (int)other.Value.size())   B = other.Value[i];
      Result.Value[i] = A + B;
   }

   Result.SortOutDigits();

   return Result;
}
//----------------------------------------------------------------------------
LargeInteger LargeInteger::operator -(const LargeInteger &other) const
{
   if(Sign != other.Sign)
   {
      LargeInteger MinusOther = other;
      MinusOther.Sign = !MinusOther.Sign;

      return *this + MinusOther;
   }

   LargeInteger Result;
   Result.Sign = Sign;
   Result.Value.resize(std::max(Value.size(), other.Value.size()));

   for(int i = 0; i < (int)Result.Value.size(); i++)
   {
      int A = 0;
      int B = 0;
      if(i < (int)Value.size())         A = Value[i];
      if(i < (int)other.Value.size())   B = other.Value[i];
      Result.Value[i] = A - B;
   }

   Result.SortOutDigits();

   return Result;
}
//----------------------------------------------------------------------------
LargeInteger LargeInteger::operator -() const
{
   LargeInteger Result;

   Result.Sign = !Sign;
   Result.Value = Value;

   return Result;
}
//----------------------------------------------------------------------------
LargeInteger LargeInteger::ShiftOutDigits(int N) const
{
   if(LargeIntegerDigitLimit == 1000)
   {
      int X = N / 3;
      int Y = N % 3;

      if(Value.size() <= X)
         return LargeInteger(0);

      LargeInteger Result = *this;
      Result.Value.erase(Result.Value.begin() + (Value.size() - X), Result.Value.end());

      if(Y == 1)
         Result = Result / 10;
      else if(Y == 2)
         Result = Result / 100;

      return Result;
   }

   LargeInteger Result = *this;

   for(int i = 0; i < N / 8; i++)
      Result = Result / 100000000;
   for(int i = 0; i < N % 8; i++)
      Result = Result / 10;

   return Result;
}
//----------------------------------------------------------------------------
LargeInteger LargeInteger::operator *(const LargeInteger &other) const
{
   LargeInteger Result;
   Result.Sign = !(Sign ^ other.Sign);

   int Size1 = Value.size();
   int Size2 = other.Value.size();

   if(Size1 < 100 && Size2 < 100)
   {
      static int V1[100] = {0};
      static int V2[100] = {0};
      static int V3[200] = {0};

      for(int i = 0; i < Size1; i++)
         V1[i] = Value[i];
      for(int i = 0; i < Size2; i++)
         V2[i] = other.Value[i];
      for(int i = 0; i < Size1 + Size2; i++)
         V3[i] = 0;

      for(int i = 0; i < Size1; i++)
         for(int j = 0; j < Size2; j++)
            V3[i+j] = V3[i+j] + V1[i] * V2[j];

      Result.Value = std::vector<int>(V3, V3 + (Size1 + Size2));
      Result.SortOutDigits();

      return Result;
   }

   Result.Value.resize(Size1 + Size2);
   for(int i = 0; i < Size1; i++)
      for(int j = 0; j < Size2; j++)
         Result.Value[i+j] = Result.Value[i+j] + Value[i] * other.Value[j];

   Result.SortOutDigits();

   return Result;
}
//----------------------------------------------------------------------------
int LargeInteger::operator %(int number) const
{
   if(Value.size() == 0)
      return 0;

   int LimitResidual = LargeIntegerDigitLimit % number;
   int CurrentLimitResidual = 1;

   int Answer = Value[0];
   for(int i = 1; i < (int)Value.size(); i++)
   {
      Answer = Answer + (Value[i] * CurrentLimitResidual) % number;
      CurrentLimitResidual = (CurrentLimitResidual * LimitResidual) % number;
   }
   Answer = Answer % LimitResidual;

   return Answer;
}
//----------------------------------------------------------------------------
LargeInteger LargeInteger::operator /(int number) const
{
   if(number == LargeIntegerDigitLimit)
   {
      LargeInteger Result;
      Result.Value = Value;
      Result.Sign = Sign;

      if(Value.size() > 0)
         Result.Value.erase(Result.Value.begin());

      return Result;
   }

   LargeInteger Result = *this;
   Result.Sign = !((number >= 0) ^ Sign);

   if(number < 0)
      number = -number;

   for(int i = (int)Result.Value.size() - 1; i >= 0; i--)
   {
      int Q = Result.Value[i] / number;
      int R = Result.Value[i] % number;

      if(i != 0)
         Result.Value[i-1] = R * LargeIntegerDigitLimit + Result.Value[i-1];
      Result.Value[i] = Q;
   }

   Result.SortOutDigits();

   return Result;
}
//----------------------------------------------------------------------------
bool LargeInteger::operator <(const LargeInteger &other) const
{
   if(Sign == false && other.Sign == true)
      return true;
   if(Sign == true && other.Sign == false)
      return false;

   if(Sign == false && other.Sign == false)
      return -other < -(*this);

   if(Value.size() < other.Value.size())
      return true;
   if(Value.size() > other.Value.size())
      return false;

   for(int i = (int)Value.size() - 1; i >= 0; i--)
   {
      if(Value[i] < other.Value[i])
         return true;
      if(Value[i] > other.Value[i])
         return false;
   }

   return false;
}
//----------------------------------------------------------------------------
LargeInteger LargeInteger::RaiseToPower(int X) const
{
   if(X < 0)
      return 0;

   LargeInteger Result(1);

   for(int i = 0; i < X; i++)
      Result = Result * (*this);

   return Result;
}
//----------------------------------------------------------------------------
void LargeInteger::Print(std::ostream &out) const
{
   if(Sign == false)
      out << "-";

   if(LargeIntegerDigitLimit == 10)
   {
      for(int i = (int)Value.size() - 1; i >= 0; i--)
         out << Value[i];
   }
   else if(LargeIntegerDigitLimit == 1000)
   {
      for(int i = (int)Value.size() - 1; i >= 0; i--)
      {
         if(i != (int)Value.size() - 1)
         {
            if(Value[i] < 100)   out << "0";
            if(Value[i] < 10)    out << "0";
         }

         out << Value[i];
         if(i != 0)
            out << ",";
      }
   }
   else
   {
      out << "(";
      for(int i = (int)Value.size() - 1; i >= 0; i--)
      {
         out << Value[i];
         if(i != 0)
            out << ",";
      }
      out << ")";
   }
}
//----------------------------------------------------------------------------
std::ostream &operator <<(std::ostream &out, const LargeInteger &I)
{
   I.Print(out);
   return out;
}
//----------------------------------------------------------------------------




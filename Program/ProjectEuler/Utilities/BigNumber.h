#include <vector>

class BigNumber
{
public:
   bool Sign;
   std::vector<int> Digits;
public:
   BigNumber()
   {
      Sign = true;
      Digits.clear();
      Digits.push_back(0);
   }
   BigNumber(int Value)
   {
      Sign = true;
      if(Value < 0)
      {
         Value = -Value;
         Sign = false;
      }

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
   bool IsZero() const
   {
      if(Digits.size() == 0)
         return true;
      if(Digits.size() == 1 && Digits[0] == 0)
         return true;
      return false;
   }
   bool IsPositive() const
   {
      if(IsZero() == false && Sign == true)
         return true;
      return false;
   }
   bool IsNegative() const
   {
      if(IsZero() == false && Sign == false)
         return true;
      return false;
   }
   bool operator <(const BigNumber &other) const
   {
      if(IsNegative() == true && other.IsZero() == true)
         return true;
      if(IsNegative() == true && other.IsPositive() == true)
         return true;
      if(IsZero() == true && other.IsPositive() == true)
         return true;

      int Answer = 0;

      if(Digits.size() > other.Digits.size())
         Answer = -1;
      else if(Digits.size() < other.Digits.size())
         Answer = 1;
      else
      {
         for(int i = (int)Digits.size() - 1; i >= 0 && Answer == 0; i--)
         {
            if(Digits[i] < other.Digits[i])
               Answer = 1;
            else
               Answer = -1;
         }
      }

      if(Answer == 1 && Sign == true)
         return true;
      if(Answer == -1 && Sign == false)
         return true;

      return false;
   }
   BigNumber operator +(const BigNumber &other)
   {
      if(Sign != other.Sign)
      {
         BigNumber Temp = other;
         Temp.Sign = !Temp.Sign;
         return *this - Temp;
      }
         
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

      if(Sign == other.Sign)
         Result.Sign = true;
      else
         Result.Sign = false;

      return Result;
   }
   int operator [](int index)
   {
      if(index >= Digits.size())
         return 0;
      return Digits[index];
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
      if(Sign == false)
         out << "-";
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



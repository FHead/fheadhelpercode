//----------------------------------------------------------------------------
#ifndef LARGEINTEGER_H_19283751928375192837512
#define LARGEINTEGER_H_19283751928375192837512
//----------------------------------------------------------------------------
#include <iostream>
#include <vector>
//----------------------------------------------------------------------------
#define LargeIntegerDigitLimit 1000
//----------------------------------------------------------------------------
class LargeInteger;
std::ostream &operator <<(std::ostream &out, const LargeInteger &I);
//----------------------------------------------------------------------------
class LargeInteger
{
private:
   bool Sign;   // true = positive
   std::vector<int> Value;
public:
   LargeInteger();
   LargeInteger(int value);
private:
   void SortOutDigits();
public:
   LargeInteger &operator =(const LargeInteger &other);
   LargeInteger operator +(const LargeInteger &other) const;
   LargeInteger operator -(const LargeInteger &other) const;
   LargeInteger operator -() const;
   LargeInteger operator *(const LargeInteger &other) const;
   LargeInteger ShiftOutDigits(int N) const;
   int operator %(int number) const;
   LargeInteger operator /(int number) const;
   bool operator <(const LargeInteger &other) const;
   LargeInteger RaiseToPower(int X) const;
   void Print(std::ostream &out) const;
};
//----------------------------------------------------------------------------
#endif












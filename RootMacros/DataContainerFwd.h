//---------------------------------------------------------------------------
#ifndef DATACONTAINER_H_6427_FHEAD_AJGKFVNGERINHGANGKFKAKNARGN
#define DATACONTAINER_H_6427_FHEAD_AJGKFVNGERINHGANGKFKAKNARGN
//---------------------------------------------------------------------------
#include <string>
#include <istream>
#include <ostream>
#include <sstream>
#include <algorithm>
using namespace std;
//---------------------------------------------------------------------------
class DataContainer;
union DataMessenger;
//---------------------------------------------------------------------------
ostream &operator <<(ostream &out, DataContainer data);
istream &operator >>(istream &in, DataContainer &data);
//---------------------------------------------------------------------------
void IntegerToChar4(int Number, char ChNumber[4]);
long long Char4ToInteger(char ChNumber[4]);
//---------------------------------------------------------------------------
class DataContainer
{
   friend class DataHelper;
   friend class StateContainer;
public:
   enum {DataTypeNone, DataTypeString, DataTypeDouble, DataTypeInteger};
private:
   string StringValue;
   double DoubleValue;
   long long IntegerValue;
   int Type;
public:
   DataContainer();
   DataContainer(string value);
   DataContainer(double value);
   DataContainer(long long value);
   ~DataContainer();
   long long GetInteger();
   double GetDouble();
   string GetString();
   string GetRepresentation();
   int GetType();
   DataContainer &operator =(string value);
   DataContainer &operator =(double value);
   DataContainer &operator =(int value);
   DataContainer &operator =(long long value);
   DataContainer &operator =(DataContainer &other);
   bool operator <(string value) const { return *this < DataContainer(value); }
   bool operator <(double value) const { return *this < DataContainer(value); }
   bool operator <(long long value) const { return *this < DataContainer(value); }
   bool operator <(const DataContainer &other) const;
   bool operator <=(string value) const { return *this <= DataContainer(value); }
   bool operator <=(double value) const { return *this <= DataContainer(value); }
   bool operator <=(long long value) const { return *this <= DataContainer(value); }
   bool operator <=(const DataContainer &other) const { return *this < other || *this == other; }
   bool operator >(string value) const { return *this > DataContainer(value); }
   bool operator >(double value) const { return *this > DataContainer(value); }
   bool operator >(long long value) const { return *this > DataContainer(value); }
   bool operator >(const DataContainer &other) const { return *this >= other && *this != other; }
   bool operator >=(string value) const { return *this >= DataContainer(value); }
   bool operator >=(double value) const { return *this >= DataContainer(value); }
   bool operator >=(long long value) const { return *this >= DataContainer(value); }
   bool operator >=(const DataContainer &other) const { return !(*this < other); }
   bool operator ==(string value) const { return *this == DataContainer(value); }
   bool operator ==(double value) const { return *this == DataContainer(value); }
   bool operator ==(long long value) const { return *this == DataContainer(value); }
   bool operator ==(const DataContainer &other) const;
   bool operator !=(string value) const { return *this != DataContainer(value); }
   bool operator !=(double value) const { return *this != DataContainer(value); }
   bool operator !=(long long value) const { return *this != DataContainer(value); }
   bool operator !=(const DataContainer &other) const { return !(*this == other); }
   DataContainer operator +(const DataContainer &other);   // none: nothing, string: concatenation, numbers: addition
   DataContainer operator -(const DataContainer &other);   // none: nothing, string: nothing, numbers: subtraction
   DataContainer operator *(const DataContainer &other);   // none: nothing, string * string: concatenation, string * number: repetition, numbers: multiplication
   DataContainer operator /(const DataContainer &other);   // none: nothing, string: nothing, numbers: division
   DataContainer operator -();   // none: nothing, string: reverse, numbers: negation
   void SaveToStream(ostream &out);
   void LoadFromStream(istream &in);
};
//---------------------------------------------------------------------------
union DataMessenger
{
   char CharValue[20];   // 20 bytes should be enough for all numbers?
   double DoubleValue;
   long long LongLongValue;
   int IntegerValue;
};
//---------------------------------------------------------------------------
#endif

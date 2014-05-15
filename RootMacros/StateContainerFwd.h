//---------------------------------------------------------------------------
#ifndef STATECONTAINER_H_6427_FHEAD_JFRNHGKIARFNHSGKNLAGRKIR
#define STATECONTAINER_H_6427_FHEAD_JFRNHGKIARFNHSGKNLAGRKIR
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <map>
using namespace std;
//---------------------------------------------------------------------------
#include "DataContainerFwd.h"
//---------------------------------------------------------------------------
class StateContainer;
//---------------------------------------------------------------------------
ostream &operator <<(ostream &out, StateContainer &data);
istream &operator >>(istream &in, StateContainer &data);
//---------------------------------------------------------------------------
class StateContainer
{
   friend class DataHelper;
private:
   map<string, DataContainer> Data;
public:
   StateContainer();
   ~StateContainer();
private:
   void Initialize();
   void CleanUp();
public:
   vector<string> GetListOfKeys();
   DataContainer &operator [](string Key);   // get single object
   void Insert(string Key, DataContainer NewData);
   bool Exist(string Key);
   void Touch(string Key);
   void Delete(string Key);
   string GetRepresentation(string Key);   // get representation of single value
   string GetRepresentation();   // get representation of whole object
   void SaveToStream(ostream &out);
   void LoadFromStream(istream &in);
   StateContainer &operator =(StateContainer &other);
};
//---------------------------------------------------------------------------
#endif

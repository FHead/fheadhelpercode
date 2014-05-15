//---------------------------------------------------------------------------
#ifndef DATAHELPER_H_6427_FHEAD_JANHIWFWKIGHWKIDAGFBAFKER
#define DATAHELPER_H_6427_FHEAD_JANHIWFWKIGHWKIDAGFBAFKER
//---------------------------------------------------------------------------
#include <string>
#include <cstring>
#include <istream>
#include <ostream>
#include <fstream>
#include <map>
using namespace std;
//---------------------------------------------------------------------------
#include "StateContainerFwd.h"
//---------------------------------------------------------------------------
class DataHelper;
//---------------------------------------------------------------------------
ostream &operator <<(ostream &out, DataHelper &data);
istream &operator >>(istream &in, DataHelper &data);
//---------------------------------------------------------------------------
class DataHelper
{
private:
   map<string, StateContainer> States;
   char ConstantHeader[32];
public:
   DataHelper();
   DataHelper(string FileName);
   ~DataHelper(); 
private:
   void Initialize();
   void CleanUp();
public:
   StateContainer &operator [](string Key);
   vector<string> GetListOfKeys();
   bool Exist(string Key);
   void Touch(string Key);
   void Insert(string Key, StateContainer NewState);
   void Erase(string Key);
   string GetRepresentation();
   string GetRepresentation(string Key);
   DataHelper &operator =(DataHelper &other);
   void LoadFromFile(string FileName);
   void SaveToFile(string FileName);
   void LoadFromStream(istream &in);
   void SaveToStream(ostream &out);
};
//---------------------------------------------------------------------------
#endif


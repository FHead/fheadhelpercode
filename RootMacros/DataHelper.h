//---------------------------------------------------------------------------
#ifndef DATAHELPER_H_6427_FHEAD_JANHIWFWKIGHWKIDAGFBAFKER
#define DATAHELPER_H_6427_FHEAD_JANHIWFWKIGHWKIDAGFBAFKER
//---------------------------------------------------------------------------
#include <string>
#include <istream>
#include <ostream>
#include <map>
using namespace std;
//---------------------------------------------------------------------------
#include "StateContainer.h"
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
DataHelper::DataHelper()
{
   Initialize();
}
//---------------------------------------------------------------------------
DataHelper::DataHelper(string FileName)
{
   Initialize();
   LoadFromFile(FileName);
}
//---------------------------------------------------------------------------
DataHelper::~DataHelper()
{
   CleanUp();
}
//---------------------------------------------------------------------------
void DataHelper::Initialize()
{
   memset(ConstantHeader, '\0', 32);
   strcpy(ConstantHeader, "DataHelperFHead6427");
}
//---------------------------------------------------------------------------
void DataHelper::CleanUp()
{
   States.clear();
}
//---------------------------------------------------------------------------
StateContainer &DataHelper::operator [](string Key)
{
   Touch(Key);
   
   return States[Key];
}
//---------------------------------------------------------------------------
vector<string> DataHelper::GetListOfKeys()
{
   vector<string> Keys;

   for(map<string, StateContainer>::iterator iter = States.begin(); iter != States.end(); iter++)
      Keys.push_back(iter->first);
      
   return Keys;
}
//---------------------------------------------------------------------------
void DataHelper::Touch(string Key)
{
   if(States.find(Key) != States.end())
      return;
      
   StateContainer NewState;
   States.insert(pair<string, StateContainer>(Key, NewState));
}
//---------------------------------------------------------------------------
void DataHelper::Insert(string Key, StateContainer NewState)
{
   Touch(Key);
   
   States[Key] = NewState;
}
//---------------------------------------------------------------------------
void DataHelper::Erase(string Key)
{
   if(States.find(Key) == States.end())
      return;
   
   States.erase(States.find(Key));
}
//---------------------------------------------------------------------------
string DataHelper::GetRepresentation()
{
   string Representation = "[";

   bool FirstItem = true;
   
   for(map<string, StateContainer>::iterator iter = States.begin(); iter != States.end(); iter++)
   {
      if(FirstItem == true)
         FirstItem = false;
      else
         Representation = Representation + ", ";
      
      Representation = Representation + "\"" + iter->first + "\" -- " + iter->second.GetRepresentation();
   }

   Representation = Representation + "]";

   return Representation;
}
//---------------------------------------------------------------------------
string DataHelper::GetRepresentation(string Key)
{
   if(States.find(Key) == States.end())
      return "STATENOTFOUND";
   
   return States[Key].GetRepresentation();
}
//---------------------------------------------------------------------------
DataHelper &DataHelper::operator =(DataHelper &other)
{
   States = other.States;
   
   return *this;
}
//---------------------------------------------------------------------------
void DataHelper::LoadFromFile(string FileName)
{
   ifstream in(FileName.c_str());
   LoadFromStream(in);
   in.close();
}
//---------------------------------------------------------------------------
void DataHelper::SaveToFile(string FileName)
{
   ofstream out(FileName.c_str());
   SaveToStream(out);
   out.close();
}
//---------------------------------------------------------------------------
void DataHelper::LoadFromStream(istream &in)
{
   char Header[33];
   in.read(Header, 32);
   Header[32] = '\0';
   
   if(strcmp(Header, ConstantHeader) != 0)   // wrong file type
      return;
   
   char EntryCountChar[4];
   in.read(EntryCountChar, 4);
   int EntryCount = Char4ToInteger(EntryCountChar);
   
   for(int i = 0; i < EntryCount; i++)
   {
      char KeySizeChar[4] = "";
      in.read(KeySizeChar, 4);
      int KeySize = Char4ToInteger(KeySizeChar);
      
      char *ch = new char[KeySize+1];
      in.read(ch, KeySize);
      ch[KeySize] = '\0';
      
      string Key = ch;
      delete[] ch;
      
      StateContainer NewState;
      NewState.LoadFromStream(in);
      
      States.insert(pair<string, StateContainer>(Key, NewState));
   }
}
//---------------------------------------------------------------------------
void DataHelper::SaveToStream(ostream &out)
{
   out.write(ConstantHeader, 32);
   
   char EntryCount[4];
   IntegerToChar4(States.size(), EntryCount);
   out.write(EntryCount, 4);
   
   for(map<string, StateContainer>::iterator iter = States.begin(); iter != States.end(); iter++)
   {
      char KeySize[4];
      IntegerToChar4(iter->first.size(), KeySize);

      out.write(KeySize, 4);
      out.write(iter->first.c_str(), iter->first.size());

      iter->second.SaveToStream(out);
   }
}
//---------------------------------------------------------------------------
ostream &operator <<(ostream &out, DataHelper &data)
{
   out << data.GetRepresentation();
   return out;
}
//---------------------------------------------------------------------------
istream &operator >>(istream &in, DataHelper &data)
{
   data.LoadFromStream(in);
   return in;
}
//---------------------------------------------------------------------------
#endif


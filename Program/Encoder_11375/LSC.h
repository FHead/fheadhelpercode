//---------------------------------------------------------------------------
#ifndef LSC_H_11375_WQKIWAVGFWQHNGVIQAHNGQRFG
#define LSC_H_11375_WQKIWAVGFWQHNGVIQAHNGQRFG
//---------------------------------------------------------------------------
#include <string>
using namespace std;
//---------------------------------------------------------------------------
#include "LargeInteger.h"
//---------------------------------------------------------------------------
#define MUPRECISION 8
#define XPRECISION 137
//---------------------------------------------------------------------------
LargeInteger NextNumber(LargeInteger previous, LargeInteger mu);
LargeInteger IterateNumber(LargeInteger previous, LargeInteger mu, int iteration);
int GetNumber(LargeInteger x);
//---------------------------------------------------------------------------
void CopyFile(string SourceFileName, string TargetFileName);
//---------------------------------------------------------------------------
void EncryptFile(string FileName, LargeInteger x0, LargeInteger mu, bool jump = false);
void DecryptFile(string FileName, LargeInteger x0, LargeInteger mu, bool jump = false);
//---------------------------------------------------------------------------
#endif


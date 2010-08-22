//---------------------------------------------------------------------------
#ifndef LSC_H_5611_WQKIWAVGFWQHNGVIQAHNGQRFG
#define LSC_H_5611_WQKIWAVGFWQHNGVIQAHNGQRFG
//---------------------------------------------------------------------------
#include <string>
using namespace std;
//---------------------------------------------------------------------------
double NextNumber(double previous, double mu, double precision);
double IterateNumber(double previous, double mu, double precision, int iteration);
int GetNumber(double x, double precision);
//---------------------------------------------------------------------------
void CopyFile(string SourceFileName, string TargetFileName);
//---------------------------------------------------------------------------
void EncryptFile(string FileName, double x0, double mu, double precision, bool jump = false);
void DecryptFile(string FileName, double x0, double mu, double precision, bool jump = false);
//---------------------------------------------------------------------------
#endif


//---------------------------------------------------------------------------
#ifndef LSCYICHEN20041223_H
#define LSCYICHEN20041223_H
//---------------------------------------------------------------------------
//
//   LSC.h
//   Date : 2004/12/23
//   By : Yi Chen
//   Contains definitions of basic functions for logistic stream cipher
//
//---------------------------------------------------------------------------
#include <string>

using namespace std;
//---------------------------------------------------------------------------
//   constant definitions
#define LSC_MODE_ORIGINAL 0
#define LSC_MODE_JUMPED 1
//---------------------------------------------------------------------------
//   inside functions
double _next_number(double _previous, double _mju, double _precision);
   // _previous : previous number
   // _mju : the parameter for logistic equation
   // _precision : could be 100000000, whenever we produces a new number,
   //    discard small fraction that is smaller than 1 / (_precision)
int _get_number(double x, double precision);
   // x : the iterated number (0 ~ 1)
   // precision : could be 100000000, answer = (x * precision) % 256;
void _LSC_original(string plain_text_filename, string cipher_text_filename, double x0, double mju, double precision);
	// plain_text_filename : just as it said
	// cipher_text_filename : just as it said
	// x0 : initial value for logistic equation
   // mju : the parameter for logistic equation
   // precision : could be 100000000, whenever we produces a new number,
   //    discard small fraction that is smaller than 1 / (_precision)
void _LSC_encrypt_jumped(string plain_text_filename, string cipher_text_filename, double x0, double mju, double precision);
	// plain_text_filename : just as it said
	// cipher_text_filename : just as it said
	// x0 : initial value for logistic equation
   // mju : the parameter for logistic equation
   // precision : could be 100000000, whenever we produces a new number,
   //    discard small fraction that is smaller than 1 / (_precision)
void _LSC_decrypt_jumped(string plain_text_filename, string cipher_text_filename, double x0, double mju, double precision);
	// plain_text_filename : just as it said
	// cipher_text_filename : just as it said
	// x0 : initial value for logistic equation
   // mju : the parameter for logistic equation
   // precision : could be 100000000, whenever we produces a new number,
   //    discard small fraction that is smaller than 1 / (_precision)
//---------------------------------------------------------------------------
//   outside functions
void LSCEncrypt(string plain_text_filename, string cipher_text_filename, double x0, double mju, double precision, int mode);
	// plain_text_filename : just as it said
	// cipher_text_filename : just as it said
	// x0 : initial value for logistic equation
   // mju : the parameter for logistic equation
   // precision : could be 100000000, whenever we produces a new number,
   //    discard small fraction that is smaller than 1 / (_precision)
	// mode : encoding methods = {LSC_MODE_ORIGINAL | LSC_MODE_JUMPED}
void LSCDecrypt(string plain_text_filename, string cipher_text_filename, double x0, double mju, double precision, int mode);
	// plain_text_filename : just as it said
	// cipher_text_filename : just as it said
	// x0 : initial value for logistic equation
   // mju : the parameter for logistic equation
   // precision : could be 100000000, whenever we produces a new number,
   //    discard small fraction that is smaller than 1 / (_precision)
	// mode : encoding methods = {LSC_MODE_ORIGINAL | LSC_MODE_JUMPED}
//---------------------------------------------------------------------------
#include "LSC.cpp"
#endif


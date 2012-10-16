//---------------------------------------------------------------------------
//#include "LSC.h"
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
//---------------------------------------------------------------------------
#define LSC_MODE_ORIGINAL 0
#define LSC_MODE_JUMPED 1
//---------------------------------------------------------------------------
//   inside functions
//---------------------------------------------------------------------------
double _next_number(double _previous, double _mju, double _precision)
{
	double answer = _mju * _previous * (1 - _previous);
	answer = answer * _precision;
	long long intanswer = (long long)answer;
	if(intanswer > answer)
		intanswer = intanswer - 1;
	answer = (double)intanswer / _precision;
	return answer;
}
//---------------------------------------------------------------------------
int _get_number(double x, double precision)
{
	int answer = (long long)(x * precision) % 256;
	return answer;
}
//---------------------------------------------------------------------------
void _LSC_original(string plain_text_filename, string cipher_text_filename, double x0, double mju, double precision)
{
	FILE *in = fopen(plain_text_filename.c_str(), "rb");
	FILE *out = fopen(cipher_text_filename.c_str(), "wb");

	for(int i = 0; i < 31426; i++)
		x0 = _next_number(x0, mju, precision);

	int count = 0;

	while(feof(in) == 0)
	{
		char ch;
		ch = fgetc(in);

		if(feof(in) == 0)
		{
			_next_number(x0, mju, precision);
			ch = (char)((int)ch ^ _get_number(x0, precision));

			fputc(ch, out);
			count = count + 1;
		}
	}

	fclose(out);
	fclose(in);

	return;
}
//---------------------------------------------------------------------------
void _LSC_encrypt_jumped(string plain_text_filename, string cipher_text_filename, double x0, double mju, double precision)
{
	FILE *in = fopen(plain_text_filename.c_str(), "rb");
	FILE *out = fopen(cipher_text_filename.c_str(), "wb");

	for(int i = 0; i < 31426; i++)
		x0 = _next_number(x0, mju, precision);

	int count = 0;

	while(feof(in) == 0)
	{
		char ch;
		ch = fgetc(in);

		if(feof(in) == 0)
		{
			_next_number(x0, mju, precision);
			ch = (char)((int)ch ^ _get_number(x0, precision));

			for(int i = 0; i < ch; i++)
				x0 = _next_number(x0, mju, precision);

			fputc(ch, out);
			count = count + 1;
		}
	}

	fclose(out);
	fclose(in);

	return;
}
//---------------------------------------------------------------------------
void _LSC_decrypt_jumped(string plain_text_filename, string cipher_text_filename, double x0, double mju, double precision)
{
	FILE *in = fopen(plain_text_filename.c_str(), "rb");
	FILE *out = fopen(cipher_text_filename.c_str(), "wb");

	for(int i = 0; i < 31426; i++)
		x0 = _next_number(x0, mju, precision);

	int count = 0;

	while(feof(in) == 0)
	{
		char ch;
		ch = fgetc(in);

		if(feof(in) == 0)
		{
			_next_number(x0, mju, precision);

			double xtemp = x0;

			for(int i = 0; i < ch; i++)
				x0 = _next_number(x0, mju, precision);

			ch = (char)((int)ch ^ _get_number(xtemp, precision));

			fputc(ch, out);
			count = count + 1;
		}
	}

	fclose(out);
	fclose(in);

	return;
}
//---------------------------------------------------------------------------
//   outside functions
void LSCEncrypt(string plain_text_filename, string cipher_text_filename, double x0, double mju, double precision, int mode)
{
   if(mode == LSC_MODE_ORIGINAL)
		_LSC_original(plain_text_filename, cipher_text_filename, x0, mju, precision);
   else if(mode == LSC_MODE_JUMPED)
		_LSC_encrypt_jumped(plain_text_filename, cipher_text_filename, x0, mju, precision);

	return;
}
//---------------------------------------------------------------------------
void LSCDecrypt(string plain_text_filename, string cipher_text_filename, double x0, double mju, double precision, int mode)
{
   if(mode == LSC_MODE_ORIGINAL)
		_LSC_original(plain_text_filename, cipher_text_filename, x0, mju, precision);
   else if(mode == LSC_MODE_JUMPED)
		_LSC_decrypt_jumped(plain_text_filename, cipher_text_filename, x0, mju, precision);

	return;
}
//---------------------------------------------------------------------------


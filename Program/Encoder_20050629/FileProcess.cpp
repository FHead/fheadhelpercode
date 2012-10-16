//---------------------------------------------------------------------------
//#include "FileProcess.h"
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
//---------------------------------------------------------------------------
//   outside functions
//---------------------------------------------------------------------------
void ClearFile(string filename)
{
	ofstream out;
	out.open(filename.c_str());

	out << "";

	out.close();

	return;
}
//---------------------------------------------------------------------------
void CopyFile(string filename, string destination)
{
	string command = "copy ";
	command = command + filename + " " + destination;
	system(command.c_str());

	return;
}
//---------------------------------------------------------------------------
void CopyFileIO(string filename, string destination)
{
	FILE *in = fopen(filename.c_str(), "rb");
	FILE *out = fopen(destination.c_str(), "wb");

	while(feof(in) == 0)
	{
		char ch = fgetc(in);
		if(feof(in) == 0)
			fputc(ch, out);
	}

	fclose(in);
	fclose(out);

	return;
}
//---------------------------------------------------------------------------
void BlankFile(string filename, int size)
{
	ofstream out(filename.c_str());

	string str = "";
	for(int i = 0; i < 10000; i++)
		str = str + '\0';

	if(size % 10000 == 0 && size > 0)
		out << str;
	for(int i = 10000; i < size; i = i + 10000)
		out << str;
	int temp = size % 10000;
	for(int i = 0; i < temp; i++)
		out << '\0';

	return;
}
//---------------------------------------------------------------------------


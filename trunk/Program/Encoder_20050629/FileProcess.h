//---------------------------------------------------------------------------
#ifndef FILEPROCESSYICHEN20041226_H
#define FILEPROCESSYICHEN20041226_H
//---------------------------------------------------------------------------
//
//   FileProcess.h
//   Date : 2004/12/26
//   By : Yi Chen
//   Contains definitions to basic functions on file processing
//
//---------------------------------------------------------------------------
#include <string>

using namespace std;
//---------------------------------------------------------------------------
//   outside functions
void ClearFile(string filename);
   // clears a file with the specified filename
   // filename : the file that is going to be "killed"
void CopyFile(string filename, string destination);
	// uses system("copy") to copy
	// filename : source file
	// destination : new file
void CopyFileIO(string filename, string destination);
	// uses file I/O to copy
	// filename : source file
	// destination : new file
void BlankFile(string filename, int size);
	// creates a "blank" file
	// filename : the name of new file
	// size : file size in bytes
//---------------------------------------------------------------------------
#include "FileProcess.cpp"
#endif

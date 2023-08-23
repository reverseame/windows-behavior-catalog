// Compiled with: cl /EHsc .\PathCombine.cpp
// Alter filename extension with PathCombine
// Adapted from https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathcombinea
#include <windows.h>
#include <iostream>
#include "Shlwapi.h"

void main( void ) {

	using namespace std;
// Buffer to hold combined path.
	char buffer_1[MAX_PATH] = "";
	char *lpStr1;
	lpStr1 = buffer_1;

// String for balance of path name.
	char buffer_2[ ] = "One\\Two\\Three\\Razvi.dll";
	char *lpStr2;
	lpStr2 = buffer_2;

// String for directory name.
	char buffer_3[ ] = "C:";
	char *lpStr3;
	lpStr3 = buffer_3;

	cout << "The file path to be combined is  " 
	<< lpStr2 << endl;
	cout << "The directory name path is       " 
	<< lpStr3 << endl;
	cout << "The combined path is             " 
	<< PathCombine(lpStr1,lpStr3,lpStr2) << endl;
}
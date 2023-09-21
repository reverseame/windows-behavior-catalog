// Compiled with: cl /EHsc .\PathAddExtension.cpp   Shlwapi.lib
// Alter filename extension with PathAddExtension
// Adapted from https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathaddextensiona
#include <windows.h>
#include <iostream>
#include "Shlwapi.h"

void main( void ){
     // String for path name without file name extension.
     char buffer_1[MAX_PATH] = "file";
     char *lpStr1;
     lpStr1 = buffer_1;

     // String for extension name.
     char F_Ext[MAX_PATH] = ".dll";
     char *lpStr3;
     lpStr3 = F_Ext;

     // Path 1 without the file name extension.
     //std::cout << "The original path string 1 is  " << lpStr1 << std::endl;

     if(!PathAddExtension(lpStr1,lpStr3)){ // FALSE in case of errors
          std::cerr << "PathAddExtension error: " << GetLastError() << std::endl;
     }
     //std::cout << "The modified path string 1 is  " << lpStr1 << std::endl;
     
}
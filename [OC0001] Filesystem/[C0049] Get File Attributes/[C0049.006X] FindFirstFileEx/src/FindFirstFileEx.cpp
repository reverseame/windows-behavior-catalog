// Compiled with: cl /EHsc .\FindFirstFileEx.cpp
// Get file attributes with FindFirstFileEx
// Adapted from https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfileexa
#include <windows.h>
#include <iostream>

void main(){
   const char* filePath = "C:\\Windows\\regedit.exe";
   WIN32_FIND_DATA FindFileData;
   HANDLE hFind;

   hFind = FindFirstFileEx(filePath, FindExInfoStandard, &FindFileData,
             FindExSearchNameMatch, NULL, 0);
   if (hFind == INVALID_HANDLE_VALUE) {
       std::cerr << "FindFirstFileEx failed " << GetLastError() << std::endl;
      return;
   } else {
       std::cout << "The first file found is :" << FindFileData.cFileName << std::endl;
      if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            std::cout << "File is a directory" << std::endl;
      } else {
            std::cout << "File is not a directory" << std::endl;
      }
      FindClose(hFind);
   }
}
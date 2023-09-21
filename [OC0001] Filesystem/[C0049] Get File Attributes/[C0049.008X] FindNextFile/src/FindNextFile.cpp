// Compiled with: cl /EHsc .\FindNextFile.cpp
// Get file attributes with FindNextFile
#include <Windows.h>
#include <iostream>
#include <string>

int main() {
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFile("C:\\Windows\\*.exe", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "FindFirstFileA failed, error: " << GetLastError() << std::endl;
        return 1;
    }
  
    /*if (FindNextFile(hFind, &findFileData) != 0){
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            std::cout << "File: " << findFileData.cFileName << std::endl;
        } else {
            std::cout << "Directory: " << findFileData.cFileName << std::endl;
        }
    } else {
        std::cerr << "FindNextFileA failed, error: " << GetLastError() << std::endl;
        FindClose(hFind);
        return 1;
    }*/

    while (FindNextFile(hFind, &findFileData)){
       printf("File: %s\n", findFileData.cFileName);
    }

    FindClose(hFind);

    return 0;
}

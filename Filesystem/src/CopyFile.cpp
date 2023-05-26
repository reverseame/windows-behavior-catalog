// Compiled with: cl /EHsc .\CopyFile.cpp
// Copy file with CopyFile
#include <Windows.h>
#include <iostream>

int main() {
    LPCSTR sourceFile = "C:\\Windows\\explorer.exe";
    LPCSTR destinationFile = ".\\copiedexample.exe";

    if (CopyFile(sourceFile, destinationFile, FALSE)) {
        std::cout << "File copied successfully." << std::endl;
    } else {
        std::cout << "Failed to copy file. Error code: " << GetLastError() << std::endl;
    }

    return 0;
}
// Compiled with: cl /EHsc .\CopyFile2.cpp
// Copy file with CopyFile2
#include <Windows.h>
#include <iostream>

int main() {
    PCWSTR sourceFile = L"C:\\Windows\\explorer.exe";
    PCWSTR destinationFile = L".\\copiedexample.exe";

    if (!SUCCEEDED(CopyFile2(sourceFile, destinationFile, NULL))) {
        std::cout << "Failed to copy file. Error code: " << GetLastError() << std::endl;
    }

    return 0;
}
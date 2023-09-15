// Compiled with: cl /EHsc .\CreateDirectoryEx.cpp
// Create directory with CreateDirectoryEx
#include <iostream>
#include <Windows.h>

int main() {
    if (!CreateDirectoryEx(".\\", "ExampleDirectory", NULL)) {
        std::cerr << "Failed to create directory. Error code: " << GetLastError() << std::endl;
    }

    return 0;
}

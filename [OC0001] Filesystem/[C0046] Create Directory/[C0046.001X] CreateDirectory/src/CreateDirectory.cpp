// Compiled with: cl /EHsc .\CreateDirectory.cpp
// Create directory with CreateDirectory
#include <iostream>
#include <Windows.h>

int main() {
    if (!CreateDirectory(".\\ExampleDirectory", nullptr)) {
        std::cerr << "Failed to create directory. Error code: " << GetLastError() << std::endl;
    }

    return 0;
}


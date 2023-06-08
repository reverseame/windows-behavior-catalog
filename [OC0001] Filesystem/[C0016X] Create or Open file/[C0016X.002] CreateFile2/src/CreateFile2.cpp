// Compiled with: cl /EHsc .\CreateFile2.cpp
// Create file with CreateFile2
#include <Windows.h>
#include <iostream>

int main() {
    HANDLE hFile = CreateFile2(L"example.txt", GENERIC_WRITE, 0, OPEN_ALWAYS, nullptr);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to create file. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "File created successfully." << std::endl;

    CloseHandle(hFile);
    return 0;
}


// Compiled with: cl /EHsc .\GetFileAttributesEx.cpp
// Get file attributes with GetFileAttributesEx
#include <iostream>
#include <Windows.h>

int main() {
    const char* filePath = "C:\\Windows\\regedit.exe";
    WIN32_FILE_ATTRIBUTE_DATA fileInfo;

    if (GetFileAttributesExA(filePath, GetFileExInfoStandard, &fileInfo)) {
        if (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            std::cout << "File is a directory" << std::endl;
        } else {
            std::cout << "File is not a directory" << std::endl;
        }
    } else {
        DWORD error = GetLastError();
        std::cerr << "Failed to get file attributes. Error code: " << error << std::endl;
    }

    return 0;
}

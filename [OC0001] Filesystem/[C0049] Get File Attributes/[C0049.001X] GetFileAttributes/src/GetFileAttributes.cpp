// Compiled with: cl /EHsc .\GetFileAttributes.cpp
// Get file attributes with GetFileAttributes
#include <iostream>
#include <Windows.h>

int main() {
    const char* filePath = "C:\\Windows\\regedit.exe";

    DWORD fileAttributes = GetFileAttributes(filePath);

    /*
    if (fileAttributes != INVALID_FILE_ATTRIBUTES) {
        if (fileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            std::cout << "File is a directory" << std::endl;
        } else {
            std::cout << "File is not a directory" << std::endl;
        }
    } else {
        std::cerr << "Failed to get file attributes. Error code: " << GetLastError() << std::endl;
    }*/

    if (fileAttributes == INVALID_FILE_ATTRIBUTES) {
        std::cerr << "Failed to get file attributes. Error code: " << GetLastError() << std::endl;
    } 

    return 0;
}

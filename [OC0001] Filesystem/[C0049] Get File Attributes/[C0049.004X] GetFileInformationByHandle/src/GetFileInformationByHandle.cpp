// Compiled with: cl /EHsc .\GetFileInformationByHandle.cpp
// Get file attributes with GetFileInformationByHandle
#include <iostream>
#include <Windows.h>

int main() {
    const char* filePath = "C:\\Windows\\regedit.exe";
    HANDLE hFile = CreateFileA(filePath, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open file. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    BY_HANDLE_FILE_INFORMATION fileInfo;
    if (GetFileInformationByHandle(hFile, &fileInfo)) {
        std::cout << "File Size: " << fileInfo.nFileSizeLow << std::endl;
        if (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            std::cout << "File is a directory" << std::endl;
        } else {
            std::cout << "File is not a directory" << std::endl;
        }
        // You can extract other file information from the fileInfo structure
    } else {
        std::cerr << "Failed to get file information. Error code: " << GetLastError() << std::endl;
    }

    CloseHandle(hFile);
    return 0;
}

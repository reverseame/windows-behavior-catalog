// Compiled with: cl /EHsc .\FindFirstFile.cpp
// Get file attributes with FindFirstFile
#include <iostream>
#include <Windows.h>

int main() {
    const char* filePath = "C:\\Windows\\regedit.exe";
    WIN32_FIND_DATA findData;

    HANDLE hFind = FindFirstFile(filePath, &findData);
    if (hFind != INVALID_HANDLE_VALUE) {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            std::wcout << L"File is a directory" << std::endl;
        } else {
            std::wcout << L"File is not a directory" << std::endl;
        }

        FindClose(hFind);
    } else {
        std::wcerr << L"Failed to find file. Error code: " << GetLastError() << std::endl;
    }

    return 0;
}

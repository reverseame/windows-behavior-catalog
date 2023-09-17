// Compiled with: cl /EHsc .\FindFirstFileTransacted.cpp KtmW32.lib
// Get file attributes with FindFirstFileTransacted
#include <iostream>
#include <Windows.h>
#include <ktmw32.h>

int main() {
    const char* filePath = "C:\\Windows\\regedit.exe";
    HANDLE hTransaction = CreateTransaction(nullptr, nullptr, 0, 0, 0, 0, nullptr);
    if (hTransaction == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create transaction. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileTransacted(filePath, FindExInfoStandard, &findFileData, FindExSearchNameMatch, NULL, 0, hTransaction);
    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to find the first file. Error code: " << GetLastError() << std::endl;
        CloseHandle(hTransaction);
        return 1;
    }

    /*do {
        std::cout << "File Name: " << findFileData.cFileName << std::endl;
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            std::cout << "File is a directory" << std::endl;
        } else {
            std::cout << "File is not a directory" << std::endl;
        }
    } while (FindNextFileA(hFind, &findFileData));*/

    FindClose(hFind);
    CloseHandle(hTransaction);

    return 0;
}

// Compiled with: cl /EHsc .\GetFileAttributesTransacted.cpp KtmW32.lib
// Get file attributes with GetFileAttributesTransacted
#include <iostream>
#include <Windows.h>
#include <ktmw32.h>

int main() {
    const char* filePath = "C:\\Windows\\regedit.exe";
    WIN32_FILE_ATTRIBUTE_DATA fileInfo;
    HANDLE hTransaction = CreateTransaction(nullptr, nullptr, 0, 0, 0, 0, nullptr);

    if (hTransaction == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create transaction. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    if (GetFileAttributesTransacted(filePath, GetFileExInfoStandard, &fileInfo, hTransaction)) {
        if (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            std::cout << "File is a directory" << std::endl;
        } else {
            std::cout << "File is not a directory" << std::endl;
        }
    } else {
        DWORD error = GetLastError();
        std::cerr << "Failed to get file attributes transacted. Error code: " << error << std::endl;
    }

    if (!CommitTransaction(hTransaction)) {
        std::cerr << "Failed to commit transaction. Error code: " << GetLastError() << std::endl;
    }

    return 0;
}

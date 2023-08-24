// Compiled with: cl /EHsc .\CreateFileTransacted.cpp KtmW32.lib
// Create directory with CreateFileTransacted
#include <iostream>
#include <Windows.h>
#include <ktmw32.h>

int main() {
    //LPCSTR sourceDirectory = "C:";
    LPCSTR targetDirectory = "C:\\TargetDirectory";
    HANDLE transactionHandle = CreateTransaction(nullptr, 0, 0, 0, 0, INFINITE, nullptr);
    
    if (transactionHandle == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create transaction. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    if (CreateDirectoryTransacted(NULL, targetDirectory, NULL, transactionHandle)) {
        std::cout << "Directory created successfully." << std::endl;
    } else {
        std::cerr << "Failed to create directory. Error code: " << GetLastError() << std::endl;
    }

    CloseHandle(transactionHandle);
    return 0;
}

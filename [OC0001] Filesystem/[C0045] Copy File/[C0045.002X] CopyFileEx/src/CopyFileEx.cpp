// Compiled with: cl /EHsc .\CopyFileEx.cpp
// Copy file with CopyFileEx
#include <Windows.h>
#include <iostream>

// Callback function for copy progress
DWORD CALLBACK CopyProgressCallback(LARGE_INTEGER TotalFileSize, LARGE_INTEGER TotalBytesTransferred,
                                    LARGE_INTEGER StreamSize, LARGE_INTEGER StreamBytesTransferred,
                                    DWORD dwStreamNumber, DWORD dwCallbackReason, HANDLE hSourceFile,
                                    HANDLE hDestinationFile, LPVOID lpData) {
    // Calculate the percentage of the copy progress
    double progress = (double(TotalBytesTransferred.QuadPart) / double(TotalFileSize.QuadPart)) * 100.0;

    // Output the progress
    std::cout << "Copy progress: " << progress << "%" << std::endl;

    // Continue the copy operation
    return PROGRESS_CONTINUE;
}

int main() {
   LPCSTR sourceFile = "C:\\Windows\\explorer.exe";
   LPCSTR destinationFile = ".\\copiedexample.exe";

    if (!CopyFileEx(sourceFile, destinationFile, CopyProgressCallback, nullptr, nullptr,
                   COPY_FILE_COPY_SYMLINK | COPY_FILE_FAIL_IF_EXISTS | COPY_FILE_RESTARTABLE)) {
        std::cout << "File copy failed. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    return 0;
}
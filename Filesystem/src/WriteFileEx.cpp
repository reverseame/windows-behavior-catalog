// Compiled with: cl /EHsc .\WriteFileEx.cpp
// Wirte to file with WriteFileEx
#include <Windows.h>
#include <iostream>

void CALLBACK WriteCompletionRoutine(DWORD dwErrorCode, DWORD dwBytesTransferred, LPOVERLAPPED lpOverlapped) {
    if (dwErrorCode == ERROR_SUCCESS) {
        std::cout << "Write operation completed. Bytes written: " << dwBytesTransferred << std::endl;
    } else {
        std::cout << "Write operation failed. Error code: " << dwErrorCode << std::endl;
    }
}

int main() {
    HANDLE hFile = CreateFile("example.txt", GENERIC_WRITE, 0, nullptr, OPEN_ALWAYS, FILE_FLAG_OVERLAPPED, nullptr);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to open/create file. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    const char* text = "Hello, world! Example of filesystem operations";
    OVERLAPPED overlapped = { 0 };
    overlapped.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);

    if (overlapped.hEvent == nullptr) {
        std::cout << "Failed to create event. Error code: " << GetLastError() << std::endl;
        CloseHandle(hFile);
        return 1;
    }

    if (!WriteFileEx(hFile, text, strlen(text), &overlapped, WriteCompletionRoutine)) {
        std::cout << "Failed to start write operation. Error code: " << GetLastError() << std::endl;
        CloseHandle(overlapped.hEvent);
        CloseHandle(hFile);
        return 1;
    }

    std::cout << "Write operation started." << std::endl;

    /*
    // Wait for the write operation to complete
    if (WaitForSingleObject(overlapped.hEvent, INFINITE) != WAIT_OBJECT_0) {
        std::cout << "Failed to wait for write operation to complete. Error code: " << GetLastError() << std::endl;
    }*/

    CloseHandle(overlapped.hEvent);
    CloseHandle(hFile);
    return 0;
}

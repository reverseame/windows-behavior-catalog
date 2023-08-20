// Compiled with: cl /EHsc .\SuspendThread.cpp
// Suspend thread with SuspendThread
#include <Windows.h>
#include <iostream>

int main() {
    HANDLE hThread = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(GetTickCount), NULL, 0, NULL);

    if (hThread == NULL) {
        std::cerr << "Failed to create thread." << std::endl;
        return 1;
    }

    // Suspend the thread
    DWORD suspendCount = SuspendThread(hThread);
    if (suspendCount == (DWORD)-1) {
        std::cerr << "SuspendThread failed." << std::endl;
        CloseHandle(hThread);
        return 1;
    }

    std::cout << "Thread suspended. Suspend count: " << suspendCount << std::endl;

    CloseHandle(hThread);
    return 0;
}

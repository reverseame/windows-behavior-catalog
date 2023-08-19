// Compiled with: cl /EHsc .\ResumeThread.cpp
// Resume thread with REsumeThread
#include <Windows.h>
#include <iostream>

int main() {
    HANDLE hThread = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(GetTickCount), NULL, 0, NULL);

    if (hThread == NULL) {
        std::cerr << "Failed to create thread." << std::endl;
        return 1;
    }

    // Resume the thread (it has no effect given that the thread is not previously suspended)
    DWORD resumeCount = ResumeThread(hThread);
    if (resumeCount == (DWORD)-1) {
        std::cerr << "ResumeThread failed." << std::endl;
        CloseHandle(hThread);
        return 1;
    }

    std::cout << "Thread resumed. Suspend count: " << resumeCount << std::endl;

    CloseHandle(hThread);
    return 0;
}
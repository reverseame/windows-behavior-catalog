// Compiled with: cl /EHsc .\enumerate_threads.cpp
// Thread Enumeration
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

int main() {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        DWORD error = GetLastError();
        std::cerr << "CreateToolhelp32Snapshot failed with error " << error << std::endl;
        return 1;
    }

    THREADENTRY32 threadEntry;
    threadEntry.dwSize = sizeof(THREADENTRY32);

    if (Thread32First(snapshot, &threadEntry)) {
        do {
            std::cout << "Thread ID: " << threadEntry.th32ThreadID << " in process ID: " << threadEntry.th32OwnerProcessID << std::endl;
        } while (Thread32Next(snapshot, &threadEntry));
    } else {
        DWORD error = GetLastError();
        std::cerr << "Thread32First failed with error " << error << std::endl;
    }

    CloseHandle(snapshot);

    return 0;
}

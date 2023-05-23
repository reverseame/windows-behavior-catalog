// Compiled with: cl /EHsc .\create_thread_v1.cpp
// Create thread using CreateThread 
#include <iostream>
#include <windows.h>

// Thread function that will be executed by the new thread
DWORD WINAPI ThreadFunction(LPVOID lpParam) {
    std::cout << "Thread running..." << std::endl;
    return 0;
}

int main() {
    // Create a handle for the new thread
    HANDLE hThread;

    // Create the thread
    hThread = CreateThread(NULL, 0, ThreadFunction, NULL, 0, NULL);
    if (hThread == NULL) {
        std::cerr << "Failed to create thread!" << std::endl;
        return 1;
    }

    // Wait for the thread to finish
    WaitForSingleObject(hThread, INFINITE);

    // Close the thread handle
    CloseHandle(hThread);

    return 0;
}
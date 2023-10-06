// Compiled with: cl /EHsc .\GetProcessHeap_HeapAlloc.cpp
// Memory Allocation with HeapAlloc and GetProcessHeap
#include <Windows.h>
#include <iostream>

int main() {
    HANDLE hHeap = GetProcessHeap();  // Get handle to the process's default heap

    if (hHeap == NULL) {
        std::cerr << "GetProcessHeap failed." << std::endl;
        return 1;
    }

    DWORD dwSize = 4919;  // Size of memory to allocate (in bytes)
    LPVOID lpMemory = HeapAlloc(hHeap, 0, dwSize);

    if (lpMemory == NULL) {
        std::cerr << "HeapAlloc failed." << std::endl;
        return 1;
    } else {
        std::cout << "HeapAlloc successful." << std::endl;
    }

    // Use the allocated memory here...

    // Free the allocated memory when done
    if (!HeapFree(hHeap, 0, lpMemory)) {
        std::cerr << "HeapFree failed." << std::endl;
        return 1;
    }

    return 0;
}

// Compiled with: cl /EHsc .\LocalAlloc.cpp
// Memory Allocation with LocalAlloc
#include <Windows.h>
#include <Windows.h>
#include <iostream>

int main() {
    UINT uFlags = LMEM_FIXED;  // Allocate memory with fixed allocation
    DWORD dwSize = 4096;       // Size of memory to allocate (in bytes)
    HLOCAL hLocal = LocalAlloc(uFlags, dwSize);

    if (hLocal == NULL) {
        std::cerr << "LocalAlloc failed." << std::endl;
        return 1;
    }

    // LPVOID lpMemory = LocalLock(hLocal);  // Lock the allocated memory

    // if (lpMemory == NULL) {
    //     std::cerr << "LocalLock failed." << std::endl;
    //     LocalFree(hLocal);  // Free the allocated memory
    //     return 1;
    // }

    // // Use the allocated memory here...

    // LocalUnlock(hLocal);   // Unlock the memory

    // if (!LocalFree(hLocal)) {  // Free the allocated memory
    //     std::cerr << "LocalFree failed." << std::endl;
    //     return 1;
    // }

    return 0;
}

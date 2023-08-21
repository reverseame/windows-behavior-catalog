// Compiled with: cl /EHsc .\GlobalAlloc.cpp
// Memory Allocation with GlobalAlloc
#include <Windows.h>
#include <iostream>

#include <Windows.h>
#include <iostream>

int main() {
    UINT uFlags = GMEM_FIXED;  // Allocate memory with fixed allocation
    DWORD dwSize = 4096;       // Size of memory to allocate (in bytes)
    HGLOBAL hGlobal = GlobalAlloc(uFlags, dwSize);

    if (hGlobal == NULL) {
        std::cerr << "GlobalAlloc failed." << std::endl;
        return 1;
    }

    // LPVOID lpMemory = GlobalLock(hGlobal);  // Lock the allocated memory

    // if (lpMemory == NULL) {
    //     std::cerr << "GlobalLock failed." << std::endl;
    //     GlobalFree(hGlobal);  // Free the allocated memory
    //     return 1;
    // }

    // // Use the allocated memory here...

    // GlobalUnlock(hGlobal);   // Unlock the memory

    // if (!GlobalFree(hGlobal)) {  // Free the allocated memory
    //     std::cerr << "GlobalFree failed." << std::endl;
    //     return 1;
    // }

    // return 0;
}

// Compiled with: cl /EHsc .\GlobalAlloc.cpp
// Memory Allocation with GlobalAlloc
#include <windows.h>
#include <iostream>

int main() {
    // Allocate 1024 bytes of memory globally
    HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, 4919);
    if (hGlobal == NULL) {
        std::cerr << "Error in GlobalAlloc: " << GetLastError() << std::endl; // Error handling
        return 1;
    }

    // Lock the memory and get a pointer to it
    LPVOID pData = GlobalLock(hGlobal);
    if (pData == NULL) {
        std::cerr << "Error in GlobalLock: " << GetLastError() << std::endl; // Error handling
        GlobalFree(hGlobal);
        return 1;
    }

    // Write data to the allocated memory
    strcpy_s((char*)pData, 1024, "Hello, GlobalAlloc!");

    // Unlock the memory
    GlobalUnlock(hGlobal);

    // Use the allocated memory...

    // Free the allocated memory
    GlobalFree(hGlobal);

    return 0;
}


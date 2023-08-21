// Compiled with: cl /EHsc .\VirtualAlloc.cpp
// Memory Allocation with VirtualAlloc
#include <Windows.h>
#include <iostream>

int main() {
    DWORD dwSize = 4096;  // Size of memory to allocate (in bytes)
    LPVOID lpMemory = VirtualAlloc(NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);

    if (lpMemory == NULL) {
        std::cerr << "VirtualAlloc failed." << std::endl;
        return 1;
    }

    // Use the allocated memory here...

    // Free the allocated memory when done
    // if (!VirtualFree(lpMemory, 0, MEM_RELEASE)) {
    //     std::cerr << "VirtualFree failed." << std::endl;
    //     return 1;
    // }

    return 0;
}

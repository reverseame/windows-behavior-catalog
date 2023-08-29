// Compiled with: cl /EHsc .\HeapCreate_HeapAlloc.cpp
// Memory Allocation with HeapAlloc and HeapCreate
#include <Windows.h>
#include <iostream>

#include <Windows.h>
#include <iostream>

int main() {
    HANDLE hCustomHeap = HeapCreate(0, 0, 0);  // Create a custom heap

    if (hCustomHeap == NULL) {
        std::cerr << "HeapCreate failed." << std::endl;
        return 1;
    } else {
        std::cout << "HeapCreate successful." << std::endl;
    }

    DWORD dwSize = 4919;  // Size of memory to allocate (in bytes)
    LPVOID lpMemory = HeapAlloc(hCustomHeap, 0, dwSize);

    if (lpMemory == NULL) {
        std::cerr << "HeapAlloc failed." << std::endl;
        HeapDestroy(hCustomHeap);  // Clean up the custom heap
        return 1;
    } else {
        std::cout << "HeapAlloc successful." << std::endl;
    }

    // Use the allocated memory here...

    // // Free the allocated memory when done
    if (!HeapFree(hCustomHeap, 0, lpMemory)) {
        std::cerr << "HeapFree failed." << std::endl;
    }

    // // Clean up the custom heap
    if (!HeapDestroy(hCustomHeap)) {
        std::cerr << "HeapDestroy failed." << std::endl;
        return 1;
    }

    return 0;
}


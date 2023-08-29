// Compiled with: cl /EHsc .\malloc.cpp
// Memory Allocation with malloc
#include <Windows.h>
#include <iostream>

int main() {
    size_t size = 4919;  // Size of memory to allocate (in bytes)
    LPVOID lpMemory = malloc(size);  // Allocate memory using malloc

    if (lpMemory == NULL) {
        std::cerr << "malloc failed." << std::endl;
        return 1;
    }

    // Use the allocated memory here...

    free(lpMemory);  // Free the allocated memory

    return 0;
}

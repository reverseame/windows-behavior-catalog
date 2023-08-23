// Compiled with: cl /EHsc .\VirtualProtect.cpp
// Memory protection modification with VirtualProtect
#include <Windows.h>
#include <iostream>

int main() {
    LPVOID lpMemory = VirtualAlloc(NULL, 4096, MEM_COMMIT, PAGE_READWRITE);  // Allocate memory with read-write protection

    if (lpMemory == NULL) {
        std::cerr << "VirtualAlloc failed." << std::endl;
        return 1;
    }

    // Change the memory protection to PAGE_EXECUTE_READ
    DWORD oldProtect;
    if (!VirtualProtect(lpMemory, 4096, PAGE_EXECUTE_READ, &oldProtect)) {
        std::cerr << "VirtualProtect failed." << std::endl;
        VirtualFree(lpMemory, 0, MEM_RELEASE);  // Free the allocated memory
        return 1;
    }

    // Use the memory with new protection...

    // Restore the original protection
    // DWORD restoredProtect;
    // if (!VirtualProtect(lpMemory, 4096, oldProtect, &restoredProtect)) {
    //     std::cerr << "VirtualProtect failed." << std::endl;
    // }

    // VirtualFree(lpMemory, 0, MEM_RELEASE);  // Free the allocated memory

    return 0;
}

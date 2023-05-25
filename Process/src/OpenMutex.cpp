// Compiled with: cl /EHsc .\OpenMutex.cpp
// Check mutex using OpenMutex
#include <Windows.h>
#include <iostream>

int main() {
    // Check if the global mutex exists
    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "Global\\MyGlobalMutexExample");

    if (hMutex == NULL) {
        std::cout << "Global mutex does not exist." << std::endl;
        return 1;
    }

    std::cout << "Global mutex exists." << std::endl;

    // Close the handle
    CloseHandle(hMutex);

    return 0;
}
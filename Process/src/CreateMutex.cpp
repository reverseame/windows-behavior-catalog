// Compiled with: cl /EHsc .\CreateMutex.cpp
// Create mutex using CreateMutex
#include <Windows.h>
#include <iostream>

int main() {
    // Create a global mutex
    HANDLE hMutex = CreateMutex(NULL, FALSE, "Global\\MyGlobalMutexExample");

    if (hMutex == NULL) {
        std::cout << "Failed to create mutex. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        std::cout << "Mutex already exists." << std::endl;
        return 1;
    }

    std::cout << "Mutex created successfully." << std::endl;

    // Use the mutex...

    // Release the mutex
    CloseHandle(hMutex);

    return 0;
}
// Compiled with: cl /EHsc .\create_mutex_v2.cpp
// Create mutex using CreateMutexEx 
#include <Windows.h>
#include <iostream>

int main() {
    // Create a global mutex
    HANDLE hMutex = CreateMutexEx(NULL, "Global\\MyGlobalMutexExample", 0, MUTEX_ALL_ACCESS);

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

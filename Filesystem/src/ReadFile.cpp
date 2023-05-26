// Compiled with: cl /EHsc .\ReadFile.cpp
// read file with ReadFile

#include <iostream>
#include <windows.h>

int main() {
    // Create a new file named "example.txt"
    HANDLE fileHandle = CreateFile("example.txt", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to create file." << std::endl;
        return 1;
    }
    
    // Read the text from the file
    char buffer[1024];
    DWORD bytesRead;
    int success = ReadFile(fileHandle, buffer, sizeof(buffer), &bytesRead, NULL);
    if (!success) {
        std::cout << "Failed to read from file." << std::endl;
        CloseHandle(fileHandle);
        return 1;
    }
    buffer[bytesRead] = '\0'; // Null-terminate the string
    
    std::cout << "File contents: " << buffer << std::endl;
    
    // Close the file handle
    CloseHandle(fileHandle);
    
    return 0;
}

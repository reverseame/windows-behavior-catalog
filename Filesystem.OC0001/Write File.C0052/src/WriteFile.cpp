// Compiled with: cl /EHsc .\WriteFile.cpp
// Wirte to file with WriteFile

#include <iostream>
#include <windows.h>

int main() {
    // Create a new file named "example.txt"
    HANDLE fileHandle = CreateFile("example.txt", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to create file." << std::endl;
        return 1;
    }
    
    // Write some text to the file
    const char* text = "Hello, world! Example of filesystem operations";
    DWORD bytesWritten;
    BOOL success = WriteFile(fileHandle, text, strlen(text), &bytesWritten, NULL);
    if (!success) {
        std::cout << "Failed to write to file." << std::endl;
        CloseHandle(fileHandle);
        return 1;
    }
    
    // Close the file handle
    CloseHandle(fileHandle);
    
    return 0;
}

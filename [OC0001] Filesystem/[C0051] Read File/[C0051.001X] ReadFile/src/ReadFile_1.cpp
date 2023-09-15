// Compiled with: cl /EHsc .\ReadFile_1.cpp
// Read file with ReadFile and opening it with CreateFile

#include <iostream>
#include <windows.h>

int main() {
    // Open kernel32
    HANDLE fileHandle = CreateFile("C:\\Windows\\System32\\kernel32.dll", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to open file." << std::endl;
        return 1;
    }

    // Read the text from the file
    char buffer[4096];
    DWORD bytesRead;
    int success = ReadFile(fileHandle, buffer, sizeof(buffer), &bytesRead, NULL);
    if (!success) {
        std::cout << "Failed to read from file." << std::endl;
        CloseHandle(fileHandle);
        return 1;
    }

    //std::cout << "Read " << bytesRead << " bytes from the file." << std::endl;
    //std::cout << "File contents: " << buffer << std::endl;

    // Close the file handle
    CloseHandle(fileHandle);
    
    return 0;
}

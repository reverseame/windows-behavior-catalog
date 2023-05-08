#include <iostream>
#include <windows.h>

int main() {
    // Create a new file named "example.txt"
    HANDLE fileHandle = CreateFile("example.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to create file." << std::endl;
        return 1;
    }
    
    // Write some text to the file
    const char* text = "Hello, world!";
    DWORD bytesWritten;
    BOOL success = WriteFile(fileHandle, text, strlen(text), &bytesWritten, NULL);
    if (!success) {
        std::cout << "Failed to write to file." << std::endl;
        CloseHandle(fileHandle);
        return 1;
    }
    
    // Move the file pointer to the beginning of the file
    SetFilePointer(fileHandle, 0, NULL, FILE_BEGIN);
    
    // Read the text from the file
    char buffer[1024];
    DWORD bytesRead;
    success = ReadFile(fileHandle, buffer, sizeof(buffer), &bytesRead, NULL);
    if (!success) {
        std::cout << "Failed to read from file." << std::endl;
        CloseHandle(fileHandle);
        return 1;
    }
    buffer[bytesRead] = '\0'; // Null-terminate the string
    
    std::cout << "File contents: " << buffer << std::endl;
    
    // Close the file handle
    CloseHandle(fileHandle);
    
    // Delete the file
    success = DeleteFile("example.txt");
    if (!success) {
        std::cout << "Failed to delete file." << std::endl;
        return 1;
    }
    
    return 0;
}

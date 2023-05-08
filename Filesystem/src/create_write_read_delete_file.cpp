// Compiled with: cl /EHsc .\create_write_read_delete_file.cpp

#include <iostream>
#include <windows.h>

std::string GetLastErrorAsString()
{
    //Get the error message ID, if any.
    DWORD errorMessageID = ::GetLastError();
    if(errorMessageID == 0) {
        return std::string(); //No error message has been recorded
    }
    
    LPSTR messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    
    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);
    
    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);
            
    return message;
}

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
    
    // Move the file pointer to the beginning of the file
    SetFilePointer(fileHandle, 0, NULL, FILE_BEGIN);
    
    // Read the text from the file
    char buffer[1024];
    DWORD bytesRead;
    success = ReadFile(fileHandle, buffer, sizeof(buffer), &bytesRead, NULL);
    if (!success) {
        std::cout << "Failed to read from file." << std::endl;
        std::cout << GetLastErrorAsString() << std::endl;
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

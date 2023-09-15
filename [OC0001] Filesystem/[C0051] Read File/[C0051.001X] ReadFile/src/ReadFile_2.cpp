// Compiled with: cl /EHsc .\ReadFile_2.cpp
// Read file with ReadFile and opening it with OpenFile

#include <iostream>
#include <windows.h>

int main() {
    OFSTRUCT _buffer = {0};
    // Open kernel32
    HFILE hFile = OpenFile("C:\\Windows\\System32\\kernel32.dll", &_buffer, OF_READ);
    if (hFile != HFILE_ERROR) {

        // Conversion from HFILE to HANDLE
        HANDLE fileHandle = reinterpret_cast<HANDLE>(hFile);

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
        
    } else {
        std::cout << "Failed to open file." << std::endl;
        return 1;
    }

    
}

// Compiled with: cl /EHsc .\ExpandEnvironmentStrings.cpp
// Set environment variable using ExpandEnvironmentStrings   
#include <Windows.h>
#include <iostream>

int main(){
    // Input string containing environment variable
    const char* inputString = "User profile folder: %USERPROFILE%";

    // Buffer to store the expanded string
    char expandedBuffer[4096];  // Adjust the buffer size as needed

    // Expand environment variables in the input string
    DWORD expandedSize = ExpandEnvironmentStrings(inputString, expandedBuffer, sizeof(expandedBuffer) / sizeof(char));
    if (expandedSize > 0 && expandedSize < sizeof(expandedBuffer) / sizeof(char)) {
        std::cout << "Expanded string: " << expandedBuffer << std::endl;
    }
    else if (expandedSize == 0) {
        std::cerr << "Failed to expand environment variables." << std::endl;
    }
    else {
        std::cerr << "Buffer size is insufficient." << std::endl;
    }

    return 0;
}

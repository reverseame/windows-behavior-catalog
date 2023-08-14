// Compiled with: cl /EHsc .\GetEnvironmentVariable.cpp
// Check environment variable using GetEnvironmentVariable
#include <Windows.h>
#include <iostream>

int main() {
    // Name of the environment variable to retrieve
    const char* variableName = "Path";

    // Buffer to store the environment variable value
    char buffer[4096];  // Adjust the buffer size as needed

    // Get the value of the environment variable
    DWORD bufferSize = GetEnvironmentVariable(variableName, buffer, sizeof(buffer) / sizeof(char));
    if (bufferSize > 0 && bufferSize < sizeof(buffer) / sizeof(char)) {
        std::cout << "Value of " << variableName << ": " << buffer << std::endl;
    }
    else if (bufferSize == 0) {
        std::cerr << "The environment variable doesn't exist." << std::endl;
    }
    else {
        std::cerr << "Failed to retrieve environment variable." << std::endl;
    }

    return 0;
}


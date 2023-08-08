// Compiled with: cl /EHsc .\SetEnvironmentVariable.cpp
// Set environment variable using SetenvironmentVariable   
#include <iostream>
#include <Windows.h>
#include <iostream>

int main(){
    
    // Set a new environment variable
    if (SetEnvironmentVariable("MyVariable", "MyValue")){
        std::cout << "Environment variable set successfully." << std::endl;
    } else {
        std::cerr << "Failed to set environment variable." << std::endl;
    }

    return 0;
}

// Compiled with: cl /EHsc .\GetEnvironmentStrings.cpp
// Check environment variable using GetEnvironmentStrings
// Adapted from https://www.installsetupconfig.com/win32programming/windowsthreadsprocessapis7_22.html
#include <Windows.h>
#include <iostream>


int main() {

    LPTSTR lpszVariable;
    LPCH lpvEnv;

    // Get a pointer to the environment block.
    lpvEnv = GetEnvironmentStrings();

    // If the returned pointer is NULL, exit.
    if (lpvEnv == NULL)
        std::cerr << "GetEnvironmentStrings() failed." << std::endl;
    else
        std::cout << "GetEnvironmentStrings() is OK.\n\n" << std::endl;

    // Variable strings are separated by NULL byte, and the block is terminated by a NULL byte.
    lpszVariable = (LPTSTR) lpvEnv;
    while(*lpszVariable) {
        std::cout << lpszVariable << std::endl;
        lpszVariable += lstrlen(lpszVariable) + 1;
    }

    if(FreeEnvironmentStrings(lpvEnv) == 0)
        std::cerr << "GetEnvironmentStrings() failed.\n" << std::endl;
    else
        std::cout << "\nGetEnvironmentStrings() is OK.\n" << std::endl;
    return 0;

}

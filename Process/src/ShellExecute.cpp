// Compiled with: cl /EHsc .\ShellExecute.cpp Shell32.lib
// Open process using ShellExecute
#include <windows.h>
#include <iostream>

int main()
{
    LPCSTR lpOperation = "open";
    LPCSTR lpFile = "C:\\Windows\\System32\\calc.exe";
    LPCSTR lpParameters = NULL;
    LPCSTR lpDirectory = NULL;
    INT nShowCmd = SW_SHOWNORMAL;

    HINSTANCE hInstance = ShellExecute(NULL, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd);
    if ((int)hInstance <= 32)
    {
        DWORD errorCode = (DWORD)hInstance;
        std::cerr << "Failed to open the process. Error code: " << errorCode << std::endl;
        return 1;
    }

    std::cout << "Process opened successfully!" << std::endl;

    return 0;
}
// Compiled with: cl /EHsc .\ShellExecuteEx.cpp Shell32.lib
// Open process using ShellExecuteEx
#include <windows.h>
#include <iostream>

int main()
{
    SHELLEXECUTEINFO sei = { 0 };
    sei.cbSize = sizeof(sei);
    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    sei.lpVerb = "open";
    sei.lpFile = "C:\\Windows\\System32\\calc.exe";
    sei.lpParameters = NULL;
    sei.lpDirectory = NULL;
    sei.nShow = SW_SHOWNORMAL;

    if (ShellExecuteEx(&sei))
    {
        HANDLE hProcess = sei.hProcess;
        std::cout << "Process opened successfully!" << std::endl;
        // Use hProcess as needed
        CloseHandle(hProcess);
    }
    else
    {
        DWORD errorCode = GetLastError();
        std::cerr << "Failed to open the process. Error code: " << errorCode << std::endl;
        return 1;
    }

    return 0;
}

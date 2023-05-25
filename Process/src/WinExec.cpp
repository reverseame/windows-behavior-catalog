// Compiled with: cl /EHsc .\WinExec.cpp
// Open process using WinExec
#include <windows.h>
#include <iostream>

int main()
{
    const char* command = "C:\\Windows\\System32\\calc.exe";
    int showCmd = SW_SHOWNORMAL;

    int result = WinExec(command, showCmd);

    if (result > 31)
    {
        std::cout << "Process opened successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Failed to open the process." << std::endl;
        return 1;
    }

    return 0;
}


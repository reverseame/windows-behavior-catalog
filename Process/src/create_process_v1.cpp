// Compiled with: cl /EHsc .\create_process_v1.cpp Wtsapi32.lib
// Create process using CreateProcess
#include <windows.h>
#include <iostream>

int main()
{
    // Specify the path to the target executable
    LPSTR targetExe = "C:\\Windows\\System32\\calc.exe";

    // Initialize the STARTUPINFO structure
    STARTUPINFO si = {};
    si.cb = sizeof(STARTUPINFO);

    // Launch the process
    PROCESS_INFORMATION pi;
    if (!CreateProcess(NULL, targetExe, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        std::cout << "Failed to create process. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Process created successfully!" << std::endl;

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

// Compiled with: cl /EHsc .\OpenProcess.cpp
// Open process using CreateProcess
#include <windows.h>
#include <iostream>

int main()
{
    // Specify the desired access rights and the process ID of the target process
    DWORD desiredAccess = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ;
    BOOL inheritHandle = FALSE;
    DWORD processId = 916; // Replace with the actual process ID

    // Open the process
    HANDLE hProcess = OpenProcess(desiredAccess, inheritHandle, processId);
    if (hProcess == NULL)
    {
        std::cout << "Failed to open process. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Process opened successfully!" << std::endl;

    // Close the process handle
    CloseHandle(hProcess);

    return 0;
}
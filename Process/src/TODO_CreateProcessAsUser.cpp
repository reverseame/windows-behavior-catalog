// Compiled with: cl /EHsc .\CreateProcessAsUser.cpp Wtsapi32.lib Advapi32.lib
// Create process using CreateProcessAsUser
#include <windows.h>
#include <iostream>
#include <wtsapi32.h>

int main()
{
    HANDLE hToken;
    DWORD sessionId;

    // Obtain the primary access token of the specified user
    if (!WTSQueryUserToken(WTSGetActiveConsoleSessionId(), &hToken))
    {
        std::cout << "Failed to get user token. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    // Specify the path to the target executable
    LPSTR targetExe = "C:\\Windows\\System32\\calc.exe";

    // Set the appropriate session ID
    if (!ProcessIdToSessionId(GetCurrentProcessId(), &sessionId))
    {
        std::cout << "Failed to get session ID. Error code: " << GetLastError() << std::endl;
        CloseHandle(hToken);
        return 1;
    }

    // Initialize the STARTUPINFO structure
    STARTUPINFO si = {};
    si.cb = sizeof(STARTUPINFO);
    si.lpDesktop = "winsta0\\default";

    // Launch the process as the specified user
    PROCESS_INFORMATION pi;
    if (!CreateProcessAsUser(hToken, NULL, targetExe, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        std::cout << "Failed to create process as user. Error code: " << GetLastError() << std::endl;
        CloseHandle(hToken);
        return 1;
    }

    std::cout << "Process created successfully!" << std::endl;

    // Clean up the handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hToken);

    return 0;
}
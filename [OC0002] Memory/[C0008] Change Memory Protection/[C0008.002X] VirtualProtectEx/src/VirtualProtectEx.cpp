// Compiled with: cl /EHsc .\VirtualProtectEx.cpp user32.lib
// Memory protection modification with VirtualProtectEx
#include <windows.h>
#include <iostream>

int main() {
    STARTUPINFO startupInfo = { sizeof(startupInfo) };
    PROCESS_INFORMATION processInfo;

    // Start Notepad
    if (!CreateProcess(NULL, "notepad.exe", NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo)) {
        std::cout << "Failed to create process. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    // Wait for Notepad to start
    WaitForInputIdle(processInfo.hProcess, INFINITE);

    // Address of a memory region in Notepad's address space
    LPVOID targetAddress = reinterpret_cast<LPVOID>(0x00400000); // Base address of Notepad (adjust as needed)
    SIZE_T size = 0x1000; // Modify protection for the first memory page

    DWORD newProtection = PAGE_EXECUTE_READWRITE;
    DWORD oldProtection;

    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processInfo.dwProcessId);
    if (!processHandle) {
        std::cout << "Failed to open process. Error code: " << GetLastError() << std::endl;
        return 1;
    }

    // Modify memory protection
    if (!VirtualProtectEx(processHandle, targetAddress, size, newProtection, &oldProtection)) {
        std::cout << "Failed to modify memory protection. Error code: " << GetLastError() << std::endl;
    } else {
        std::cout << "Memory protection modified successfully." << std::endl;
    }

    // Clean up
    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);
    CloseHandle(processHandle);

    return 0;
}


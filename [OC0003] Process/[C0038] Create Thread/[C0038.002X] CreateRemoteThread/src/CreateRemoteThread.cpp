// Compiled with: cl /EHsc .\CreateRemoteThread.cpp user32.lib
// Create thread using CreateRemoteThread 
#include <Windows.h>
#include <iostream>

int main() {
    const char* targetProcessName = "notepad.exe";
    const char* dllPath = "advapi32.dll";

    // Create the target process
    STARTUPINFOA startupInfo = { sizeof(startupInfo) };
    PROCESS_INFORMATION processInfo;

    if (!CreateProcessA(NULL, const_cast<char*>(targetProcessName), NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo)) {
        std::cerr << "Failed to create target process." << std::endl;
        return 1;
    }

    // Wait for the process to initialize
    WaitForInputIdle(processInfo.hProcess, INFINITE);

    // Open the target process with required access
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processInfo.dwProcessId);
    if (!hProcess) {
        std::cerr << "Failed to open target process." << std::endl;
        return 1;
    }

    // Allocate memory for the DLL path in the target process
    LPVOID dllPathAddress = VirtualAllocEx(hProcess, NULL, strlen(dllPath) + 1,
                                           MEM_COMMIT, PAGE_READWRITE);
    if (!dllPathAddress) {
        std::cerr << "Failed to allocate memory in target process." << std::endl;
        CloseHandle(hProcess);
        return 1;
    }

    // Write the DLL path into the allocated memory
    if (!WriteProcessMemory(hProcess, dllPathAddress, dllPath,
                            strlen(dllPath) + 1, NULL)) {
        std::cerr << "Failed to write DLL path to target process memory." << std::endl;
        VirtualFreeEx(hProcess, dllPathAddress, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return 1;
    }

    // Load the kernel32.dll module to get the address of LoadLibraryA function
    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
    FARPROC loadLibraryAddr = GetProcAddress(hKernel32, "LoadLibraryA");

    if (!loadLibraryAddr) {
        std::cerr << "Failed to get address of LoadLibraryA function." << std::endl;
        VirtualFreeEx(hProcess, dllPathAddress, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return 1;
    }

    // Create a remote thread in the target process to load the DLL
    HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, 0,
        (LPTHREAD_START_ROUTINE)loadLibraryAddr, dllPathAddress, 0, NULL);

    if (!hRemoteThread) {
        std::cerr << "Failed to create remote thread." << std::endl;
        VirtualFreeEx(hProcess, dllPathAddress, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return 1;
    } else {
        std::cout << "Successful call to CreateRemoteThread" << std::endl;
    }

    // Wait for the remote thread to finish
    WaitForSingleObject(hRemoteThread, INFINITE);

    // Clean up
    CloseHandle(hRemoteThread);
    VirtualFreeEx(hProcess, dllPathAddress, 0, MEM_RELEASE);
    CloseHandle(hProcess);

    // Clean up process handles
    CloseHandle(processInfo.hThread);
    CloseHandle(processInfo.hProcess);

    return 0;
}

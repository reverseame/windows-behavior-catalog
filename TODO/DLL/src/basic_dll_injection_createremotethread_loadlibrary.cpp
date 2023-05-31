#include <Windows.h>
#include <iostream>

int main()
{
    // Replace with the full path of your DLL
    const char* dllPath = "C:\\Path\\To\\Your\\DLL.dll";
    // Replace with the name of the process you want to inject into
    const char* targetProcessName = "TargetProcess.exe";

    // Find the target process by name
    PROCESSENTRY32 processEntry = {};
    processEntry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE processSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (Process32First(processSnapshot, &processEntry))
    {
        do
        {
            if (strcmp(processEntry.szExeFile, targetProcessName) == 0)
            {
                std::cout << "Found target process with PID: " << processEntry.th32ProcessID << std::endl;
                // Open the process with all access
                HANDLE targetProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processEntry.th32ProcessID);

                // Allocate memory in the target process for the DLL path
                LPVOID remoteDllPath = VirtualAllocEx(targetProcessHandle, NULL, strlen(dllPath) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

                // Write the DLL path to the target process
                WriteProcessMemory(targetProcessHandle, remoteDllPath, dllPath, strlen(dllPath) + 1, NULL);

                // Get the address of LoadLibraryA in kernel32.dll
                HMODULE kernel32Handle = GetModuleHandle("kernel32.dll");
                FARPROC loadLibraryAddr = GetProcAddress(kernel32Handle, "LoadLibraryA");

                // Create a remote thread in the target process to load the DLL
                HANDLE remoteThread = CreateRemoteThread(targetProcessHandle, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddr, remoteDllPath, 0, NULL);
                if (remoteThread != NULL)
                {
                    std::cout << "Remote thread created successfully" << std::endl;
                    CloseHandle(remoteThread);
                }
                else
                {
                    std::cerr << "Failed to create remote thread" << std::endl;
                }

                 // Wait for the remote thread to complete
                WaitForSingleObject(remoteThread, INFINITE);

                // Free the memory allocated in the target process
                VirtualFreeEx(targetProcessHandle, remoteDllPath, 0, MEM_RELEASE);

                // Close the handle to the target process
                CloseHandle(targetProcessHandle);

                break;
            }
        } while (Process32Next(processSnapshot, &processEntry));
    }

    // Close the snapshot handle
    CloseHandle(processSnapshot);

    return 0;
}

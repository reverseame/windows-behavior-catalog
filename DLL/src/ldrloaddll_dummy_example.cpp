#include <windows.h>
#include <winternl.h>
#include <iostream>

#pragma comment(lib, "ntdll.lib")  // Import ntdll.lib library

int main()
{
    // Define variables
    UNICODE_STRING dllName;
    HANDLE dllHandle = NULL;
    NTSTATUS status;

    // Initialize the DLL name as a UNICODE_STRING
    WCHAR dllPath[] = L"C:\\path\\to\\dll.dll";
    RtlInitUnicodeString(&dllName, dllPath);

    // Load the DLL using LdrLoadDll
    status = LdrLoadDll(NULL, NULL, &dllName, &dllHandle);
    if (NT_SUCCESS(status))
    {
        std::cout << "DLL loaded successfully!\n";
    }
    else
    {
        std::cout << "Failed to load DLL! Error code: " << status << "\n";
    }

    // Close the DLL handle
    if (dllHandle != NULL)
    {
        NtClose(dllHandle);
    }

    return 0;
}

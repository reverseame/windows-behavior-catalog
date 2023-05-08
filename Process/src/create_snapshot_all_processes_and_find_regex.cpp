#include <Windows.h>
#include <tlhelp32.h>
#include <regex>
#include <iostream>

int main() {
    // Take a snapshot of all running processes
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create snapshot of running processes\n";
        return 1;
    }

    PROCESSENTRY32 process_entry = { 0 };
    process_entry.dwSize = sizeof(process_entry);

    // Iterate through all running processes
    if (Process32First(snapshot, &process_entry)) {
        do {
            // Open a handle to the process with read permissions
            HANDLE process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_entry.th32ProcessID);
            if (process_handle != NULL) {
                // Get the range of memory addresses used by the process
                SYSTEM_INFO system_info;
                GetSystemInfo(&system_info);
                LPVOID start_address = system_info.lpMinimumApplicationAddress;
                LPVOID end_address = system_info.lpMaximumApplicationAddress;

                // Iterate through all pages of memory and read their contents
                for (LPVOID address = start_address; address < end_address; address = (LPVOID)((DWORD_PTR)address + system_info.dwPageSize)) {
                    MEMORY_BASIC_INFORMATION memory_info;
                    if (VirtualQueryEx(process_handle, address, &memory_info, sizeof(memory_info)) == sizeof(memory_info)) {
                        // Only read pages with read and write permissions
                        if (memory_info.Protect == PAGE_READWRITE) {
                            // Allocate a buffer to hold the contents of the page
                            LPVOID buffer = VirtualAlloc(NULL, memory_info.RegionSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
                            if (buffer != NULL) {
                                // Read the contents of the page into the buffer
                                SIZE_T bytes_read;
                                if (ReadProcessMemory(process_handle, memory_info.BaseAddress, buffer, memory_info.RegionSize, &bytes_read)) {
                                    // Convert the buffer to a string and search for the regular expression
                                    std::string contents((char*)buffer, bytes_read);
                                    std::regex regex("[0-9]");
                                    std::smatch match;
                                    if (std::regex_search(contents, match, regex)) {
                                        std::cout << "Process ID " << process_entry.th32ProcessID << " matched the regex, Name:" << process_entry.szExeFile << std::endl;
                                    }
                                }
                                // Free the buffer
                                VirtualFree(buffer, 0, MEM_RELEASE);
                            }
                        }
                    }
                }
                // Close the process handle
                CloseHandle(process_handle);
            }
        } while (Process32Next(snapshot, &process_entry));
    } else {
        std::cerr << "Failed to get first process.\n";
        CloseHandle(snapshot);
        return 1;
    }

    // Close the snapshot handle
    CloseHandle(snapshot);

    return 0;
}

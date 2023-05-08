#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

int main() {
    // Take a snapshot of all running processes in the system
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: CreateToolhelp32Snapshot failed.\n";
        return 1;
    }

    // Get the first process in the snapshot
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32)) {
        std::cerr << "Error: Process32First failed.\n";
        CloseHandle(hProcessSnap);
        return 1;
    }

    // Loop through all processes in the snapshot
    do {
        std::cout << "Process ID: " << pe32.th32ProcessID << "\n";
        std::cout << "Process Name: " << pe32.szExeFile << "\n";

        // Open the process
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
        if (hProcess == NULL) {
            std::cerr << "Error: OpenProcess failed.\n";
            continue;
        }

        // Get the address range of the process
        SYSTEM_INFO si;
        GetSystemInfo(&si);
        LPVOID lpMinimumAddress = si.lpMinimumApplicationAddress;
        LPVOID lpMaximumAddress = si.lpMaximumApplicationAddress;
        SIZE_T dwPageSize = si.dwPageSize;

        // Loop through all memory pages in the address range of the process
        for (LPVOID lpAddress = lpMinimumAddress; lpAddress < lpMaximumAddress; lpAddress += dwPageSize) {
            MEMORY_BASIC_INFORMATION mbi;
            SIZE_T dwSize = VirtualQueryEx(hProcess, lpAddress, &mbi, sizeof(mbi));
            if (dwSize == 0) {
                break;
            }

            // Check if the memory page is readable and has committed memory
            if ((mbi.State == MEM_COMMIT) && (mbi.Protect != PAGE_NOACCESS) && (mbi.Protect != PAGE_GUARD)) {
                CHAR* pBuffer = new CHAR[mbi.RegionSize];
                SIZE_T dwBytesRead = 0;
                if (ReadProcessMemory(hProcess, lpAddress, pBuffer, mbi.RegionSize, &dwBytesRead)) {
                    // Search the memory page for the string "RazviOverflow"
                    for (DWORD i = 0; i < mbi.RegionSize; i++) {
                        if (memcmp(&pBuffer[i], "RazviOverflow", sizeof("RazviOverflow") - 1) == 0) {
                            std::cout << "String found at address: " << &pBuffer[i] << "\n";
                        }
                    }
                }
                delete[] pBuffer;
            }
        }

        // Close the process handle
        CloseHandle(hProcess);
    } while (Process32Next(hProcessSnap, &pe32));

    // Close the snapshot handle
    CloseHandle(hProcessSnap);

    return 0;
}

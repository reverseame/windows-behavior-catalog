// Compiled with: cl /EHsc .\CreateSnapshot_Iterate.cpp
// Process iteration with CreateToolhelp32Snapshot, Process32First and Process32Next
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

int main() {

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Failed to create process snapshot." << std::endl;
        return 1;
    }

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(snapshot, &entry))
    {
        std::cerr << "Failed to retrieve first process entry." << std::endl;
        CloseHandle(snapshot);
        return 1;
    }

    std::cout << "Process List:" << std::endl;
    do
    {
        std::cout << "Name: " << entry.szExeFile << ", PID: " << entry.th32ProcessID << std::endl;
    } while (Process32Next(snapshot, &entry));

    CloseHandle(snapshot);

    return 0;
}
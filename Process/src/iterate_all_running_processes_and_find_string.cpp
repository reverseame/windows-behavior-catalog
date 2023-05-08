#include <iostream>
#include <windows.h>
#include <psapi.h>
#include <string>

using namespace std;

int main()
{
    // Define the string to search for
    string searchString = "RazviOverflow";
    // Get the list of process identifiers (PIDs)
    DWORD processIDs[1024], bytesReturned;
    if (!EnumProcesses(processIDs, sizeof(processIDs), &bytesReturned))
    {
        cout << "Error: could not enumerate processes." << endl;
        return 1;
    }

    // Calculate the number of processes
    int numProcesses = bytesReturned / sizeof(DWORD);

    // Loop through each process
    for (int i = 0; i < numProcesses; i++)
    {
        // Open the process
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processIDs[i]);
        if (hProcess)
        {
            // Get the process name
            TCHAR processName[MAX_PATH] = TEXT("<unknown>");
            HMODULE hModule;
            DWORD bytesNeeded;
            if (EnumProcessModules(hProcess, &hModule, sizeof(hModule), &bytesNeeded))
            {
                GetModuleBaseName(hProcess, hModule, processName, sizeof(processName) / sizeof(TCHAR));
            }

            // Get the process memory information
            PROCESS_MEMORY_COUNTERS pmc;
            if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
            {
                // Allocate memory to hold the process memory contents
                LPVOID lpBuffer = VirtualAlloc(NULL, pmc.WorkingSetSize, MEM_COMMIT, PAGE_READWRITE);
                if (lpBuffer)
                {
                    // Read the process memory
                    SIZE_T bytesRead;
                    if (ReadProcessMemory(hProcess, pmc.WorkingSetSize, lpBuffer, pmc.WorkingSetSize, &bytesRead))
                    {
                        // Search the process memory for the specified string
                        string memoryContents(static_cast<char*>(lpBuffer), pmc.WorkingSetSize);
                        size_t found = memoryContents.find(searchString);
                        if (found != string::npos)
                        {
                            cout << "Found string " << searchString << " in process " << processName << " (PID: " << processIDs[i] << ")" << endl;
                        }
                    }

                    // Free the allocated memory
                    VirtualFree(lpBuffer, 0, MEM_RELEASE);
                }
            }

            // Close the process handle
            CloseHandle(hProcess);
        }
    }

    return 0;
}

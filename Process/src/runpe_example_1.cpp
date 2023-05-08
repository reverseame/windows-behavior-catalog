#include <windows.h>
#include <stdio.h>

// Function pointer type for the loaded executable's entry point
typedef int (__stdcall *ENTRYPOINT)();

int main() {
    // Open the target executable file
    FILE* fp = fopen("calc.exe", "rb");
    if (!fp) {
        printf("Failed to open executable file.\n");
        return 1;
    }

    // Get the file size
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Allocate memory to hold the executable file contents
    BYTE* fileData = new BYTE[fileSize];
    if (!fileData) {
        printf("Failed to allocate memory for file contents.\n");
        return 1;
    }

    // Read the executable file into memory
    if (fread(fileData, 1, fileSize, fp) != fileSize) {
        printf("Failed to read file data into memory.\n");
        return 1;
    }

    // Close the file handle
    fclose(fp);

    // Get a handle to the current process
    HANDLE currentProcessHandle = GetCurrentProcess();

    // Create a new process in a suspended state
    PROCESS_INFORMATION processInfo = {0};
    STARTUPINFO startupInfo = {0};
    startupInfo.cb = sizeof(STARTUPINFO);
    if (!CreateProcess(NULL, "notepad.exe", NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &startupInfo, &processInfo)) {
        printf("Failed to create new process.\n");
        return 1;
    }

    // Allocate memory in the remote process for the executable file contents
    LPVOID remoteMemory = VirtualAllocEx(processInfo.hProcess, NULL, fileSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (!remoteMemory) {
        printf("Failed to allocate memory in remote process.\n");
        return 1;
    }

    // Write the executable file contents to the remote process
    if (!WriteProcessMemory(processInfo.hProcess, remoteMemory, fileData, fileSize, NULL)) {
        printf("Failed to write data to remote process memory.\n");
        return 1;
    }

    // Get the entry point for the loaded executable
    ENTRYPOINT entryPoint = (ENTRYPOINT)((DWORD_PTR)remoteMemory + ((IMAGE_NT_HEADERS*)((DWORD_PTR)fileData + ((IMAGE_DOS_HEADER*)fileData)->e_lfanew))->OptionalHeader.AddressOfEntryPoint);

    // Resume the suspended process, executing the loaded executable from memory
    if (ResumeThread(processInfo.hThread) == -1) {
        printf("Failed to resume thread.\n");
        return 1;
    }

    // Call the loaded executable's entry point
    int result = entryPoint();

    // Clean up and exit
    VirtualFreeEx(processInfo.hProcess, remoteMemory, fileSize, MEM_RELEASE);
    CloseHandle(processInfo.hThread);
    CloseHandle(processInfo.hProcess);
    delete[] fileData;
    return 0;
}

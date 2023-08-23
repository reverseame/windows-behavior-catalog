// Compiled with: cl /EHsc .\PathAllocCombine.cpp Pathcch.lib
// Alter filename extension with PathAllocCombine
#include <Windows.h>
#include <Shlwapi.h>
#include <stdio.h>
#include <pathcch.h>

int main() {
    PCWSTR basePath = L"C:\\Program Files";
    PCWSTR additionalPath = L"MyApp\\bin\\app.exe";

    PWSTR combinedPath = NULL;
    HRESULT result = PathAllocCombine(basePath, additionalPath, 0, &combinedPath);

    if (SUCCEEDED(result)) {
        wprintf(L"Combined Path: %s\n", combinedPath);
        //LocalFree(combinedPath); // Remember to free the allocated memory
    } else {
        wprintf(L"Path combination failed with HRESULT 0x%X\n", result);
    }

    return 0;
}

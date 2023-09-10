// Compiled with: cl /EHsc .\PathCchRenameExtension.cpp Pathcch.lib
// Alter filename extension with PathCchRenameExtension
// Adapted from https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathaddextensiona
#include <Windows.h>
#include <pathcch.h>
#include <iostream>

int main() {
    wchar_t filePath[40];
    PCWSTR newExtension = L".dll";
    wcsncpy(filePath, L"C:\\Users\\User\\Documents\\example.txtasd", 39);
    PathCchRenameExtension(filePath, 40, newExtension);

    wprintf(L"Modified Path: %s", filePath);

    return 0;
}

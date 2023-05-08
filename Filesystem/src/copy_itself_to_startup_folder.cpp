#include <iostream>
#include <Windows.h>
#include <ShlObj.h>

int main() {
    // Get the path to the current executable
    TCHAR szExePath[MAX_PATH];
    GetModuleFileName(NULL, szExePath, MAX_PATH);

    // Get the path to the startup folder
    TCHAR szStartupPath[MAX_PATH];
    SHGetFolderPath(NULL, CSIDL_STARTUP, NULL, SHGFP_TYPE_CURRENT, szStartupPath);

    // Create the destination path
    TCHAR szDestPath[MAX_PATH];
    PathCombine(szDestPath, szStartupPath, TEXT("MyProgram.exe"));

    // Copy the file to the startup folder
    CopyFile(szExePath, szDestPath, FALSE);

    std::cout << "File copied to startup folder." << std::endl;

    return 0;
}

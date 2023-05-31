// Compiled with: cl /EHsc .\RegQueryValueEx.cpp advapi32.lib
// Query registry value using RegQueryValueEx  
#include <iostream>
#include <Windows.h>

int main() {
    HKEY hKey;
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion", 0, KEY_READ, &hKey);
    if (result != ERROR_SUCCESS) {
        std::cout << "Failed to open registry key. Error code: " << result << std::endl;
        return 1;
    }

    DWORD bufferSize = 256;
    LPBYTE buffer = new BYTE[bufferSize];
    DWORD valueType;

    result = RegQueryValueEx(hKey, "CommonFilesDir", NULL, &valueType, buffer, &bufferSize);
    if (result == ERROR_SUCCESS && valueType == REG_SZ) {
        std::cout << "CommonFilesDir: " << buffer << std::endl;
    } else {
        std::cout << "Failed to query registry value. Error code: " << result << std::endl;
    }

    delete[] buffer;
    RegCloseKey(hKey);

    return 0;
}


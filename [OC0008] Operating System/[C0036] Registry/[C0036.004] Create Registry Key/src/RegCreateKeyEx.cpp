// Compiled with: cl /EHsc .\RegCreateKeyEx.cpp advapi32.lib
// Create registry key using RegCreateKeyEx
#include <Windows.h>
#include <iostream>

int main() {
    HKEY hKey;
    LPCSTR subKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run\\MalwareExample";
    DWORD disposition;

    // Create the registry key
    LONG result = RegCreateKeyEx(HKEY_CURRENT_USER, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &disposition);
    if (result == ERROR_SUCCESS) {
        std::cout << "Registry key created successfully." << std::endl;
        RegCloseKey(hKey);
    } else {
        std::cout << "Failed to create registry key. Error code: " << result << std::endl;
    }

    return 0;
}
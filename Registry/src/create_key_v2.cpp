// Compiled with: cl /EHsc .\create_key_v2.cpp advapi32.lib
// Create registry key using RegCreateKey
#include <Windows.h>
#include <iostream>

int main() {
    HKEY hKey;
    LPCSTR subKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run\\MalwareExample";
    DWORD disposition;

    // Create the registry key
    LONG result = RegCreateKey(HKEY_CURRENT_USER, subKey, &hKey);
    if (result == ERROR_SUCCESS) {
        std::cout << "Registry key created successfully." << std::endl;
        RegCloseKey(hKey);
    } else {
        std::cout << "Failed to create registry key. Error code: " << result << std::endl;
    }

    return 0;
}
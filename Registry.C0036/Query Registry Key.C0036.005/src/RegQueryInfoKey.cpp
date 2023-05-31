// Compiled with: cl /EHsc .\RegQueryInfoKey.cpp advapi32.lib
// Query registry key using RegQueryInfoKey 
#include <iostream>
#include <Windows.h>

int main() {
    HKEY hKey;
    LONG result = RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion", 0, KEY_READ, &hKey);
    if (result != ERROR_SUCCESS) {
        std::cout << "Failed to open registry key. Error code: " << result << std::endl;
        return 1;
    }

    DWORD subkeyCount;
    DWORD maxSubkeyLength;
    DWORD valueCount;
    DWORD maxValueNameLength;
    DWORD maxValueDataLength;
    DWORD securityDescriptor;
    FILETIME lastWriteTime;

    result = RegQueryInfoKey(
        hKey,
        NULL,
        NULL,
        NULL,
        &subkeyCount,
        &maxSubkeyLength,
        NULL,
        &valueCount,
        &maxValueNameLength,
        &maxValueDataLength,
        &securityDescriptor,
        &lastWriteTime
    );

    if (result == ERROR_SUCCESS) {
        std::cout << "Subkey count: " << subkeyCount << std::endl;
        std::cout << "Max subkey length: " << maxSubkeyLength << std::endl;
        std::cout << "Value count: " << valueCount << std::endl;
        std::cout << "Max value name length: " << maxValueNameLength << std::endl;
        std::cout << "Max value data length: " << maxValueDataLength << std::endl;
    } else {
        std::cout << "Failed to query registry key information. Error code: " << result << std::endl;
    }

    RegCloseKey(hKey);

    return 0;
}

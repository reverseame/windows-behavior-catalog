// Compiled with: cl /EHsc .\RegDeleteKeyEx.cpp advapi32.lib
// Delete registry key using RegDeleteKeyEx
#include <Windows.h>
#include <iostream>

int main() {
    LPCSTR subKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run\\MalwareExample";

    // Delete the registry key
    LONG result = RegDeleteKeyEx(HKEY_CURRENT_USER, subKey, KEY_WOW64_64KEY, 0);
    if (result == ERROR_SUCCESS) {
        std::cout << "Registry key deleted successfully." << std::endl;
    } else {
        std::cout << "Failed to delete registry key. Error code: " << result << std::endl;
    }

    return 0;
}
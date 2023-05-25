// Compiled with: cl /EHsc .\RegOpenKeyEx.cpp advapi32.lib
// Open registry key using RegOpenKeyEx
#include <Windows.h>
#include <iostream>

int main()
{
    HKEY hKey;
    LONG result;

    // Open the HKEY_CURRENT_USER\Software registry key
    result = RegOpenKeyEx(HKEY_CURRENT_USER, "Software", 0, KEY_READ, &hKey);
    if (result == ERROR_SUCCESS) {
        std::cout << "Registry key opened successfully." << std::endl;

        // Do something with the opened key

        // Close the opened key
        RegCloseKey(hKey);
    } else {
        std::cout << "Failed to open registry key. Error code: " << result << std::endl;
    }

    return 0;
}
// Compiled with: cl /EHsc .\RegOpenCurrentUser.cpp advapi32.lib
// Open registry key using RegOpenCurrentUser
#include <Windows.h>
#include <iostream>

int main()
{
    HKEY hKey;
    LONG result;

    // Open the HKEY_CURRENT_USER registry key for the current user
    result = RegOpenCurrentUser(KEY_READ, &hKey);
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
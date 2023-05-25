// Compiled with: cl /EHsc .\RegGetValue.cpp advapi32.lib
// Query registry value using RegGetValue   
#include <iostream>
#include <Windows.h>

int main() {
    HKEY hKey;
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion", 0, KEY_READ, &hKey);
    if (result != ERROR_SUCCESS) {
        std::cout << "Failed to open registry key. Error code: " << result << std::endl;
        return 1;
    }

    CHAR valueData[1024];
    DWORD valueDataSize = sizeof(valueData);
    DWORD dataType;

    result = RegGetValue(hKey, NULL, "CommonFilesDir", RRF_RT_REG_SZ, &dataType, valueData, &valueDataSize);
    if (result == ERROR_SUCCESS) {
        if (dataType == REG_SZ) {
            std::cout << "Value Data: " << valueData << "; Data type: " << dataType << std::endl;
        }
        else {
            std::cout << "Invalid data type." << std::endl;
        }
    } else {
        std::cout << "Failed to query registry value. Error code: " << result << std::endl;
    }

    RegCloseKey(hKey);

    return 0;
}
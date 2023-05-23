// Compiled with: cl /EHsc .\query_value_v3.cpp advapi32.lib
// Query registry value using RegEnumValue   
#include <iostream>
#include <Windows.h>

int main() {
    HKEY hKey;
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion", 0, KEY_READ, &hKey);
    if (result != ERROR_SUCCESS) {
        std::cout << "Failed to open registry key. Error code: " << result << std::endl;
        return 1;
    }

    DWORD index = 0;
    CHAR valueName[256];
    DWORD valueNameSize = sizeof(valueName);
    BYTE data[1024];
    DWORD dataSize = sizeof(data);
    DWORD dataType;

    while ((result = RegEnumValue(hKey, index++, valueName, &valueNameSize, NULL, &dataType, data, &dataSize)) == ERROR_SUCCESS) {
        std::cout << "Value Name: " << valueName << std::endl;
        std::cout << "Data Type: " << dataType << std::endl;

        if (dataType == REG_SZ || dataType == REG_EXPAND_SZ) {
            std::cout << "String Value: " << reinterpret_cast<CHAR*>(data) << std::endl;
        }
        else if (dataType == REG_DWORD) {
            DWORD value = *reinterpret_cast<DWORD*>(data);
            std::cout << "DWORD Value: " << value << std::endl;
        }

        // Reset the buffer sizes for the next enumeration
        valueNameSize = sizeof(valueName);
        dataSize = sizeof(data);
    }

    if (result != ERROR_NO_MORE_ITEMS) {
        std::cout << "Failed to enumerate registry values. Error code: " << result << std::endl;
    }

    RegCloseKey(hKey);

    return 0;
}
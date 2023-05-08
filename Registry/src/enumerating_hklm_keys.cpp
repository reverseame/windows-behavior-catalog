// Compiled with: cl /EHsc .\enumerating_hklm_keys.cpp Advapi32.lib
#include <iostream>
#include <windows.h>

// Enumerate all values of a given registry key
void EnumerateValues(HKEY hKey)
{
    DWORD dwIndex = 0;
    TCHAR szValueName[MAX_PATH] = { 0 };
    DWORD dwValueNameLen = MAX_PATH;
    DWORD dwType = 0;
    BYTE* lpData = nullptr;
    DWORD dwDataLen = 0;

    while (RegEnumValue(hKey, dwIndex, szValueName, &dwValueNameLen, NULL, &dwType, nullptr, &dwDataLen) != ERROR_NO_MORE_ITEMS)
    {
        // Allocate memory for the value data
        lpData = new BYTE[dwDataLen];

        // Read the value data
        if (RegEnumValue(hKey, dwIndex, szValueName, &dwValueNameLen, NULL, &dwType, lpData, &dwDataLen) == ERROR_SUCCESS)
        {
            // Print the value name and value data
            std::cout << szValueName << " = ";

            if (dwType == REG_SZ)
            {
                std::cout << (LPCTSTR)lpData << std::endl;
            }
            else if (dwType == REG_DWORD)
            {
                std::cout << *(DWORD*)lpData << std::endl;
            }
            else
            {
                std::cout << "(Unknown value type)" << std::endl;
            }
        }

        // Clean up the allocated memory
        delete[] lpData;

        // Move on to the next value
        dwIndex++;
        dwValueNameLen = MAX_PATH;
        dwDataLen = 0;
    }
}

// Enumerate all subkeys of a given registry key
void EnumerateSubkeys(HKEY hKey)
{
    DWORD dwIndex = 0;
    TCHAR szSubkeyName[MAX_PATH] = { 0 };
    DWORD dwSubkeyNameLen = MAX_PATH;
    HKEY hSubkey = nullptr;

    while (RegEnumKeyEx(hKey, dwIndex, szSubkeyName, &dwSubkeyNameLen, NULL, NULL, NULL, NULL) != ERROR_NO_MORE_ITEMS)
    {
        // Print the subkey name
        std::cout << "[" << szSubkeyName << "]" << std::endl;

        // Open the subkey
        if (RegOpenKeyEx(hKey, szSubkeyName, 0, KEY_READ, &hSubkey) == ERROR_SUCCESS)
        {
            // Recursively enumerate the subkey's subkeys and values
            EnumerateSubkeys(hSubkey);
            EnumerateValues(hSubkey);

            // Close the subkey
            RegCloseKey(hSubkey);
        }

        // Move on to the next subkey
        dwIndex++;
        dwSubkeyNameLen = MAX_PATH;
    }
}

int main()
{
    // Open the root key for reading
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, NULL, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        // Recursively enumerate all subkeys and values of the root key
        EnumerateSubkeys(hKey);
        EnumerateValues(hKey);

        // Close the root key
        RegCloseKey(hKey);
    }
    else
    {
        std::cerr << "Failed to open registry key" << std::endl;
    }

    return 0;
}
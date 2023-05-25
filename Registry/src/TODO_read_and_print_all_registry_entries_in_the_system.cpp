// Compiled with: cl /EHsc .\read_and_print_all_registry_entries_in_the_system.cpp Advapi32.lib
#include <iostream>
#include <Windows.h>

void readSubkeys(HKEY key)
{
    // Get the number of subkeys
    DWORD numSubkeys;
    RegQueryInfoKey(key, NULL, NULL, NULL, &numSubkeys, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    // Read each subkey
    char subkeyName[256];
    for (DWORD i = 0; i < numSubkeys; i++)
    {
        
        DWORD subkeyNameSize = 256;
        RegEnumKeyEx(key, i, subkeyName, &subkeyNameSize, NULL, NULL, NULL, NULL);

        // Open the subkey
        HKEY subkey;
        RegOpenKeyEx(key, subkeyName, 0, KEY_READ, &subkey);

        // Recursively read subkeys
        readSubkeys(subkey);

        // Close the subkey
        RegCloseKey(subkey);
    }

    // Read each value
    DWORD numValues;
    RegQueryInfoKey(key, NULL, NULL, NULL, NULL, NULL, NULL, &numValues, NULL, NULL, NULL, NULL);

    for (DWORD i = 0; i < numValues; i++)
    {
        char valueName[256];
        DWORD valueNameSize = 256;
        RegEnumValue(key, i, valueName, &valueNameSize, NULL, NULL, NULL, NULL);

        DWORD type;
        DWORD dataSize;
        RegQueryValueEx(key, valueName, NULL, &type, NULL, &dataSize);

        // Allocate a buffer for the data
        BYTE* data = new BYTE[dataSize];

        // Read the data
        RegQueryValueEx(key, valueName, NULL, &type, data, &dataSize);

        // Print the value
        std::cout << "Key: " << subkeyName << ", Value: " << valueName << ", Type: " << type << ", Data: ";
        for (DWORD j = 0; j < dataSize; j++)
        {
            std::cout << std::hex << (int)data[j];
        }
        std::cout << std::dec << std::endl;

        // Free the buffer
        delete[] data;
    }
}

int main()
{
    // Open the root key
    HKEY key;
    RegOpenKeyEx(HKEY_LOCAL_MACHINE, NULL, 0, KEY_READ, &key);

    // Read all subkeys and values
    readSubkeys(key);

    // Close the root key
    RegCloseKey(key);

    return 0;
}
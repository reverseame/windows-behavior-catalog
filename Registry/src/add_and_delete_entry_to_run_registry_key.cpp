// Compiled with: cl /EHsc .\add_and_delete_entry_to_run_registry_key.cpp Advapi32.lib
#include <Windows.h>
#include <string>
#include <iostream>

//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
std::string GetLastErrorAsString()
{
    //Get the error message ID, if any.
    DWORD errorMessageID = ::GetLastError();
    if(errorMessageID == 0) {
        return std::string(); //No error message has been recorded
    }
    
    LPSTR messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    
    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);
    
    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);
            
    return message;
}

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

    
    lResult = RegDeleteKeyValue(hKey, NULL, lpValueName);
    if (lResult != ERROR_SUCCESS) {
        // Handle error
        std::cerr << "Error while deleting the subkey"<< std::endl;

        std::cerr << GetLastErrorAsString() << std::endl;
        RegCloseKey(hKey);
        return 1;
    } else {
        std::cout << "Registry entry deleted successfully" << std::endl;
    }

    // Close the key
    RegCloseKey(hKey);

    return 0;
}
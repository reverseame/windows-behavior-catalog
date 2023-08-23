// Compiled with: cl /EHsc .\PathRenameExtension.cpp Shlwapi.lib
// Alter filename extension with PathRenameExtension
// Adapted from https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-pathaddextensiona
#include <Windows.h>
#include <Shlwapi.h>
#include <iostream>

int main() {
    char filePath[40];
    PSTR newExtension = ".dll";
    strncpy(filePath, "C:\\Users\\User\\Documents\\example.txtasd", 39);
    PathRenameExtension(filePath, newExtension);

    std::cout << "Modified Path: " << filePath << std::endl;

    return 0;
}

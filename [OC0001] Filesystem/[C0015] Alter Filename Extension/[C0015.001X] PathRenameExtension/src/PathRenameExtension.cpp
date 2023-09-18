// Compiled with: cl /EHsc .\PathRenameExtension.cpp shlwapi.lib
// Alter filename extension with PathRenameExtension
#include <windows.h>
#include <shlwapi.h>
#include <iostream>

int main() {
    // ANSI string
    const char ansiFilePath[] = "C:\\path\\to\\file.txt";

    // Change the file extension to ".dat"
    char modifiedPath[MAX_PATH];
    strcpy_s(modifiedPath, ansiFilePath);
    if(!PathRenameExtension(modifiedPath, ".dat")){
    	std::cerr << "PathRenameExtension error: " << GetLastError() << std::endl;
    }

    // Print the modified file path
    //std::cout << "Modified file path: " << modifiedPath;

    return 0;
}
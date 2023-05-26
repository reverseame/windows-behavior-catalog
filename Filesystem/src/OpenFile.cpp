// Compiled with: cl /EHsc .\OpenFile.cpp
// Open file with OpenFile
#include <windows.h>
#include <iostream>

int main()
{
    LPSTR filePath = "C:\\Users\\Default\\NTUSER.DAT";
    OFSTRUCT buffer;

    HFILE hFile = OpenFile(filePath, &buffer, OF_READ);
    if (hFile != HFILE_ERROR){
        // File opened successfully.
        std::cout << "File opened successfully." << std::endl;

        // Close the file handle.
        _lclose(hFile);
    }
    else {
        // Failed to open file. 
        std::cout << "Failed to open file: " << GetLastError() << std::endl;
    }

    return 0;
}
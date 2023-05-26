// Compiled with: cl /EHsc .\MoveFile.cpp
// Move file with MoveFile
#include <Windows.h>
#include <iostream>

int main()
{
    LPCSTR sourceFile = "C:\\Users\\Default\\NTUSER.DAT";
    LPCSTR destinationFile = ".\\movedexample";

    BOOL result = MoveFile(sourceFile, destinationFile);
    if (result)
    {
        std::cout << "File moved successfully." << std::endl;
    }
    else
    {
        DWORD errorCode = GetLastError();
        std::cout << "Failed to move file: " << errorCode << std::endl;
    }

    return 0;
}

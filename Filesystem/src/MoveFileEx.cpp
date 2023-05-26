// Compiled with: cl /EHsc .\MoveFileEx.cpp
// Move file with MoveFileEx
#include <Windows.h>
#include <iostream>

int main()
{
    LPCSTR sourceFile = "C:\\Users\\Default\\NTUSER.DAT";
    LPCSTR destinationFile = ".\\movedexample";

    BOOL result = MoveFileEx(sourceFile, destinationFile, MOVEFILE_REPLACE_EXISTING);
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

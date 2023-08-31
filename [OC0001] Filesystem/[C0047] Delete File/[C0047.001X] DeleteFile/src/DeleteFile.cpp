// Compiled with: cl /EHsc .\DeleteFile.cpp
// Delete file with DeleteFile
#include <iostream>
#include <windows.h>

int main() {

    // Delete the file
    int success = DeleteFile("C:\\Users\\Default\\NTUSER.DAT");
    if (!success) {
        std::cout << "Failed to delete file: " << GetLastError() << std::endl;
        return 1;
    }
    
    return 0;
}

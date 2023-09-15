// Compiled with: cl /EHsc .\SHCreateDirectoryEx.cpp Shell32.lib
// Create directory with SHCreateDirectoryEx
#include <iostream>
#include <Shlobj.h>

int main() {
    HRESULT result = SHCreateDirectoryEx(NULL, "C:\\ExampleDirectory", NULL);
    if (!SUCCEEDED(result)) {
        std::cerr << "Failed to create directory. HRESULT: " << result << std::endl;
    }

    return 0;
}

// Compiled with: cl /EHsc .\SHCreateDirectory.cpp Shell32.lib
// Create directory with SHCreateDirectory
#include <iostream>
#include <Shlobj.h>

int main() {
    HRESULT result = SHCreateDirectory(NULL, L"C:\\ExampleDirectory");
    if (SUCCEEDED(result)) {
        std::cout << "Directory created successfully." << std::endl;
    } else {
        std::cerr << "Failed to create directory. HRESULT: " << result << std::endl;
    }

    return 0;
}

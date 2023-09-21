// Compiled with: cl /EHsc .\PathCchCombine.cpp Pathcch.lib
// Alter filename extension with PathCchCombine
#include <windows.h>
#include <pathcch.h>
#include <iostream>

int main() {
    const size_t cchPathOut = 300;
    wchar_t pszPathOut[cchPathOut];

    HRESULT hr = PathCchCombine(pszPathOut, cchPathOut, L"C:\\Razvi\\",  L".dll");

    /*
    // Check if the combination was successful
    if (SUCCEEDED(hr)) {
        // Print the combined path
        wprintf(L"Combined path: %s", pszPathOut);
    } else {
        // Print an error message
        std::cerr << "Error combining paths: " << hr << std::endl;
    }*/

    if (!SUCCEEDED(hr)) {
        std::cerr << "Error combining paths: " << hr << std::endl;
    }

    return 0;
}
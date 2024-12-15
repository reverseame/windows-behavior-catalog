// Compiled with: cl /EHsc .\CryptCreateHash.cpp advapi32.lib
// Create hash with CryptCreateHash
#include <windows.h>
#include <wincrypt.h>
#include <iostream>

int main() {
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;

    // Acquire a cryptographic context
    if (!CryptAcquireContext(&hProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        std::cerr << "CryptAcquireContext failed. Error: " << GetLastError() << "\n";
        return 1;
    }

    // Create a hash object
    if (!CryptCreateHash(hProv, CALG_SHA1, 0, 0, &hHash)) {
        std::cerr << "CryptCreateHash failed. Error: " << GetLastError() << "\n";
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    std::cout << "Hash object created successfully.\n";

    // Cleanup
    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);

    return 0;
}

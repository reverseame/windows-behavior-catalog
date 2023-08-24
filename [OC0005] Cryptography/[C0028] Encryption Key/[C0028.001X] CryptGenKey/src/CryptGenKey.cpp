// Compiled with: cl /EHsc .\CryptGenKey.cpp Advapi32.lib
// Generate encryption key with CryptGenKey
#include <Windows.h>
#include <Wincrypt.h>
#include <iostream>

int main() {
    HCRYPTPROV hCryptProv = NULL;
    HCRYPTKEY hKey = NULL;

    // Acquire a cryptographic context
    if (!CryptAcquireContext(&hCryptProv, "random_container_name", NULL, PROV_RSA_FULL, NULL )) {
        if (GetLastError() == NTE_BAD_KEYSET){
           if (!CryptAcquireContext(&hCryptProv,  "random_container_name",  NULL,  PROV_RSA_FULL,  CRYPT_NEWKEYSET)){
                std::cerr << "CryptAcquireContext failed, error: " << GetLastError() << GetLastErrorAsString() << std::endl;
                CryptReleaseContext(hCryptProv, 0);
           }
            std::cerr << "CryptAcquireContext failed, error: " << GetLastError() << std::endl;
            CryptReleaseContext(hCryptProv, 0);
        return 1;
        }
    }

    // Generate a random session key
    if (!CryptGenKey(hCryptProv, CALG_RSA_KEYX, CRYPT_EXPORTABLE, &hKey)) {
        std::cerr << "CryptGenKey failed, error: " << GetLastError() << std::endl;
        CryptReleaseContext(hCryptProv, 0);
        return 1;
    }

    std::cout << "Cryptographic key generated successfully!" << std::endl;

    // Clean up
    CryptDestroyKey(hKey);
    CryptReleaseContext(hCryptProv, 0);

    return 0;
}

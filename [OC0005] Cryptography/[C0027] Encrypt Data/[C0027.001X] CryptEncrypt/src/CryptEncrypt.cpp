// Compiled with: cl /EHsc .\CryptEncrypt.cpp Advapi32.lib
// Encrypt data withCryptEncrypt
#include <Windows.h>
#include <Wincrypt.h>
#include <iostream>

int main() {
    HCRYPTPROV hCryptProv = NULL;
    HCRYPTKEY hKey = NULL;

    // Acquire a cryptographic context
    // Acquire a cryptographic context
    if (!CryptAcquireContext(&hCryptProv, "random_container_name", NULL, PROV_RSA_FULL, 0)) {
        if (GetLastError() == NTE_BAD_KEYSET){
           if (!CryptAcquireContext(&hCryptProv,  "random_container_name",  NULL,  PROV_RSA_FULL,  CRYPT_NEWKEYSET)){
                std::cerr << "CryptAcquireContext failed, error: " << GetLastError() <<  std::endl;
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

    // Data to be encrypted
    BYTE plainData[] = "Hello, encryption!";
    DWORD dataLen = sizeof(plainData);
    BYTE cipherData[1000];

    // Encrypt the data
    if (!CryptEncrypt(hKey, NULL, TRUE, 0, cipherData, &dataLen, 1000)) {
        std::cerr << "CryptEncrypt failed, error: " << GetLastError() << std::endl;
        CryptDestroyKey(hKey);
        CryptReleaseContext(hCryptProv, 0);
        return 1;
    }

    std::cout << "Data encrypted successfully!" << cipherData << std::endl;

    // Clean up
    CryptDestroyKey(hKey);
    CryptReleaseContext(hCryptProv, 0);

    return 0;
}

// Compiled with: cl /EHsc .\CryptDecrypt.cpp Advapi32.lib
// Decrypt data with CryptDecrypt
#include <Windows.h>
#include <Wincrypt.h>
#include <iostream>

int main() {
    HCRYPTPROV hCryptProv = NULL;
    HCRYPTKEY hKey = NULL;

    // Acquire a cryptographic context
    if (!CryptAcquireContext(&hCryptProv, "random_container_name_1337", NULL, PROV_RSA_FULL, 0)) {
        if (GetLastError() == NTE_BAD_KEYSET){
           if (!CryptAcquireContext(&hCryptProv,  "random_container_name_1337",  NULL,  PROV_RSA_FULL,  CRYPT_NEWKEYSET)){
                std::cerr << "CryptAcquireContext with CRYPT_NEWKEYSET failed, error: " << GetLastError() << std::endl;
                CryptReleaseContext(hCryptProv, 0);
                return 1;
           }
        } else {
            std::cerr << "CryptAcquireContext with null flags failed, error: " << GetLastError() << std::endl;
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
    //BYTE cipherData[1000];

    // Encrypt the data
    if (!CryptEncrypt(hKey, NULL, TRUE, 0, plainData, &dataLen, 1000)) {
        std::cerr << "CryptEncrypt failed, error: " << GetLastError() << std::endl;
        CryptDestroyKey(hKey);
        CryptReleaseContext(hCryptProv, 0);
        return 1;
    }

    std::cout << "Data encrypted successfully! " << plainData << std::endl;

    if (!CryptDecrypt(hKey, NULL, TRUE, NULL, plainData, &dataLen)) {
        std::cerr << "CryptDecrypt failed, error: " << GetLastError() << std::endl;
        CryptDestroyKey(hKey);
        CryptReleaseContext(hCryptProv, 0);
        return 1;
    }

    std::cout << "Data decrypted successfully! " << plainData << std::endl;

    // Clean up
    CryptDestroyKey(hKey);
    CryptReleaseContext(hCryptProv, 0);

    return 0;
}

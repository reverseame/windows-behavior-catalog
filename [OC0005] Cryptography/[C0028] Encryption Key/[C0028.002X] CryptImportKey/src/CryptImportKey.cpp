// Compiled with: cl /EHsc .\CryptImportKey.cpp Advapi32.lib
// Import key with CryptImportKey
#include <windows.h>
#include <wincrypt.h>
#include <iostream>

int main() {
    HCRYPTPROV hProv;
    HCRYPTKEY hKey;
    BYTE keyBlob[256];
    DWORD keyBlobLen = 256;

    if (!CryptAcquireContext(&hProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        std::cerr << "CryptAcquireContext failed.\n";
        return 1;
    }

    if (!CryptGenKey(hProv, CALG_RSA_KEYX, 0x04000000, &hKey)) {
        std::cerr << "CryptGenKey failed.\n";
        CryptReleaseContext(hProv, 0);
        return 1;
    }


    // Export Key
    if (!CryptExportKey(hKey, 0, PUBLICKEYBLOB, 0, keyBlob, &keyBlobLen)) {
        std::cerr << "CryptExportKey failed, error: " << GetLastError() << std::endl;
        CryptDestroyKey(hKey);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    std::cout << "Key exported, length: " << keyBlobLen << "\n" << keyBlob << std::endl;

    // Import key
    if (!CryptImportKey(hProv, keyBlob, keyBlobLen, 0, 0, &hKey)) {
        std::cerr << "CryptImportKey failed.\n";
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    std::cout << "Key imported successfully.\n";

    CryptDestroyKey(hKey);
    CryptReleaseContext(hProv, 0);
    return 0;
}

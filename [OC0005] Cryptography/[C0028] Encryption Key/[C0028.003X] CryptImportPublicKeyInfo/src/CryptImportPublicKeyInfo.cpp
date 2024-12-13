// Compiled with: cl /EHsc .\CryptImportPublicKeyInfo.cpp Advapi32.lib Crypt32.lib
// Import key with CryptImportPublicKeyInfo
#include <windows.h>
#include <wincrypt.h>
#include <iostream>

int main() {
    HCRYPTPROV hProv = 0;
    HCRYPTKEY hKey = 0;
    CERT_PUBLIC_KEY_INFO publicKeyInfo;
    DWORD publicKeyInfoLen = 0;

    // Acquire a cryptographic provider
    if (!CryptAcquireContext(&hProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        std::cerr << "CryptAcquireContext failed. Error: " << GetLastError() << "\n";
        return 1;
    }

    // Generate a key pair (RSA in this case)
    if (!CryptGenKey(hProv, AT_KEYEXCHANGE, 0, &hKey)) {
        std::cerr << "CryptGenKey failed. Error: " << GetLastError() << "\n";
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    // Query size of the public key info
    if (!CryptExportPublicKeyInfo(hProv, AT_KEYEXCHANGE, X509_ASN_ENCODING, NULL, &publicKeyInfoLen)) {
        std::cerr << "CryptExportPublicKeyInfo (size query) failed. Error: " << GetLastError() << "\n";
        CryptDestroyKey(hKey);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    // Allocate memory for the public key info
    BYTE* publicKeyInfoBuffer = new BYTE[publicKeyInfoLen];

    // Export the public key info
    if (!CryptExportPublicKeyInfo(hProv, AT_KEYEXCHANGE, X509_ASN_ENCODING, (PCERT_PUBLIC_KEY_INFO)publicKeyInfoBuffer, &publicKeyInfoLen)) {
        std::cerr << "CryptExportPublicKeyInfo failed. Error: " << GetLastError() << "\n";
        delete[] publicKeyInfoBuffer;
        CryptDestroyKey(hKey);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

   // Import the public key info
    HCRYPTKEY hImportedKey = 0;
    if (!CryptImportPublicKeyInfo(hProv, X509_ASN_ENCODING, (PCERT_PUBLIC_KEY_INFO)publicKeyInfoBuffer, &hImportedKey)) {
        std::cerr << "CryptImportPublicKeyInfo failed. Error: " << GetLastError() << "\n";
        delete[] publicKeyInfoBuffer;
        CryptDestroyKey(hKey);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    std::cout << "Public key info imported successfully.\n" << hImportedKey << std::endl;

    // Cleanup
    delete[] publicKeyInfoBuffer;
    CryptDestroyKey(hKey);
    CryptDestroyKey(hImportedKey);
    CryptReleaseContext(hProv, 0);
    return 0;
}

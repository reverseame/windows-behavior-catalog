// Compiled with: cl /EHsc .\BCryptImportKeyPair.cpp bcrypt.lib
// Import key with BCryptImportKeyPair

#include <windows.h>
#include <bcrypt.h>
#include <iostream>
#include <vector>

int main() {
    BCRYPT_ALG_HANDLE hAlg = NULL;
    BCRYPT_KEY_HANDLE hKey = NULL;
    BCRYPT_KEY_HANDLE hImportedKey = NULL;
    NTSTATUS status;

    // Open RSA algorithm provider
    status = BCryptOpenAlgorithmProvider(&hAlg, BCRYPT_RSA_ALGORITHM, NULL, 0);
    if (status) {
        std::cerr << "BCryptOpenAlgorithmProvider failed. Error: 0x" << std::hex << status << "\n";
        return 1;
    }

    // Generate a key pair
    status = BCryptGenerateKeyPair(hAlg, &hKey, 2048, 0); // 2048-bit RSA key
    if (status) {
        std::cerr << "BCryptGenerateKeyPair failed. Error: 0x" << std::hex << status << "\n";
        BCryptCloseAlgorithmProvider(hAlg, 0);
        return 1;
    }

    // Finalize the key pair
    status = BCryptFinalizeKeyPair(hKey, 0);
    if (status) {
        std::cerr << "BCryptFinalizeKeyPair failed. Error: 0x" << std::hex << status << "\n";
        BCryptDestroyKey(hKey);
        BCryptCloseAlgorithmProvider(hAlg, 0);
        return 1;
    }

    std::cout << "Key pair generated successfully. Length: " << std::endl;

    // Export the key pair in BCRYPT_RSAPRIVATE_BLOB format
    DWORD keyBlobLen = 0;

    // Query the size of the exported blob
    status = BCryptExportKey(hKey, NULL, BCRYPT_RSAPRIVATE_BLOB, NULL, 0, &keyBlobLen, 0);
    if (status) {
        std::cerr << "BCryptExportKey (size query) failed. Error: 0x" << std::hex << status << "\n";
        BCryptDestroyKey(hKey);
        BCryptCloseAlgorithmProvider(hAlg, 0);
        return 1;
    }

    // Allocate memory for the exported blob
    std::vector<UCHAR> keyBlob(keyBlobLen);

    // Export the key
    status = BCryptExportKey(hKey, NULL, BCRYPT_RSAPRIVATE_BLOB, keyBlob.data(), keyBlobLen, &keyBlobLen, 0);
    if (status) {
        std::cerr << "BCryptExportKey failed. Error: 0x" << std::hex << status << "\n";
        BCryptDestroyKey(hKey);
        BCryptCloseAlgorithmProvider(hAlg, 0);
        return 1;
    }

    std::cout << "Key pair exported successfully. Length: " << keyBlobLen << " bytes\n";

    // Import the key pair back using BCryptImportKeyPair
    status = BCryptImportKeyPair(hAlg, NULL, BCRYPT_RSAPRIVATE_BLOB, &hImportedKey, keyBlob.data(), keyBlobLen, 0);
    if (status) {
        std::cerr << "BCryptImportKeyPair failed. Error: 0x" << std::hex << status << "\n";
        BCryptDestroyKey(hKey);
        BCryptCloseAlgorithmProvider(hAlg, 0);
        return 1;
    }

    std::cout << "Key pair imported successfully.\n" << keyBlob.data() << std::endl;

    // Cleanup
    BCryptDestroyKey(hKey);
    BCryptDestroyKey(hImportedKey);
    BCryptCloseAlgorithmProvider(hAlg, 0);

    return 0;
}
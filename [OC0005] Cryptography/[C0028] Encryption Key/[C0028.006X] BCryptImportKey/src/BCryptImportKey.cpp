// Compiled with: cl /EHsc .\BCryptImportKey.cpp bcrypt.lib
// Import key with BCryptImporttKey
#include <windows.h>
#include <bcrypt.h>
#include <iostream>
#include <vector>

int main() {
    BCRYPT_ALG_HANDLE hAlg = NULL;
    BCRYPT_KEY_HANDLE hKey = NULL;
    NTSTATUS status;

    // Symmetric key material
    UCHAR keyMaterial[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                             0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};

    // Open AES algorithm provider
    status = BCryptOpenAlgorithmProvider(&hAlg, BCRYPT_AES_ALGORITHM, NULL, 0);
    if (status) {
        std::cerr << "BCryptOpenAlgorithmProvider failed. Error: " << std::hex << status << "\n";
        return 1;
    }

    // Generate a symmetric key
    status = BCryptGenerateSymmetricKey(hAlg, &hKey, NULL, 0, keyMaterial, sizeof(keyMaterial), 0);
    if (status) {
        std::cerr << "BCryptGenerateSymmetricKey failed. Error: " << std::hex << status << "\n";
        BCryptCloseAlgorithmProvider(hAlg, 0);
        return 1;
    }

    // Export the key in raw format
    DWORD exportedKeyLen = 0;

    // Step 1: Get the size of the exported key
    status = BCryptExportKey(hKey, NULL, BCRYPT_KEY_DATA_BLOB, NULL, 0, &exportedKeyLen, 0);
    if (status) {
        std::cerr << "BCryptExportKey (size query) failed. Error: " << std::hex << status << "\n";
        BCryptDestroyKey(hKey);
        BCryptCloseAlgorithmProvider(hAlg, 0);
        return 1;
    }

    // Allocate buffer for exported key
    std::vector<UCHAR> exportedKey(exportedKeyLen);

    // Step 2: Export the key
    status = BCryptExportKey(hKey, NULL, BCRYPT_KEY_DATA_BLOB, exportedKey.data(), exportedKeyLen, &exportedKeyLen, 0);
    if (status) {
        std::cerr << "BCryptExportKey (export) failed. Error: " << std::hex << status << "\n";
        BCryptDestroyKey(hKey);
        BCryptCloseAlgorithmProvider(hAlg, 0);
        return 1;
    }

    std::cout << "Key exported successfully. Exported key length: " << exportedKeyLen << "\n";

    status = BCryptImportKey(hAlg, NULL, BCRYPT_KEY_DATA_BLOB, &hKey, NULL, 0, exportedKey.data(), exportedKeyLen, 0);
    if (status) {
        std::cerr << "BCryptImportKey failed.\n";
        BCryptCloseAlgorithmProvider(hAlg, 0);
        return 1;
    }

    std::cout << "Key imported successfully.\n";

    // Cleanup
    BCryptDestroyKey(hKey);
    BCryptCloseAlgorithmProvider(hAlg, 0);
    return 0;
}

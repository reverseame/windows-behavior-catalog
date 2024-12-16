// Compiled with: cl /EHsc .\BCryptGenerateKeyPair.cpp bcrypt.lib
// Generate key with BCryptGenerateKeyPair

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

    // Cleanup
    BCryptDestroyKey(hKey);
    BCryptDestroyKey(hImportedKey);
    BCryptCloseAlgorithmProvider(hAlg, 0);

    return 0;
}

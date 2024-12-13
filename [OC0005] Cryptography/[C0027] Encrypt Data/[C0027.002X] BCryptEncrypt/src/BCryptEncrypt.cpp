// Compiled with: cl /EHsc .\BCryptEncrypt.cpp bcrypt.lib
// Encrypt data with BCryptEncrypt
//#include <ntstatus.h>
#include <windows.h>
#include <bcrypt.h>
#include <iostream>

int main() {
    BCRYPT_ALG_HANDLE hAlg = NULL;
    BCRYPT_KEY_HANDLE hKey = NULL;
    NTSTATUS status;
    UCHAR keyMaterial[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                             0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};
    UCHAR plainText[] = "RazviOverflow!!0x1337DEADBEEF!!!"; // Length multiple of 16
    UCHAR cipherText[128] = {0};
    UCHAR iv[16] = {0}; // Initialization vector (all zero for simplicity).
    DWORD cipherTextLen = 0, dataLen = 0;

    // Open AES algorithm provider
    status = BCryptOpenAlgorithmProvider(&hAlg, BCRYPT_AES_ALGORITHM, NULL, 0);
    if (status) {
        std::cerr << "BCryptOpenAlgorithmProvider failed. Error: " << std::hex << status << "\n";
        return 1;
    }

    // Set the block chaining mode to CBC
    status = BCryptSetProperty(hAlg, BCRYPT_CHAINING_MODE, (PUCHAR)BCRYPT_CHAIN_MODE_CBC, sizeof(BCRYPT_CHAIN_MODE_CBC), 0);
    if (status) {
        std::cerr << "BCryptSetProperty failed. Error: " << std::hex << status << "\n";
        BCryptCloseAlgorithmProvider(hAlg, 0);
        return 1;
    }

    // Generate a symmetric key
    status = BCryptGenerateSymmetricKey(hAlg, &hKey, NULL, 0, keyMaterial, sizeof(keyMaterial), 0);
    if (status) {
        std::cerr << "BCryptGenerateSymmetricKey failed. Error: " << std::hex << status << "\n";
        BCryptCloseAlgorithmProvider(hAlg, 0);
        return 1;
    }

    // Encrypt the data
    status = BCryptEncrypt(hKey, plainText, sizeof(plainText) - 1, NULL, iv, sizeof(iv), cipherText, sizeof(cipherText), &cipherTextLen, 0);
    if (status) {
        std::cerr << "BCryptEncrypt failed. Error: " << std::hex << status << "\n";
        BCryptDestroyKey(hKey);
        BCryptCloseAlgorithmProvider(hAlg, 0);
        return 1;
    }

    //std::cout << "Encryption succeeded. CipherText length: " << cipherTextLen << std::endl;
    //std::cout << "Plaintext is: " << plainText << " while ciphertext is: " << cipherText << std::endl;

    // Cleanup
    BCryptDestroyKey(hKey);
    BCryptCloseAlgorithmProvider(hAlg, 0);
    return 0;
}
#include <iostream>
#include <Windows.h>
#include <WinInet.h>
#include <iphlpapi.h>
#include <icmpapi.h>

#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

bool CheckInternetConnection() {
    DWORD flags = 0;
    return InternetGetConnectedState(&flags, 0);
}

bool Ping(const char* address) {
    HANDLE handle = IcmpCreateFile();
    if (handle == INVALID_HANDLE_VALUE) {
        return false;
    }

    const int bufferSize = 32;
    char sendBuffer[bufferSize] = { 0 };
    char receiveBuffer[bufferSize] = { 0 };

    IPAddr ipAddress;
    if (InetPton(AF_INET, address, &ipAddress) != 1) {
        return false;
    }

    const int timeout = 1000;
    DWORD replyCount = IcmpSendEcho(handle, ipAddress, sendBuffer, bufferSize, NULL, receiveBuffer, bufferSize, timeout);
    IcmpCloseHandle(handle);

    return replyCount > 0;
}

int main() {
    if (!CheckInternetConnection()) {
        std::cout << "No internet connection." << std::endl;
        return 0;
    }

    if (Ping("www.google.com")) {
        std::cout << "Ping successful." << std::endl;
    } else {
        std::cout << "Ping failed." << std::endl;
    }

    return 0;
}

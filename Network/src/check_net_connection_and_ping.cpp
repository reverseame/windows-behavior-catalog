// Compiled with cl /EHsc .\check_net_connection_and_ping.cpp Ws2_32.lib Iphlpapi.lib Wininet.lib

#include <iostream>
#include <Ws2tcpip.h>
#include <Windows.h>
#include <WinInet.h>
#include <iphlpapi.h>
#include <icmpapi.h>

bool CheckInternetConnection() {
    DWORD flags = 0;
    return InternetGetConnectedState(&flags, 0);
}

bool Ping(const char* address) {
    HANDLE handle = IcmpCreateFile();
    if (handle == INVALID_HANDLE_VALUE) {
    	std::cout << "Error creating ICMP handle" << std::endl;
        return false;
    }

    const int bufferSize = 100;
    char sendBuffer[bufferSize] = { 0 };
    char receiveBuffer[bufferSize] = { 0 };

    IPAddr ipAddress;
    if (InetPton(AF_INET, address, &ipAddress) != 1) {
    	std::cout << "Error transforming addres to IPAddr (InetPton)" << std::endl;
        return false;
    }

    const int timeout = 1000;
    DWORD replyCount = IcmpSendEcho(handle, ipAddress, sendBuffer, bufferSize, NULL, receiveBuffer, bufferSize, timeout);
    
    if (!replyCount){
    	std::cout << "No replies received" << std::endl;
    }

    IcmpCloseHandle(handle);
    return replyCount > 0;
}

int main() {
    if (!CheckInternetConnection()) {
        std::cout << "No internet connection." << std::endl;
        return 0;
    }

    if (Ping("142.250.184.14")) { // google.com ip
        std::cout << "Ping successful." << std::endl;
    } else {
        std::cout << "Ping failed." << std::endl;
    }

    return 0;
}

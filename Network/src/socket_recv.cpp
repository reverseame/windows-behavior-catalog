// Compiled with: cl /EHsc .\socket_recv.cpp ws2_32.lib
// Adapted from https://learn.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-recv
#include <iostream>
#include <winsock2.h>

#define DEFAULT_BUFLEN 512

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed with error: " << iResult << std::endl;
        return 1;
    }

    // Create a socket
    SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        std::cerr << "socket failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Define the server address
    SOCKADDR_IN serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("1.1.1.1"); // Replace with the IP address of the server you want to connect to
    serverAddr.sin_port = htons(80); // Replace with the port number of the server

    // Connect to the server
    iResult = connect(ConnectSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    if (iResult == SOCKET_ERROR) {
        std::cerr << "connect failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Receive one chunk of data
    iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    if ( iResult > 0 )
        printf("Bytes received: %d\n", iResult);
    else if ( iResult == 0 )
        printf("Connection closed\n");
    else
        printf("recv failed: %d\n", WSAGetLastError());
   
    // Close the socket and cleanup Winsock
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}

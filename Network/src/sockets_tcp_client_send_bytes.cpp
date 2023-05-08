#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") // Link to ws2_32.lib library

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
    serverAddr.sin_addr.s_addr = inet_addr("216.58.194.174"); // Replace with the IP address of the server you want to connect to
    serverAddr.sin_port = htons(80); // Replace with the port number of the server

    // Connect to the server
    iResult = connect(ConnectSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    if (iResult == SOCKET_ERROR) {
        std::cerr << "connect failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // Send some bytes to the server
    char* sendData = "Hello, server!";
    iResult = send(ConnectSocket, sendData, strlen(sendData), 0);
    if (iResult == SOCKET_ERROR) {
        std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // Close the socket and cleanup Winsock
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}

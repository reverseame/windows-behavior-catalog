// Compiled with: cl /EHsc .\InternetConnect.cpp Wininet.lib
// Establish HTTP connection with InternetConnect, HttpOpenRequest, HttpSendRequest
#include <Windows.h>
#include <WinInet.h>
#include <iostream>

int main() {
    // Open a connection to the internet
    HINTERNET hInternet = InternetOpen("HTTP Example", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) {
        std::cerr << "Failed to open internet connection" << std::endl;
        return 1;
    }

    // Open a connection to a website
    HINTERNET hConnect = InternetConnect(hInternet, "www.google.com", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (!hConnect) {
        std::cerr << "Failed to connect to website" << std::endl;
        InternetCloseHandle(hInternet);
        return 1;
    }

    // Open an HTTP request
    HINTERNET hRequest = HttpOpenRequest(hConnect, "GET", "/", NULL, NULL, NULL, INTERNET_FLAG_RELOAD, 0);
    if (!hRequest) {
        std::cerr << "Failed to open HTTP request" << std::endl;
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return 1;
    }

    // Send the HTTP request
    BOOL bSendRequest = HttpSendRequest(hRequest, NULL, 0, NULL, 0);
    if (!bSendRequest) {
        std::cerr << "Failed to send HTTP request" << std::endl;
        InternetCloseHandle(hRequest);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return 1;
    }

    // Read the response from the server
    char buffer[1024];
    DWORD bytesRead = 0;
    while (InternetReadFile(hRequest, buffer, sizeof(buffer), &bytesRead) && bytesRead != 0) {
        std::cout.write(buffer, bytesRead);
    }

    // Close the HTTP request, connection, and internet handles
    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return 0;
}

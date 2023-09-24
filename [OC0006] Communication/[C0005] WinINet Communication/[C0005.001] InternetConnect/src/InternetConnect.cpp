// Compiled with: cl /EHsc .\InternetConnect.cpp Wininet.lib
// Establish HTTP connection with InternetConnect, HttpOpenRequest, HttpSendRequest
#include <Windows.h>
#include <WinInet.h>
#include <iostream>

int main() {
    // Open a connection to the internet
    HINTERNET hInternet = InternetOpen("HTTP Example", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) {
        printf("Failed to open internet connection: %d", GetLastError());
        return 1;
    }

    // Open a connection to a website
    HINTERNET hConnect = InternetConnect(hInternet, "www.httpbin.org", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (!hConnect) {
        printf("Failed to connect to website: %d", GetLastError());
        InternetCloseHandle(hInternet);
        return 1;
    }

    // Open an HTTP request
    HINTERNET hRequest = HttpOpenRequest(hConnect, "GET", "/", NULL, NULL, NULL, INTERNET_FLAG_RELOAD, 0);
    if (!hRequest) {
        printf("Failed to open HTTP request: %d", GetLastError());
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return 1;
    }

    // Send the HTTP request
    BOOL bSendRequest = HttpSendRequest(hRequest, NULL, 0, NULL, 0);
    if (!bSendRequest) {
        printf("Failed to send HTTP request: %d", GetLastError());
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

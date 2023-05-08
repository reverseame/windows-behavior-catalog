// Note that the wininet.lib library must be linked in order to use the WinINet functions.
#include <windows.h>
#include <wininet.h>
#include <iostream>
#pragma comment(lib, "wininet.lib")

int main() {
    // Initialize WinINet
    HINTERNET hInternet = InternetOpen(L"WinINet", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) {
        std::cout << "Error initializing WinINet: " << GetLastError() << std::endl;
        return 1;
    }

    // Check for internet connectivity by pinging Google
    HINTERNET hUrl = InternetOpenUrl(hInternet, L"https://www.google.com", NULL, 0, INTERNET_FLAG_NO_CACHE_WRITE, 0);
    if (!hUrl) {
        std::cout << "Error connecting to Google: " << GetLastError() << std::endl;
        return 1;
    }

    // Check the HTTP status code
    DWORD statusCode;
    DWORD statusCodeSize = sizeof(DWORD);
    HttpQueryInfo(hUrl, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &statusCode, &statusCodeSize, NULL);
    if (statusCode != HTTP_STATUS_OK) {
        std::cout << "HTTP error: " << statusCode << std::endl;
        return 1;
    }

    std::cout << "Internet connection successful!" << std::endl;

    // Clean up
    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);

    return 0;
}

// Compiled with: cl /EHsc .\InternetOpenUrl.cpp Wininet.lib
// Establish HTTP connection with InternetOpenUrl
#include <Windows.h>
#include <WinInet.h>
#include <iostream>

int main() {
    
    DWORD bytesRead = 0;
    char buffer[1024];

    // Initialize WinINet
    HINTERNET hInternet = InternetOpen("HTTP Example", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) {
        printf("Failed to open internet connection: %d", GetLastError());
        return 1;
    }

    // Open the connection 
    HINTERNET hConnect = InternetOpenUrl(hInternet, "https://www.httpbin.org", NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hConnect) {
        printf("InternetOpenUrl failed: %d", GetLastError());
        InternetCloseHandle(hInternet);
        return 1;
    }

    // Read the response
    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        // Process or display the data as needed
        std::cout.write(buffer, bytesRead);
    }

    // Cleanup
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return 0;
}
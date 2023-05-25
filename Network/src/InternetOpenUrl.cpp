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
        std::cerr << "Failed to open internet connection: " << GetLastError() << std::endl;
        return 1;
    }

    // Open the connection 
    HINTERNET hConnect = InternetOpenUrl(hInternet, "https://www.google.com", NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hConnect) {
        std::cerr << "InternetOpenUrl failed: " << GetLastError() << std::endl;
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
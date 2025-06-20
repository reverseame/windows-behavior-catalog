// Compiled with: cl /EHsc .\winhttp_send_recv.cpp winhttp.lib
// Establish HTTP connection with Winhttp library https://learn.microsoft.com/en-us/windows/win32/api/winhttp/
// Adapted from https://github.com/MicrosoftDocs/win32/blob/docs/desktop-src/WinHttp/winhttp-sessions-overview.md
#include <windows.h>
#include <winhttp.h>
#include <iostream>

int main()
{
    // Initialize WinHTTP
    HINTERNET hSession = WinHttpOpen(L"WinHTTP Example/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (hSession == NULL)
    {
        printf("Failed to initialize WinHTTP: %d", GetLastError());
        return 1;
    }

    // Connect to the server
    LPCWSTR serverName = L"www.microsoft.com";
    INTERNET_PORT serverPort = INTERNET_DEFAULT_HTTPS_PORT;
    DWORD flags = 0;

    HINTERNET hConnect = WinHttpConnect(hSession, serverName, serverPort, flags);
    if (hConnect == NULL)
    {
        printf("Failed to connect to the server.%d", GetLastError());
        WinHttpCloseHandle(hSession);
        return 1;
    }

    // Open a connection
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", NULL, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE );
    if (hRequest == NULL)
    {
        printf("Failed to open connection: %d", GetLastError());
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 1;
    }

    // Send the request
    if (!WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0))
    {
        printf("Failed to send request: %d", GetLastError());
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 1;
    }

    // Wait for the response
    if (!WinHttpReceiveResponse(hRequest, NULL))
    {
        printf("Failed to receive response: %d", GetLastError());
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 1;
    }

    // Read and print the response
    DWORD bytesRead;
    LPSTR buffer[4096];
    while (WinHttpReadData(hRequest, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0)
    {
        std::cout.write(reinterpret_cast<char*>(buffer), bytesRead);
    }

    // Clean up
    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    return 0;
}
// Compiled with: cl /EHsc .\OpenThread.cpp
// Open thread using OpenThread 
#include <Windows.h>
#include <iostream>

int main() {
    DWORD threadId = 1337; // Fictional Thread ID

    HANDLE hThread = OpenThread(THREAD_QUERY_INFORMATION, FALSE, threadId);
    if (hThread) {
        std::cout << "Thread handle opened successfully." << std::endl;
        // Use the hThread handle here

        // Remember to close the thread handle when you're done
        CloseHandle(hThread);
    } else {
        std::cerr << "Failed to open thread handle." << std::endl;
    }

    return 0;
}

// Compiled with: cl /EHsc .\DeleteFileTransacted.cpp KtmW32.lib
// Delete file with DeleteFileTransacted
#include <windows.h>
#include <iostream>
#include <ktmw32.h>

int main() {
    // Define the path to the file you want to delete
    LPCSTR filePath = "C:\\Users\\Default\\NTUSER.DAT"; // Replace with the actual file path

    // Initialize the transaction
    HANDLE hTransaction = CreateTransaction(NULL, 0, 0, 0, 0, 0, NULL);
    if (hTransaction == NULL) {
        std::cerr << "Failed to create transaction" << GetLastError() << std::endl;
        return 1;
    }

    // Attempt to delete the file within the transaction
    if (!DeleteFileTransacted(filePath, hTransaction)) {
        std::cerr << "Failed to delete file within transaction" << GetLastError() << std::endl;

        // Rollback the transaction on failure
        // if (!RollbackTransaction(hTransaction)) {
        //     std::cerr << "Failed to rollback transaction" << std::endl;
        // }

        CloseHandle(hTransaction);
        return 1;
    }

    // Commit the transaction to finalize the deletion
    if (!CommitTransaction(hTransaction)) {
        std::cerr << "Failed to commit transaction" << GetLastError() << std::endl;
        CloseHandle(hTransaction);
        return 1;
    }

    // Close the transaction handle
    CloseHandle(hTransaction);

    //std::cout << "File deleted successfully." << GetLastError() << std::endl;

    return 0;
}

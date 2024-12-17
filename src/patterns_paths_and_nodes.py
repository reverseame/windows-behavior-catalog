included_single_nodes = {
    "['NtCreateFile']":"",
    "['DeleteFileA']":"",
    "['MoveFileWithProgressTransacted']":"",
    "['CreateThread']":"",
    "['NtOpenProcess']":"",
    "['NtResumeThread']":"",
    "['RegDeleteKeyA']":"",
    "['RegDeleteKeyExA']":"",
    "['LocalAlloc']":"",
    "['NtAllocateVirtualMemory']":"",
    "['NtQueryFullAttributesFile']":"",
    "['NtOpenFile']":"",
    "['FindFirstFileEx']":"",
    "['NtQueryAttributesFile']":"",
    "['PathAddExtension']":"",
    "['PathCombine']":"",
    "['PathCchRenameExtension']":"",
    "['PathCchCombineEx']":"",
    "['PathRenameExtension']":"",
    "['PathAllocCombine']":"",
    "['CopyFile2']":"",
    "['CopyFileEx']":"",
    "['CopyFile']":"",
    "['DeleteFile']":"",
    "['DeleteFileTransacted']":"",
    "['GetEnvironmentStrings']":"",
    "['RegDeleteKeyEx']":"",
    "['RegDeleteKey']":"",
    "['RegOpenKeyEx']":"",
    "['RegCreateKeyEx']":"",
    "['GetEnvironmentVariable']":"",
    "['CreateRemoteThread']":"",
    "['Thread32Next']":"",
    "['NtOpenThread']":"",
    "['ShellExecuteEx']":"",
    "['Process32Next']":"",
    "['SetEnvironmentVariable']":"",
    "['ExpandEnvironmentStrings']":"",
    "['BCryptExportKey']":"",
    "['BCryptGenerateKeyPair']":"",
    "['CryptExportKey']":"",
    "['BCryptImportKeyPair']":"",
    "['CryptImportPublicKeyInfo']":"",
    "['BCryptGenerateKeyPair']":"",
    "['CryptImportPublicKeyInfoEx']":"",
    "['CryptImportKey']":"",
    "['BCryptImportKey']":"",
    "['BCryptEncrypt']":"",
    "['CryptCreateHash']":"",
    "['CryptHashData']":"",
    "['CryptDestroyHash']":"",
    "['BCryptDecrypt']":"",
    "['CryptDecrypt']":"",
    "['CryptExportPublicKeyInfoEx']":"",
}

manually_included_patterns = {
    "C0001.006":[
        ['WSAStartup', 'socket', 'connect', 'recv'],
    ],
    "C0001.007":[
        ['send'],
    ],
    "C0070X.002X":[
        ['EnumProcesses'],
        ['K32EnumProcesses']
    ],
    "C0027.002X":[
        ['BCryptEncrypt'],
    ],
    "C0027.001X":[
        ['CryptEncrypt'],
    ],
    "C0028.002X":[
        ['CryptImportKey'],
    ],
    # "C0028.003X":[
    #     ['CryptImportPublicKeyInfo'],
    # ],
    "C0028.004X":[
        ['CryptImportPublicKeyInfoEx'],
    ],
    "C0028.005X":[
        ['BCryptImportKeyPair'],
    ],
    # "C0028.006X":[
    #     ['BCryptImportKey'],
    # ],
    "C0028.007X":[
        ['CryptDecodeObjectEx'],
    ],
    # "C0028.008X":[
    #     ['CryptExportKey'],
    # ],
    "C0029.001X":[
        ['CryptCreateHash'],
    ],
    "C0029.002X":[
        ['CryptHashData'],
    ],
    # "C0029.003X":[
    #     ['CryptDestroyHash'],
    # ],
    "C0031.001X":[
        ['CryptDecrypt'],
    ],
    "C0031.002X":[
        ['BCryptDecrypt'],
    ],
    "C0028.001X":[
        ['CryptAcquireContext', 'CryptGenRandom'], # Deprecated, but still in use https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptgenrandom
        ['CryptGenKey'],
        ['CryptGenRandom']
    ],
    "C0036.006":[
        ['RegOpenKeyEx', 'RegQueryValueEx', 'RegCloseKey'],
    ],
    "C0036.001":[
        ['RegOpenKeyEx', 'RegSetValueEx', 'RegCloseKey'],
    ],
    "C0043.001X":[
        ['NtOpenMutant'],
    ],
    "C0042.001X":[
        ['NtCreateMutant'],
    ],
    "C0042.002X":[
        ['NtCreateMutant'],
    ],
    "C0047.001X":[
        ['NtDeleteFile'],
    ],
    "C0028.010X":[
        ['CryptExportPublicKeyInfo']
    ],
    "C0028.011X":[
        ['CryptExportPublicKeyInfoEx']
    ],
}

# Methods that comprise other methods hence they must be disjointed.
# For instance, to read a file you must first open it. That is:
# ReadFile_behavior = OpenFile_pattern + ReadFile_pattern. In order to get the true
# and standalone ReadFile_behavior one must subtract OpenFile thus resulting in:
# ReadFile_behavior = OpenFile_pattern + ReadFile_pattern - OpenFile_pattern -> 
# -> ReadFile_behavior = ReadFile_pattern
compound_behaviors = {
    "[C0051.001X] ReadFile":[
        "[C0016X.003X] OpenFile"
    ],
    "[C0052.001X] WriteFile":[
        "[C0016X.001X] CreateFile"
    ],
    "[C0052.002X] WriteFileEx":[
        "[C0016X.001X] CreateFile"
    ],
    "[C0049.004X] GetFileInformationByHandle":[
        "[C0016X.001X] CreateFile"
    ],
    "[C0049.008X] FindNextFile":[
        "[C0049.005X] FindFirstFile"
    ],
    "[C0001.006] Receive Data":[
        "[C0001.007] Send Data"
    ],
    "[C0054.001X] ResumeThread":[
        "[C0038.001X] CreateThread"
    ],
    "[C0055] Suspend Thread":[
        "[C0038.001X] CreateThread"
    ],
    "[C0038.002X] CreateRemoteThread":[
        "[C0017.003X] CreateProcess",
        "[C0065.001X] OpenProcess"
    ],
    "[C0036.006] Query Registry Value":[
        "[C0036.003] Open Registry Key"
    ],
    "[C0036.005] Query Registry Key":[
        "[C0036.003] Open Registry Key"
    ],
    "[C0036.001] Create or Set Registry Value":[
        "[C0036.003] Open Registry Key"
    ],
    "[C0036.007] Delete Registry Value":[
        "[C0036.003] Open Registry Key"
    ],
    "[C0028.010X] CryptExportPublicKeyInfo":[
        "[C0028.001X] CryptGenKey"
    ],
    "[C0028.008X] CryptExportKey":[
        "[C0028.001X] CryptGenKey"
    ],
    "[C0028.011X] CryptExportPublicKeyInfoEx":[
        "[C0028.001X] CryptGenKey",
        "[C0028.005X] BCryptImportKeyPair"
    ],
    "[C0028.003X] CryptImportPublicKeyInfo":[
        "[C0028.001X] CryptGenKey",
        "[C0028.008X] CryptExportKey",
        "[C0028.005X] BCryptImportKeyPair"
    ],
    "[C0028.004X] CryptImportPublicKeyInfoEx":[
        "[C0028.005X] BCryptImportKeyPair",
        "[C0028.001X] CryptGenKey",
        "[C0028.008X] CryptExportKey"
    ],
    "[C0028.002X] CryptImportKey":[
        "[C0028.001X] CryptGenKey",
        "[C0028.008X] CryptExportKey"
    ],
    "[C0029.002X] CryptHashData":[
        "[C0029.001X] CryptCreateHash",
        "[C0029.003X] CryptDestroyHash"
    ],
    "[C0029.003X] CryptDestroyHash":[
        "[C0029.001X] CryptCreateHash",
        "[C0029.002X] CryptHashData"
    ],
    "[C0029.001X] CryptCreateHash":[
        "[C0029.003X] CryptDestroyHash"
    ]
}

# Paths to be discarded (usually because they have no operational meaning but 
# result from our generation mechanism).
paths_to_filter = {
    "['GetCommandLine', 'GetCommandLine']":"",
    "['GetCommandLine', 'GetCommandLine', 'NtFreeVirtualMemory']":"",
    #"['WSAStartup', 'socket', 'setsockopt']":"",
    "['WSAStartup', 'closesocket']":"",
    "['WSAStartup', 'shutdown', 'closesocket']":"",
    "['NtCreateSection', 'NtMapViewOfSection']":"",
    "['NtQueryInformationThread', 'NtOpenSection']":"",
    "['NtWaitForSingleObject']":"",
    "['NtOpenKey']":"",
    "['NtQueryInformationThread', 'NtTerminateThread']":"",
    "['CryptAcquireContext', 'CryptDestroyKey']":"", 
    "['CryptAcquireContext'":"",
    "['CryptDestroyKey']":"",
}
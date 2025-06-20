# Windows Behavior Catalog (WBC)
Collection of common Windows behaviors and their corresponding implementation. The source code is written in C++ and has been tested with `cl` (`Microsoft (R) C/C++ Optimizing Compiler Version 19.34.31935 for x86`). **The files have been compiled and tested under Windows 10 Pro Version 10.0.19044 Build 19044**.

The vast majority of the behaviors here defined are based on the [Malware Behavior Catalog (MBC)](https://github.com/MBCProject/mbc-markdown)'s micro-behaviors.

Feel free to contribute to the WBC's corpus by opening PRs and/or issues.

# Contents

- [`/src`](./src) contains the tool to generate the catalog itself based on the contents of this repository.
- [`/utils`](./utils) contains several utilities.
- [`catalog.json`](./catalog.json) and [`catalog.txt`](./catalog.txt) contain the WBC in JSON and plain text format, respectively.
- [`discarded.json`](./discarded.json) and [`discarded.txt`](./discarded.txt) contain the WBC discarded patterns in JSON and plain text format, respectively. This is just some additional info.
- Each **[OC000\*]** folder contain the sources, exes, reports and graphviz files the catalog is originated from.

## Naming
In order to understand what a micro-objective, micro-behavior, or method is, please refer to the [MBC](https://github.com/MBCProject/mbc-markdown). The contents of this catalog uses the following naming convention:
 
- **OC####**: Micro-Objective 
- **C####**: Micro-Behavior
- **C####.###**: Method
	- **X** at the end: eXpanded by us (with respect to the MBC)
		- Behaviors we consider relevant but are not included in the MBC as of the moment of this writing. We will eventually pull request the MBC to include them, if they deem it. 
- **P####**: Individual behavioral pattern
	- **H** at the end: Manually added pattern
		- Behavioral patterns both single or multiple nodes long we manually added to a specific method. This situation occurs when there is a behavior unequivocally identified by any pattern that does not arise as a result of our behavioral pattern generation algorithm (from the Category Graphs).

## Structure
Within each category (or micro-objective) you will find the all the associated behaviors and their corresponding source code files, as well as the executables and the reports generated from CAPEv2. For each behavior, the source code file has (or pretends to) a self-explanatory name. Each category has the following structure: 

- [ID] Micro-objective
	- [ID] Micro-behavior
		- [ID] Method
			- **src**: Folder containing the source code files.
			- **exe**: Folder containing the executable files.
			- **reports**: Folder containing the report files, as generated by CAPEv2 (JSON formatted).
			- **gv**: Folder containing the _graphviz_ files, used to perform pattern matching and other analysis techniques.

## Source Code
This repository contains a mix of original work by the WBC authors and code adapted or inspired by other sources. When using content from others, we make sure to credit the original creators.

Each behavior implementation is designed to be a straightforward, working example of that behavior. Keep it simple, clear, and focused!

## Compilation

Files have been compiled with `cl`, the same compiler Visual Studio uses, but from the command line: [Use the Microsoft C++ toolset from the command line](https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170). You can find more information and instructions here: [Walkthrough: Compiling a Native C++ Program on the Command Line](https://learn.microsoft.com/en-us/cpp/build/walkthrough-compiling-a-native-cpp-program-on-the-command-line?view=msvc-170).

The specific command used to compile each `.cpp` file is specified within the header of the file itself.

## How to cite
TBD

# How to update
The typical workflow for adding new content to the Windows Behavior Catalog is as follows:

1. Create the corresponding folder for the method.
2. Place in `\src` the (ideally working) C/C++ source code.
3. Compile the source code and place the resulting executable in the `\exe` folder.
4. Submit the executable file to CAPEv2 for analysis. **ATTENTION!** We are using [our modified version of capemon](https://github.com/reverseame/capemon).
5. Download the generated `report.json` file(s) and place them in the `\reports` folder.
6. Transform the analysis/es into their corresponding transition matrices and callgraphs (using our tool TBA). Place the resulting `.gv` files into their corresponding `\gv` folder.
	1. In the [utils](./utils) folder there are some tools to help automatically move .gv and report files.
7. Update [winapi_categories_json](https://github.com/reverseame/winapi-categories) if needed.
8. Update the catalog creation [script](./src/create_behavior_catalog.py) if needed.
9. Use the [script](./src/create_behavior_catalog.py) to regenerate the .json and .txt catalogs (the WBC itself).

# Authors

[Razvan Raducu](https://www.youtube.com/@RazviOverflow)  
[Ricardo J. Rodríguez](https://webdiis.unizar.es/~ricardo/)  
[Pedro Álvarez](https://i3a.unizar.es/es/investigadores/pedro-javier-alvarez-perez-aradros)

# WBC Composition
The WBC comprises: *(Information generated with [statistics.py](./utils/statistics.py))*
- Total Micro-objectives: 6
- Total Micro-behaviors: 30
- Total Methods: 87
- Total Patterns: 329
- Minimum Pattern Length: 1
- Maximum Pattern Length: 7

*Information subject to change. Updated on 2024.17.12*

```
$ tree -L 5 -P "*.exe"
.
├── [OC0001] Filesystem
│   ├── [C0015] Alter Filename Extension
│   │   ├── [C0015.001X] PathRenameExtension
│   │   │   ├── exe
│   │   │   │   └── PathRenameExtension.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0015.002X] PathCombine
│   │   │   ├── exe
│   │   │   │   └── PathCombine.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0015.003X] PathCchCombine
│   │   │   ├── exe
│   │   │   │   └── PathCchCombine.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0015.004X] PathCchCombineEx
│   │   │   ├── exe
│   │   │   │   └── PathCchCombineEx.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0015.005X] PathAllocCombine
│   │   │   ├── exe
│   │   │   │   └── PathAllocCombine.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0015.006X] PathAddExtension
│   │   │   ├── exe
│   │   │   │   └── PathAddExtension.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   └── [C0015.007X] PathCchRenameExtension
│   │       ├── exe
│   │       │   └── PathCchRenameExtension.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0016X] Create or Open file
│   │   ├── [C0016X.001X] CreateFile
│   │   │   ├── exe
│   │   │   │   └── CreateFile.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0016X.002X] CreateFile2
│   │   │   ├── exe
│   │   │   │   └── CreateFile2.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   └── [C0016X.003X] OpenFile
│   │       ├── exe
│   │       │   └── OpenFile.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0045] Copy File
│   │   ├── [C0045.001X] CopyFile
│   │   │   ├── exe
│   │   │   │   └── CopyFile.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0045.002X] CopyFileEx
│   │   │   ├── exe
│   │   │   │   └── CopyFileEx.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   └── [C0045.003X] CopyFile2
│   │       ├── exe
│   │       │   └── CopyFile2.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0046] Create Directory
│   │   ├── [C0046.001X] CreateDirectory
│   │   │   ├── exe
│   │   │   │   └── CreateDirectory.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0046.002X] CreateDirectoryEx
│   │   │   ├── exe
│   │   │   │   └── CreateDirectoryEx.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0046.003X] SHCreateDirectory
│   │   │   ├── exe
│   │   │   │   └── SHCreateDirectory.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0046.004X] SHCreateDirectoryEx
│   │   │   ├── exe
│   │   │   │   └── SHCreateDirectoryEx.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   └── [C0046.005X] CreateFileTransacted
│   │       ├── exe
│   │       │   └── CreateFileTransacted.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0047] Delete File
│   │   ├── [C0047.001X] DeleteFile
│   │   │   ├── exe
│   │   │   │   └── DeleteFile.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   └── [C0047.002X] DeleteFileTransacted
│   │       ├── exe
│   │       │   └── DeleteFileTransacted.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0049] Get File Attributes
│   │   ├── [C0049.001X] GetFileAttributes
│   │   │   ├── exe
│   │   │   │   └── GetFileAttributes.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0049.002X] GetFileAttributesEx
│   │   │   ├── exe
│   │   │   │   └── GetFileAttributesEx.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0049.003X] GetFileAttributesTransacted
│   │   │   ├── exe
│   │   │   │   └── GetFileAttributesTransacted.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0049.004X] GetFileInformationByHandle
│   │   │   ├── exe
│   │   │   │   └── GetFileInformationByHandle.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0049.005X] FindFirstFile
│   │   │   ├── exe
│   │   │   │   └── FindFirstFile.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0049.006X] FindFirstFileEx
│   │   │   ├── exe
│   │   │   │   └── FindFirstFileEx.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0049.007X] FindFirstFileTransacted
│   │   │   ├── exe
│   │   │   │   └── FindFirstFileTransacted.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   └── [C0049.008X] FindNextFile
│   │       ├── exe
│   │       │   └── FindNextFile.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0051] Read File
│   │   └── [C0051.001X] ReadFile
│   │       ├── exe
│   │       │   ├── ReadFile_1.exe
│   │       │   └── ReadFile_2.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0052] Write File
│   │   ├── [C0052.001X] WriteFile
│   │   │   ├── exe
│   │   │   │   └── WriteFile.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   └── [C0052.002X] WriteFileEx
│   │       ├── exe
│   │       │   └── WriteFileEx.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0063] Move File
│   │   ├── [C0063.001X] MoveFile
│   │   │   ├── exe
│   │   │   │   └── MoveFile.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   └── [C0063.002X] MoveFileEx
│   │       ├── exe
│   │       │   └── MoveFileEx.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   └── TODO
│       └── src
├── [OC0002] Memory
│   ├── [C0007] Allocate Memory
│   │   ├── [C0007.001X] VirtualAlloc
│   │   │   ├── exe
│   │   │   │   └── VirtualAlloc.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0007.003X] GlobalAlloc
│   │   │   ├── exe
│   │   │   │   └── GlobalAlloc.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0007.004X] LocalAlloc
│   │   │   ├── exe
│   │   │   │   └── LocalAlloc.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0007.005X] malloc
│   │   │   ├── exe
│   │   │   │   └── malloc.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   └── TODO
│   │       └── [C0007.002X] HeapAlloc
│   │           ├── exe
│   │           └── src
│   └── [C0008] Change Memory Protection
│       ├── [C0008.001X] VirtualProtect
│       │   ├── exe
│       │   │   └── VirtualProtect.exe
│       │   ├── gv
│       │   ├── reports
│       │   └── src
│       └── [C0008.002X] VirtualProtectEx
│           ├── exe
│           │   └── VirtualProtectEx.exe
│           ├── gv
│           ├── reports
│           └── src
├── [OC0003] Process
│   ├── [C0017] Create Process
│   │   ├── [C0017.001X] ShellExecute
│   │   │   ├── exe
│   │   │   │   └── ShellExecute.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0017.002X] ShellExecuteEx
│   │   │   ├── exe
│   │   │   │   └── ShellExecuteEx.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0017.003X] CreateProcess
│   │   │   ├── exe
│   │   │   │   └── CreateProcess.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   └── [C0017.004X] WinExec
│   │       ├── exe
│   │       │   └── WinExec.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0038] Create Thread
│   │   ├── [C0038.001X] CreateThread
│   │   │   ├── exe
│   │   │   │   └── CreateThread.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   └── [C0038.002X] CreateRemoteThread
│   │       ├── exe
│   │       │   └── CreateRemoteThread.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0042] Create Mutex
│   │   ├── [C0042.001X] CreateMutex
│   │   │   ├── exe
│   │   │   │   └── CreateMutex.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   └── [C0042.002X] CreateMutexEx
│   │       ├── exe
│   │       │   └── CreateMutexEx.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0043] Check Mutex
│   │   └── [C0043.001X] OpenMutex
│   │       ├── exe
│   │       │   └── OpenMutex.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0054] Resume Thread
│   │   └── [C0054.001X] ResumeThread
│   │       ├── exe
│   │       │   └── ResumeThread.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0055] Suspend Thread
│   │   └── [C0055.001X] SuspendThread
│   │       ├── exe
│   │       │   └── SuspendThread.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0064] Enumerate Threads
│   │   └── [C0064.001X] Thread32First_Thread32Next
│   │       ├── exe
│   │       │   └── enumerate_threads.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0065] Open Process
│   │   └── [C0065.001X] OpenProcess
│   │       ├── exe
│   │       │   └── OpenProcess.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0066] Open Thread
│   │   └── [C0066.001X] OpenThread
│   │       ├── exe
│   │       │   └── OpenThread.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0070X] Process Enumeration
│   │   ├── [C0070X.001X] CreateSnapshot_Process32Next
│   │   │   ├── exe
│   │   │   │   └── CreateSnapshot_Iterate.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   └── [C0070X.002X] EnumProcesses
│   │       ├── exe
│   │       │   └── EnumProcesses.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   └── TODO
│       └── src
├── [OC0005] Cryptography
│   ├── [C0027] Encrypt Data
│   │   ├── [C0027.001X] CryptEncrypt
│   │   │   ├── exe
│   │   │   │   └── CryptEncrypt.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   └── [C0027.002X] BCryptEncrypt
│   │       ├── exe
│   │       │   └── BCryptEncrypt.exe
│   │       └── src
│   ├── [C0028] Encryption Key
│   │   ├── [C0028.001X] CryptGenKey
│   │   │   ├── exe
│   │   │   │   └── CryptGenKey.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   ├── [C0028.002X] CryptImportKey
│   │   │   ├── exe
│   │   │   │   └── CryptImportKey.exe
│   │   │   └── src
│   │   ├── [C0028.003X] CryptImportPublicKeyInfo
│   │   │   ├── exe
│   │   │   │   └── CryptImportPublicKeyInfo.exe
│   │   │   └── src
│   │   ├── [C0028.004X] CryptImportPublicKeyInfoEx
│   │   │   ├── exe
│   │   │   │   └── CryptImportPublicKeyInfoEx.exe
│   │   │   └── src
│   │   ├── [C0028.005X] BCryptImportKeyPair
│   │   │   ├── exe
│   │   │   │   └── BCryptImportKeyPair.exe
│   │   │   └── src
│   │   ├── [C0028.006X] BCryptImportKey
│   │   │   ├── exe
│   │   │   │   └── BCryptImportKey.exe
│   │   │   └── src
│   │   ├── [C0028.008X] CryptExportKey
│   │   │   ├── exe
│   │   │   │   └── CryptExportKey.exe
│   │   │   └── src
│   │   ├── [C0028.009X] BCryptExportKey
│   │   │   ├── exe
│   │   │   │   └── BCryptExportKey.exe
│   │   │   └── src
│   │   ├── [C0028.010X] CryptExportPublicKeyInfo
│   │   │   ├── exe
│   │   │   │   └── CryptExportPublicKeyInfo.exe
│   │   │   └── src
│   │   ├── [C0028.011X] CryptExportPublicKeyInfoEx
│   │   │   ├── exe
│   │   │   │   └── CryptExportPublicKeyInfoEx.exe
│   │   │   └── src
│   │   └── [C0028.012X] BCryptGenerateKeyPair
│   │       ├── exe
│   │       │   └── BCryptGenerateKeyPair.exe
│   │       └── src
│   ├── [C0029] Cryptographic Hash
│   │   ├── [C0029.001X] CryptCreateHash
│   │   │   ├── exe
│   │   │   │   └── CryptCreateHash.exe
│   │   │   └── src
│   │   ├── [C0029.002X] CryptHashData
│   │   │   ├── exe
│   │   │   │   └── CryptHashData.exe
│   │   │   └── src
│   │   └── [C0029.003X] CryptDestroyHash
│   │       ├── exe
│   │       │   └── CryptDestroyHash.exe
│   │       └── src
│   ├── [C0031] Decrypt Data
│   │   ├── [C0031.001X] CryptDecrypt
│   │   │   ├── exe
│   │   │   │   └── CryptDecrypt.exe
│   │   │   └── src
│   │   └── [C0031.002X] BCryptDecrypt
│   │       ├── exe
│   │       │   └── BCryptDecrypt.exe
│   │       └── src
│   └── TODO
│       ├── [C0028.007X] CryptDecodeObjectEx
│       └── CryptDecodeObject
├── [OC0006] Communication
│   ├── [C0001] Socket Communication
│   │   ├── [C0001.006] Receive Data
│   │   │   ├── exe
│   │   │   │   └── socket_recv.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   └── [C0001.007] Send Data
│   │       ├── exe
│   │       │   └── socket_send.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0002] HTTP Communication
│   │   └── [C0002.008] WinHTTP
│   │       ├── exe
│   │       │   └── winhttp_send_recv.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   ├── [C0005] WinINet Communication
│   │   ├── [C0005.001] InternetConnect
│   │   │   ├── exe
│   │   │   │   └── InternetConnect.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   └── [C0005.003] InternetOpenURL
│   │       ├── exe
│   │       │   └── InternetOpenUrl.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   └── TODO
├── [OC0008] Operating System
│   ├── [C0034] Environment Variable
│   │   ├── [C0034.001] Set Environment Variable
│   │   │   ├── exe
│   │   │   │   └── SetEnvironmentVariable.exe
│   │   │   ├── gv
│   │   │   ├── reports
│   │   │   └── src
│   │   └── [C0034.002] Check Environment Variable
│   │       ├── exe
│   │       │   ├── ExpandEnvironmentStrings.exe
│   │       │   ├── GetEnvironmentStrings.exe
│   │       │   └── GetEnvironmentVariable.exe
│   │       ├── gv
│   │       ├── reports
│   │       └── src
│   └── [C0036] Registry
│       ├── [C0036.001] Create or Set Registry Value
│       │   ├── exe
│       │   │   ├── RegSetKeyValue.exe
│       │   │   ├── RegSetValue.exe
│       │   │   └── RegSetValueEx.exe
│       │   ├── gv
│       │   ├── reports
│       │   └── src
│       ├── [C0036.002] Delete Registry Key
│       │   ├── exe
│       │   │   ├── RegDeleteKey.exe
│       │   │   └── RegDeleteKeyEx.exe
│       │   ├── gv
│       │   ├── reports
│       │   └── src
│       ├── [C0036.003] Open Registry Key
│       │   ├── exe
│       │   │   ├── RegOpenCurrentUser.exe
│       │   │   ├── RegOpenKey.exe
│       │   │   └── RegOpenKeyEx.exe
│       │   ├── gv
│       │   ├── reports
│       │   └── src
│       ├── [C0036.004] Create Registry Key
│       │   ├── exe
│       │   │   ├── RegCreateKey.exe
│       │   │   └── RegCreateKeyEx.exe
│       │   ├── gv
│       │   ├── reports
│       │   └── src
│       ├── [C0036.005] Query Registry Key
│       │   ├── exe
│       │   │   └── RegQueryInfoKey.exe
│       │   ├── gv
│       │   ├── reports
│       │   └── src
│       ├── [C0036.006] Query Registry Value
│       │   ├── exe
│       │   │   ├── RegEnumValue.exe
│       │   │   ├── RegGetValue.exe
│       │   │   └── RegQueryValueEx.exe
│       │   ├── gv
│       │   ├── reports
│       │   └── src
│       ├── [C0036.007] Delete Registry Value
│       │   ├── exe
│       │   │   ├── RegDeleteKeyValue.exe
│       │   │   └── RegDeleteValue.exe
│       │   ├── gv
│       │   ├── reports
│       │   └── src
│       └── TODO
│           ├── exe
│           │   └── RegQueryValue.exe
│           ├── gv
│           ├── reports
│           └── src
```

## TODO
- Code for:
	- NtDeleteFile
	- NtOpenFile
	- getaddrinfo
	- More code with HttpOpenRequest and HttpSendRequest (maybe consider them single-node patterns)
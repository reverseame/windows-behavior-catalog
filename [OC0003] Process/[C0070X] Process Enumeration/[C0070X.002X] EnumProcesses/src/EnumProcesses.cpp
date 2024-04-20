// Compiled with: cl /EHsc .\EnumPcoresses.cpp
// Process iteration with EnumPcoresses
#include <stdio.h>
#include <windows.h>
#include <psapi.h>

int main() {
  // Array to store process IDs
  DWORD process_ids[1024];
  DWORD cbNeeded;

  // Get the PIDs of all processes (might need a larger array for many processes)
  if (!EnumProcesses(process_ids, sizeof(process_ids), &cbNeeded)) {
    printf("Error enumerating processes: %d\n", GetLastError());
    return 1;
  }

  // Calculate the number of processes retrieved
  int num_processes = cbNeeded / sizeof(DWORD);

  // Print the PIDs of all processes
  printf("Process IDs:\n");
  for (int i = 0; i < num_processes; i++) {
    printf("%d\n", process_ids[i]);
  }

  return 0;
}
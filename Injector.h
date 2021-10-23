#include <Windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string.h>

const char* dllPath = "C:\\ProgramData\\Osiris.dll";
const char* processName = "csgo.exe";



bool TrustedModeBypass(const HANDLE bypassHandle)
{
    HMODULE getDLLAddress = LoadLibrary("ntdll");

    if (getDLLAddress)
    {
        void* getNtOpenFileAddress = GetProcAddress(getDLLAddress, "NtOpenFile");

        if (getNtOpenFileAddress)
        {
            char originalNtOpenFileBytes[5]; 
            memcpy(originalNtOpenFileBytes, getNtOpenFileAddress, 5); 
            bool bypassMemoryWrite = WriteProcessMemory(bypassHandle, getNtOpenFileAddress, originalNtOpenFileBytes, 5, 0);

            if (!bypassMemoryWrite)
            {
                std::cout << "Failed to bypass Trusted Mode " << GetLastError() << std::endl;
                return false;
            }
            else
            {
                std::cout << "Trusted Mode Bypassed..." << std::endl;
                return true;
            }
        }
    }
}


void InjectDLL()
{
    DWORD processID = 0;
    PROCESSENTRY32 processesArray{ 0 };
    processesArray.dwSize = sizeof(processesArray); 
    HANDLE findProcessID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
    BOOL processEnum = Process32First(findProcessID, &processesArray);
    while (processEnum)
    {
        if (strcmp(processName, processesArray.szExeFile) == 0)
        {
            processID = processesArray.th32ProcessID;
            break;
        }
        processEnum = Process32Next(findProcessID, &processesArray);
    }
    CloseHandle(findProcessID);
    if (processID == 0)
    {
        std::cout << "Process ID could not be found - Error code: " << GetLastError() << std::endl;
        exit(1);
    }
    else
    {
        std::cout << "The process ID of target process is: " << (processID) << std::endl;
    }
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
    if (processHandle == NULL)
    {
        std::cout << "Failed to gain a handle to the process - Error code: " << GetLastError() << std::endl;
        exit(1);
    }
    else
    {
        std::cout << "Handle to target process acquired..." << std::endl;
        TrustedModeBypass(processHandle);
    }
    void* memoryAddress = VirtualAllocEx(processHandle, NULL, strlen(dllPath) + 1, MEM_COMMIT, PAGE_READWRITE);
    if (!memoryAddress)
    {
        std::cout << "Memory space could not be allocated - Error code: " << GetLastError() << std::endl;
        exit(1);
    }
    else
    {
        std::cout << "Memory space allocated..." << std::endl;
        std::cout << "Memory address is: " << memoryAddress << std::endl;
    }
    bool memoryWrite = WriteProcessMemory(processHandle, memoryAddress, dllPath, strlen(dllPath) + 1, NULL);
    if (!memoryWrite)
    {
        std::cout << "Memory space could not be written to - Error code: " << GetLastError() << std::endl;
        exit(1);
    }
    else
    {
        std::cout << "Memory space written to..." << std::endl;
    }
    HANDLE memoryWriteHandle = CreateRemoteThread(processHandle, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, memoryAddress, NULL, NULL);
    if (!memoryWriteHandle)
    {
        std::cout << "DLL could not be injected - Error code: " << GetLastError() << std::endl;
        exit(1);
    }
    CloseHandle(memoryWriteHandle);
    CloseHandle(processHandle);
    exit(1);
}
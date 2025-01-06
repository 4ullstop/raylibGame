#include <windows.h>
#include "memory_setup.h"
#include <stdio.h>

void* SetupSharedMemoryAndCreateProcess(STARTUPINFO* si, PROCESS_INFORMATION* pi, HANDLE* hMapFile, size_t valueSize, HANDLE* eventHandle)
{

    printf("\n");
    printf("\n");
    printf("\n");
    printf("opening sceneb.exe\n");

    void* sharedValue = SetupSharedMemory(hMapFile, valueSize);

    printf("Zeroing memory\n");
    ZeroMemory(si, sizeof(STARTUPINFO));
    si->cb = sizeof(STARTUPINFO);

    if (CreateProcess(
	    NULL, //Executable name if there is an application to run
	    "sceneb.exe b", //commandline string
	    NULL, //Security attributes
	    NULL, //Thread security attributes
	    FALSE, //bInheritHandles, if the child should inherit handles
	    0, //Creation flags
	    NULL, //a pointer to the environment block of new process
	    NULL, //Current directory startup process
	    si, //startup info
	    pi)) //process info
    {
	printf("Parent process: child process forked with PID %ld\n", pi->dwProcessId);
	printf("\n");
	printf("\n");
	printf("\n");
	*eventHandle = CreateEventW(NULL, FALSE, FALSE, L"sceneb");
	return sharedValue;
	//WaitForSingleObject(pi->hProcess, INFINITE);
    }
    else
    {
	printf("Failed to fork process");
	printf("\n");
	printf("\n");
	printf("\n");
	return NULL;
    }
}

void* SetupSharedMemory(HANDLE* hMapFile, size_t valueSize)
{
    *hMapFile = CreateFileMapping(
	INVALID_HANDLE_VALUE, //hFile a handle to a file or device
	NULL, //lpAttributes: determines if the handle can be inherited by a child process
        PAGE_READWRITE, //flProtext: the protection for the desired file
	0, //MaximumSizeHigh
	valueSize, //MaximumSizeLow, this will be your struct when you have one made eventually
	"sceneb" //lpName: name of the file object mapped
        );
    
    if (*hMapFile == NULL)
    {
	printf("ERROR, HMAPFILE NULL\n");
	return NULL;
    }

    printf("creating sharedValue\n");
    void* sharedValue = MapViewOfFile(
	*hMapFile, //handle to the memory allocated
	FILE_MAP_ALL_ACCESS, //dwDesiredAccess: the type of access desired r/rw/rwx
	0, //file offset high
	0, //file offset low
	valueSize); //number of bytes to map into the calling process's address
    if (sharedValue == NULL)
    {
	printf("ERROR SHAREDVALUE IS NULL\n");
	CloseHandle(hMapFile);
	return NULL;
    }
    return sharedValue;
}

void* FindWindowByTitle(const char* windowTitle)
{
    HWND* hwnd = malloc(sizeof(HWND));
    *hwnd = FindWindow(NULL, windowTitle);
    return hwnd;
}

bool SwitchToWindow(const char* windowTitle)
{
    HWND hwnd = *(HWND*)(FindWindowByTitle(windowTitle));

    if (hwnd == NULL)
    {
	return false;
    }

    return SetForegroundWindow(hwnd);
}
    
void* AttachChildProcessToMemory(HANDLE* hMapFileB, size_t valueSize)
{
    printf("\n");
    printf("\n");
    printf("\n");
    

    printf("opening file location\n");
    
    *hMapFileB = OpenFileMapping(
	FILE_MAP_ALL_ACCESS,
	TRUE,
	"sceneb");
    
    if (*hMapFileB == NULL)
    {
	printf("FAILED TO OPEN SHARED MEMORY IN CHILD PROCESS\n");
	return NULL;
    }
    if (*hMapFileB == INVALID_HANDLE_VALUE)
    {
	printf("Failed to open handle: invalid handle. Error: %ld\n", GetLastError());
	return NULL;
    }

    printf("creating shared value\n");
    void* sharedValue = MapViewOfFile(*hMapFileB, FILE_MAP_ALL_ACCESS, 0, 0, valueSize);

    
    
    if (sharedValue == NULL)
    {
	printf("FAILED TO MAP TO SHARED MEMORY\n");
	return NULL;
    }

    HANDLE eventHandle = CreateEventW(NULL, FALSE, FALSE, L"sceneb");
    
    WaitForSingleObject(eventHandle, 20);
    
    printf("memory success\n");
    printf("\n");
    printf("\n");
    printf("\n");
    return sharedValue;
    
}

void ReportEditedValue(HANDLE* inHandle)
{
    SetEvent(*inHandle);
}

void DestroyChildSharedMemory(HANDLE* hMapFileB, void* sharedValueB)
{
    UnmapViewOfFile(sharedValueB);
    CloseHandle(*hMapFileB);
}

void DestroySharedMemory(PROCESS_INFORMATION* pi, HANDLE* hMapFile, void* sharedValue)
{
    UnmapViewOfFile(sharedValue);
    CloseHandle(*hMapFile);
    CloseHandle(pi->hProcess);
    CloseHandle(pi->hThread);
}



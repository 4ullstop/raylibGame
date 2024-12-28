#include <windows.h>
#include "memory_setup.h"
#include <stdio.h>

void* SetupSharedMemory(STARTUPINFO* si, PROCESS_INFORMATION* pi, HANDLE* hMapFile, size_t valueSize)
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
	return sharedValue;
	//WaitForSingleObject(pi->hProcess, INFINITE);
    }
    else
    {
	printf("Failed to fork process");
	return NULL;
    }
}

void DestroySharedMemory(PROCESS_INFORMATION* pi, HANDLE* hMapFile, void* sharedValue)
{
    UnmapViewOfFile(sharedValue);
    CloseHandle(*hMapFile);
    CloseHandle(pi->hProcess);
    CloseHandle(pi->hThread);
}

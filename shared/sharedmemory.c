#include "sharedmemory.h"
#include <stdio.h>

void SetupSharedMemory(void)
{
    HANDLE hMapFile = CreateFileMapping(
	INVALID_HANDLE_VALUE, //hFile a handle to a file or device
	NULL, //lpAttributes: determines if the handle can be inherited by a child process
	PAGE_READWRITE, //flProtext: the protection for the desired file
	0, //MaximumSizeHigh
	sizeof(int), //MaximumSizeLow, this will be your struct when you have one made eventually
	"sceneb" //lpName: name of the file object mapped
	);
    if (hMapFile == NULL)
    {
	printf("ERROR, HMAPFILE NULL\n");
	return;
    }

    int* sharedValue = (int* )MapViewOfFile(
	hMapFile, //handle to the memory allocated
	FILE_MAP_ALL_ACCESS, //dwDesiredAccess: the type of access desired r/rw/rwx
	0, //file offset high
	0, //file offset low
	sizeof(int)); //number of bytes to map into the calling process's address

    if (sharedValue == NULL)
    {
	printf("ERROR SHAREDVALUE IS NULL\n");
	CloseHandle(hMapFile);
	return;
    }
}

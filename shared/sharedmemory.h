#pragma once

void SetupSharedMemory(STARTUPINFO* si, PROCESS_INFORMATION* pi, HANDLE* hMapFile, int* outValue);

void DestroySharedMemory(PROCESS_INFORMATION* pi, HANDLE* hMapFile, int* sharedValue);

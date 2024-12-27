#pragma once

void* SetupSharedMemory(STARTUPINFO* si, PROCESS_INFORMATION* pi, HANDLE* hMapFile, void* outValue);

void DestroySharedMemory(PROCESS_INFORMATION* pi, HANDLE* hMapFile, void* sharedValue);

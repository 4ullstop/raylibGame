#pragma once
#include <stdbool.h>
#ifndef MEMORY_SETUP_HEADER
#define MEMORY_SETUP_HEADER
#include "processthreadsapi.h"
#endif

void* SetupSharedMemoryAndCreateProcess(STARTUPINFO* si, PROCESS_INFORMATION* pi, HANDLE* hMapFile, size_t valueSize, HANDLE* eventHandle, char* mapFileName);

void* SetupSharedMemory(HANDLE* hMapFile, size_t valueSize, char* mapFileName);

void* FindWindowByTitle(const char* windowTitle);

bool SwitchToWindow(const char* windowTitle);

void* AttachChildProcessToMemory(HANDLE* hMapFileB, size_t valueSize, char* mapFileName);

void ReportEditedValue(HANDLE* inHandle);

void DestroySharedMemory(PROCESS_INFORMATION* pi, HANDLE* hMapFile, void* sharedValue);

void DestroyChildSharedMemory(HANDLE* hMapFileB, void* sharedValueB);

#pragma once
#include <stdbool.h>
#ifndef MEMORY_SETUP_HEADER
#define MEMORY_SETUP_HEADER
#include "processthreadsapi.h"
#endif

void* SetupSharedMemory(STARTUPINFO* si, PROCESS_INFORMATION* pi, HANDLE* hMapFile, size_t valueSize, HANDLE* eventHandle);

void DestroySharedMemory(PROCESS_INFORMATION* pi, HANDLE* hMapFile, void* sharedValue);

void* FindWindowByTitle(const char* windowTitle);

bool SwitchToWindow(const char* windowTitle);

void* AttachChildProcessToMemory(HANDLE* hMapFileB, size_t valueSize);

void DestroyChildSharedMemory(HANDLE* hMapFileB, void* sharedValueB);

void ReportEditedValue(HANDLE* inHandle);

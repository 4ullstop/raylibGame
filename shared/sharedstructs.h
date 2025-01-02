#pragma once
#include <stdbool.h>

#ifndef SHARED_MEM_HEADER
#define SHARED_MEM_HEADER
#include "../initialization/corestructs.h"
#endif

#ifndef SHARED_MEMORY_DATA
#define SHARED_MEMORY_DATA
typedef struct SharedMemoryData
{
    ButtonMaster* sharedPuzzleA;
    ButtonMaster* sharedPuzzleB;

    void (*StartSharedSetup)(ButtonMaster** allPuzzles, ButtonMaster* sharedPuzzle);
} SharedMemoryData;
#endif

#ifndef SHARED_MEMORY
#define SHARED_MEMORY
typedef struct SharedMemory
{
    SharedMemoryData** allSharedMemory;
    bool ActiveWindowA;

    int sharedValTesting;
    int flag;
} SharedMemory;
#endif




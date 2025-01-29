#pragma once
#include <stdbool.h>

#ifndef SHARED_MEM_HEADER
#define SHARED_MEM_HEADER
//#include "../initialization/corestructs.h"
#include "../initialization/windowstructs.h"
#include "processthreadsapi.h"
#endif

#ifndef PUZZLE_SHARED_VALUES
#define PUZZLE_SHARED_VALUES
typedef struct
{
    Vector2Int sharedCursorLocation;
    Vector2Int oldSharedCursorLocation;
    enum Direction inputDirection;
    bool submitButtonPressed; 
} PuzzleSharedValues;
#endif

#ifndef SHARED_MEMORY
#define SHARED_MEMORY
typedef struct SharedMemory
{
    bool ActiveWindowA;

    int sharedValTesting;
    int flag;

    bool gameClosing;

    int pairsOfSharedPuzzles;

    bool gameAInSharedPuzzle;
    bool gameBInSharedPuzzle;

    int gameACurrPuzzleId;
    int gameBCurrPuzzleId;

    bool sharingPuzzles;
} SharedMemory;
#endif

//the values inside of this struct are shared as opposed to the struct itself being shared
#ifndef OPEN_SHARED_VALUES
#define OPEN_SHARED_VALUES
typedef struct OpenSharedValues
{
    SharedMemory* mainSharedValues;
    PuzzleSharedValues* puzzleSharedValues;

    bool playerIsSharingPuzzles;

    STARTUPINFO* si;
    PROCESS_INFORMATION* pi;
    HANDLE* hMapFile;
    HANDLE* eventHandle;
    HANDLE* puzzleHandle;

    WindowData* windowData;
    
} OpenSharedValues;
#endif

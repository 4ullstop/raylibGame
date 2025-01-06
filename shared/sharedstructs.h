#pragma once
#include <stdbool.h>

#ifndef SHARED_MEM_HEADER
#define SHARED_MEM_HEADER
#include "../initialization/corestructs.h"
#endif

#ifndef PRESSED_BUTTON
#define PRESSED_BUTTON
enum PressedButton 
{
    PB_Up,
    PB_Down,
    PB_Left,
    PB_Right,
    PB_Enter,
    PB_Reset
};
#endif

#ifndef PUZZLE_SHARED_VALUES
#define PUZZLE_SHARED_VALUES
typedef struct
{
    Vector2Int sharedCursorLocation;
    enum PressedButton pressedButton;
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
} OpenSharedValues;
#endif

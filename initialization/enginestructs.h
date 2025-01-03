#pragma once

#ifndef EXIT_CODE
#define EXIT_CODE
typedef struct ExitCode
{
    int returnCode;
    char* gameVersion;
    char* extraReturnInfo;

    int numOfLoadedItems; 
} ExitCode;
#endif

#ifndef DESTRUCTION_LOCATIONS
#define DESTRUCTION_LOCATIONS
enum DestructionLocations
{
    DL_EMPTY,
    DL_Textures,
    DL_Models,
    DL_Puzzles,
    DL_AreaQueryBoxes,
    DL_Interactables,
    DL_OverlapBoxes,
    DL_GameplayElements,
    DL_SharedMemory,
    DL_Threads
};
#endif



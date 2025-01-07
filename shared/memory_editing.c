#include "memory_editing.h"
#include <stdlib.h>
#include <stdio.h>

void InitSharedMemoryValues(SharedMemory* sharedMemory, int pairsOfSharedPuzzles)
{
    //sharedMemory = (SharedMemory*)malloc(sizeof(SharedMemory*) * pairsOfSharedPuzzles);

    sharedMemory->gameClosing = false;
    sharedMemory->sharingPuzzles = false;
    sharedMemory->ActiveWindowA = false;
    
}

void AddPuzzleToSharedPuzzles(ButtonMaster* puzzleToAdd, SharedMemory* sharedMemory, int location, bool gameA)
{

}

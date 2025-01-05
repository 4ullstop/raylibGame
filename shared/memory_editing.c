#include "memory_editing.h"
#include <stdlib.h>
#include <stdio.h>

void InitSharedMemoryValues(SharedMemory* sharedMemory, int pairsOfSharedPuzzles)
{
    sharedMemory->allSharedMemory = (SharedMemoryData**)malloc(sizeof(SharedMemoryData*) * pairsOfSharedPuzzles);

    sharedMemory->gameClosing = false;

    
}

void AddPuzzleToSharedPuzzles(ButtonMaster* puzzleToAdd, SharedMemory* sharedMemory, int location, bool gameA)
{

}

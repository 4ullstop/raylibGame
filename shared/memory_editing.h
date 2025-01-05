#pragma once

#ifndef MEMORY_EDITING_HEADER
#define MEMORY_EDITING_HEADER
#include "../initialization/corestructs.h"
#include "sharedstructs.h"
#endif

void InitSharedMemoryValues(SharedMemory* sharedMemory, int pairsOfSharedPuzzles);

void AddPuzzleToSharedPuzzles(ButtonMaster* puzzleToAdd, SharedMemory* sharedMemory, int location, bool gameA);

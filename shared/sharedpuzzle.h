#pragma once

#ifndef SHARED_PUZZLE_HEADER
#define SHARED_PUZZLE_HEADER
#include "memory_setup.h"
#include "sharedstructs.h"
#include <stdbool.h>
#endif

void InitSharedPuzzleGameA(HANDLE* puzzleHMapFile, OpenSharedValues* openSharedValues);

void InitSharedPuzzleGameB(HANDLE* puzzleHMapFile, OpenSharedValues* openSharedValues);

bool IsPlayerReadyToSharePuzzles(SharedMemory* mainSharedValues);


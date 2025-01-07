#pragma once

#ifndef SHARED_PUZZLE_HEADER
#define SHARED_PUZZLE_HEADER
#include "memory_setup.h"
#include "sharedstructs.h"
#include <stdbool.h>
#endif

void InitSharedPuzzleGameA(HANDLE* puzzleHMapFile, OpenSharedValues* openSharedValues, ExitCode* exitCode, char* mapFileName);

void InitSharedPuzzleGameB(HANDLE* puzzleHMapFile, OpenSharedValues* openSharedValues, ExitCode* exitCode, char* mapFileName);

bool IsPlayerReadyToSharePuzzles(SharedMemory* mainSharedValues);

void HandleProducerInput(ButtonMaster* puzzle, Button* oldButton, Button* newButton, OpenSharedValues* openSharedValues, bool isConsumer);

Button* HandleConsumerInput(ButtonMaster* puzzle, Button* button, OpenSharedValues* openSharedValues);
    


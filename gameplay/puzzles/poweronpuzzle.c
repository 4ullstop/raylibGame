#include "poweronpuzzle.h"
#include "../../shared/memory_setup.h"
#include "../../shared/sharedpuzzle.h"
#include <stdio.h>

void OpenSecondGame(OpenSharedValues* openSharedValues, ExitCode* exitCode, enum Gametype gametype)
{
    switch(gametype)
    {
    case EGT_A:
	GameAOpening(openSharedValues, exitCode);
	break;
    case EGT_B:
	GameBOpening(openSharedValues, exitCode);
    }
}

void GameAOpening(OpenSharedValues* openSharedValues, ExitCode* exitCode)
{
    openSharedValues->mainSharedValues = (SharedMemory *)SetupSharedMemoryAndCreateProcess(openSharedValues->si, openSharedValues->pi, openSharedValues->hMapFile, sizeof(SharedMemory), openSharedValues->eventHandle, "sceneb");
    ReportEditedValue(openSharedValues->eventHandle);
    InitSharedPuzzleGameA(openSharedValues->puzzleHandle, openSharedValues, exitCode, "puzzle");
    printf("GameA opened\n");
    printf("\n");
}

void GameBOpening(OpenSharedValues* openSharedValues, ExitCode* exitCode)
{
    openSharedValues->mainSharedValues = (SharedMemory *)AttachChildProcessToMemory(openSharedValues->hMapFile, sizeof(SharedMemory), "sceneb");
    InitSharedPuzzleGameB(openSharedValues->puzzleHandle, openSharedValues, exitCode, "puzzle");
}

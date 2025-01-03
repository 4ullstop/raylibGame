#include "globalfunc.h"
#include "enginestructs.h"
#include <stdio.h>

bool CheckForErrors(ExitCode* exitCode, enum DestructionLocations* destructionLocations)
{
    if (exitCode->returnCode > 0)
    {
	HandleEarlyExit(exitCode->returnCode, destructionLocations);
	ReportError(exitCode);
	return true;
    }
    return false;
}

void ReportError(ExitCode* exitCode)
{
    printf("GAME %s, exited with code: %i\n", exitCode->gameVersion, exitCode->returnCode);
    printf("%s\n", exitCode->extraReturnInfo);
}

void EditReturnCodeInfo(int returnCode, char* extraInfo, ExitCode* exitCode)
{
    exitCode->returnCode = returnCode;
    exitCode->extraReturnInfo = extraInfo;
}

void HandleEarlyExit(int returnCode, enum DestructionLocations* destructionLocations)
{
    if (returnCode > 0 && returnCode < 100)
    {
	//Error in loading textures
	*destructionLocations = DL_Textures;
    }
    else if (returnCode > 99 && returnCode < 200)
    {
	//Gameplay elements
	*destructionLocations = DL_GameplayElements;
    }
    else if (returnCode > 199 && returnCode < 400)
    {
	//Puzzles
	*destructionLocations = DL_Puzzles;
    }
    else if (returnCode > 399 && returnCode < 500)
    {
	//Models
	*destructionLocations = DL_Models;
    }
    else if (returnCode > 499 && returnCode < 600)
    {
	//Area Queries
	*destructionLocations = DL_AreaQueryBoxes;
    }
    else if (returnCode > 599 && returnCode < 700)
    {
	//Interactables
	*destructionLocations = DL_Interactables;
    }
    else if (returnCode > 699 && returnCode < 800)
    {
	//Overlap Boxes
	*destructionLocations = DL_OverlapBoxes;
    }
    else if (returnCode > 799 && returnCode < 1000)
    {
	//Shared Memory
	*destructionLocations = DL_SharedMemory;
    }
    else if (returnCode > 999 && returnCode < 1100)
    {
	*destructionLocations = DL_Threads;
    }
}





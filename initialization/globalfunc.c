#include "globalfunc.h"
#include "enginestructs.h"
#include <stdio.h>

void CheckForErrors(ExitCode* exitCode)
{
    if (exitCode->returnCode > 0)
    {
	ReportError(exitCode);
    }
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

void HandleEarlyExit(int returnCode)
{
    if (returnCode > 0 && returnCode < 100)
    {
	//Error in loading textures
	
    }
    else if (returnCode > 99 && returnCode < 200)
    {
	//Gameplay elements
    }
    else if (returnCode > 199 && returnCode < 400)
    {
	//Puzzles
    }
    else if (returnCode > 399 && returnCode < 500)
    {
	//Models
    }
    else if (returnCode > 499 && returnCode < 600)
    {
	//Area Queries
    }
    else if (returnCode > 599 && returnCode < 700)
    {
	//Interactables
    }
    else if (returnCode > 699 && returnCode < 800)
    {
	//Overlap Boxes
    }
    else if (returnCode > 799 && returnCode < 1000)
    {
	//Shared Memory
    }
    else if (returnCode > 999 && returnCode < 1100)
    {
	
    }
}





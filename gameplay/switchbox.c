#include "switchbox.h"
#include <stdlib.h>
#include <stdio.h>

void ConstructSingleSwitchBox(GameplayElements* gameplayElements, ExitCode* exitCode, int numOfSwitches, int* lastSwitchBox, Door* referenceDoor)
{
    gameplayElements->switchBox[*lastSwitchBox] = malloc(sizeof(SwitchBox));
    if (gameplayElements->switchBox[*lastSwitchBox] == NULL)
    {
	EditReturnCodeInfo(400, "Failed to allocate memory for switchBox", exitCode);
	return;
    }
    gameplayElements->switchBox[*lastSwitchBox]->allSwitches = malloc(sizeof(bool) * numOfSwitches);
    if (gameplayElements->switchBox[*lastSwitchBox]->allSwitches == NULL)
    {
	EditReturnCodeInfo(400, "Failed to allocate memory for switchbox", exitCode);
	return;
    }
    gameplayElements->switchBox[*lastSwitchBox]->numOfSwitches = numOfSwitches;
    gameplayElements->switchBox[*lastSwitchBox]->lastSwitchId = 0;
    gameplayElements->switchBox[*lastSwitchBox]->referenceDoor = referenceDoor;
   
    for (int i = 0; i < numOfSwitches; i++)
    {
	gameplayElements->switchBox[*lastSwitchBox]->allSwitches[i] = false;
    }
    *lastSwitchBox = *lastSwitchBox + 1;
}

void QuerySwitchBox(SwitchBox** switchBox, int switchBoxId, int activatedId)
{
    switchBox[switchBoxId]->allSwitches[activatedId] = true;
    for (int i = 0; i < switchBox[switchBoxId]->numOfSwitches; i++)
    {
	printf("switch %i powered on\n", i);
	if (switchBox[switchBoxId]->allSwitches[i] == false)
	{
	    return;
	}
    }
    switchBox[switchBoxId]->referenceDoor->isLowering = true;
}

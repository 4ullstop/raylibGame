#include "switchbox.h"
#include <stdlib.h>
#include <stdio.h>

void ConstructSingleSwitchBox(GameplayElements* gameplayElements, ExitCode* exitCode, int numOfSwitches, int* lastSwitchBox, Door* referenceDoor)
{
    printf("constructing switchbox\n");
    gameplayElements->switchBox[*lastSwitchBox]->allSwitches = malloc(sizeof(bool) * numOfSwitches);
    if (gameplayElements->switchBox[*lastSwitchBox]->allSwitches == NULL)
    {
	EditReturnCodeInfo(400, "Failed to allocate memory for switchbox", exitCode);
    }
    gameplayElements->switchBox[*lastSwitchBox]->numOfSwitches = numOfSwitches;
    gameplayElements->switchBox[*lastSwitchBox]->lastSwitchId = 0;
    printf("about to construct reference door\n");
    gameplayElements->switchBox[*lastSwitchBox]->referenceDoor = referenceDoor;
   
    for (int i = 0; i < numOfSwitches; i++)
    {
	printf("rolling through switches\n");
	gameplayElements->switchBox[*lastSwitchBox]->allSwitches[i] = false;
    }
    printf("switchbox constructed\n");
    *lastSwitchBox = *lastSwitchBox + 1;
}

void QuerySwitchBox(SwitchBox** switchBox, int switchBoxId, int activatedId)
{
    switchBox[switchBoxId]->allSwitches[activatedId] = true;
    for (int i = 0; i < switchBox[switchBoxId]->numOfSwitches; i++)
    {
	if (switchBox[switchBoxId]->allSwitches[i] == false)
	{
	    return;
	}
    }
    switchBox[switchBoxId]->referenceDoor->isLowering = true;
}

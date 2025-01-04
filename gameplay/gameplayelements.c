#include "gameplayelements.h"
#include <stdio.h>

void PollAllGameplayElements(Door** allDoors, double deltaTime, int numOfDoors)
{
    PollDoors(allDoors, deltaTime, numOfDoors);
}

void ConstructGameplayElements(modelInfo** models, int* lastModelIndex, Texture2D** allTextures, int numOfDoors, GameplayElements* gameplayElements, Door* allDoors[], ExitCode* exitCode)
{
    if (gameplayElements == NULL)
    {
	EditReturnCodeInfo(103, "Gameplay elements NULL upon Construction", exitCode);
	return;
    }
    
    ConstructDoors(models, allTextures, lastModelIndex, allDoors, exitCode);
    gameplayElements->numOfDoors = numOfDoors;
    for (int i = 0; i < gameplayElements->numOfDoors; i++)
    {
        printf("Gameplay elements door: %p\n", (void*)&allDoors[i]);
        printf("\n");
        gameplayElements->doors[i] = allDoors[i];
        printf("Gameplay elements door: %p\n", (void*)&gameplayElements->doors[i]);
        printf("\n");
    }
}

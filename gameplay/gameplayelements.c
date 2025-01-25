#include "gameplayelements.h"
#include <stdio.h>
#include "../gamea/gameagameplayelements.h"
#include "../gameb/gamebgameplayelements.h"

void PollAllGameplayElements(Door** allDoors, double deltaTime, int numOfDoors)
{
    PollDoors(allDoors, deltaTime, numOfDoors);
}

void ConstructGameplayElements(modelInfo** models, int* lastModelIndex, Texture2D** allTextures, int numOfDoors, GameplayElements* gameplayElements, Door** allDoors, ExitCode* exitCode, enum Gametype gametype)
{
    if (gameplayElements == NULL)
    {
	EditReturnCodeInfo(103, "Gameplay elements NULL upon Construction", exitCode);
	return;
    }
    if (gametype == EGT_A)
    {
	ConstructGameAGameplayElements(models, lastModelIndex, allTextures, numOfDoors, gameplayElements, allDoors, exitCode);
	gameplayElements->numOfDoors = numOfDoors;
    }
    else
    {
	ConstructGameBGameplayElements(models, lastModelIndex, allTextures, numOfDoors, gameplayElements, allDoors, exitCode);
	gameplayElements->numOfDoors = numOfDoors;	
    }

    /*
    for (int i = 0; i < gameplayElements->numOfDoors; i++)
    {
        printf("Gameplay elements door: %p\n", (void*)&allDoors[i]);
        printf("\n");
        gameplayElements->doors[i] = allDoors[i];
        printf("Gameplay elements door: %p\n", (void*)&gameplayElements->doors[i]);
        printf("\n");
    }
    */
}

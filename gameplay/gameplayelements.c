#include "gameplayelements.h"
#include <stdio.h>

void PollAllGameplayElements(Door** allDoors, double deltaTime, int numOfDoors)
{
    PollDoors(allDoors, deltaTime, numOfDoors);
}

void DestructAllGameplayElements(GameplayElements* gameplayElements)
{
    DestructAllDoors(gameplayElements->doors, gameplayElements->numOfDoors);
}

void ConstructGameplayElements(modelInfo** models, int* lastModelIndex, int numOfDoors, GameplayElements* gameplayElements, Door** allDoors)
{
    ConstructDoors(models, lastModelIndex, allDoors);
    gameplayElements->numOfDoors = numOfDoors;
    for (int i = 0; i < gameplayElements->numOfDoors; i++)
    {
        gameplayElements->doors[i] = allDoors[i];
    }
}
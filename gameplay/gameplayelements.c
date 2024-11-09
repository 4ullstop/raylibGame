#include "gameplayelements.h"
#include <stdio.h>

void PollAllGameplayElements(Door** allDoors, double deltaTime, int numOfDoors)
{
    PollDoors(allDoors, deltaTime, numOfDoors);
}

void DestructAllGameplayElements(GameplayElements* gameplayElements, Door** allDoors)
{
    DestructAllDoors(allDoors, gameplayElements->numOfDoors);
}

void ConstructGameplayElements(modelInfo** models, int* lastModelIndex, int numOfDoors, GameplayElements* gameplayElements, Door* allDoors[])
{
    ConstructDoors(models, lastModelIndex, allDoors);
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
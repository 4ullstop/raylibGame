#ifndef GAMEPLAY_ELEMENTS_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "../initialization/corestructs.h"
#include "door.h"
#endif

void PollAllGameplayElements(Door** allDoors, double deltaTime, int numOfDoors);

void ConstructGameplayElements(modelInfo** models, int* lastModelIndex, int numOfDoors, GameplayElements* gameplayElements, Door** allDoors);

void DestructAllGameplayElements(GameplayElements* gameplayElements, Door* allDoors[]);
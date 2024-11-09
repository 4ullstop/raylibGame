#ifndef DOOR_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "../initialization/corestructs.h"
#endif

void ConstructDoors(modelInfo** dynamicModels, int* lastModelIndex, Door** allDoors);

void LowerDoor(Door* door, double deltaTime);

void PollDoors(Door** allDoors, double deltaTime, int numOfDoors);

void DestructAllDoors(Door** allDoors, int numOfDoors);
#ifndef DOOR_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "../initialization/corestructs.h"
#endif

void ConstructDoors(modelInfo** dynamicModels, Texture2D** gameTextures, int* lastModelIndex, Door** allDoors, ExitCode* exitCode);

void LowerDoor(Door* door, double deltaTime);

void PollDoors(Door** allDoors, double deltaTime, int numOfDoors);

void DestructAllDoors(Door* allDoors[], int numOfDoors);

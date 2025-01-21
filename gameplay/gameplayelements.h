#ifndef GAMEPLAY_ELEMENTS_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "../initialization/corestructs.h"
#include "door.h"
#endif

void PollAllGameplayElements(Door** allDoors, double deltaTime, int numOfDoors);

void ConstructGameplayElements(modelInfo** models, int* lastModelIndex, Texture2D** allTextures, int numOfDoors, GameplayElements* gameplayElements, Door** allDoors, ExitCode* exitCode, enum Gametype gametype);


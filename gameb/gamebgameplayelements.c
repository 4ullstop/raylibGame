#include "gamebgameplayelements.h"

void ConstructGameBGameplayElements(modelInfo** models, int* lastModelIndex, Texture2D** allTextures, int numOfDoors, GameplayElements* gameplayElements, Door* allDoors[], ExitCode* exitCode)
{
    if (numOfDoors == 0) return;
    ConstructGameBDoors(models, allTextures, lastModelIndex, allDoors, exitCode);
}

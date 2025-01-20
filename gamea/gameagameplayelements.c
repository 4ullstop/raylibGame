#include "gameagameplayelements.h"

void ConstructGameAGameplayElements(modelInfo** models, int* lastModelIndex, Texture2D** allTextures, int numOfDoors, GameplayElements* gameplayElements, Door* allDoors[], ExitCode* exitCode)
{
    if (numOfDoors == 0) return;
    ConstructDoors(models, allTextures, lastModelIndex, allDoors, exitCode);
}

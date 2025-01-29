#include "gameagameplayelements.h"
#include "gameaswitchboxes.h"
#include "gameaindicators.h"

void ConstructGameAGameplayElements(modelInfo** models, int* lastModelIndex, Texture2D** allTextures, int numOfDoors, GameplayElements* gameplayElements, Door** allDoors, Indicator** indicators, ExitCode* exitCode)
{
    if (numOfDoors == 0) return;
    ConstructGameADoors(models, allTextures, lastModelIndex, allDoors, exitCode);
    ConstructGameASwitchBoxes(gameplayElements, exitCode);
    ConstructGameAIndicators(models, allTextures, lastModelIndex, indicators, exitCode);
}


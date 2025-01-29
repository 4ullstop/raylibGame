#include "gamebgameplayelements.h"
#include "gamebswitchboxes.h"
#include "gamebindicators.h"x

void ConstructGameBGameplayElements(modelInfo** models, int* lastModelIndex, Texture2D** allTextures, int numOfDoors, GameplayElements* gameplayElements, Door** allDoors, Indicator** indicators, ExitCode* exitCode)
{
    if (numOfDoors == 0) return;
    ConstructGameBDoors(models, allTextures, lastModelIndex, allDoors, exitCode);
    ConstructGameBSwitchBoxes(gameplayElements, exitCode);
    ConstructGameBIndicators(models, allTextures, lastModelIndex, indicators, exitCode);
}

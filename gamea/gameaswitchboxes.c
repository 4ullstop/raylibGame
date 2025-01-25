#include "gameaswitchboxes.h"
#include <stdlib.h>
#include <stdio.h>
#include "../gameplay/switchbox.h"

void ConstructGameASwitchBoxes(GameplayElements* gameplayElements, ExitCode* exitCode)
{
    int lastSwitchBoxIndex = 0;
    ConstructSingleSwitchBox(gameplayElements,
			     exitCode,
			     3,
			     &lastSwitchBoxIndex,
			     gameplayElements->doors[3]);
}

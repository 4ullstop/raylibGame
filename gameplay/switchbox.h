#ifndef SWITCH_BOX_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "../initialization/corestructs.h"
#endif

void ConstructSingleSwitchBox(GameplayElements* gameplayElements, ExitCode* exitCode, int numOfSwitches, int*lastSwitchBox, Door* referenceDoor);

void QuerySwitchBox(SwitchBox** switchBox, int switchBoxId, int activatedId);

void DestroySwitchBoxes(GameplayElements* gameplayElements);

void DestroySwitches(SwitchBox* switchBox);



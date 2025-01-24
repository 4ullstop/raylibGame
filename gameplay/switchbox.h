#pragma once

#ifndef SWITCH_BOX_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "../initialization/corestructs.h"
#endif

void ConstructSingleSwitchBox(GameplayElements* gameplayElements, ExitCode* exitCode, int numOfSwitches, int*lastSwitchBox, Door* referenceDoor);

void QuerySwitchBox(SwitchBox** switchBox, int switchBoxId, int activatedId);



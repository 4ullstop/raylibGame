#pragma once

#ifndef POWER_ON_PUZZLE_HEADER
#define POWER_ON_PUZZLE_HEADER
#include "../../initialization/corestructs.h"
#include "../../shared/sharedstructs.h"
#endif

void OpenSecondGame(OpenSharedValues* openSharedValues, ExitCode* exitCode, enum Gametype gametype);

void GameAOpening(OpenSharedValues* openSharedValues, ExitCode* exitCode);

void GameBOpening(OpenSharedValues* openSharedValues, ExitCode* exitCode);

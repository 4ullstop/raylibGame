#pragma once

#ifndef GAMEB_INDICATORS_HEADER
#define GAMEB_INDICATORS_HEADER
#include "../initialization/corestructs.h"
#endif

void ConstructGameBIndicators(modelInfo** dynamicModels, Texture2D** gameBTextures, int* lastModelIndex, Indicator** allIndicators, ExitCode* exitCode);

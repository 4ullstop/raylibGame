#pragma once

#ifndef INDICATOR_HEADER
#define INDICATOR_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "../../initialization/corestructs.h"
#endif

void ConstructSingleIndicator(modelInfo** allModels, Texture2D** gameTextures, char* modelFileLocation, Vector3 location, int gameTextureIndex, int* lastIndicatorIndex, int* lastModelIndex);

void UpdateShaderForIndicator(Indicator* indicator);

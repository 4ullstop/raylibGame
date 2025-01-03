#pragma once

#ifndef DESTROY_OBJECTS_HEADER
#define DESTROY_OBJECTS_HEADER
#include "../initialization/corestructs.h"
#endif

void DestroyAllModels(modelInfo** models, int numOfModels, Texture2D** allTextures, int numOfTextures);

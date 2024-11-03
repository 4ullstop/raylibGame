#ifndef RAYLIB_CAMERA_HEAD
#include "C:\raylib\raylib\src\raylib.h"
#include "../../initialization/corestructs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#endif



void CreateModels(modelInfo** models, int* lastModelIndex, enum Gametype gametype);

void DrawAllModels(modelInfo** models);

void DestroyAllModels(modelInfo** models);
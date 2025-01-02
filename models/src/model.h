#ifndef RAYLIB_CAMERA_HEAD
#include "C:\raylib\raylib\src\raylib.h"
#include "../../initialization/corestructs.h"
#include "../../gamea/gameamodels.h"
#include "../../gameb/gamebmodels.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#endif



void CreateModels(modelInfo** models, int* lastModelIndex, enum Gametype gametype, Texture2D** allTextures, ExitCode* exitCode);

void DrawAllModels(modelInfo** models, int numOfModels);

void DestroyAllModels(modelInfo** models, int numOfModels, Texture2D** allTextures, int numOfTextures);


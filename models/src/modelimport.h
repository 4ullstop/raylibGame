#ifndef RAYLIB_CAMERA_HEAD
#include "C:\raylib\raylib\src\raylib.h"
#include "../../initialization/corestructs.h"
#endif

/*
    At some point you will need to delete this file and remove it from the make file
    Seeing as this comment is still here it means I was too lazy to do it rn
*/

void DrawModels(modelInfo* models[], int size);

void UnloadAllModels(modelInfo** models, int size);

void PollModels(modelInfo* model);
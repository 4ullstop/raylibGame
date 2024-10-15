#ifndef RAYLIB_CAMERA_HEAD
#include "C:\raylib\raylib\src\raylib.h"
#endif

typedef struct modelInfo
{
    char* modelPathLocation;
    char* texturePathLocation;
    Model model;
    Texture2D texture;

    Vector3 modelLocation;
    int modelArrSize;
    
} modelInfo;

void InitModels(modelInfo* models, int size);

void DrawModels(modelInfo* models, int size);

void UnloadAllModels(modelInfo* models, int size);

void PollModels(modelInfo* model);
#ifndef RAYLIB_CAMERA_HEAD
#include "C:\raylib\raylib\src\raylib.h"
#endif

typedef struct modelInfo
{
    Model model;
    Texture2D texture;

    Vector3 modelLocation;
    int modelArrSize;
    
} modelInfo;


void DrawModels(modelInfo** models, int size);

void UnloadAllModels(modelInfo** models, int size);

void PollModels(modelInfo* model);
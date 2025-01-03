#include "model.h"
#include <stdio.h>

/*
    Used for construction, destruction and drawing of static models
    within the scene, not intended for models that are associated 
    entities... probably
*/

void CreateModels(modelInfo** models, int* lastModelIndex, enum Gametype gametype, Texture2D** allTextures, ExitCode* exitCode)
{
    if (gametype == EGT_A)
    {
        CreateModelsForGameA(models, lastModelIndex, allTextures, exitCode);
    }
    else
    {
        CreateModelsForGameB(models, lastModelIndex, allTextures, exitCode);
    }
}

void DrawAllModels(modelInfo** models, int numOfModels)
{
    for (int i = 0; i < numOfModels; i++)
    {
        if (models[i]->modelVisible == false) continue;
        DrawModel(models[i]->model, models[i]->modelLocation, 1.0f, WHITE);
    }
}

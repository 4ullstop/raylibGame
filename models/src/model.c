#include "model.h"
#include <stdio.h>

/*
    Used for construction, destruction and drawing of static models
    within the scene, not intended for models that are associated 
    entities... probably
*/

void CreateModels(modelInfo** models, int* lastModelIndex, enum Gametype gametype)
{
    if (gametype == EGT_A)
    {
        printf("last model index in model.c: %i\n", lastModelIndex);
        CreateModelsForGameA(models, lastModelIndex);
    }
    else
    {
        CreateModelsForGameB(models, lastModelIndex);
    }
}

void DrawAllModels(modelInfo** models, int numOfModels)
{
    for (int i = 0; i < numOfModels; i++)
    {
        DrawModel(models[i]->model, models[i]->modelLocation, 1.0f, WHITE);
    }
}

void DestroyAllModels(modelInfo** models, int numOfModels)
{
    for (int i = 0; i < numOfModels; i++)
    {
        UnloadTexture(models[i]->texture);
        UnloadModel(models[i]->model);
        free(models[i]);
        models[i] = NULL;
    }
}
#include "model.h"

/*
    Used for construction, destruction and drawing of static models
    within the scene, not intended for models that are associated 
    entities... probably
*/

void CreateModels(modelInfo** models, int* lastModelIndex, enum Gametype gametype)
{
    if (gametype == EGT_A)
    {
        CreateModelsForGameA(models, lastModelIndex);
    }
    else
    {
        CreateModelsForGameB(models, lastModelIndex);
    }
}

void DrawAllModels(modelInfo** models)
{
    for (int i = 0; i < NUMBER_OF_MODELS; i++)
    {
        DrawModel(models[i]->model, models[i]->modelLocation, 1.0f, WHITE);
    }
}

void DestroyAllModels(modelInfo** models)
{
    for (int i = 0; i < NUMBER_OF_MODELS; i++)
    {
        UnloadTexture(models[i]->texture);
        UnloadModel(models[i]->model);
        free(models[i]);
        models[i] = NULL;
    }
}
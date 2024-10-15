#include "modelimport.h"
#include <stdio.h>

void InitModels(modelInfo** models, int size)
{
    printf("Log: Loading models...");

    for (int i = 0; i < size; i++)
    {
        models[i]->modelLocation;
        Model tempMod = LoadModel(models[i]->modelPathLocation);
        Texture2D tempText = LoadTexture(models[i]->texturePathLocation);
        tempMod.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tempText;
        models[i]->model = tempMod;
        models[i]->texture = tempText;
    }
}

void PollModels(modelInfo* model)
{
    if (IsFileDropped())
    {
        FilePathList droppedFiles = LoadDroppedFiles();

        if (droppedFiles.count == 1)
        {
            if (IsFileExtension(droppedFiles.paths[0], "obj"))
            {
                UnloadModel(model->model);
                model->model = LoadModel(droppedFiles.paths[0]);
                model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = model->texture;
            }
            else if (IsFileExtension(droppedFiles.paths[0], "png"))
            {
                UnloadTexture(model->texture);
                model->texture = LoadTexture(droppedFiles.paths[0]);
                model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = model->texture;
            }
        }
        UnloadDroppedFiles(droppedFiles);
    }
}

void DrawModels(modelInfo* models, int size)
{
    for (int i = 0; i < size; i++)
    {
        DrawModel(models[i].model, models[i].modelLocation, 1.0f, WHITE);
    }
}

void UnloadAllModels(modelInfo* models, int size)
{
    for (int i = 0; i < size; i++)
    {
        UnloadTexture(models[i].texture);
        UnloadModel(models[i].model);
    }
}
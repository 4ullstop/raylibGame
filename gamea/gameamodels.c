#include "gameamodels.h"
#include <stdlib.h>
#include <stdio.h>

void CreateModelsForGameA(modelInfo** models, int* lastModelIndex, Texture2D** allTextures, ExitCode* exitCode)
{
    //room 1
    exitCode->numOfLoadedItems = 0;
    modelInfo* floor = malloc(sizeof(modelInfo));
    if (floor == NULL)
    {
	EditReturnCodeInfo(400, "Failed to allocate memory for model\n", exitCode);
	return;
    }
    floor->collisionDisabled = false;
    floor->modelVisible = true;
    floor->model = LoadModel("D:/CFiles/FirstGame/models/obj/ground.obj");
    floor->texture = *allTextures[0];
    floor->modelLocation = (Vector3){0.0f, 0.0f, 0.0f};
    floor->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floor->texture;
    models[*lastModelIndex] = floor;
    *lastModelIndex = *lastModelIndex + 1;
    exitCode->numOfModelsLoaded = exitCode->numOfModelsLoaded + 1;
    

    modelInfo* dock = malloc(sizeof(modelInfo));
    if (dock == NULL)
    {
	EditReturnCodeInfo(400, "Failed to allocate memory for model", exitCode);
	return;
    }
    dock->collisionDisabled = false;
    dock->modelVisible = true;
    dock->model = LoadModel("D:/CFiles/FirstGame/models/obj/dock_01.obj");
    dock->texture = *allTextures[9];
    dock->modelLocation = (Vector3){-2.7f, 2.0f, 0.0f};
    dock->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = dock->texture;
    models[*lastModelIndex] = dock;
    *lastModelIndex = *lastModelIndex + 1;
    exitCode->numOfModelsLoaded = exitCode->numOfModelsLoaded + 1;

    modelInfo* dock_02 = malloc(sizeof(modelInfo));
    if (dock_02 == NULL)
    {
	EditReturnCodeInfo(400, "Failed to allocated memory for model", exitCode);
	return;
    }
    dock_02->collisionDisabled = false;
    dock_02->modelVisible = true;
    dock_02->model = LoadModel("D:/CFiles/FirstGame/models/obj/dock_02.obj");
    dock_02->texture = *allTextures[9];
    dock_02->modelLocation = (Vector3){0.0f, 2.0f, 0.0f};
    dock_02->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = dock_02->texture;
    models[*lastModelIndex] = dock_02;
    *lastModelIndex = *lastModelIndex + 1;
    exitCode->numOfModelsLoaded = exitCode->numOfModelsLoaded + 1;

    modelInfo* scale = malloc(sizeof(modelInfo));
    if (scale == NULL)
    {
	EditReturnCodeInfo(400, "Failed to allocate memory for model", exitCode);
	return;
    }
    scale->collisionDisabled = false;
    scale->modelVisible = true;
    scale->model = LoadModel("D:/CFiles/FirstGame/models/obj/scaleref.obj");
    scale->texture = *allTextures[9];
    scale->modelLocation = (Vector3) {0.0f, 0.0f, 0.0f};
    scale->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = scale->texture;
    models[*lastModelIndex] = scale;
    *lastModelIndex = *lastModelIndex + 1;
    exitCode->numOfModelsLoaded = exitCode->numOfModelsLoaded + 1;
    
    //
}

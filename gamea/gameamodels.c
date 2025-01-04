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
    floor->model = LoadModel("D:/CFiles/FirstGame/models/obj/floor_02.obj");
    floor->texture = *allTextures[0];
    floor->modelLocation = (Vector3){0.0f, 0.0f, 0.0f};
    floor->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floor->texture;
    models[*lastModelIndex] = floor;
    *lastModelIndex = *lastModelIndex + 1;
    exitCode->numOfModelsLoaded = exitCode->numOfModelsLoaded + 1;
    
    modelInfo* wall_01 = malloc(sizeof(modelInfo));
    if (wall_01 == NULL)
    {
	EditReturnCodeInfo(400, "Failed to allocate memory for model\n", exitCode);
	return;
    }
    wall_01->collisionDisabled = false;
    wall_01->modelVisible = true;
    wall_01->model = LoadModel("D:/CFiles/FirstGame/models/obj/level_01.obj");
    wall_01->texture = *allTextures[1];
    wall_01->modelLocation = (Vector3){0.0f, 0.0f, -15.0f};
    wall_01->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = wall_01->texture;
    models[*lastModelIndex] = wall_01;
    *lastModelIndex = *lastModelIndex + 1;
    exitCode->numOfModelsLoaded = exitCode->numOfModelsLoaded + 1;

    //
}

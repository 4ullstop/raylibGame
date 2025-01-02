#include "gamebmodels.h"
#include <stdlib.h>

void CreateModelsForGameB(modelInfo** models, int* lastModelIndex, Texture2D** allTextures, ExitCode* exitCode)
{
    exitCode->numOfLoadedItems = 0;
    modelInfo* floor = malloc(sizeof(modelInfo));
    if (floor == NULL)
    {
	EditReturnCodeInfo(400, "Failed to allocate memory for model\n", exitCode);
	return;
    }
    floor->collisionDisabled = false;
    floor->modelVisible = true;
    floor->model = LoadModel("D:/CFiles/FirstGame/models/obj/floor.obj"); 
    floor->texture = *allTextures[0];
    floor->modelLocation = (Vector3){0.0f, 0.0f, 0.0f};
    floor->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floor->texture;
    models[*lastModelIndex] = floor;
    *lastModelIndex = *lastModelIndex + 1;
    exitCode->numOfLoadedItems = exitCode->numOfLoadedItems + 1;
}

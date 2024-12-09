#include "gamebmodels.h"
#include <stdlib.h>

void CreateModelsForGameB(modelInfo** models, int* lastModelIndex, Texture2D** allTextures)
{
    modelInfo* floor = malloc(sizeof(modelInfo));
    floor->collisionDisabled = false;
    floor->modelVisible = true;
    floor->model = LoadModel("D:/CFiles/FirstGame/models/obj/floor.obj"); 
    floor->texture = *allTextures[0];
    floor->modelLocation = (Vector3){0.0f, 0.0f, 0.0f};
    floor->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floor->texture;
    models[*lastModelIndex] = floor;
    *lastModelIndex = *lastModelIndex + 1;

    modelInfo* wall_01 = malloc(sizeof(modelInfo));
    wall_01->collisionDisabled = false;
    wall_01->modelVisible = true;
    wall_01->model = LoadModel("D:/CFiles/FirstGame/models/obj/level_01.obj");
    wall_01->texture = *allTextures[1];
    wall_01->modelLocation = (Vector3){0.0f, 0.0f, 0.0f};
    wall_01->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = wall_01->texture;
    models[*lastModelIndex] = wall_01;
    *lastModelIndex = *lastModelIndex + 1; 
}

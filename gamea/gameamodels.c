#include "gameamodels.h"
#include <stdlib.h>
#include <stdio.h>

void CreateModelsForGameA(modelInfo** models, int* lastModelIndex)
{
    //room 1
    modelInfo* floor = malloc(sizeof(modelInfo));
    floor->collisionDisabled = false;
    floor->model = LoadModel("D:/CFiles/FirstGame/models/obj/floor_02.obj");
    floor->texture = LoadTexture("D:/CFiles/FirstGame/models/obj/walls.png");
    floor->modelLocation = (Vector3){0.0f, 0.0f, 0.0f};
    floor->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floor->texture;
    models[*lastModelIndex] = floor;
    *lastModelIndex = *lastModelIndex + 1;
    
    modelInfo* wall_01 = malloc(sizeof(modelInfo));
    wall_01->collisionDisabled = false;
    wall_01->model = LoadModel("D:/CFiles/FirstGame/models/obj/level_01.obj");
    wall_01->texture = LoadTexture("D:/CFiles/FirstGame/models/obj/walls_03.png");
    wall_01->modelLocation = (Vector3){0.0f, 0.0f, -15.0f};
    wall_01->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = wall_01->texture;
    models[*lastModelIndex] = wall_01;
    *lastModelIndex = *lastModelIndex + 1;
    //
}
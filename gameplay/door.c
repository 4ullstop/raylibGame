#include "door.h"

void ConstructDoors(modelInfo** dynamicModels, int* lastModelIndex, Door** allDoors)
{
    Door* door_01 = malloc(sizeof(Door));
    door_01->doorModel.collisionDisabled = false;
    door_01->id = 1;
    door_01->location = (Vector3){0.0f, 0.0f, 0.0f};
    door_01->doorModel.modelLocation = door_01->location;
    door_01->doorModel.model = LoadModel("D:/CFiles/FirstGame/models/obj/door.obj");
    door_01->doorModel.texture = LoadTexture("D:/CFiles/FirstGame/models/obj/door.png");
    door_01->doorModel.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = door_01->doorModel.texture;
    dynamicModels[*lastModelIndex] = &door_01->doorModel;
    *lastModelIndex = *lastModelIndex + 1;
    allDoors[0] = &door_01;
}
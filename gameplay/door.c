#include "door.h"
#include <stdlib.h>
#include <stdio.h>

void ConstructDoors(modelInfo** dynamicModels, Texture2D** gameTextures, int* lastModelIndex, Door** allDoors)
{
    Door* door_01 = malloc(sizeof(Door));
    door_01->doorModel.collisionDisabled = false;
    door_01->id = 1;
    door_01->location = (Vector3){0.0f, 0.0f, -13.8f};
    door_01->doorModel.modelLocation = door_01->location;
    door_01->openPosition = (Vector3){door_01->location.x, door_01->location.y - 3.0f, door_01->location.z};
    door_01->closedPosition = door_01->location;
    door_01->speed = 1.0f;
    door_01->isLowering = false;
    door_01->doorModel.model = LoadModel("D:/CFiles/FirstGame/models/obj/door.obj");
    door_01->doorModel.texture = *gameTextures[2];
    door_01->doorModel.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = door_01->doorModel.texture;
    dynamicModels[*lastModelIndex] = &door_01->doorModel;
    *lastModelIndex = *lastModelIndex + 1;
    allDoors[0] = door_01;

    printf("doors constructed\n");
    printf("door on construct %p \n", (void*)&door_01);
    printf("alldoors on construct %p \n", (void*)&allDoors[0]);
}

void PollDoors(Door** allDoors, double deltaTime, int numOfDoors)
{
    for (int i = 0; i < numOfDoors; i++)
    {
        if (allDoors[i]->isLowering == true)
        {
            LowerDoor(allDoors[i], deltaTime);
        }
    }
}

void LowerDoor(Door* door, double deltaTime)
{
    
    if (door->isLowering == true)
    {
        
        if (Vector3Distance(door->location, door->openPosition) > 0.01f)
        {
            Vector3 direction = Vector3Normalize(Vector3Subtract(door->openPosition, door->location));
            door->location = Vector3Add(door->location, Vector3Scale(direction, door->speed * deltaTime));
            door->doorModel.modelLocation = door->location;
        }
        else
        {
            door->location = door->openPosition;
            door->isLowering = false;
        }
    }
}

void DestructAllDoors(Door* allDoors[], int numOfDoors)
{
    // for (int i = 0; i < numOfDoors; i++)
    // {
    //     printf("alldoors %p\n", (void*)&allDoors[i]);
        
    //     free(allDoors[i]);
    //     allDoors[i] = NULL;
    // }
    printf("alldoors %p\n", (void*)&allDoors[0]);

    if (allDoors[0] != NULL)
    {
        free(allDoors[0]);
        allDoors[0] = NULL;
    }
    printf("Destruct complete\n");
}
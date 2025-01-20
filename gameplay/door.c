#include "door.h"
#include <stdlib.h>
#include <stdio.h>
#include "../externmath/externmath.h"

void ConstructDoors(modelInfo** dynamicModels, Texture2D** gameTextures, int* lastModelIndex, Door** allDoors, ExitCode* exitCode)
{
    Door* door_01 = malloc(sizeof(Door));
    if (door_01 == NULL)
    {
	EditReturnCodeInfo(100, "Failed to allocated memory for Door\n", exitCode);
	return;
    }
    door_01->doorModel.collisionDisabled = false;
    door_01->id = 1;
    door_01->location = (Vector3){0.0f, 0.0f, -13.8f};
    door_01->doorModel.modelLocation = door_01->location;
    door_01->doorType = DT_Vertical;
    door_01->openPosition = (Vector3){door_01->location.x, door_01->location.y - 3.0f, door_01->location.z};
    door_01->closedPosition = door_01->location;
    door_01->speed = 1.0f;
    door_01->isLowering = false;
    door_01->doorModel.model = LoadModel("D:/CFiles/FirstGame/models/obj/door.obj");
    exitCode->numOfModelsLoaded = exitCode->numOfModelsLoaded + 1;
    door_01->doorModel.texture = *gameTextures[2];
    door_01->doorModel.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = door_01->doorModel.texture;
    dynamicModels[*lastModelIndex] = &door_01->doorModel;
    *lastModelIndex = *lastModelIndex + 1;
    allDoors[0] = door_01;
    exitCode->numOfDoorsLoaded = exitCode->numOfDoorsLoaded + 1;

    Door* gate = malloc(sizeof(Door));
    if (gate == NULL)
    {
	EditReturnCodeInfo(100, "Failed to allocate memory for Door\n", exitCode);
	return;
    }
    gate->doorModel.collisionDisabled = false;
    gate->id = 2;
    gate->location = (Vector3){0.0f, 0.0f, 0.0f};
    gate->doorModel.modelLocation = gate->location;
    gate->doorType = DT_Hinged;
    gate->hingeOffset = Vector3Subtract(gate->location, (Vector3){1.0f, 0.0f, 0.0f});
    gate->desiredAngle = -90.0f;
    gate->currAngle = 0.0f;
    exitCode->numOfModelsLoaded = exitCode->numOfModelsLoaded + 1;
    gate->doorModel.texture = *gameTextures[9];
    gate->doorModel.model = LoadModel("D:/CFiles/FirstGame/models/obj/gate.obj");
    gate->doorModel.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = gate->doorModel.texture;
    dynamicModels[*lastModelIndex] = &gate->doorModel;
    *lastModelIndex = *lastModelIndex + 1;
    allDoors[1] = gate;
    exitCode->numOfDoorsLoaded = exitCode->numOfDoorsLoaded + 1;
    
    printf("doors constructed\n");
    printf("door on construct %p \n", (void*)&door_01);
    printf("alldoors on construct %p \n", (void*)&allDoors[0]);
}

void ConstructSingleDoor(modelInfo** dynamicModels, Texture2D** gameTextures, int* lastModelIndex, Door** allDoors, ExitCode* exitCode, Vector3 doorLocation, enum DoorType doorType, char* modelFileLocation, int textureIndex, float destVal, float hingeOffset)
{
    Door* door = malloc(sizeof(Door));
    if (door == NULL)
    {
	EditReturnCodeInfo(100, "Failed to allocate memory for door\n", exitCode);
	return;
    }
    door->doorModel.collisionDisabled = false;
    door->id = *lastModelIndex;
    door->location = doorLocation;
    door->doorType = doorType;
    door->doorModel.modelLocation = doorLocation;
    door->speed = 1.0f;
    door->isLowering = false;
    door->doorModel.model = LoadModel(modelFileLocation);
    exitCode->numOfModelsLoaded = exitCode->numOfModelsLoaded + 1;
    door->doorModel.texture = *gameTextures[textureIndex];
    door->doorModel.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = door->doorModel.texture;
    CustomDoorParameters(door, doorType, destVal, hingeOffset);
    *lastModelIndex = *lastModelIndex + 1;
    allDoors[exitCode->numOfDoorsLoaded] = door;
    exitCode->numOfDoorsLoaded = exitCode->numOfDoorsLoaded + 1;
}

void CustomDoorParameters(Door* door, enum DoorType doorType, float value, float hingeOffset)
{
    switch (doorType)
    {
    case DT_Vertical:
	door->openPosition = (Vector3){door->location.x, door->location.y - value, door->location.z};
	door->closedPosition = door->location;
	break;
    case DT_Hinged:
	door->hingeOffset = Vector3Subtract(door->location, (Vector3){hingeOffset, hingeOffset, hingeOffset});
	door->desiredAngle = value;
	door->currAngle = 0.0f;
	break;
    }
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

void SwingDoor(Door* door, double deltaTime)
{
    if (door->isLowering == true)
    {
	if (!(door->desiredAngle == door->currAngle))
	{
	    door->currAngle = door->currAngle + (0.5 * deltaTime);
	    Vector3 newLocation = RotateAroundPoint(door->location, door->hingeOffset, door->currAngle, (Vector3){0.0f, 1.0f, 0.0f});
	    door->doorModel.modelLocation = newLocation;
	    door->location = newLocation;
	    door->doorModel.model.transform = MatrixRotateXYZ((Vector3){0.0f, 1.0f, 0.0f});
	}
	else
	{
	    door->isLowering = false;
	}
    }
}


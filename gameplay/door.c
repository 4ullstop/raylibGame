#include "door.h"
#include <stdlib.h>
#include <stdio.h>
#include "../externmath/externmath.h"

void ConstructSingleDoor(modelInfo** dynamicModels, Texture2D** gameTextures, int* lastModelIndex, Door** allDoors, ExitCode* exitCode, Vector3 doorLocation, enum DoorType doorType, char* modelFileLocation, int textureIndex, float destVal, float hingeOffset, int* lastDoorIndex)
{
    Door* door = malloc(sizeof(Door));
    if (door == NULL)
    {
	EditReturnCodeInfo(100, "Failed to allocate memory for door\n", exitCode);
	return;
    }
    door->doorModel.collisionDisabled = false;
    door->doorModel.modelVisible = true;
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
    dynamicModels[*lastModelIndex] = &door->doorModel;
    *lastModelIndex = *lastModelIndex + 1;
    
    allDoors[*lastDoorIndex] = door;
    *lastDoorIndex = *lastDoorIndex + 1;
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
    default:
	printf("ERROR DEFAULT RUN CUSTOMDOORPARAMETERS\n");
    }
}

void PollDoors(Door** allDoors, double deltaTime, int numOfDoors)
{
    for (int i = 0; i < numOfDoors; i++)
    {
        if (allDoors[i]->isLowering == true)
        {
	    if (allDoors[i]->doorType == DT_Vertical)
	    {
		LowerDoor(allDoors[i], deltaTime);
	    }
	    else
	    {
		SwingDoor(allDoors[i], deltaTime);
	    }
	    
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
	float angleR = (int)(door->currAngle * 100 + .5);
	angleR /= 100;
	if (!( 1.4f == angleR))
	{
	    door->currAngle = door->currAngle + (0.5 * deltaTime);
	    door->doorModel.modelLocation = door->location;
      	    door->doorModel.model.transform = MatrixRotateXYZ((Vector3){0.0f, 1.0f * door->currAngle, 0.0f});
	}
	else
	{
	    door->isLowering = false;
	}
    }
}


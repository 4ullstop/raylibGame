#include "gameadoors.h"
#include "../gameplay/door.h"

void ConstructGameADoors(modelInfo** dynamicModels, Texture2D** gameATextures, int* lastModelIndex, Door** allDoors, ExitCode* exitCode)
{
    int lastDoorIndex = 0;
	
    ConstructSingleDoor(dynamicModels,
			gameATextures,
			lastModelIndex,
			allDoors,
			exitCode,
			(Vector3){6.3f, -0.8f, -35.9f},
			DT_Hinged,
			"D:/CFiles/FirstGame/models/obj/gate.obj",
			9,
			90.0f,
			0.5f,
			&lastDoorIndex);

    ConstructSingleDoor(dynamicModels,
			gameATextures,
			lastModelIndex,
			allDoors,
			exitCode,
			(Vector3){-12.3f, 0.0f, 16.65f},
			DT_Hinged,
			"D:/CFiles/FirstGame/models/obj/gate_03.obj",
			9,
			90.0f,
			0.5f,
			&lastDoorIndex);

    ConstructSingleDoor(dynamicModels,
			gameATextures,
			lastModelIndex,
			allDoors,
			exitCode,
			(Vector3){10.5f, -10.0f, 3.0f},
			DT_Hinged,
			"D:/CFiles/FirstGame/models/obj/lighthousedoor.obj",
			9,
			90.0f,
			0.5f,
			&lastDoorIndex);

    
}

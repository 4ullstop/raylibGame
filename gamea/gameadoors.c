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
			(Vector3){0.0f, 0.0f, -13.8f},
			DT_Vertical,
			"D:/CFiles/FirstGame/models/obj/door.obj",
			2,
			3.0f,
			0.0f,
			&lastDoorIndex);
	
    ConstructSingleDoor(dynamicModels,
			gameATextures,
			lastModelIndex,
			allDoors,
			exitCode,
			(Vector3){6.5f, -0.4f, -34.85f},
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
			(Vector3){-3.45f, 0.0f, -4.0f},
			DT_Hinged,
			"D:/CFiles/FirstGame/models/obj/gate_02.obj",
			9,
			90.0f,
			0.5f,
			&lastDoorIndex);
    
}

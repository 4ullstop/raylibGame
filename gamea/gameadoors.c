#include "gameadoors.h"
#include "../gameplay/door.h"

void ConstructGameADoors(modelInfo** dynamicModels, Texture2D** gameATextures, int* lastModelIndex, Door** allDoors, ExitCode* exitCode)
{
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
			0.0f);
	
    ConstructSingleDoor(dynamicModels,
			gameATextures,
			lastModelIndex,
			allDoors,
			exitCode,
			(Vector3){6.5f, -0.4f, -36.85f},
			DT_Hinged,
			"D:/CFiles/FirstGame/models/obj/gate.obj",
			9,
			-90.0f,
			1.0f);
    
}

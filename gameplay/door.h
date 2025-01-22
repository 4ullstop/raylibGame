#ifndef DOOR_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "../initialization/corestructs.h"
#endif

void LowerDoor(Door* door, double deltaTime);

void PollDoors(Door** allDoors, double deltaTime, int numOfDoors);

void ConstructSingleDoor(modelInfo** dynamicModels, Texture2D** gameTextures, int* lastModelIndex, Door** allDoors, ExitCode* exitCode, Vector3 doorLocation, enum DoorType doorType, char* modelFileLocation, int textureIndex, float destVal, float hingeOffset, int* lastDoorIndex);

void CustomDoorParameters(Door* door, enum DoorType doorType, float value, float hingeOffset);

void SwingDoor(Door* door, double deltaTime);

void UpdateSwingCollision(modelInfo* model, Door* door);

Vector3 GetModelVertex(Model* model, int i);

void EditModelVertex(Vector3 newVertex, Model* model, int i);

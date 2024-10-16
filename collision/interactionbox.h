#ifndef RAYLIB_CAMERA_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "../initialization/corestructs.h"
#endif

Interactable* ConstructInteractable(Vector3 location, ColBox* box, float boxSize);

void DestructInteractable(Interactable* interactable);

bool IsPointInInteractable(Interactable* interactable, Vector3 point);

ColBox* ConstructColBox(Vector3 location, float width, float height, float length);

void DestructColBox(ColBox* box);
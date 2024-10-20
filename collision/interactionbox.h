#ifndef RAYLIB_CAMERA_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "../initialization/corestructs.h"
#endif

void ConstructInteractable(Interactable* interactable, Vector3 location, ColBox* box, float boxWidth, float boxHeight, float boxLength);

void DestructInteractable(Interactable* interactable);

bool IsPointInInteractable(Interactable* interactable, Vector3 point);

void ConstructColBox(ColBox* box, Vector3 location, float width, float height, float length);

void DestructColBox(ColBox* box);
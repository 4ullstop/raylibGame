#ifndef RAYLIB_CAMERA_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "../initialization/corestructs.h"
#include "../gameplay/gameplaystructs.h"
#endif

void ConstructInteractable(Interactable* interactable, Vector3 location, ColBox* box, float boxWidth, float boxHeight, float boxLength);

void DestructInteractable(Interactable* interactable);

bool IsPointInInteractable(Interactable* interactable, Vector3 point);

void ConstructColBox(ColBox* box, Vector3 location, float width, float height, float length);

void DestructColBox(ColBox* box);

void InteractionBoxInteract(void);

void CreatePlayerAreaQueries(QueryBox** areaQueryBoxes);

void CreateInteractables(Interactable** interactables, QueryBox** areaQueryBoxes, ButtonMaster** allPuzzles);

void DestroyAreasAndInteractables(QueryBox** areaQueryBoxes);

void NullifyColBoxValues(ColBox* box);

void AssignInteractionBoxToPuzzle(ButtonMaster** master, Interactable* interactable);
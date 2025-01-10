#ifndef RAYLIB_CAMERA_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "../initialization/corestructs.h"
#include "../gameplay/gameplaystructs.h"
#include "externcollision.h"
#include "../gamea/gameaqueryboxes.h"
#include "../gameb/gamebqueryboxes.h" 
#endif

void ConstructInteractable(Interactable* interactable, Vector3 location, ColBox* box, float boxWidth, float boxHeight, float boxLength, Vector3 locOffset, ExitCode* exitCode);

bool IsPointInInteractable(Interactable* interactable, Vector3 point);

void PuzzleInteract(FPSPlayer* player, ColBox* box);

void CreatePlayerAreaQueries(QueryBox** areaQueryBoxes, enum Gametype gametype, ExitCode* exitCode);

void CreateInteractables(Interactable** interactables, QueryBox** areaQueryBoxes, ButtonMaster** allPuzzles);

void NullifyColBoxValues(ColBox* box);

void ConstructSingleInteractable(int* lastInteractableIndex, enum InteractableType puzzleType, bool showArrowKeyHint, float len, float width, float height, ButtonMaster* assignedPuzzle, void(*colBoxInteract)(FPSPlayer*, ColBox*), Interactable** interactables, QueryBox** areaQueryBox, int areaQueryBoxId, Vector3 locOffset, ExitCode* exitCode);


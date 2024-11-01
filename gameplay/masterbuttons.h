#ifndef RAYLIB_CAMERA_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "gameplaystructs.h"
#include "../initialization/corestructs.h"
#endif

void CreateAllButtons(ButtonMaster* master, modelInfo** dynamicModels, int* lastModelIndex);

void ConstructSingleButton(ButtonMaster* master, int i, int j, int* lastModelIndex, modelInfo** dynamicModels);

void DestructAllButtons(ButtonMaster* master);

//void AssignInteractBoxesToPuzzle(Interactable** interactables, ButtonMaster** master);

void ConstructPuzzles(ButtonMaster** allPuzzles, modelInfo** dynamicModels, int* lastModelIndex);

void DestructAllPuzzles(ButtonMaster** allPuzzles);

//void SetupInteractBoxForPuzzle(ButtonMaster* master);

void PuzzleInteract(void);

void MoveCursor(enum Direction direction, Interactable* interactedItem);

void RemoveHighlight(Button* button);

void AddHighlight(Button* button);
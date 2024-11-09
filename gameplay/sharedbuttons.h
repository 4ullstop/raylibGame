#ifndef GAMEAPUZZLES_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "../initialization/corestructs.h"
#include "../externmath/externmath.h"
#endif

void CreateAllButtons(ButtonMaster* master, modelInfo** dynamicModels, int* lastModelIndex);

void ConstructSingleButton(ButtonMaster* master, int i, int j, int* lastModelIndex, modelInfo** dynamicModels);

void AddHighlight(Button* button);

void RotateButtonMaster(ButtonMaster* master, float angle, Vector3 axis);

void OnPuzzleCompleted(ButtonMaster* master);

void AssignGameplayElementsToPuzzles(ButtonMaster* puzzle, Door* door);

void InactGameplayElement(GameplayElements* gameplayElement);
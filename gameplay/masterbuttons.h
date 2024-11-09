#ifndef RAYLIB_CAMERA_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "gameplaystructs.h"
#include "../initialization/corestructs.h"
#include "../filereading/filereader.h"
#include "../externmath/externmath.h"
#include "../gamea/gameapuzzles.h"
#include "../gameb/gamebpuzzles.h"
#include "sharedbuttons.h"
#endif

//void CreateAllButtons(ButtonMaster* master, modelInfo** dynamicModels, int* lastModelIndex);

//void ConstructSingleButton(ButtonMaster* master, int i, int j, int* lastModelIndex, modelInfo** dynamicModels);

void DestructAllButtons(ButtonMaster* master);

void ConstructPuzzles(ButtonMaster** allPuzzles, modelInfo** dynamicModels, int* lastModelIndex, enum Gametype gametype, FPSPlayer* player, GameplayElements* gameplayElements);

void DestructAllPuzzles(ButtonMaster** allPuzzles, int numberOfPuzzles);

void DestructAllSolutionLocations(ButtonMaster* master);

void MoveCursor(enum Direction direction, Interactable* interactedItem, enum Gamemode* mode);

void RemoveHighlight(Button* button);

//void AddHighlight(Button* button);

void ChangeSelection(Button* button);

void CheckForSolution(Button* button, ButtonMaster* master, enum Gamemode* mode);

void RotateButtonMaster(ButtonMaster* master, float angle, Vector3 axis);


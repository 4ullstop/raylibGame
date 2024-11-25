#ifndef RAYLIB_CAMERA_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "gameplaystructs.h"
#include "../initialization/corestructs.h"
#include "../filereading/filereader.h"
#include "../externmath/externmath.h"
#include "../gamea/gameapuzzles.h"
#include "../gameb/gamebpuzzles.h"
#include "gameplayelements.h"
#include "sharedbuttons.h"
#endif

void DestructAllButtons(ButtonMaster* master);

void ConstructPuzzles(ButtonMaster** allPuzzles, modelInfo** dynamicModels, int* lastModelIndex, enum Gametype gametype, FPSPlayer* player, GameplayElements* gameplayElements, Texture2D** allTextures);

void DestructAllPuzzles(ButtonMaster** allPuzzles, int numberOfPuzzles);

void DestructAllSolutionLocations(ButtonMaster* master);

void MoveCursor(enum Direction direction, Interactable* interactedItem, enum Gamemode* mode);

void RemoveHighlight(Button* button);

void ChangeSelection(Button* button);

void CheckForSolution(Button* button, ButtonMaster* master, enum Gamemode* mode);

void RotateButtonMaster(ButtonMaster* master, float angle, Vector3 axis);

void ResetPuzzle(ButtonMaster* puzzle, bool resultOfFailure);

Button* PushCursor(Button* button);

void PollPuzzles(ButtonMaster* puzzle, TickNode* tickNode);

void BlinkCursor(ButtonMaster* puzzle, TickNode* tickNode);
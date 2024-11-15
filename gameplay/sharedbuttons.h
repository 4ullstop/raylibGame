#ifndef GAMEAPUZZLES_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "../initialization/corestructs.h"
#include "../externmath/externmath.h"
#include "puzzles/togglepuzzle.h"
#endif

void CreateAllButtons(ButtonMaster* master, modelInfo** dynamicModels, int* lastModelIndex, Texture2D** allTextures);

void ConstructSingleButton(ButtonMaster* master, int i, int j, int* lastModelIndex, modelInfo** dynamicModels, Texture2D** allTextures);

void AddHighlight(Button* button);

void RotateButtonMaster(ButtonMaster* master, float angle, Vector3 axis);

void OnPuzzleCompleted(ButtonMaster* master);

void AssignGameplayElementsToPuzzles(ButtonMaster* puzzle, Door* door);

void InactGameplayElement(GameplayElements* gameplayElement);

void ConstructSinglePuzzle(int* lastPuzzleIndex, int columns, int rows, Vector3 location, FPSPlayer* player, void(*puzzleLocConstruct)(ButtonMaster*), bool hasGameplayElements, GameplayElements* gameplayElements, ButtonMaster** gameAPuzzles, Vector2Int highlightStart, bool hasHighlightStartLoc, enum PuzzleState puzzleState);

void EnactButton(Button* button);

void SwitchTextureOnPuzzleState(ButtonMaster* puzzle, Button* button, bool isHighlightedButton);

void PowerOnPuzzle(ButtonMaster* puzzle);
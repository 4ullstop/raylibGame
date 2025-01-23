#ifndef GAMEAPUZZLES_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "../initialization/corestructs.h"
#include "../externmath/externmath.h"
#include "puzzles/togglepuzzle.h"
#include "../models/src/buttonatlas.h"
#endif

void CreateAllButtons(ButtonMaster* master, modelInfo** dynamicModels, int* lastModelIndex, Texture2D** allTextures, ExitCode* exitCode);

void ConstructSingleButton(ButtonMaster* master, int i, int j, int* lastModelIndex, modelInfo** dynamicModels, Texture2D** allTextures, ExitCode* exitCode);

void AddHighlight(Button* button);

void RotateButtonMaster(ButtonMaster* master, float angle, Vector3 axis);

void OnPuzzleCompleted(ButtonMaster* master);

void AssignGameplayElementsToPuzzles(ButtonMaster* puzzle, GameplayElements* gameplayElements, enum GameplayElementType gameplayElementType, int gameplayElementIndex);

void InactGameplayElement(GameplayElements* gameplayElement);

void ConstructSinglePuzzle(int* lastPuzzleIndex, int columns, int rows, Vector3 location, FPSPlayer* player, void(*puzzleLocConstruct)(ButtonMaster*), enum GameplayElementType gameplayElementType, GameplayElements* gameplayElements, int gameplayElementIndex, ButtonMaster** gameAPuzzles, Vector2Int highlightStart, bool hasHighlightStartLoc, enum PuzzleState puzzleState, float buttonSpread, bool sharedPuzzle, bool gameA, Vector3 puzzleLerpOffset, ExitCode* exitCode);

void EnactButton(Button* button);

void SwitchTextureOnPuzzleState(ButtonMaster* puzzle, Button* button, bool isHighlightedButton);

void PowerOnPuzzle(ButtonMaster* puzzle);

void AssignAllPuzzlesNormals(ButtonMaster** allPuzzles, int numOfPuzzles);

Vector3 CalculatePuzzleNormal(ButtonMaster* puzzle);

void AssignButtonSpecialTextureAndAction(Button* button, enum TextureCoordinateLocations textureLocations);

void AssignSolutionsTextures(ButtonMaster* puzzle);

void DetermineAndUpdateTexture(Button* button, enum ButtonState state);

void DetermineStartVal(int* min, enum PuzzleOnOffDirection direction);

void AssignAllPuzzlesSolutionButtons(ButtonMaster** allPuzzles, int numOfPuzzles, ExitCode* exitCode);

void AssignSolutionButtonsToPuzzle(ButtonMaster* puzzle, ExitCode* exitCode);

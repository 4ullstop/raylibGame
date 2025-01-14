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
#include "../shared/sharedstructs.h"
#endif

void ConstructPuzzles(ButtonMaster** allPuzzles, modelInfo** dynamicModels, int* lastModelIndex, enum Gametype gametype, FPSPlayer* player, GameplayElements* gameplayElements, Texture2D** allTextures, SharedMemory* sharedMemory, ExitCode* exitCode);

void MoveCursor(enum Direction direction, Interactable* interactedItem, enum Gamemode* mode, OpenSharedValues* openSharedValues, bool isPlayerSharingPuzzle);

void RemoveHighlight(Button* button);

void ChangeSelection(Button* button, ButtonMaster* puzzle);

void CheckForSolution(Button* button, ButtonMaster* master, enum Gamemode* mode);

void RotateButtonMaster(ButtonMaster* master, float angle, Vector3 axis);

void ResetPuzzle(ButtonMaster* puzzle, bool resultOfFailure);

Button* PushCursor(Button* button, ButtonMaster* master);

void PollPuzzles(ButtonMaster* puzzle, TickNode* tickNode);

void BlinkCursor(ButtonMaster* puzzle, TickNode* tickNode);

void RunThroughErrorButtons(ButtonMaster* puzzle, TickNode* tickNode, ErrorButtons* errorButtons);

bool BlinkError(Button* button, TickNode* tickNode);

void AddItemToSolvedButtonList(SolvedButtons** head, enum ButtonTextureSizes textureSizesToAdd);

void RemoveItemToSolvedButtonList(SolvedButtons** head, enum ButtonTextureSizes buttonToRemove);

void ClearSolvedButtons(SolvedButtons* solvedButtons);

void AddButtonToErrorList(Button* button, ErrorButtons** errorButton);

bool PushedCheckForEdges(Button* button);

void PuzzleCompleted(ButtonMaster* puzzle);

bool SubmitButton(Button* button, ButtonMaster* puzzle);

void UnsubmitButton(Button* button, ButtonMaster* puzzle, bool isFromAuto);

void AddPlainButtonToSubmittedList(Button* buttonToAdd, PlainSubmittedButtons** head, ButtonMaster* puzzle);

void RemoveHead(PlainSubmittedButtons** head, ButtonMaster* puzzle);

void HandleCursorMovement(Button* currSelectedButton, Button* newButton, ButtonMaster* puzzle, OpenSharedValues* openSharedValues, bool isConsumer, bool isSharedPuzzle);

void PollConsumer(OpenSharedValues* openSharedValues, ButtonMaster* puzzle, enum Gamemode* mode);

Button* FindCursoredButton(ButtonMaster* puzzle);

Button* HandleCursorSelection(Button* currSelectedButton, ButtonMaster* puzzle, enum Gamemode* gameMode, bool isSharedPuzzle, bool isConsumer, OpenSharedValues* openSharedValues);

void SharedButtonNeighborDetermination(Button** leftCurrSelected, Button** rightCurrSelected, Button** aboveCurrSelected, Button** belowCurrSelected, Button* currSelectedButton, ButtonMaster* puzzle);

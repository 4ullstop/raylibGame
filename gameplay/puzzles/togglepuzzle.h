#ifndef TOGGLE_PUZZLE_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "../../initialization/corestructs.h"
#endif

void EnactToggle(Button* button);

void ToggleNeighbors(Button* button, Vector2Int direction);

void ToggleCurrButton(Button* currButton, int ogId);

void AssignButtonToToggleAction(Button* button);

Button* GetNextButton(Button* next, Vector2Int direction);

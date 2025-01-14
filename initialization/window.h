#ifndef RAYLIB_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "corestructs.h"
#endif


void CreateWindow(const int screenWidth, const int screenHeight, const char* title);

void SetWindowLocationForGameType(enum Gametype gametype);

void MoveWindowFromPuzzle(int units, bool leftRight);
/*

HWND FindWindowByTitle(const char* windowTitle);

bool SwitchToWindow(const char* windowTitle);
*/

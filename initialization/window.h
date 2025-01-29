#pragma once

#ifndef RAYLIB_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "corestructs.h"
#include "windowstructs.h"
#endif


void CreateWindow(const int screenWidth, const int screenHeight, const char* title, WindowData* windowData);

void SetWindowLocationForGameType(enum Gametype gametype, WindowData* windowData);

void MoveWindowFromPuzzle(int units, bool leftRight);

void PollWindow(double deltaTime, WindowData* windowData);

void LerpWindowLocation(WindowData* windowData, double deltaTime);
    

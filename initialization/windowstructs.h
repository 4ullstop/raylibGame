#pragma once

#ifndef WINDOW_STRUCT_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "corestructs.h"
#endif

#ifndef WINDOW_STRUCT
#define WINDOW_STRUCT
typedef struct WindowData
{
    Vector2 windowStartLoc;
    Vector2 windowCurrLoc;
    Vector2 windowGoalLoc;

    bool shouldPollWindow;

    bool isWindowA;

    void (*SetupWindowMovement)(enum Gametype gametype, struct WindowData* windowData);
} WindowData;
#endif

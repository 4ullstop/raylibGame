#include "window.h"
#include <stdio.h>

void CreateWindow(const int screenWidth, const int screenHeight)
{
    InitWindow(screenWidth, screenHeight, "Game");
}

void SetWindowLocationForGameType(enum Gametype gametype)
{
    int screenWidth = GetMonitorWidth(GetCurrentMonitor());
    int screenHeight = GetMonitorHeight(GetCurrentMonitor());

    int midpointX = screenWidth / 2;
    int midpointY = screenHeight / 2;

    int windowW = 800;
    int windowH = 450;

    int locX = 0, locY = 0;
    
    if (gametype == EGT_A)
    {
	locX = midpointX - windowW;
    }
    else
    {
	locX = midpointX;
    }
    locY = midpointY - (windowH / 2);

    SetWindowPosition(locX, locY);

    printf("screenWidth: %i, screenHeight: %i\n", screenWidth, screenHeight);
    printf("midpointX: %i, midpointY: %i\n", midpointX, midpointY);
    printf("locX: %i, locY: %i\n", locX, locY);
}

#include "window.h"
#include <stdio.h>
#include "processthreadsapi.h"

void CreateWindow(const int screenWidth, const int screenHeight, const char* title, WindowData* windowData)
{
    InitWindow(screenWidth, screenHeight, title);
    windowData->SetupWindowMovement = SetWindowLocationForGameType;
    windowData->windowGoalLoc = (Vector2){0.0f, 0.0f};
    windowData->windowCurrLoc = (Vector2){0.0f, 0.0f};
    windowData->shouldPollWindow = false;
}

void SetWindowLocationForGameType(enum Gametype gametype, WindowData* windowData)
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
	windowData->isWindowA = true;
    }
    else
    {
	locX = midpointX;
	windowData->isWindowA = false;
    }
    locY = midpointY - (windowH / 2);

//    SetWindowPosition(locX, locY);

    windowData->windowGoalLoc.x = locX;
    windowData->windowGoalLoc.y = locY;

    windowData->windowCurrLoc = GetWindowPosition();
    
    windowData->shouldPollWindow = true;
    
    printf("screenWidth: %i, screenHeight: %i\n", screenWidth, screenHeight);
    printf("midpointX: %i, midpointY: %i\n", midpointX, midpointY);
    printf("locX: %i, locY: %i\n", locX, locY);
}

void MoveWindowFromPuzzle(int units, bool leftRight)
{
    Vector2 windowLoc = GetWindowPosition();

    
    
    if (leftRight == true)
    {
	windowLoc.x = windowLoc.x + units;
	printf("window loc x: %f\n", windowLoc.x);
    }
    else
    {
	windowLoc.y = windowLoc.y + units;
	printf("window loc y: %f\n", windowLoc.y);
    }
    SetWindowPosition((int)windowLoc.x, (int)windowLoc.y);
}

void PollWindow(double deltaTime, WindowData* windowData)
{
    if (windowData->shouldPollWindow == true)
    {
	LerpWindowLocation(windowData, deltaTime);
    }
}

void LerpWindowLocation(WindowData* windowData, double deltaTime)
{
    printf("curr loc: %f, %f\n", windowData->windowCurrLoc.x, windowData->windowCurrLoc.y);
    printf("curr goal: %f, %f\n", windowData->windowGoalLoc.x, windowData->windowGoalLoc.y);


    float speed = 500.0f;
    if (windowData->isWindowA == true)
    {
	if((int)windowData->windowCurrLoc.x <= (int)windowData->windowGoalLoc.x)
	{
	    windowData->shouldPollWindow = false;
	    SetWindowPosition((int)windowData->windowGoalLoc.x, (int)windowData->windowGoalLoc.y);
	    return;
	}
	windowData->windowCurrLoc.x -= speed * deltaTime;
    }
    else
    {
	if ((int)windowData->windowCurrLoc.x >= (int)windowData->windowGoalLoc.x)
	{
	    windowData->shouldPollWindow = false;
	    SetWindowPosition((int)windowData->windowGoalLoc.x, (int)windowData->windowGoalLoc.y);
	    return;
	}
	windowData->windowCurrLoc.x += speed * deltaTime;
    }

    SetWindowPosition((int)windowData->windowCurrLoc.x, (int)windowData->windowCurrLoc.y);
}

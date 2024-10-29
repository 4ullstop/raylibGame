#pragma once

#ifndef RAYLIB_CAMERA_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "../initialization/corestructs.h"
#endif

#ifndef VECTOR_2_INT
#define VECTOR_2_INT
typedef struct 
{
    int x;
    int y;
} Vector2Int;
#endif

#ifndef BUTTON
#define BUTTON
typedef struct Button
{
    Vector3 location;
    bool solutionButton;
    bool highlighted;
    bool submitted;

    Vector2Int buttonVectorLocation;

    modelInfo* model;

    //n(direction) (aka neighbor(direction))
    struct Button* nLeft;
    struct Button* nRight;
    struct Button* nAbove;
    struct Button* nBelow;
} Button;
#endif

#ifndef MASTER_OF_BUTTONS
#define MASTER_OF_BUTTONS
typedef struct ButtonMaster
{
    Button** childButtons;
    
    unsigned int rows;
    unsigned int columns;

    Vector2Int highlightLocation;
    unsigned int totalButtons;
    bool solved;

    Vector3 location;

    float buttonSpread;
} ButtonMaster;
#endif
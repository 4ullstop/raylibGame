#pragma once
#ifndef DRAWING_STRUCTS_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#endif


#ifndef DRAWLINE
#define DRAWLINE
typedef struct Drawline
{
    Vector3 start;
    Vector3 end;
    Color color;

    Vector3 hitpoint;

    struct Drawline* next;
} Drawline;
#endif
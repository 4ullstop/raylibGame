#pragma once

#ifndef RAYLIB_COLLISION_HEAD
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#endif

typedef struct CPlane
{
    Vector3 origin;
    Vector3 normal;

    float equation[4];

} CPlane;

void ConstructCPlane(CPlane* plane, Vector3 inOrigin, Vector3 inNormal);

void ConstructFromTriangle(CPlane* plane, Vector3 p1, Vector3 p2, Vector3 p3);

bool IsFrontFacingTo(CPlane* plane, Vector3 direction);

double SignedDistanceToPlane(CPlane* plane, Vector3 point);

bool CheckPointInTriangle(Vector3 point, Vector3 pa, Vector3 pb, Vector3 pc);

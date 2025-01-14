#ifndef EXTERN_MATH_HEADER
#define EXTERN_MATH_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "../initialization/corestructs.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "../collision/collisionplane.h"
#include "../collision/externcollision.h"
#endif

bool IsPointInColBox(ColBox* box, Vector3 point);

Vector3 RotateAroundPoint(Vector3 point, Vector3 origin, float angle, Vector3 axis);

bool IsPointInDistanceTo(Vector3 pointA, Vector3 pointB, float distanceToObject);

float ComputeAngleBetweenVectors(Vector3 v1, Vector3 v2);

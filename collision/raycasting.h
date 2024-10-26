#ifndef RAYCAST_HEADER
#define RAYCAST_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "../initialization/corestructs.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "collisionplane.h"
#include "externcollision.h"
#include "../libs/drawingstructs.h"
#endif

bool CastRayLine(FPSPlayer* player, Vector3 camForward, Raycast* ray, ColBox* allLocalBoxes);

bool HitDetected(Vector3 start, Vector3 end, Raycast* ray, ColBox* allLocalBoxes);

void DrawNewLine(Raycast* ray, Vector3 start, Vector3 end);

void DestroyLines(Drawline* line);
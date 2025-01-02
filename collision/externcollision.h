#ifndef EXTERN_COLLISION_HEADER
#define EXTERN_COLLISION_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "../initialization/corestructs.h"
#endif

void GetVertsForIndexedMesh(float* allVerts, unsigned short* indices, int i, Vector3* v1, Vector3* v2, Vector3* v3);
void GetVertsForNonIndexedMesh(float* allVerts, int i, Vector3* v1, Vector3* v2, Vector3* v3);
bool SetT(float normalDotComparison, float signedDistToPlane, bool* embeddedInPlane, double* t0, double* t1);
void CheckVertice(Vector3 vector, Vector3 base, float* t, Vector3 vertex, bool* foundCollision, Vector3* collisionPoint);
void CheckEdge(Vector3 p1, Vector3 p2, Vector3 base, Vector3 vector, float* t, bool* foundCollision, Vector3* collisionPoint);
bool GetLowestRoot(float a, float b, float c, float maxR, float* root);

void ConstructColBox(ColBox* box, Vector3 location, float width, float height, float length, ExitCode* exitCode);

void InteractionBoxInteract(FPSPlayer* player, ColBox* box);

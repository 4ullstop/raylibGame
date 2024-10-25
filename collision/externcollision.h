#ifndef RAYLIB_CAMERA_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#endif

void GetVertsForIndexedMesh(float* allVerts, unsigned short* indices, int i, Vector3* v1, Vector3* v2, Vector3* v3);
void GetVertsForNonIndexedMesh(float* allVerts, int triCount, Vector3* v1, Vector3* v2, Vector3* v3);
bool SetT(float normalDotComparison, float signedDistToPlane, bool* embeddedInPlane, double* t0, double* t1);
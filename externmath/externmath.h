#ifndef RAYLIB_CAMERA_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "../initialization/corestructs.h"
#include "C:\raylib\raylib\src\raymath.h"
#endif

bool IsPointInColBox(ColBox* box, Vector3 point);

void FaceFromIndexedColBox(Vector3* v1, Vector3* v2, Vector3* v3, ColBox* box, int i);

bool CompareMatrix(Vector3 transformedVector);
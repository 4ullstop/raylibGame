#ifndef RAYLIB_CAMERA_HEAD
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#endif

typedef struct CollisionPacket
{
    //ellipsoid radius
    Vector3 eRadius; 

    //information need of the player in R3
    Vector3 R3Velocity;
    Vector3 R3Position; 

    //information needed for detection converted to eSpace
    Vector3 velocity;
    Vector3 normalizedVelocity;
    Vector3 basePoint;

    //Hit information
    bool foundCollision;
    double nearestDistance;
    Vector3 intersectionPoint;

    int collisionRecursionDepth;

} CollisionPacket;



Vector3 ConvertVecToEllipsoid(Vector3 r3Vector, Vector3 eRadius);

void CheckTriangle(CollisionPacket* collPacket, Vector3 p1, Vector3 p2, Vector3 p3);

void PollCollision(CollisionPacket* collPacket, Mesh* mesh);

bool GetLowestRoot(float a, float b, float c, float maxR, float* root);
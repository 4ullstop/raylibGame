#include "collisionplane.h"
#include <stdint.h>
#include <stdio.h>

#define in(a) (*(uint32_t*)&(a))

void ConstructCPlane(CPlane* plane, Vector3 inOrigin, Vector3 inNormal)
{
    plane->origin = inOrigin;
    plane->normal = inNormal;

    plane->equation[0] = inNormal.x;
    plane->equation[1] = inNormal.y;
    plane->equation[2] = inNormal.z;
    plane->equation[3] = -(inNormal.x * inOrigin.x + inNormal.y * inOrigin.y + inNormal.z * inOrigin.z);
}

void ConstructFromTriangle(CPlane* plane, Vector3 p1, Vector3 p2, Vector3 p3)
{
    // Vector3 v1 = Vector3Subtract(p2, p1);
    // Vector3 v2 = Vector3Subtract(p3, p1);
    plane->normal = Vector3CrossProduct(Vector3Subtract(p2, p1), Vector3Subtract(p3, p1));

    plane->normal = Vector3Normalize(plane->normal);

    plane->origin = p1;

    plane->equation[0] = plane->normal.x;
    plane->equation[1] = plane->normal.y;
    plane->equation[2] = plane->normal.z;
    plane->equation[3] = -(plane->normal.x * plane->origin.x + plane->normal.y * plane->origin.y + plane->normal.z * plane->origin.z);
}

bool IsFrontFacingTo(CPlane* plane, Vector3 direction)
{
    
    double dot = Vector3DotProduct(plane->normal, direction);
    //printf("Dot: %f\n", dot);
    return (dot <= 0);
}

double SignedDistanceToPlane(CPlane* plane, Vector3 point)
{
    //This is our equation: SignedDistance(p) = N (dot) p + PlaneConstant
    return (Vector3DotProduct(point, plane->normal) + plane->equation[3]);
}

bool CheckPointInTriangle(Vector3 point, Vector3 pa, Vector3 pb, Vector3 pc)
{
    //uhh yeah this function does some magic that I don't understand 
    //all ik it does what the name implies to see if a point is in a triangle
    Vector3 e10 = Vector3Subtract(pb, pa);
    Vector3 e20 = Vector3Subtract(pc, pa);

    float a = Vector3DotProduct(e10, e10);
    float b = Vector3DotProduct(e10, e20);
    float c = Vector3DotProduct(e20, e20);
    float ac_bb = (a * c) - (b * b);

    Vector3 vp = {point.x - pa.x, point.y - pa.y, point.z - pa.z};

    float d = Vector3DotProduct(vp, e10);
    float e = Vector3DotProduct(vp, e20);
    float x = (d * c) - (e * b);
    float y = (e * a) - (d * b);
    float z = x + y - ac_bb;

    return (( in(z))& ~(in(x) | in(y)) & 0x80000000);
}

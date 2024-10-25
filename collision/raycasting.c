#include "raycasting.h"
#include <stddef.h>

bool CastRayLine(FPSPlayer* player, Raycast* ray, ColBox* allLocalBoxes)
{
    Vector3 start = player->location;
    Vector3 end = Vector3Add(start, Vector3Scale(player->attachedCam->target, ray->rayLength));
    bool hit = HitDetected(start, end, ray, allLocalBoxes);
    return hit;
}

bool HitDetected(Vector3 start, Vector3 end, Raycast* ray, ColBox* allLocalBoxes)
{
    for (int i = 0, n = allLocalBoxes->vertsNum; i < n; i++)
    {
        Vector3 v1, v2, v3;
        GetVertsForIndexedMesh(allLocalBoxes->verts, allLocalBoxes->indices, i, &v1, &v2, &v3);

        Vector3 normal = Vector3CrossProduct(Vector3Subtract(v2, v1), Vector3Subtract(v3, v1));

        double t0, t1;

        double equationVal = -(normal.x * v1.x + normal.y * v1.y + normal.z * v1.z);
        double signedDistToTrianglePlane = Vector3DotProduct(start, normal) + equationVal;

        float normalDotEnd = Vector3DotProduct(normal, end);

        if (!SetT(normalDotEnd, signedDistToTrianglePlane, NULL, &t0, &t1))
        {
            continue;
        }
        
        bool foundCollision = false;

        Vector3 intersectionPoint = Vector3Add(start, Vector3Scale(end, t1));

        if (CheckPointInTriangle(intersectionPoint, v1, v2, v3))
        {
            ray->hitLocation = intersectionPoint;
            allLocalBoxes->interact();
            return true;
        }
    }
    return false;
}
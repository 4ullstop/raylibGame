#include "externmath.h"
#include <stdlib.h>
#include <stdio.h>

/*
    I'm using the same algorithm of checking lines and triangles as I did with 
    detecting player collision https://www.peroxide.dk/papers/collision/collision.pdf
*/

bool IsPointInColBox(ColBox* box, Vector3 point)
{
    int intersectionCount = 0;

    if (box->showDebug)
    {
        box->randDirectionDebug = malloc(sizeof(Vector3) * 12);
        box->cubeVertsDebug = malloc(sizeof(Vector3) * 8);
        box->debugPoint = point;
        box->cubeVertsSize = 36;
        box->randDirectionSize = 12;
    }

    int debugStartingIndex = 0;

    Vector3 randomDirection = (Vector3)
    {
        (float)rand() / RAND_MAX * 2.0f - 1.0f,
        (float)rand() / RAND_MAX * 2.0f - 1.0f,
        (float)rand() / RAND_MAX * 2.0f - 1.0f
    };

    for (int i = 0; i < 8; i++)
    {
        
        Vector3 v1, v2, v3;
        GetVertsForIndexedMesh(box->verts, box->indices, i, &v1, &v2, &v3);

        if (box->showDebug)
        {
            box->cubeVertsDebug[i] = v1;
        }

        
        Vector3 b = Vector3Add(point, Vector3Scale(randomDirection, 1000.0f));
        //our random direction seems fine as viewable with our raycasts

        if (box->showDebug)
        {
            box->randDirectionDebug[i] = b;
        }
        
        /*
            At this point I'm reusing code from my collision detection algorithm
            At some point I will come along and tighten everything up with universal
            functions but that point has yet to come
        */
        Vector3 normal = (Vector3CrossProduct(Vector3Subtract(v2, v1), Vector3Subtract(v3, v1)));

        
        double t0, t1;

        /*
            Originally what was wrong was that rather than using the location of the triangle, you were 
            using the location of the box itself
        */
        double equationVal = -(normal.x * v1.x + normal.y * v1.y + normal.z * v1.z);
        double signedDistToTrianglePlane = Vector3DotProduct(point, normal) + equationVal;

        float normalDotB = (Vector3DotProduct(normal, b));
        
        if (!SetT(normalDotB, signedDistToTrianglePlane, NULL, &t0, &t1))
        {
            continue;
        }

        Vector3 collisionPoint;
        bool foundCollision = false;

        /*
            The intersection point was also wrong as you weren't scaling it properly according
            to the point
        */
        Vector3 intersectionPoint = Vector3Add(point, Vector3Scale(b, t1));

        
        
        if (CheckPointInTriangle(intersectionPoint, v1, v2, v3))
        {
            intersectionCount++;
        }
        
    }

    return intersectionCount % 2 != 0;
}



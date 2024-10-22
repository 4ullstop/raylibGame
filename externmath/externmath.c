#include "externmath.h"
#include <stdlib.h>
#include <stdio.h>

/*
    This Point inside Collision box algorithm was developed
    according to the article Checking if A Point is Inside a Shape
    which you can find here: https://mathsfromnothing.au/checking-if-a-point-is-inside-a-shape/?i=2
*/

bool IsPointInColBox(ColBox* box, Vector3 point)
{
    //12 triangles to check
    //make an affine transform matrix at some point
    //

    

    int intersectionCount = 0;

    if (box->showDebug)
    {
        box->randDirectionDebug = malloc(sizeof(Vector3) * 12);
        box->cubeVertsDebug = malloc(sizeof(Vector3) * 36);
        box->debugPoint = point;
        box->cubeVertsSize = 36;
        box->randDirectionSize = 12;
    }

    
    int debugStartingIndex = 0;

    for (int i = 0; i < 12; i++)
    {
        
        Vector3 v1;
        Vector3 v2;
        Vector3 v3;

        FaceFromIndexedColBox(&v1, &v2, &v3, box, i);

        if (box->showDebug)
        {
            box->cubeVertsDebug[i] = v1;
        }

        Vector3 randomDirection = (Vector3){
            (float)rand() / RAND_MAX * 2.0f - 1.0f,
            (float)rand() / RAND_MAX * 2.0f -1.0f,
            (float)rand() / RAND_MAX * 2.0f - 1.0f
        };
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
        Vector3 normal = Vector3CrossProduct(Vector3Subtract(v2, v1), Vector3Subtract(v3, v1));

        double t0, t1;

        double equationVal = -(normal.x * box->location.x, normal.y * box->location.y, normal.z * box->location.z);
        double signedDistToTrianglePlane = Vector3DotProduct(point, normal) + equationVal;

        float normalDotB = Vector3Dot(normal, b);

        if (normalDotB == 0.0f)
        {
            if (fabs(signedDistToTrianglePlane) >= 1.0f)
            {
                continue;
            }
            else
            {
                t0 = 0.0;
                t1 = 1.0;
            }
        }
        else
        {
            t0 = (-1.0 - signedDistToTrianglePlane) / normalDotB;
            t1 = (1.0 - signedDistToTrianglePlane) / normalDotB;

            if (t0 > t1)
            {
                double temp = t1;
                t1 = t0;
                t0 = temp;
            }

            if (t0 > 1.0f || t1 < 0.0f)
            {
                continue;
            }
            if (t0 < 0.0) t0 = 0.0;
            if (t1 < 0.0) t1 = 0.0;
            if (t0 > 1.0) t0 = 1.0;
            if (t1 > 1.0) t1 = 1.0;
        }

        Vector3 collisionPoint;
        bool foundCollision = false;
        float t = 1.0;

        Vector3 intersectionPoint = Vector3Add(Vector3Subtract(box->location, normal), Vector3Scale(b, t0));

        if (CheckPointInTriangle(intersectionPoint, v1, v2, v3))
        {
            
        }

        
    }


    return intersectionCount % 2 != 0;
}


void FaceFromIndexedColBox(Vector3* v1, Vector3* v2, Vector3* v3, ColBox* box, int i)
{
    //the error is probably here somewhere
    unsigned short index0 = box->indices[i * 3];
    unsigned short index1 = box->indices[i * 3 + 1];
    unsigned short index2 = box->indices[i * 3 + 2];

    Vector3 vert1 = 
    {
        box->verts[index0 * 3],
        box->verts[index0 * 3 + 1],
        box->verts[index0 * 3 + 2]
    };

    Vector3 vert2 = 
    {
        box->verts[index1 * 3],
        box->verts[index1 * 3 + 1],
        box->verts[index1 * 3 + 2]
    };

    Vector3 vert3 = 
    {
        box->verts[index2 * 3],
        box->verts[index2 * 3 + 1],
        box->verts[index2 * 3 + 2]
    };

    *v1 = vert1;
    *v2 = vert2;
    *v3 = vert3;
}
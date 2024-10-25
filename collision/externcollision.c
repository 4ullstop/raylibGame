#include "externcollision.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void GetVertsForIndexedMesh(float* allVerts, unsigned short* indices, int i, Vector3* v1, Vector3* v2, Vector3* v3)
{
    unsigned short index0 = indices[i * 3];
    unsigned short index1 = indices[i * 3 + 1];
    unsigned short index2 = indices[i * 3 + 2];

    Vector3 vert1 = 
    {
        allVerts[index0 * 3],
        allVerts[index0 * 3 + 1],
        allVerts[index0 * 3 + 2]
    };

    Vector3 vert2 = 
    {
        allVerts[index1 * 3],
        allVerts[index1 * 3 + 1],
        allVerts[index1 * 3 + 2]
    };

    Vector3 vert3 = 
    {
        allVerts[index2 * 3],
        allVerts[index2 * 3 + 1],
        allVerts[index2 * 3 + 2]
    };

    *v1 = vert1;
    *v2 = vert2;
    *v3 = vert3;
}

void GetVertsForNonIndexedMesh(float* allVerts, int i, Vector3* v1, Vector3* v2, Vector3* v3)
{
    Vector3 vert1 = 
    {
        allVerts[i * 9],
        allVerts[i * 9 + 1],
        allVerts[i * 9 + 2]
    };
    Vector3 vert2 = 
    {
        allVerts[i * 9 + 3],
        allVerts[i * 9 + 4],
        allVerts[i * 9 + 5]
    };
    Vector3 vert3 = 
    {
        allVerts[i * 9 + 6],
        allVerts[i * 9 + 7],
        allVerts[i * 9 + 8]
    };

    *v1 = vert1;
    *v2 = vert2;
    *v3 = vert3;
}

bool SetT(float normalDotComparison, float signedDistToPlane, bool* embeddedInPlane, double* t0, double* t1)
{
    //check if the sphere is travelling parallel, then we don't need to run any calculations
    if (normalDotComparison == 0.0f)
    {
        if (fabs(signedDistToPlane) >= 1.0f)
        {
            //the sphere is not embedded in the plane, no collision is possible so we
            //return
            return false;
        }
        else
        {
            //the sphere is embedded in the plane
            //it intersects with the whole range [0...1]
            if (embeddedInPlane != NULL)
            {
                *embeddedInPlane = true;
            }
            
            *t0 = 0.0;
            *t1 = 1.0; 
        }
    }
    //the swept sphere is going to intersect with the triangle, so run this
    else
    {
        //this is where we use our giant math equation to determine t0 and t1
        //and get the first time (t0) that the triangle will intersect with our plane
        *t0 = (-1.0 - signedDistToPlane) / normalDotComparison;
        *t1 = (1.0 - signedDistToPlane) / normalDotComparison;

        //swap our values t0 and t1 if t1 is less (ie we are approaching 
        //the plane from behind)
        if (*t0 > *t1)
        {
            double temp = *t1;
            *t1 = *t0;
            *t0 = temp;
        }

        //check that at least one result is within our time range
        if (*t0 > 1.0f || *t1 < 0.0f)
        {
            //both t values are outside [0, 1]
            //No collision is possible
            return false;
        }
        //clamp to [0, 1]
        if (*t0 < 0.0) *t0 = 0.0;
        if (*t1 < 0.0) *t1 = 0.0;
        if (*t0 > 1.0) *t0 = 1.0;
        if (*t1 < 1.0) *t1 = 1.0;
    }
    return true;
}
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
        if (*t1 > 1.0) *t1 = 1.0;
    }
    return true;
}

/*
    Checking each vertice for collision
*/
void CheckVertice(Vector3 vector, Vector3 base, float* t, Vector3 vertex, bool* foundCollision, Vector3* collisionPoint)
{
    float vectorSquaredLength = Vector3LengthSqr(vector);
    float a, b, c;
    float newT;

    a = vectorSquaredLength;
    b = 2.0 * (Vector3DotProduct(vector, Vector3Subtract(base, vertex)));
    c = Vector3LengthSqr(Vector3Subtract(vertex, base)) - 1.0;
    if (GetLowestRoot(a, b, c, *t, &newT))
    {
        *t = newT;
        *foundCollision = true;
        *collisionPoint = vertex;
    }
}

/*
    Checking each edge of the triangle
*/
void CheckEdge(Vector3 p1, Vector3 p2, Vector3 base, Vector3 vector, float* t, bool* foundCollision, Vector3* collisionPoint)
{
    Vector3 edge = Vector3Subtract(p2, p1);
    Vector3 baseToVertex = Vector3Subtract(p1, base);
    float vectorSquaredLength = Vector3LengthSqr(vector);
    float edgeSquareLength = Vector3LengthSqr(edge);
    float edgeDotVector = Vector3DotProduct(edge, vector);
    float edgeDotBaseToVertex = Vector3DotProduct(edge, baseToVertex);
    float a, b, c;
    float newT;

    a = edgeSquareLength * -vectorSquaredLength + edgeDotVector * edgeDotVector;
    b = edgeSquareLength * (2 * Vector3DotProduct(vector, baseToVertex)) - 2.0 * edgeDotVector * edgeDotBaseToVertex;
    c = edgeSquareLength * (1 - Vector3LengthSqr(baseToVertex)) + edgeDotBaseToVertex * edgeDotBaseToVertex;

    if (GetLowestRoot(a, b, c, *t, &newT))
    {
        float f = (edgeDotVector * newT - edgeDotBaseToVertex) / edgeSquareLength;

        if (f >= 0.0 && f <= 1.0f)
        {
            *t = newT;
            *foundCollision = true;
            *collisionPoint = Vector3Add(p1, Vector3Scale(edge, f));
        }
    }
}

/*
    This function solves a quadratic equation and returns the lowest root, 
    below a certain threshold (maxR)
*/
bool GetLowestRoot(float a, float b, float c, float maxR, float* root)
{
    //check if the solution exists
    float determinant = b * b - 4.0 * a * c;

    //if determinant is negative, it means no solutions
    if (determinant < 0.0f) return false;

    //calculate the two roots: (if determinante == 0 then x1==x2 or something?)
    float sqrtD = sqrt(determinant);
    float r1 = (-b - sqrtD) / (2 * a);
    float r2 = (-b + sqrtD) / (2 * a);

    //Sort so x1 <= x2
    if (r1 > r2)
    {
        float temp = r2;
        r2 = r1;
        r1 = temp;
    }

    //get lowest root
    if (r1 > 0 && r1 < maxR)
    {
        *root = r1;
        return true;
    }

    //It is possible that we want x2
    //This can happen if x1 < 0
    if (r2 > 0 && r2 < maxR)
    {
        *root = r2;
        return true;
    }

    //No valid solutions
    return false;
}


void ConstructColBox(ColBox* box, Vector3 location, float width, float height, float length)
{
    box->vertsNum = 8;
    box->verts = malloc(sizeof(float) * 24);

    if (box->verts == NULL)
    {
        printf("BAD ALLOCATION YOU ARE OUT OF MEMORY?\n");
    }

    box->interact = InteractionBoxInteract;

    float unassignedVerts[] = {
        location.x - width/2, location.y - height/2, location.z - length/2, // bottom left back (0)
        location.x + width/2, location.y - height/2, location.z - length/2, // bottom right back (1)
        location.x + width/2, location.y + height/2, location.z - length/2, // top right back (2)
        location.x - width/2, location.y + height/2, location.z - length/2, // top left back (3)
    
        location.x - width/2, location.y - height/2, location.z + length/2, // bottom left front (4)
        location.x + width/2, location.y - height/2, location.z + length/2, // bottom right front (5)
        location.x + width/2, location.y + height/2, location.z + length/2, // top right front (6)
        location.x - width/2, location.y + height/2, location.z + length/2  // top left front (7)
    };

    for (int i = 0; i < 24; i++)
    {
        box->verts[i] = unassignedVerts[i];
    }
    

    unsigned short unassignedIndicies[] = {
        0, 1, 2,  2, 3, 0, //back face
        4, 5, 6,  6, 7, 4, //front face
        0, 3, 7,  7, 4, 0, //left face
        1, 5, 6,  6, 2, 1, //right face
        3, 2, 6,  6, 7, 3, //top face
        0, 1, 5,  5, 4, 0 //bottomface
    };

    box->indices = malloc(sizeof(unsigned short) * 36);

    for (int i = 0; i < 36; i++)
    {
        box->indices[i] = unassignedIndicies[i];
    }
}


void InteractionBoxInteract(FPSPlayer* player, ColBox* box)
{
    //do stuff here later
    printf("You interacted and everything works!\n");
}

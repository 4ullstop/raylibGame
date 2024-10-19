#include "externmath.h"
#include <stdlib.h>

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

    Matrix affineTrans = 
    {
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };

    int intersectionCount = 0;

    for (int i = 0; i < 12; i++)
    {
        Vector3 v1;
        Vector3 v2;
        Vector3 v3;

        FaceFromIndexedColBox(&v1, &v2, &v3, box, i);

        /*
            Solving for t
        */
        Vector3 normal = Vector3CrossProduct(Vector3Subtract(v2, v1), Vector3Subtract(v3, v1));

        if (Vector3Length(normal) == 0.0f) continue;

        Vector3 x1 = v1;

        Vector3 randomDirection = (Vector3){
            (float)rand() / RAND_MAX * 2.0f - 1.0f,
            (float)rand() / RAND_MAX * 2.0f -1.0f,
            (float)rand() / RAND_MAX * 2.0f - 1.0f
        };
        Vector3 b = Vector3Add(point, Vector3Scale(randomDirection, 1000.0f));

        float numerator = Vector3DotProduct(normal, Vector3Subtract(x1, point));
        float denominator = Vector3DotProduct(normal, b);

        if (denominator == 0.0f) continue;

        float t = numerator / denominator;

        if (t <= 0) continue;

        
        /*
            Solving for D
            D = MC

            Where c is the test if the intersection between the line and face
            And m is the affine transform matrix based on our dimensions * the transform matrix of the object
        */

        Matrix facemat = 
        {
            v1.x, v2.x, v3.x, normal.x,
            v1.y, v2.y, v3.y, normal.y,
            v1.z, v2.z, v3.z, normal.z,
            1.0f, 1.0f, 1.0f, 1.0f
        };

        Vector3 c = Vector3Add(Vector3Scale(b, t), point);

        Matrix invertedFaceMat = MatrixInvert(facemat);
        Matrix m = MatrixMultiply(affineTrans, invertedFaceMat);

        Vector3 transformedVec = Vector3Transform(c, m);
        
        bool MatCheck = CompareMatrix(transformedVec);

        if (MatCheck && t > 0) intersectionCount++;
    }

    return intersectionCount % 2 != 0;
}


void FaceFromIndexedColBox(Vector3* v1, Vector3* v2, Vector3* v3, ColBox* box, int i)
{
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

bool CompareMatrix(Vector3 transformedVector)
{
    if (transformedVector.x < 0.0f || transformedVector.y < 0.0f || transformedVector.z < 0.0f) return false;
    float sum = transformedVector.x + transformedVector.y;
    if (sum < 1.0f) return true;
    else return false;
}
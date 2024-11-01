#include "raycasting.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/*
    With this current set up for the raycast system, you can cast and interact
    through walls. Also it doesn't always register because we aren't checking edges
    or vertices of a mesh. These are things that are relatively simple to fix, but
    I'm not gonna do it just yet because I want to acutally get started on other parts
    of the game.
*/

bool CastRayLine(FPSPlayer* player, Vector3 camForward, Raycast* ray, ColBox* allLocalBoxes, enum Gamemode* mode)
{
    Vector3 start = player->location;
    //ray->showDebugLines = true;
    Vector3 end = Vector3Add(start, Vector3Scale(camForward, ray->rayLength));
    
    if (ray->showDebugLines == true)
    {
        printf("about to draw line\n");
        DrawNewLine(ray, start, end);
    }
    bool hit = HitDetected(start, end, ray, allLocalBoxes, mode);
    return hit;
}

bool HitDetected(Vector3 start, Vector3 end, Raycast* ray, ColBox* allLocalBoxes, enum Gamemode* mode)
{
    for (int i = 0; i < 12; i++)
    {
        Vector3 v1, v2, v3;
        GetVertsForIndexedMesh(allLocalBoxes->verts, allLocalBoxes->indices, i, &v1, &v2, &v3);
        
        Vector3 normal = Vector3CrossProduct(Vector3Subtract(v2, v1), Vector3Subtract(v3, v1));
        normal = Vector3Normalize(normal);

        double t0, t1;

        double equationVal = -(normal.x * v1.x + normal.y * v1.y + normal.z * v1.z);
        double signedDistToTrianglePlane = Vector3DotProduct(start, normal) + equationVal;

        float normalDotEnd = Vector3DotProduct(normal, end);


        if (!SetT(normalDotEnd, signedDistToTrianglePlane, NULL, &t0, &t1))
        {
            continue;
        }
        
        bool foundCollision = false;
        float t = 1.0;

        //it turns out the intersection point was the problem, the direction wasn't normalized 
        //before scaling it by t0
        Vector3 intersectionPoint = Vector3Add(start, Vector3Scale(Vector3Subtract(end, start), t0));
        
        if (CheckPointInTriangle(intersectionPoint, v1, v2, v3))
        {
            ray->hitLocation = intersectionPoint;
            allLocalBoxes->interact();
            printf("Hit found\n");
            return true;
        }
        else
        {
            CheckVertice(end, start, &t, v1, &foundCollision, &intersectionPoint);
            CheckVertice(end, start, &t, v2, &foundCollision, &intersectionPoint);
            CheckVertice(end, start, &t, v3, &foundCollision, &intersectionPoint);

            CheckEdge(v1, v2, start, end, &t, &foundCollision, &intersectionPoint);
            CheckEdge(v2, v3, start, end, &t, &foundCollision, &intersectionPoint);
            CheckEdge(v3, v1, start, end, &t, &foundCollision, &intersectionPoint);
        }

        if (foundCollision == true)
        {
            ray->hitLocation = intersectionPoint;
            allLocalBoxes->interact();
            *mode = EGM_Puzzle;
            return true;
        }

        // if (foundCollision == true)
        // {
        //     float distToCollision = t * Vector3Length(end);

        //     if (ray->foundCollision == false || distToCollision < ray->nearestCollision)
        //     {
        //         ray->nearestCollision = distToCollision;
        //         ray->hitLocation = intersectionPoint;
        //         ray->foundCollision = true;
        //     }
        // }
    }
    return false;
}

void DrawNewLine(Raycast* ray, Vector3 start, Vector3 end)
{
    printf("new line added\n");
    Drawline* line = malloc(sizeof(Drawline));
    line->start = start;
    line->end = end;
    line->color = RED;
    line->hitpoint = ray->hitLocation;

    line->next = NULL;
    if (ray->linesToDraw == NULL)
    {
        ray->linesToDraw = line;
    }
    else
    {
        line->next = ray->linesToDraw;
        ray->linesToDraw = line;
        line->next = NULL;
    }
}

void DestroyLines(Drawline* line)
{
    if (line == NULL)
    {
        return;
    }
    else
    {
        DestroyLines(line->next);
        free(line);
        line = NULL;
    }
}
#include "interactionbox.h"
#include "../externmath/externmath.h"   
#include <stdlib.h>
#include <stdio.h>

void ConstructInteractable(Interactable* interactable, Vector3 location, ColBox* box, float boxWidth, float boxHeight, float boxLength)
{
    if (interactable == NULL)
    {
        printf("ERROR: Interactable is invalid!\n");
    }
    interactable->Location = location;

    
    ConstructColBox(box, interactable->Location, boxWidth, boxHeight, boxLength);
    interactable->colBox = box;

}

void DestructInteractable(Interactable* interactable)
{
    DestructColBox(interactable->colBox);
    free(interactable);
}

bool IsPointInInteractable(Interactable* interactable, Vector3 point)
{
    return IsPointInColBox(interactable->colBox, point);
}

void ConstructColBox(ColBox* box, Vector3 location, float width, float height, float length)
{
    box->vertsNum = 8;
    
    box->verts = malloc(sizeof(float) * 24);

    

    float unassignedVerts[] = {
        location.x - width/2, location.y - height/2, location.z - length/2, //bottom left back (0)
        location.x + width/2, location.y - height/2, location.z - length/2, //bottom right back (1)
        location.x + width/2, location.y + height/2, location.z - length/2, //top right back (2)
        location.x - width/2, location.y + height/2, location.z - length/2, //top left back (3)

        location.x - width/2, location.y - height/2, location.z + length/2, //bottom left fron (4)
        location.x + width/2, location.y - height/2, location.z + length/2, //bottom right front (5)
        location.x + width/2, location.y + height/2, location.z + length/2, //top right front (6)
        location.x - width/2, location.y + height/2, location.z + length/2 //top left front (7)
    };

    for (int i = 0; i < 24; i++)
    {
        box->verts[i] = unassignedVerts[i];
    }
    printf("\n");

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

void DestructColBox(ColBox* box)
{
    free(box->verts);
    free(box->indices);
    free(box->randDirectionDebug);
    free(box);
}
#include "interactionbox.h"
#include "../externmath/externmath.h"   
#include <stdlib.h>
#include <stdio.h>

void CreateInteractables(Interactable** interactables, QueryBox** areaQueryBoxes, ButtonMaster** allPuzzles)
{
    
}


void InteractionBoxInteract(FPSPlayer* player, ColBox* box)
{
    //do stuff here later
    printf("You interacted and everything works!\n");
}

void ConstructInteractable(Interactable* interactable, Vector3 location, ColBox* box, float boxWidth, float boxHeight, float boxLength)
{
    if (interactable == NULL)
    {
        printf("ERROR: Interactable is invalid!\n");
    }
    interactable->Location = location;
    interactable->width = boxWidth;
    interactable->height = boxHeight;
    interactable->length = boxLength;
    
    ConstructColBox(box, interactable->Location, boxWidth, boxHeight, boxLength);
    interactable->colBox = box;

}

void DestructInteractable(Interactable* interactable)
{
    DestructColBox(interactable->colBox);
    //free(interactable);
}

bool IsPointInInteractable(Interactable* interactable, Vector3 point)
{
    return IsPointInColBox(interactable->colBox, point);
}

void ConstructColBox(ColBox* box, Vector3 location, float width, float height, float length)
{
    box->vertsNum = 8;
    box->verts = malloc(sizeof(float) * 24);

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

void DestructColBox(ColBox* box)
{
    free(box->verts);
    box->verts = NULL;
    free(box->indices);
    box->indices = NULL;
    // if (box->randDirectionDebug != NULL)
    // {
    //     free(box->randDirectionDebug);
    //     box->randDirectionDebug = NULL;
    // }
    // if (box->cubeVertsDebug != NULL)
    // {
    //     free(box->cubeVertsDebug);
    //     box->cubeVertsDebug = NULL;
    // }
    
    free(box);
    box = NULL;
}

void CreatePlayerAreaQueries(QueryBox** areaQueryBoxes)
{
    QueryBox* box_01 = malloc(sizeof(QueryBox));
    box_01->areaBox = malloc(sizeof(ColBox));
    box_01->location = (Vector3){1.0, 2.0, -15.0};
    box_01->length = 100.f;
    box_01->width = 100.f;
    box_01->height = 20.f;
    ConstructColBox(box_01->areaBox, box_01->location, box_01->width, box_01->height, box_01->length);

    areaQueryBoxes[0] = box_01;
    areaQueryBoxes[0]->numberOfInteractables = 3;
}


void NullifyColBoxValues(ColBox* box)
{
    box->randDirectionDebug = NULL;
    box->verts = NULL;
    box->indices = NULL;
}

void DestroyAreasAndInteractables(QueryBox** areaQueryBoxes, int numOfQueryBoxes, int numOfInteractables)
{
    printf("num of queryboxes: %i\n", numOfQueryBoxes);
        printf("num of interactables: %i\n", numOfInteractables);
    for (int i = 0; i < numOfQueryBoxes; i++)
    {
        for (int j = 0; j < numOfInteractables; j++)
        {
            DestructInteractable(areaQueryBoxes[i]->associatedInteractables[j]);
            printf("destroying interactable\n");
            free(areaQueryBoxes[i]->associatedInteractables[j]);
        }
        DestructColBox(areaQueryBoxes[i]->areaBox);
        //Wouldn't doubt if there were still things that needed to be freed
        //but uhh... you got this Windows
    }
}


void PuzzleInteract(FPSPlayer* player, ColBox* box)
{
    printf("puzzle interact! %i\n", box->id);
    if (box->id == 1)
    {
        //hide 'e' to interact hint show 'enter' to select button hint
        player->playerHUD[1]->hidden = true;
        player->playerHUD[2]->hidden = false;
    }
    if (box->id == 2)
    {
        player->playerHUD[3]->hidden = false;
    }
}
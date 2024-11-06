#include "interactionbox.h"
#include "../externmath/externmath.h"   
#include <stdlib.h>
#include <stdio.h>

void CreateInteractables(Interactable** interactables, QueryBox** areaQueryBoxes, ButtonMaster** allPuzzles)
{
    ColBox* colBox_01 = malloc(sizeof(ColBox));
    NullifyColBoxValues(colBox_01);
    Interactable* interactable_01 = malloc(sizeof(Interactable));
    interactable_01->associatedPuzzle = NULL;
    ConstructInteractable(interactable_01, (Vector3){0.0f, 3.0f, -4.0f}, colBox_01, 2.0f, 2.0f, 2.0f);

    ColBox* puzzleBox_01 = malloc(sizeof(ColBox));
    NullifyColBoxValues(puzzleBox_01);
    Interactable* interactable_02 = malloc(sizeof(Interactable));
    interactable_02->type = ITT_Puzzle;
    interactable_02->hasBeenUsed = false;
    interactable_02->id = 23;
    ConstructInteractable(interactable_02, (Vector3){0.0f, 0.0f, 0.0f}, puzzleBox_01, 2.0f, 2.0f, 2.0f);
    //AssignInteractionBoxToPuzzle(allPuzzles, interactable_02);
    interactable_02->associatedPuzzle = allPuzzles[0];
    interactable_02->Location = allPuzzles[0]->location;

    ColBox* puzzleBox_02 = malloc(sizeof(ColBox));
    NullifyColBoxValues(puzzleBox_02);
    Interactable* interactable_03 = malloc(sizeof(Interactable));
    interactable_03->type = ITT_Puzzle;
    interactable_03->hasBeenUsed = false;
    interactable_03->id = 3;
    ConstructInteractable(interactable_03, (Vector3){3.0f, 0.0f, -4.0f}, puzzleBox_02, 2.0f, 2.0f, 2.0f);
    //AssignInteractionBoxToPuzzle(allPuzzles, interactable_03);
    interactable_03->associatedPuzzle = allPuzzles[1];
    interactable_03->Location = allPuzzles[1]->location;
    printf("%f, %f, %f\n", interactable_03->Location.x, interactable_03->Location.y, interactable_03->Location.z);

    interactables[0] = interactable_01;
    areaQueryBoxes[0]->associatedInteractables[0] = interactable_01;

    interactables[1] = interactable_02;
    areaQueryBoxes[0]->associatedInteractables[1] = interactable_02;

    interactables[2] = interactable_03;
    areaQueryBoxes[0]->associatedInteractables[2] = interactable_03;
}


void InteractionBoxInteract(void)
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
    box_01->location = (Vector3){2.0, 2.0, -2.0};
    box_01->length = 10.f;
    box_01->width = 10.f;
    box_01->height = 10.f;
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

void DestroyAreasAndInteractables(QueryBox** areaQueryBoxes)
{
    for (int i = 0; i < NUMBER_OF_AREA_QUERY_BOXES; i++)
    {
        for (int j = 0; j < NUMBER_OF_INTERACTABLES; j++)
        {
            DestructInteractable(areaQueryBoxes[i]->associatedInteractables[j]);
            free(areaQueryBoxes[i]->associatedInteractables[j]);
        }
        DestructColBox(areaQueryBoxes[i]->areaBox);
        //Wouldn't doubt if there were still things that needed to be freed
        //but uhh... you got this Windows
    }
}

void AssignInteractionBoxToPuzzle(ButtonMaster** master, Interactable* interactable)
{
    //do our other setup stuff as well
    printf("about to assign boxes\n");
    for (int i = 0; i < NUMBER_OF_PUZZLES; i++)
    {
        if (!master[i]->hasBoxAssigned)
        {
            interactable->associatedPuzzle = master[i];
            interactable->Location = master[i]->location;
            printf("assigning puzzle to interactable\n");
            return;
        }
    }
}
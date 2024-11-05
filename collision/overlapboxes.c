#include "overlapboxes.h"
#include <stdlib.h>
#include <stdio.h>

/*
    We use a double pointer for allQueriedBoxes so that it's value as a linked list is
    passed by reference and not by value because pointers, it might be helpful to come
    back to this to understand why when you are less tired
*/
void ConstructOverlapBoxes(OverlapBox** allBoxes)
{
    OverlapBox* interactHintOverlap = malloc(sizeof(OverlapBox));
    ColBox* overlapBox = malloc(sizeof(ColBox));
    interactHintOverlap->collisionBox = overlapBox;
    interactHintOverlap->location = (Vector3){3.0f, 2.0f, -4.0f};
    overlapBox->location = interactHintOverlap->location;
    interactHintOverlap->height = 7.0f;
    interactHintOverlap->width = 7.0f;
    interactHintOverlap->length = 7.0f;
    interactHintOverlap->next = NULL;
    interactHintOverlap->id = 1;
    interactHintOverlap->shouldDetect = true;
    ConstructColBox(overlapBox, interactHintOverlap->location, interactHintOverlap->width, interactHintOverlap->height, interactHintOverlap->length);
    interactHintOverlap->OnOverlap = PlayerInInteractHintBox;

    allBoxes[0] = interactHintOverlap;
}
void DestroyOverlapBoxes(OverlapBox** allBoxes)
{
    for (int i = 0; i < NUMBER_OF_OVERLAP_BOXES_A; i++)
    {
        DestructColBox(allBoxes[i]->collisionBox);
        free(allBoxes[i]);
        allBoxes[i] = NULL;
    }
    
}

void PlayerInInteractHintBox(FPSPlayer* player)
{
    printf("player in interaction hit box\n");
}

/*
    Checking for overlaps, with the current implementation, you can only
    check if the player is in one box meaning overlap boxes cannot be nested inside of 
    the area of other overlap boxes
*/
void PollOverlaps(OverlapBox** queryList, FPSPlayer* player)
{
    
    for (int i = 0; i < NUMBER_OF_OVERLAP_BOXES_A; i++)
    {
        bool playerInOverlap = IsPointInColBox(queryList[i]->collisionBox, player->location);
        //printf("%f, %f, %f\n", player->location.x, player->location.y, player->location.z);
        //printf("%i\n", queryList[i]->id);
        if (playerInOverlap == true)
        {
            queryList[i]->OnOverlap(player);
            return;
        }
    }
}
#include "overlapboxes.h"
#include <stdlib.h>
#include <stdio.h>

/*
    We use a double pointer for allQueriedBoxes so that it's value as a linked list is
    passed by reference and not by value because pointers, it might be helpful to come
    back to this to understand why when you are less tired
*/
void ConstructOverlapBoxes(OverlapBox** allBoxes, ExitCode* exitCode)
{
    OverlapBox* interactHintOverlap = malloc(sizeof(OverlapBox));
    if (interactHintOverlap == NULL)
    {
	EditReturnCodeInfo(700, "Failed to allocate memory for Overlap Box", exitCode);
	return;
    }
    ColBox* overlapBox = malloc(sizeof(ColBox));
    if (overlapBox == NULL)
    {
	EditReturnCodeInfo(701, "Failed to allocate memory for OverlapBox", exitCode);
    }
    interactHintOverlap->collisionBox = overlapBox;
    interactHintOverlap->location = (Vector3){2.3f, 1.0f, -15.0f};
    overlapBox->location = interactHintOverlap->location;
    interactHintOverlap->height = 5.0f;
    interactHintOverlap->width = 10.0f;
    interactHintOverlap->length = 10.0f;
    interactHintOverlap->next = NULL;
    interactHintOverlap->id = 1;
    interactHintOverlap->shouldDetect = true;
    overlapBox->id = 11;
    ConstructColBox(overlapBox, interactHintOverlap->location, interactHintOverlap->width, interactHintOverlap->height, interactHintOverlap->length, exitCode);
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

void PlayerInInteractHintBox(FPSPlayer* player, OverlapBox* box)
{
    Vector3 puzzleLocation = (Vector3){2.3f, 1.0f, -15.0f};
    
    float lookRange = 5.f;
    if (IsPointInDistanceTo(player->location, puzzleLocation, 2.0f))
    {
        float dot = Vector3DotProduct(player->playerLookForward, puzzleLocation);
        printf("dot: %f\n", dot);
        if ((dot <= lookRange && dot >= 0) || (dot >= -(lookRange) && dot <= 0))
        {
            //show the widget
            player->playerHUD[1]->hidden = false;
            box->shouldDetect = false;
            printf("displaying interact widget now\n");
        }
    }
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
        if (queryList[i]->shouldDetect == false) continue;
        bool playerInOverlap = IsPointInColBox(queryList[i]->collisionBox, player->location);
        if (playerInOverlap == true)
        {
            queryList[i]->OnOverlap(player, queryList[i]);
            return;
        }
    }
}

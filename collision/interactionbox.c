#include "interactionbox.h"
#include "../externmath/externmath.h"   
#include <stdlib.h>
#include <stdio.h>

void CreateInteractables(Interactable** interactables, QueryBox** areaQueryBoxes, ButtonMaster** allPuzzles)
{
    
}

void ConstructInteractable(Interactable* interactable, Vector3 location, ColBox* box, float boxWidth, float boxHeight, float boxLength, ExitCode* exitCode)
{
    if (interactable == NULL || box == NULL)
    {
        EditReturnCodeInfo(605, "Interactable/box is null upon construction", exitCode);
	return;
    }
    
    interactable->Location = location;
    interactable->width = boxWidth;
    interactable->height = boxHeight;
    interactable->length = boxLength;
    
    ConstructColBox(box, interactable->Location, boxWidth, boxHeight, boxLength, exitCode);
    interactable->colBox = box;

}

void DestructInteractable(Interactable* interactable)
{
    DestructColBox(interactable->colBox);
}

bool IsPointInInteractable(Interactable* interactable, Vector3 point)
{
    return IsPointInColBox(interactable->colBox, point);
}

void DestructColBox(ColBox* box)
{
    printf("ColBox id on destruct: %i\n", box->id);
    if (box->verts == NULL || box->indices == NULL|| box == NULL) return;
    printf("verts: %f\n", *box->verts);
    free(box->verts);
    box->verts = NULL;
    printf("ColBox destroyed\n");
    free(box->indices);
    box->indices = NULL;
    
    free(box);
    box = NULL;
    
}

void CreatePlayerAreaQueries(QueryBox** areaQueryBoxes, enum Gametype gametype, ExitCode* exitCode)
{
    if (gametype == EGT_A)
    {
	CreateGameAQueryBoxes(areaQueryBoxes, exitCode);
    }
    else
    {
	CreateGameBQueryBoxes(areaQueryBoxes, exitCode);
    }
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
            
            if (areaQueryBoxes[i]->associatedInteractables[j] != NULL)
            {
                free(areaQueryBoxes[i]->associatedInteractables[j]);
                areaQueryBoxes[i]->associatedInteractables[j] = NULL;
            }
            
        }
        DestructColBox(areaQueryBoxes[i]->areaBox);
        areaQueryBoxes[i]->areaBox = NULL;
        //Wouldn't doubt if there were still things that needed to be freed
        //but uhh... you got this Windows
    }
}


void PuzzleInteract(FPSPlayer* player, ColBox* box)
{
    if (player == NULL || box == NULL)
    {
	
    }
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

void ConstructSingleInteractable(int* lastInteractableIndex, enum InteractableType puzzleType, bool showArrowKeyHint, float len, float width, float height, ButtonMaster* assignedPuzzle, void(*colBoxInteract)(FPSPlayer*, ColBox*), Interactable** interactables, QueryBox** areaQueryBox, int areaQueryBoxId, ExitCode* exitCode)
{
    if (assignedPuzzle == NULL || lastInteractableIndex == NULL)
    {
	EditReturnCodeInfo(601, "Assigned puzzle/last interactable null", exitCode);
	return;
    }
    ColBox* box = malloc(sizeof(ColBox));
    if (box == NULL)
    {
	EditReturnCodeInfo(600, "Failed To allocate memory for interactable box\n", exitCode);
	return;
    }
    NullifyColBoxValues(box);
    box->id = *lastInteractableIndex;
    Interactable* interactable = malloc(sizeof(Interactable));
    if (interactable == NULL)
    {
	EditReturnCodeInfo(601, "Failed to allocate memory for Interactable\n", exitCode);
	return;
    }
    interactable->type = puzzleType;
    interactable->hasBeenUsed = false;
    interactable->id = *lastInteractableIndex;
    interactable->showsArrowKeyHint = showArrowKeyHint;
    ConstructInteractable(interactable, assignedPuzzle->location, box, width, height, len, exitCode);
    box->interact = colBoxInteract;
    interactable->associatedPuzzle = assignedPuzzle;
    interactable->Location = assignedPuzzle->location;

    interactables[*lastInteractableIndex] = interactable;
    areaQueryBox[areaQueryBoxId]->associatedInteractables[*lastInteractableIndex] = interactable;
    *lastInteractableIndex = *lastInteractableIndex + 1;
}

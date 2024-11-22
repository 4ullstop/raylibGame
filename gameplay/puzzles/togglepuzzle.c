#include "togglepuzzle.h"
#include <stdio.h>
#include <stdlib.h>



void AssignToggleAction(Button* button, enum TextureCoordinateLocations textureLocations)
{
    button->buttonRules = malloc(sizeof(ButtonRules));
    button->buttonRules->toggleRule = malloc(sizeof(ToggleRule));
    button->buttonRules->toggleRule->puzzleOODirection = FindDirectionFromCoordLoc(textureLocations);
    button->buttonRules->toggleRule->hasBeenToggled = false;
    button->ButtonSelected = EnactToggle;
}

enum PuzzleOnOffDirection FindDirectionFromCoordLoc(enum TextureCoordinateLocations textureLocations)
{
    if ((textureLocations > 13 && textureLocations < 22) || (textureLocations == 10))
    {
        return POOD_BottomUp;
    }
    else if ((textureLocations > 21 && textureLocations < 30) || (textureLocations == 11))
    {
        return POOD_LeftRight;
    }
    else if ((textureLocations > 29 && textureLocations < 38) || (textureLocations == 12))
    {
        return POOD_DRL;
    }
    else if ((textureLocations > 37 && textureLocations < 46) || (textureLocations == 13))
    {
        return POOD_DUR;
    }
    else 
    {
        printf("ERROR, TEXTURE LOCATION INCORRECT TOGGLEPUZZLE FINDDIRECTIONFROMCOORDLOC\n");
        return POOD_BottomUp;
    }
}


void EnactToggle(Button* button)
{
    //regardless you are gonna look at this later and realize that
    //the directions are completely wrong, but it's a start
    Vector2Int direction = {0};
    button->buttonRules->toggleRule->hasBeenToggled = true;
    switch (button->buttonRules->toggleRule->puzzleOODirection)
    {
    case POOD_TopDown:
        direction = (Vector2Int){-1, 0};
        //do top down action
        break;
    case POOD_BottomUp:
        direction = (Vector2Int){1, 0};
        //do bottom up action
        break;
    case POOD_DDL:
        direction = (Vector2Int){-1, 1};
        //ddl
        break;
    case POOD_DRL:
        direction = (Vector2Int){-1, 1};
        //drl
        break;
    case POOD_DUL:
        direction = (Vector2Int){1, -1};
        //dul
        break;
    case POOD_DUR:
        direction = (Vector2Int){1, 1};
        //dur
        break;
    case POOD_RightLeft:
        direction = (Vector2Int){0, -1};
        break;
    case POOD_LeftRight:
        direction = (Vector2Int){0, 1};
        break;
    default:
        printf("toggle unassigned direction\n");
        return;
    }
    //do something with the direction
    ToggleNeighbors(button, direction);
}

void ToggleNeighbors(Button* button, Vector2Int direction)
{
    //this is basically all just pseudocode
    CollateralPower* collateralButtons = NULL;
    ToggleRule* rule = button->buttonRules->toggleRule;
    //check each time that we haven't extended the range of the columns and rows based 
    //on our calculation with the direction
    int ogId = 0;
    if (button->isBeingAssessed == true)
    {
        
        ogId = 100;
        ToggleCurrButton(button, ogId);
    }
    else
    {
        ogId = button->id;
    }
    Button* ogButton = button;
    Button* currButton = button;
    
    currButton = GetNextButton(currButton, direction); 
    ToggleCurrButton(currButton, ogId);
    do
    {
        if (currButton->buttonRules != NULL && currButton->buttonRules->toggleRule != NULL)
        {
            AddButtonToList(&collateralButtons, currButton);
            printf("button added to list\n");
        }
        currButton = GetNextButton(currButton, direction);
        //run associated action (select the curr button/change the texture)
        ToggleCurrButton(currButton, ogId);
    } while (currButton->id != button->id);
    //
    AssessList(collateralButtons);
    DestroyList(&collateralButtons);
}

Button* GetNextButton(Button* next, Vector2Int direction)
{
    //gonna wann check here when you add in the other types of highlights
    Button* tempButton = NULL;
    if (direction.x > 0)
    {
        tempButton = next->nAbove;
        printf("getting above\n");
    }
    else if (direction.x < 0)
    {
        tempButton = next->nBelow;
        printf("getting below\n");
    }

    if (tempButton == NULL)
    {
        if (direction.y > 0)
        {
            tempButton = next->nRight;
        }
        else if (direction.y < 0)
        {
            tempButton = next->nLeft;
        }
    }
    else
    {
        if (direction.y > 0)
        {
            tempButton = tempButton->nRight;
            printf("yo b\n");
        }
        else if (direction.y < 0)
        {
            tempButton = tempButton->nLeft;
            printf("yo\n");
        }
    }
    next = tempButton;
    return tempButton;
}

void ToggleCurrButton(Button* currButton, int ogId)
{
    printf("address of curr button: %p\n", (void*)currButton);
    if (currButton->id != ogId)
    {
        if (currButton->submitted == true)
        {
            currButton->model->texture = currButton->buttonTextures->idle;
            currButton->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = currButton->buttonTextures->idle;
            currButton->submitted = false;
            currButton->buttonState = EBS_idle;
        }
        else
        {
            currButton->model->texture = currButton->buttonTextures->selected;
            currButton->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = currButton->model->texture;
            currButton->buttonState = EBS_selected;
            currButton->submitted = true;
        }
    }
    else
    {
        currButton->model->texture = currButton->buttonTextures->highlighted;
        currButton->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = currButton->model->texture;
        //currButton->submitted = true;
        currButton->buttonState = EBS_highlighted;
    }
}

void AddButtonToList(CollateralPower** head, Button* button)
{
    if (button->buttonRules->toggleRule->hasBeenToggled == true) return;
    CollateralPower* node = malloc(sizeof(CollateralPower));
    node->poweredButton = button;
    node->next = NULL;

    if (*head == NULL)
    {
        *head = node;
        return;
    }

    CollateralPower* temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = node;
}

void DestroyList(CollateralPower** head)
{
    CollateralPower* curr = *head;
    CollateralPower* next = NULL;

    while (curr != NULL)
    {
        next = curr->next; 
        free(curr);
        curr = next;
    }
    *head = NULL;

}

void AssessList(CollateralPower* head)
{
    CollateralPower* temp = head;

    printf("about to assess list\n");
    while (temp != NULL)
    {
        printf("looping through assessment\n");
        
        temp->poweredButton->isBeingAssessed = true;
        EnactToggle(temp->poweredButton);
        
        temp = temp->next;
    }
}
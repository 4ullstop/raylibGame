#include "togglepuzzle.h"

void EnactToggle(Button* button)
{
    //regardless you are gonna look at this later and realize that
    //the directions are completely wrong, but it's a start
    Vector2Int direction = {0};
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
        direction = (Vector2Int){-1, -1};
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
    ToggleRule* rule = button->buttonRules->toggleRule;
    //check each time that we haven't extended the range of the columns and rows based 
    //on our calculation with the direction
    int x = 0;
    int y = 0;
    Button* currButton = button;
    while (currButton->id != button->id)
    {
        Button* tempButton = NULL;
        if (direction.x > 0)
        {
            tempButton = currButton->nAbove;
        }
        else if (direction.x < 0)
        {
            tempButton = currButton->nBelow;
        }

        if (tempButton != NULL)
        {
            if (direction.y > 0)
            {
                tempButton = tempButton->nRight;
            }
            else if (direction.y < 0)
            {
                tempButton = tempButton->nLeft;
            }
        }
        else
        {
            if (direction.y > 0)
            {
                tempButton = currButton->nRight;
            }
            else if (direction.y < 0)
            {
                tempButton = currButton->nLeft;
            }
        }
        
        currButton = tempButton;
        //run associated action (select the curr button/change the texture)
        ToggleCurrButton(currButton);
    }
}

void ToggleCurrButton(Button* currButton)
{
    if (currButton->submitted == true)
    {
        currButton->model->texture = currButton->buttonTextures->highlighted;
        currButton->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = currButton->model->texture;
        currButton->submitted = false;
        currButton->buttonState = EBS_highlighted;
    }
    else
    {
        currButton->model->texture = currButton->buttonTextures->selected;
        currButton->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = currButton->model->texture;
        currButton->buttonState = EBS_selected;
        currButton->submitted = true;
    }
     
}
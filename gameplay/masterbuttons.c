#include "masterbuttons.h"
#include <stdlib.h>
#include <stdio.h>

void ConstructPuzzles(ButtonMaster** allPuzzles, modelInfo** dynamicModels, int* lastModelIndex)
{
    ButtonMaster* puzzle_01 = malloc(sizeof(ButtonMaster));
    puzzle_01->columns = 3;
    puzzle_01->rows = 3;
    puzzle_01->location = (Vector3){0.0f, 2.0f, 0.0f};
    puzzle_01->buttonSpread = 0.5f;
    puzzle_01->hasBoxAssigned = false;
    allPuzzles[0] = puzzle_01;


    for (int i = 0; i < NUMBER_OF_PUZZLES; i++)
    {
        CreateAllButtons(allPuzzles[i], dynamicModels, lastModelIndex);
    }

}

void CreateAllButtons(ButtonMaster* master, modelInfo** dynamicModels, int* lastModelIndex)
{
    master->totalButtons = master->rows * master->columns;
    master->childButtons = (Button**)malloc(master->rows * sizeof(Button*));
    Vector3 location = master->location;
    int r = master->rows;
    int c = master->columns;
    for (int i = 0; i < r; i++)
    {
        master->childButtons[i] = (Button*)malloc(c * sizeof(Button));
    }
    printf("%i\n", *lastModelIndex);

    int centerR = round((float)r / 2.0);
    int centerC = round((float)c / 2.0); 
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            ConstructSingleButton(master, i, j, lastModelIndex, dynamicModels);
        }
    }
}

void ConstructSingleButton(ButtonMaster* master, int i, int j, int* lastModelIndex, modelInfo** dynamicModels)
{
    printf("%i\n", *lastModelIndex);
    int centerR = round((float)master->rows / 2.0);
    int centerC = round((float)master->columns / 2.0);

    master->childButtons[i][j].buttonVectorLocation.x = i;
    master->childButtons[i][j].buttonVectorLocation.y = j;

    int multipleR = i - centerR;
    float locX = master->location.x + (multipleR * master->buttonSpread);
    int multipleC = j - centerC;
    float locY = master->location.y + (multipleC * master->buttonSpread);
    master->childButtons[i][j].location = (Vector3){master->location.x, locY, locX};
    
    //setting up our neighbors which will be important when cycling through
    //based on the player input
    int above = i < 1 ? master->rows - 1 : i - 1;
    int below = i >= master->rows ? 0 : i + 1;
    int left = j < 1 ? master->columns - 1 : j - 1;
    int right = j >= master->columns ? 0 : j + 1;

    master->childButtons[i][j].nAbove = &master->childButtons[above][j];
    master->childButtons[i][j].nBelow = &master->childButtons[below][j];
    master->childButtons[i][j].nLeft = &master->childButtons[i][left];
    master->childButtons[i][j].nRight = &master->childButtons[i][right];

    //initializng the associated models for the mechanic
    master->childButtons[i][j].model = malloc(sizeof(modelInfo));
    master->childButtons[i][j].model->collisionDisabled = true;
    master->childButtons[i][j].model->modelLocation = master->childButtons[i][j].location;
    master->childButtons[i][j].model->model = LoadModel("D:/CFiles/FirstGame/models/obj/button.obj");
    master->childButtons[i][j].model->texture = LoadTexture("D:/CFiles/FirstGame/models/obj/buttonIdle.png");
    master->childButtons[i][j].model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = master->childButtons[i][j].model->texture;
    dynamicModels[*lastModelIndex] = master->childButtons[i][j].model;
    *lastModelIndex = *lastModelIndex + 1;
    //highlighting our middle button
    if (i == centerR && j == centerC)
    {
        master->childButtons[i][j].highlighted = true;
        AddHighlight(&master->childButtons[i][j]);
    }
    
}

void DestructAllPuzzles(ButtonMaster** allPuzzles)
{
    for (int i = 0; i < NUMBER_OF_PUZZLES; i++)
    {
        DestructAllButtons(allPuzzles[i]);
        free(allPuzzles[i]);
    }
}

void DestructAllButtons(ButtonMaster* master)
{
    for (int i = 0; i < master->rows; i++)
    {
        free(master->childButtons[i]);
    }
}

// void AssignInteractBoxesToPuzzle(Interactable** interactables, ButtonMaster** master)
// {
//     //set location
//     //set interact function
//     //set size probably?
//     //assign to puzzle
//     for (int i = 0; i < NUMBER_OF_PUZZLES; i++)
//     {
//         for (int j = 0; j < NUMBER_OF_INTERACTABLES; j++)
//         {
//             if (interactables[j]->type == EGM_Puzzle && interactables[j]->hasBeenUsed == false)
//             {
//                 interactables[j]->hasBeenUsed = true;
//                 master[i]->associatedBox = interactables[j];
//                 SetupInteractBoxForPuzzle(master[i]);
//                 break;
//             }
//         }
//     }
// }

// void SetupInteractBoxForPuzzle(ButtonMaster* master)
// {
    
//     master->associatedBox->Location = master->location;
//     master->associatedBox->colBox->interact = PuzzleInteract;
// }

void PuzzleInteract(void)
{
    printf("puzzle interact!\n");
}

void MoveCursor(enum Direction direction, ButtonMaster* master)
{
    Button* currSelectedButton;
    bool found = false;
    for (int i = 0; i < master->rows; i++)
    {
        for (int j = 0; j < master->columns; j++)
        {
            if (master->childButtons[i][j].highlighted)
            {
                currSelectedButton = &master->childButtons[i][j];
                found = true;
                break;
            }
        }
        if (found)
        {
            break;
        }
    }
    
    switch (direction)
    {
        case ED_Up:
            RemoveHighlight(currSelectedButton);
            currSelectedButton = currSelectedButton->nAbove;
            AddHighlight(currSelectedButton);
            break;
        case ED_Down:
            RemoveHighlight(currSelectedButton);
            currSelectedButton = currSelectedButton->nBelow;
            AddHighlight(currSelectedButton);
            break;
        case ED_Left:
            RemoveHighlight(currSelectedButton);
            currSelectedButton = currSelectedButton->nLeft;
            AddHighlight(currSelectedButton);
            break;
        case ED_Right:
            RemoveHighlight(currSelectedButton);
            currSelectedButton = currSelectedButton->nRight;
            AddHighlight(currSelectedButton);
            break;
        case ED_Enter:
            break;
        default:
            printf("error default case run on switching highlight");
            break;
    }
}

void RemoveHighlight(Button* button)
{
    button->highlighted = false;
    button->model->texture = LoadTexture("D:/CFiles/FirstGame/models/obj/buttonIdle.png");
    button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture; 
}

void AddHighlight(Button* button)
{
    button->highlighted = true;
    button->model->texture = LoadTexture("D:/CFiles/FirstGame/models/obj/buttonHighlighted.png");
    button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture; 
}
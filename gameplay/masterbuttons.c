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
    //puzzle_01->solutionLocations = 
    ReadPuzzleCSV(puzzle_01,"D:/CFiles/FirstGame/filereading/csv/puzzle_01.csv");
    //
    allPuzzles[0] = puzzle_01;


    for (int i = 0; i < NUMBER_OF_PUZZLES; i++)
    {
        CreateAllButtons(allPuzzles[i], dynamicModels, lastModelIndex);
    }
    RotateButtonMaster(puzzle_01, 180.f, (Vector3){0.0f, 1.0f, 0.0f});
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
    //printf("%i\n", *lastModelIndex);
    int centerR = floor((float)master->rows / 2.0);
    int centerC = floor((float)master->columns / 2.0);

    master->childButtons[i][j].buttonVectorLocation.x = i;
    master->childButtons[i][j].buttonVectorLocation.y = j;

    int multipleR = i - centerR;
    float locX = master->location.x + (multipleR * master->buttonSpread);
    int multipleC = j - centerC;
    float locY = master->location.y + (multipleC * master->buttonSpread);
    master->childButtons[i][j].location = (Vector3){master->location.x, locY, locX};
    
    
    //setting up our neighbors which will be important when cycling through
    //based on the player input
    int below = j < 1 ? master->columns - 1 : j - 1;
    int above = j + 1 >= master->columns ? 0 : j + 1;
    int left = i < 1 ? master->rows - 1 : i - 1;
    int right = i + 1 >= master->rows ? 0 : i + 1;

    master->childButtons[i][j].nAbove = &master->childButtons[i][above];
    master->childButtons[i][j].nBelow = &master->childButtons[i][below];
    master->childButtons[i][j].nLeft = &master->childButtons[left][j];
    master->childButtons[i][j].nRight = &master->childButtons[right][j];

    for (int k = 0; k < master->rows; k++)
    {
        if (master->solutionLocations[k].x == i && master->solutionLocations[k].y == j)
        {
            master->childButtons[i][j].solutionButton = true;
        }
    }

    //initializng the associated models for the mechanic
    master->childButtons[i][j].model = malloc(sizeof(modelInfo));
    master->childButtons[i][j].model->collisionDisabled = true;
    master->childButtons[i][j].model->modelLocation = master->childButtons[i][j].location;
    master->childButtons[i][j].model->model = LoadModel("D:/CFiles/FirstGame/models/obj/button.obj");
    master->childButtons[i][j].model->texture = LoadTexture("D:/CFiles/FirstGame/models/obj/buttonIdle.png");
    master->childButtons[i][j].model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = master->childButtons[i][j].model->texture;
    master->childButtons[i][j].highlighted = false;
    master->childButtons[i][j].submitted = false;
    dynamicModels[*lastModelIndex] = master->childButtons[i][j].model;
    *lastModelIndex = *lastModelIndex + 1;
    //highlighting our middle button
    if (i == centerC && j == centerR)
    {
        master->childButtons[i][j].highlighted = true;
        AddHighlight(&master->childButtons[i][j]);
    }
    
}

void RotateButtonMaster(ButtonMaster* master, float angle, Vector3 axis)
{
    int centerR = floor((float)master->rows / 2.0);
    int centerC = floor((float)master->columns / 2.0);
    for (int i = 0; i < master->rows; i++)
    {
        for (int j = 0; j < master->columns; j++)
        {
            if (i == centerR && j == centerC)
            {
                master->childButtons[i][j].model->model.transform = MatrixRotateXYZ((Vector3){axis.x * angle, axis.y * angle, axis.z * angle});
                continue;
            }
            Vector3 newLocation = RotateAroundPoint(master->childButtons[i][j].location, master->childButtons[centerR][centerC].location, angle, axis);
            master->childButtons[i][j].location = newLocation;
            master->childButtons[i][j].model->modelLocation = master->childButtons[i][j].location; 
            master->childButtons[i][j].model->model.transform = MatrixRotateXYZ((Vector3){axis.x * angle, axis.y * angle, axis.z * angle});
        }
    }
}

void DestructAllPuzzles(ButtonMaster** allPuzzles)
{
    for (int i = 0; i < NUMBER_OF_PUZZLES; i++)
    {
        DestructAllButtons(allPuzzles[i]);
        DestructAllSolutionLocations(allPuzzles[i]);
        free(allPuzzles[i]);
        allPuzzles[i] = NULL;
    }
}

void DestructAllButtons(ButtonMaster* master)
{
    for (int i = 0; i < master->rows; i++)
    {
        free(master->childButtons[i]);
        master->childButtons[i] = NULL;
    }
}

void DestructAllSolutionLocations(ButtonMaster* master)
{
    free(master->solutionLocations);
    master->solutionLocations = NULL;
}

void PuzzleInteract(void)
{
    printf("puzzle interact!\n");
}

void MoveCursor(enum Direction direction, Interactable* interactedItem)
{
    ButtonMaster* master = interactedItem->associatedPuzzle;
    Button* currSelectedButton;
    if (master == NULL)
    {
        printf("master is null\n");
        return;
    }
    bool found = false;
    for (int i = 0; i < master->columns; i++)
    {
        for (int j = 0; j < master->rows; j++)
        {
            if (master->childButtons[i][j].highlighted == true)
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
    if (!found)
    {
        printf("highlighted button not found there is an error somewhere\n");
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
            ChangeSelection(currSelectedButton);
            CheckForSolution(currSelectedButton, master);
            break;
        default:
            printf("error default case run on switching highlight");
            break;
    }
}

void RemoveHighlight(Button* button)
{
    button->highlighted = false;
    if (button->submitted)
    {
        UnloadTexture(button->model->texture);
        button->model->texture = LoadTexture("D:/CFiles/FirstGame/models/obj/buttonSelected.png");
        button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture;
    }
    else
    {
        UnloadTexture(button->model->texture);
        button->model->texture = LoadTexture("D:/CFiles/FirstGame/models/obj/buttonIdle.png");
        button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture;
    }
}

void AddHighlight(Button* button)
{
    button->highlighted = true;
    UnloadTexture(button->model->texture);
    button->model->texture = LoadTexture("D:/CFiles/FirstGame/models/obj/buttonHighlighted.png");
    button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture; 
}

void ChangeSelection(Button* button)
{
    if (!button->submitted)
    {
        button->submitted = true;
        UnloadTexture(button->model->texture);
        button->model->texture = LoadTexture("D:/CFiles/FirstGame/models/obj/buttonSelected.png");
        button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture;
    }
    else
    {
        button->submitted = false;
        AddHighlight(button);
    }
}

void CheckForSolution(Button* button, ButtonMaster* master)
{
    
    int numberOfSolved = 0;
    for (int i = 0; i < master->rows; i++)
    {
        for (int j = 0; j < master->columns; j++)
        {
            if (master->childButtons[i][j].submitted && master->childButtons[i][j].solutionButton)
            {
                numberOfSolved++;
                printf("this was one of the buttons\n");
            }
            else if (master->childButtons[i][j].submitted && !master->childButtons[i][j].solutionButton)
            {
                numberOfSolved = 0;
                printf("this was NOT one of the buttons\n");
            }
        }
        
    }
    if (master->numberOfSolutions == numberOfSolved)
    {
        printf("congrats you solved the puzzle\n");
    }
    
}
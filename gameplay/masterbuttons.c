#include "masterbuttons.h"
#include <stdlib.h>
#include <stdio.h>

void ConstructPuzzles(ButtonMaster** allPuzzles, modelInfo** dynamicModels, int* lastModelIndex, enum Gametype gametype, FPSPlayer* player)
{
    if (gametype == EGT_A)
    {
        printf("last model index in construct puzzles: %i\n", *lastModelIndex);
        ConstructGameAPuzzles(allPuzzles, dynamicModels, lastModelIndex, player);
    }
    else
    {
        ConstructGameBPuzzles(allPuzzles, dynamicModels, lastModelIndex);
    }
    
}

void DestructAllPuzzles(ButtonMaster** allPuzzles, int numberOfPuzzles)
{
    for (int i = 0; i < numberOfPuzzles; i++)
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



void MoveCursor(enum Direction direction, Interactable* interactedItem, enum Gamemode* mode)
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
            CheckForSolution(currSelectedButton, master, mode);
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

void CheckForSolution(Button* button, ButtonMaster* master, enum Gamemode* mode)
{
    int numberOfSolved = 0;
    for (int i = 0; i < master->rows; i++)
    {
        for (int j = 0; j < master->columns; j++)
        {
            if (master->childButtons[i][j].submitted && master->childButtons[i][j].solutionButton)
            {
                numberOfSolved++;
                printf("this was one of the buttons, %i\n", numberOfSolved);
            }
            else if (master->childButtons[i][j].submitted && !master->childButtons[i][j].solutionButton)
            {
                numberOfSolved = 0;
                printf("this was NOT one of the buttons\n");
            }
        }
    }
    printf("number of solutions: %i\n", master->numberOfSolutions);
    if (master->numberOfSolutions == numberOfSolved)
    {
        printf("congrats you solved the puzzle\n");
        *mode = EGM_Normal;
        master->OnPuzzleSolved(master);
    }
}
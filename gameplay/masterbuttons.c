#include "masterbuttons.h"
#include <stdlib.h>
#include <stdio.h>

void ConstructPuzzles(ButtonMaster** allPuzzles, modelInfo** dynamicModels, int* lastModelIndex, enum Gametype gametype, FPSPlayer* player, GameplayElements* gameplayElements, Texture2D** allTextures)
{
    if (gametype == EGT_A)
    {
        printf("last model index in construct puzzles: %i\n", *lastModelIndex);
        ConstructGameAPuzzles(allPuzzles, allTextures, dynamicModels, lastModelIndex, player, gameplayElements);
    }
    else
    {
        ConstructGameBPuzzles(allPuzzles, allTextures, dynamicModels, lastModelIndex);
        printf("gametype b\n");
    }
}

void DestructAllPuzzles(ButtonMaster** allPuzzles, int numberOfPuzzles)
{
    for (int i = 0; i < numberOfPuzzles; i++)
    {
        
        DestructAllButtons(allPuzzles[i]);
        if (allPuzzles[i]->associatedGameplayElements != NULL)
        {
            free(allPuzzles[i]->associatedGameplayElements);
            allPuzzles[i]->associatedGameplayElements = NULL;
        }
        DestructAllSolutionLocations(allPuzzles[i]);
        
        printf("solution locations destroyed\n");
        free(allPuzzles[i]);
        allPuzzles[i] = NULL;
        
    }
    printf("puzzles freed\n");
}

void DestructAllButtons(ButtonMaster* master)
{
    for (int i = 0; i < master->rows; i++)
    {
        if (master->childButtons[i]->buttonRules != NULL)
        {
            free(master->childButtons[i]->buttonRules->toggleRule);
            free(master->childButtons[i]->buttonRules);  
            master->childButtons[i]->buttonRules->toggleRule = NULL; 
            master->childButtons[i]->buttonRules = NULL;
        }
        if (master->childButtons[i]->loadedShader != NULL)
        {
            free(master->childButtons[i]->loadedShader);
        }
        free(master->childButtons[i]->buttonTextures);
        free(master->childButtons[i]);
        master->childButtons[i]->buttonTextures = NULL;
        master->childButtons[i] = NULL;
    }
    for (int i = 0; i < master->numberOfSolutions; i++)
    {
        master->solutionButtons[i] = NULL;
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
    for (int i = 0; i < master->rows; i++)
    {
        for (int j = 0; j < master->columns; j++)
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
        case ED_Reset:
            //do reset thingys
            ResetPuzzle(master);
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
        button->model->texture = button->buttonTextures->selected;
        button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture;
        button->buttonState = EBS_selected;
    }
    else
    {
        button->model->texture = button->buttonTextures->idle;
        button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture;
        button->buttonState = EBS_idle;
    }
}

void ChangeSelection(Button* button)
{
    if (!button->submitted)
    {
        button->model->texture = button->buttonTextures->selected;
        button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture;
        button->submitted = true;
        if (button->ButtonSelected != NULL)
        {
            button->ButtonSelected(button);
        }
    }
    // else
    // {
    //     button->submitted = false;
    //     if (button->ButtonSelected != NULL)
    //     {
    //         button->ButtonSelected(button);
    //     }
    //     AddHighlight(button);
    // }
}

void CheckForSolution(Button* button, ButtonMaster* master, enum Gamemode* mode)
{
    int numberOfSolved = 0;
    int numberOfSelected = 0;
    if (master->isUnderExamination == false)
    {
        master->solvedOrder = malloc(sizeof(int) * master->numberOfSolutions);
        master->isUnderExamination = true;
        master->solvedOrderIndex = 0;
    }
    master->solvedOrder[master->solvedOrderIndex] = button->textureSizes;
    master->solvedOrderIndex++; 
    for (int i = 0; i < master->rows; i++)
    {
        for (int j = 0; j < master->columns; j++)
        {
            if (master->childButtons[i][j].submitted && master->childButtons[i][j].solutionButton)
            {
                numberOfSolved++;
                numberOfSelected++;
                printf("this was one of the buttons, %i\n", numberOfSolved);
            }
            else if (master->childButtons[i][j].submitted && !master->childButtons[i][j].solutionButton)
            {
                numberOfSolved = 0;
                numberOfSelected++;
                printf("this was NOT one of the buttons\n");
            }
        }
    }
    if (master->numberOfSolutions == numberOfSolved)
    {
        bool wasCorrectOrder = true;
        int prevIndex = 0;
        for (int i = 0; i < master->numberOfSolutions; i++)
        {
            printf("master solved order: %i, i: %i\n", master->solvedOrder[i], i);
            if (i - 1 < 0) continue;
            if (master->solvedOrder[i] < master->solvedOrder[i - 1])
            {
                wasCorrectOrder = false;
                break;
            }
        }
        if (wasCorrectOrder == true)
        {
            printf("congrats you solved the puzzle\n");
            *mode = EGM_Normal;
            master->OnPuzzleSolved(master);
            printf("puzzle solved end\n");
            free(master->solvedOrder);
            master->solvedOrder = NULL;
            master->isUnderExamination = false;
        }
        else
        {
            printf("these are the right buttons but were input in the incorrect order\n");
            ResetPuzzle(master);
        }
        
    }
    else
    {
        if (numberOfSelected >= (master->columns * master->rows))
        {
            printf("You have selected all of the present buttons, try again\n");
        }
    }
}

void ResetPuzzle(ButtonMaster* puzzle)
{
    for (int i = 0; i < puzzle->rows; i++)
    {
        for (int j = 0; j < puzzle->columns; j++)
        {
            puzzle->childButtons[i][j].buttonState = EBS_idle;
            puzzle->childButtons[i][j].model->texture = puzzle->childButtons[i][j].buttonTextures->idle;
            puzzle->childButtons[i][j].model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = puzzle->childButtons[i][j].model->texture; 
            puzzle->childButtons[i][j].submitted = false;
            if (puzzle->childButtons[i][j].highlighted == true)
            {
                puzzle->childButtons[i][j].highlighted = false;
            }
        }
    }
    
    if (puzzle->isUnderExamination == true)
    {
        free(puzzle->solvedOrder);
        puzzle->solvedOrder = NULL;
        puzzle->isUnderExamination = false;
    }

    puzzle->childButtons[puzzle->highlightStartLoc.x][puzzle->highlightStartLoc.y].buttonState = EBS_highlighted;
    puzzle->childButtons[puzzle->highlightStartLoc.x][puzzle->highlightStartLoc.y].model->texture = puzzle->childButtons[puzzle->highlightStartLoc.x][puzzle->highlightStartLoc.y].buttonTextures->highlighted; 
    puzzle->childButtons[puzzle->highlightStartLoc.x][puzzle->highlightStartLoc.y].model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = puzzle->childButtons[puzzle->highlightStartLoc.x][puzzle->highlightStartLoc.y].model->texture; 
    puzzle->highlightLocation = puzzle->highlightStartLoc;
    puzzle->childButtons[puzzle->highlightStartLoc.x][puzzle->highlightStartLoc.y].highlighted = true;
}
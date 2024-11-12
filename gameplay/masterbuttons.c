#include "masterbuttons.h"
#include <stdlib.h>
#include <stdio.h>

void ConstructPuzzles(ButtonMaster** allPuzzles, modelInfo** dynamicModels, int* lastModelIndex, enum Gametype gametype, FPSPlayer* player, GameplayElements* gameplayElements)
{
    if (gametype == EGT_A)
    {
        printf("last model index in construct puzzles: %i\n", *lastModelIndex);
        ConstructGameAPuzzles(allPuzzles, dynamicModels, lastModelIndex, player, gameplayElements);
    }
    else
    {
        ConstructGameBPuzzles(allPuzzles, dynamicModels, lastModelIndex);
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
        free(allPuzzles[i]);
        allPuzzles[i] = NULL;
    }
}

void DestructAllButtons(ButtonMaster* master)
{
    for (int i = 0; i < master->rows; i++)
    {
        UnloadButtonTextures(master->childButtons[i]);
        free(master->childButtons[i]->buttonTextures);
        free(master->childButtons[i]);
        master->childButtons[i] = NULL;
    }
}

void UnloadButtonTextures(Button* button)
{
    switch (button->buttonState)
    {
    case EBS_highlighted:
        TexturesToUnload(button->buttonTextures->idle, button->buttonTextures->selected);
        break;
    case EBS_idle:
        TexturesToUnload(button->buttonTextures->highlighted, button->buttonTextures->selected);
        break;
    case EBS_selected:
        TexturesToUnload(button->buttonTextures->idle, button->buttonTextures->highlighted);
        break;
    default:
        printf("ERROR!: BUTTON STATE UNSET IN BUTTON, NO TEXTURES WERE UNLOADED\n");
    }
}

void TexturesToUnload(Texture2D textureA, Texture2D textureB)
{
    UnloadTexture(textureA);
    UnloadTexture(textureB);
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
    int numberOfSelected = 0;
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
        printf("congrats you solved the puzzle\n");
        *mode = EGM_Normal;
        master->OnPuzzleSolved(master);
    }
    else
    {
        if (numberOfSelected >= (master->columns * master->rows))
        {
            printf("You have selected all of the present buttons, try again\n");
        }
    }
}


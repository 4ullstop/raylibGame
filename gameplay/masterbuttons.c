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
    free(master->correctOrder);
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
            if (currSelectedButton->nAbove->buttonState == EBS_off || currSelectedButton->nAbove->submitted == true) return;
            if (currSelectedButton->isAboveEdge == true)
            {
                return;
            }
            RemoveHighlight(currSelectedButton);
            currSelectedButton = currSelectedButton->nAbove;
            AddHighlight(currSelectedButton);
            master->cursoredButton = currSelectedButton;
            break;
        case ED_Down:
            if (currSelectedButton->nBelow->buttonState == EBS_off || currSelectedButton->nBelow->submitted == true) return;
            if (currSelectedButton->isBelowEdge == true)
            {
                return;
            }
            RemoveHighlight(currSelectedButton);
            currSelectedButton = currSelectedButton->nBelow;
            AddHighlight(currSelectedButton);
            master->cursoredButton = currSelectedButton;
            break;
        case ED_Left:
            if (currSelectedButton->nLeft->buttonState == EBS_off || currSelectedButton->nLeft->submitted == true) return;
            if (currSelectedButton->isLeftEdge == true)
            {
                return;
            }
            RemoveHighlight(currSelectedButton);
            currSelectedButton = currSelectedButton->nLeft;
            AddHighlight(currSelectedButton);
            master->cursoredButton = currSelectedButton;
            break;
        case ED_Right:
            if (currSelectedButton->nRight->buttonState == EBS_off || currSelectedButton->nRight->submitted == true) return;
            if (currSelectedButton->isRightEdge == true)
            {
                return;
            }
            RemoveHighlight(currSelectedButton);
            currSelectedButton = currSelectedButton->nRight;
            AddHighlight(currSelectedButton);
            master->cursoredButton = currSelectedButton;
            break;
        case ED_Enter:
            ChangeSelection(currSelectedButton);
            CheckForSolution(currSelectedButton, master, mode);
            currSelectedButton = PushCursor(currSelectedButton, master);
            master->cursoredButton = currSelectedButton;
            break;
        case ED_Reset:
            ResetPuzzle(master, false);
            break;
        default:
            printf("error default case run on switching highlight");
            break;
    }
}

Button* PushCursor(Button* button, ButtonMaster* master)
{
    int circledButtonNum = 8;
    Button* buttons[] = {
        button->nAbove,
        button->nAbove->nLeft,
        button->nLeft,
        button->nLeft->nBelow,
        button->nBelow,
        button->nBelow->nRight,
        button->nRight,
        button->nRight->nAbove
    };

    Button* buttonToHopTo = NULL;
    for (int i = 0; i < circledButtonNum; i++)
    {
        if (buttons[i]->submitted == false && buttons[i]->buttonState != EBS_off && buttons[i] != button)
        {
            buttonToHopTo = buttons[i];
            break;
        }
    }

    if (buttonToHopTo != NULL)
    {
        RemoveHighlight(button);
        AddHighlight(buttonToHopTo);
        return buttonToHopTo;
    }
    else
    {
        //nothing was found reset the puzzle
        printf("nothing was found, should reset puzzle\n");
        ResetPuzzle(master, false);
        return NULL;
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
    if (button->solutionButton == true)
    {
        master->solvedOrder[master->solvedOrderIndex] = button->textureSizes;
        master->solvedOrderIndex++;
    }
    for (int i = 0; i < master->rows; i++)
    {
        for (int j = 0; j < master->columns; j++)
        {
            if (master->childButtons[i][j].submitted == true && master->childButtons[i][j].solutionButton == true)
            {
                numberOfSolved++;
                numberOfSelected++;
                printf("this was one of the buttons, %i\n", numberOfSolved);
            }
            else if (master->childButtons[i][j].submitted == true && master->childButtons[i][j].solutionButton == false)
            {
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
            if (i - 1 < 0) continue;
            if (master->solvedOrder[i] != master->correctOrder[i])
            {
                wasCorrectOrder = false;
                master->solutionButtons[i]->wasFlippedIncorrectly = true;
            }
        }
        if (wasCorrectOrder == true)
        {
            printf("congrats you solved the puzzle\n");
            *mode = EGM_Normal;
            master->OnPuzzleSolved(master);
            master->shouldBlinkCursor = false;
            printf("puzzle solved end\n");
            free(master->solvedOrder);
            master->solvedOrder = NULL;
            master->isUnderExamination = false;
        }
        else
        {
            printf("these are the right buttons but were input in the incorrect order\n");
            ResetPuzzle(master, true);
        }
        
    }
    else
    {
        if (numberOfSelected >= (master->columns * master->rows))
        {
            printf("You have selected all of the present buttons, try again\n");
            ResetPuzzle(master, true);
        }
    }
    ResetTemporaryPuzzleInfo(master);
}

void ResetTemporaryPuzzleInfo(ButtonMaster* puzzle)
{
    for (int i = 0; i < puzzle->rows; i++)
    {
        for (int j = 0; j < puzzle->columns; j++)
        {
            puzzle->childButtons[i][j].wasFlippedIncorrectly = false;
        }
    }
}

void ResetPuzzle(ButtonMaster* puzzle, bool resultOfFailure)
{
    puzzle->shouldBlinkCursor = false;
    if (resultOfFailure == true)
    {
        ErrorButtons* errorButtons = NULL;
        PopulateErrorButtons(puzzle, &errorButtons);
        puzzle->errorButtons = errorButtons;
        puzzle->player->puzzleInputEnabled = false;
        puzzle->shouldReadTick = true;
        puzzle->puzzleUnSolved = true;
        return;
    }
    for (int i = 0; i < puzzle->rows; i++)
    {
        for (int j = 0; j < puzzle->columns; j++)
        {
            if (puzzle->childButtons[i][j].buttonState == EBS_off)
            {
                continue;
            }
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

void PopulateErrorButtons(ButtonMaster* puzzle, ErrorButtons** errorButtons)
{
    
    for (int i = 0; i < puzzle->rows; i++)
    {
        for (int j = 0; j < puzzle->columns; j++)
        {
            printf("i: %i, j: %i\n", i, j);
            if (puzzle->childButtons[i][j].wasFlippedIncorrectly == true)
            {
                printf("button added to population\n");
                ErrorButtons* newNode = malloc(sizeof(ErrorButtons));
                newNode->button = &puzzle->childButtons[i][j];
                newNode->next = *errorButtons;
                *errorButtons = newNode;
            }
        }
    }
    
}

void PollPuzzles(ButtonMaster* puzzle, TickNode* tickNode)
{
    if (puzzle == NULL) return;
    if (puzzle->shouldReadTick == true)
    {
        //blink cursor here
        if (puzzle->shouldBlinkCursor == true)
        {
            BlinkCursor(puzzle, tickNode);
        }
        
        if (puzzle->puzzleUnSolved == true)
        {
            //blink here for errors
            RunThroughErrorButtons(puzzle, tickNode, puzzle->errorButtons);
        }
    }
}

void BlinkCursor(ButtonMaster* puzzle, TickNode* tickNode)
{
    if (puzzle->cursoredButton == NULL) return;
    
    tickNode->frameCounter = tickNode->frameCounter + 1;
    if (tickNode->frameCounter >= (60/tickNode->frameSpeed))
    {
        tickNode->frameCounter = 0;
        tickNode->iterations = tickNode->iterations + 1;


        if (tickNode->a == false)
        {
            tickNode->a = true;
            if (puzzle->cursoredButton->submitted == true)
            {
                puzzle->cursoredButton->model->texture = puzzle->cursoredButton->buttonTextures->selected;
            }
            else
            {
                puzzle->cursoredButton->model->texture = puzzle->cursoredButton->buttonTextures->idle;
            }
        }
        else
        {
            tickNode->a = false;
            puzzle->cursoredButton->model->texture = puzzle->cursoredButton->buttonTextures->highlighted;
        }
        puzzle->cursoredButton->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = puzzle->cursoredButton->model->texture;
    }
}

void RunThroughErrorButtons(ButtonMaster* puzzle, TickNode* tickNode, ErrorButtons* errorButtons)
{
    ErrorButtons* buttonsToError = errorButtons;
    if (buttonsToError == NULL)
    {
        printf("error bruh is null\n");
    }
    tickNode->frameCounter = tickNode->frameCounter + 1;
    bool wasFired = false;
    
    while (buttonsToError != NULL)
    {
        
        wasFired = BlinkError(buttonsToError->button, tickNode);
        buttonsToError = buttonsToError->next;
        
    }
    if (wasFired == true)
    {
        tickNode->frameCounter = 0;
        if (tickNode->a == true)
        {
            tickNode->a = false;
        }
        else
        {
            tickNode->a = true;
        }
    }
    tickNode->iterations = tickNode->iterations + 1;
    if (tickNode->iterations >= 2000)
    {
        puzzle->player->puzzleInputEnabled = true;
        if (tickNode->iterations >= 4000)
        {
            puzzle->puzzleUnSolved = false;
            DepopulateErrorButtons(puzzle->errorButtons);
            ResetPuzzle(puzzle, false);
        }
    }
    buttonsToError = NULL;
}

bool BlinkError(Button* button, TickNode* tickNode)
{
    bool wasFired = false;
    if (tickNode->frameCounter >= (60/tickNode->frameSpeed))
    {
        wasFired = true;
        if (tickNode->a == false)
        {
            if (button->submitted == true)
            {
                button->model->texture = button->buttonTextures->selected;
            }
            else
            {
                button->model->texture = button->buttonTextures->idle;
            }
        }
        else
        {
            button->model->texture = button->buttonTextures->error;
        }
    }
    button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture;
    return wasFired;
}

void DepopulateErrorButtons(ErrorButtons* buttons)
{
    if (buttons == NULL)
    {
        return;
    }
    else
    {
        DepopulateErrorButtons(buttons->next);
        free(buttons);
        buttons = NULL;
    }
}
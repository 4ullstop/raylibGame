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
        ConstructGameBPuzzles(allPuzzles, allTextures, dynamicModels, lastModelIndex, player, gameplayElements);
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
    bool checkForEdges = false;
    switch (direction)
    {
        case ED_Up:
            if (currSelectedButton->nAbove->buttonState == EBS_off) return;
            if (currSelectedButton->isAboveEdge == true && checkForEdges == true)
            {
                return;
            }
            RemoveHighlight(currSelectedButton);
            currSelectedButton = currSelectedButton->nAbove;
            AddHighlight(currSelectedButton);
            master->cursoredButton = currSelectedButton;
            break;
        case ED_Down:
            if (currSelectedButton->nBelow->buttonState == EBS_off) return;
            if (currSelectedButton->isBelowEdge == true && checkForEdges == true)
            {
                return;
            }
            RemoveHighlight(currSelectedButton);
            currSelectedButton = currSelectedButton->nBelow;
            AddHighlight(currSelectedButton);
            master->cursoredButton = currSelectedButton;
            break;
        case ED_Left:
            if (currSelectedButton->nLeft->buttonState == EBS_off) return;
            if (currSelectedButton->isLeftEdge == true && checkForEdges == true)
            {
                return;
            }
            RemoveHighlight(currSelectedButton);
            currSelectedButton = currSelectedButton->nLeft;
            AddHighlight(currSelectedButton);
            master->cursoredButton = currSelectedButton;
            break;
        case ED_Right:
            if (currSelectedButton->nRight->buttonState == EBS_off) return;
            if (currSelectedButton->isRightEdge == true && checkForEdges == true)
            {
                return;
            }
            RemoveHighlight(currSelectedButton);
            currSelectedButton = currSelectedButton->nRight;
            AddHighlight(currSelectedButton);
            master->cursoredButton = currSelectedButton;
            break;
        case ED_Enter:
            ChangeSelection(currSelectedButton, master);
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
	if (button->isRightEdge == true)
	{
	    if (i == 6 || i == 7 || i == 5) continue;
	}
	if (button->isLeftEdge == true)
	{
	    if (i == 2 || i == 3 || i == 1) continue;
       	}
	if (button->isAboveEdge == true)
	{
	    if (i == 0 || i == 1 || i == 7) continue;
	}
	if (button->isBelowEdge == true)
	{
	    if (i == 3 || i == 5 || i == 4) continue;
       	}
	
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

bool PushedCheckForEdges(Button* button)
{
    return button->isRightEdge == true || button->isLeftEdge == true || button->isBelowEdge == true || button->isAboveEdge == true;
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

void ChangeSelection(Button* button, ButtonMaster* puzzle)
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
	if (button->solutionButton == true)
	{
	    AddItemToSolvedButtonList(&puzzle->solvedButtons, button->textureSizes);
	    puzzle->numOfSolved = puzzle->numOfSolved + 1;
	    puzzle->numOfSelected = puzzle->numOfSelected + 1;
	    printf("this was one of the buttons\n");
	}
    }
    else
    {
        button->submitted = false;
        if (button->ButtonSelected != NULL)
        {
            button->ButtonSelected(button);
        }
	if (button->solutionButton == true)
	{
	    printf("removing item from linked list\n");
	    RemoveItemToSolvedButtonList(&puzzle->solvedButtons, button->textureSizes);
	    puzzle->numOfSolved = puzzle->numOfSolved - 1;
	}
	
        AddHighlight(button);
    }
}

void CheckForSolution(Button* button, ButtonMaster* puzzle, enum Gamemode* mode)
{
    bool answerFound = false;
    if (puzzle->numberOfSolutions == puzzle->numOfSolved)
    {
	puzzle->errorButtons = malloc(sizeof(ErrorButtons));
	printf("numOfSolutions: %i\n", puzzle->numberOfSolutions);
	bool wasCorrectOrder = true;
	SolvedButtons* solvedButtons = puzzle->solvedButtons;
	for (int i = 0; i < puzzle->numberOfSolutions; i++)
	{
	    if (puzzle->correctOrder[i] != solvedButtons->textureSizes)
	    {
		Button* incorrectButton = NULL;
		for (int j = 0; j < puzzle->numberOfSolutions; j++)
		{
		    if (puzzle->solutionButtons[j]->textureSizes == solvedButtons->textureSizes)
		    {
			incorrectButton = puzzle->solutionButtons[j];
			printf("incorrectButton found\n"); 
			break;
		    }
		}
		
		wasCorrectOrder = false;
		printf("solved button: %i\n", solvedButtons->textureSizes);
		printf("incorrectButton id: %i\n", incorrectButton->id);
		puzzle->errorButtons->next = NULL;
		AddButtonToErrorList(incorrectButton, &puzzle->errorButtons);
	    }
	    solvedButtons = solvedButtons->next;
	}
	if (wasCorrectOrder == true)
	{
	    printf("Congrats, you solved the puzzle!\n");
	    *mode = EGM_Normal;
	    puzzle->shouldBlinkCursor = false;
	    ClearSolvedButtons(puzzle->solvedButtons);
	    puzzle->solvedButtons = NULL;
	    answerFound = true;
	    PuzzleCompleted(puzzle);
	    puzzle->player->puzzleInputType = EPIT_ResetOnly;
	    puzzle->puzzleHasBeenSolved = true;
       	}
	else
	{
	    
	    printf("These are the right buttons input in the incorrect order\n");
	    
	    ResetPuzzle(puzzle, true);
	}
    }
    else
    {
	if (puzzle->numOfSelected >= (puzzle->columns * puzzle->rows) && answerFound == false)
	{
	    printf("You have selected all of the present buttons, try again\n");
	    ResetPuzzle(puzzle, true);
	}
    }
}

void AddButtonToErrorList(Button* button, ErrorButtons** errorButton)
{
    ErrorButtons* newButton = (ErrorButtons*)malloc(sizeof(ErrorButtons));

    if (newButton == NULL)
    {
	printf("Failed to allocate for errorbutton nodes\n");
	return;
    }

    newButton->button = button;
    newButton->next = *errorButton;
    *errorButton = newButton;
    
    printf("button id added to list: %i\n", button->id);
}

void AddItemToSolvedButtonList(SolvedButtons** head, enum ButtonTextureSizes textureSizesToAdd)
{
    SolvedButtons* newNode = (SolvedButtons*)malloc(sizeof(SolvedButtons));
    if (newNode == NULL)
    {
	printf("ERROR, Failed to allocated memory for solved button list\n");
	return;
    }

    newNode->textureSizes = textureSizesToAdd;
    newNode->next = NULL;

    if (*head == NULL)
    {
	*head = newNode;
	return;
    }

    SolvedButtons* lastNode = *head;
    while (lastNode->next != NULL)
    {
	lastNode = lastNode->next;
    }
    
    lastNode->next = newNode;
}

void RemoveItemToSolvedButtonList(SolvedButtons** head, enum ButtonTextureSizes buttonToRemove)
{
    SolvedButtons* current = *head;
    SolvedButtons* previous = NULL;

    if (current == NULL)
    {
	return;
    }

    if (current->textureSizes == buttonToRemove)
    {
	*head = current->next;
	free(current);
	return;
    }

    while (current != NULL && current->textureSizes != buttonToRemove)
    {
	previous = current;
	current = current->next;
    }

    if (current == NULL)
    {
	return;
    }

    previous->next = current->next;
    free(current);
}

void ClearSolvedButtons(SolvedButtons* solvedButtons)
{
    SolvedButtons* current = solvedButtons;
    SolvedButtons* next;

    while (current != NULL)
    {
	next = current->next;
	free(current);
	current = next;
    }
}

void ResetPuzzle(ButtonMaster* puzzle, bool resultOfFailure)
{
    puzzle->shouldBlinkCursor = false;
    puzzle->numOfSelected = 0;
    puzzle->numOfSolved = 0;
    if (resultOfFailure == true)
    {
        puzzle->player->puzzleInputType = EPIT_Disabled;
        puzzle->shouldReadTick = true;
        puzzle->puzzleUnSolved = true;
	printf("about to blink cursor\n");
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
	    if (puzzle->childButtons[i][j].shouldStaySubmitted == true)
	    {
		printf("button should stay submitted\n");
		puzzle->childButtons[i][j].buttonState = EBS_selected;
		puzzle->childButtons[i][j].model->texture = puzzle->childButtons[i][j].buttonTextures->selected;
		puzzle->childButtons[i][j].model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = puzzle->childButtons[i][j].model->texture;
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

    ClearSolvedButtons(puzzle->solvedButtons);
    puzzle->solvedButtons = NULL;
   
    puzzle->childButtons[puzzle->highlightStartLoc.x][puzzle->highlightStartLoc.y].buttonState = EBS_highlighted;
    puzzle->childButtons[puzzle->highlightStartLoc.x][puzzle->highlightStartLoc.y].model->texture = puzzle->childButtons[puzzle->highlightStartLoc.x][puzzle->highlightStartLoc.y].buttonTextures->highlighted; 
    puzzle->childButtons[puzzle->highlightStartLoc.x][puzzle->highlightStartLoc.y].model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = puzzle->childButtons[puzzle->highlightStartLoc.x][puzzle->highlightStartLoc.y].model->texture; 
    puzzle->highlightLocation = puzzle->highlightStartLoc;
    puzzle->childButtons[puzzle->highlightStartLoc.x][puzzle->highlightStartLoc.y].highlighted = true;


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
        
        if (tickNode->iterations >= 4000)
        {
            puzzle->puzzleUnSolved = false;
	    tickNode->iterations = 0;
	    puzzle->player->puzzleInputType = EPIT_Enabled;
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

void PuzzleCompleted(ButtonMaster* puzzle)
{
    for (int i = 0; i < puzzle->numberOfSolutions; i++)
    {
	puzzle->solutionButtons[i]->model->texture = puzzle->solutionButtons[i]->buttonTextures->completed;
	puzzle->solutionButtons[i]->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = puzzle->solutionButtons[i]->model->texture;
    }
}

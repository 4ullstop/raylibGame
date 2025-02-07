#include "masterbuttons.h"
#include "../shared/sharedpuzzle.h"
#include "puzzles/movepuzzle.h"
#include "puzzles/poweronpuzzle.h"
#include <stdlib.h>
#include <stdio.h>

void ConstructPuzzles(ButtonMaster** allPuzzles, modelInfo** dynamicModels, int* lastModelIndex, enum Gametype gametype, FPSPlayer* player, GameplayElements* gameplayElements, Texture2D** allTextures, SharedMemory* sharedMemory, SharedPuzzleList* sharedPuzzleList, ExitCode* exitCode)
{
    if (gametype == EGT_A)
    {
        printf("last model index in construct puzzles: %i\n", *lastModelIndex);
        ConstructGameAPuzzles(allPuzzles, allTextures, dynamicModels, lastModelIndex, player, gameplayElements, sharedMemory, sharedPuzzleList, exitCode);
    }
    else
    {
        ConstructGameBPuzzles(allPuzzles, allTextures, dynamicModels, lastModelIndex, player, gameplayElements, sharedMemory, sharedPuzzleList, exitCode);
        printf("gametype b\n");
    }
}

void MoveCursor(enum Direction direction, Interactable* interactedItem, enum Gamemode* mode, OpenSharedValues* openSharedValues, bool isPlayerSharingPuzzle, enum Gametype gametype, ExitCode* exitCode)
{
    printf("moving cursor\n");
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


    Button* aboveCurrSelected = currSelectedButton->nAbove;
    Button* belowCurrSelected = currSelectedButton->nBelow;
    Button* leftCurrSelected = currSelectedButton->nLeft;
    Button* rightCurrSelected = currSelectedButton->nRight;
    
    if (master->sharedPuzzle == true && isPlayerSharingPuzzle == false)
    {
	SharedButtonNeighborDetermination(&leftCurrSelected, &rightCurrSelected, &aboveCurrSelected, &belowCurrSelected, currSelectedButton, master);
    }
    
    bool isConsumer = IsPuzzleConsumer(master, openSharedValues);

    if (currSelectedButton->buttonRules != NULL && currSelectedButton->buttonRules->moveRule != NULL)
    {
	DetermineWindowMovement(direction, currSelectedButton);
    }
    
    switch (direction)
    {
        case ED_Up:
            if (currSelectedButton->nAbove->buttonState == EBS_off || aboveCurrSelected == EBS_off) return;
            if (currSelectedButton->isAboveEdge == true && checkForEdges == true)
            {
                return;
            }
	    HandleCursorMovement(currSelectedButton, aboveCurrSelected, master, openSharedValues, isConsumer, isPlayerSharingPuzzle);
            break;
        case ED_Down:
            if (currSelectedButton->nBelow->buttonState == EBS_off || belowCurrSelected == EBS_off) return;
            if (currSelectedButton->isBelowEdge == true && checkForEdges == true)
            {
                return;
            }
	    HandleCursorMovement(currSelectedButton, belowCurrSelected, master, openSharedValues, isConsumer, isPlayerSharingPuzzle);
            break;
        case ED_Left:
            if (currSelectedButton->nLeft->buttonState == EBS_off || leftCurrSelected == EBS_off) return;
            if (currSelectedButton->isLeftEdge == true && checkForEdges == true)
            {
                return;
            }
	    HandleCursorMovement(currSelectedButton, leftCurrSelected, master, openSharedValues, isConsumer, isPlayerSharingPuzzle);
            break;
        case ED_Right:
            if (currSelectedButton->nRight->buttonState == EBS_off || rightCurrSelected == EBS_off) return;
            if (currSelectedButton->isRightEdge == true && checkForEdges == true)
            {
                return;
            }
	    HandleCursorMovement(currSelectedButton, rightCurrSelected, master, openSharedValues, isConsumer, isPlayerSharingPuzzle);
            break;
        case ED_Enter:
	    Button* oldButton = master->cursoredButton;
	    master->cursoredButton = HandleCursorSelection(currSelectedButton, master, mode, isPlayerSharingPuzzle, isConsumer, openSharedValues, gametype, exitCode);
	    MakeDeterminationForPreSubmittedButtons(master, oldButton, openSharedValues);
	    printf("enter action complete\n");
            break;
        case ED_Reset:
	    openSharedValues->puzzleSharedValues->inputDirection = ED_Reset;
	    printf("\n");
	    printf("case ed reset\n");
	    printf("\n");
	    if (isPlayerSharingPuzzle == true && openSharedValues->mainSharedValues != NULL)
	    {
		printf("\n");
		printf("handling producer input reset\n");
		printf("\n");
		HandleProducerInput(master, currSelectedButton, currSelectedButton, openSharedValues, isConsumer);
	    }
	    WipePreSubmittedList(openSharedValues);
            ResetPuzzle(master, false);
            break;
         default:
            printf("error default case run on switching highlight");
            break;
    }
}

//this is to be called external no matter whether the consumer is in a puzzle or not
void PollConsumerExternal(OpenSharedValues* openSharedValues, enum Gamemode* mode, enum Gametype gametype, SharedPuzzleList* sharedPuzzleList, ExitCode* exitCode)
{
    
    if (openSharedValues->mainSharedValues == NULL) return;
    
   
    if (openSharedValues->mainSharedValues->flagExtConsumer == 0) return;
    printf("flag has been set cont\n");
    if (openSharedValues->puzzleSharedValues->puzzleId == 0) return;
    printf("shared puzzle id is open cont\n");

    if (gametype == EGT_B && openSharedValues->mainSharedValues->ActiveWindowA == false)
    {
	printf("for some reason game b is the consumer\n");
	return;
    }

    ButtonMaster* sharedPuzzle = SearchForSharedPuzzle(sharedPuzzleList, openSharedValues->puzzleSharedValues->puzzleId);
    if (sharedPuzzle == NULL)
    {
	printf("Error puzzle not found\n");
	printf("sharedPuzzleId: %i\n", openSharedValues->puzzleSharedValues->puzzleId);
	openSharedValues->mainSharedValues->flagExtConsumer = 0;
	return;
    }
    if (IsPuzzleConsumer(sharedPuzzle, openSharedValues) == false) return;
    printf("puzzle is consumer cont\n");
    WipePreSubmittedList(openSharedValues);
    FillListFromBuffer(openSharedValues, sharedPuzzle);
    openSharedValues->puzzleSharedValues->sharedCursorLocation = sharedPuzzle->cursoredButton->buttonVectorLocation;
    openSharedValues->puzzleSharedValues->preSubmitIndex = openSharedValues->submitIndexBuffer;
    openSharedValues->mainSharedValues->consumerPost = true;
    openSharedValues->mainSharedValues->preSubmitCheck = false;
    openSharedValues->mainSharedValues->flagExtConsumer = 0;
    openSharedValues->mainSharedValues->flagProducer = 1;
    printf("\n");
    printf("\n");
    printf("consumer inputs posted\n");
    printf("\n");
    printf("\n");
}

ButtonMaster* SearchForSharedPuzzle(SharedPuzzleList* sharedPuzzles, int puzzleId)
{
    printf("about to search for puzzle\n");
    if (sharedPuzzles == NULL)
    {
	printf("shared puzzles is null\n");
    }
    SharedPuzzleList* current = sharedPuzzles;
    while (current != NULL)
    {
	if (current->sharedId == puzzleId)
	{
	    return current->puzzle;
	}
	current = current->next;
	printf("searching for puzzle\n");
    }
    return NULL;
}

void EnteringDetermination(ButtonMaster* puzzle, OpenSharedValues* openSharedValues, enum Gametype gametype, ExitCode* exitCode, enum Gamemode* gamemode)
{
    printf("making entering determination\n");
    if (puzzle->sharedPuzzle == false || openSharedValues->mainSharedValues == NULL) return;
    
    printf("past early returns\n");
    printf("\n");

    
    
    if (IsPuzzleConsumer(puzzle, openSharedValues) == false)
    {
	//yo consumer are there any submitted buttons?
	if (openSharedValues->mainSharedValues->sharingPuzzles == true) return;
	printf("entering determination here\n");
//	openSharedValues->mainSharedValues->flag = 1;
	openSharedValues->puzzleSharedValues->puzzleId = puzzle->sharedPuzzleId;
	printf("grabbing puzzle id\n");
	openSharedValues->mainSharedValues->preSubmitCheck = true;
//	openSharedValues->mainSharedValues->flagProducer = 1;
	openSharedValues->mainSharedValues->flagExtConsumer = 1;
	printf("setting producer flag\n");
    }
}

void FillListFromBuffer(OpenSharedValues* openSharedValues, ButtonMaster* puzzle)
{

    PreSubmittedList* current = puzzle->submitBuffer;
    PreSubmittedList* next;
    int i = 0;
    while(current != NULL)
    {
	openSharedValues->puzzleSharedValues->preSubmittedButtons[i] = current->submittedButton->buttonVectorLocation;
	current = current->next;
	i++;
    }
    
}

void RunThroughPreSubmittedButtons(OpenSharedValues* openSharedValues, ButtonMaster* puzzle, enum Gametype gametype, ExitCode* exitCode, enum Gamemode* gamemode)
{
    if (openSharedValues->puzzleSharedValues->preSubmitIndex + 1 == puzzle->numOfSelected)
    {
	printf("the number of submitted is the same as the report\n");
	return;
    }
    for (int i = 0, n = openSharedValues->puzzleSharedValues->preSubmitIndex; i < n; i++)
    {
	int x = openSharedValues->puzzleSharedValues->preSubmittedButtons[i].x;
	int y = openSharedValues->puzzleSharedValues->preSubmittedButtons[i].y;
	Button* currButton = &puzzle->childButtons[x][y];
	printf("adding button and changing selection\n");
	printf("\n");

	if (currButton->submitted == true)
	{
	    printf("current state is selected, do not change\n");
	    continue;
	}
	ChangeSelection(currButton, puzzle, openSharedValues, gametype, exitCode);

	CheckForSolution(currButton, puzzle, gamemode); 
    }
    for (int i = 0; i < puzzle->rows; i++)
    {
	for (int j = 0; j < puzzle->columns; j++)
	{
	    if (puzzle->childButtons[i][j].highlighted == true) puzzle->childButtons[i][j].highlighted = false;
	}
    }
}

void MakeDeterminationForPreSubmittedButtons(ButtonMaster* puzzle, Button* button, OpenSharedValues* openSharedValues)
{
    printf("about to make determination for pre submitted buttons\n");
    printf("\n");
    //regardless of whether the shared memory is open or not, put the information of the submitted buttons into  the buffer to be read later
    if (puzzle->sharedPuzzle == false) return;
    AddButtonToPreSubmittedBuffer(button, &puzzle->submitBuffer);
    openSharedValues->submitIndexBuffer = openSharedValues->submitIndexBuffer + 1;
}

void AddButtonToPreSubmittedBuffer(Button* button, PreSubmittedList** head)
{
    printf("adding button to list\n");
    PreSubmittedList* newNode = (PreSubmittedList*)malloc(sizeof(PreSubmittedList));
    if (newNode == NULL)
    {
	printf("ERROR FAILED TO ALLOCATE MEMORY FOR SOLVED BUTTON LIST\n");
	return;
    }
    newNode->submittedButton = button;
    newNode->next = NULL;

    if (*head == NULL)
    {
	*head = newNode;
	return;
    }

    PreSubmittedList* lastNode = *head;
    while (lastNode->next != NULL)
    {
	lastNode = lastNode->next;
    }
    lastNode->next = newNode;
}

void AddButtonToPreSubmittedList(Button* button, OpenSharedValues* openSharedValues)
{
    int index = openSharedValues->puzzleSharedValues->preSubmitIndex;
    openSharedValues->puzzleSharedValues->preSubmittedButtons[index].x = button->buttonVectorLocation.x;
    openSharedValues->puzzleSharedValues->preSubmittedButtons[index].y = button->buttonVectorLocation.y;
    openSharedValues->puzzleSharedValues->preSubmitIndex = openSharedValues->puzzleSharedValues->preSubmitIndex + 1;
}

void WipePreSubmittedList(OpenSharedValues* openSharedValues)
{
    if (openSharedValues->mainSharedValues == NULL || openSharedValues->puzzleSharedValues->preSubmitIndex == 0) return;
    for (int i = 0, n = openSharedValues->puzzleSharedValues->preSubmitIndex + 1; i < n; i++)
    {
	openSharedValues->puzzleSharedValues->preSubmittedButtons[i] = (Vector2Int){0, 0};
    }
    openSharedValues->puzzleSharedValues->preSubmitIndex = 0;
}

void SharedButtonNeighborDetermination(Button** leftCurrSelected, Button** rightCurrSelected, Button** aboveCurrSelected, Button** belowCurrSelected, Button* currSelectedButton, ButtonMaster* puzzle)
{
    printf("making determination\n");
    if (puzzle->gameAPuzzle == true)
    {
	if (currSelectedButton->buttonVectorLocation.x + 1 == (puzzle->rows / 2))
	{
	    if (puzzle->childButtons[0][currSelectedButton->buttonVectorLocation.y].buttonState == EBS_off) return;
	    *rightCurrSelected = &puzzle->childButtons[0][currSelectedButton->buttonVectorLocation.y];
	}
	else if (currSelectedButton->buttonVectorLocation.x == 0)
	{
	    printf("about to make left side determination\n");
	    if (puzzle->childButtons[(puzzle->rows / 2) - 1][currSelectedButton->buttonVectorLocation.y].buttonState == EBS_off)
	    {
		*leftCurrSelected  = currSelectedButton;
		return;
	    }
	    printf("left curr selected assigned\n");
	    *leftCurrSelected = &puzzle->childButtons[(puzzle->rows / 2) - 1][currSelectedButton->buttonVectorLocation.y];
	}
    }
    else
    {
	printf("button location: %i\n", currSelectedButton->buttonVectorLocation.x);
	if (currSelectedButton->buttonVectorLocation.x + 1 == puzzle->rows)
	{
	    if (puzzle->childButtons[(puzzle->rows / 2)][currSelectedButton->buttonVectorLocation.y].buttonState == EBS_off) return;
	    *rightCurrSelected = &puzzle->childButtons[(puzzle->rows / 2)][currSelectedButton->buttonVectorLocation.y];
	}
	else if (currSelectedButton->buttonVectorLocation.x == (puzzle->rows / 2))
	{
	    if (puzzle->childButtons[puzzle->rows - 1][currSelectedButton->buttonVectorLocation.y].buttonState == EBS_off) return;
	    *leftCurrSelected = &puzzle->childButtons[puzzle->rows - 1][currSelectedButton->buttonVectorLocation.y];
 	}
    }
}

Button* HandleCursorSelection(Button* currSelectedButton, ButtonMaster* puzzle, enum Gamemode* gameMode, bool isSharedPuzzle, bool isConsumer, OpenSharedValues* openSharedValues, enum Gametype gametype, ExitCode* exitCode)
{
    Button* oldButton = currSelectedButton;

    ChangeSelection(currSelectedButton, puzzle, openSharedValues, gametype, exitCode);
    if (CheckForSolution(currSelectedButton, puzzle, gameMode) == true)
    {
	printf("solution check is true returning null\n");
	if (isConsumer == true)
	{
	    printf("consumer found solution should be exiting puzzle view\n");
	    printf("\n");
	}
	if (openSharedValues->mainSharedValues != NULL && openSharedValues->mainSharedValues->sharingPuzzles == true)
	{
	    openSharedValues->puzzleSharedValues->inputDirection = ED_Enter;
	    HandleProducerInput(puzzle, oldButton, currSelectedButton, openSharedValues, isConsumer);
	}
	return NULL;
    }


    currSelectedButton = PushCursor(currSelectedButton, puzzle, openSharedValues);

    if (currSelectedButton == NULL)
    {
	return NULL;
    }
    if (isSharedPuzzle == true && openSharedValues->mainSharedValues != NULL && currSelectedButton->puzzleType != EPT_WindowPower)
    {
	HandleProducerInput(puzzle, oldButton, currSelectedButton, openSharedValues, isConsumer);
    }

    printf("cursor selection complete for producer\n");
    return currSelectedButton;
    
}

void HandleCursorMovement(Button* currSelectedButton, Button* newButton, ButtonMaster* puzzle, OpenSharedValues* openSharedValues, bool isConsumer, bool isSharedPuzzle)
{
    if (isSharedPuzzle == true && openSharedValues->mainSharedValues != NULL)
    {
	printf("handing cursor movement for shared puzzle\n");
	HandleProducerInput(puzzle, currSelectedButton, newButton, openSharedValues, isConsumer);
    }

    RemoveHighlight(currSelectedButton);
    currSelectedButton = newButton;
    AddHighlight(currSelectedButton);
    puzzle->cursoredButton = currSelectedButton;

}

Button* FindCursoredButton(ButtonMaster* puzzle)
{
    bool found = false;
    for (int i = 0; i < puzzle->rows; i++)
    {
	for (int j = 0; j < puzzle->columns; j++)
	{
	    if (puzzle->childButtons[i][j].highlighted == true)
	    {
		return &puzzle->childButtons[i][j];
	    }
	}
    }
    return NULL;
}

void PollProducer(OpenSharedValues* openSharedValues, ButtonMaster* puzzle, enum Gamemode* mode, enum Gametype gametype, ExitCode* exitCode)
{
    if (openSharedValues->mainSharedValues->flagProducer == 0) return;
    
    
    if (IsPuzzleConsumer(puzzle, openSharedValues) == true) return;

    



    if (openSharedValues->mainSharedValues->consumerPost == true)
    {
	printf("producer polled reading inputs\n");
	RunThroughPreSubmittedButtons(openSharedValues, puzzle, gametype, exitCode, mode);
	int x = openSharedValues->puzzleSharedValues->sharedCursorLocation.x;
	int y = openSharedValues->puzzleSharedValues->sharedCursorLocation.y;
	puzzle->cursoredButton = &puzzle->childButtons[x][y];
	puzzle->cursoredButton->highlighted = true;
	openSharedValues->mainSharedValues->consumerPost = false;
	openSharedValues->mainSharedValues->preSubmitCheck = false;
	openSharedValues->mainSharedValues->flagProducer = 0;
    }

}

void PollConsumer(OpenSharedValues* openSharedValues, ButtonMaster* puzzle, enum Gamemode* mode, enum Gametype gametype, ExitCode* exitCode)
{
    if (openSharedValues->mainSharedValues->flag == 0) return;
    
    if (IsPuzzleConsumer(puzzle, openSharedValues) == false)
    {
	return;
    }


    printf("\n");
    printf("in consumer polling\n");
    Button* cursoredButton = FindCursoredButton(puzzle);

    if (cursoredButton == NULL)
    {
	printf("cursored button is null\n");
    }
/*
    if (openSharedValues->mainSharedValues->preSubmitCheck == true)
    {
	//find any submitted buttons and then return
	//wipe the list
	//fill the list if any
	WipePreSubmittedList(openSharedValues);
	//openSharedValues->puzzleSharedValues->preSubmitIndex = 0;
	//openSharedValues->submitIndexBuffer = 0;
	FillListFromBuffer(openSharedValues, puzzle);
	openSharedValues->puzzleSharedValues->sharedCursorLocation = puzzle->cursoredButton->buttonVectorLocation;
	openSharedValues->puzzleSharedValues->preSubmitIndex = openSharedValues->submitIndexBuffer;
	openSharedValues->mainSharedValues->consumerPost = true;
	openSharedValues->mainSharedValues->preSubmitCheck = false;
	openSharedValues->mainSharedValues->flag = 0;
	printf("\n");
	printf("\n");
	printf("consumer inputs posted\n");
	printf("\n");
	printf("\n");
	return;
    }
*/    
    enum Direction inputDirection = 0;
    
    if (openSharedValues->puzzleSharedValues->inputDirection > 0 && openSharedValues->puzzleSharedValues->inputDirection < 5)
    {
	inputDirection = ED_Direction;
	printf("inputDirection set to Direction\n");
	printf("\n");
    }
    else
    {
	inputDirection = openSharedValues->puzzleSharedValues->inputDirection;
    }

    switch(inputDirection)
    {
    case ED_Direction:
	RemoveHighlight(cursoredButton);
	cursoredButton = HandleConsumerInput(puzzle, cursoredButton, openSharedValues);
	AddHighlight(cursoredButton);
	printf("direction read in consumer\n");
	break;
    case ED_Enter:
	printf("consumer about to change selection\n");
	ChangeSelection(cursoredButton, puzzle, NULL, EGT_NULL, NULL);
	CheckForSolution(cursoredButton, puzzle, mode);
	cursoredButton = PushCursor(cursoredButton, puzzle, openSharedValues);
	printf("consumer button pushed\n");
	break;
    case ED_Reset:
	printf("\n");
	printf("reseting puzzle in consumer\n");
	printf("\n");
	ResetPuzzle(puzzle, false);
	break;
    default:
	printf("ERROR DEFAULT RUN IN POLL CONSUMER SWITCH STATEMENT\n");
    }
    puzzle->cursoredButton = cursoredButton;
    if (openSharedValues->mainSharedValues == NULL) return;
    openSharedValues->mainSharedValues->flag = 0;
    printf("consumer read and complete, flag is returned\n");
}

Button* PushCursor(Button* button, ButtonMaster* master, OpenSharedValues* openSharedValues)
{
    printf("about to push cursor right now\n");
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
	
	if (openSharedValues->mainSharedValues != NULL && openSharedValues->mainSharedValues->sharingPuzzles == true)
	{
	    openSharedValues->puzzleSharedValues->inputDirection = ED_Reset;
	    HandleProducerInput(master, button, button, openSharedValues, IsPuzzleConsumer(master, openSharedValues));
	}
        ResetPuzzle(master, false);
	printf("puzzle reset\n");
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

void ChangeSelection(Button* button, ButtonMaster* puzzle, OpenSharedValues* openSharedValues, enum Gametype gametype, ExitCode* exitCode)
{
    if (!button->submitted)
    {
	bool solutionButton = SubmitButton(button, puzzle, openSharedValues, gametype, exitCode);
	if (solutionButton == false)
	{
	    AddPlainButtonToSubmittedList(button, &puzzle->plainSubmittedButtons, puzzle);
	}
    }
    else
    {
	UnsubmitButton(button, puzzle, false);
    }
}

bool SubmitButton(Button* button, ButtonMaster* puzzle, OpenSharedValues* openSharedValues, enum Gametype gametype, ExitCode* exitCode)
{
    printf("button submitted\n");
    button->model->texture = button->buttonTextures->selected;
    button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture;
    button->submitted = true;
    if (gametype == EGT_NULL)
    {
	printf("gametype is NULL\n");
    }
    if (button == NULL)
    {
	printf("the button is null\n");
    }
    if (button->ButtonSelected == NULL)
    {
	printf("only the button selected is null\n");
    }
    if (button->ButtonSelected != NULL)
    {
	//Somehow, I need to pass in the OpenSharedValues, exitcode and gametype here
	switch(button->puzzleType)
	{
	case EPT_Free:
	    button->ButtonSelected(button);
	    break;
	case EPT_OnOff:
	    button->ButtonSelected(button);
	    break;
	case EPT_WindowPower:
	    if (button->sharedWindowOpened == false && gametype != EGT_NULL)
	    {
		printf("second game should be opening\n");
		openSharedValues->windowData->SetupWindowMovement(gametype, openSharedValues->windowData);
		OpenSecondGame(openSharedValues, exitCode, gametype);
		button->sharedWindowOpened = true;
	    }
	    break;
	default:
	    button->ButtonSelected(button);
	    printf("button was defaulted\n");
	    break;
	}
    }
    else
    {
	printf("button selected is null or the gametype is\n");
    }
    if (button->solutionButton == true)
    {
	AddItemToSolvedButtonList(&puzzle->solvedButtons, button->textureSizes);
	puzzle->numOfSolved = puzzle->numOfSolved + 1;
	puzzle->numOfSelected = puzzle->numOfSelected + 1;
	printf("this was one of the buttons\n");
	return true;
    }
    return false;
}

void UnsubmitButton(Button* button, ButtonMaster* puzzle, bool isFromAuto)
{
    button->submitted = false;
    if (button->ButtonSelected != NULL)
    {
	button->ButtonSelected(button);
    }
    if (button->solutionButton == true)
    {
	RemoveItemToSolvedButtonList(&puzzle->solvedButtons, button->textureSizes);
	puzzle->numOfSolved = puzzle->numOfSolved - 1;
    }
    if (isFromAuto == true)
    {
	button->model->texture = button->buttonTextures->idle;
	button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture;
	return;
    }
    AddHighlight(button);
}

bool CheckForSolution(Button* button, ButtonMaster* puzzle, enum Gamemode* mode)
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
	    puzzle->puzzleInputType = EPIT_ResetOnly;
	    return true; //this is new lets see what this will do
      	}
	else
	{
	    
	    printf("These are the right buttons input in the incorrect order\n");
	    
	    ResetPuzzle(puzzle, true);
	    return false;
	}
    }
    else
    {
	if (puzzle->numOfSelected >= (puzzle->columns * puzzle->rows) && answerFound == false)
	{
	    printf("You have selected all of the present buttons, try again\n");
	    ResetPuzzle(puzzle, true);
	    return false;
	}
    }
    return false;
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
	puzzle->puzzleInputType = EPIT_Disabled;
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
	    puzzle->puzzleInputType = EPIT_Enabled;
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
    puzzle->OnPuzzleSolved(puzzle);
    for (int i = 0; i < puzzle->numberOfSolutions; i++)
    {
	puzzle->solutionButtons[i]->model->texture = puzzle->solutionButtons[i]->buttonTextures->completed;
	puzzle->solutionButtons[i]->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = puzzle->solutionButtons[i]->model->texture;
    }
}

void AddPlainButtonToSubmittedList(Button* buttonToAdd, PlainSubmittedButtons** head, ButtonMaster* puzzle)
{
    if (puzzle->numOfPlainSubmittedButtons >= puzzle->plainSubmittedButtonsMax)
    {
	RemoveHead(head, puzzle);
    }
    PlainSubmittedButtons* newNode = (PlainSubmittedButtons*)malloc(sizeof(SolvedButtons));

    if (newNode == NULL)
    {
	printf("ERROR, Failed to allocated memory for plain submitted button list\n");
	return;
    }

    newNode->button = buttonToAdd;
    newNode->next = NULL;

    if (*head == NULL)
    {
	*head = newNode;
	return;
    }

    PlainSubmittedButtons* lastNode = *head;
    while (lastNode->next != NULL)
    {
	lastNode = lastNode->next;
    }
    lastNode-> next = newNode;
    puzzle->numOfPlainSubmittedButtons = puzzle->numOfPlainSubmittedButtons + 1;
}

void RemoveHead(PlainSubmittedButtons** head, ButtonMaster* puzzle)
{
    puzzle->numOfPlainSubmittedButtons = puzzle->numOfPlainSubmittedButtons - 1;
    
    PlainSubmittedButtons* out = (*head)->next;

    UnsubmitButton((*head)->button, puzzle, true);

    PlainSubmittedButtons* temp = *head;

    *head = out;

    free(temp);
}

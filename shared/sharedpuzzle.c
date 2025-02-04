#include "sharedpuzzle.h"
#include <stdio.h>

void InitSharedPuzzleGameA(HANDLE* puzzleHMapFile, OpenSharedValues* openSharedValues, ExitCode* exitCode, char* mapFileName)
{
    openSharedValues->puzzleSharedValues = (PuzzleSharedValues*) SetupSharedMemory(puzzleHMapFile, sizeof(PuzzleSharedValues), mapFileName);

    if (openSharedValues->puzzleSharedValues == NULL)
    {
	EditReturnCodeInfo(900, "Failed to setup shared memory for puzzle", exitCode);
    }
    
}

void InitSharedPuzzleGameB(HANDLE* puzzleHMapFile, OpenSharedValues* openSharedValues, ExitCode* exitCode, char* mapFileName)
{
    openSharedValues->puzzleSharedValues = (PuzzleSharedValues*) AttachChildProcessToMemory(puzzleHMapFile, sizeof(PuzzleSharedValues), mapFileName);
    
    if (openSharedValues->puzzleSharedValues == NULL)
    {
	EditReturnCodeInfo(901, "Failed to attach child process for puzzle", exitCode);
	return;
    }
    
}

bool IsPlayerReadyToSharePuzzles(SharedMemory* mainSharedValues)
{
    printf("gameASharedPuzzleId: %i, gameBSharedPuzzleId: %i\n", mainSharedValues->gameACurrPuzzleId, mainSharedValues->gameBCurrPuzzleId);
    if (mainSharedValues->gameAInSharedPuzzle == true && mainSharedValues->gameBInSharedPuzzle == true && mainSharedValues->gameACurrPuzzleId == mainSharedValues->gameBCurrPuzzleId)
    {
	
	printf("you ahve interacted with a shared puzzle preapre to be sharing\n");
	mainSharedValues->sharingPuzzles = true;
	return true;
    }
    return false;
}

//the function to move the cursor on the other screen if needed
void HandleProducerInput(ButtonMaster* puzzle, Button* oldButton, Button* newButton, OpenSharedValues* openSharedValues, bool isConsumer)
{
    if (isConsumer == false)
    {
	printf("is consumer is false\n");
	if (openSharedValues->puzzleSharedValues->inputDirection == ED_Reset)
	{
	    openSharedValues->mainSharedValues->flag = 1;
	    return;
	}
	
	openSharedValues->puzzleSharedValues->sharedCursorLocation = newButton->buttonVectorLocation;
	openSharedValues->puzzleSharedValues->oldSharedCursorLocation = oldButton->buttonVectorLocation;
	printf("button location in A, x: %i, y: %i\n", newButton->buttonVectorLocation.x, newButton->buttonVectorLocation.y);
	puzzle->cursoredButton = newButton;
	openSharedValues->mainSharedValues->flag = 1;
    }
}

Button* HandleConsumerInput(ButtonMaster* puzzle, Button* button, OpenSharedValues* openSharedValues)
{
    int x = openSharedValues->puzzleSharedValues->sharedCursorLocation.x;
    int y = openSharedValues->puzzleSharedValues->sharedCursorLocation.y;

    printf("shared x: %i. y: %i\n", x, y);
    
    button = &puzzle->childButtons[x][y];
    return &puzzle->childButtons[x][y];
}

bool IsPuzzleConsumer(ButtonMaster* puzzle, OpenSharedValues* openSharedValues)
{
    if (openSharedValues->mainSharedValues == NULL) return false;
    if (puzzle->gameAPuzzle == true)
    {
	if (openSharedValues->mainSharedValues->ActiveWindowA == true)
	{
	    return false;
	}
	else
	{
	    return true;
	}
    }
    else
    {
	if (openSharedValues->mainSharedValues->ActiveWindowA == true)
	{
	    return true;
	}
	else
	{
	    return false;
	}
    }
}

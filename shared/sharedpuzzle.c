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
    if (mainSharedValues->gameAInSharedPuzzle == true && mainSharedValues->gameBInSharedPuzzle)
    {
	printf("you ahve interacted with a shared puzzle preapre to be sharing\n");
	mainSharedValues->sharingPuzzles = true;
	return true;
	/*
	if (mainSharedValues->gameACurrPuzzleId == mainSharedValues->gameBCurrPuzzleId)
	{
	    printf("you have interacted with a shared puzzle prepare to be sharing\n");
	    mainSharedValues->sharingPuzzles = true;
	    return true;
	}
	*/
    }
    return false;
}

//the function to move the cursor on the other screen if needed
void HandleProducerInput(ButtonMaster* puzzle, Button* oldButton, Button* newButton, OpenSharedValues* openSharedValues, bool isConsumer)
{
    
    if (isConsumer == false)
    {
	openSharedValues->puzzleSharedValues->sharedCursorLocation = newButton->buttonVectorLocation;
	openSharedValues->puzzleSharedValues->oldSharedCursorLocation = oldButton->buttonVectorLocation;
	printf("button location in A, x: %i, y: %i\n", newButton->buttonVectorLocation.x, newButton->buttonVectorLocation.y);
	openSharedValues->mainSharedValues->flag = 1;
    }
    else
    {
	int x = openSharedValues->puzzleSharedValues->sharedCursorLocation.x;
	int y = openSharedValues->puzzleSharedValues->sharedCursorLocation.y;
	printf("new location x: %i, y: %i\n", x, y);
	newButton = &puzzle->childButtons[x][y];

	int oldX = openSharedValues->puzzleSharedValues->oldSharedCursorLocation.x;
	int oldY = openSharedValues->puzzleSharedValues->oldSharedCursorLocation.y;
	oldButton = &puzzle->childButtons[oldX][oldY];
	printf("old location x: %i, y: %i\n", oldX, oldY);
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

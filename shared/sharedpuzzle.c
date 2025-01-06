#include "sharedpuzzle.h"
#include <stdio.h>

void InitSharedPuzzleGameA(HANDLE* puzzleHMapFile, OpenSharedValues* openSharedValues)
{
    openSharedValues->puzzleSharedValues = (PuzzleSharedValues*) SetupSharedMemory(puzzleHMapFile, sizeof(PuzzleSharedValues));

    
}

void InitSharedPuzzleGameB(HANDLE* puzzleHMapFile, OpenSharedValues* openSharedValues)
{
    openSharedValues->puzzleSharedValues = (PuzzleSharedValues*) AttachChildProcessToMemory(puzzleHMapFile, sizeof(PuzzleSharedValues));

    
}

bool IsPlayerReadyToSharePuzzles(SharedMemory* mainSharedValues)
{
    if (mainSharedValues->gameAInSharedPuzzle == true && mainSharedValues->gameBInSharedPuzzle)
    {
	if (mainSharedValues->gameACurrPuzzleId == mainSharedValues->gameBCurrPuzzleId)
	{
	    printf("you have interacted with a shared puzzle prepare to be sharing\n");
	    return true;
	}
    }
    return false;
}

//the function to move the cursor on the other screen if needed
void HandleConsumerCursorMovement(ButtonMaster* puzzle, Button* inButton, OpenSharedValues* openSharedValues, bool isConsumer)
{
    if (isConsumer == false)
    {
	openSharedValues->puzzleSharedValues->sharedCursorLocation = inButton->buttonVectorLocation;
    }
    else
    {
	puzzle->cursoredButton = puzzle->childButtons[openSharedValues->puzzleSharedValues->sharedCursorLocation.x][openSharedValues->sharedCursoredLocation.y];
    }
}

#include "gamebinteractables.h"
#include <stdlib.h>
#include <stdio.h>

void CreateGameBInteractables(Interactable** interactables, QueryBox** areaQueryBoxes, ButtonMaster** allPuzzles)
{
    int lastInteractableIndex = 0;

    ConstructSingleInteractable(&lastInteractableIndex,
				ITT_Puzzle,
				false,
				2.0f,
				2.0f,
				2.0f,
				allPuzzles[0],
				PuzzleInteract,
				interactables,
				areaQueryBoxes,
				0);
    
}

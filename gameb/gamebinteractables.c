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

    ConstructSingleInteractable(&lastInteractableIndex,
				ITT_Puzzle,
				false,
				2.0f,
				2.0f,
				2.0f,
				allPuzzles[1],
				PuzzleInteract,
				interactables,
				areaQueryBoxes,
				0);

    ConstructSingleInteractable(&lastInteractableIndex,
			      ITT_Puzzle,
			      false,
			      2.0f,
			      2.0f,
			      2.0f,
			      allPuzzles[2],
			      PuzzleInteract,
			      interactables,
			      areaQueryBoxes,
			      0);

    ConstructSingleInteractable(&lastInteractableIndex,
				ITT_Puzzle,
				false,
				2.0f,
				2.0f,
				2.0f,
				allPuzzles[3],
				PuzzleInteract,
				interactables,
				areaQueryBoxes,
				0);

    ConstructSingleInteractable(&lastInteractableIndex,
				ITT_Puzzle,
				false,
				2.0f,
				2.0f,
				2.0f,
				allPuzzles[4],
				PuzzleInteract,
				interactables,
				areaQueryBoxes,
				0);

    ConstructSingleInteractable(&lastInteractableIndex,
				ITT_Puzzle,
				false,
				2.0f,
				2.0f,
				2.0f,
				allPuzzles[5],
				PuzzleInteract,
				interactables,
				areaQueryBoxes,
				0);

    ConstructSingleInteractable(&lastInteractableIndex,
				ITT_Puzzle,
				false,
				2.0f,
				2.0f,
				2.0f,
				allPuzzles[6],
				PuzzleInteract,
				interactables,
				areaQueryBoxes,
				0);
}

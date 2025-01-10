#include "gamebinteractables.h"
#include <stdlib.h>
#include <stdio.h>

void CreateGameBInteractables(Interactable** interactables, QueryBox** areaQueryBoxes, ButtonMaster** allPuzzles, ExitCode* exitCode)
{
    int lastInteractableIndex = 0;

    exitCode->numOfLoadedItems = 0;

    Vector3 nullOffset = (Vector3){0.0f, 0.0f, 0.0f};
    
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
				0,
				nullOffset,
				exitCode);

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
				0,
				nullOffset,
				exitCode);

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
				0,
				nullOffset,
				exitCode);

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
				0,
				nullOffset,
				exitCode);

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
				0,
				nullOffset,
				exitCode);

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
				0,
				nullOffset,
				exitCode);

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
				0,
				nullOffset,
				exitCode);

    ConstructSingleInteractable(&lastInteractableIndex,
				ITT_Puzzle,
				false,
				2.0f,
				2.0f,
				2.0f,
				allPuzzles[7],
				PuzzleInteract,
				interactables,
				areaQueryBoxes,
				0,
				(Vector3){0.5f, 0.0f, 0.0f},
				exitCode);
}

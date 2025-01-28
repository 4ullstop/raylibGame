#include "gameainteractables.h"
#include <stdlib.h>
#include <stdio.h>

void CreateGameAInteractables(Interactable** interactables, QueryBox** areaQueryBoxes, ButtonMaster** allPuzzles, ExitCode* exitCode)
{
    int lastInteractableIndex = 0;

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
				true,
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
				nullOffset,
				exitCode);
    
    ConstructSingleInteractable(&lastInteractableIndex,
				ITT_Puzzle,
				false,
				2.0f,
				2.0f,
				2.0f,
				allPuzzles[8],
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
				allPuzzles[9],
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
				allPuzzles[10],
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
				allPuzzles[11],
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
				allPuzzles[12],
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
				allPuzzles[13],
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
				allPuzzles[14],
				PuzzleInteract,
				interactables,
				areaQueryBoxes,
				0,
				(Vector3){-1.0f, 0.0f, 0.0f},
				exitCode);

    ConstructSingleInteractable(&lastInteractableIndex,
				ITT_Puzzle,
				false,
				2.0f,
				2.0f,
				2.0f,
				allPuzzles[15],
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
				allPuzzles[16],
				PuzzleInteract,
				interactables,
				areaQueryBoxes,
				0,
				nullOffset,
				exitCode);
}

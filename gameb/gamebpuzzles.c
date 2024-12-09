#include "gamebpuzzles.h"
#include <stdlib.h>
#include <stdio.h> 

void ConstructGameBPuzzles(ButtonMaster** gameBPuzzles, Texture2D** allTextures, modelInfo** dynamicModels, int* lastModelIndex, FPSPlayer* player, GameplayElements* gameplayElements)
{
    int lastPuzzleIndex = 0;

    ConstructSinglePuzzle(&lastPuzzleIndex,
			  3,
			  3,
			  (Vector3){0.0f, 0.0f, 0.0f},
			  player,
			  Puzzle_01B,
			  false,
			  gameplayElements,
			  gameBPuzzles,
			  (Vector2Int){0, 0},
			  true,
			  EPS_active,
			  0.0f);





    
    for (int i = 0; i < NUMBER_OF_PUZZLES_B; i++)
    {
        CreateAllButtons(gameBPuzzles[i], dynamicModels, lastModelIndex, allTextures);
    }

    printf("buttons created in game b\n");
    //rotate buttons here
    //assign all values here
    AssignAllPuzzlesSolutionButtons(gameBPuzzles, NUMBER_OF_PUZZLES_B);
    AssignSpecialTexturesGameB(gameBPuzzles, allTextures);
}

void AssignSpecialTexturesGameB(ButtonMaster** allPuzzles, Texture2D** allTextures)
{
    AssignSolutionsTextures(allPuzzles[0]);
}

void Puzzle_01B(ButtonMaster* puzzle)
{
    int numOfSolutions = 3;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 0};
    puzzle->solutionLocations[1] = (Vector2Int){1, 0};
    puzzle->solutionLocations[2] = (Vector2Int){2, 0};
    
    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_02;
    puzzle->textureSizes[1] = EBTS_04;
    puzzle->textureSizes[2] = EBTS_07;

}


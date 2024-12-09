#include "gamebpuzzles.h"
#include <stdlib.h>

void ConstructGameBPuzzles(ButtonMaster** gameBPuzzles, Texture2D** allTextures, modelInfo** dynamicModels, int* lastModelIndex, FPSPlayer* player, GameplayElements* gameplayElements)
{
    int lastPuzzleIndex = 0;

    ConstructSinglePuzzle(&lastPuzzleIndex,
			  3,
			  3,
			  (Vector3){0.0f, 0.0f, 0.0f},
			  player,
			  Puzzle_01,
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


    //rotate buttons here
    //assign all values here
    AssignSpecialTexturesGameB(gameBPuzzles, allTextures);
}

void AssignSpecialTexturesGameB(ButtonMaster** allPuzzles, Texture2D** allTextures)
{
    AssignSolutionTextures(allPuzzles[0]);
}

void Puzzle_01(ButtonMaster* puzzle)
{
    int numOfSolutions = 3;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzl->numberOfSolutions);

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_01;
    puzzle->textureSizes[1] = EBTS_04;
    puzzle->textureSizes[2] = EBTS_07;

}


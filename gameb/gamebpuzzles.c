#include "gamebpuzzles.h"
#include <stdlib.h>
#include <stdio.h> 

void ConstructGameBPuzzles(ButtonMaster** gameBPuzzles, Texture2D** allTextures, modelInfo** dynamicModels, int* lastModelIndex, FPSPlayer* player, GameplayElements* gameplayElements)
{
    int lastPuzzleIndex = 0;

    ConstructSinglePuzzle(&lastPuzzleIndex,
			  3,
			  3,
			  (Vector3){3.0f, 1.0f, 2.0f},
			  player,
			  Puzzle_01B,
			  false,
			  gameplayElements,
			  gameBPuzzles,
			  (Vector2Int){2, 0},
			  true,
			  EPS_active,
			  0.0f);
    
    ConstructSinglePuzzle(&lastPuzzleIndex,
			  4,
			  1,
			  (Vector3){1.0f, 1.5f, 1.0f},
			  player,
			  Puzzle_02B,
			  false,
			  gameplayElements,
			  gameBPuzzles,
			  (Vector2Int){0, 0},
			  true,
			  EPS_active,
			  0.0f);

    ConstructSinglePuzzle(&lastPuzzleIndex,
			3,
			3,
			(Vector3){6.0f, 1.0f, 3.0f},
			player,
		        Puzzle_03B,
			false,
			gameplayElements,
			gameBPuzzles,
			(Vector2Int){0, 1},
			true,
			EPS_active,
			0.0f);

    for (int i = 0; i < NUMBER_OF_PUZZLES_B; i++)
    {
        CreateAllButtons(gameBPuzzles[i], dynamicModels, lastModelIndex, allTextures);
    }

    AssignAllPuzzlesNormals(gameBPuzzles, NUMBER_OF_PUZZLES_B);
    printf("buttons created in game b\n");
    //rotate buttons here
    //assign all values here
    AssignAllPuzzlesSolutionButtons(gameBPuzzles, NUMBER_OF_PUZZLES_B);
    printf("solutions assigned\n");
    AssignSpecialTexturesGameB(gameBPuzzles, allTextures);
}

void AssignSpecialTexturesGameB(ButtonMaster** allPuzzles, Texture2D** allTextures)
{
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[0][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[0][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[1][1], TCL_OFF);

    AssignButtonSpecialTextureAndAction(&allPuzzles[2]->childButtons[1][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[2]->childButtons[1][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[2]->childButtons[1][2], TCL_OFF);

    
    AssignSolutionsTextures(allPuzzles[0]);
    AssignSolutionsTextures(allPuzzles[1]);
    AssignSolutionsTextures(allPuzzles[2]);
}

void Puzzle_01B(ButtonMaster* puzzle)
{
    int numOfSolutions = 3;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){1, 0};
    puzzle->solutionLocations[1] = (Vector2Int){2, 2};
    puzzle->solutionLocations[2] = (Vector2Int){0, 1};
    
    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_02;
    puzzle->textureSizes[1] = EBTS_04;
    puzzle->textureSizes[2] = EBTS_07;

}

void Puzzle_02B(ButtonMaster* puzzle)
{
    printf("building puzzle 02");
    int numOfSolutions = 4;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 0};
    puzzle->solutionLocations[1] = (Vector2Int){1, 0};
    puzzle->solutionLocations[2] = (Vector2Int){2, 0};
    puzzle->solutionLocations[3] = (Vector2Int){3, 0};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_01;
    puzzle->textureSizes[1] = EBTS_03;
    puzzle->textureSizes[2] = EBTS_05;
    puzzle->textureSizes[3] = EBTS_07;
}

void Puzzle_03B(ButtonMaster* puzzle)
{
    int numOfSolutions = 3;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){2, 0};
    puzzle->solutionLocations[1] = (Vector2Int){1, 0};
    puzzle->solutionLocations[2] = (Vector2Int){2, 2};
    
    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_01;
    puzzle->textureSizes[1] = EBTS_05;
    puzzle->textureSizes[2] = EBTS_07;
}



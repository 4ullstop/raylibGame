#include "gamebpuzzles.h"
#include <stdlib.h>
#include <stdio.h> 

void ConstructGameBPuzzles(ButtonMaster** gameBPuzzles, Texture2D** allTextures, modelInfo** dynamicModels, int* lastModelIndex, FPSPlayer* player, GameplayElements* gameplayElements, SharedMemory* sharedMemory, SharedPuzzleList** sharedPuzzleList, ExitCode* exitCode)
{
    int lastPuzzleIndex = 0;

    Vector3 nullLerpLoc = (Vector3){0.0f, 0.0f, 0.0f};
    
    exitCode->numOfLoadedItems = 0;
    //Stay
    ConstructSinglePuzzle(&lastPuzzleIndex,
			  3,
			  3,
			  (Vector3){0.0f, 1.0f, -6.0f},
			  player,
			  Puzzle_01B,
			  GET_NULL,
			  gameplayElements,
			  0,
			  0,
			  gameBPuzzles,
			  (Vector2Int){2, 0},
			  true,
			  EPS_active,
			  0.0f,
			  false,
			  false,
			  nullLerpLoc,
			  exitCode);
    
    
    //staying
    ConstructSinglePuzzle(&lastPuzzleIndex,
			  6,
			  3,
			  (Vector3){-5.0f, 1.0f, 3.0f},
			  player,
			  Puzzle_02B,
			  GET_NULL,
			  gameplayElements,
			  0,
			  0,
			  gameBPuzzles,
			  (Vector2Int){0, 1},
			  true,
			  EPS_active,
			  0.3f,
			  false,
			  false,
			  nullLerpLoc,
			  exitCode);

    //Shared memory testing
    ConstructSinglePuzzle(&lastPuzzleIndex,
			  3,
			  6,
			  (Vector3){-5.0f, 1.2f, -3.0f},
			  player,
			  Puzzle_03B,
			  GET_NULL,
			  gameplayElements,
			  0,
			  0,
			  gameBPuzzles,
			  (Vector2Int){0, 0},
			  true,
			  EPS_active,
			  0.0f,
			  true,
			  false,
			  (Vector3){1.1f, 0.2f, -0.6f},
			  exitCode);

    ConstructSinglePuzzle(&lastPuzzleIndex,
			  3,
			  8,
			  (Vector3){0.0f, 1.5f, 0.0f},
			  player,
			  Puzzle_04B,
			  GET_NULL,
			  gameplayElements,
			  0,
			  0,
			  gameBPuzzles,
			  (Vector2Int){0, 0},
			  true,
			  EPS_active,
			  0.3f,
			  true,
			  false,
			  (Vector3){0.8f, 0.0f, -1.0f},
			  exitCode);

    ConstructSinglePuzzle(&lastPuzzleIndex,
			  3,
			  6,
			  (Vector3){1.0f, 1.2f, -3.0f},
			  player,
			  Puzzle_05B,
			  GET_NULL,
			  gameplayElements,
			  0,
			  0,
			  gameBPuzzles,
			  (Vector2Int){4, 0},
			  true,
			  EPS_active,
			  0.3f,
			  true,
			  false,
			  nullLerpLoc,
			  exitCode);
			  
    
    exitCode->numOfLoadedItems = 0;
    
    for (int i = 0; i < NUMBER_OF_PUZZLES_B; i++)
    {
        CreateAllButtons(gameBPuzzles[i], dynamicModels, lastModelIndex, allTextures, exitCode);
    }

    AssignAllPuzzlesNormals(gameBPuzzles, NUMBER_OF_PUZZLES_B);
    printf("buttons created in game b\n");
    //rotate buttons here
    //assign all values here
    AssignAllPuzzlesSolutionButtons(gameBPuzzles, NUMBER_OF_PUZZLES_B, exitCode);
    printf("solutions assigned\n");
    AssignSpecialTexturesGameB(gameBPuzzles, allTextures);

    AddGameBPuzzlesToSharedMemory(gameBPuzzles, sharedMemory);
    FillSharedPuzzleList(gameBPuzzles, NUMBER_OF_PUZZLES_B, sharedPuzzleList);
}

void AddGameBPuzzlesToSharedMemory(ButtonMaster** allPuzzles, SharedMemory* sharedMemory)
{
    AddPuzzleToSharedPuzzles(allPuzzles[2], sharedMemory, 0, false);

    allPuzzles[2]->sharedPuzzleId = 1;
    allPuzzles[3]->sharedPuzzleId = 2;
    allPuzzles[4]->sharedPuzzleId = 3;
}

void AssignSpecialTexturesGameB(ButtonMaster** allPuzzles, Texture2D** allTextures)
{
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[0][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[0][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[1][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[2][1], TCL_OFF);
    
    AssignButtonSpecialTextureAndAction(&allPuzzles[1]->childButtons[0][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[1]->childButtons[0][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[1]->childButtons[0][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[1]->childButtons[0][5], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[1]->childButtons[2][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[1]->childButtons[1][4], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[1]->childButtons[2][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[1]->childButtons[1][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[1]->childButtons[1][0], TCL_OFF);

    AssignButtonSpecialTextureAndAction(&allPuzzles[3]->childButtons[0][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[3]->childButtons[1][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[3]->childButtons[1][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[3]->childButtons[2][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[3]->childButtons[3][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[3]->childButtons[3][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[3]->childButtons[3][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[3]->childButtons[4][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[3]->childButtons[5][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[3]->childButtons[6][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[3]->childButtons[7][0], TCL_OFF);

    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[0][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[2][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[3][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[5][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[1][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[4][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[5][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[2][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[3][2], TCL_OFF);
    
            
    AssignSolutionsTextures(allPuzzles[0]);
    AssignSolutionsTextures(allPuzzles[1]);
    AssignSolutionsTextures(allPuzzles[2]);
    AssignSolutionsTextures(allPuzzles[3]);
    AssignSolutionsTextures(allPuzzles[4]);
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

/*
  {3,0} {3,1} {3,2} {3,3}
  {2,0} {2,1} {2,2} {2,3}
  {1,0} {1,1} {1,2} {1,3}
  {0,0} {0,1} {0,2} {0,3}
*/

/*
  {5,0} {5,1} {5,2}
  {4,0} {4,1} {4,2}
  {3,0} {3,1} {3,2}
  {2,0} {2,1} {2,2}
  {1,0} {1,1} {1,2}
  {0,0} {0,1} {0,2}
*/

void Puzzle_02B(ButtonMaster* puzzle)
{
    int numOfSolutions = 4;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){1, 0};
    puzzle->solutionLocations[1] = (Vector2Int){4, 0};
    puzzle->solutionLocations[2] = (Vector2Int){3, 1};
    puzzle->solutionLocations[3] = (Vector2Int){0, 2};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_01;
    puzzle->textureSizes[1] = EBTS_03;
    puzzle->textureSizes[2] = EBTS_05;
    puzzle->textureSizes[3] = EBTS_07;
}

/*
  {2,0} {2,1} {2,2} {2,3} {2,4} {2,5} {2,6} {2,7}
  {1,0} {1,1} {1,2} {1,3} {1,4} {1,5} {1,6} {1,7}
  {0,0} {0,1} {0,2} {0,3} {0,4} {0,5} {0,6} {0,7}
*/


/*
  {4,0} {4,1} {4,2}
  {3,0} {3,1} {3,2}
  {2,0} {2,1} {2,2}
  {1,0} {1,1} {1,2}
  {0,0} {0,1} {0,2}
*/

void Puzzle_03B(ButtonMaster* puzzle)
{
    int numOfSolutions = 2;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){1, 1};
    puzzle->solutionLocations[1] = (Vector2Int){1, 2};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_03;
    puzzle->textureSizes[1] = EBTS_06;
}

void Puzzle_04B(ButtonMaster* puzzle)
{
    int numOfSolutions = 3;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){2, 5};
    puzzle->solutionLocations[1] = (Vector2Int){0, 4};
    puzzle->solutionLocations[2] = (Vector2Int){2, 1};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_01;
    puzzle->textureSizes[1] = EBTS_03;
    puzzle->textureSizes[2] = EBTS_06;
}

void Puzzle_05B(ButtonMaster* puzzle)
{
    int numOfSolutions = 4;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 4};
    puzzle->solutionLocations[1] = (Vector2Int){0, 1};
    puzzle->solutionLocations[2] = (Vector2Int){1, 2};
    puzzle->solutionLocations[3] = (Vector2Int){2, 5};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_01;
    puzzle->textureSizes[1] = EBTS_03;
    puzzle->textureSizes[2] = EBTS_05;
    puzzle->textureSizes[3] = EBTS_07;
}

#include "gameapuzzles.h"
#include <stdlib.h>
#include <stdio.h>
#include "../shared/memory_editing.h"

void ConstructGameAPuzzles(ButtonMaster** gameAPuzzles, Texture2D** allTextures, modelInfo** dynamicModels, int* lastModelIndex, FPSPlayer* player, GameplayElements* gameplayElements, SharedMemory* sharedMemory, ExitCode* exitCode)
{
    int lastPuzzleIndex = 0;

    Vector2Int nullStartLoc = (Vector2Int){0, 0};
    float lighthouseZHeight = 5.0f;
    Vector3 nullLerpLoc = (Vector3){0.0f, 0.0f, 0.0f};
    
    //Second Starter puzzle
    ConstructSinglePuzzle(&lastPuzzleIndex, 
			  5, 
			  3, 
			  (Vector3){-8.0f, 1.0f, -35.0f},
			  player,
			  Puzzle_01,
			  GET_SwitchBox,
			  gameplayElements,
			  0,
			  0,
			  gameAPuzzles,
			  (Vector2Int){1, 1},
			  true,
			  EPS_active,
			  0.3f,
			  false,
			  true,
			  nullLerpLoc,
			  exitCode);

    //The very first puzzle that isn't really a puzzle
    ConstructSinglePuzzle(&lastPuzzleIndex,
			  1,
			  1,
			  (Vector3){15.3f, -0.3f, -36.0f},
			  player,
			  Puzzle_02,
			  GET_Basic,
			  gameplayElements,
			  0,
			  109,
			  gameAPuzzles,
			  nullStartLoc,
			  false,
			  EPS_active,
			  0.0f,
			  false,
			  true,
			  nullLerpLoc,
			  exitCode);

    //Intro puzzle 2
    ConstructSinglePuzzle(&lastPuzzleIndex,
			  5,
			  1,
			  (Vector3){8.0f, -0.2f, -37.9f},
			  player,
			  Puzzle_03,
			  GET_Door,
			  gameplayElements,
			  1,
			  110,
			  gameAPuzzles,
			  (Vector2Int){0, 1},
			  true,
			  EPS_inactive,
			  0.3f,
			  false,
			  true,
			  nullLerpLoc,
			  exitCode);
    //First direction
    ConstructSinglePuzzle(&lastPuzzleIndex,
			  3,
			  3,
			  (Vector3){-5.2f, lighthouseZHeight, -8.28f},
			  player,
			  Puzzle_04,
			  GET_Basic,
			  gameplayElements,
			  0,
			  101,
			  gameAPuzzles,
			  (Vector2Int){0, 0},
			  true,
			  EPS_active,
			  0.0f,
			  false,
			  true,
			  nullLerpLoc,
			  exitCode);

    //First starter puzzle
    ConstructSinglePuzzle(&lastPuzzleIndex,
			  4,
			  3,
			  (Vector3){-4.0f, 1.0f, -35.0f},
			  player,
			  Puzzle_05,
			  GET_SwitchBox,
			  gameplayElements,
			  0,
			  0,
			  gameAPuzzles,
			  (Vector2Int){0, 0},
			  true,
			  EPS_active,
			  0.3f,
			  false,
			  true,
			  nullLerpLoc,
			  exitCode);

    //Second direction
    ConstructSinglePuzzle(&lastPuzzleIndex,
			  3,
			  5,
			  (Vector3){-7.9f, lighthouseZHeight, -1.1f},
			  player,
			  Puzzle_06,
			  GET_Basic,
			  gameplayElements,
			  0,
			  102,
			  gameAPuzzles,
			  (Vector2Int){2, 0},
			  true,
			  EPS_inactive,
			  0.3f,
			  false,
			  true,
			  nullLerpLoc,
			  exitCode);

    //Intro puzzle 1
    ConstructSinglePuzzle(&lastPuzzleIndex,
			  1,
			  5,
			  (Vector3){-2.3f, 1.2f, -6.0f},
			  player,
			  Puzzle_07,
			  GET_NULL,
			  gameplayElements,
			  0,
			  0,
			  gameAPuzzles,
			  (Vector2Int){1, 0},
			  true, 
			  EPS_inactive,
			  0.3f,
			  false,
			  true,
			  nullLerpLoc,
			  exitCode);

    //Direction
    ConstructSinglePuzzle(&lastPuzzleIndex,
			  3,
			  5,
			  (Vector3){-4.5f, lighthouseZHeight, 6.8f},
			  player,
			  Puzzle_08,
			  GET_Basic,
			  gameplayElements,
			  0,
			  103,
			  gameAPuzzles,
			  (Vector2Int){0, 2},
			  true, 
			  EPS_inactive,
			  0.3f,
			  false,
			  true,
			  nullLerpLoc,
			  exitCode);

    //test puzzle
    ConstructSinglePuzzle(&lastPuzzleIndex,
			  3,
			  3,
			  (Vector3){5.0f, 1.0f, -3.0f},
			  player,
			  Puzzle_09,
			  GET_NULL,
			  gameplayElements,
			  0,
			  0,
			  gameAPuzzles,
			  (Vector2Int){0, 0},
			  false, 
			  EPS_active,
			  0.3f,
			  false,
			  true,
			  nullLerpLoc,
			  exitCode);

    //Down left
    ConstructSinglePuzzle(&lastPuzzleIndex,
			  4,
			  5,
			  (Vector3){3.0f, lighthouseZHeight, 10.0f},
			  player,
			  Puzzle_10,
			  GET_Basic,
			  gameplayElements,
			  0,
			  0,
			  gameAPuzzles,
			  (Vector2Int){4, 2},
			  true, 
			  EPS_inactive,
			  0.3f,
			  false,
			  true,
			  nullLerpLoc,
			  exitCode);
    //Direction down
    ConstructSinglePuzzle(&lastPuzzleIndex,
			  3,
			  4,
			  (Vector3){11.5f, 5.8f, 6.1f},
			  player,
			  Puzzle_11,
			  GET_Basic,
			  gameplayElements,
			  0,
			  105,
			  gameAPuzzles,
			  (Vector2Int){0, 2},
			  true,
			  EPS_inactive,
			  0.3f,
			  false,
			  true,
			  nullLerpLoc,
			  exitCode);

    //Direction down left
    ConstructSinglePuzzle(&lastPuzzleIndex,
			  5,
			  4,
			  (Vector3){14.0f, lighthouseZHeight, -1.6f},
			  player,
			  Puzzle_12,
			  GET_Basic,
			  gameplayElements,
			  0,
			  104,
			  gameAPuzzles,
			  (Vector2Int){0, 1},
			  true,
			  EPS_inactive,
			  0.3f,
			  false,
			  true,
			  nullLerpLoc,
			  exitCode);

    ConstructSinglePuzzle(&lastPuzzleIndex,
			  3,
			  5,
			  (Vector3){10.1f, lighthouseZHeight, -9.3f},
			  player,
			  Puzzle_13,
			  GET_Basic,
			  gameplayElements,
			  0,
			  106,
			  gameAPuzzles,
			  (Vector2Int){0, 1},
			  true,
			  EPS_inactive,
			  0.3f,
			  false,
			  true,
			  nullLerpLoc,
			  exitCode);

    ConstructSinglePuzzle(&lastPuzzleIndex,
			  5,
			  6,
			  (Vector3){1.8f, lighthouseZHeight, -11.9f},
			  player,
			  Puzzle_14,
			  GET_Basic,
			  gameplayElements,
			  0,
			  107,
			  gameAPuzzles,
			  (Vector2Int){1, 2},
			  true,
			  EPS_inactive,
			  0.3f,
			  false,
			  true,
			  nullLerpLoc,
			  exitCode);

    ConstructSinglePuzzle(&lastPuzzleIndex,
			  3,
			  6,
			  (Vector3){0.0f, 1.2f, 0.0f},
			  player,
			  Puzzle_15,
			  GET_Basic,
			  gameplayElements,
			  0,
			  108,
			  gameAPuzzles,
			  (Vector2Int){0, 0},
			  true,
			  EPS_inactive,
			  0.0f,
			  true,
			  true,
			  (Vector3){-1.7f, 0.2f, -0.6f},
			  exitCode);

    ConstructSinglePuzzle(&lastPuzzleIndex,
			  3,
			  3,
			  (Vector3){-12.0f, 1.0f, -35.0f},
			  player,
			  Puzzle_16,
			  GET_SwitchBox,
			  gameplayElements,
			  0,
			  0,
			  gameAPuzzles,
			  (Vector2Int){0, 0},
			  true,
			  EPS_active,
			  0.0f,
			  false,
			  true,
			  nullLerpLoc,
			  exitCode);

    ConstructSinglePuzzle(&lastPuzzleIndex,
			  1,
			  1,
			  (Vector3){1.0f, 1.0f, 1.0f},
			  player,
			  Puzzle_17,
			  GET_NULL,
			  gameplayElements,
			  0,
			  0,
			  gameAPuzzles,
			  (Vector2Int){0, 0},
			  true,
			  EPS_active,
			  0.0f,
			  false,
			  true,
			  nullLerpLoc,
			  exitCode);
    
    for (int i = 0; i < NUMBER_OF_PUZZLES_A; i++)
    {
        CreateAllButtons(gameAPuzzles[i], dynamicModels, lastModelIndex, allTextures, exitCode);
    }


    RotateButtonMaster(gameAPuzzles[1], 115.0f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[2], 45.0f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[3], 45.0f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[5], 90.0f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[6], 90.f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[7], 135.0f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[9], 180.0f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[10], 225.f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[11], 270.f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[12], 315.f, (Vector3){0.0f, 1.0f, 0.0f});
    AssignAllPuzzlesNormals(gameAPuzzles, NUMBER_OF_PUZZLES_A);
    /*
        After the initialziation of our buttons, we want to perscribe special textures to them if they so require
    */
    AssignAllPuzzlesSolutionButtons(gameAPuzzles, NUMBER_OF_PUZZLES_A, exitCode);
    AssignSpecialTexturesGameA(gameAPuzzles, allTextures);

    AddGameAPuzzlesToSharedMemory(gameAPuzzles, sharedMemory);
    
    gameAPuzzles[1]->puzzleToPowerOn = gameAPuzzles[2];
    gameAPuzzles[2]->puzzleToPowerOn = gameAPuzzles[6];

    gameAPuzzles[3]->puzzleToPowerOn = gameAPuzzles[5];
    gameAPuzzles[5]->puzzleToPowerOn = gameAPuzzles[7];
    gameAPuzzles[7]->puzzleToPowerOn = gameAPuzzles[9];
    gameAPuzzles[9]->puzzleToPowerOn = gameAPuzzles[10];
    gameAPuzzles[10]->puzzleToPowerOn = gameAPuzzles[11];
    gameAPuzzles[11]->puzzleToPowerOn = gameAPuzzles[12];
    gameAPuzzles[12]->puzzleToPowerOn = gameAPuzzles[13]; 
}

void AddGameAPuzzlesToSharedMemory(ButtonMaster** allPuzzles, SharedMemory* sharedMemory)
{
    AddPuzzleToSharedPuzzles(allPuzzles[14], sharedMemory, 0, true);
}

/*
    {2,0} {2,1} {2,2}
    {1,0} {1,1} {1,2}
    {0,0} {0,1} {0,2}
*/

void AssignSpecialTexturesGameA(ButtonMaster** allPuzzles, Texture2D** allTextures)
{
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[0][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[1][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[2][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[2][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[2][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[2][4], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[1][4], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[0][2], TCL_OFF);


    AssignButtonSpecialTextureAndAction(&allPuzzles[2]->childButtons[0][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[2]->childButtons[0][4], TCL_OFF);

    AssignButtonSpecialTextureAndAction(&allPuzzles[3]->childButtons[1][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[3]->childButtons[1][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[3]->childButtons[1][2], TCL_OFF);
    
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[1][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[0][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[1][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[2][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[2][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[2][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[2][3], TCL_OFF);

    AssignButtonSpecialTextureAndAction(&allPuzzles[5]->childButtons[3][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[5]->childButtons[1][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[5]->childButtons[0][1], TCL_OFF);
    
    AssignButtonSpecialTextureAndAction(&allPuzzles[6]->childButtons[0][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[6]->childButtons[4][0], TCL_OFF);

    AssignButtonSpecialTextureAndAction(&allPuzzles[7]->childButtons[2][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[7]->childButtons[0][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[7]->childButtons[1][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[7]->childButtons[2][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[7]->childButtons[3][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[7]->childButtons[4][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[7]->childButtons[2][2], TCL_OFF);

    AssignButtonSpecialTextureAndAction(&allPuzzles[8]->childButtons[1][1], TCL_Move);
    
    AssignButtonSpecialTextureAndAction(&allPuzzles[9]->childButtons[0][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[9]->childButtons[0][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[9]->childButtons[0][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[9]->childButtons[1][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[9]->childButtons[2][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[9]->childButtons[3][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[9]->childButtons[3][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[9]->childButtons[4][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[9]->childButtons[4][1], TCL_OFF);

    AssignButtonSpecialTextureAndAction(&allPuzzles[10]->childButtons[1][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[10]->childButtons[1][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[10]->childButtons[0][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[10]->childButtons[3][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[10]->childButtons[1][0], TCL_OFF);
        
    AssignButtonSpecialTextureAndAction(&allPuzzles[11]->childButtons[0][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[11]->childButtons[0][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[11]->childButtons[1][4], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[11]->childButtons[2][4], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[11]->childButtons[2][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[11]->childButtons[2][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[11]->childButtons[3][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[11]->childButtons[3][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[11]->childButtons[2][0], TCL_OFF);

    
    AssignButtonSpecialTextureAndAction(&allPuzzles[12]->childButtons[0][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[12]->childButtons[1][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[12]->childButtons[0][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[12]->childButtons[1][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[12]->childButtons[2][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[12]->childButtons[2][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[12]->childButtons[3][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[12]->childButtons[4][1], TCL_OFF);
    
   
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[0][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[0][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[2][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[2][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[3][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[3][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[4][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[4][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[5][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[5][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[1][4], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[2][4], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[3][4], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[4][4], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[5][4], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[0][4], TCL_OFF);
    
    AssignButtonSpecialTextureAndAction(&allPuzzles[15]->childButtons[1][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[15]->childButtons[1][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[15]->childButtons[1][2], TCL_OFF);

    AssignButtonSpecialTextureAndAction(&allPuzzles[16]->childButtons[0][0], TCL_Window);
    
    AssignSolutionsTextures(allPuzzles[0]);
    AssignSolutionsTextures(allPuzzles[2]);
    AssignSolutionsTextures(allPuzzles[3]);
    AssignSolutionsTextures(allPuzzles[4]);
    AssignSolutionsTextures(allPuzzles[5]);
    AssignSolutionsTextures(allPuzzles[6]);
    AssignSolutionsTextures(allPuzzles[7]);
    AssignSolutionsTextures(allPuzzles[8]);
    AssignSolutionsTextures(allPuzzles[9]);
    AssignSolutionsTextures(allPuzzles[10]);
    AssignSolutionsTextures(allPuzzles[11]);
    AssignSolutionsTextures(allPuzzles[12]);
    AssignSolutionsTextures(allPuzzles[13]);
    AssignSolutionsTextures(allPuzzles[14]);
    AssignSolutionsTextures(allPuzzles[15]);
    AssignSolutionsTextures(allPuzzles[15]);
}

void AssignPuzzlesToSharedMemory(ButtonMaster** allPuzzles, ButtonMaster* sharedPuzzle)
{
    sharedPuzzle = allPuzzles[14];
}












/*
    {3,0} {3,1} {3,2} {3,3} {3,4} {3,5}
    {2,0} {2,1} {2,2} {2,3} {2,4} {2,5}
    {1,0} {1,1} {1,2} {1,3} {1,4} {1,5}
    {0,0} {0,1} {0,2} {0,3} {0,4} {0,5}
*/

/*
    {2,0} {2,1} {2,2}
    {1,0} {1,1} {1,2}
    {0,0} {0,1} {0,2}
*/

void Puzzle_01(ButtonMaster* puzzle)
{
    int numOfSolutions = 4;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions); //another thing you need to destroy at some point
    //the order in which these are determines which buttons need to be pressed first
    puzzle->solutionLocations[0] = (Vector2Int){2, 2};
    puzzle->solutionLocations[1] = (Vector2Int){1, 0};
    puzzle->solutionLocations[2] = (Vector2Int){4, 0};
    puzzle->solutionLocations[3] = (Vector2Int){2, 1};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_01;
    puzzle->textureSizes[1] = EBTS_04;
    puzzle->textureSizes[2] = EBTS_06;
    puzzle->textureSizes[3] = EBTS_08;
}

void Puzzle_02(ButtonMaster* puzzle)
{
    int numOfSolutions = 1;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 0};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes)* puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_06;

}

void Puzzle_03(ButtonMaster* puzzle)
{
    int numOfSolutions = 2;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){1, 0};
    puzzle->solutionLocations[1] = (Vector2Int){3, 0};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_01;
    puzzle->textureSizes[1] = EBTS_05;
}

void Puzzle_04(ButtonMaster* puzzle)
{
    puzzle->numberOfSolutions = 2;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * puzzle->numberOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 2};
    puzzle->solutionLocations[1] = (Vector2Int){0, 0};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_02;
    puzzle->textureSizes[1] = EBTS_06;
}

void Puzzle_05(ButtonMaster* puzzle)
{
    puzzle->numberOfSolutions = 3;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * puzzle->numberOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){2, 0};
    puzzle->solutionLocations[2] = (Vector2Int){1, 1};
    puzzle->solutionLocations[1] = (Vector2Int){0, 1};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_01;
    puzzle->textureSizes[1] = EBTS_03;
    puzzle->textureSizes[2] = EBTS_05;
}

/*
    {2,0} {2,1} {2,2}
    {1,0} {1,1} {1,2}
    {0,0} {0,1} {0,2}
*/

/*
    {3,0} {3,1} {3,2} {3,3}
    {2,0} {2,1} {2,2} {2,3}
    {1,0} {1,1} {1,2} {1,3}
    {0,0} {0,1} {0,2} {0,3}
*/

void Puzzle_06(ButtonMaster* puzzle)
{
    int numOfSolutions = 4;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){1, 3};
    puzzle->solutionLocations[1] = (Vector2Int){1, 2};
    puzzle->solutionLocations[2] = (Vector2Int){0, 2};
    puzzle->solutionLocations[3] = (Vector2Int){2, 0};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_01;
    puzzle->textureSizes[1] = EBTS_05;
    puzzle->textureSizes[2] = EBTS_06;
    puzzle->textureSizes[3] = EBTS_08;
}

void Puzzle_07(ButtonMaster* puzzle)
{
    int numOfSolutions = 2;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 1};
    puzzle->solutionLocations[1] = (Vector2Int){0, 3};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_02;
    puzzle->textureSizes[1] = EBTS_05;
}

/*
    {3,0} {3,1} {3,2} {3,3}
    {2,0} {2,1} {2,2} {2,3}
    {1,0} {1,1} {1,2} {1,3}
    {0,0} {0,1} {0,2} {0,3}
*/

void Puzzle_08(ButtonMaster* puzzle)
{
    int numOfSolutions = 3;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){2, 1};
    puzzle->solutionLocations[1] = (Vector2Int){0, 1};
    puzzle->solutionLocations[2] = (Vector2Int){1, 4};
    
    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_02;
    puzzle->textureSizes[1] = EBTS_04;
    puzzle->textureSizes[2] = EBTS_07;
}

void Puzzle_09(ButtonMaster* puzzle)
{
    int numOfSolutions = 3;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 0};
    puzzle->solutionLocations[1] = (Vector2Int){1, 0};
    puzzle->solutionLocations[2] = (Vector2Int){2, 0};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_05;
    puzzle->textureSizes[1] = EBTS_02;
    puzzle->textureSizes[2] = EBTS_04;
}

/*
    {2,0} {2,1} {2,2}
    {1,0} {1,1} {1,2}
    {0,0} {0,1} {0,2}
*/

void Puzzle_10(ButtonMaster* puzzle)
{
    int numOfSolutions = 3;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){2, 4};
    puzzle->solutionLocations[1] = (Vector2Int){3, 3};
    puzzle->solutionLocations[2] = (Vector2Int){0, 0};
    
    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_01;
    puzzle->textureSizes[1] = EBTS_03;
    puzzle->textureSizes[2] = EBTS_05;
}

void Puzzle_11(ButtonMaster* puzzle)
{
    int numOfSolutions = 3;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){2, 2};
    puzzle->solutionLocations[1] = (Vector2Int){1, 2};
    puzzle->solutionLocations[2] = (Vector2Int){2, 0};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_02;
    puzzle->textureSizes[1] = EBTS_05;
    puzzle->textureSizes[2] = EBTS_07;
}

void Puzzle_12(ButtonMaster* puzzle)
{
    int numOfSolutions = 3;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){1, 1};
    puzzle->solutionLocations[1] = (Vector2Int){4, 3};
    puzzle->solutionLocations[2] = (Vector2Int){3, 1};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_01;
    puzzle->textureSizes[1] = EBTS_04;
    puzzle->textureSizes[2] = EBTS_08;
}

void Puzzle_13(ButtonMaster* puzzle)
{
    int numOfSolutions = 3;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){1, 0};
    puzzle->solutionLocations[1] = (Vector2Int){0, 2};
    puzzle->solutionLocations[2] = (Vector2Int){2, 3};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_02;
    puzzle->textureSizes[1] = EBTS_04;
    puzzle->textureSizes[2] = EBTS_08;
}

void Puzzle_14(ButtonMaster* puzzle)
{
    int numOfSolutions = 2;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){2, 3};
    puzzle->solutionLocations[1] = (Vector2Int){2, 5};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_03;
    puzzle->textureSizes[1] = EBTS_05;
}

void Puzzle_15(ButtonMaster* puzzle)
{
    int numOfSolutions = 2;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){1, 1};
    puzzle->solutionLocations[1] = (Vector2Int){1, 2};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_02;
    puzzle->textureSizes[1] = EBTS_05;
}

void Puzzle_16(ButtonMaster* puzzle)
{
    int numOfSolutions = 2;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 0};
    puzzle->solutionLocations[1] = (Vector2Int){0, 2};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_01;
    puzzle->textureSizes[1] = EBTS_05;
}

void Puzzle_17(ButtonMaster* puzzle)
{
    int numOfSolutions = 1;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 0};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_01;
}
	       

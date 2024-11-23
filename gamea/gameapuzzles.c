#include "gameapuzzles.h"
#include <stdlib.h>
#include <stdio.h>

void ConstructGameAPuzzles(ButtonMaster** gameAPuzzles, Texture2D** allTextures, modelInfo** dynamicModels, int* lastModelIndex, FPSPlayer* player, GameplayElements* gameplayElements)
{
    int lastPuzzleIndex = 0;

    Vector2Int nullStartLoc = (Vector2Int){0, 0};

    ConstructSinglePuzzle(&lastPuzzleIndex, 
        3, 
        3, 
        (Vector3){0.0f, 1.0f, 0.0f},
        player,
        Puzzle_01,
        false,
        gameplayElements,
        gameAPuzzles,
        nullStartLoc,
        false,
        EPS_active,
        0.0f);
    
    ConstructSinglePuzzle(&lastPuzzleIndex,
        1,
        1,
        (Vector3){2.3f, 1.0f, -15.0f},
        player,
        Puzzle_02,
        true,
        gameplayElements,
        gameAPuzzles,
        nullStartLoc,
        false,
        EPS_active,
        0.0f);

    ConstructSinglePuzzle(&lastPuzzleIndex,
        4,
        1,
        (Vector3){2.3f, 1.2f, -6.0f},
        player,
        Puzzle_03,
        false,
        gameplayElements,
        gameAPuzzles,
        (Vector2Int){0, 1},
        true,
        EPS_active,
        0.3f);

    ConstructSinglePuzzle(&lastPuzzleIndex,
        3,
        1,
        (Vector3){1.0f, 1.0f, 1.0f},
        player,
        Puzzle_04,
        false,
        gameplayElements,
        gameAPuzzles,
        (Vector2Int){0, 0},
        true,
        EPS_active,
        0.0f);

    ConstructSinglePuzzle(&lastPuzzleIndex,
        3,
        2,
        (Vector3){4.0f, 1.0f, 3.0f},
        player,
        Puzzle_05,
        false,
        gameplayElements,
        gameAPuzzles,
        (Vector2Int){0, 0},
        true,
        EPS_inactive,
        0.0f);

    ConstructSinglePuzzle(&lastPuzzleIndex,
        3,
        3,
        (Vector3){0.0f, 1.0f, 3.0f},
        player,
        Puzzle_06,
        false,
        gameplayElements,
        gameAPuzzles,
        (Vector2Int){0, 0},
        true,
        EPS_active,
        0.0f);

    ConstructSinglePuzzle(&lastPuzzleIndex,
        1,
        5,
        (Vector3){-2.3f, 1.2f, -6.0f},
        player,
        Puzzle_07,
        false,
        gameplayElements,
        gameAPuzzles,
        (Vector2Int){0, 0},
        false, 
        EPS_inactive,
        0.3f);

    ConstructSinglePuzzle(&lastPuzzleIndex,
        5,
        1,
        (Vector3){4.0f, 1.0f, 1.0f},
        player,
        Puzzle_08,
        false,
        gameplayElements,
        gameAPuzzles,
        (Vector2Int){0, 1},
        true, 
        EPS_active,
        0.3f);

    for (int i = 0; i < NUMBER_OF_PUZZLES_A; i++)
    {
        CreateAllButtons(gameAPuzzles[i], dynamicModels, lastModelIndex, allTextures);
    }

    RotateButtonMaster(gameAPuzzles[0], 45.f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[1], 80.0f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[2], 80.0f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[3], DEG2RAD * 180.0f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[6], DEG2RAD * 90.f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[7], DEG2RAD * 180.f, (Vector3){0.0f, 1.0f, 0.0f});

    /*
        After the initialziation of our buttons, we want to perscribe special textures to them if they so require
    */
    AssignAllPuzzlesSolutionButtons(gameAPuzzles);
    AssignSpecialTexturesGameA(gameAPuzzles, allTextures);
    
    gameAPuzzles[3]->puzzleToPowerOn = gameAPuzzles[4];
    gameAPuzzles[2]->puzzleToPowerOn = gameAPuzzles[6];
}

/*
    {2,0} {2,1} {2,2}
    {1,0} {1,1} {1,2}
    {0,0} {0,1} {0,2}
*/

void AssignSpecialTexturesGameA(ButtonMaster** allPuzzles, Texture2D** allTextures)
{
    AssignButtonSpecialTextureAndAction(&allPuzzles[3]->childButtons[0][2], TCL_UD);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[1][2], TCL_UD);

    AssignButtonSpecialTextureAndAction(&allPuzzles[2]->childButtons[0][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[2]->childButtons[0][3], TCL_OFF);

    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[0][0], TCL_LR);
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[0][2], TCL_UD);

    AssignButtonSpecialTextureAndAction(&allPuzzles[6]->childButtons[0][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[6]->childButtons[4][0], TCL_OFF);

    // AssignButtonSpecialTextureAndAction(&allPuzzles[5]->childButtons[0][2], TCL_DDR);
    // AssignButtonSpecialTextureAndAction(&allPuzzles[5]->childButtons[0][2], TCL_UD); //this one is wrong, you need to add this direction
    // AssignButtonSpecialTextureAndAction(&allPuzzles[5]->childButtons[2][2], TCL_LR);


    AssignSolutionsTextures(allPuzzles[2]);
    AssignSolutionsTextures(allPuzzles[5]);
    AssignSolutionsTextures(allPuzzles[6]);
    AssignSolutionsTextures(allPuzzles[7]);
}

/*
    {2,0} {2,1} {2,2}
    {1,0} {1,1} {1,2}
    {0,0} {0,1} {0,2}
*/

void Puzzle_01(ButtonMaster* puzzle)
{
    int numOfSolutions = 5;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions); //another thing you need to destroy at some point
    //the order in which these are determines which buttons need to be pressed first
    puzzle->solutionLocations[0] = (Vector2Int){2, 0};
    puzzle->solutionLocations[1] = (Vector2Int){1, 0};
    puzzle->solutionLocations[2] = (Vector2Int){0, 0};
    puzzle->solutionLocations[3] = (Vector2Int){0, 1};
    puzzle->solutionLocations[4] = (Vector2Int){0, 2};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_04;
    puzzle->textureSizes[1] = EBTS_06;
    puzzle->textureSizes[2] = EBTS_08;
    puzzle->textureSizes[3] = EBTS_03;
    puzzle->textureSizes[4] = EBTS_02;
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
    puzzle->solutionLocations[1] = (Vector2Int){2, 0};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_05;
    puzzle->textureSizes[1] = EBTS_02;
}

void Puzzle_04(ButtonMaster* puzzle)
{
    puzzle->numberOfSolutions = 3;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * puzzle->numberOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 0};
    puzzle->solutionLocations[1] = (Vector2Int){1, 0};
    puzzle->solutionLocations[2] = (Vector2Int){2, 0};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_05;
    puzzle->textureSizes[1] = EBTS_07;
    puzzle->textureSizes[2] = EBTS_03;

}

void Puzzle_05(ButtonMaster* puzzle)
{
    puzzle->numberOfSolutions = 3;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * puzzle->numberOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 1};
    puzzle->solutionLocations[1] = (Vector2Int){1, 1};
    puzzle->solutionLocations[2] = (Vector2Int){2, 1};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_03;
    puzzle->textureSizes[1] = EBTS_07;
    puzzle->textureSizes[2] = EBTS_02;
}

/*
    {2,0} {2,1} {2,2}
    {1,0} {1,1} {1,2}
    {0,0} {0,1} {0,2}
*/

void Puzzle_06(ButtonMaster* puzzle)
{
    int numOfSolutions = 5;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 2};
    puzzle->solutionLocations[1] = (Vector2Int){2, 1};
    puzzle->solutionLocations[2] = (Vector2Int){1, 0};
    puzzle->solutionLocations[3] = (Vector2Int){1, 2};
    puzzle->solutionLocations[4] = (Vector2Int){2, 0};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_01;
    puzzle->textureSizes[1] = EBTS_03;
    puzzle->textureSizes[2] = EBTS_04;
    puzzle->textureSizes[3] = EBTS_06;
    puzzle->textureSizes[4] = EBTS_08;
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
    puzzle->textureSizes[0] = EBTS_05;
    puzzle->textureSizes[1] = EBTS_02;
}

void Puzzle_08(ButtonMaster* puzzle)
{
    int numOfSolutions = 3;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){1, 0};
    puzzle->solutionLocations[1] = (Vector2Int){2, 0};
    puzzle->solutionLocations[2] = (Vector2Int){0, 0};
    
    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_02;
    puzzle->textureSizes[1] = EBTS_04;
    puzzle->textureSizes[2] = EBTS_06;
}
#include "gameapuzzles.h"
#include <stdlib.h>
#include <stdio.h>

void ConstructGameAPuzzles(ButtonMaster** gameAPuzzles, Texture2D** allTextures, modelInfo** dynamicModels, int* lastModelIndex, FPSPlayer* player, GameplayElements* gameplayElements)
{
    int lastPuzzleIndex = 0;

    Vector2Int nullStartLoc = (Vector2Int){0, 0};

    //Second Starter puzzle
    ConstructSinglePuzzle(&lastPuzzleIndex, 
        3, 
        3, 
        (Vector3){-0.5f, 1.0f, 1.0f},
        player,
        Puzzle_01,
        false,
        gameplayElements,
        gameAPuzzles,
        (Vector2Int){0, 0},
        true,
        EPS_active,
        0.0f);

    //The very first puzzle that isn't really a puzzle
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

    //Intro puzzle 2
    ConstructSinglePuzzle(&lastPuzzleIndex,
        5,
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
        2,
        2,
        (Vector3){-3.0f, 1.0f, 5.0f},
        player,
        Puzzle_04,
        false,
        gameplayElements,
        gameAPuzzles,
        (Vector2Int){0, 0},
        true,
        EPS_active,
        0.0f);

    //First starter puzzle
    ConstructSinglePuzzle(&lastPuzzleIndex,
        4,
        3,
        (Vector3){2.0f, 1.0f, 0.0f},
        player,
        Puzzle_05,
        false,
        gameplayElements,
        gameAPuzzles,
        (Vector2Int){0, 0},
        true,
        EPS_active,
        0.3f);


    ConstructSinglePuzzle(&lastPuzzleIndex,
        3,
        3,
        (Vector3){-0.5f, 1.0f, 4.0f},
        player,
        Puzzle_06,
        false,
        gameplayElements,
        gameAPuzzles,
        (Vector2Int){2, 0},
        true,
        EPS_active,
        0.3f);

    //Intro puzzle 1
    ConstructSinglePuzzle(&lastPuzzleIndex,
        1,
        5,
        (Vector3){-2.3f, 1.2f, -6.0f},
        player,
        Puzzle_07,
        false,
        gameplayElements,
        gameAPuzzles,
        (Vector2Int){1, 0},
        true, 
        EPS_inactive,
        0.3f);

    ConstructSinglePuzzle(&lastPuzzleIndex,
        3,
        3,
        (Vector3){2.0f, 1.0f, 3.0f},
        player,
        Puzzle_08,
        false,
        gameplayElements,
        gameAPuzzles,
        (Vector2Int){1, 0},
        true, 
        EPS_active,
        0.3f);

    //test puzzle
    ConstructSinglePuzzle(&lastPuzzleIndex,
        3,
        3,
        (Vector3){5.0f, 1.0f, -3.0f},
        player,
        Puzzle_09,
        false,
        gameplayElements,
        gameAPuzzles,
        (Vector2Int){0, 0},
        false, 
        EPS_active,
        0.3f);

    ConstructSinglePuzzle(&lastPuzzleIndex,
        4,
        5,
        (Vector3){-3.0f, 1.0f, 2.0f},
        player,
        Puzzle_10,
        false,
        gameplayElements,
        gameAPuzzles,
        (Vector2Int){1, 0},
        true, 
        EPS_active,
        0.3f);

    ConstructSinglePuzzle(&lastPuzzleIndex,
			  3,
			  3,
			  (Vector3){-15.0f, 1.0f, -10.0f},
			  player,
			  Puzzle_11,
			  false,
			  gameplayElements,
			  gameAPuzzles,
			  (Vector2Int){0, 0},
			  true,
			  EPS_active,
			  0.0f);

    ConstructSinglePuzzle(&lastPuzzleIndex,
			  5,
			  4,
			  (Vector3){-12.0f, 1.0f, -10.0f},
			  player,
			  Puzzle_12,
			  false,
			  gameplayElements,
			  gameAPuzzles,
			  (Vector2Int){0, 0},
			  true,
			  EPS_active,
			  0.3f);

    ConstructSinglePuzzle(&lastPuzzleIndex,
			  4,
			  3,
			  (Vector3){-18.0f, 1.0f, -10.0f},
			  player,
			  Puzzle_13,
			  false,
			  gameplayElements,
			  gameAPuzzles,
			  (Vector2Int){0, 0},
			  true,
			  EPS_active,
			  0.3f);

    ConstructSinglePuzzle(&lastPuzzleIndex,
			  5,
			  4,
			  (Vector3){-21.0f, 1.0f, -10.0f},
			  player,
			  Puzzle_14,
			  false,
			  gameplayElements,
			  gameAPuzzles,
			  (Vector2Int){0, 0},
			  true,
			  EPS_active,
			  0.3f);
    
    for (int i = 0; i < NUMBER_OF_PUZZLES_A; i++)
    {
        CreateAllButtons(gameAPuzzles[i], dynamicModels, lastModelIndex, allTextures);
    }

    //I need to construct 4 more puzzles, you need to get rid of 50 models
    

    RotateButtonMaster(gameAPuzzles[0], 180.f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[1], -90.0f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[2], -90.0f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[4], 180.0f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[6], 90.f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[9], 180.0f, (Vector3){0.0f, 1.0f, 0.0f});

    AssignAllPuzzlesNormals(gameAPuzzles, NUMBER_OF_PUZZLES_A);
    /*
        After the initialziation of our buttons, we want to perscribe special textures to them if they so require
    */
    AssignAllPuzzlesSolutionButtons(gameAPuzzles, NUMBER_OF_PUZZLES_A);
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
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[1][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[0]->childButtons[1][1], TCL_OFF);

    AssignButtonSpecialTextureAndAction(&allPuzzles[2]->childButtons[0][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[2]->childButtons[0][4], TCL_OFF);

    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[1][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[0][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[1][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[2][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[2][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[2][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[4]->childButtons[2][3], TCL_OFF);

    AssignButtonSpecialTextureAndAction(&allPuzzles[5]->childButtons[1][2], TCL_OFF);
    
    AssignButtonSpecialTextureAndAction(&allPuzzles[6]->childButtons[0][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[6]->childButtons[4][0], TCL_OFF);

    AssignButtonSpecialTextureAndAction(&allPuzzles[7]->childButtons[0][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[7]->childButtons[1][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[7]->childButtons[2][0], TCL_OFF);
    
    AssignButtonSpecialTextureAndAction(&allPuzzles[9]->childButtons[0][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[9]->childButtons[0][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[9]->childButtons[1][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[9]->childButtons[2][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[9]->childButtons[3][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[9]->childButtons[2][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[9]->childButtons[3][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[9]->childButtons[1][1], TCL_OFF);

    AssignButtonSpecialTextureAndAction(&allPuzzles[10]->childButtons[1][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[10]->childButtons[1][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[10]->childButtons[2][0], TCL_OFF);

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
    AssignButtonSpecialTextureAndAction(&allPuzzles[12]->childButtons[0][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[12]->childButtons[1][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[12]->childButtons[1][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[12]->childButtons[2][0], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[12]->childButtons[2][3], TCL_OFF);
    
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[0][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[0][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[0][4], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[1][4], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[2][3], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[3][2], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[3][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[2][1], TCL_OFF);
    AssignButtonSpecialTextureAndAction(&allPuzzles[13]->childButtons[1][0], TCL_OFF);
    
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
}

/*
    {3,0} {3,1} {3,2} {3,3}
    {2,0} {2,1} {2,2} {2,3}
    {1,0} {1,1} {1,2} {1,3}
    {0,0} {0,1} {0,2} {0,3}
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
    puzzle->solutionLocations[0] = (Vector2Int){0, 2};
    puzzle->solutionLocations[1] = (Vector2Int){1, 2};
    puzzle->solutionLocations[2] = (Vector2Int){2, 0};
    puzzle->solutionLocations[3] = (Vector2Int){0, 0};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_02;
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
    puzzle->textureSizes[0] = EBTS_02;
    puzzle->textureSizes[1] = EBTS_05;
}

void Puzzle_04(ButtonMaster* puzzle)
{
    puzzle->numberOfSolutions = 2;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * puzzle->numberOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 1};
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
    puzzle->textureSizes[0] = EBTS_02;
    puzzle->textureSizes[1] = EBTS_04;
    puzzle->textureSizes[2] = EBTS_07;
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
    int numOfSolutions = 3;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){1, 1};
    puzzle->solutionLocations[1] = (Vector2Int){0, 1};
    puzzle->solutionLocations[2] = (Vector2Int){0, 2};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_01;
    puzzle->textureSizes[1] = EBTS_05;
    puzzle->textureSizes[2] = EBTS_08;
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
    int numOfSolutions = 4;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){2, 2};
    puzzle->solutionLocations[1] = (Vector2Int){2, 1};
    puzzle->solutionLocations[2] = (Vector2Int){1, 2};
    puzzle->solutionLocations[3] = (Vector2Int){1, 1};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_02;
    puzzle->textureSizes[1] = EBTS_04;
    puzzle->textureSizes[2] = EBTS_07;
    puzzle->textureSizes[3] = EBTS_08;
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
    puzzle->solutionLocations[0] = (Vector2Int){2, 1};
    puzzle->solutionLocations[1] = (Vector2Int){2, 3};
    puzzle->solutionLocations[2] = (Vector2Int){0, 1};
    
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
    puzzle->solutionLocations[0] = (Vector2Int){2, 0};
    puzzle->solutionLocations[1] = (Vector2Int){2, 2};
    puzzle->solutionLocations[2] = (Vector2Int){1, 2};

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
    puzzle->solutionLocations[0] = (Vector2Int){3, 0};
    puzzle->solutionLocations[1] = (Vector2Int){3, 1};
    puzzle->solutionLocations[2] = (Vector2Int){1, 0};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_02;
    puzzle->textureSizes[1] = EBTS_04;
    puzzle->textureSizes[2] = EBTS_08;
}

void Puzzle_14(ButtonMaster* puzzle)
{
    int numOfSolutions = 3;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){3, 1};
    puzzle->solutionLocations[1] = (Vector2Int){4, 2};
    puzzle->solutionLocations[2] = (Vector2Int){0, 0};

    puzzle->textureSizes = malloc(sizeof(enum ButtonTextureSizes) * puzzle->numberOfSolutions);
    puzzle->textureSizes[0] = EBTS_03;
    puzzle->textureSizes[1] = EBTS_05;
    puzzle->textureSizes[2] = EBTS_07;
}

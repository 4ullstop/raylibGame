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
        EPS_active);
    
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
        EPS_active);

    ConstructSinglePuzzle(&lastPuzzleIndex,
        2,
        2,
        (Vector3){2.3f, 1.0f, -6.0f},
        player,
        Puzzle_03,
        false,
        gameplayElements,
        gameAPuzzles,
        nullStartLoc,
        false,
        EPS_active);

    ConstructSinglePuzzle(&lastPuzzleIndex,
        3,
        1,
        (Vector3){4.0f, 1.0f, 1.0f},
        player,
        Puzzle_04,
        false,
        gameplayElements,
        gameAPuzzles,
        (Vector2Int){0, 0},
        true,
        EPS_active);

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
        EPS_inactive);

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
        EPS_active);

    printf("here\n");
    for (int i = 0; i < NUMBER_OF_PUZZLES_A; i++)
    {
        CreateAllButtons(gameAPuzzles[i], dynamicModels, lastModelIndex, allTextures);
    }

    RotateButtonMaster(gameAPuzzles[0], 45.f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[1], 80.0f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[2], 80.0f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[3], DEG2RAD * 180.0f, (Vector3){0.0f, 1.0f, 0.0f});
    printf("%f, %f, %f\n", gameAPuzzles[1]->location.x, gameAPuzzles[1]->location.y, gameAPuzzles[1]->location.z);

    /*
        After the initialziation of our buttons, we want to perscribe special textures to them if they so require
    */
    AssignSpecialTexturesGameA(gameAPuzzles, allTextures);
    
    gameAPuzzles[3]->puzzleToPowerOn = gameAPuzzles[4];
}

/*
    {2,0} {2,1} {2,2}
    {1,0} {1,1} {1,2}
    {0,0} {0,1} {0,2}
*/

void AssignSpecialTexturesGameA(ButtonMaster** allPuzzles, Texture2D** allTextures)
{   
    PuzzleTexture* puzzleTextures[3];
    LoadAllSpecialTextures(puzzleTextures, allTextures);
    AssignTextureAndActionAtSpot(allTextures, puzzleTextures, &allPuzzles[3]->childButtons[0][2], POOD_TopDown, EBS_idle);

    AssignTextureAndActionAtSpot(allTextures, puzzleTextures, &allPuzzles[4]->childButtons[1][2], POOD_TopDown, EBS_off);

    AssignTextureAndActionAtSpot(allTextures, puzzleTextures, &allPuzzles[0]->childButtons[0][0], POOD_RightLeft, EBS_idle);
    AssignTextureAndActionAtSpot(allTextures, puzzleTextures, &allPuzzles[0]->childButtons[0][2], POOD_BottomUp, EBS_idle);

    AssignTextureAndActionAtSpot(allTextures, puzzleTextures, &allPuzzles[5]->childButtons[0][2], POOD_DDL, EBS_idle);
    AssignTextureAndActionAtSpot(allTextures, puzzleTextures, &allPuzzles[5]->childButtons[0][0], POOD_BottomUp, EBS_highlighted);
    AssignTextureAndActionAtSpot(allTextures, puzzleTextures, &allPuzzles[5]->childButtons[2][2], POOD_RightLeft, EBS_idle);


    PuzzleTexture* solutionTextures[7];
    LoadAllSolutionTextures(solutionTextures, allTextures);

}

void AssignTextureAndActionAtSpot(Texture2D** allTextures, PuzzleTexture** puzzleTextures, Button* button, enum PuzzleOnOffDirection direction, enum ButtonState state)
{
    PuzzleTexture* textureToUse = NULL;
    switch (direction)
    {
    case POOD_BottomUp:
        textureToUse = puzzleTextures[1];
        break;
    case POOD_TopDown:
        textureToUse = puzzleTextures[1];
        break;
    case POOD_LeftRight:
        textureToUse = puzzleTextures[0];
        break;
    case POOD_RightLeft:
        textureToUse = puzzleTextures[0];
        break;
    case POOD_DDL:
        textureToUse = puzzleTextures[2];
        break;
    default:
        printf("ERROR BUTTON DIRECTION NOT SET IN ASSIGNTEXTUREANDACTIONATSPOT\n");
        break;
    }
    LoadAndAssignSingleTexture(button, textureToUse, state);
    AssignButtonToToggleAction(button, direction);
}

void SwitchOnSolutionSizes(enum ButtonTextureSizes textureSizes, Button* button, PuzzleTexture** solutionTextures, enum ButtonState state)
{
    PuzzleTexture* assignedTexture = NULL;
    switch (textureSizes)
    {
    case EBTS_02:
        assignedTexture = solutionTextures[0];
        break;
    case EBTS_03:
        assignedTexture = solutionTextures[1];
        break;
    case EBTS_04:
        assignedTexture = solutionTextures[2];
        break;
    case EBTS_05:
        assignedTexture = solutionTextures[3];
        break;
    case EBTS_06:
        assignedTexture = solutionTextures[4];
        break;
    case EBTS_07:
        assignedTexture = solutionTextures[5];
        break;
    case EBTS_08:
        assignedTexture = solutionTextures[6];
        break;
    default:
        printf("ERROR SOLUTION BUTTONTEXTURESIZES UNASSIGNED\n");
        break;
    }
    LoadAndAssignSingleTexture(button, assignedTexture, state);
}

void LoadAllSpecialTextures(PuzzleTexture** textures, Texture2D** allTextures)
{
    PuzzleTexture* buttonLRToggle = malloc(sizeof(PuzzleTexture));
    buttonLRToggle->highlighted = *allTextures[10];
    buttonLRToggle->idle = *allTextures[11];
    buttonLRToggle->off = *allTextures[5];
    buttonLRToggle->selected = *allTextures[12];
    textures[0] = buttonLRToggle;
    
    PuzzleTexture* buttonUpToggle = malloc(sizeof(PuzzleTexture));
    buttonUpToggle->highlighted = *allTextures[6];
    buttonUpToggle->idle = *allTextures[7];
    buttonUpToggle->off = *allTextures[5];
    buttonUpToggle->selected = *allTextures[8];
    textures[1] = buttonUpToggle;

    PuzzleTexture* buttonDDLToggle = malloc(sizeof(PuzzleTexture));
    buttonDDLToggle->highlighted = *allTextures[13];
    buttonDDLToggle->idle = *allTextures[14];
    buttonDDLToggle->off = *allTextures[5];
    buttonDDLToggle->selected = *allTextures[15];
    textures[2] = buttonDDLToggle;
}

void LoadAndAssignSingleTexture(Button* button, PuzzleTexture* newTextures, enum ButtonState state)
{
    button->buttonTextures = newTextures;
    switch (state)
    {
    case EBS_highlighted:
        button->model->texture = newTextures->highlighted;
        break;
    case EBS_idle:
        button->model->texture = newTextures->idle;
        break;
    case EBS_selected:
        button->model->texture = newTextures->selected;
        break;
    case EBS_off:
        button->model->texture = newTextures->off;
        break;
    default:
        button->model->texture = newTextures->idle;
        printf("ERROR!: DEFAULT RUN IN LOADANDASSIGNSINGLETEXTURE\n");
    }
    button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture;
}

void AssignSolutionLocationTextures(Texture2D** allTextures, Button* button)
{
    
}

void LoadAllSolutionTextures(PuzzleTexture** solutionTextures, Texture2D** allTextures)
{
    PuzzleTexture* solution_02 = malloc(sizeof(PuzzleTexture));
    solution_02->highlighted = *allTextures[17];
    solution_02->idle = *allTextures[24];
    solution_02->selected = *allTextures[31];
    solution_02->off = *allTextures[5];
    solutionTextures[0] = solution_02;

    PuzzleTexture* solution_03 = malloc(sizeof(PuzzleTexture));
    solution_03->highlighted = *allTextures[18];
    solution_03->idle = *allTextures[25];
    solution_03->selected = *allTextures[32];
    solution_03->off = *allTextures[5];
    solutionTextures[1] = solution_03;

    PuzzleTexture* solution_04 = malloc(sizeof(PuzzleTexture));
    solution_04->highlighted = *allTextures[19];
    solution_04->idle = *allTextures[26];
    solution_04->selected = *allTextures[33];
    solution_04->off = *allTextures[5];
    solutionTextures[2] = solution_04;

    PuzzleTexture* solution_05 = malloc(sizeof(PuzzleTexture));
    solution_05->highlighted = *allTextures[20];
    solution_05->idle = *allTextures[27];
    solution_05->selected = *allTextures[34];
    solution_05->off = *allTextures[5];
    solutionTextures[3] = solution_05;

    PuzzleTexture* solution_06 = malloc(sizeof(PuzzleTexture));
    solution_06->highlighted = *allTextures[21];
    solution_06->idle = *allTextures[28];
    solution_06->selected = *allTextures[35];
    solution_06->off = *allTextures[5];
    solutionTextures[4] = solution_06;
    
    PuzzleTexture* solution_07 = malloc(sizeof(PuzzleTexture));
    solution_07->highlighted = *allTextures[22];
    solution_07->idle = *allTextures[29];
    solution_07->selected = *allTextures[36];
    solution_07->off = *allTextures[5];
    solutionTextures[5] = solution_07;

    PuzzleTexture* solution_08 = malloc(sizeof(PuzzleTexture));
    solution_08->highlighted = *allTextures[23];
    solution_08->idle = *allTextures[30];
    solution_08->selected = *allTextures[37];
    solution_08->off = *allTextures[5];
    solutionTextures[6] = solution_08;
}


/*
    {2,0} {2,1} {2,2}
    {1,0} {1,1} {1,2}
    {0,0} {0,1} {0,2}
*/

void AssignSolutionButtonsToPuzzle(ButtonMaster* puzzle)
{
    for (int i = 0; i < puzzle->numberOfSolutions; i++)
    {
        puzzle->solutionButtons[i] = &puzzle->childButtons[puzzle->solutionLocations[i].x][puzzle->solutionLocations[i].y]; //be sure to remove the dangling pointers when these are destroyed
    }
}

void Puzzle_01(ButtonMaster* puzzle)
{
    int numOfSolutions = 5;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions); //another thing you need to destroy at some point
    puzzle->solutionLocations[0] = (Vector2Int){2, 0};
    puzzle->solutionLocations[1] = (Vector2Int){1, 0};
    puzzle->solutionLocations[2] = (Vector2Int){0, 0};
    puzzle->solutionLocations[3] = (Vector2Int){0, 1};
    puzzle->solutionLocations[4] = (Vector2Int){0, 2};

    AssignSolutionButtonsToPuzzle(puzzle);
}

void Puzzle_02(ButtonMaster* puzzle)
{
    int numOfSolutions = 1;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 0};

    AssignSolutionButtonsToPuzzle(puzzle);
}

void Puzzle_03(ButtonMaster* puzzle)
{
    //your locations are wrong here, figure it out
    int numOfSolutions = 4;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 0};
    puzzle->solutionLocations[1] = (Vector2Int){0, 1};
    puzzle->solutionLocations[2] = (Vector2Int){1, 0};
    puzzle->solutionLocations[3] = (Vector2Int){1, 1};

    AssignSolutionButtonsToPuzzle(puzzle);
}

void Puzzle_04(ButtonMaster* puzzle)
{
    puzzle->numberOfSolutions = 3;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * puzzle->numberOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 0};
    puzzle->solutionLocations[1] = (Vector2Int){1, 0};
    puzzle->solutionLocations[2] = (Vector2Int){2, 0};

    AssignSolutionButtonsToPuzzle(puzzle);
}

void Puzzle_05(ButtonMaster* puzzle)
{
    puzzle->numberOfSolutions = 3;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * puzzle->numberOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 1};
    puzzle->solutionLocations[1] = (Vector2Int){1, 1};
    puzzle->solutionLocations[2] = (Vector2Int){2, 1};

    AssignSolutionButtonsToPuzzle(puzzle);
}

void Puzzle_06(ButtonMaster* puzzle)
{
    int numOfSolutions = 7;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionButtons = malloc(sizeof(Button) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){2, 0};
    puzzle->solutionLocations[1] = (Vector2Int){1, 0};
    puzzle->solutionLocations[2] = (Vector2Int){0, 0};
    puzzle->solutionLocations[3] = (Vector2Int){2, 1};
    puzzle->solutionLocations[4] = (Vector2Int){2, 2};
    puzzle->solutionLocations[5] = (Vector2Int){1, 1};
    puzzle->solutionLocations[6] = (Vector2Int){0, 2};

    AssignSolutionButtonsToPuzzle(puzzle);
}
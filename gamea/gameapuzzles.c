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
    puzzle->solutionLocations[0] = (Vector2Int){2, 0};
    puzzle->solutionLocations[1] = (Vector2Int){1, 0};
    puzzle->solutionLocations[2] = (Vector2Int){0, 0};
    puzzle->solutionLocations[3] = (Vector2Int){0, 1};
    puzzle->solutionLocations[4] = (Vector2Int){0, 2};

    printf("-----------------------------------------\n");
    printf("PUZZLE_01 CREATED\n");
    printf("-----------------------------------------\n");
}

void Puzzle_02(ButtonMaster* puzzle)
{
    int numOfSolutions = 1;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 0};
}

void Puzzle_03(ButtonMaster* puzzle)
{
    //your locations are wrong here, figure it out
    int numOfSolutions = 4;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 0};
    puzzle->solutionLocations[1] = (Vector2Int){0, 1};
    puzzle->solutionLocations[2] = (Vector2Int){1, 0};
    puzzle->solutionLocations[3] = (Vector2Int){1, 1};
}

void Puzzle_04(ButtonMaster* puzzle)
{
    puzzle->numberOfSolutions = 3;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 0};
    puzzle->solutionLocations[1] = (Vector2Int){1, 0};
    puzzle->solutionLocations[2] = (Vector2Int){2, 0};
}

void Puzzle_05(ButtonMaster* puzzle)
{
    puzzle->numberOfSolutions = 3;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * puzzle->numberOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){0, 1};
    puzzle->solutionLocations[1] = (Vector2Int){1, 1};
    puzzle->solutionLocations[2] = (Vector2Int){2, 1};
}

void Puzzle_06(ButtonMaster* puzzle)
{
    int numOfSolutions = 7;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){2, 0};
    puzzle->solutionLocations[1] = (Vector2Int){1, 0};
    puzzle->solutionLocations[2] = (Vector2Int){0, 0};
    puzzle->solutionLocations[3] = (Vector2Int){2, 1};
    puzzle->solutionLocations[4] = (Vector2Int){2, 2};
    puzzle->solutionLocations[5] = (Vector2Int){1, 1};
    puzzle->solutionLocations[6] = (Vector2Int){0, 2};
}
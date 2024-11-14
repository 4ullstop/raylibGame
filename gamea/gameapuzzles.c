#include "gameapuzzles.h"
#include <stdlib.h>
#include <stdio.h>

void ConstructGameAPuzzles(ButtonMaster** gameAPuzzles, modelInfo** dynamicModels, int* lastModelIndex, FPSPlayer* player, GameplayElements* gameplayElements)
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
        CreateAllButtons(gameAPuzzles[i], dynamicModels, lastModelIndex);
    }

    RotateButtonMaster(gameAPuzzles[0], 45.f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[1], 80.0f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[2], 80.0f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(gameAPuzzles[3], DEG2RAD * 180.0f, (Vector3){0.0f, 1.0f, 0.0f});
    printf("%f, %f, %f\n", gameAPuzzles[1]->location.x, gameAPuzzles[1]->location.y, gameAPuzzles[1]->location.z);

    /*
        After the initialziation of our buttons, we want to perscribe special textures to them if they so require
    */
    AssignSpecialTexturesGameA(gameAPuzzles);
    
    gameAPuzzles[3]->puzzleToPowerOn = gameAPuzzles[4];
}

void AssignSpecialTexturesGameA(ButtonMaster** allPuzzles)
{
    //this is gross, please restructure this at some point 
    PuzzleTexture* onOffBar_01 = malloc(sizeof(PuzzleTexture));
    onOffBar_01->highlighted = LoadTexture("D:/CFiles/FirstGame/models/obj/button_highlighted_lines_up.png");
    onOffBar_01->idle = LoadTexture("D:/CFiles/FirstGame/models/obj/button_idle_lines_up.png");
    onOffBar_01->selected = LoadTexture("D:/CFiles/FirstGame/models/obj/button_selected_lines_up.png");
    onOffBar_01->off = LoadTexture("D:/CFiles/FirstGame/models/obj/button_off.png");
    LoadAndAssignSingleTexture(&allPuzzles[3]->childButtons[0][2], onOffBar_01, EBS_idle);
    AssignButtonToToggleAction(&allPuzzles[3]->childButtons[0][2], POOD_TopDown);

    PuzzleTexture* onOffBar_02 = malloc(sizeof(PuzzleTexture));
    onOffBar_02->highlighted = LoadTexture("D:/CFiles/FirstGame/models/obj/button_highlighted_lines_up.png");
    onOffBar_02->idle = LoadTexture("D:/CFiles/FirstGame/models/obj/button_idle_lines_up.png");
    onOffBar_02->selected = LoadTexture("D:/CFiles/FirstGame/models/obj/button_selected_lines_up.png");
    onOffBar_02->off = LoadTexture("D:/CFiles/FirstGame/models/obj/button_off.png");
    LoadAndAssignSingleTexture(&allPuzzles[4]->childButtons[1][2], onOffBar_02, EBS_off);
    AssignButtonToToggleAction(&allPuzzles[4]->childButtons[1][2], POOD_TopDown);
    
    PuzzleTexture* onOffBar_03 = malloc(sizeof(PuzzleTexture));
    onOffBar_03->highlighted = LoadTexture("D:/CFiles/FirstGame/models/obj/button_highlighted_lines_up.png");
    onOffBar_03->idle = LoadTexture("D:/CFiles/FirstGame/models/obj/button_idle_lines_up.png");
    onOffBar_03->selected = LoadTexture("D:/CFiles/FirstGame/models/obj/button_selected_lines_up.png");
    onOffBar_03->off = LoadTexture("D:/CFiles/FirstGame/models/obj/button_off.png");
    LoadAndAssignSingleTexture(&allPuzzles[0]->childButtons[0][0], onOffBar_03, EBS_idle);
    AssignButtonToToggleAction(&allPuzzles[0]->childButtons[0][0], POOD_RightLeft);

    PuzzleTexture* onOffBar_04 = malloc(sizeof(PuzzleTexture));
    onOffBar_04->highlighted = LoadTexture("D:/CFiles/FirstGame/models/obj/button_highlighted_lines_lr.png");
    onOffBar_04->idle = LoadTexture("D:/CFiles/FirstGame/models/obj/button_idle_lines_lr.png");
    onOffBar_04->selected = LoadTexture("D:/CFiles/FirstGame/models/obj/button_selected_lines_lr.png");
    onOffBar_04->off = LoadTexture("D:/CFiles/FirstGame/models/obj/button_off.png");
    LoadAndAssignSingleTexture(&allPuzzles[0]->childButtons[2][2], onOffBar_04, EBS_idle);
    AssignButtonToToggleAction(&allPuzzles[0]->childButtons[2][2], POOD_BottomUp);      

    PuzzleTexture* onOffBar_05 = malloc(sizeof(PuzzleTexture));  
    onOffBar_05->highlighted = LoadTexture("D:/CFiles/FirstGame/models/obj/button_highlighted_lines_ddl.png");
    onOffBar_05->idle = LoadTexture("D:/CFiles/FirstGame/models/obj/button_idle_lines_ddl.png");
    onOffBar_05->selected = LoadTexture("D:/CFiles/FirstGame/models/obj/button_selected_lines_ddl.png");
    onOffBar_05->off = LoadTexture("D:/CFiles/FirstGame/models/obj/button_off.png");
    LoadAndAssignSingleTexture(&allPuzzles[5]->childButtons[0][2], onOffBar_05, EBS_idle);
    AssignButtonToToggleAction(&allPuzzles[5]->childButtons[0][2], POOD_DDL); 

    PuzzleTexture* onOffBar_06 = malloc(sizeof(PuzzleTexture));
    onOffBar_06->highlighted = LoadTexture("D:/CFiles/FirstGame/models/obj/button_highlighted_lines_up.png");
    onOffBar_06->idle = LoadTexture("D:/CFiles/FirstGame/models/obj/button_idle_lines_up.png");
    onOffBar_06->selected = LoadTexture("D:/CFiles/FirstGame/models/obj/button_selected_lines_up.png");
    onOffBar_06->off = LoadTexture("D:/CFiles/FirstGame/models/obj/button_off.png");
    LoadAndAssignSingleTexture(&allPuzzles[5]->childButtons[0][0], onOffBar_06, EBS_highlighted);
    AssignButtonToToggleAction(&allPuzzles[5]->childButtons[0][0], POOD_BottomUp);

    PuzzleTexture* onOffBar_07 = malloc(sizeof(PuzzleTexture));
    onOffBar_07->highlighted = LoadTexture("D:/CFiles/FirstGame/models/obj/button_highlighted_lines_lr.png");
    onOffBar_07->idle = LoadTexture("D:/CFiles/FirstGame/models/obj/button_idle_lines_lr.png");
    onOffBar_07->selected = LoadTexture("D:/CFiles/FirstGame/models/obj/button_selected_lines_lr.png");
    onOffBar_07->off = LoadTexture("D:/CFiles/FirstGame/models/obj/button_off.png");
    LoadAndAssignSingleTexture(&allPuzzles[5]->childButtons[2][2], onOffBar_07, EBS_idle);
    AssignButtonToToggleAction(&allPuzzles[5]->childButtons[2][2], POOD_RightLeft);  
}

void LoadAndAssignSingleTexture(Button* button, PuzzleTexture* newTextures, enum ButtonState state)
{
    UnloadTexture(button->buttonTextures->highlighted);
    UnloadTexture(button->buttonTextures->idle);
    UnloadTexture(button->buttonTextures->selected);
    UnloadTexture(button->buttonTextures->off);
    free(button->buttonTextures);
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
    puzzle->solutionLocations[3] = (Vector2Int){2, 1};
    puzzle->solutionLocations[4] = (Vector2Int){2, 2};
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
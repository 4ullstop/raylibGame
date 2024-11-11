#include "gameapuzzles.h"
#include <stdlib.h>
#include <stdio.h>

void ConstructGameAPuzzles(ButtonMaster** gameAPuzzles, modelInfo** dynamicModels, int* lastModelIndex, FPSPlayer* player, GameplayElements* gameplayElements)
{
    // PuzzleTexture linesPuzzle = {0};
    // linesPuzzle.highlighted = LoadTexture("D:/CFiles/FirstGame/models/obj/button_highlighted_lines_up.png");
    // linesPuzzle.idle = LoadTexture("D:/CFiles/FirstGame/models/obj/button_idle_lines_up.png");
    // linesPuzzle.selected = LoadTexture("D:/CFiles/FirstGame/models/obj/button_selected_lines_up.png");
    
    ButtonMaster* puzzle_01 = malloc(sizeof(ButtonMaster));
    puzzle_01->columns = 3;
    puzzle_01->rows = 3;
    puzzle_01->location = (Vector3){0.0f, 1.0f, 0.0f};
    puzzle_01->buttonSpread = 0.5f;
    puzzle_01->hasBoxAssigned = false;
    puzzle_01->id = 123;
    puzzle_01->numberOfSolutions = 0;
    puzzle_01->player = player;
    Puzzle_01(puzzle_01);
    //ReadPuzzleCSV(puzzle_01, "D:/CFiles/FirstGame/filereading/csv/puzzle_01.csv");
    puzzle_01->associatedGameplayElements = malloc(sizeof(GameplayElements));
    AssignGameplayElementsToPuzzles(puzzle_01, NULL);
    gameAPuzzles[0] = puzzle_01;

    
    ButtonMaster* puzzle_02 = malloc(sizeof(ButtonMaster));
    puzzle_02->columns = 1;
    puzzle_02->rows = 1;
    puzzle_02->location = (Vector3){2.3f, 1.0f, -15.0f};
    puzzle_02->buttonSpread = 0.5f;
    puzzle_02->hasBoxAssigned = false;
    puzzle_02->id = 234;
    puzzle_02->numberOfSolutions = 0;
    puzzle_02->player = player;
    Puzzle_02(puzzle_02);
    //ReadPuzzleCSV(puzzle_02, "D:/CFiles/FirstGame/filereading/csv/puzzle_02.csv");
    puzzle_02->associatedGameplayElements = malloc(sizeof(GameplayElements));
    AssignGameplayElementsToPuzzles(puzzle_02, gameplayElements->doors[0]);
    gameAPuzzles[1] = puzzle_02;

    ButtonMaster* puzzle_03 = malloc(sizeof(ButtonMaster));
    puzzle_03->columns = 2;
    puzzle_03->rows = 2;
    puzzle_03->location = (Vector3){2.3f, 1.0f, -6.0f};
    puzzle_03->buttonSpread = 0.5f;
    puzzle_03->hasBoxAssigned = false;
    puzzle_03->id = 345;
    puzzle_03->numberOfSolutions = 0;
    puzzle_03->player = player;
    Puzzle_03(puzzle_03);
    //ReadPuzzleCSV(puzzle_03, "D:/CFiles/FirstGame/filereading/csv/puzzle_04.csv");
    puzzle_03->associatedGameplayElements = malloc(sizeof(GameplayElements));
    AssignGameplayElementsToPuzzles(puzzle_03, NULL);
    gameAPuzzles[2] = puzzle_03;

    ButtonMaster* puzzle_04 = malloc(sizeof(ButtonMaster));
    puzzle_04->columns = 1;
    puzzle_04->rows = 3;
    puzzle_04->location = (Vector3){0.0f, 0.0f, 0.0f};
    puzzle_04->buttonSpread = 0.5f;
    puzzle_04->hasBoxAssigned = false;
    puzzle_04->id = 192;
    puzzle_04->numberOfSolutions = 0;
    puzzle_04->player = player;
    Puzzle_04(puzzle_04);

    printf("here\n");
    for (int i = 0; i < NUMBER_OF_PUZZLES_A; i++)
    {
        CreateAllButtons(gameAPuzzles[i], dynamicModels, lastModelIndex);
    }
    RotateButtonMaster(puzzle_01, 45.f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(puzzle_02, 80.0f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(puzzle_03, 80.0f, (Vector3){0.0f, 1.0f, 0.0f});
    printf("%f, %f, %f\n", gameAPuzzles[1]->location.x, gameAPuzzles[1]->location.y, gameAPuzzles[1]->location.z);

    /*
        After the initialziation of our buttons, we want to perscribe special textures to them if they so require
    */
    
    

}

void AssignSpecialTexturesGameA(ButtonMaster** allPuzzles)
{
    PuzzleTexture* onOffBar = malloc(sizeof(PuzzleTexture));
    onOffBar->highlighted = LoadTexture("D:/CFiles/FirstGame/models/obj/button_highlighted_lines_up.png");
    onOffBar->idle = LoadTexture("D:/CFiles/FirstGame/models/obj/button_idle_lines.png");
    onOffBar->selected = LoadTexture("D:/CFiles/FirstGame/models/obj/button_selected_lines_up.png");
    allPuzzles[3]->childButtons[2][0].specialTexture = onOffBar;
}


/*
    {2,0} {2,1} {2,2}
    {1,0} {1,1} {1,2}
    {0,0} {0,1} {0,2}
*/

void Puzzle_01(ButtonMaster* puzzle)
{
    int numOfSolutions = 3;
    puzzle->numberOfSolutions = numOfSolutions;
    puzzle->solutionLocations = malloc(sizeof(Vector2Int) * numOfSolutions);
    puzzle->solutionLocations[0] = (Vector2Int){2, 0};
    puzzle->solutionLocations[1] = (Vector2Int){1, 1};
    puzzle->solutionLocations[2] = (Vector2Int){0, 2};
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
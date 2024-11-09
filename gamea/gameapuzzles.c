#include "gameapuzzles.h"
#include <stdlib.h>
#include <stdio.h>

void ConstructGameAPuzzles(ButtonMaster** gameAPuzzles, modelInfo** dynamicModels, int* lastModelIndex, FPSPlayer* player, GameplayElements* gameplayElements)
{
    ButtonMaster* puzzle_01 = malloc(sizeof(ButtonMaster));
    puzzle_01->columns = 3;
    puzzle_01->rows = 3;
    puzzle_01->location = (Vector3){0.0f, 1.0f, 0.0f};
    puzzle_01->buttonSpread = 0.5f;
    puzzle_01->hasBoxAssigned = false;
    puzzle_01->id = 123;
    puzzle_01->numberOfSolutions = 0;
    puzzle_01->player = player;
    ReadPuzzleCSV(puzzle_01, "D:/CFiles/FirstGame/filereading/csv/puzzle_01.csv");
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
    ReadPuzzleCSV(puzzle_02, "D:/CFiles/FirstGame/filereading/csv/puzzle_02.csv");
    puzzle_02->associatedGameplayElements = malloc(sizeof(GameplayElements));
    AssignGameplayElementsToPuzzles(puzzle_02, gameplayElements->doors[0]);
    gameAPuzzles[1] = puzzle_02;

    ButtonMaster* puzzle_03 = malloc(sizeof(ButtonMaster));
    puzzle_03->columns = 2;
    puzzle_03->rows = 2;
    puzzle_03->location = (Vector3){1.0f, 1.0f, -6.0f};
    puzzle_03->buttonSpread = 0.5f;
    puzzle_03->hasBoxAssigned = false;
    puzzle_03->id = 345;
    puzzle_03->numberOfSolutions = 0;
    puzzle_03->player = player;
    ReadPuzzleCSV(puzzle_03, "D:/CFiles/FirstGame/filereading/csv/puzzle_03.csv");
    puzzle_03->associatedGameplayElements = malloc(sizeof(GameplayElements));
    AssignGameplayElementsToPuzzles(puzzle_03, NULL);
    gameAPuzzles[2] = puzzle_03;


    printf("here\n");
    for (int i = 0; i < NUMBER_OF_PUZZLES_A; i++)
    {
        CreateAllButtons(gameAPuzzles[i], dynamicModels, lastModelIndex);
    }
    RotateButtonMaster(puzzle_01, 45.f, (Vector3){0.0f, 1.0f, 0.0f});
    RotateButtonMaster(puzzle_02, 80.0f, (Vector3){0.0f, 1.0f, 0.0f});
    printf("%f, %f, %f\n", gameAPuzzles[1]->location.x, gameAPuzzles[1]->location.y, gameAPuzzles[1]->location.z);

}
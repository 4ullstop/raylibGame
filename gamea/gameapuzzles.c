#include "gameapuzzles.h"
#include <stdlib.h>
#include <stdio.h>

void ConstructGameAPuzzles(ButtonMaster** gameAPuzzles, modelInfo** dynamicModels, int* lastModelIndex)
{
    ButtonMaster* puzzle_01 = malloc(sizeof(ButtonMaster));
    puzzle_01->columns = 3;
    puzzle_01->rows = 3;
    puzzle_01->location = (Vector3){0.0f, 1.0f, 0.0f};
    puzzle_01->buttonSpread = 0.5f;
    puzzle_01->hasBoxAssigned = false;
    puzzle_01->id = 123;
    puzzle_01->numberOfSolutions = 0;
    ReadPuzzleCSV(puzzle_01, "D:/CFiles/FirstGame/filereading/csv/puzzle_01.csv");
    gameAPuzzles[0] = puzzle_01;

    
    ButtonMaster* puzzle_02 = malloc(sizeof(ButtonMaster));
    puzzle_02->columns = 1;
    puzzle_02->rows = 1;
    puzzle_02->location = (Vector3){3.0f, 1.0f, -4.0f};
    puzzle_02->buttonSpread = 0.5f;
    puzzle_02->hasBoxAssigned = false;
    puzzle_02->id = 234;
    puzzle_02->numberOfSolutions = 0;
    ReadPuzzleCSV(puzzle_02, "D:/CFiles/FirstGame/filereading/csv/puzzle_02.csv");
    gameAPuzzles[1] = puzzle_02;

    
    for (int i = 0; i < NUMBER_OF_PUZZLES; i++)
    {
        CreateAllButtons(gameAPuzzles[i], dynamicModels, lastModelIndex);
    }
    RotateButtonMaster(puzzle_01, 45.f, (Vector3){0.0f, 1.0f, 0.0f});
    printf("%f, %f, %f\n", gameAPuzzles[1]->location.x, gameAPuzzles[1]->location.y, gameAPuzzles[1]->location.z);

}
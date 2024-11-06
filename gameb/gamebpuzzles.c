#include "gamebpuzzles.h"
#include <stdlib.h>

void ConstructGameBPuzzles(ButtonMaster** gameBPuzzles, modelInfo** dynamicModels, int* lastModelIndex)
{
    ButtonMaster* puzzle_01 = malloc(sizeof(ButtonMaster));
    puzzle_01->columns = 3;
    puzzle_01->rows = 3;
    puzzle_01->location = (Vector3){3.0f, 1.0f, 0.0f};
    puzzle_01->buttonSpread = 0.5f;
    puzzle_01->hasBoxAssigned = false;
    ReadPuzzleCSV(puzzle_01, "D:/CFiles/FirstGame/filereading/csv/puzzle_01.csv");
    gameBPuzzles[0] = puzzle_01;

    for (int i = 0; i < NUMBER_OF_PUZZLES_B; i++)
    {
        CreateAllButtons(gameBPuzzles[i], dynamicModels, lastModelIndex);
    }
    
}
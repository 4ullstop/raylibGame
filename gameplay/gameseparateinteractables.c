#include "gameseparateinteractables.h"

void CreateInteractablesForGameType(Interactable** interactables, QueryBox** areaQueryBoxes, ButtonMaster** allPuzzles, enum Gametype type, ExitCode* exitCode)
{
    if (type == EGT_A)
    {
        CreateGameAInteractables(interactables, areaQueryBoxes, allPuzzles, exitCode);
    }
    else
    {
        CreateGameBInteractables(interactables, areaQueryBoxes, allPuzzles, exitCode);
    }
}

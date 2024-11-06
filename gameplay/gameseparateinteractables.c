#include "gameseparateinteractables.h"

void CreateInteractablesForGameType(Interactable** interactables, QueryBox** areaQueryBoxes, ButtonMaster** allPuzzles, enum Gametype type)
{
    if (type == EGT_A)
    {
        CreateGameAInteractables(interactables, areaQueryBoxes, allPuzzles);
    }
    else
    {
        CreateGameBInteractables(interactables, areaQueryBoxes, allPuzzles);
    }
}
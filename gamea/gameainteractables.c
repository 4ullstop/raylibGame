#include "gameainteractables.h"
#include <stdlib.h>
#include <stdio.h>

void CreateGameAInteractables(Interactable** interactables, QueryBox** areaQueryBoxes, ButtonMaster** allPuzzles)
{
    ColBox* colBox_01 = malloc(sizeof(ColBox));
    NullifyColBoxValues(colBox_01);
    Interactable* interactable_01 = malloc(sizeof(Interactable));
    interactable_01->associatedPuzzle = NULL;
    interactable_01->id = 432;
    interactable_01->showsArrowKeyHint = false;
    ConstructInteractable(interactable_01, (Vector3){0.0f, 3.0f, -4.0f}, colBox_01, 2.0f, 2.0f, 2.0f);

    ColBox* puzzleBox_01 = malloc(sizeof(ColBox));
    NullifyColBoxValues(puzzleBox_01);
    puzzleBox_01->id = 2;
    Interactable* interactable_02 = malloc(sizeof(Interactable));
    interactable_02->type = ITT_Puzzle;
    interactable_02->hasBeenUsed = false;
    interactable_02->id = 23;
    interactable_02->showsArrowKeyHint = true;
    ConstructInteractable(interactable_02, (Vector3){0.0f, 0.0f, 0.0f}, puzzleBox_01, 2.0f, 2.0f, 2.0f);
    //AssignInteractionBoxToPuzzle(allPuzzles, interactable_02);
    puzzleBox_01->interact = PuzzleInteract;
    interactable_02->associatedPuzzle = allPuzzles[0];
    interactable_02->Location = allPuzzles[0]->location;

    ColBox* puzzleBox_02 = malloc(sizeof(ColBox));
    NullifyColBoxValues(puzzleBox_02);
    puzzleBox_02->id = 1;
    Interactable* interactable_03 = malloc(sizeof(Interactable));
    interactable_03->type = ITT_Puzzle;
    interactable_03->hasBeenUsed = false;
    interactable_03->id = 3;
    interactable_01->showsArrowKeyHint = false;
    ConstructInteractable(interactable_03, (Vector3){3.0f, 0.0f, -4.0f}, puzzleBox_02, 2.0f, 2.0f, 2.0f);
    //AssignInteractionBoxToPuzzle(allPuzzles, interactable_03);
    puzzleBox_02->interact = PuzzleInteract;
    interactable_03->associatedPuzzle = allPuzzles[1];
    interactable_03->Location = allPuzzles[1]->location;
    printf("%f, %f, %f\n", interactable_03->Location.x, interactable_03->Location.y, interactable_03->Location.z);

    interactables[0] = interactable_01;
    areaQueryBoxes[0]->associatedInteractables[0] = interactable_01;

    interactables[1] = interactable_02;
    areaQueryBoxes[0]->associatedInteractables[1] = interactable_02;

    interactables[2] = interactable_03;
    areaQueryBoxes[0]->associatedInteractables[2] = interactable_03;
}
#include "movepuzzle.h"
#include "../../initialization/window.h"
#include <stdio.h>
#include <stdlib.h>


void AssignMoveAction(Button* button, enum TextureCoordinateLocations textureLocations)
{
    button->buttonRules = malloc(sizeof(ButtonRules));
    button->buttonRules->moveRule = malloc(sizeof(MoveRule));
    button->buttonRules->moveRule->direction = ED_NULL;
    button->buttonRules->moveRule->movementUnits = 50;
    button->buttonRules->toggleRule = NULL;
}


void DetermineWindowMovement(enum Direction direction, Button* button)
{
    printf("Moving window\n");
    switch(direction)
    {
    case ED_Up:
	MoveWindowFromPuzzle(-button->buttonRules->moveRule->movementUnits, false);
	break;
    case ED_Down:
	MoveWindowFromPuzzle(button->buttonRules->moveRule->movementUnits, false);
	break;
    case ED_Left:
	MoveWindowFromPuzzle(-button->buttonRules->moveRule->movementUnits, true);
	break;
    case ED_Right:
	MoveWindowFromPuzzle(button->buttonRules->moveRule->movementUnits, true);
	break;
    default:
	printf("Movement unavailable\n");
	break;
    }
}

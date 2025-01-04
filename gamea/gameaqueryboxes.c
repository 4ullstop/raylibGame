#include "gameaqueryboxes.h"
#include <stdlib.h>

void CreateGameAQueryBoxes(QueryBox** areaQueryBoxes, ExitCode* exitCode)
{
    QueryBox* box_01 = malloc(sizeof(QueryBox));
    if (box_01 == NULL)
    {
	EditReturnCodeInfo(500, "Failed to allocate memory for QueryBox\n", exitCode);
	return;
    }
    box_01->areaBox = malloc(sizeof(ColBox));
    if (box_01->areaBox == NULL)
    {
	EditReturnCodeInfo(501, "Failed to allocate memory for QueryBox\n", exitCode);
	return;
    }
    box_01->location = (Vector3){1.0, 2.0, -15.0};
    box_01->length = 100.f;
    box_01->width = 100.f;
    box_01->height = 20.f;
    box_01->areaBox->id = 10;
    ConstructColBox(box_01->areaBox, box_01->location, box_01->width, box_01->height, box_01->length, exitCode);
    exitCode->numOfQueryBoxesLoaded = exitCode->numOfQueryBoxesLoaded + 1;
    
    areaQueryBoxes[0] = box_01;
    areaQueryBoxes[0]->numberOfInteractables = NUMBER_OF_INTERACTABLES_A;
}


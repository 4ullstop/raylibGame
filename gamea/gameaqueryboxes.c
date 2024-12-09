#include "gameaqueryboxes.h"
#include <stdlib.h>

void CreateGameAQueryBoxes(QueryBox** areaQueryBoxes)
{
    QueryBox* box_01 = malloc(sizeof(QueryBox));
    box_01->areaBox = malloc(sizeof(ColBox));
    box_01->location = (Vector3){1.0, 2.0, -15.0};
    box_01->length = 100.f;
    box_01->width = 100.f;
    box_01->height = 20.f;
    box_01->areaBox->id = 10;
    ConstructColBox(box_01->areaBox, box_01->location, box_01->width, box_01->height, box_01->length);

    areaQueryBoxes[0] = box_01;
    areaQueryBoxes[0]->numberOfInteractables = NUMBER_OF_INTERACTABLES_A;
}


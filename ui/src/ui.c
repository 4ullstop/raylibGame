#include "ui.h"
#include <stdlib.h>

void ConstructUIElements(UIElements** elements)
{
    UIElements* movementHintUI = malloc(sizeof(UIElements));
    movementHintUI->hidden = false;
    Image image =  LoadImage("D:/CFiles/FirstGame/UI/png");
    movementHintUI->texture = LoadTextureFromImage(image);
    UnloadImage(image);
    movementHintUI->screenLocation = (Vector2){100.f, 200.f};
    movementHintUI->scale = 1.0f;
    movementHintUI->id = 1;

    elements[0] = movementHintUI;
}

void ToggleMovementHintUI(bool hidden, UIElements** elements)
{
    //the id for this piece is

}
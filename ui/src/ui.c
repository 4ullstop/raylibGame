#include "ui.h"
#include <stdlib.h>
#include <stdio.h>

void ConstructUIElements(UIElements** elements)
{
    UIElements* movementHintUI = malloc(sizeof(UIElements));
    movementHintUI->hidden = false;
    Image image =  LoadImage("D:/CFiles/FirstGame/UI/png/wasd.png");
    movementHintUI->texture = LoadTextureFromImage(image);
    UnloadImage(image);
    movementHintUI->screenLocation = (Vector2){100.f, 200.f};
    movementHintUI->scale = 0.9f;
    movementHintUI->id = 1;
    movementHintUI->startHide = false;
    movementHintUI->tint = (Color){255, 255, 255, 255};
    movementHintUI->fadeAlpha = 0.0f;

    UIElements* interactHintUI = malloc(sizeof(UIElements));
    interactHintUI->hidden = true;
    image = LoadImage("D:/CFiles/FirstGame/UI/png/e.png");
    interactHintUI->texture = LoadTextureFromImage(image);
    UnloadImage(image);
    interactHintUI->screenLocation = (Vector2){100.0f, 200.0f};
    interactHintUI->scale = 0.9f;
    interactHintUI->id = 2;
    interactHintUI->startHide = false;
    interactHintUI->tint = (Color){255, 255, 255, 255};
    interactHintUI->fadeAlpha = 0.0f;


    elements[0] = movementHintUI;
    elements[1] = interactHintUI;
}

void DestructAllUIElements(UIElements** elements)
{
    for (int i = 0; i < UI_ELEMENT_TOTAL; i++)
    {
        UnloadTexture(elements[i]->texture);
        free(elements[i]);
        elements[i] = NULL;
    }
}

void ToggleMovementHintUI(bool hidden, UIElements** elements)
{
    //the id for this piece is
    
}

void FadeUIElement(UIElements* element)
{
    element->tint.a -= 1;
    if (element->tint.a <= 1)
    {
        FadeComplete(element);
    }
}

void FadeComplete(UIElements* element)
{
    element->hidden = true;
    element->tint = (Color){255, 255, 255, 255};
    element->startHide = false;
}
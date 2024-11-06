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

    UIElements* enterSubmitUI = malloc(sizeof(UIElements));
    enterSubmitUI->hidden = true;
    image = LoadImage("D:/CFiles/FirstGame/UI/png/enter.png");
    enterSubmitUI->texture = LoadTextureFromImage(image);
    UnloadImage(image);
    enterSubmitUI->screenLocation = (Vector2){100.0f, 200.0f};
    enterSubmitUI->scale = 0.9f;
    enterSubmitUI->id = 3;
    enterSubmitUI->startHide = false;
    enterSubmitUI->tint = (Color){255, 255, 255, 255};
    enterSubmitUI->fadeAlpha = 0.0f;

    UIElements* arrowHintUI = malloc(sizeof(UIElements));
    arrowHintUI->hidden = true;
    image = LoadImage("D:/CFiles/FirstGame/UI/png/arrows.png");
    arrowHintUI->texture = LoadTextureFromImage(image);
    UnloadImage(image);
    arrowHintUI->screenLocation = (Vector2){100.0f, 200.0f};
    arrowHintUI->scale = 1.0f;
    arrowHintUI->id = 4;
    arrowHintUI->startHide = false;
    arrowHintUI->tint = (Color){255, 255, 255, 255};
    arrowHintUI->fadeAlpha = 0.0f;

    elements[0] = movementHintUI;
    elements[1] = interactHintUI;
    elements[2] = enterSubmitUI;
    elements[3] = arrowHintUI;
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
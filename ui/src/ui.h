#ifndef UI_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "uistructs.h"
#endif 

void ConstructUIElements(UIElements** elements);

void ToggleMovementHintUI(bool hidden, UIElements** elements);

void FadeUIElement(UIElements* element);

void FadeComplete(UIElements* element);

void DestructAllUIElements(UIElements** elements);
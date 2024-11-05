#ifndef UISTRUCTS_HEAD
#include "C:\raylib\raylib\src\raylib.h"
#endif

#define UI_ELEMENT_TOTAL 2

#ifndef ELEMENTS
#define ELEMENTS
typedef struct UIElements 
{
    Texture2D texture;
    Vector2 screenLocation;
    float scale;
    bool hidden;
    int id;

    bool startHide;
    Color tint;

    double fadeAlpha;
} UIElements;
#endif
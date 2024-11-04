#ifndef UISTRUCTS_HEAD
#include "C:\raylib\raylib\src\raylib.h"
#include "../../initialization/corestructs.h"
#endif

#define UI_ELEMENT_TOTAL 1

#ifndef ELEMENTS
#define ELEMENTS
typedef struct UIElements 
{
    Texture2D texture;
    Vector2 screenLocation;
    float scale;
    bool hidden;
    int id;

} UIElements;
#endif
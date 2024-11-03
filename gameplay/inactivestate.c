#include "inactivestate.h"

void PollPlayerInactiveStateInputs(enum Gamemode* mode)
{
    if (IsCursorOnScreen() && IsKeyPressed(KEY_F))
    {
        *mode = EGM_Normal;
        HideCursor();
        DisableCursor();
    }   
    if (IsCursorOnScreen())
    {
        
    }
}
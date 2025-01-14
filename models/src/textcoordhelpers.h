#pragma once

#ifndef TEXTCOORDHELPERS_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#endif 


#ifndef TEXT_COORD_LOC
#define TEXT_COORD_LOC
enum TextureCoordinateLocations
{
    TCL_NULL,
    TCL_Plain,
    TCL_08,
    TCL_07,
    TCL_06,
    TCL_05,
    TCL_04,
    TCL_03,
    TCL_02,
    TCL_01,
    TCL_UD, //updown (or down up)
    TCL_LR, //left right (or right left)
    TCL_DDR, //down diagonal right
    TCL_UDR, //up diagonal right
    TCL_08UD,
    TCL_07UD,
    TCL_06UD,
    TCL_05UD,
    TCL_04UD,
    TCL_03UD,
    TCL_02UD,
    TCL_01UD,
    TCL_08LR,
    TCL_07LR,
    TCL_06LR,
    TCL_05LR,
    TCL_04LR,
    TCL_03LR,
    TCL_02LR,
    TCL_01LR,
    TCL_08DDR,
    TCL_07DDR,
    TCL_06DDR,
    TCL_05DDR,
    TCL_04DDR,
    TCL_03DDR,
    TCL_02DDR,
    TCL_01DDR,
    TCL_08UDR,
    TCL_07UDR,
    TCL_06UDR,
    TCL_05UDR,
    TCL_04UDR,
    TCL_03UDR,
    TCL_02UDR,
    TCL_01UDR,
    TCL_OFF,
    TCL_Move,
    TCL_SUB
};
#endif

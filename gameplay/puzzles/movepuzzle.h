#pragma once

#ifndef MOVE_PUZZLE_HEADER
#define MOVE_PUZZLE_HEADER
#include "../../initialization/corestructs.h"
#endif

void AssignMoveAction(Button* button, enum TextureCoordinateLocations textureLocations);

void DetermineWindowMovement(enum Direction direction, Button* button);

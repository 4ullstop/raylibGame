#ifndef BUTTON_ATLAS_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "../../initialization/corestructs.h"
#endif

void AssignButtonTextCoord(Model* model, enum TextureCoordinateLocations textureLocation);

void AssignAndUpdateTextRecForAtlas(Button* button, enum TextureCoordinateLocations textureLocation);

void UpdateShaderForButtonAtlas(Button* button, enum TextureCoordinateLocations textureLocation);
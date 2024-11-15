#pragma once

#ifndef GAMEA_TEXTURE_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "../initialization/corestructs.h"
#endif

void RetrieveGameATextureFiles(char** textureFiles);

void LoopThroughFiles(char** outputFiles, char** filesToRead);
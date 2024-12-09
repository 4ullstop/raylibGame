#pragma once

#ifndef TEXTURE_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "../../initialization/corestructs.h"
#include "../../gamea/gameatextures.h"
#include "../../gameb/gamebtextures.h"
#endif

void LoadAllTextures(Texture2D** allTextures, enum Gametype gametype);

void LoadGameAModels(Texture2D** allTextures);

void LoadGameBModels(Texture2D** allTextures);

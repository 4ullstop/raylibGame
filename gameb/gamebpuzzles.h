#ifndef GAMEBPUZZLES_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "../initialization/corestructs.h"
#include "../filereading/filereader.h"
#include "../gameplay/sharedbuttons.h"

#endif

void ConstructGameBPuzzles(ButtonMaster** gameBPuzzles, Texture2D** allTextures, modelInfo** dynamicModels, int* lastModelIndex, FPSPlayer* player, GameplayElements* gameplayElements);

void Puzzle_01B(ButtonMaster* puzzle);

void Puzzle_02B(ButtonMaster* puzzle);

void Puzzle_03B(ButtonMaster* puzzle);

void Puzzle_04B(ButtonMaster* puzzle);

void AssignSpecialTexturesGameB(ButtonMaster** allPuzzles, Texture2D** allTextures);

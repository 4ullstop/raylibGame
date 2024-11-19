#ifndef GAMEAPUZZLES_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "../initialization/corestructs.h"
#include "../filereading/filereader.h"
#include "../gameplay/sharedbuttons.h"
#include "../gameplay/puzzles/togglepuzzle.h"
#endif

void ConstructGameAPuzzles(ButtonMaster** gameAPuzzles, Texture2D** allTextures, modelInfo** dynamicModels, int* lastModelIndex, FPSPlayer* player, GameplayElements* gameplayElements, PuzzleTextureLocations* puzzleTextureLocations);

void Puzzle_01(ButtonMaster* puzzle);

void Puzzle_02(ButtonMaster* puzzle);

void Puzzle_03(ButtonMaster* puzzle);

void Puzzle_04(ButtonMaster* puzzle);

void Puzzle_05(ButtonMaster* puzzle);

void Puzzle_06(ButtonMaster* puzzle);

void AssignSpecialTexturesGameA(ButtonMaster** allPuzzles, Texture2D** allTextures, PuzzleTextureLocations* puzzleTextureLocations);

#pragma once
#ifndef GAMEBPUZZLES_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "../initialization/corestructs.h"
#include "../filereading/filereader.h"
#include "../gameplay/sharedbuttons.h"
#include "../shared/memory_editing.h"
#endif

void ConstructGameBPuzzles(ButtonMaster** gameBPuzzles, Texture2D** allTextures, modelInfo** dynamicModels, int* lastModelIndex, FPSPlayer* player, GameplayElements* gameplayElements, SharedMemory* sharedMemory, SharedPuzzleList** sharedPuzzleList, ExitCode* exitCode);

void Puzzle_01B(ButtonMaster* puzzle);

void Puzzle_02B(ButtonMaster* puzzle);

void Puzzle_03B(ButtonMaster* puzzle);

void Puzzle_04B(ButtonMaster* puzzle);

void Puzzle_05B(ButtonMaster* puzzle);

void Puzzle_06B(ButtonMaster* puzzle);

void Puzzle_07B(ButtonMaster* puzzle);

void AssignSpecialTexturesGameB(ButtonMaster** allPuzzles, Texture2D** allTextures);

void AddGameBPuzzlesToSharedMemory(ButtonMaster** allPuzzles, SharedMemory* sharedMemory);

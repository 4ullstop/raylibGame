#pragma once
#ifndef GAMEAPUZZLES_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "C:\raylib\raylib\src\raymath.h"
#include "../initialization/corestructs.h"
#include "../filereading/filereader.h"
#include "../gameplay/sharedbuttons.h"
#include "../gameplay/puzzles/togglepuzzle.h"
#include "../shared/memory_editing.h"
#endif

void ConstructGameAPuzzles(ButtonMaster** gameAPuzzles, Texture2D** allTextures, modelInfo** dynamicModels, int* lastModelIndex, FPSPlayer* player, GameplayElements* gameplayElements, SharedMemory* sharedMemory, SharedPuzzleList** sharedPuzzleList, ExitCode* exitCode);
void Puzzle_01(ButtonMaster* puzzle);

void Puzzle_02(ButtonMaster* puzzle);

void Puzzle_03(ButtonMaster* puzzle);

void Puzzle_04(ButtonMaster* puzzle);

void Puzzle_05(ButtonMaster* puzzle);

void Puzzle_06(ButtonMaster* puzzle);

void Puzzle_07(ButtonMaster* puzzle);

void Puzzle_08(ButtonMaster* puzzle);

void Puzzle_09(ButtonMaster* puzzle);

void Puzzle_10(ButtonMaster* puzzle);

void Puzzle_11(ButtonMaster* puzzle);

void Puzzle_12(ButtonMaster* puzzle);

void Puzzle_13(ButtonMaster* puzzle);

void Puzzle_14(ButtonMaster* puzzle);

void Puzzle_15(ButtonMaster* puzzle);

void Puzzle_16(ButtonMaster* puzzle);

void Puzzle_17(ButtonMaster* puzzle);

void Puzzle_18(ButtonMaster* puzzle);

void Puzzle_19(ButtonMaster* puzzle);

void Puzzle_20(ButtonMaster* puzzle);

void Puzzle_21(ButtonMaster* puzzle);

void AssignSpecialTexturesGameA(ButtonMaster** allPuzzles, Texture2D** allTextures);

void AddGameAPuzzlesToSharedMemory(ButtonMaster** allPuzzles, SharedMemory* sharedMemory);

#pragma once

#ifndef DESTROY_OBJECTS_HEADER
#define DESTROY_OBJECTS_HEADER
#include "../initialization/corestructs.h"
#include "processthreadsapi.h"
#include "../shared/memory_setup.h"
#endif

void DestroyAllModels(modelInfo** models, int numOfModels, Texture2D** allTextures, int numOfTextures);

void EnduceTearDown(modelInfo** models, int numOfModels, Texture2D** allTextures, int numOfTextures, ButtonMaster** allPuzzles, int numOfPuzzles, SharedPuzzleList** sharedPuzzleList, QueryBox** areaQueryBoxes, int numOfQueryBoxes, int numOfInteractables, OverlapBox** allOverlapBoxes, int numOfOverlapBoxes, GameplayElements* gameplayElements, int numOfDoors, STARTUPINFO* si, HANDLE* hMapFile, PROCESS_INFORMATION* pi, enum DestructionLocations destructionLocations, void* sharedMemVal, ExitCode* exitCode, enum Gametype gametype);

void UnloadAllTextures(Texture2D** allTextures, int numOfTextures);

void FreeAllTextures(Texture2D** allTextures, int numOfTextures);

void DestructAllPuzzles(ButtonMaster** allPuzzles, int numberOfPuzzles, SharedPuzzleList** sharedPuzzleList);

void DestructAllButtons(ButtonMaster* master);

void DestructAllPlainSubmittedButtons(ButtonMaster* puzzle);

void DestructAllSolutionLocations(ButtonMaster* master);

void DestroyAreasAndInteractables(QueryBox** areaQueryBoxes, int numOfQueryBoxes, int numOfInteractables);

void DestructInteractable(Interactable* interactable);

void DestructColBox(ColBox* box);

void DestroyOverlapBoxes(OverlapBox** allBoxes, int numOfOverlapBoxes);

void DestructAllGameplayElements(GameplayElements* gameplayElements, int numOfDoors);

void DestructAllDoors(Door** allDoors, int numOfDoors);

void DestroySwitchBoxes(GameplayElements* gameplayElements);

void DestroySwitches(SwitchBox* switchBox);

void DestroyIndicators(GameplayElements* gameplayElements);

void DestroySharedPuzzleList(SharedPuzzleList** sharedPuzzleList);

#pragma once

#ifndef DESTROY_OBJECTS_HEADER
#define DESTROY_OBJECTS_HEADER
#include "../initialization/corestructs.h"
#endif

void DestroyAllModels(modelInfo** models, int numOfModels, Texture2D** allTextures, int numOfTextures);

void EnduceTearDown(modelInfo** models, int numOfModels, Texture2D** allTextures, int numOfTextures, ButtonMaster** allPuzzles, int numOfPuzzles, QueryBox** areaQueryBoxes, int numOfQueryBoxes, int numOfInteractables, OverlapBox** allOverlapBoxes, enum DestructionLocations destructionLocations, ExitCode* exitCode);

void UnloadAllTextures(Texture2D** allTextures, int numOfTextures);

void FreeAllTextures(Texture2D** allTextures, int numOfTextures);

void DestructAllPuzzles(ButtonMaster** allPuzzles, int numberOfPuzzles);

void DestructAllButtons(ButtonMaster* master);

void DestructAllPlainSubmittedButtons(ButtonMaster* puzzle);

void DestructAllSolutionLocations(ButtonMaster* master);

void DestroyAreasAndInteractables(QueryBox** areaQueryBoxes, int numOfQueryBoxes, int numOfInteractables);

void DestructInteractable(Interactable* interactable);

void DestructColBox(ColBox* box);

void DestroyOverlapBoxes(OverlapBox** allBoxes);


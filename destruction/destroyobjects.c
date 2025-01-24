#include "destroyobjects.h"
#include <stdlib.h>
#include <stdio.h>

void EnduceTearDown(modelInfo** models, int numOfModels, Texture2D** allTextures, int numOfTextures, ButtonMaster** allPuzzles, int numOfPuzzles, QueryBox** areaQueryBoxes, int numOfQueryBoxes, int numOfInteractables, OverlapBox** allOverlapBoxes, int numOfOverlapBoxes, GameplayElements* gameplayElements, int numOfDoors, STARTUPINFO* si, HANDLE* hMapFile, PROCESS_INFORMATION* pi, enum DestructionLocations destructionLocations, void* sharedMemVal, ExitCode* exitCode, enum Gametype gametype)
{
    //destroy textures
    UnloadAllTextures(allTextures, numOfTextures);
    if (destructionLocations == DL_Textures && exitCode->gameLoaded == false)
    {
	FreeAllTextures(allTextures, numOfTextures);
	return;
    }


    DestroyAllModels(models, numOfModels, allTextures, numOfTextures);
    if (destructionLocations == DL_Models && exitCode->gameLoaded == false) return;

    //destroy puzzles
    DestructAllPuzzles(allPuzzles, numOfPuzzles);
    if (destructionLocations == DL_Puzzles && exitCode->gameLoaded == false) return;    

    DestroyAreasAndInteractables(areaQueryBoxes, numOfQueryBoxes, numOfInteractables);
    if (destructionLocations == DL_AreaQueryBoxes && exitCode->gameLoaded == false) return;    
    
    //destroy gameplay elements
    DestructAllGameplayElements(gameplayElements, numOfDoors);
    if (destructionLocations == DL_GameplayElements && exitCode->gameLoaded == false) return;
    
    //destroy overlaps
    DestroyOverlapBoxes(allOverlapBoxes, numOfOverlapBoxes);
    if (destructionLocations == DL_OverlapBoxes && exitCode->gameLoaded == false) return;

    //destroy shared memory
    if (gametype == EGT_A)
    {
	DestroySharedMemory(pi, hMapFile, sharedMemVal); 
    }
    else
    {
	DestroyChildSharedMemory(hMapFile, &sharedMemVal);
    }
    if (destructionLocations == DL_SharedMemory && exitCode->gameLoaded == false) return;
}

void DestroyAllModels(modelInfo** models, int numOfModels, Texture2D** allTextures, int numOfTextures)
{
    for (int i = 0; i < numOfModels; i++)
    {
	if (models[i] == NULL) continue;
        UnloadModel(models[i]->model);
        free(models[i]);
        models[i] = NULL;
    }
    FreeAllTextures(allTextures, numOfTextures);
}

void UnloadAllTextures(Texture2D** allTextures, int numOfTextures)
{
    for (int i = 0; i < numOfTextures; i++)
    {
	if (allTextures[i] == NULL) continue;
	UnloadTexture(*allTextures[i]);
    }
}

void FreeAllTextures(Texture2D** allTextures, int numOfTextures)
{
    for (int i = 0; i < numOfTextures; i++)
    {
	if (allTextures[i] == NULL) continue;
	free(allTextures[i]);
	allTextures[i] = NULL;
    }
}

void DestructAllPuzzles(ButtonMaster** allPuzzles, int numberOfPuzzles)
{
    for (int i = 0; i < numberOfPuzzles; i++)
    {
	DestructAllPlainSubmittedButtons(allPuzzles[i]);
        DestructAllButtons(allPuzzles[i]);
        if (allPuzzles[i]->associatedGameplayElements != NULL)
        {
            free(allPuzzles[i]->associatedGameplayElements);
            allPuzzles[i]->associatedGameplayElements = NULL;
        }
        DestructAllSolutionLocations(allPuzzles[i]);
        
        printf("solution locations destroyed\n");
        free(allPuzzles[i]);
        allPuzzles[i] = NULL;
    }
    printf("puzzles freed\n");
}

void DestructAllButtons(ButtonMaster* master)
{
    for (int i = 0; i < master->rows; i++)
    {
        if (master->childButtons[i]->buttonRules != NULL)
        {
            free(master->childButtons[i]->buttonRules->toggleRule);
            free(master->childButtons[i]->buttonRules);  
            master->childButtons[i]->buttonRules->toggleRule = NULL; 
            master->childButtons[i]->buttonRules = NULL;
        }
        if (master->childButtons[i]->loadedShader != NULL)
        {
            free(master->childButtons[i]->loadedShader);
        }
        free(master->childButtons[i]->buttonTextures);
        free(master->childButtons[i]);
        master->childButtons[i]->buttonTextures = NULL;
        master->childButtons[i] = NULL;
    }
    for (int i = 0; i < master->numberOfSolutions; i++)
    {
        master->solutionButtons[i] = NULL;
    }
}

void DestructAllPlainSubmittedButtons(ButtonMaster* puzzle)
{
    PlainSubmittedButtons* current = puzzle->plainSubmittedButtons;
    PlainSubmittedButtons* next;

    while (current != NULL)
    {
	next = current->next;
	free(current);
	current = next;
    }
}

void DestructAllSolutionLocations(ButtonMaster* master)
{
    free(master->correctOrder);
    free(master->solutionLocations);
    master->solutionLocations = NULL;
}

void DestroyAreasAndInteractables(QueryBox** areaQueryBoxes, int numOfQueryBoxes, int numOfInteractables)
{
    printf("num of queryboxes: %i\n", numOfQueryBoxes);
    printf("num of interactables: %i\n", numOfInteractables);
    for (int i = 0; i < numOfQueryBoxes; i++)
    {
        for (int j = 0; j < numOfInteractables; j++)
        {
            DestructInteractable(areaQueryBoxes[i]->associatedInteractables[j]);
            
            if (areaQueryBoxes[i]->associatedInteractables[j] != NULL)
            {
                free(areaQueryBoxes[i]->associatedInteractables[j]);
                areaQueryBoxes[i]->associatedInteractables[j] = NULL;
            }
            
        }
        DestructColBox(areaQueryBoxes[i]->areaBox);
        areaQueryBoxes[i]->areaBox = NULL;
        //Wouldn't doubt if there were still things that needed to be freed
        //but uhh... you got this Windows
    }
}

void DestructInteractable(Interactable* interactable) 
{
    DestructColBox(interactable->colBox);
}

void DestructColBox(ColBox* box)
{
    printf("ColBox id on destruct: %i\n", box->id);
    if (box->verts == NULL || box->indices == NULL|| box == NULL) return;
    printf("verts: %f\n", *box->verts);
    free(box->verts);
    box->verts = NULL;
    printf("ColBox destroyed\n");
    free(box->indices);
    box->indices = NULL;
    
    free(box);
    box = NULL;
    
}

void DestroyOverlapBoxes(OverlapBox** allBoxes, int numOfOverlapBoxes)
{
    for (int i = 0; i < numOfOverlapBoxes; i++)
    {
        DestructColBox(allBoxes[i]->collisionBox);
        free(allBoxes[i]);
        allBoxes[i] = NULL;
    }
}

void DestructAllGameplayElements(GameplayElements* gameplayElements, int numOfDoors)
{
//    DestructAllDoors(gameplayElements->doors, numOfDoors);
    DestroySwitchBoxes(gameplayElements);
}

void DestroySwitchBoxes(GameplayElements* gameplayElements)
{
    int switchBoxNum = gameplayElements->numOfSwitchBoxes;
    for (int i = 0; i < switchBoxNum; i++)
    {
	DestroySwitches(gameplayElements->switchBox[i]);
	free(gameplayElements->switchBox[i]);
	gameplayElements->switchBox[i] = NULL;
    }
    free(gameplayElements->switchBox);
    gameplayElements->switchBox = NULL;
}

void DestroySwitches(SwitchBox* switchBox)
{
    int switchNum = switchBox->numOfSwitches;
    for (int i = 0; i < switchNum; i++)
    {
	free(switchBox->allSwitches);
	switchBox->allSwitches++;
    }
}

void DestructAllDoors(Door* allDoors[], int numOfDoors)
{
    printf("alldoors %p\n", (void*)&allDoors[0]);
    printf("num of doors %i\n", numOfDoors);
    if (allDoors[0] != NULL)
    {
	free(allDoors[0]);
	allDoors[0] = NULL;
    }
    
    printf("Door destruct complete\n");
}

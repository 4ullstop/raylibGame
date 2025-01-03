#include "destroyobjects.h"
#include <stdlib.h>

void EnduceTearDown(modelInfo** models, int numOfModels, Texture2D** allTextures, int numOfTextures, ButtonMaster** allPuzzles, int numOfPuzzles, QueryBox** areaQueryBoxes, int numOfQueryBoxes, int numOfInteractables, OverlapBox** allOverlapBoxes, enum DestructionLocations destructionLocations)
{
    //destroy textures
    if (destructionLocations == DL_Textures) return;

    //destroy gameplay elements
    if (destructionLocations == DL_GameplayElements) return;

    //destroy puzzles
    if (destructionLocations == DL_Puzzles) return;

    //destroy models
    if (destructionLocations == DL_Models) return;

    //destroy area queries
    if (destructionLocations == DL_AreaQueryBoxes) return;

    //destroy interactables
    if (destructionLocations == DL_Interactables) return;

    //destroy overlaps
    if (destructionLocations == DL_OverlapBoxes) return;

    //destroy shared memory
    if (destructionLocations == DL_SharedMemory) return;

    //destroy threads
    if (destructionLocations == DL_Threads) return;
    
}

void DestroyAllModels(modelInfo** models, int numOfModels, Texture2D** allTextures, int numOfTextures)
{
    for (int i = 0; i < numOfTextures; i++)
    {
        UnloadTexture(*allTextures[i]);
    }
    for (int i = 0; i < numOfModels; i++)
    {
        UnloadModel(models[i]->model);
        free(models[i]);
        models[i] = NULL;
    }

    for (int i = 0; i < numOfTextures; i++)
    {
	free(allTextures[i]);
	allTextures[i] = NULL;
    }
}


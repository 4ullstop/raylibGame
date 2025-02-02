#include "gamebmodels.h"
#include "../models/src/modelinit.h"
#include <stdlib.h>
#include <stdio.h>

void CreateModelsForGameB(modelInfo** models, int* lastModelIndex, Texture2D** allTextures, ExitCode* exitCode)
{

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");

    printf("about to create models for game b\n");

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/floor_02.obj",
		      false,
		      true,
		      (Vector3){0.0f, 0.0f, 0.0f},
		      0);

    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/gameb/buildings/cabin.obj",
		      false,
		      true,
		      (Vector3){0.0f, 0.0f, 0.0f},
		      9);

    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/gameb/buildings/cabinstairs.obj",
		      false,
		      true,
		      (Vector3){0.0f, 0.0f, 0.0f},
		      0);
}



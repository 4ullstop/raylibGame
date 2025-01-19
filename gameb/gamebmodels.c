#include "gamebmodels.h"
#include "../models/src/modelinit.h"
#include <stdlib.h>

void CreateModelsForGameB(modelInfo** models, int* lastModelIndex, Texture2D** allTextures, ExitCode* exitCode)
{
    CreateSingleModel(models,
		      lastModelIndex,
		      allTextures,
		      exitCode,
		      "D:/CFiles/FirstGame/models/obj/floor.obj",
		      false,
		      true,
		      (Vector3){0.0f, 0.0f, 0.0f},
		      0);
}

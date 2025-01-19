#include "modelinit.h"
#include <stdlib.h>

void CreateSingleModel(modelInfo** models, int* lastModelIndex, Texture2D** allTextures, ExitCode* exitCode, char* fileLocation, bool collisionDisabled, bool modelVisible, Vector3 modelLocation, int textureIndex)
{
    modelInfo* model = malloc(sizeof(modelInfo));
    if (model == NULL)
    {
	EditReturnCodeInfo(400, "Failed to allocate mrmoy for model", exitCode);
	return;
    }
    model->collisionDisabled = collisionDisabled;
    model->modelVisible = modelVisible;
    model->model = LoadModel(fileLocation);
    model->texture = *allTextures[textureIndex];
    model->modelLocation = modelLocation;
    model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = model->texture;
    models[*lastModelIndex] = model;
    *lastModelIndex = *lastModelIndex + 1;
    exitCode->numOfModelsLoaded = exitCode->numOfModelsLoaded + 1;
    
}

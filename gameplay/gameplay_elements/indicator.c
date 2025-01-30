#include "indicator.h"
#include <stdio.h>
#include <stdlib.h>

void ConstructSingleIndicator(modelInfo** allModels, Texture2D** gameTextures, Indicator** allIndicators, char* modelFileLocation, Vector3 location, int gameTextureIndex, int indicatorId, int* lastIndicatorIndex, int* lastModelIndex, ExitCode* exitCode)
{
    printf("Constructing single indicator\n");
    Indicator* indicator = malloc(sizeof(Indicator));
    if (indicator == NULL)
    {
	EditReturnCodeInfo(1000, "Failed to allocate memory for indicator", exitCode);
	return;
    }
    indicator->model = malloc(sizeof(modelInfo));
    if (indicator->model == NULL)
    {
	EditReturnCodeInfo(1000, "Failed to allocate memory for indicator mesh", exitCode);
    }
    
    indicator->model->collisionDisabled = true;
    indicator->model->modelVisible = true; 
    indicator->location = location;
    printf("here\n");
    indicator->id = indicatorId;
    indicator->PowerOnIndicator = UpdateShaderForIndicator;
    indicator->model->modelLocation = indicator->location;
    indicator->model->model = LoadModel(modelFileLocation);
    printf("model loaded\n");
    indicator->indicatorTexture = IT_Off;
    indicator->model->texture = *gameTextures[gameTextureIndex];
    indicator->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = indicator->model->texture;
    allModels[*lastModelIndex] = indicator->model;
    *lastModelIndex = *lastModelIndex + 1;

    *lastIndicatorIndex = *lastIndicatorIndex + 1;
    exitCode->numOfModelsLoaded = exitCode->numOfModelsLoaded + 1;
    printf("indicator constructed\n");
}


void UpdateShaderForIndicator(Indicator* indicator)
{
    const float uvWidth = 1.0f / 2.0f;

    Shader* shader = malloc(sizeof(Shader));
    *shader = LoadShader(0, "D:/CFiles/FirstGame/shaders/indicator.fs");

    float offsetX = (float)((indicator->indicatorTexture - 1) % 2) * uvWidth;

    SetShaderValue(*shader, GetShaderLocation(*shader, "uvOffset"), (float[2]){offsetX, 1.0f}, SHADER_UNIFORM_VEC2);
    SetShaderValue(*shader, GetShaderLocation(*shader, "uvScale"), (float[2]){1.0f, 1.0f}, SHADER_UNIFORM_VEC2);

    indicator->model->model.materials[0].shader = *shader;
}

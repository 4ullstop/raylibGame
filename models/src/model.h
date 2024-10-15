#ifndef RAYLIB_CAMERA_HEAD
#include "C:\raylib\raylib\src\raylib.h"
#include "modelimport.h"
#include <stdlib.h>
#include <string.h>
#endif


void CompileModels(modelInfo** models, int size)
{
    modelInfo cube = 
    {
        cube.modelPathLocation = malloc(100 * sizeof(char)),
        cube.texturePathLocation = malloc(100 * sizeof(char)),
        cube.model = (Model){0},
        cube.texture = (Texture2D){0},
        cube.modelLocation = (Vector3){0.0f, 0.0f, 0.0f}
    };
    strcpy(cube.modelPathLocation, "C:/raylib/raylib/examples/models/resources/models/obj/cube_diffuse.png");
    strcpy(cube.texturePathLocation, "C:/raylib/raylib/examples/models/resources/models/obj/cube_diffuse.png");



    models[0] = &cube;
    InitModels(models, size);
}

void DestroyModels(modelInfo** models, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (models[i] != NULL)
        {
            free(models[i]->modelPathLocation);
            free(models[i]->texturePathLocation);
            free(models[i]);
        }
    }
}
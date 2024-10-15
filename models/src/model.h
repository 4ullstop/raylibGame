#ifndef RAYLIB_CAMERA_HEAD
#include "C:\raylib\raylib\src\raylib.h"
#include "modelimport.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#endif


void CompileModels(modelInfo** models, int size)
{
    printf("yo\n");
    modelInfo cube = 
    {
        cube.model = LoadModel("C:/raylib/raylib/examples/models/resources/models/obj/cube.obj"),
        cube.texture = LoadTexture("C:/raylib/raylib/examples/models/resources/models/obj/cube_diffuse.png"),
        cube.modelLocation = (Vector3){0.0f, 5.0f, 0.0f}
    };
    cube.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = cube.texture;



    models[0] = &cube;
}

void DestroyModels(modelInfo** models, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (models[i] != NULL)
        {
            free(models[i]);
        }
    }
}
#include "model.h"

void CreateModels(modelInfo** models)
{
    //cube model 01
    modelInfo* cube = malloc(sizeof(modelInfo));
    cube->model = LoadModel("C:/raylib/raylib/examples/models/resources/models/obj/cube.obj");
    cube->texture = LoadTexture("C:/raylib/raylib/examples/models/resources/models/obj/cube_diffuse.png");
    cube->modelLocation = (Vector3){5.0f, 0.0f, 0.0f};
    cube->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = cube->texture;
    
    modelInfo* cube_02 = malloc(sizeof(modelInfo));
    cube_02->model = LoadModel("C:/raylib/raylib/examples/models/resources/models/obj/cube.obj");
    cube_02->texture = LoadTexture("C:/raylib/raylib/examples/models/resources/models/obj/cube_diffuse.png");
    cube_02->modelLocation = (Vector3){-2.0f, 0.0f, 0.0f};
    cube_02->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = cube_02->texture;

    modelInfo* floor = malloc(sizeof(modelInfo));
    floor->model = LoadModel("D:/CFiles/FirstGame/models/obj/floor.obj");
    floor->texture = LoadTexture("C:/raylib/raylib/examples/models/resources/models/obj/cube_diffuse.png");
    floor->modelLocation = (Vector3){0.0f, 0.0f, 0.0f};
    floor->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floor->texture;

    models[0] = cube;
    models[1] = cube_02;
    models[2] = floor;
    
}

void DrawAllModels(modelInfo** models)
{
    for (int i = 0; i < NUMBER_OF_MODELS; i++)
    {
        DrawModel(models[i]->model, models[i]->modelLocation, 1.0f, WHITE);
    }
}

void DestroyAllModels(modelInfo** models)
{
    for (int i = 0; i < NUMBER_OF_MODELS; i++)
    {
        UnloadTexture(models[i]->texture);
        UnloadModel(models[i]->model);
        free(models[i]);
    }
}
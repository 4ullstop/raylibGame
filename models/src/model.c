#include "model.h"

/*
    Used for construction, destruction and drawing of static models
    within the scene, not intended for models that are associated 
    entities... probably
*/

void CreateModels(modelInfo** models, int* lastModelIndex, enum Gametype gametype)
{
    if (gametype == EGT_A)
    {
        printf("hello model here\n");
        CreateModelsForGameA(models, lastModelIndex);
    }
    else
    {
        CreateModelsForGameB(models, lastModelIndex);
    }

    
    printf("yo\n");

    // modelInfo* floor = malloc(sizeof(modelInfo));
    // floor->collisionDisabled = false;
    // floor->model = LoadModel("D:/CFiles/FirstGame/models/obj/floor.obj");
    // floor->texture = LoadTexture("C:/raylib/raylib/examples/models/resources/models/obj/cube_diffuse.png");
    // floor->modelLocation = (Vector3){0.0, 0.0, 0.0};
    // floor->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floor->texture;
    // models[*lastModelIndex] = floor;
    // *lastModelIndex = *lastModelIndex + 1;

    // modelInfo* cube = malloc(sizeof(modelInfo));
    // cube->collisionDisabled = false;
    // cube->model = LoadModel("C:/raylib/raylib/examples/models/resources/models/obj/cube.obj");
    // cube->texture = LoadTexture("C:/raylib/raylib/examples/models/resources/models/obj/cube_diffuse.png");
    // cube->modelLocation = (Vector3){5.0f, 0.0f, 0.0f};
    // cube->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = cube->texture;
    // models[*lastModelIndex] = cube;
    // *lastModelIndex = *lastModelIndex + 1;
    

    // modelInfo* cube_02 = malloc(sizeof(modelInfo));
    // cube_02->collisionDisabled = false;
    // cube_02->model = LoadModel("C:/raylib/raylib/examples/models/resources/models/obj/cube.obj");
    // cube_02->texture = LoadTexture("C:/raylib/raylib/examples/models/resources/models/obj/cube_diffuse.png");
    // cube_02->modelLocation = (Vector3){-2.0f, 0.0f, 0.0f};
    // cube_02->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = cube_02->texture;
    // models[*lastModelIndex] = cube_02;
    // *lastModelIndex = *lastModelIndex + 1;

    

    
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
        models[i] = NULL;
    }
}
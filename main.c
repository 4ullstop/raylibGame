#include "main.h"
#include "player/player.h"
#include "initialization/window.h"

#include <stdlib.h>
#include <stdio.h>



PlayerCam pcam = {0};
FPSPlayer player = {0};


double deltaTime = 0.0;
double lastTime = 0.0;

const float gravity = 400.0f;

float groundLevel = 2.0f;
float zVelocity = 0.0f;


Vector3 cubePos = {0.0f, 0.0f, 0.0f};
Vector3 twoCube = {0.0f, 5.0f, 0.0f};

CollisionPacket colPacket = {0};



int main(void)
{
    printf("Initializing window and player camera...\n");
    CreateWindow(800, 450);
    PlayerCamSetup(&pcam);
    PlayerSetup(&player, &pcam);
    //DO NOT PUT ANYTHING ABOVE THESE LINES, YOUR CODE WILL NOT WORK

    printf("Preparing model loading...\n");
    Model cube = LoadModel("C:/raylib/raylib/examples/models/resources/models/obj/cube.obj");
    Texture2D texture = LoadTexture("C:/raylib/raylib/examples/models/resources/models/obj/cube_diffuse.png");
    cube.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    //initializing all of our models
    modelInfo* models[NUMBER_OF_MODELS];
    CreateModels(models);
    

    colPacket.eRadius = (Vector3){1.0f, 1.0f, 1.0f};
    
    printf("Game loop starting...\n");
    while (!WindowShouldClose())
    {
        float now = GetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        
        InitializeModel(&cube, &texture);
        
        CallAllPolls(deltaTime, &cube);
        
        
        Draw(&cube, models);

    }

    DestroyAllModels(models);
    UnloadTexture(texture);
    UnloadModel(cube);
    CloseWindow();

    return 0;
}

void CallAllPolls(float dTime, Model* inModel)
{
    PollPlayer(dTime, &pcam, &player, &colPacket, inModel->meshes);
}

void Draw(Model* cubeModel, modelInfo** models)
{
    Mesh* mesh = cubeModel->meshes;
    
    BeginDrawing();

        ClearBackground(RAYWHITE);

        StartMode3D(pcam);

        //draw here
        DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f}, RED);
        
        
        DrawModel(*cubeModel, cubePos, 1.0f, WHITE);
        DrawAllModels(models);


        //debugging showing verts in cube mesh
        for (int i = 0, n = mesh->triangleCount; i < n; i++)
        {
            Vector3 vertex0 = 
            {
                mesh->vertices[i * 9],
                mesh->vertices[i * 9 + 1],
                mesh->vertices[i * 9 + 2]
            };
            Vector3 vertex1 = 
            {
                mesh->vertices[i * 9 + 3],
                mesh->vertices[i * 9 + 4],
                mesh->vertices[i * 9 + 5]
            };
            Vector3 vertex2 = 
            {
                mesh->vertices[i * 9 + 6],
                mesh->vertices[i * 9 + 7],
                mesh->vertices[i * 9 + 8]
            };
            DrawSphere(vertex0, 0.2f, BLUE);
            DrawSphere(vertex1, 0.2f, BLUE);
            DrawSphere(vertex2, 0.2f, BLUE);
        }

        
        

        DrawPlayerCollisionCapsule(player.location);

        Complete3DMode();

    EndDrawing();
}

void InitializeModel(Model* cube, Texture2D* text)
{
    if (IsFileDropped())
    {
        FilePathList droppedFiles = LoadDroppedFiles();

        if (droppedFiles.count == 1)
        {
            if(IsFileExtension(droppedFiles.paths[0], ".obj"))
            {
                UnloadModel(*cube);
                *cube = LoadModel(droppedFiles.paths[0]);
                cube->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *text;
            }
            else if (IsFileExtension(droppedFiles.paths[0], ".png"))
            {
                UnloadTexture(*text);
                *text = LoadTexture(droppedFiles.paths[0]);
                cube->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *text;
            }
            
        }
        UnloadDroppedFiles(droppedFiles);
    }
    
}
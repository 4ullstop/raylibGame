#include "main.h"
#include "player/player.h"
#include "initialization/window.h"
#include "collision/interactionbox.h" 
#include <stdlib.h>
#include <stdio.h>



PlayerCam pcam = {0};
FPSPlayer player = {0};


double deltaTime = 0.0;
double lastTime = 0.0;

const float gravity = 400.0f;

float groundLevel = 2.0f;
float zVelocity = 0.0f;


Vector3 cubePos = {-5.0f, 0.0f, 0.0f};
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
    
    //Set the size for our ellipsoid for collision
    colPacket.eRadius = (Vector3){1.0f, 1.0f, 1.0f};
    
    Vector3 interactLoc = (Vector3){0.0f, 3.0f, -4.0f};
    ColBox* colBox;
    Interactable* interactable = ConstructInteractable(interactLoc, colBox, 2.0f, 2.0f, 2.0f);
    interactable->colBox->showDebug = true;
    bool is = IsPointInInteractable(interactable, interactLoc);
    if (is)
    {
        printf("is in box\n");
    }
    /*
        Issues: 
         - is isn't true
         - we have random crashes
         - slow closes (most likely the result of improperly freeing memory)
    */

    printf("Game loop starting...\n");
    while (!WindowShouldClose())
    {
        float now = GetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        
        InitializeModel(&cube, &texture);
        
        CallAllPolls(deltaTime, models);
        
        
        Draw(models, interactable->colBox);

    }
    DestructInteractable(interactable);
    DestroyAllModels(models);
    UnloadTexture(texture);
    UnloadModel(cube);
    CloseWindow();

    return 0;
}

void CallAllPolls(float dTime, modelInfo** models)
{
    PollPlayer(dTime, &pcam, &player, &colPacket, models);
}

void Draw(modelInfo** models, ColBox* box)
{
    
    
    BeginDrawing();

        ClearBackground(RAYWHITE);

        StartMode3D(pcam);

        //draw here
        //DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f}, RED);
        
        DrawAllModels(models);

        

        if (box->showDebug)
        {
            
            for (int i = 0; i < box->randDirectionSize; i++)
            {
                DrawLine3D(box->debugPoint, box->randDirectionDebug[i], RED);
            }
            for (int i = 0; i < box->cubeVertsSize; i++)
            {
                DrawPoint3D(box->cubeVertsDebug[i], BLUE);
            }
            DrawPoint3D(box->debugPoint, GREEN);
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
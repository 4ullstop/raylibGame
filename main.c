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

Raycast ray = {0};

int main(void)
{
    printf("Initializing window and player camera...\n");
    CreateWindow(800, 450);
    
    PlayerCamSetup(&pcam);
    PlayerSetup(&player, &pcam);
    //DO NOT PUT ANYTHING ABOVE THESE LINES, YOUR CODE WILL NOT WORK


    ray.showDebugLines = true;
    ray.rayLength = 10.f;
    printf("Preparing model loading...\n");
    Model cube = LoadModel("C:/raylib/raylib/examples/models/resources/models/obj/cube.obj");
    Texture2D texture = LoadTexture("C:/raylib/raylib/examples/models/resources/models/obj/cube_diffuse.png");
    cube.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    //initializing all of our models
    modelInfo* models[NUMBER_OF_MODELS];
    CreateModels(models);

    Interactable* interactables[NUMBER_OF_INTERACTABLES];
    QueryBox* areaQueryBoxes[NUMBER_OF_AREA_QUERY_BOXES];
    CreatePlayerAreaQueries(areaQueryBoxes);
    CreateInteractables(interactables, areaQueryBoxes);
    
    //Set the size for our ellipsoid for collision
    colPacket.eRadius = (Vector3){1.0f, 1.0f, 1.0f};
    
    Vector3 interactLoc = (Vector3){0.0f, 3.0f, -4.0f};
    Vector3 point = (Vector3){0.0f, 3.0f, -4.0f};
    ColBox colBox = {0};
    Interactable interactable = {0};
    ConstructInteractable(&interactable, interactLoc, &colBox, 2.0f, 2.0f, 2.0f);
    interactable.colBox->showDebug = true;
    bool is = IsPointInInteractable(&interactable, point);
    if (is)
    {
        printf("is in box\n");
    }
    /*
        Where are we?:
            - Interaction system basics essentially works, I sort of tested it thats why I'm skeptical
            - I need to round out the system so that it takes into account player location
            to designated boxes so we aren't querying all of the boxes in the world inefficiently

    */

    printf("Game loop starting...\n");
    while (!WindowShouldClose())
    {
        float now = GetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        
        InitializeModel(&cube, &texture);
        
        CallAllPolls(deltaTime, models, &interactable);
        
        Draw(models, interactable.colBox, &ray, areaQueryBoxes);
    }
    DestructInteractable(&interactable);
    DestroyAllModels(models);
    UnloadTexture(texture);
    DestroyLines(ray.linesToDraw);
    UnloadModel(cube);
    CloseWindow();

    return 0;
}

void CallAllPolls(float dTime, modelInfo** models, Interactable* interactable)
{
    PollPlayer(dTime, &pcam, &player, &colPacket, models);
    PollPlayerSecondary(interactable->colBox, &player, &ray);
}

void Draw(modelInfo** models, ColBox* box, Raycast* ray, QueryBox** queryBoxes)
{
    
    BeginDrawing();

        ClearBackground(RAYWHITE);

        StartMode3D(pcam);

        //draw here
        
        
        DrawAllModels(models);

        for (int i = 0; i < NUMBER_OF_AREA_QUERY_BOXES; i++)
        {
            //printf("%f\n", queryBoxes[i]->width);
            DrawCubeWires(queryBoxes[i]->location, queryBoxes[i]->width, queryBoxes[i]->height, queryBoxes[i]->length, BLUE);
            
            for (int i = 0, n = queryBoxes[i]->numberOfInteractables; i < n; i++)
            {
                DrawCubeWires(queryBoxes[i]->associatedInteractables[0]->Location, 2.0f, 2.0f, 2.0f, RED);
            }
        }
        
        Drawline* line = ray->linesToDraw;

        while (line != NULL)
        {
            //printf("drawing new line\n");
            DrawLine3D(ray->linesToDraw->start, ray->linesToDraw->end, ray->linesToDraw->color);
            DrawSphere(line->hitpoint, 0.08f, RED);
            line = line->next;
        }
        
        
        
        if (box->showDebug)
        {
            DrawLine3D(box->debugPoint, box->randDirectionDebug[0], RED);
            for (int i = 0; i < box->vertsNum; i++)
            {
                DrawSphere(box->cubeVertsDebug[i], 0.1f, GREEN);
                //printf("Point %i: %f, %f, %f\n", i, box->cubeVertsDebug[i].x, box->cubeVertsDebug[i].y, box->cubeVertsDebug[i].z);
            }
            DrawSphere(box->debugPoint, 0.1f, RED);
            DrawPoint3D(box->debugPoint, GREEN);
        }
        // printf("\n");
        // printf("\n");
        // printf("\n");

        //DrawPlayerCollisionCapsule(player.location);
        
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
#include "main.h"
#include "gameplay/masterbuttons.h"
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

enum Gamemode gamemode = normal;

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

    //initializing all of our models
    modelInfo* models[NUMBER_OF_MODELS];
    //put the creation of gameplay elements here
    int lastModelIndex = 0;

    //At some point it would be nice to move this part to a separate file
    ButtonMaster puzzle_01;
    puzzle_01.columns = 3;
    puzzle_01.rows = 3;
    puzzle_01.location = (Vector3){0.0f, 2.0f, 0.0f};
    puzzle_01.buttonSpread = 0.5f;
    //
    
    CreateAllButtons(&puzzle_01, models, &lastModelIndex);
    CreateModels(models, &lastModelIndex);

    Interactable* interactables[NUMBER_OF_INTERACTABLES];
    QueryBox* areaQueryBoxes[NUMBER_OF_AREA_QUERY_BOXES];
    CreatePlayerAreaQueries(areaQueryBoxes);
    CreateInteractables(interactables, areaQueryBoxes);
    
    //Set the size for our ellipsoid for collision
    colPacket.eRadius = (Vector3){1.0f, 1.0f, 1.0f};

    /*
        Where are we?:
            - Buttons are initialized according to the system I designed and developed
            - Button functionality is the next thing as well as trying to make them
            look good so you have better visual feedback

    */

    printf("Game loop starting...\n");
    while (!WindowShouldClose())
    {
        float now = GetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        CallAllPolls(deltaTime, models, areaQueryBoxes);
        
        Draw(models, &ray, areaQueryBoxes);
    }
    DestroyAreasAndInteractables(areaQueryBoxes);
    DestructAllButtons(&puzzle_01);
    DestroyAllModels(models);
    DestroyLines(ray.linesToDraw);
    printf("destroyed\n");
    CloseWindow();

    return 0;
}

void CallAllPolls(float dTime, modelInfo** models, QueryBox** areaBoxes)
{
    PollPlayer(dTime, &pcam, &player, &colPacket, models);
    PollPlayerSecondary(&player, &ray, areaBoxes);
}

void Draw(modelInfo** models, Raycast* ray, QueryBox** queryBoxes)
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
            DrawSphere(line->hitpoint, 0.08f, PURPLE);
            line = line->next;
        }
        
        
        
        // if (box->showDebug)
        // {
        //     DrawLine3D(box->debugPoint, box->randDirectionDebug[0], RED);
        //     for (int i = 0; i < 12; i++)
        //     {
        //         DrawSphere(box->cubeVertsDebug[i], 0.1f, GREEN);
        //         //printf("%i\n", i);
        //         //printf("Point %i: %f, %f, %f\n", i, box->cubeVertsDebug[i].x, box->cubeVertsDebug[i].y, box->cubeVertsDebug[i].z);
        //     }
        //     DrawSphere(box->debugPoint, 0.1f, RED);
        //     DrawPoint3D(box->debugPoint, GREEN);
        // }
        // printf("\n");
        // printf("\n");
        // printf("\n");

        //DrawPlayerCollisionCapsule(player.location);
        
        Complete3DMode();
    
    EndDrawing();
}


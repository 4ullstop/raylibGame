#include "main.h"
#include "gameplay/masterbuttons.h"
#include "player/player.h"
#include "initialization/window.h"
#include "collision/interactionbox.h" 
#include "filereading/filereader.h"
#include <stdlib.h>
#include <stdio.h>

//telling opengl to use the graphics card and not the cpu
typedef unsigned long DWORD;

__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;

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

enum Gamemode gamemode = EGM_Normal;

enum Gametype gametype = EGT_A;


int main(int argc, char* argv[])
{
    printf("%i\n", argc);
    if (argc > 1) gametype = EGT_B;
    printf("Initializing window and player camera...\n");
    CreateWindow(800, 450);
    
    //intialize UI
    UIElements* ui[UI_ELEMENT_TOTAL];
    ConstructUIElements(ui);

    PlayerCamSetup(&pcam);
    PlayerSetup(&player, &pcam, ui);
    //DO NOT PUT ANYTHING ABOVE THESE LINES, YOUR CODE WILL NOT WORK

    Interactable interactedItem = {0};
    ray.showDebugLines = true;
    ray.rayLength = 10.f;
    printf("Preparing model loading...\n");

    //initializing all of our models
    modelInfo* models[NUMBER_OF_MODELS];
    //put the creation of gameplay elements here
    int lastModelIndex = 0;

    /*
        Creation of puzzles
    */
    ButtonMaster* allPuzzles[NUMBER_OF_PUZZLES];
    ConstructPuzzles(allPuzzles, models, &lastModelIndex, gametype);
    printf("puzzles constructed\n");
    CreateModels(models, &lastModelIndex, gametype);

    /*
        Creation of interactables
    */
    Interactable* interactables[NUMBER_OF_INTERACTABLES];
    QueryBox* areaQueryBoxes[NUMBER_OF_AREA_QUERY_BOXES];
    CreatePlayerAreaQueries(areaQueryBoxes);
    CreateInteractables(interactables, areaQueryBoxes, allPuzzles);
    
    

    OverlapBox* allBoxes[NUMBER_OF_OVERLAP_BOXES_A];
    ConstructOverlapBoxes(allBoxes);
    
    
    //Set the size for our ellipsoid for collision
    colPacket.eRadius = (Vector3){1.0f, 1.0f, 1.0f};

    /*
        Where are we?:
            - 

    */

    printf("Game loop starting...\n");
    while (!WindowShouldClose())
    {
        float now = GetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        CallAllPolls(deltaTime, models, areaQueryBoxes, &interactedItem, allBoxes);
        
        Draw(models, &ray, areaQueryBoxes, ui, allBoxes);

        
    }
    DestroyAreasAndInteractables(areaQueryBoxes);
    DestructAllPuzzles(allPuzzles);
    DestroyAllModels(models);
    DestroyLines(ray.linesToDraw);
    DestructAllUIElements(ui);
    DestroyOverlapBoxes(allBoxes);
    printf("destroyed\n");
    CloseWindow();

    return 0;
}

void CallAllPolls(float dTime, modelInfo** models, QueryBox** areaBoxes, Interactable* interactedItem, OverlapBox** overlapBoxes)
{
    if (gamemode == EGM_Normal)
    {
        PollPlayer(dTime, &pcam, &player, &colPacket, models);
        PollPlayerSecondary(&player, &ray, areaBoxes, &gamemode, interactedItem);
        PollOverlaps(overlapBoxes, &player);
    }
    else if (gamemode == EGM_Puzzle)
    {
        PollPlayerPuzzle(interactedItem);
    }
    else if (gamemode == EGM_Inactive)
    {
        PollPlayerInactiveStateInputs(&gamemode);
    }
    
}

void Draw(modelInfo** models, Raycast* ray, QueryBox** queryBoxes, UIElements** ui, OverlapBox** overlapQueryList)
{
    
    BeginDrawing();

        ClearBackground(RAYWHITE);

        StartMode3D(pcam);

        //draw here
        
        
        DrawAllModels(models);

        for (int i = 0; i < NUMBER_OF_AREA_QUERY_BOXES; i++)
        {
            //printf("%f\n", queryBoxes[i]->width);
            //printf("%i", i);
            DrawCubeWires(queryBoxes[i]->location, queryBoxes[i]->width, queryBoxes[i]->height, queryBoxes[i]->length, BLUE);
            
            for (int j = 0, n = queryBoxes[i]->numberOfInteractables; j < n; j++)
            {
                DrawCubeWires(queryBoxes[i]->associatedInteractables[j]->Location, queryBoxes[i]->associatedInteractables[j]->width, queryBoxes[i]->associatedInteractables[j]->height, queryBoxes[i]->associatedInteractables[j]->length, RED);
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
        
        //printf("about to draw overlap box\n");
        
        for (int i = 0; i < NUMBER_OF_OVERLAP_BOXES_A; i++)
        {
            if (overlapQueryList[i]->shouldDetect == true)
            {
                DrawCubeWires(overlapQueryList[i]->location, overlapQueryList[i]->width, overlapQueryList[i]->height, overlapQueryList[i]->length, BLACK);
                
            }
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

        Draw2D(ui);
    EndDrawing();
}

void Draw2D(UIElements** ui)
{
    //draw all UI here
    for (int i = 0; i < UI_ELEMENT_TOTAL; i++)
    {
        if (ui[i]->hidden == false && ui[i]->startHide == false)
        {
            DrawTextureEx(ui[i]->texture, (Vector2){10.f, 320.f}, 0.0f, ui[i]->scale, ui[i]->tint);
        }
        else if (ui[i]->hidden == false && ui[i]->startHide == true)
        {
            ui[i]->fadeAlpha += 0.00001 * deltaTime;
            if (ui[i]->fadeAlpha >= 1.0)
            {
                ui[i]->fadeAlpha = 0.0;
                FadeUIElement(ui[i]);
            }
        }
    }
}


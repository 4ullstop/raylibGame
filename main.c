#include "main.h"
#include "gameplay/masterbuttons.h"
#include "player/player.h"
#include "initialization/window.h"
#include "collision/interactionbox.h" 
#include "gameplay/gameseparateinteractables.h"
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
    PlayerSetup(&player, &pcam, ui, &gamemode);
    //DO NOT PUT ANYTHING ABOVE THESE LINES, YOUR CODE WILL NOT WORK

    Interactable interactedItem = {0};
    ray.showDebugLines = true;
    ray.rayLength = 10.f;
    printf("Preparing model loading...\n");

    //initializing all of our models
    //modelInfo* models[NUMBER_OF_MODELS];

    modelInfo* modelsA[NUMBER_OF_MODELS_A];
    modelInfo* modelsB[NUMBER_OF_MODELS_B];

    //put the creation of gameplay elements here
    int lastModelIndex = 0;
    int numOfModels = 0;
    if (gametype == EGT_A)
    {
        numOfModels = NUMBER_OF_MODELS_A;
    }
    else
    {
        numOfModels = NUMBER_OF_MODELS_B;
    }

    //
    /*
        Creation of puzzles
    */
    //ButtonMaster* allPuzzles[NUMBER_OF_PUZZLES];

    ButtonMaster* allPuzzlesA[NUMBER_OF_PUZZLES_A];
    ButtonMaster* allPuzzlesB[NUMBER_OF_PUZZLES_B];
    
    printf("puzzles constructed\n");
    int numOfPuzzles = 0;
    if (gametype == EGT_A)
    {
        ConstructPuzzles(allPuzzlesA, modelsA, &lastModelIndex, gametype, &player);
        CreateModels(modelsA, &lastModelIndex, gametype);\
        numOfPuzzles = NUMBER_OF_PUZZLES_A;
    }
    else
    {
        ConstructPuzzles(allPuzzlesB, modelsB, &lastModelIndex, gametype, &player);
        CreateModels(modelsB, &lastModelIndex, gametype);
        numOfPuzzles = NUMBER_OF_PUZZLES_B;
    }
    printf("puzzles created\n");

    /*
        Creation of interactables
    */
    //Interactable* interactables[NUMBER_OF_INTERACTABLES];

    Interactable* interactablesA[NUMBER_OF_INTERACTABLES_A];
    Interactable* interactablesB[NUMBER_OF_INTERACTABLES_B];

    //QueryBox* areaQueryBoxes[NUMBER_OF_AREA_QUERY_BOXES];
    QueryBox* areaQueryBoxesA[NUMBER_OF_AREA_QUERY_BOXES_A];
    QueryBox* areaQueryBoxesB[NUMBER_OF_AREA_QUERY_BOXES_B];
    int numOfInteractables = 0;
    int numOfQueryBoxes = 0;
    if (gametype == EGT_A)
    {
        CreatePlayerAreaQueries(areaQueryBoxesA);
        CreateInteractablesForGameType(interactablesA, areaQueryBoxesA, allPuzzlesA, gametype);
        numOfInteractables = NUMBER_OF_INTERACTABLES_A;
        numOfQueryBoxes = NUMBER_OF_AREA_QUERY_BOXES_A;
    }
    else
    {
        CreatePlayerAreaQueries(areaQueryBoxesB);
        CreateInteractablesForGameType(interactablesB, areaQueryBoxesB, allPuzzlesB, gametype);
        numOfInteractables = NUMBER_OF_INTERACTABLES_B;
        numOfQueryBoxes = NUMBER_OF_AREA_QUERY_BOXES_B;
    }


    
    //CreateInteractables(interactables, areaQueryBoxes, allPuzzles);
    
    
    

    //OverlapBox* allBoxes[NUMBER_OF_OVERLAP_BOXES_A];

    OverlapBox* allBoxesA[NUMBER_OF_OVERLAP_BOXES_A];
    OverlapBox* allBoxesB[NUMBER_OF_AREA_QUERY_BOXES_B];

    if (gametype == EGT_A)
    {
        ConstructOverlapBoxes(allBoxesA);
    }
    else
    {
        ConstructOverlapBoxes(allBoxesB);
    }
    
    
    
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

        if (gametype == EGT_A)
        {
            CallAllPolls(deltaTime, modelsA, areaQueryBoxesA, &interactedItem, allBoxesA, numOfModels, numOfQueryBoxes);
            Draw(modelsA, &ray, areaQueryBoxesA, ui, allBoxesA, numOfModels, numOfQueryBoxes, numOfInteractables);
        }
        else
        {
            CallAllPolls(deltaTime, modelsB, areaQueryBoxesB, &interactedItem, allBoxesB, numOfModels, numOfQueryBoxes);
            Draw(modelsB, &ray, areaQueryBoxesB, ui, allBoxesB, numOfModels, numOfQueryBoxes, numOfInteractables);
        }
    }
    
    
    if (gametype == EGT_A)
    {
        DestroyAllModels(modelsA, numOfModels);
        DestructAllPuzzles(allPuzzlesA, numOfPuzzles);
        DestroyAreasAndInteractables(areaQueryBoxesA, numOfQueryBoxes, numOfInteractables);
        DestroyOverlapBoxes(allBoxesA);
    }
    else
    {
        DestroyAllModels(modelsB, numOfModels);
        DestructAllPuzzles(allPuzzlesB, numOfPuzzles);
        DestroyAreasAndInteractables(areaQueryBoxesB, numOfQueryBoxes, numOfInteractables);
        DestroyOverlapBoxes(allBoxesB);
    }
    
    DestroyLines(ray.linesToDraw);
    DestructAllUIElements(ui);
    
    printf("destroyed\n");
    CloseWindow();

    return 0;
}

void CallAllPolls(float dTime, modelInfo** models, QueryBox** areaBoxes, Interactable* interactedItem, OverlapBox** overlapBoxes, int numberOfModels, int numOfAreaQueryBoxes)
{
    if (gamemode == EGM_Normal)
    {
        PollPlayer(dTime, &pcam, &player, &colPacket, models, numberOfModels);
        PollPlayerSecondary(&player, &ray, areaBoxes, &gamemode, interactedItem, numOfAreaQueryBoxes);
        PollOverlaps(overlapBoxes, &player);
    }
    else if (gamemode == EGM_Puzzle)
    {
        PollPlayerPuzzle(interactedItem, &gamemode);
    }
    else if (gamemode == EGM_Inactive)
    {
        PollPlayerInactiveStateInputs(&gamemode);
    }
    
}

void Draw(modelInfo** models, Raycast* ray, QueryBox** queryBoxes, UIElements** ui, OverlapBox** overlapQueryList, int numberOfModels, int numberOfQueryBoxes, int numberOfInteractables)
{
    
    BeginDrawing();

        ClearBackground(RAYWHITE);

        StartMode3D(pcam);

        //draw here
        DrawAllModels(models, numberOfModels);
        
        for (int i = 0; i < numberOfQueryBoxes; i++)
        {
            DrawCubeWires(queryBoxes[i]->location, queryBoxes[i]->width, queryBoxes[i]->height, queryBoxes[i]->length, BLUE);
            
            for (int j = 0, n = queryBoxes[i]->numberOfInteractables; j < n; j++)
            {
                DrawCubeWires(queryBoxes[i]->associatedInteractables[j]->Location, queryBoxes[i]->associatedInteractables[j]->width, queryBoxes[i]->associatedInteractables[j]->height, queryBoxes[i]->associatedInteractables[j]->length, RED);
            }
        }
        
        
        Drawline* line = ray->linesToDraw;

        while (line != NULL)
        {
            DrawLine3D(ray->linesToDraw->start, ray->linesToDraw->end, ray->linesToDraw->color);
            DrawSphere(line->hitpoint, 0.08f, PURPLE);
            line = line->next;
        }
        
        
        
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
        if (ui[i] == NULL)
        {
            continue;
        }
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


#include "main.h"
#include "gameplay/masterbuttons.h"
#include "player/player.h"
#include "initialization/window.h"
#include "collision/interactionbox.h" 
#include "gameplay/gameseparateinteractables.h"
#include "filereading/filereader.h"
#include <stdlib.h>
#include <stdio.h>

#define GLSL_VERSION 330

//telling opengl to use the graphics card and not the cpu graphics
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

GameplayElements gameplayElements = {0};


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

    modelInfo* modelsA[NUMBER_OF_MODELS_A];
    modelInfo* modelsB[NUMBER_OF_MODELS_B];

    Texture2D* texturesA[NUMBER_OF_TEXTURES_A];
    Texture2D* texturesB[NUMBER_OF_TEXTURES_B];


    //put the creation of gameplay elements here
    int lastModelIndex = 0;
    int numOfModels = 0;
    int numOfTextures = 0;
    if (gametype == EGT_A)
    {
        numOfModels = NUMBER_OF_MODELS_A;
        numOfTextures = NUMBER_OF_TEXTURES_A;
    }
    else
    {
        numOfModels = NUMBER_OF_MODELS_B;
        numOfTextures = NUMBER_OF_TEXTURES_B;
    }

    //
    /*
        Creation of puzzles
    */

    Door* allDoorsA[NUMBER_OF_DOORS_A];
    Door* allDoorsB[NUMBER_OF_DOORS_B];

    ButtonMaster* allPuzzlesA[NUMBER_OF_PUZZLES_A];
    ButtonMaster* allPuzzlesB[NUMBER_OF_PUZZLES_B];
    
    printf("Puzzles constructing...\n");
    int numOfPuzzles = 0;
    int numOfDoors = 0;
    if (gametype == EGT_A)
    {
        LoadAllTextures(texturesA, gametype);
        ConstructGameplayElements(modelsA, &lastModelIndex, texturesA, NUMBER_OF_DOORS_A, &gameplayElements, allDoorsA);
        ConstructPuzzles(allPuzzlesA, modelsA, &lastModelIndex, gametype, &player, &gameplayElements, texturesA);
        CreateModels(modelsA, &lastModelIndex, gametype, texturesA);
        numOfPuzzles = NUMBER_OF_PUZZLES_A;
        numOfDoors = NUMBER_OF_DOORS_A;
        
    }
    else
    {
        ConstructGameplayElements(modelsB, &lastModelIndex, texturesB, NUMBER_OF_DOORS_B, &gameplayElements, allDoorsB);
        ConstructPuzzles(allPuzzlesB, modelsB, &lastModelIndex, gametype, &player, &gameplayElements, texturesB);
        CreateModels(modelsB, &lastModelIndex, gametype, texturesB);
        numOfPuzzles = NUMBER_OF_PUZZLES_B;
        numOfDoors = NUMBER_OF_DOORS_B;
    }

    /*
        Creation of interactables
    */

    Interactable* interactablesA[NUMBER_OF_INTERACTABLES_A];
    Interactable* interactablesB[NUMBER_OF_INTERACTABLES_B];

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

    /*
        MAIN GAME LOOP
        MAIN GAME LOOP
        MAIN GAME LOOP
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
            PollAllGameplayElements(allDoorsA, deltaTime, numOfDoors);
            Draw(modelsA, &ray, areaQueryBoxesA, ui, allBoxesA, numOfModels, numOfQueryBoxes, numOfInteractables);
        }
        else
        {
            CallAllPolls(deltaTime, modelsB, areaQueryBoxesB, &interactedItem, allBoxesB, numOfModels, numOfQueryBoxes);
            PollAllGameplayElements(allDoorsB, deltaTime, numOfDoors);
            Draw(modelsB, &ray, areaQueryBoxesB, ui, allBoxesB, numOfModels, numOfQueryBoxes, numOfInteractables);
        }
    }
    /*
        MAIN GAME LOOP
        MAIN GAME LOOP
        MAIN GAME LOOP
    */

    if (gametype == EGT_A)
    {
        DestroyAllModels(modelsA, numOfModels, texturesA, numOfTextures);
        printf("models destroyed\n");
        DestructAllPuzzles(allPuzzlesA, numOfPuzzles);
        printf("puzzles destroyed\n");
        DestroyAreasAndInteractables(areaQueryBoxesA, numOfQueryBoxes, numOfInteractables);
        printf("interactables destroyed\n");
        DestroyOverlapBoxes(allBoxesA);
        printf("game a destroyed\n");
    }
    else
    {
        DestroyAllModels(modelsB, numOfModels, texturesB, numOfTextures);
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
            //DrawSphere(line->hitpoint, 0.08f, PURPLE);
            line = line->next;
        }
        
        
        for (int i = 0; i < NUMBER_OF_OVERLAP_BOXES_A; i++)
        {
            if (overlapQueryList[i]->shouldDetect == true)
            {
                DrawCubeWires(overlapQueryList[i]->location, overlapQueryList[i]->width, overlapQueryList[i]->height, overlapQueryList[i]->length, BLACK);
                
            }
        }

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


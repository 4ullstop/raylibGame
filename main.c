#include "main.h"
#include "gameplay/masterbuttons.h"
#include "player/player.h"
#include "initialization/window.h"
#include "collision/interactionbox.h" 
#include "gameplay/gameseparateinteractables.h"
#include "filereading/filereader.h"
#include <stdlib.h>
#include <stdio.h>
#include "processthreadsapi.h"
#include "shared/memory_setup.h"



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

HANDLE hMapFile;
HANDLE eventHandle;
STARTUPINFO si;
PROCESS_INFORMATION pi;

CollisionPacket colPacket = {0};

Raycast ray = {0};

enum Gamemode gamemode = EGM_Normal;

enum Gametype gametype = EGT_A;

GameplayElements gameplayElements = {0};

TickNode interactedItemTickNode = {0};

bool hideObjects;

int main(int argc, char* argv[])
{
    ExitCode exitCodes = {0};
    enum DestructionLocations destructionLocations = 0;
    exitCodes.returnCode = 0;
    exitCodes.gameLoaded = false;
    SharedMemory* sharedMemValA = malloc(sizeof(SharedMemory));
    sharedMemValA->sharedValTesting = 23;
    sharedMemValA->ActiveWindowA = false;
    sharedMemValA->gameClosing = false;
    hideObjects = false;
    printf("%i\n", argc);
    if (argc > 1) gametype = EGT_B;
    printf("Initializing window and player camera...\n");

    char* windowTitle = "";
    if (gametype == EGT_A)
    {
	windowTitle = "Scenea";
    }
    else
    {
	windowTitle = "Sceneb";
    }
    
    CreateWindow(800, 450, windowTitle);

    printf("\n");
    printf("num of argc: %i\n", argc);
    printf("\n");
    interactedItemTickNode.a = false;
    interactedItemTickNode.frameCounter = 0;
    interactedItemTickNode.frameSpeed = 0.1f;
    interactedItemTickNode.iterations = 0;

   

    //intialize UI
    UIElements* ui[UI_ELEMENT_TOTAL];
    ConstructUIElements(ui);

    PlayerCamSetup(&pcam);
    PlayerSetup(&player, &pcam, ui, &gamemode);
    //DO NOT PUT ANYTHING ABOVE THESE LINES, YOUR CODE WILL NOT WORK

    Interactable interactedItem = {0};
    interactedItem.associatedPuzzle = NULL;
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
	exitCodes.gameVersion = "A";
    }
    else
    {
        numOfModels = NUMBER_OF_MODELS_B;
        numOfTextures = NUMBER_OF_TEXTURES_B;
	exitCodes.gameVersion = "B";
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
        LoadAllTextures(texturesA, gametype, &exitCodes);
	if (CheckForErrors(&exitCodes, &destructionLocations)) goto KillProgram; 

        ConstructGameplayElements(modelsA, &lastModelIndex, texturesA, NUMBER_OF_DOORS_A, &gameplayElements, allDoorsA, &exitCodes);
	if (CheckForErrors(&exitCodes, &destructionLocations)) goto KillProgram; 
        ConstructPuzzles(allPuzzlesA, modelsA, &lastModelIndex, gametype, &player, &gameplayElements, texturesA, &exitCodes);
	if (CheckForErrors(&exitCodes, &destructionLocations)) goto KillProgram; 
	
        CreateModels(modelsA, &lastModelIndex, gametype, texturesA, &exitCodes);
	if (CheckForErrors(&exitCodes, &destructionLocations)) goto KillProgram; 
	
        numOfPuzzles = NUMBER_OF_PUZZLES_A;
        numOfDoors = NUMBER_OF_DOORS_A;
        
    }
    else
    {
	LoadAllTextures(texturesB, gametype, &exitCodes);
	if (CheckForErrors(&exitCodes, &destructionLocations)) goto KillProgram; 
	
        ConstructGameplayElements(modelsB, &lastModelIndex, texturesB, NUMBER_OF_DOORS_B, &gameplayElements, allDoorsB, &exitCodes);
	if (CheckForErrors(&exitCodes, &destructionLocations)) goto KillProgram; 
	
        ConstructPuzzles(allPuzzlesB, modelsB, &lastModelIndex, gametype, &player, &gameplayElements, texturesB, &exitCodes);
	if (CheckForErrors(&exitCodes, &destructionLocations)) goto KillProgram; 
	
	printf("puzzles created for game b\n");
	CreateModels(modelsB, &lastModelIndex, gametype, texturesB, &exitCodes);

	if (CheckForErrors(&exitCodes, &destructionLocations)) goto KillProgram; 
	
        numOfPuzzles = NUMBER_OF_PUZZLES_B;
        numOfDoors = NUMBER_OF_DOORS_B;
    }
    if (CheckForErrors(&exitCodes, &destructionLocations)) goto KillProgram; 

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
        CreatePlayerAreaQueries(areaQueryBoxesA, EGT_A, &exitCodes);

	if (CheckForErrors(&exitCodes, &destructionLocations)) goto KillProgram; 
	
        CreateInteractablesForGameType(interactablesA, areaQueryBoxesA, allPuzzlesA, gametype, &exitCodes);

	if (CheckForErrors(&exitCodes, &destructionLocations)) goto KillProgram; 
	
        numOfInteractables = NUMBER_OF_INTERACTABLES_A;
        numOfQueryBoxes = NUMBER_OF_AREA_QUERY_BOXES_A;
    }
    else
    {
        CreatePlayerAreaQueries(areaQueryBoxesB, EGT_B, &exitCodes);

	if (CheckForErrors(&exitCodes, &destructionLocations)) goto KillProgram; 
	
        CreateInteractablesForGameType(interactablesB, areaQueryBoxesB, allPuzzlesB, gametype, &exitCodes);

	if (CheckForErrors(&exitCodes, &destructionLocations)) goto KillProgram; 
	
        numOfInteractables = NUMBER_OF_INTERACTABLES_B;
        numOfQueryBoxes = NUMBER_OF_AREA_QUERY_BOXES_B;
    }

    OverlapBox* allBoxesA[NUMBER_OF_OVERLAP_BOXES_A];
    OverlapBox* allBoxesB[NUMBER_OF_AREA_QUERY_BOXES_B];

    if (gametype == EGT_A)
    {
        ConstructOverlapBoxes(allBoxesA, &exitCodes);
	if (CheckForErrors(&exitCodes, &destructionLocations)) goto KillProgram; 
    }
    else
    {
        ConstructOverlapBoxes(allBoxesB, &exitCodes);
	if (CheckForErrors(&exitCodes, &destructionLocations)) goto KillProgram; 
    }

    colPacket.eRadius = (Vector3){1.0f, 4.0f, 1.0f};

    if (gametype == EGT_A)
    {
	sharedMemValA  = (SharedMemory *)SetupSharedMemory(&si, &pi, &hMapFile, sizeof(SharedMemory), &eventHandle);
	sharedMemValA->sharedValTesting = 23;
	ReportEditedValue(&eventHandle);
	

    }
    else
    {
	sharedMemValA = (SharedMemory *)AttachChildProcessToMemory(&hMapFile, sizeof(SharedMemory));
	

    }

    SetWindowLocationForGameType(gametype);

    exitCodes.gameLoaded = true;
    
    /*
        Where are we?:
            -
    */

    /*
        MAIN GAME LOOP
        MAIN GAME LOOP
        MAIN GAME LOOP
    */
    bool doOnce = false;
    printf("Game loop starting...\n");
    printf("numOfLoaded models: %i\n", exitCodes.numOfModelsLoaded);
    printf("numOfLoaded puzzles: %i\n", exitCodes.numOfPuzzlesLoaded);
    while (!WindowShouldClose())
    {
        float now = GetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        if (gametype == EGT_A)
        {
            CallAllPolls(deltaTime, modelsA, areaQueryBoxesA, &interactedItem, allBoxesA, numOfModels, numOfQueryBoxes, sharedMemValA);
            PollAllGameplayElements(allDoorsA, deltaTime, numOfDoors);
            Draw(modelsA, &ray, areaQueryBoxesA, ui, allBoxesA, numOfModels, numOfQueryBoxes, numOfInteractables, allPuzzlesA);
        }
        else
        {
            CallAllPolls(deltaTime, modelsB, areaQueryBoxesB, &interactedItem, allBoxesB, numOfModels, numOfQueryBoxes, sharedMemValA);
            PollAllGameplayElements(allDoorsB, deltaTime, numOfDoors);
            Draw(modelsB, &ray, areaQueryBoxesB, ui, allBoxesB, numOfModels, numOfQueryBoxes, numOfInteractables, allPuzzlesB);
        }

	if (sharedMemValA->gameClosing == true)
	{
	    goto KillProgram;
	}
    }
    /*
        MAIN GAME LOOP END
        MAIN GAME LOOP END
        MAIN GAME LOOP END
    */



KillProgram:

    
    if (sharedMemValA->gameClosing == false)
    {
	sharedMemValA->gameClosing = true;
    }
    if (gametype == EGT_A)
    {
	EnduceTearDown(modelsA, exitCodes.numOfModelsLoaded, texturesA, numOfTextures, allPuzzlesA, exitCodes.numOfPuzzlesLoaded, areaQueryBoxesA, exitCodes.numOfQueryBoxesLoaded, exitCodes.numOfInteractablesLoaded, allBoxesA, exitCodes.numOfOverlapBoxesLoaded, &gameplayElements, exitCodes.numOfDoorsLoaded, &si, &hMapFile, &pi, destructionLocations, sharedMemValA, &exitCodes, gametype);
    }
    else
    {
	EnduceTearDown(modelsB, exitCodes.numOfModelsLoaded, texturesB, numOfTextures, allPuzzlesB, exitCodes.numOfPuzzlesLoaded, areaQueryBoxesB, exitCodes.numOfQueryBoxesLoaded, exitCodes.numOfInteractablesLoaded, allBoxesB, exitCodes.numOfOverlapBoxesLoaded, &gameplayElements, exitCodes.numOfDoorsLoaded, &si, &hMapFile, &pi, destructionLocations,sharedMemValA, &exitCodes, gametype);
    }
    
    DestroyLines(ray.linesToDraw);
    DestructAllUIElements(ui);

    printf("destroyed\n");
    CloseWindow();

    return 0;
}

void CallAllPolls(float dTime, modelInfo** models, QueryBox** areaBoxes, Interactable* interactedItem, OverlapBox** overlapBoxes, int numberOfModels, int numOfAreaQueryBoxes, SharedMemory* sharedMemory)
{
    if (gamemode == EGM_Normal)
    {
        PollPlayer(dTime, &pcam, &player, &colPacket, models, numberOfModels);
        PollPlayerSecondary(&player, &ray, areaBoxes, &gamemode, interactedItem, numOfAreaQueryBoxes, &hideObjects, dTime, sharedMemory, gametype);
        PollOverlaps(overlapBoxes, &player);
    }
    else if (gamemode == EGM_Puzzle)
    {
        PollPlayerPuzzle(&player, dTime, interactedItem, &gamemode);
    }
    else if (gamemode == EGM_Inactive)
    {
        PollPlayerInactiveStateInputs(&gamemode);
    }
    if (interactedItem != NULL)
    {
        if (interactedItem->associatedPuzzle != NULL)
        {
            PollPuzzles(interactedItem->associatedPuzzle, &interactedItemTickNode);
        }
    }
    
}

void Draw(modelInfo** models, Raycast* ray, QueryBox** queryBoxes, UIElements** ui, OverlapBox** overlapQueryList, int numberOfModels, int numberOfQueryBoxes, int numberOfInteractables, ButtonMaster** allPuzzles)
{   
    BeginDrawing();

        ClearBackground(RAYWHITE);

        StartMode3D(pcam);

        //draw here
        DrawAllModels(models, numberOfModels);
        
        if (hideObjects == false)
        {
            for (int i = 0; i < numberOfQueryBoxes; i++)
            {
                DrawCubeWires(queryBoxes[i]->location, queryBoxes[i]->width, queryBoxes[i]->height, queryBoxes[i]->length, BLUE);
                
                for (int j = 0, n = queryBoxes[i]->numberOfInteractables; j < n; j++)
                {
                    DrawCubeWires(queryBoxes[i]->associatedInteractables[j]->Location, queryBoxes[i]->associatedInteractables[j]->width, queryBoxes[i]->associatedInteractables[j]->height, queryBoxes[i]->associatedInteractables[j]->length, RED);
                }
            }
        }

        //DEBUG
        // for (int i = 0; i < NUMBER_OF_PUZZLES_A; i++)
        // {
        //     //printf("PuzzleNormal: %f, %f, %f\n", allPuzzles[i]->puzzleNormalDirection.x, allPuzzles[i]->puzzleNormalDirection.y, allPuzzles[i]->puzzleNormalDirection.z);
        //     Vector3 end = Vector3Add(Vector3Scale(allPuzzles[i]->puzzleNormalDirection, 10.f), allPuzzles[i]->location);
        //     DrawLine3D(Vector3Add(allPuzzles[i]->puzzleNormalDirection, allPuzzles[i]->location), end, RED);
        //     DrawSphere(Vector3Add(allPuzzles[i]->puzzleNormalDirection, allPuzzles[i]->location), 0.1f, BLUE);
        // }
        
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


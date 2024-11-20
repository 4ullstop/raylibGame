#include "sharedbuttons.h"
#include <stdlib.h>
#include <stdio.h>

void CreateAllButtons(ButtonMaster* master, modelInfo** dynamicModels, int* lastModelIndex, Texture2D** allTextures)
{
    
    printf("master id:%i\n", master->id);
    master->totalButtons = master->rows * master->columns;
    master->childButtons = (Button**)malloc(master->rows * sizeof(Button*));
    master->OnPuzzleSolved = OnPuzzleCompleted;
    Vector3 location = master->location;
    int r = master->rows;
    int c = master->columns;
    for (int i = 0; i < r; i++)
    {
        master->childButtons[i] = (Button*)malloc(c * sizeof(Button));
    }

    


    int centerR = round((float)r / 2.0);
    int centerC = round((float)c / 2.0); 
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("i: %i, j: %i\n", i, j);
            printf("\n");
            ConstructSingleButton(master, i, j, lastModelIndex, dynamicModels, allTextures);
        }
    }
}

void ConstructSingleButton(ButtonMaster* master, int i, int j, int* lastModelIndex, modelInfo** dynamicModels, Texture2D** allTextures)
{
    
    int centerR = floor((float)master->rows / 2.0);
    int centerC = floor((float)master->columns / 2.0);

    master->childButtons[i][j].buttonVectorLocation.x = i;
    master->childButtons[i][j].buttonVectorLocation.y = j;

    if (master->hasHighlightStartLoc == false)
    {    
        master->highlightStartLoc.x = centerR;
        master->highlightStartLoc.y = centerC;
    }


    int multipleR = i - centerR;
    float locX = master->location.x + (multipleR * master->buttonSpread);
    int multipleC = j - centerC;
    float locY = master->location.y + (multipleC * master->buttonSpread);
    master->childButtons[i][j].location = (Vector3){locX, locY, master->location.z};
    
    //setting up our neighbors which will be important when cycling through
    //based on the player input
    int below = j < 1 ? master->columns - 1 : j - 1;
    int above = j + 1 >= master->columns ? 0 : j + 1;
    int left = i < 1 ? master->rows - 1 : i - 1;
    int right = i + 1 >= master->rows ? 0 : i + 1;

    master->childButtons[i][j].nAbove = &master->childButtons[i][above];
    master->childButtons[i][j].nBelow = &master->childButtons[i][below];
    master->childButtons[i][j].nLeft = &master->childButtons[left][j];
    master->childButtons[i][j].nRight = &master->childButtons[right][j];

    
    master->childButtons[i][j].solutionButton = false;
    for (int k = 0, n = master->numberOfSolutions; k < n; k++)
    {
        if (master->solutionLocations[k].x == j && master->solutionLocations[k].y == i)
        {
            master->childButtons[i][j].solutionButton = true;
            printf("Puzzle solution location for puzzle: %i, (%i, %i)\n", master->id, i, j);
        }
    }

    PuzzleTexture* buttonTextures = malloc(sizeof(PuzzleTexture));
    buttonTextures->highlighted = *allTextures[39];
    buttonTextures->idle = *allTextures[38];
    buttonTextures->selected = *allTextures[40];
    buttonTextures->off = *allTextures[5];

    //initializng the associated models for the mechanic
    
    
    

    master->childButtons[i][j].model = malloc(sizeof(modelInfo));
    master->childButtons[i][j].model->collisionDisabled = true;
    master->childButtons[i][j].isBeingAssessed = false;
    master->childButtons[i][j].buttonTextures = buttonTextures;
    master->childButtons[i][j].puzzleType = EPT_Free;
    master->childButtons[i][j].isBeingAssessed = false;
    master->childButtons[i][j].model->modelLocation = master->childButtons[i][j].location;
    master->childButtons[i][j].model->model = LoadModel("D:/CFiles/FirstGame/models/obj/button_03.obj");
    AssignButtonTextCoord(&master->childButtons[i][j].model->model, TCL_Plain);
    master->childButtons[i][j].buttonState = EBS_idle;
    master->childButtons[i][j].highlighted = false;
    master->childButtons[i][j].model->texture = buttonTextures->idle;
    master->childButtons[i][j].buttonRules = NULL;
    master->childButtons[i][j].ButtonSelected = NULL;
    master->childButtons[i][j].submitted = false;
    master->childButtons[i][j].id = rand();
    dynamicModels[*lastModelIndex] = master->childButtons[i][j].model;
    *lastModelIndex = *lastModelIndex + 1;
    //highlighting our middle button
    printf("creating button model\n");



    if (i == master->highlightStartLoc.x && j == master->highlightStartLoc.y)
    {
        SwitchTextureOnPuzzleState(master, &master->childButtons[i][j], true);
    }
    else
    {
        SwitchTextureOnPuzzleState(master, &master->childButtons[i][j], false);
    }
    
}

void SwitchTextureOnPuzzleState(ButtonMaster* puzzle, Button* button, bool isHighlightedButton)
{
    switch (puzzle->puzzleState)
    {
    case EPS_active:
        if (isHighlightedButton != true)
        {
            button->model->texture = button->buttonTextures->idle;
        }
        else
        {
            button->highlighted = true;
            AddHighlight(button);
        }
        break;
    case EPS_inactive:
        button->model->texture = button->buttonTextures->off;
        if (isHighlightedButton == true)
        {
            button->highlighted = true;   
        }
        break;
    default:
        printf("PUZZLE STATE IS NOT SET\n");
        break;
    }
    button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture;
}

void AddHighlight(Button* button)
{
    button->highlighted = true;
    button->buttonState = EBS_highlighted;
    button->model->texture = button->buttonTextures->highlighted;
    button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture; 
}

void RotateButtonMaster(ButtonMaster* master, float angle, Vector3 axis)
{
    int centerR = floor((float)master->rows / 2.0);
    int centerC = floor((float)master->columns / 2.0);
    for (int i = 0; i < master->rows; i++)
    {
        for (int j = 0; j < master->columns; j++)
        {
            if (i == centerR && j == centerC)
            {
                master->childButtons[i][j].model->model.transform = MatrixRotateXYZ((Vector3){axis.x * angle, axis.y * angle, axis.z * angle});
                continue;
            }
            Vector3 newLocation = RotateAroundPoint(master->childButtons[i][j].location, master->childButtons[centerR][centerC].location, angle, axis);
            master->childButtons[i][j].location = newLocation;
            master->childButtons[i][j].model->modelLocation = master->childButtons[i][j].location; 
            master->childButtons[i][j].model->model.transform = MatrixRotateXYZ((Vector3){axis.x * angle, axis.y * angle, axis.z * angle});
        }
    }
}

void OnPuzzleCompleted(ButtonMaster* master)
{
    printf("puzzle complete\n");
    if (master->id == 1)
    {
        master->player->playerHUD[2]->hidden = true;
    }
    InactGameplayElement(master->associatedGameplayElements);

    if (master->puzzleToPowerOn != NULL)
    {
        PowerOnPuzzle(master->puzzleToPowerOn);
    }

}

void PowerOnPuzzle(ButtonMaster* puzzle)
{
    printf("Powering on powered off puzzle: %i\n", puzzle->id);
    puzzle->puzzleState = EPS_active;
    for (int i = 0, n = puzzle->rows; i < n; i++)
    {
        for (int j = 0, m = puzzle->columns; j < m; j++)
        {
            SwitchTextureOnPuzzleState(puzzle, &puzzle->childButtons[i][j], puzzle->childButtons[i][j].highlighted);
        }
    }
}

void AssignGameplayElementsToPuzzles(ButtonMaster* puzzle, Door* door)
{

    if (door != NULL)
    {
        printf("the door is not null\n");
        puzzle->associatedGameplayElements->associatedDoor = door;
        printf("doors[0]: %p\n", (void*)&door);
        printf("ptr val in puzzle: %p\n", &puzzle->associatedGameplayElements->associatedDoor);
    }
    else
    {
        printf("should be null\n");
        puzzle->associatedGameplayElements = NULL;
    }
    
}

void InactGameplayElement(GameplayElements* gameplayElement)
{
    printf("enacting gameplay element\n");
    if (gameplayElement != NULL && gameplayElement->associatedDoor != NULL)
    {
        printf("something is not null when it should be\n");
        gameplayElement->associatedDoor->isLowering = true;
    }
    printf("gameplay element enacted\n");
}

void ConstructSinglePuzzle(int* lastPuzzleIndex, int columns, int rows, Vector3 location, FPSPlayer* player, void(*puzzleLocConstruct)(ButtonMaster*), bool hasGameplayElements, GameplayElements* gameplayElements, ButtonMaster** gameAPuzzles, Vector2Int highlightStart, bool hasHighlightStartLoc, enum PuzzleState puzzleState)
{
    ButtonMaster* puzzle = malloc(sizeof(ButtonMaster));
    puzzle->columns = columns;
    puzzle->rows = rows;
    puzzle->location = location;
    puzzle->puzzleToPowerOn = NULL;
    puzzle->buttonSpread = 0.5f;
    puzzle->hasBoxAssigned = false;
    puzzle->id = *lastPuzzleIndex;
    puzzle->player = player;
    puzzle->puzzleState = puzzleState;
    puzzleLocConstruct(puzzle);
    puzzle->highlightStartLoc = highlightStart;
    puzzle->hasHighlightStartLoc = hasHighlightStartLoc;
    puzzle->associatedGameplayElements = malloc(sizeof(GameplayElements));
    if (hasGameplayElements == true)
    {
        AssignGameplayElementsToPuzzles(puzzle, gameplayElements->doors[0]);
    }
    else
    {
        AssignGameplayElementsToPuzzles(puzzle, NULL);
    }
    gameAPuzzles[*lastPuzzleIndex] = puzzle;
    *lastPuzzleIndex = *lastPuzzleIndex + 1;
}

//this is our function that will need to be assigned to our function pointer for special
//button actions
void EnactButton(Button* button)
{
    switch (button->puzzleType)
    {
    case EPT_Free:
        printf("button is free of action\n");
        break;
    case EPT_OnOff:
        EnactToggle(button);
        break;
    default:
        printf("button unassigned action\n");
        break;
    }
}

void AssignAllPuzzlesSolutionButtons(ButtonMaster** allPuzzles)
{
    for (int i = 0; i < NUMBER_OF_PUZZLES_A; i++)
    {
        AssignSolutionButtonsToPuzzle(allPuzzles[i]);
    }
}

void AssignSolutionButtonsToPuzzle(ButtonMaster* puzzle)
{
    printf("num of solutions: %i\n", puzzle->numberOfSolutions);
    for (int i = 0; i < puzzle->numberOfSolutions; i++)
    {
        puzzle->solutionButtons[i] = &puzzle->childButtons[puzzle->solutionLocations[i].y][puzzle->solutionLocations[i].x]; //be sure to remove the dangling pointers when these are destroyed   
        puzzle->solutionButtons[i]->textureSizes = puzzle->textureSizes[i];
        puzzle->solutionButtons[i]->buttonSolutionIndex = i;
        printf("buttonSolutionIndex is: %i\n", puzzle->solutionButtons[i]->buttonSolutionIndex);
    }
}

void AssignTextureAndActionAtSpot(Texture2D** allTextures, PuzzleTexture** puzzleTextures, Button* button, enum PuzzleOnOffDirection direction, enum ButtonState state)
{
    PuzzleTexture* textureToUse = NULL;
    switch (direction)
    {
    case POOD_BottomUp:
        textureToUse = puzzleTextures[1];
        break;
    case POOD_TopDown:
        textureToUse = puzzleTextures[1];
        break;
    case POOD_LeftRight:
        textureToUse = puzzleTextures[0];
        break;
    case POOD_RightLeft:
        textureToUse = puzzleTextures[0];
        break;
    case POOD_DDL:
        textureToUse = puzzleTextures[2];
        break;
    default:
        printf("ERROR BUTTON DIRECTION NOT SET IN ASSIGNTEXTUREANDACTIONATSPOT\n");
        break;
    }
    LoadAndAssignSingleTexture(button, textureToUse, state);
    AssignButtonToToggleAction(button, direction);
}

void AssignSolutionLocationTextures(PuzzleTexture** solutionTextures, ButtonMaster* puzzle)
{
    for (int i = 0; i < puzzle->numberOfSolutions; i++)
    {
        SwitchOnSolutionSizes(puzzle->solutionButtons[i], solutionTextures, puzzle->solutionButtons[i]->buttonState);
    }
}

void SwitchOnSolutionSizes(Button* button, PuzzleTexture** solutionTextures, enum ButtonState state)
{
    PuzzleTexture* assignedTexture = NULL;
    printf("button texturesSizes: %i\n", button->textureSizes);
    switch (button->textureSizes)
    {
    case EBTS_02:
        assignedTexture = solutionTextures[0];
        break;
    case EBTS_03:
        assignedTexture = solutionTextures[1];
        break;
    case EBTS_04:
        assignedTexture = solutionTextures[2];
        break;
    case EBTS_05:
        assignedTexture = solutionTextures[3];
        break;
    case EBTS_06:
        assignedTexture = solutionTextures[4];
        break;
    case EBTS_07:
        assignedTexture = solutionTextures[5];
        break;
    case EBTS_08:
        assignedTexture = solutionTextures[6];
        break;
    default:
        printf("ERROR SOLUTION BUTTONTEXTURESIZES UNASSIGNED\n");
        return;
    }
    printf("About to load and assign single texture\n");
    LoadAndAssignSingleTexture(button, assignedTexture, state);
}

void LoadAllSpecialTextures(PuzzleTexture** textures, Texture2D** allTextures)
{
    textures[0] = malloc(sizeof(PuzzleTexture));
    textures[0]->highlighted = *allTextures[10];
    textures[0]->idle = *allTextures[11];
    textures[0]->off = *allTextures[5];
    textures[0]->selected = *allTextures[12];
    
    textures[1] = malloc(sizeof(PuzzleTexture));
    textures[1]->highlighted = *allTextures[6];
    textures[1]->idle = *allTextures[7];
    textures[1]->off = *allTextures[5];
    textures[1]->selected = *allTextures[8];

    textures[2] = malloc(sizeof(PuzzleTexture));
    textures[2]->highlighted = *allTextures[13];
    textures[2]->idle = *allTextures[14];
    textures[2]->off = *allTextures[5];
    textures[2]->selected = *allTextures[15];
}

void LoadAndAssignSingleTexture(Button* button, PuzzleTexture* newTextures, enum ButtonState state)
{
    button->buttonTextures = newTextures;
    switch (state)
    {
    case EBS_highlighted:
        button->model->texture = newTextures->highlighted;
        break;
    case EBS_idle:
        button->model->texture = newTextures->idle;
        break;
    case EBS_selected:
        button->model->texture = newTextures->selected;
        break;
    case EBS_off:
        button->model->texture = newTextures->off;
        break;
    default:
        button->model->texture = newTextures->idle;
        printf("ERROR!: DEFAULT RUN IN LOADANDASSIGNSINGLETEXTURE\n");
    }
    button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture;
}

void LoadAllSolutionTextures(PuzzleTexture** solutionTextures, Texture2D** allTextures)
{
    printf("about to allocate textures\n");
    
    solutionTextures[0] = malloc(sizeof(PuzzleTexture));
    solutionTextures[0]->highlighted = *allTextures[17];
    solutionTextures[0]->idle = *allTextures[24];
    solutionTextures[0]->selected = *allTextures[31];
    solutionTextures[0]->off = *allTextures[5];

    solutionTextures[1] = malloc(sizeof(PuzzleTexture));
    solutionTextures[1]->highlighted = *allTextures[18];
    solutionTextures[1]->idle = *allTextures[25];
    solutionTextures[1]->selected = *allTextures[32];
    solutionTextures[1]->off = *allTextures[5];

    solutionTextures[2] = malloc(sizeof(PuzzleTexture));
    solutionTextures[2]->highlighted = *allTextures[19];
    solutionTextures[2]->idle = *allTextures[26];
    solutionTextures[2]->selected = *allTextures[33];
    solutionTextures[2]->off = *allTextures[5];

    solutionTextures[3] = malloc(sizeof(PuzzleTexture));
    solutionTextures[3]->highlighted = *allTextures[20];
    solutionTextures[3]->idle = *allTextures[27];
    solutionTextures[3]->selected = *allTextures[34];
    solutionTextures[3]->off = *allTextures[5];

    solutionTextures[4] = malloc(sizeof(PuzzleTexture));
    solutionTextures[4]->highlighted = *allTextures[21];
    solutionTextures[4]->idle = *allTextures[28];
    solutionTextures[4]->selected = *allTextures[35];
    solutionTextures[4]->off = *allTextures[5];
    
    solutionTextures[5] = malloc(sizeof(PuzzleTexture));
    solutionTextures[5]->highlighted = *allTextures[22];
    solutionTextures[5]->idle = *allTextures[29];
    solutionTextures[5]->selected = *allTextures[36];
    solutionTextures[5]->off = *allTextures[5];
    
    solutionTextures[6] = malloc(sizeof(PuzzleTexture));
    solutionTextures[6]->highlighted = *allTextures[23];
    solutionTextures[6]->idle = *allTextures[30];
    solutionTextures[6]->selected = *allTextures[37];
    solutionTextures[6]->off = *allTextures[5];

    printf("made it to the end\n");
}


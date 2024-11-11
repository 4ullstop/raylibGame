#include "sharedbuttons.h"
#include <stdlib.h>
#include <stdio.h>

void CreateAllButtons(ButtonMaster* master, modelInfo** dynamicModels, int* lastModelIndex)
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
            ConstructSingleButton(master, i, j, lastModelIndex, dynamicModels);
        }
    }
}

void ConstructSingleButton(ButtonMaster* master, int i, int j, int* lastModelIndex, modelInfo** dynamicModels)
{
    
    int centerR = floor((float)master->rows / 2.0);
    int centerC = floor((float)master->columns / 2.0);

    master->childButtons[i][j].buttonVectorLocation.x = i;
    master->childButtons[i][j].buttonVectorLocation.y = j;


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

    for (int k = 0, n = master->numberOfSolutions; k < n; k++)
    {
        if (master->solutionLocations[k].x == j && master->solutionLocations[k].y == i)
        {
            master->childButtons[i][j].solutionButton = true;
        }
    }

    PuzzleTexture* buttonTextures = malloc(sizeof(PuzzleTexture));
    buttonTextures->highlighted = LoadTexture("D:/CFiles/FirstGame/models/obj/buttonHighlighted.png");
    buttonTextures->idle = LoadTexture("D:/CFiles/FirstGame/models/obj/buttonIdle.png");
    buttonTextures->selected = LoadTexture("D:/CFiles/FirstGame/models/obj/buttonSelected.png");

    //initializng the associated models for the mechanic
    master->childButtons[i][j].model = malloc(sizeof(modelInfo));
    master->childButtons[i][j].model->collisionDisabled = true;
    master->childButtons[i][j].buttonTextures = buttonTextures;
    master->childButtons[i][j].puzzleType = EPT_Free;
    master->childButtons[i][j].model->modelLocation = master->childButtons[i][j].location;
    master->childButtons[i][j].model->model = LoadModel("D:/CFiles/FirstGame/models/obj/button2.obj");
    master->childButtons[i][j].buttonState = EBS_idle;
    master->childButtons[i][j].model->texture = buttonTextures->idle;
    master->childButtons[i][j].model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = master->childButtons[i][j].model->texture;
    master->childButtons[i][j].highlighted = false;
    master->childButtons[i][j].submitted = false;
    dynamicModels[*lastModelIndex] = master->childButtons[i][j].model;
    *lastModelIndex = *lastModelIndex + 1;
    //highlighting our middle button
    printf("creating button model\n");
    if (i == centerC && j == centerR)
    {
        master->childButtons[i][j].highlighted = true;
        AddHighlight(&master->childButtons[i][j]);
    }
    
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
    if (master->id == 234)
    {
        master->player->playerHUD[2]->hidden = true;
    }
    InactGameplayElement(master->associatedGameplayElements);

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
    
    if (gameplayElement != NULL && gameplayElement->associatedDoor != NULL)
    {
        
        gameplayElement->associatedDoor->isLowering = true;
    }

}




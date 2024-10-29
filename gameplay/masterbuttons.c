#include "masterbuttons.h"
#include <stdlib.h>

void CreateAllButtons(ButtonMaster* master, modelInfo** dynamicModels, int* lastModelIndex)
{
    master->totalButtons = master->rows * master->columns;
    master->childButtons = (Button**)malloc(master->rows * sizeof(Button*));
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
            ConstructSingleButton(master, i, j, lastModelIndex, dynamicModels);
        }
    }
}

void ConstructSingleButton(ButtonMaster* master, int i, int j, int* lastModelIndex, modelInfo** dynamicModels)
{
    int centerR = round((float)master->rows / 2.0);
    int centerC = round((float)master->columns / 2.0);

    master->childButtons[i][j].buttonVectorLocation.x = i;
    master->childButtons[i][j].buttonVectorLocation.y = j;

    int multipleR = i - centerR;
    float locX = master->location.x + (multipleR * master->buttonSpread);
    int multipleC = j - centerC;
    float locY = master->location.y + (multipleC * master->buttonSpread);
    master->childButtons[i][j].location = (Vector3){locX, locY, master->location.z};
    
    //setting up our neighbors which will be important when cycling through
    //based on the player input
    int above = i < 1 ? master->rows - 1 : i - 1;
    int below = i >= master->rows ? 0 : i + 1;
    int left = j < 1 ? master->columns - 1 : j - 1;
    int right = j >= master->columns ? 0 : j + 1;

    master->childButtons[i][j].nAbove = &master->childButtons[above][j];
    master->childButtons[i][j].nBelow = &master->childButtons[below][j];
    master->childButtons[i][j].nLeft = &master->childButtons[i][left];
    master->childButtons[i][j].nRight = &master->childButtons[i][right];

    //initializng the associated models for the mechanic
    master->childButtons[i][j].model = malloc(sizeof(modelInfo));
    master->childButtons[i][j].model->modelLocation = master->childButtons[i][j].location;
    // master->childButtons[i][j].model->model = LoadModel();
    // master->childButtons[i][j].model->texture = LoadTexture();
    dynamicModels[*lastModelIndex] = &master->childButtons[i][j].model;
    *lastModelIndex++;
    //highlighting our middle button
    if (i == centerR && j == centerC)
    {
        master->childButtons[i][j].highlighted = true;
    }
}
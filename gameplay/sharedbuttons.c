#include "sharedbuttons.h"
#include "puzzles/movepuzzle.h"
#include <stdlib.h>
#include <stdio.h>

void CreateAllButtons(ButtonMaster* master, modelInfo** dynamicModels, int* lastModelIndex, Texture2D** allTextures, ExitCode* exitCode)
{

    if (master == NULL || lastModelIndex == NULL)
    {
	EditReturnCodeInfo(207, "Puzzle/model index null", exitCode);
	return;
    }
    
    printf("master id:%i\n", master->id);
    master->totalButtons = master->rows * master->columns;
    master->childButtons = (Button**)malloc(master->rows * sizeof(Button*));
    if (master->childButtons == NULL)
    {
	EditReturnCodeInfo(202, "Failed to allocate memory for childbuttons\n", exitCode);
	return;
    }
    
    Vector3 location = master->location;
    int r = master->rows;
    int c = master->columns;
    for (int i = 0; i < r; i++)
    {
        master->childButtons[i] = (Button*)malloc(c * sizeof(Button));
	if (master->childButtons[i] == NULL)
	{
	    EditReturnCodeInfo(203, "Failed to allocate memory for child button\n", exitCode);
	}
    }

    


    int centerR = round((float)r / 2.0);
    int centerC = round((float)c / 2.0); 
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("i: %i, j: %i\n", i, j);
            printf("\n");
            ConstructSingleButton(master, i, j, lastModelIndex, dynamicModels, allTextures, exitCode);
        }
    }
}

void ConstructSingleButton(ButtonMaster* master, int i, int j, int* lastModelIndex, modelInfo** dynamicModels, Texture2D** allTextures, ExitCode* exitCode)
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
    if (buttonTextures == NULL)
    {
	EditReturnCodeInfo(204, "Failed to allocate memory for buttontextures\n", exitCode);
	return;
    }
    buttonTextures->highlighted = *allTextures[4];
    buttonTextures->idle = *allTextures[3];
    buttonTextures->selected = *allTextures[5];
    buttonTextures->off = *allTextures[6];
    buttonTextures->error = *allTextures[7];
    buttonTextures->completed = *allTextures[8];
    
    //initializng the associated models for the mechanic
    master->childButtons[i][j].model = malloc(sizeof(modelInfo));
    if (master->childButtons[i][j].model == NULL)
    {
	EditReturnCodeInfo(205, "Failed to allocate memory for button model", exitCode);
	return;
    }

    int halfRows = master->rows / 2;
    
    
    master->childButtons[i][j].model->collisionDisabled = true;
    master->childButtons[i][j].model->modelVisible = true;
    master->childButtons[i][j].isBeingAssessed = false;
    master->childButtons[i][j].buttonTextures = buttonTextures;
    master->childButtons[i][j].puzzleType = EPT_Free;
    master->childButtons[i][j].isBeingAssessed = false;
    master->childButtons[i][j].model->modelLocation = master->childButtons[i][j].location;
    master->childButtons[i][j].shouldStayPoweredOff = false;
    master->childButtons[i][j].loadedShader = NULL;
    master->childButtons[i][j].model->model = LoadModel("D:/CFiles/FirstGame/models/obj/button.obj");
    exitCode->numOfModelsLoaded = exitCode->numOfModelsLoaded + 1;
    master->childButtons[i][j].buttonTextures = buttonTextures;
    master->childButtons[i][j].buttonTextureLocation = TCL_NULL;
    master->childButtons[i][j].buttonState = EBS_idle;
    master->childButtons[i][j].highlighted = false;
    master->childButtons[i][j].model->texture = buttonTextures->idle;
    master->childButtons[i][j].buttonRules = NULL;
    master->childButtons[i][j].ButtonSelected = NULL;
    master->childButtons[i][j].submitted = false;
    master->childButtons[i][j].wasFlippedIncorrectly = false;
    master->childButtons[i][j].shouldStaySubmitted = false;
    master->childButtons[i][j].isBelowEdge = false;
    master->childButtons[i][j].isAboveEdge = false;
    master->childButtons[i][j].isLeftEdge = false;
    master->childButtons[i][j].isRightEdge = false;
    master->childButtons[i][j].sharedWindowOpened = false;
    master->childButtons[i][j].id = rand();
    dynamicModels[*lastModelIndex] = master->childButtons[i][j].model;
    *lastModelIndex = *lastModelIndex + 1;


    if (master->sharedPuzzle)
    {
	if (master->gameAPuzzle == true)
	{
	    if (i + 1 > halfRows)
	    {
		master->childButtons[i][j].model->modelVisible = false;
	    }
	}
	else
	{
	    if (i < halfRows)
	    {
		master->childButtons[i][j].model->modelVisible = false;
	    }
	}
    }

    
											       
											       
    if (j < 1)
    {
        master->childButtons[i][j].isBelowEdge = true;
    }
    if (j + 1 >= master->columns)
    {
        master->childButtons[i][j].isAboveEdge = true;
    }
    if (i < 1)
    {
        master->childButtons[i][j].isLeftEdge = true;
    }
    if (i + 1 >= master->rows)
    {
        master->childButtons[i][j].isRightEdge = true;
    }
    //highlighting our middle button
    printf("creating button model\n");
											       
    if (i == master->highlightStartLoc.x && j == master->highlightStartLoc.y)
    {
        SwitchTextureOnPuzzleState(master, &master->childButtons[i][j], true);
	master->cursoredButton = &master->childButtons[master->highlightStartLoc.x][master->highlightStartLoc.y];
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
            button->buttonState = EBS_idle;
        }
        else
        {
            button->highlighted = true;
            button->buttonState = EBS_highlighted;
            AddHighlight(button);
        }
        break;
    case EPS_inactive:
        button->model->texture = button->buttonTextures->off;
        button->buttonState = EBS_off;
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
    if (button->buttonTextureLocation != TCL_NULL)
    {
        UpdateShaderForButtonAtlas(button, button->buttonTextureLocation);
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
    if (master->lerpRotPuzzle == false) master->originalAngle = angle;
    angle = angle * DEG2RAD;
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
//	    master->childButtons[i][j].model->model.transform = MatrixRotate(axis, angle);
        }
    }
}

void OnPuzzleCompleted(ButtonMaster* master)
{
    printf("\n");
    printf("puzzle complete\n");
    printf("\n");
    if (master->id == 1)
    {
        master->player->playerHUD[2]->hidden = true;
    }
    EnactGameplayElement(master->associatedGameplayElements, master->gameplayElementIndex, master->switchId, master->gameplayElementType);

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
            if (puzzle->childButtons[i][j].shouldStayPoweredOff == true) continue;
            SwitchTextureOnPuzzleState(puzzle, &puzzle->childButtons[i][j], puzzle->childButtons[i][j].highlighted);
        }
    }
}

void AssignGameplayElementsToPuzzles(ButtonMaster* puzzle, GameplayElements* gameplayElements, enum GameplayElementType gameplayElementType, int gameplayElementIndex, int indicatorIndex)
{
    puzzle->gameplayElementType = gameplayElementType;
    switch (gameplayElementType)
    {
    case GET_NULL:
	puzzle->associatedGameplayElements = NULL;
	printf("should be null\n");
	break;
    case GET_Basic:
	puzzle->associatedGameplayElements->associatedIndicator = FindIndicator(indicatorIndex, gameplayElements->indicators, NUMBER_OF_INDICATORS_A);
	
	if (puzzle->associatedGameplayElements->associatedIndicator == NULL)
	{
	    printf("Associated indicator is null error\n");
	    return;
	}
	break;
    case GET_Door:
	puzzle->associatedGameplayElements->associatedDoor = gameplayElements->doors[gameplayElementIndex];
	puzzle->associatedGameplayElements->switchBox = NULL;
	printf("assigning door as gameplayElement\n");
	if (indicatorIndex == 0) break;
	puzzle->associatedGameplayElements->associatedIndicator = FindIndicator(indicatorIndex, gameplayElements->indicators, NUMBER_OF_INDICATORS_A);
	printf("indicator also assigned to GET DOOR\n");
	break;
    case GET_SwitchBox:
	puzzle->associatedGameplayElements->associatedDoor = NULL;
	puzzle->associatedGameplayElements->switchBox = &gameplayElements->switchBox[gameplayElementIndex];
	puzzle->switchId = puzzle->associatedGameplayElements->switchBox[gameplayElementIndex]->lastSwitchId;
	puzzle->associatedGameplayElements->switchBox[gameplayElementIndex]->lastSwitchId = puzzle->associatedGameplayElements->switchBox[gameplayElementIndex]->lastSwitchId + 1;
	puzzle->associatedGameplayElements->associatedIndicator = FindIndicator(indicatorIndex, gameplayElements->indicators, NUMBER_OF_INDICATORS_A);
	printf("assigned switchBox as gamepalyElement\n");
	break;
    default:
	printf("ERROR DEFUALT RUN IN ASSIGNATION OF GAMEPLAY ELEMENTS\n");
    }
}

Indicator* FindIndicator(int id, Indicator** indicators, int numOfIndicators)
{
    printf("about to find indicator\n");
    for (int i = 0; i < numOfIndicators; i++)
    {
	if (indicators[i] == NULL)
	{
	    printf("indicator here is null\n");
	    continue;
	}
	printf("here in indicators\n");
	if (indicators[i]->id == id)
	{
	    printf("here in indicators 2.0\n");
	    return indicators[i];
	}
	printf("here in indicators 2.3\n");
    }
    return NULL;
}
 
void EnactGameplayElement(GameplayElements* gameplayElement, int gameplayElementIndex, int switchId, enum GameplayElementType gameplayElementType)
{
    printf("enacting gameplay element\n");
    if (gameplayElement != NULL)
    {
	switch (gameplayElementType)
	{
	case GET_NULL:
	    printf("Value not set in gameplayElementType\n");
	    break;
	case GET_Basic:
	    gameplayElement->associatedIndicator->PowerOnIndicator(gameplayElement->associatedIndicator);
	    break;
	case GET_Door:
	    gameplayElement->associatedDoor->isLowering = true;
	    if (gameplayElement->associatedIndicator == NULL) break;
	    gameplayElement->associatedIndicator->PowerOnIndicator(gameplayElement->associatedIndicator);
	    break;
	case GET_SwitchBox:
	    printf("checking switch box\n");
	    QuerySwitchBox(gameplayElement->switchBox, gameplayElementIndex, switchId);
	    if (gameplayElement->associatedIndicator != NULL)
	    {
		gameplayElement->associatedIndicator->PowerOnIndicator(gameplayElement->associatedIndicator);
	    }
	    break;
	default:
	    printf("ERROR DEFAULT RUN IN ENACTGAMEPLAYELEMENT\n");
	    break;
	}
    }
    printf("gameplay element enacted\n");
}

void ConstructSinglePuzzle(int* lastPuzzleIndex, int columns, int rows, Vector3 location, FPSPlayer* player, void(*puzzleLocConstruct)(ButtonMaster*), enum GameplayElementType gameplayElementType, GameplayElements* gameplayElements, int gameplayElementIndex, int indicatorIndex, ButtonMaster** gameAPuzzles, Vector2Int highlightStart, bool hasHighlightStartLoc, enum PuzzleState puzzleState, float buttonSpread, bool sharedPuzzle, bool gameA, Vector3 puzzleLerpOffset, ExitCode* exitCode)
{
    if (lastPuzzleIndex == NULL || player == NULL)
    {
	EditReturnCodeInfo(208, "PuzzleIndex/Player null upon puzzle construction", exitCode);
	return;
    }
    ButtonMaster* puzzle = malloc(sizeof(ButtonMaster));
    if (puzzle == NULL)
    {
	EditReturnCodeInfo(200, "Failed To allocate memory for puzzle\n", exitCode);
	return;
    }

    puzzle->gameAPuzzle = gameA;
    puzzle->columns = columns;
    puzzle->rows = rows;
    puzzle->sharedPuzzle = sharedPuzzle;
    puzzle->isCursorOnScreen = true;
    puzzle->location = location;
    puzzle->originalAngle = 0.0f;
    puzzle->tempAngle = 0.0f;
    puzzle->lerpRotPuzzle = false;
    puzzle->puzzleToPowerOn = NULL;
    puzzle->buttonSpread = buttonSpread == 0.0f ? 0.5 : buttonSpread;
    puzzle->hasBoxAssigned = false;
    puzzle->id = *lastPuzzleIndex;
    puzzle->player = player;
    puzzle->puzzleState = puzzleState;
    puzzleLocConstruct(puzzle);
    puzzle->highlightStartLoc = highlightStart;
    puzzle->hasHighlightStartLoc = hasHighlightStartLoc;
    puzzle->shouldReadTick = false;
    puzzle->numOfSubmittedButtons = 0;
    puzzle->puzzleUnSolved = false;
    puzzle->shouldBlinkCursor = true;
    puzzle->cursoredButton = NULL;
    puzzle->errorButtons = NULL;
    puzzle->solvedButtons = NULL;
    puzzle->numOfSolved = 0;
    puzzle->numOfSelected = 0;
    puzzle->puzzleInputType = EPIT_Enabled;
    puzzle->plainSubmittedButtons = NULL;
    puzzle->numOfPlainSubmittedButtons = 0;
    puzzle->sharedReach = NULL;
    puzzle->sharedPuzzleTwinId = 0;
    puzzle->gameplayElementIndex = gameplayElementIndex;
    puzzle->plainSubmittedButtonsMax = columns - 1;
    puzzle->OnPuzzleSolved = OnPuzzleCompleted;
    puzzle->submitBuffer = NULL;
    puzzle->puzzleLerpOffset = puzzleLerpOffset;
    puzzle->puzzleNormalDirection = (Vector3){0};
    puzzle->associatedGameplayElements = malloc(sizeof(GameplayElements));

    if (puzzle->sharedPuzzle == true)
    {
	if (puzzle->gameAPuzzle == true)
	{
	    if (puzzle->highlightStartLoc.x + 1 > rows / 2)
	    {
		puzzle->isCursorOnScreen = false;
	    }
	} 
	else
	{
	    if (puzzle->highlightStartLoc.x < rows / 2)
	    {
		puzzle->isCursorOnScreen = false;
	    }
	}
    }
    
    if (puzzle->associatedGameplayElements == NULL)
    {
	EditReturnCodeInfo(201, "Failed to allocate memory for puzzle's associated gameplay elements\n", exitCode);
    }

    AssignGameplayElementsToPuzzles(puzzle, gameplayElements, gameplayElementType, gameplayElementIndex, indicatorIndex);

/*
    if (hasGameplayElements == true)
    {
        AssignGameplayElementsToPuzzles(puzzle, gameplayElements->doors[gameplayElementIndex]);
    }
    else
    {
        AssignGameplayElementsToPuzzles(puzzle, NULL);
    }
*/
    
    gameAPuzzles[*lastPuzzleIndex] = puzzle;
    *lastPuzzleIndex = *lastPuzzleIndex + 1;

    exitCode->numOfPuzzlesLoaded = exitCode->numOfPuzzlesLoaded + 1;
}

void FillSharedPuzzleList(ButtonMaster** allPuzzles, int numOfPuzzles, SharedPuzzleList** sharedPuzzleList)
{
    printf("about to assign shared buttons\n");
    for (int i = 0; i < numOfPuzzles; i++)
    {
	if (allPuzzles[i]->sharedPuzzle == true)
	{
	    printf("in loop, puzzle found, maing assignation\n");
	    printf("\n");
	    printf("\n");
	    AddPuzzleToSharedPuzzleList(allPuzzles[i], sharedPuzzleList);
	}
    }
}

void AddPuzzleToSharedPuzzleList(ButtonMaster* puzzle, SharedPuzzleList** head)
{
    printf("about to add puzzle to list here\n");
    SharedPuzzleList* newNode = (SharedPuzzleList*)malloc(sizeof(SharedPuzzleList));
    if (newNode == NULL)
    {
	printf("ERROR, FAILED TO ALLOCATE MEMORY FOR SHARED PUZZLE LIST\n");
	return;
    }
    newNode->puzzle = puzzle;
    printf("sharedPuzzleId: %i\n", puzzle->sharedPuzzleId);
    newNode->sharedId = puzzle->sharedPuzzleId;
    newNode->next = NULL;
    if (*head == NULL)
    {
	*head = newNode;
	printf("*head id: %i\n", newNode->sharedId);
	return;
    }
    SharedPuzzleList* lastNode = *head;
    while(lastNode->next != NULL)
    {
	lastNode = lastNode->next;
    }
    lastNode->next = newNode;
    printf("shared id at next: %i\n", lastNode->next->sharedId);

    SharedPuzzleList* temp = *head;
    while (temp != NULL)
    {
	printf("shared id: %i\n", temp->sharedId);
	temp = temp->next;
    }
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

void AssignAllPuzzlesSolutionButtons(ButtonMaster** allPuzzles, int numOfPuzzles, ExitCode* exitCode)
{
    for (int i = 0; i < numOfPuzzles; i++)
    {
        AssignSolutionButtonsToPuzzle(allPuzzles[i], exitCode);
    }
}

void AssignSolutionButtonsToPuzzle(ButtonMaster* puzzle, ExitCode* exitCode)
{
    puzzle->correctOrder = malloc(sizeof(int) * puzzle->numberOfSolutions);
    if (puzzle->correctOrder == NULL)
    {
	EditReturnCodeInfo(206, "Failed to allocate memory for puzzle correct order\n", exitCode);
	return;
    }
    printf("num of solutions: %i\n", puzzle->numberOfSolutions);
    for (int i = 0; i < puzzle->numberOfSolutions; i++)
    {
        puzzle->solutionButtons[i] = &puzzle->childButtons[puzzle->solutionLocations[i].y][puzzle->solutionLocations[i].x]; //be sure to remove the dangling pointers when these are destroyed   
        puzzle->solutionButtons[i]->textureSizes = puzzle->textureSizes[i];
        puzzle->solutionButtons[i]->buttonSolutionIndex = i;
        printf("buttonSolutionIndex is: %i\n", puzzle->solutionButtons[i]->buttonSolutionIndex);
        puzzle->correctOrder[i] = puzzle->textureSizes[i];
    }

}

void AssignButtonSpecialTextureAndAction(Button* button, enum TextureCoordinateLocations textureLocations)
{
    if (textureLocations != TCL_OFF || textureLocations != TCL_SUB)
    {
        UpdateShaderForButtonAtlas(button, textureLocations);
	if (textureLocations == TCL_Window)
	{
	    printf("\n");
	    printf("shader updated for window button\n");
	    printf("\n");
	}
    }

    switch(textureLocations)
    {
    case TCL_OFF:
	button->buttonState = EBS_off;
	button->model->texture = button->buttonTextures->off;
	button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture;
	button->shouldStayPoweredOff = true;
	break;
    case TCL_SUB:
	button->buttonState = EBS_selected;
	button->model->texture = button->buttonTextures->selected;
	button->model->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = button->model->texture;
	button->shouldStaySubmitted = true;
	break;
    case TCL_Move:
	AssignMoveAction(button, textureLocations);
	break;
    case TCL_Window:
	button->puzzleType = EPT_WindowPower;
	UpdateShaderForButtonAtlas(button, 48);
	break;
    default:
	break;
    }
    
    AssignToggleAction(button, textureLocations);
}

void AssignSolutionsTextures(ButtonMaster* puzzle)
{
    printf("about to assign solution textures\n");
    for (int i = 0; i < puzzle->numberOfSolutions; i++)
    {
	printf("i: %i\n", i);
        DetermineAndUpdateTexture(puzzle->solutionButtons[i], puzzle->solutionButtons[i]->buttonState);
    }
    printf("Solution textures assigned gameb\n");
}

void DetermineAndUpdateTexture(Button* button, enum ButtonState state)
{
    printf("determining value\n");
    int startingValue = 2;
    if (button->buttonRules != NULL && button->buttonRules->toggleRule != NULL)
    {
        DetermineStartVal(&startingValue, button->buttonRules->toggleRule->puzzleOODirection);
    }
    startingValue += button->textureSizes;
    if (button->textureSizes == EBTS_NULL) return;
    UpdateShaderForButtonAtlas(button, startingValue);
}

void DetermineStartVal(int* min, enum PuzzleOnOffDirection direction)
{
    switch (direction)
        {
        case POOD_BottomUp:
            *min = 14;
            break;
        case POOD_DDL:
            *min = 38;
            break;
        case POOD_DRL:
            *min = 30;
            break;
        case POOD_DUL:
            *min = 30;
            break;
        case POOD_DUR:
            *min = 38;
            break;
        case POOD_LeftRight:
            *min = 22;
            break;
        case POOD_RightLeft:
            *min = 22;
            break;
        case POOD_TopDown:
            *min = 14;
            break;
        default:
            printf("ERROR, DEFAULT RUN IN DETERMINING TEXTURE\n");
        }
}

void AssignAllPuzzlesNormals(ButtonMaster** allPuzzles, int numOfPuzzles)
{
    for (int i = 0; i < numOfPuzzles; i++)
    {
        allPuzzles[i]->puzzleNormalDirection = CalculatePuzzleNormal(allPuzzles[i]);
        printf("PuzzleNormal: %f, %f, %f\n", allPuzzles[i]->puzzleNormalDirection.x, allPuzzles[i]->puzzleNormalDirection.y, allPuzzles[i]->puzzleNormalDirection.z);
        printf("\n");
    }
}

Vector3 CalculatePuzzleNormal(ButtonMaster* puzzle)
{
    int centerR = floor((float)puzzle->rows / 2.0);
    int centerC = floor((float)puzzle->columns / 2.0);
    Vector3 v1, v2, v3;
    GetVertsForNonIndexedMesh(puzzle->childButtons[centerR][centerC].model->model.meshes[0].vertices, 210, &v1, &v2, &v3);

    

    


    Vector3 normal = Vector3CrossProduct(Vector3Subtract(v2, v1), Vector3Subtract(v3, v1));
    

    normal = Vector3Transform(normal, puzzle->childButtons[centerR][centerC].model->model.transform);
    normal = Vector3Normalize(normal);
    normal = Vector3Scale(normal, -1.0f);
    //normal = Vector3Add(puzzle->location, normal);
    return normal;
}


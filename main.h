#include "C:\raylib\raylib\src\raylib.h"
#include "models/src/model.h"
#include "libs/drawingstructs.h"
#include "gameplay/gameplaystructs.h"
#include "gameplay/inactivestate.h"
#include "gameplay/gameplayelements.h"
#include "ui/src/uistructs.h"
#include "ui/src/ui.h"

void CallAllPolls(float dTime, modelInfo** models, QueryBox** areaBoxes, Interactable* interactedItem, OverlapBox** overlapBoxes, int numberOfModelss, int numOfAreaQueryBoxes);

void Draw(modelInfo** models, Raycast* ray, QueryBox** queryBoxes, UIElements** ui, OverlapBox** overlapQueryList, int numberOfModels, int numberOfQueryBoxes, int numberOfInteractable);

void Draw2D(UIElements** ui);



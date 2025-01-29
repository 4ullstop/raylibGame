#include "C:\raylib\raylib\src\raylib.h"
#include "models/src/model.h"
#include "libs/drawingstructs.h"
#include "gameplay/gameplaystructs.h"
#include "gameplay/inactivestate.h"
#include "gameplay/gameplayelements.h"
#include "ui/src/uistructs.h"
#include "ui/src/ui.h"
#include "models/src/texture.h"
#include "shared/sharedstructs.h"
#include "destruction/destroyobjects.h"
#include "initialization/windowstructs.h"


void CallAllPolls(float dTime, modelInfo** models, QueryBox** areaBoxes, Interactable* interactedItem, OverlapBox** overlapBoxes, int numberOfModelss, int numOfAreaQueryBoxes, ExitCode* exitCode);

void Draw(modelInfo** models, Raycast* ray, QueryBox** queryBoxes, UIElements** ui, OverlapBox** overlapQueryList, int numberOfModels, int numberOfQueryBoxes, int numberOfInteractable, ButtonMaster** allPuzzles);

void Draw2D(UIElements** ui);

void ReportError(ExitCode* exitCode);

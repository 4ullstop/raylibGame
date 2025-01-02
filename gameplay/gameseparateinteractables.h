#ifndef GAMESEPARATEINTERACTABLES_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "../initialization/corestructs.h"
#include "../collision/interactionbox.h"
#include "../gamea/gameainteractables.h"
#include "../gameb/gamebinteractables.h"
#endif

void CreateInteractablesForGameType(Interactable** interactables, QueryBox** areaQueryBoxes, ButtonMaster** allPuzzles, enum Gametype type, ExitCode* exitCode);

#ifndef OVERLAPBOX_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "../externmath/externmath.h"
#include "interactionbox.h"
#include "externcollision.h"
#endif 

void ConstructOverlapBoxes(OverlapBox** allBoxes, ExitCode* exitCode);

void AddBoxToQueryList(OverlapBox* newBox, OverlapBox* allQueriedBoxes);

void RemoveBoxFromQueryList(OverlapBox* boxToRemove, int id);

void DestroyOverlapBoxes(OverlapBox** allBoxes);

void PlayerInInteractHintBox(FPSPlayer* player, OverlapBox* box);

void PollOverlaps(OverlapBox** queryList, FPSPlayer* player);

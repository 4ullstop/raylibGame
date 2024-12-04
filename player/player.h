#ifndef PLAYER_HEADER
#define PLAYER_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "controller.h"
#include "../collision/overlapboxes.h"
#endif

void PollPlayer(float deltaTime, PlayerCam* pcam, FPSPlayer* player, CollisionPacket* colPacket, modelInfo** models, int numOfModels);

void DrawPlayerCollisionCapsule(Vector3 location);

void PlayerSetup(FPSPlayer* player, PlayerCam* cam, UIElements** hud, enum Gamemode* mode);

void PollPlayerSecondary(FPSPlayer* player, Raycast* interactRay, QueryBox** areaBoxes, enum Gamemode* mode, Interactable* interactedItem, int numOfAreaQueryBoxes, bool* hideHideableObjects);

void PollPlayerPuzzle(Interactable* interactedItem, enum Gamemode* mode);

void PollPlayerOverlaps(OverlapBox** queryList, FPSPlayer* player);

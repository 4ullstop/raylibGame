#ifndef PLAYER_HEADER
#define PLAYER_HEADER
#include "C:\raylib\raylib\src\raylib.h"
#include "controller.h"
#endif

void PollPlayer(float deltaTime, PlayerCam* pcam, FPSPlayer* player, CollisionPacket* colPacket, modelInfo** models);

void DrawPlayerCollisionCapsule(Vector3 location);

void PlayerSetup(FPSPlayer* player, PlayerCam* cam);

void PollPlayerSecondary(FPSPlayer* player, Raycast* interactRay, QueryBox** areaBoxes, enum Gamemode* mode, Interactable* interactedItem);

void PollPlayerPuzzle(ButtonMaster* master);
